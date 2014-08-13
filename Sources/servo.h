#pragma once
#include "typedefs.h"

typedef struct {
	void (*steer)(void * this, int32_t target);
} Servo;

void initServo(Servo * this);
