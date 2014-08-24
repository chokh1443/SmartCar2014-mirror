#include "algorithm.h"
#include "utils.h"

//camera inputing	time = 0.04~0.06s(about 50ms)
//servo motor moving time = 0.2s(200ms)
//we have about 4 data for moving servo motor
//make map using 5 camera data

void start(SmartCar * smartCar){
	uint16_t handle, speed;
	AIData data[2];
	int8_t pos[2];
	Servo_runAs(&smartCar->servo, 0);
	Motor_runAs(&smartCar->motor, 30);
	while(1){
		AIData_init(&data[0], &smartCar->camera[0]);
		AIData_init(&data[1], &smartCar->camera[1]);

		binarization(&data[0]);
		binarization(&data[1]);

		pos[0] = findIndex(&data[0]);
		pos[1] = findIndex(&data[1]);

		pos[0] = pos[0] - 64;

		if(pos[0] < 0) {
			pos[0] = pos[0] * pos[0] / 32;
		} else {
			pos[0] = pos[0] / 16;
		}

		pos[1] = 64 - pos[1];

		if(pos[1] > 0 ){
			pos[1] = pos[1] * pos[1] / 32;
		} else {
			pos[1] = pos[1] /16;
		}
		
		//decide handling value
		Servo_runAs(&smartCar->servo, (pos[0] + pos[1])/2);
		//decide speed value
		// TODO
	}
}

void AIData_init(AIData * this, Camera * camera){
	int16_t min = 0, max = 0;
	uint16_t * data = camera->rawData;
	register uint16_t i;

	this->arr[0] = this->arr[0] - this->arr[1];
	for(i = 1; i < 128; i++){
		this->arr[i] = data[i-1] - data[i];

		if(min > this->arr[i]){
			min = this->arr[i];
		}
		if(max < this->arr[i]){
			max = this->arr[i];
		}
	}
	this->min = min;
	this->max = max;

}
uint8_t findLine(AIData * data){
	binarization(data);
	return findIndex(data);
}
void binarization(AIData * data){
	register uint16_t i;
	int16_t lowCrit = data->min/2;
	int16_t highCrit = data->max/2;
	
	for(i = 0; i < 128; i++){
		if(data->arr[i] > highCrit) {
			data->arr[i] = 0;
		} else if(data->arr[i] < lowCrit){
			data->arr[i] = 1;
		} else {
			data->arr[i] = data->arr[i-1];
		}
	}
}
uint8_t findIndex(AIData * data){
	register uint16_t i;

	uint16_t first, last;
	for(i = 0; i < 128; i++){
		if(data->arr[i] == 1){
			last = i;
		} else {
			first = i;
			if(last - first <= 2){
				//noize
			} else {
				return (last + first)/2;
			}
		}
	}
}

