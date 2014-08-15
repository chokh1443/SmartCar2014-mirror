#pragma once

#include "typedefs.h"

typedef struct {
	uint8_t data[16];
	uint8_t len;
} LEDData;

typedef struct {
	LEDData data;
	
	uint8_t id;
	uint8_t index;
} BarLED;

void BarLED_init(BarLED * this, uint8_t id);
void BarLED_print(BarLED * this, LEDData data);
void BarLED_onTick(BarLED * this);

void LEDData_add(LEDData * this, uint8_t pos);
