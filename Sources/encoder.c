#include "encoder.h"

void ENCODER_ON_TIMER(Encoder * this);
void ENCODER_ON_TICK(Encoder * this);
uint16_t ENCODER_GET(Encoder * this);

void initEncoder(Encoder * encoder) {
	typedef uint16_t (*thisCall2)(void*);

	encoder->onTimer = (void (*)(void*)) ENCODER_ON_TIMER;
	encoder->onTick = (void (*)(void*)) ENCODER_ON_TICK;
	encoder->get = (uint16_t (*)(void*)) ENCODER_GET;
	
	encoder->count = 0;
	encoder->speed = 0;
}
void ENCODER_ON_TIMER(Encoder * this) {
	this->speed = this->count;
	this->count = 0;
}
void ENCODER_ON_TICK(Encoder * this) {
	this->count++;
}
uint16_t ENCODER_GET(Encoder * this) {
	return this->speed;
}
