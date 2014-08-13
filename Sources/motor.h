#pragma once
#include "typedefs.h"

typedef struct {
	void (*runAs)(void * this, int16_t);
	void (*pidTick)(void * this);
} Motor;

void initMotor(Motor * this);
