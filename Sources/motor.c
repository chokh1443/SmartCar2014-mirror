#include "motor.h"

void Motor_init(Motor * this){
	board->targetSpeed = 0;
	
}
void Motor_Enable(void) {
	board.gpio.on(DO_ENABLE);
}
void Motor_Disable(void) {
	board.gpio.off(DO_ENABLE);
}
void Motor_runAs(Motor * this, int16_t targetSpeed){
	if (targetSpeed > 100 || targetSpeed <-100) {
		return;
	}
	if (targetSpeed >= 0) {
		board.gpio.on(DO_AIN2);
		board.gpio.on(DO_BIN2);
		//FIX ME : HARDWARE!!! DO_AIN2 <-> DO_AIN1 or DO_BIN2 <-> DO_BIN1 
	} else {
		board.gpio.off(DO_AIN2);
		board.gpio.off(DO_BIN2);
		//FIX ME : HARDWARE!!! DO_AIN2 <-> DO_AIN1 or DO_BIN2 <-> DO_BIN1
		targetSpeed = 100 + targetSpeed;
	}
	
	this->targetSpeed = targetSpeed;
}
void Motor_pidTick(Motor * this){
	int32_t kp = 0x00000000;
	int32_t ki = 0x00000000;
	int32_t kd = 0x00000000;
	
	int16_t speed = Encoder_get(this->encoder);
	
	board.pwm.set(PWM_AIN1 , this->targetSpeed);
	board.pwm.set(PWM_BIN1 , this->targetSpeed);
}
