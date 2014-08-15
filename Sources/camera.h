#pragma once

#include "typedefs.h"
#include "board.h"

typedef struct {
	uint16_t data1[128];
	uint16_t data2[128];
} Camera;

void Camera_init(Camera * this, uint8_t id);
uint16_t * Camera_get(Camera * this);
