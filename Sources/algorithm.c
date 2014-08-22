#include "algorithm.h"
#include "utils.h"

//camera inputing	time = 0.04~0.06s(about 50ms)
//servo motor moving time = 0.2s(200ms)
//we have about 4 data for moving servo motor
//make map using 5 camera data

typedef struct {
	int16_t data[128];
	Range range;
} DifferentialData;

void getDifferentialData(uint16_t * data, DifferentialData * result);
void binarization(DifferentialData * differentialData, uint8_t * result);
int8_t findIndex(uint8_t * data);
int8_t findLine(Camera * camera);

void start(SmartCar * smartCar){
	uint16_t handle, speed;
	Servo_runAs(&smartCar->servo, 0);
	Motor_runAs(&smartCar->motor, 30);
	while(1){
		int8_t pos[2];
		pos[0] = findLine(&smartCar->camera[0]);
		pos[1] = findLine(&smartCar->camera[1]);

		//decide handling value
		Servo_runAs(&smartCar->servo, ((pos[0] - 64) + (64 -pos[1]))/2);
		//decide speed value
		
	}
}

int8_t findLine(Camera * camera){

	uint16_t * data = Camera_get(camera);
	DifferentialData differentialData;
	uint8_t result[128];

	getDifferentialData(data, &differentialData);
	binarization(&differentialData, result);
	return findIndex(result);
}
void getDifferentialData(uint16_t * data, DifferentialData * result){
	int16_t min = 0, max = 0;
	register uint16_t i;

	result->data[0] = data[0];
	for(i = 1; i < 128; i++){
		result->data[i] = data[i-1] - data[i];

		if(min > result->data[i]){
			min = result->data[i];
		}
		if(max < result->data[i]){
			max = result->data[i];
		}
	}
	result->range.low = min;
	result->range.high = max;
}

void binarization(DifferentialData * differentialData, uint8_t * result){
	int16_t lowCrit = ((int16_t)differentialData->range.low)/2;
	int16_t highCrit = ((int16_t)differentialData->range.high)/2;
	int16_t * diffedData = differentialData->data;

	register uint16_t i;

	result[0] = 0;
	for(i = 1; i < 128; i++){
		if(diffedData[i] > highCrit) {
			result[i] = 0;
		} else if(diffedData[i] < lowCrit){
			result[i] = 1;
		} else {
			result[i] = result[i-1];
		}
	}
}
int8_t findIndex(uint8_t * data){
	//TODO nozie controll
	register uint16_t i;

	uint16_t first, last;
	for(i = 0; i < 128; i++){
		if(data[i] == 1){
			last = i;
		} else {
			first = i;
			if(last - first <= 2){
				//nozie
			} else {
				return (last + first)/2;
			}
		}
	}
}

