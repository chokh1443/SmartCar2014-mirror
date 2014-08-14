#pragma once

#include "typedefs.h"
#include "board.h"

typedef struct {
	void (*onTick)(void * this);
} BarLED;

void BarLED_init(BarLED * this, uint8_t id);
