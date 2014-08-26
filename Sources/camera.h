#pragma once

#include "typedefs.h"
#include "board.h"

typedef struct {
	uint16_t rawData[128];

	uint8_t id;
	uint8_t count;
	
	uint32_t sum;
	uint32_t average;
} Camera;

void Camera_init(Camera * this, uint8_t id);
uint16_t * Camera_get(Camera * this);
uint32_t Camera_getInterval();
uint16_t Camera_minValue(Camera * this);
uint16_t Camera_maxValue(Camera * this);
