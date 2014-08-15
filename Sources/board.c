#include "board.h"
#include "jdp.h"
#include "zp_pin.h"
#include "intc_pit.h"

void LED_ON(uint16_t ledId);
void LED_OFF(uint16_t ledId);
void GPIO_ON(uint16_t ch);
void GPIO_OFF(uint16_t ch);
uint8_t GPIO_GET(uint16_t ch);
void GPIO_SET(uint16_t ch, uint8_t value);
void PWM_SET(uint16_t ch, uint16_t value);

void ADD_TIMER_INTERRUPT(EventHandler handler);
void ADD_CAMERA_INTERRUPT(EventHandler handler);

Board board = {
	//LED
	{LED_ON, LED_OFF},
	//GPIO
	{GPIO_ON, GPIO_OFF, GPIO_GET, GPIO_SET},
	//PWM
	{PWM_SET},
	//Interrupt
	ADD_TIMER_INTERRUPT,
	ADD_CAMERA_INTERRUPT
};

void LED_ON(uint16_t ledId) {
	GPIO_OFF(DO_LED1 + ledId-1);
}
void LED_OFF(uint16_t ledId) {
	GPIO_ON(DO_LED1 + ledId -1);
}
void GPIO_ON(uint16_t ch) {
	SIU.GPDO[ch].B.PDO = 1;
}
void GPIO_OFF(uint16_t ch) {
	SIU.GPDO[ch].B.PDO = 0;
}
uint8_t GPIO_GET(uint16_t ch) {
	return (uint8_t) SIU .GPDI[ch].B.PDI;
}
void GPIO_SET(uint16_t ch, uint8_t value){
	SIU.GPDO[ch].B.PDO = value;
}

EventEmitter timer = {{0,},0};

void ADD_TIMER_INTERRUPT(EventHandler handler){
	EventEmitter_addHandler(&timer, handler);
}
void ON_DISPLAY(){
	EventEmitter_emit(&timer);
}

EventEmitter camera = {{0,},0};
void ADD_CAMERA_INTERRUPT(EventHandler handler){
	EventEmitter_addHandler(&camera, handler);
}
void ON_CAMERA(){
	EventEmitter_emit(&camera);
}
void PWM_SET(uint16_t ch, uint16_t value) {
	EMIOS_0.CH[ch].CADR.R = value;
}
