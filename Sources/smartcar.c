#include "smartcar.h"
#include "adc_drv.h"

void SmartCar_init(SmartCar * this){
	uint8_t i; 
	
	Encoder_init(&this->encoder);
	for(i = 0; i < 2; i++){
		Camera_init(&this->camera[i], i);
	}
	
	for(i = 0; i < 3; i++){
		Segment_init(&this->segment[i], i);
	}
	
	for(i = 0; i < 2; i++){
		BarLED_init(&this->barLED[i], i);
	}
	
	Motor_init(&this->motor);
	Servo_init(&this->servo);
	
	SmartCar_setCameraPIT(this, 12000);
}

void SmartCar_setCameraPIT(SmartCar * smartCar, uint32_t value) {
	/*PIT.CH[1].LDVAL.R  = 0x00000FA0; 4000 ~ 12000*/
	smartCar->cameraPIT = value;
	PIT.CH[1].LDVAL.R = smartCar->cameraPIT;
}
