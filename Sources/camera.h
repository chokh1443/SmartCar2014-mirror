#pragma once

#include "typedefs.h"
#include "board.h"

typedef struct {
	uint16_t rawData[128];
	uint16_t lineData[128];
	Camera_Pins pins;
} Camera;

typedef struct {
	uint8_t CLK;
	uint8_t SI;
} Camera_Pins;

void Camera_init(Camera * this, uint8_t id);
uint16_t * Camera_get(Camera * this);
