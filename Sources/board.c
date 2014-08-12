#include "board.h"
#include "jdp.h"
#include "zp_pin.h"

void LED_ON(uint16_t ledId);
void LED_OFF(uint16_t ledId);
void GPIO_ON(uint16_t ch);
void GPIO_OFF(uint16_t ch);
uint8_t GPIO_GET(uint16_t ch);

const uint8_t CONST_SEGMENT_PIN_NUMBER[3][4] = {
	{ DO_SEG1_A, DO_SEG1_B, DO_SEG1_C, DO_SEG1_D },
	{ DO_SEG2_A, DO_SEG2_B, DO_SEG2_C, DO_SEG2_D },
	{ DO_SEG3_A, DO_SEG3_B, DO_SEG3_C, DO_SEG3_D }
};
const uint8_t CONST_SEGMENT_PIN_ENABLE[3][4] = {
	{ DO_SEG1_1, DO_SEG1_2, DO_SEG1_3, DO_SEG1_4 },
	{ DO_SEG2_1, DO_SEG2_2, DO_SEG2_3, DO_SEG2_4 },
	{ DO_SEG3_1, DO_SEG3_2, DO_SEG3_3, DO_SEG3_4 }
};

void initBoard(Board * board) {
	//default I/O functions
	board->led.on = LED_ON;
	board->led.off = LED_OFF;

	board->gpio.on = GPIO_ON;
	board->gpio.off = GPIO_OFF;
	board->gpio.get = GPIO_GET;
	
	board->gpio.ch.segmentNumber = (uint8_t**)CONST_SEGMENT_PIN_NUMBER;
	board->gpio.ch.segmentEnable = (uint8_t**)CONST_SEGMENT_PIN_ENABLE;
}
void LED_ON(uint16_t ledId) {
	GPIO_ON(DO_LED1 + ledId);
}
void LED_OFF(uint16_t ledId) {
	GPIO_OFF(DO_LED1 + ledId);
}
void GPIO_ON(uint16_t ch) {
	SIU.GPDO[ch].B.PDO = 0;
}
void GPIO_OFF(uint16_t ch) {
	SIU.GPDO[ch].B.PDO = 1;
}
uint8_t GPIO_GET(uint16_t ch) {
	return (uint8_t) SIU .GPDI[ch].B.PDI;
}
