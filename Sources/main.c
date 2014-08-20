
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "smartcar.h"
#include "gpio_drv.h"
#include "test.h"
#include "utils.h"
#include "preset.h"

/**********************  Function Prototype here *************************/

void main(void);
void start(SmartCar * smartCar);

unsigned char newLine[2] = {'\r','\n'};


/*********************  Initialization Function(s) ************************/

void main(void) {
	SmartCar smartCar;
	sys_init_fnc();
	EnableExternalInterrupts();
	
	SmartCar_init(&smartCar);
	
	while(1){
		switch(board.button.read()){
		case 1:
			test(&smartCar);
			break;
		case 2:
			start(&smartCar);
			break;
		case 3:
			//preset(&smartCar);
			break;
		}
	}
	
	/*
	 * usages :
	 * board.gpio.on(68);
	 * board.led.off(1);
	 * 
	 * pEncoder = board.encoder;
	 * encoder.get(pEncoder);
	 * encoder.onTick(pEncoder);
	 */

}

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
int8_t findLine(Camera * camera);

void start(SmartCar * smartCar){
	uint8_t i, j;					// 0 left, 1 right
	while(1){
		int8_t pos[2];
		pos[0] = findLine(&smartCar->camera[0]);
		pos[1] = findLine(&smartCar->camera[1]);
		
	}
}
int8_t findIndex(uint8_t * data);

int8_t findLine(Camera * camera){
	
	uint16_t * data = Camera_get(camera);
	DifferentialData differentialData;
	uint8_t result[128];
	
	getDifferentialData(data, &differentialData);
	binarization(&differentialData, result);
	findIndex(result);
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
	register uint16_t i;
	
	uint16_t first, last;
	for(i = 0; i < 128; i++){
		if(data[i] == 1){
			last = i;
		} else {
			
			first = i;
		}
		
	}
}
