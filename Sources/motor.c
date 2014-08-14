#include "motor.h"

void MOTOR_RUN_AS(Motor * this, int16_t targetSpeed);
void MOTOR_PID_TICK(Motor * this);

void Motor_init(Motor * this){
	//this->encoder = &board->;
	
	/*EventHandler handler = bind(this, this->pidTick);
	board->timerInterrupt.addHandler(&board->timerInterrupt, handler);
	
	board->timerInterrupt.setInterval(&board->timerInterrupt, 8000);*/
}
void Motor_Enable(void) {
	GPIO_ON(DO_ENABLE);
}
void Motor_Disable(void) {
	GPIO_OFF(DO_ENABLE);
}
void Motor_runAs(Motor * this, int16_t targetSpeed){
	if (targetSpeed > 100 || targetSpeed <-100) {
		
		return;
	}
	if (targetSpeed >= 0) {
		GPIO_ON(DO_AIN2);
		GPIO_ON(DO_BIN2);
	} else {
		GPIO_OFF(DO_AIN2);
		GPIO_OFF(DO_BIN2);
		targetSpeed = 100 + targetSpeed;
	}
	
	this->targetSpeed = targetSpeed;
}
void Motor_pidTick(Motor * this){
	int32_t kp = 0x00000000;
	int32_t ki = 0x00000000;
	int32_t kd = 0x00000000;
	
	int16_t speed = Encoder_get(this->encoder);
}
