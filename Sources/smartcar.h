#pragma once

#include "board.h"
#include "encoder.h"
#include "camera.h"
#include "segment.h"
#include "barled.h"
#include "servo.h"
#include "motor.h"


typedef struct {
	Encoder encoder;
	Camera camera[2];
	
	Segment segment[3];
	BarLED barLED[2];
	
	Servo servo;
	Motor motor;
} SmartCar; 

void SmartCar_init(SmartCar * smartCar);
