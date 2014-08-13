#include "motor.h"

void MOTOR_RUN_AS(Motor * this, int16_t targetSpeed);
void MOTOR_PID_TICK(Motor * this);

void initMotor(Motor * this, Board * board){
	this->runAs = (void (*)(void *, int16_t))MOTOR_RUN_AS;
	this->pidTick = (void (*)(void *))MOTOR_PID_TICK;
	
	//this->encoder = &board->;
	
	/*EventHandler handler = bind(this, this->pidTick);
	board->timerInterrupt.addHandler(&board->timerInterrupt, handler);
	
	board->timerInterrupt.setInterval(&board->timerInterrupt, 8000);*/
}

void MOTOR_RUN_AS(Motor * this, int16_t targetSpeed){
	this->targetSpeed = targetSpeed;
}
void MOTOR_PID_TICK(Motor * this){
	int32_t kp = 0x00000000;
	int32_t ki = 0x00000000;
	int32_t kd = 0x00000000;
	
	int16_t speed = this->encoder->get(this->encoder);
	
}
