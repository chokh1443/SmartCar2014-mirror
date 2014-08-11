#include "board.h"

void LED_ON(int number);
void LED_OFF(int number);
void GPIO_ON(int number);
void GPIO_OFF(int number);

void initBoard(struct Board * board){
	board->led.on = LED_ON;
	board->led.off = LED_OFF;
	
	board->gpio.on = GPIO_ON;
	board->gpio.off = GPIO_OFF;
}
void LED_ON(int number){
	
}
void LED_OFF(int number){
	
}
void GPIO_ON(int number){
	
}
void GPIO_OFF(int number){
	
}
