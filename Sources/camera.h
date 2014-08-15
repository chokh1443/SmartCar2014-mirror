#pragma once

#include "typedefs.h"
#include "board.h"

typedef struct {
	uint16_t rawData[2][128];
	uint16_t lineData[2][128];
} Camera;

void Camera_init(Camera * this, uint8_t id);
uint16_t * Camera_get(Camera * this);
