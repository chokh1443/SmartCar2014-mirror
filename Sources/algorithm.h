#pragma once

#include "smartcar.h"
#include "bluetooth.h"

typedef struct {
	int16_t arr[128];
	int16_t max;
	int16_t min;
} AIData;

void AIData_init(AIData * this, Camera * camera);
uint8_t findLine(AIData * data);
void differential(AIData * data);
void binarization(AIData * data);
uint8_t findIndex(AIData * data);
int16_t handling(uint16_t right, uint16_t left);
void dumpData(int16_t * data, BarLED * led);
void start(SmartCar * smartCar);


