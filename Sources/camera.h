#pragma once
#include "typedefs.h"
#include "board.h"

typedef struct {
	void (*onTick)(void * this);
} Camera;

void Camera_init(Camera * this, uint8_t id);
