#pragma once

#include "typedefs.h"
#include "board.h"

typedef struct {
	void (*onTick)(void * this);
	uint8_t ledLine[2][16];
	
	uint8_t * ENABLE_BAR;
	uint8_t * NUMBER_BAR;
} BarLED;

void BarLED_init(BarLED * this, uint8_t id);
void BarLED_print(BarLED * this, Camera * camera, uint16_t black);
void BarLED_onTick(BarLED * this);
