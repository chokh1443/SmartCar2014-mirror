#pragma once
#include "typedefs.h"
#include "board.h"
#include "encoder.h"

typedef struct {
	void (*runAs)(void * this, int16_t);
	void (*pidTick)(void * this);
	
	Encoder * encoder;
	
	int16_t targetSpeed;
} Motor;

void initMotor(Motor * this, Board * board);
