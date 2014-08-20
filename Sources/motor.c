#include "motor.h"

void Motor_init(Motor * this){
	this->targetSpeed = 0;
	
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
void Motor_pidTick(Motor * this){
	int32_t kp = 0x00000000;
	int32_t ki = 0x00000000;
	int32_t kd = 0x00000000;

	//int16_t speed = Encoder_get(this->encoder);

	if (this->targetSpeed >= 0) {
		board.gpio.on(DO_AIN2);
		board.gpio.on(DO_BIN2);
		//FIX ME : HARDWARE!!! DO_AIN2 <-> DO_AIN1 or DO_BIN2 <-> DO_BIN1 
	} else {
		board.gpio.off(DO_AIN2);
		board.gpio.off(DO_BIN2);
		//FIX ME : HARDWARE!!! DO_AIN2 <-> DO_AIN1 or DO_BIN2 <-> DO_BIN1

		this->targetSpeed = 100 + this->targetSpeed;
	}
	
	board.pwm.set(PWM_AIN1 , this->targetSpeed * 20);
	board.pwm.set(PWM_BIN1 , this->targetSpeed * 20);
}
