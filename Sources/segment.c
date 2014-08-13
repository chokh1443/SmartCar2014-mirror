#include "segment.h"
#include "zp_pin.h"
#include "intc_pit.h"

void SEGMENT_PRINT(Segment * this, uint16_t number);
void SEGMENT_ON_TICK(Segment * this);

initSegment(Segment * segment, Board * board, uint8_t id) {
	uint32_t i;
	segment->print = (void (*)(void*, uint16_t)) SEGMENT_PRINT;
	segment->onTick = (void (*)(void*)) SEGMENT_ON_TICK;

	for (i = 0; i < 4; i++) {
		segment->charArray[i] = 0;
	}
	segment->gpio = &(board->gpio);

	segment->ENABLE_PINS = board->gpio.ch.segmentEnable[id];
	segment->NUMBER_PINS = board->gpio.ch.segmentNumber[id];
	
}

void SEGMENT_PRINT(Segment * this, uint16_t number) {
	this->charArray[0] = (uint8_t) number % 10;
	this->charArray[1] = (uint8_t) number % 100 / 10;
	this->charArray[2] = (uint8_t) number % 1000 / 100;
	this->charArray[3] = (uint8_t) number % 10000 / 1000;
}
void SEGMENT_ON_TICK(Segment * this) {
	static uint32_t count = 0;
	uint32_t i, j;
	for (i = 0; i < 4; i++) {
		count == i ?
				this->gpio->on(this->ENABLE_PINS[i]) :
				this->gpio->off(this->ENABLE_PINS[i]);
		for(j = 0; j < 4; j++){
			if(this->charArray[i] & (0x01 << j)){
				this->gpio->on(this->NUMBER_PINS[j]);
			} else {
				this->gpio->off(this->NUMBER_PINS[j]);
			}
		}
	}
	count = ++count % 4;
}
