#pragma once
#include "typedefs.h"
#include "board.h"

typedef struct {
	void (*onTick)(void * this);
} BarLED;

void initBarLED(BarLED * this, Board * board, uint8_t id);
