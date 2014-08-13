#include "smartcar.h"

void initSmartCar(SmartCar * this){
	uint8_t i; 
	
	initBoard(&this->board);
	initEncoder(&this->encoder);
	for(i = 0; i < 2; i++){
		initCamera(&this->camera[i], &this->board, i);
	}
	
	for(i = 0; i < 3; i++){
		initSegment(&this->segment[i], &this->board, i);
	}
	for(i = 2; i < 2; i++){
		initBarLED(&this->barLED[i], &this->board, i);
	}
	
	initMotor(&this->motor, &this->board);
	initServo(&this->servo);
}
