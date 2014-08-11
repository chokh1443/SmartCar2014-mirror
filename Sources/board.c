#include "board.h"
#include "jdp.h"

void LED_ON(uint16_t number);
void LED_OFF(uint16_t number);
void GPIO_ON(uint16_t ch);
void GPIO_OFF(uint16_t ch);
uint8_t GPIO_GET(uint16_t ch);

void initBoard(Board * board) {
	board->led.on = LED_ON;
	board->led.off = LED_OFF;

	board->gpio.on = GPIO_ON;
	board->gpio.off = GPIO_OFF;
	board->gpio.get = GPIO_GET;
}
void LED_ON(uint16_t number) {
	
}
void LED_OFF(uint16_t number) {
	
}
void GPIO_ON(uint16_t ch) {
	SIU.GPDO[ch].B.PDO = 1;
}
void GPIO_OFF(uint16_t ch) {
	SIU.GPDO[ch].B.PDO = 0;
}
uint8_t GPIO_GET(uint16_t ch) {
	return (uint8_t) SIU.GPDI[ch].B.PDI;
}
