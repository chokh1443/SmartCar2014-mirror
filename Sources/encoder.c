#include "encoder.h"

void Encoder_init(Encoder * encoder) {
	encoder->count = 0;
	encoder->speed = 0;
}
void Encoder_onTimer(Encoder * this){
	this->speed = this->count;
	this->count = 0;
}
void Encoder_onTick(Encoder * this){
	this->count++;
}
 
int16_t Encoder_get(Encoder * this) {
	return this->speed;
}
