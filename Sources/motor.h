#pragma once
#include "typedefs.h"
#include "board.h"
#include "encoder.h"

typedef struct {
	Encoder * encoder;
	int16_t targetSpeed;
	
	int32_t kp;
	int32_t ki;
	int32_t kd;
	
	int32_t err[3];
} Motor;

void Motor_init(Motor * this);
void Motor_runAs(Motor * this, int16_t);
void Motor_Enable(Motor * this);
void Motor_Disable(Motor * this);
void Motor_setkp(Motor * this, int32_t val);
void Motor_setki(Motor * this, int32_t val);
void Motor_setkd(Motor * this, int32_t val);
void Motor_addErr(Motor * this, int32_t newErr);
int32_t Motor_PID(Motor * this);
void Motor_pidTick(Motor * this);
