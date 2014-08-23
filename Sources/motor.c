#include "motor.h"

int32_t Motor_PID(Motor * this);

void Motor_init(Motor * this, Encoder * encoder){
	this->encoder = encoder;
	this->targetSpeed = 0;
	this->currentSpeed = 0;

	Motor_addErr(this,0);//init Motor->err[0]
	Motor_addErr(this,0);//init Motor->err[1]
	Motor_addErr(this,0);//init Motor->err[2]
	
	Motor_setkp(this,400);
	Motor_setki(this,15);
	Motor_setkd(this,3);

	board.addMotorPIDHandler(bind(this, (ThisCall)Motor_pidTick));
}
void Motor_Enable(Motor * this) {
	board.gpio.on(DO_ENABLE);
}
void Motor_Disable(Motor * this) {
	board.gpio.off(DO_ENABLE);
}
void Motor_runAs(Motor * this, int16_t targetSpeed){
	if (targetSpeed > 2000 || targetSpeed < -2000) {
		return;
	}
	this->targetSpeed = targetSpeed;
}

void Motor_setkp(Motor * this, int32_t val){
	this->kp = val;
}
void Motor_setki(Motor * this, int32_t val){
	this->ki = val;
}
void Motor_setkd(Motor * this, int32_t val){
	this->kd = val;
}
void Motor_addErr(Motor * this, int32_t newErr) {
	this->err[0] = this->err[1];//n-2
	this->err[1] = this->err[2];//n-1
	this->err[2] = newErr;//n
}

void Motor_pidTick(Motor * this){
	int32_t dSpeed = Motor_PID(this);
	int32_t speed = this->currentSpeed + dSpeed;

	
	if (speed > 2000) {
		speed = 2000;
	} else if (speed < -2000) {
		speed = - 2000;
	}
	
	if (speed >= 0) {
		board.gpio.on(DO_AIN2);
		board.gpio.on(DO_BIN2);

		speed = speed;

	} else {
		board.gpio.off(DO_AIN2);
		board.gpio.off(DO_BIN2);

		speed = 2000 + speed;
	}

	board.pwm.set(PWM_AIN1 , speed);
	board.pwm.set(PWM_BIN1 , speed);
	this->currentSpeed = speed;
}

int32_t Motor_PID(Motor * this){
	int32_t newErr = 0;
	int32_t deltaSpeed = 0;
	int32_t encoder = 0;
	int32_t speedLimit = this->targetSpeed / 2;
	
	encoder = (this->encoder->speed * 25) / 2;
	newErr = this->targetSpeed - encoder; 

	Motor_addErr(this , newErr);

	deltaSpeed = this->kp*(this->err[2] - this->err[1])
			+ this->ki*(this->err[2])
			+ this->kd*((this->err[2] - this->err[1]) - (this->err[1] - this->err[0]));
	deltaSpeed /= 100;
	
	if(deltaSpeed > speedLimit) {
		deltaSpeed = speedLimit;
	} else if(deltaSpeed < -speedLimit) {
		deltaSpeed = -speedLimit;
	}

	return deltaSpeed;
}
