#include "barled.h"
#include "zp_pin.h"
#include "camera.h"

uint8_t BARLED_ONOFF[4] = {
	DO_BAR1_ON, DO_BAR2_ON, DO_BAR3_ON, DO_BAR4_ON
};
uint8_t BARLED_PINS[4][3] = {
	{DO_BAR1_A, DO_BAR1_B, DO_BAR1_C},
	{DO_BAR2_A, DO_BAR2_B, DO_BAR2_C},
	{DO_BAR3_A, DO_BAR3_B, DO_BAR3_C},
	{DO_BAR4_A, DO_BAR4_B, DO_BAR4_C}
};

void BarLED_init(BarLED * this, uint8_t id) {
	//FIX ME
	board.gpio.off(this->ENABLE_BAR[0]);
	board.gpio.off(this->ENABLE_BAR[1]);
	board.gpio.off(this->ENABLE_BAR[2]);
	board.gpio.off(this->ENABLE_BAR[3]);
}

void BarLED_print(BarLED * this, Camera * camera, uint16_t black) {
	uint16_t i,j;

	for(i = 0; i < 2; i++) {
		for(j = 0; j < 16; j++) {
			if ( camera->lineData[i][ j*6 +0 ] > black 
					|| camera->lineData[i][ j*6 +1 ] > black
					|| camera->lineData[i][ j*6 +2 ] > black
					|| camera->lineData[i][ j*6 +3 ] > black
					|| camera->lineData[i][ j*6 +4 ] > black
					|| camera->lineData[i][ j*6 +5 ] > black ) {
				this->ledLine[i][j] = 1;
			}
			else {
				this->ledLine[i][j] = 0;
			}		
		}
	}

}

void BarLED_onTick(BarLED * this) {
	static uint8_t index = 0;
	register uint8_t i;

	for(i = 0; i < 4; i++) {
		if (this->ledLine[ (int)(i/2) ][index] == 0) {
			board.gpio.off(this->ENABLE_BAR[i]);
		} else {
			BarLED_decToBin(this, i, index);
			board.gpio.set(this->NUMBER_BAR[i][0], index & 0x01 ? 1 : 0);
			board.gpio.set(this->NUMBER_BAR[i][1], index & 0x02 ? 1 : 0);
			board.gpio.set(this->NUMBER_BAR[i][2], index & 0x04 ? 1 : 0);
		}	
	}
	index = ++index % 8;
}
