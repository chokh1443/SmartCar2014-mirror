#pragma once
#include "typedefs.h"
#include "board.h"

typedef struct {
	int16_t steer;
} Servo;

void Servo_init(Servo * this);
void Servo_runAs(Servo * this, int16_t);
void Servo_pidTick(Servo * this);
