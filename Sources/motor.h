#pragma once
#include "typedefs.h"
#include "board.h"
#include "encoder.h"

typedef struct {
	Encoder * encoder;
	int16_t targetSpeed;
} Motor;

void Motor_init(Motor * this);
void Motor_runAs(Motor * this, int16_t);
void Motor_pidTick(Motor * this);
void Motor_Enable(void);
void Motor_Disable(void);
