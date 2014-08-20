#include "segment.h"
#include "zp_pin.h"


uint8_t ENABLE_PINS[3][4] = {
	{DO_SEG1_1,DO_SEG1_2,DO_SEG1_3,DO_SEG1_4},
	{DO_SEG2_1,DO_SEG2_2,DO_SEG2_3,DO_SEG2_4},
	{DO_SEG3_1,DO_SEG3_2,DO_SEG3_3,DO_SEG3_4}
};
uint8_t NUMBER_PINS[3][4] = {
	{DO_SEG1_A, DO_SEG1_B, DO_SEG1_C, DO_SEG1_D},
	{DO_SEG2_A, DO_SEG2_B, DO_SEG2_C, DO_SEG2_D},
	{DO_SEG3_A, DO_SEG3_B, DO_SEG3_C, DO_SEG3_D}
};

void Segment_init(Segment * this, uint8_t id) {
	uint32_t i;

	board.addTimerHandler(bind(this, (ThisCall)Segment_onTick));

	for (i = 0; i < 4; i++) {
		this->charArray[i] = 0;
	}
	
	this->id = id;
	
	this->index = 0;
	this->holdCount = 60;
}

void Segment_print(Segment * this, uint16_t number) {
	if(this->holdCount > 60){
		this->charArray[3] = (uint8_t) (number % 10);
		this->charArray[2] = (uint8_t) (number/10 % 10);
		this->charArray[1] = (uint8_t) (number/100 % 10);
		this->charArray[0] = (uint8_t) (number/1000 % 10);
		this->holdCount = 0;
	}
}

void Segment_onTick(Segment * this) {
	register uint8_t i;
	
	for(i = 0; i < 4; i++){
		if(i == this->index){
			board.gpio.off(ENABLE_PINS[this->id][i]);
		} else {
			board.gpio.on(ENABLE_PINS[this->id][i]);
		}
	}

	board.gpio.set(NUMBER_PINS[this->id][0], this->charArray[this->index] & 0x01 ? 1 : 0);
	board.gpio.set(NUMBER_PINS[this->id][1], this->charArray[this->index] & 0x02 ? 1 : 0);
	board.gpio.set(NUMBER_PINS[this->id][2], this->charArray[this->index] & 0x04 ? 1 : 0);
	board.gpio.set(NUMBER_PINS[this->id][3], this->charArray[this->index] & 0x08 ? 1 : 0);
		
	this->index = ++this->index % 4;
	this->holdCount++;
}
