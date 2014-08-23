#include "encoder.h"
#include "board.h"

void Encoder_init(Encoder * this) {
	this->count = 0;
	this->speed = 0;
	this->tickCnt = 0;
	
	board.addEncoderTimerHandler(bind(this, (ThisCall)Encoder_onTimer));
	board.addEncoderTickHandler(bind(this, (ThisCall)Encoder_onTick));
}
void Encoder_onTimer(Encoder * this){
	this->speed = this->count;
	this->count = 0;
}
void Encoder_onTick(Encoder * this){
	if(board.gpio.get(DI_ENC_B)){
		this->count++;
	} else {
		this->count--;
	}
}

int16_t Encoder_get(Encoder * this) {
	return this->speed;
}

