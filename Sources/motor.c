#include "motor.h"

int32_t Motor_PID(Motor * this);

void Motor_init(Motor * this, Encoder * encoder){
	this->encoder = encoder;
	this->targetSpeed = 0;
	this->currentSpeed = 0;

	Motor_setkp(this,400);
	Motor_setki(this,1);
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
	if (targetSpeed > 100 || targetSpeed <-100) {
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

	if (speed >= 0) {
		board.gpio.on(DO_AIN2);
		board.gpio.on(DO_BIN2);

		speed = this->targetSpeed;
	} else {
		board.gpio.off(DO_AIN2);
		board.gpio.off(DO_BIN2);

		speed = -this->targetSpeed;
	}

	board.pwm.set(PWM_AIN1 , speed);
	board.pwm.set(PWM_BIN1 , speed);

	this->currentSpeed = speed;
}

int32_t Motor_PID(Motor * this){
	int32_t newErr = 0;
	int32_t deltaSpeed = 0;

	newErr = this->targetSpeed - this->encoder->speed;

	Motor_addErr(this , newErr);

	deltaSpeed = this->kp*(this->err[2] - this->err[1])
			+ this->ki*(this->err[2])
			+ this->kd*(this->err[2] - 2 * this->err[1] + this->err[0]);
	deltaSpeed /= 100;

	return deltaSpeed;
}
