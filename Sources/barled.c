#include "barled.h"
#include "board.h"
#include "zp_pin.h"

uint16_t BARLED_ONOFF[4] = {
	DO_BAR1_ON, DO_BAR2_ON, DO_BAR3_ON, DO_BAR4_ON
};

struct {
	uint16_t A;
	uint16_t B;
	uint16_t C;
} BARLED_PINS[4] = {
	{DO_BAR1_A, DO_BAR1_B, DO_BAR1_C},
	{DO_BAR2_A, DO_BAR2_B, DO_BAR2_C},
	{DO_BAR3_A, DO_BAR3_B, DO_BAR3_C},
	{DO_BAR4_A, DO_BAR4_B, DO_BAR4_C}
};

void BarLED_init(BarLED * this, uint8_t id) {
	this->id = id;
	this->index = 0;
	this->data = (LEDData){{0,},0};
	board.addTimerHandler(bind(this, (ThisCall)BarLED_onTick));
}

void BarLED_print(BarLED * this, LEDData data) {
	this->data = data;
	if(data.len == 0){
		board.gpio.off(BARLED_ONOFF[this->id*2 + 0]);
		board.gpio.off(BARLED_ONOFF[this->id*2 + 1]);
	} else {
		board.gpio.on(BARLED_ONOFF[this->id*2 + 0]);
		board.gpio.on(BARLED_ONOFF[this->id*2 + 1]);
	}
}

void BarLED_onTick(BarLED * this) {
	if(this->data.len == 0) return;
	
	if(this->index >= this->data.len){
		this->index = 0;
	} 
	
	if(this->data.data[this->index] < 8){
		//first LED
		uint8_t value  = this->data.data[this->index];
		board.gpio.on(BARLED_ONOFF[this->id*2 + 0]);
		board.gpio.off(BARLED_ONOFF[this->id*2 + 1]);
		board.gpio.set(BARLED_PINS[this->id * 2 + 0].A, value & 0x01 ? 1 : 0);
		board.gpio.set(BARLED_PINS[this->id * 2 + 0].B, value & 0x02 ? 1 : 0);
		board.gpio.set(BARLED_PINS[this->id * 2 + 0].C, value & 0x04 ? 1 : 0);
		
	} else { 
		//Second Led
		uint8_t value  = this->data.data[this->index] - 8;
		board.gpio.off(BARLED_ONOFF[this->id*2 + 0]);
		board.gpio.on(BARLED_ONOFF[this->id*2 + 1]);
		board.gpio.set(BARLED_PINS[this->id * 2 + 1].A, value & 0x01 ? 1 : 0);
		board.gpio.set(BARLED_PINS[this->id * 2 + 1].B, value & 0x02 ? 1 : 0);
		board.gpio.set(BARLED_PINS[this->id * 2 + 1].C, value & 0x04 ? 1 : 0);
	}
	this->index++;
}

void LEDData_add(LEDData * this, uint8_t pos){
	this->data[this->len++] = pos;
}
