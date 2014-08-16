#include "servo.h"

void Servo_init(Servo * this){
	//init that servo is mid
	this->steer = 0;
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
		board.pwm.set(PWM_SERVO, this->steer);
		cnt = 0;
	}
}
