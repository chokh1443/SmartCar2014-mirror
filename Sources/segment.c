#include "segment.h"
#include "zp_pin.h"
#include "intc_pit.h"


void Segment_init(Segment * this, uint8_t id) {
	uint32_t i;

	regTest(bind(this, (void (*)(void *))Segment_onTick));

	for (i = 0; i < 4; i++) {
		this->charArray[i] = 0;
	}
	
}

void Segment_print(Segment * this, uint16_t number) {
	this->charArray[0] = (uint8_t) (number % 10);
	this->charArray[1] = (uint8_t) (number/10 % 100);
	this->charArray[2] = (uint8_t) (number/100 % 1000);
	this->charArray[3] = (uint8_t) (number/1000 % 10000);
}
void Segment_onTick(Segment * this) {
	uint8_t value = this->charArray[0];

	
	//char ENABLE_PIN [4] ={DO_SEG1_1,DO_SEG1_2,DO_SEG1_3,DO_SEG1_4};

	board.gpio.off(DO_SEG1_1);
	board.gpio.on(DO_SEG1_2);
	board.gpio.on(DO_SEG1_3);
	board.gpio.on(DO_SEG1_4);

	board.gpio.set(DO_SEG1_A, value & 0x01 ? 1 : 0);
	board.gpio.set(DO_SEG1_B, value & 0x02 ? 1 : 0);
	board.gpio.set(DO_SEG1_C, value & 0x04 ? 1 : 0);
	board.gpio.set(DO_SEG1_D, value & 0x08 ? 1 : 0);
}
