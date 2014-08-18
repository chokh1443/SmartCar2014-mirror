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

uint8_t BUTTON_GET(uint16_t ch);
uint8_t BUTTON_IS_CLICK(uint16_t ch);
uint8_t BUTTON_READ();

void ADD_TIMER_INTERRUPT(EventHandler handler);
void ADD_CAMERA_INTERRUPT(EventHandler handler);
void ADD_MOTOR_PID_INTERRUPT(EventHandler handler);
void ADD_ENCODER_TIMER_INTERRUPT(EventHandler handler);
void ADD_ENCODER_TICK_INTERRUPT(EventHandler handler);

Board board = {
	//LED
	{LED_ON, LED_OFF},
	//GPIO
	{GPIO_ON, GPIO_OFF, GPIO_GET, GPIO_SET},
	//PWM
	{PWM_SET},
	//BUTTON
	{BUTTON_GET, BUTTON_IS_CLICK, BUTTON_READ},
	//Interrupt
	ADD_TIMER_INTERRUPT,
	ADD_CAMERA_INTERRUPT,
	ADD_MOTOR_PID_INTERRUPT,
	ADD_ENCODER_TIMER_INTERRUPT,
	ADD_ENCODER_TICK_INTERRUPT
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
void PWM_SET(uint16_t ch, uint16_t value) {
	EMIOS_0.CH[ch].CADR.R = value;
}

uint8_t BUTTON_GET(uint16_t ch){
	return GPIO_GET(DI_S1 + ch - 1) == 0 ? 1 : 0; 
}
uint8_t BUTTON_IS_CLICK(uint16_t ch){
	if (BUTTON_GET(ch)){
		while (BUTTON_GET(ch));
		return 1;
	} else {
		return 0;
	}
}
uint8_t BUTTON_READ(){
	if (BUTTON_GET(1)) {
		while (BUTTON_GET(1));
		return 1;
	} else if (BUTTON_GET(2)) {
		while (BUTTON_GET(2));
		return 2;
	} else if (BUTTON_GET(3)) {
		while (BUTTON_GET(3));
		return 3;
	} else if (BUTTON_GET(4)) {
		while (BUTTON_GET(4));
		return 4;
	}
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

EventEmitter encoderTimer = {{0,},0};
void ADD_ENCODER_TIMER_INTERRUPT(EventHandler handler){
	EventEmitter_addHandler(&encoderTimer, handler);
}
void ON_ENCODER(){
	EventEmitter_emit(&encoderTimer);
}
EventEmitter encoderTick = {{0,},0};
void ADD_ENCODER_TICK_INTERRUPT(EventHandler handler){
	EventEmitter_addHandler(&encoderTick, handler);
}
void ON_ENCODER_TICK(){
	EventEmitter_emit(&encoderTick);
}

EventEmitter motor = {{0,},0};
void ADD_MOTOR_PID_INTERRUPT(EventHandler handler){
	EventEmitter_addHandler(&motor, handler);
}
void ON_MOTOR(){
	EventEmitter_emit(&motor);
}
