#include "servo.h"
#include "board.h"

void Servo_init(Servo * this){
	//board.addMotorPIDHandler(bind(this, (ThisCall)Servo_pidTick));
	//init that servo is mid
	this->steer = 0;
	board.pwm.set(PWM_SERVO, 1615);
}


void Servo_runAs(Servo * this, int16_t steer){
	if (steer > 100) {
		steer = 100;
	} else if (steer < -100) {
		steer = -100;
	}
	
	this->steer=steer;
	
	board.pwm.set(PWM_SERVO, (steer * 90 / 100) + 1615);
}

void Servo_pidTick(Servo * this){
	// ignore this func
}
