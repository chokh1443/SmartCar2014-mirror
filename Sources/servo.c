#include "servo.h"

void Servo_init(Servo * this){
	
}


void Servo_runAs(Servo * this, int16_t steer){
	if (steer > 100) {
		steer = 100;
	} else if (steer < -100) {
		steer = -100;
	}
	steer = steer * 90 / 100;
	steer = 1615 + steer;//1615 is mid of servo
	
	this->steer=steer;
}

void Servo_pidTick(Servo * this){
	static int cnt = 0;
	cnt++;
	if (cnt > 1000) {
		//FIX ME : cnt > some number
		//servo works every 160ms
		PWM_SET(PWM_SERVO, this->steer);//FIX ME : OOP
		cnt = 0;
	}
}
