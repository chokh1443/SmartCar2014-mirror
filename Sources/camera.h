#pragma once
#include "typedefs.h"
#include "board.h"

typedef struct {
	void (*onTick)(void * this);
} Camera;

void initCamera(Camera * this, Board * board, uint8_t id);
