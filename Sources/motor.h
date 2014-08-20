#pragma once
#include "typedefs.h"
#include "board.h"
#include "encoder.h"

typedef struct {
	Encoder * encoder;
	int16_t targetSpeed;
	
	int32_t kp = 0x00000000;
	int32_t ki = 0x00000000;
	int32_t kd = 0x00000000;
} Motor;

void Motor_init(Motor * this);
void Motor_runAs(Motor * this, int16_t);
void Motor_pidTick(Motor * this);
void Motor_Enable(Motor * this);
void Motor_Disable(Motor * this);
