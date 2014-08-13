
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "smartcar.h"

/**********************  Function Prototype here *************************/

void main(void);

unsigned char newLine[2] = { '\r', '\n' };
/*********************  Initialization Function(s) ************************/

void main(void) {
	SmartCar smartCar;
	sys_init_fnc();
	EnableExternalInterrupts();
	
	initSmartCar(&smartCar);
	
	smartCar.board.led.on(0);
	smartCar.board.led.off(1);
	smartCar.board.led.on(2);
	smartCar.board.led.off(3);
	
	smartCar.board.gpio.on(DO_SEG1_1);
	smartCar.board.gpio.off(DO_SEG1_2);
	smartCar.board.gpio.on(DO_SEG1_3);
	smartCar.board.gpio.off(DO_SEG1_4);
	
	smartCar.board.gpio.on(DO_SEG1_A);
	smartCar.board.gpio.off(DO_SEG1_B);
	smartCar.board.gpio.off(DO_SEG1_C);
	smartCar.board.gpio.off(DO_SEG1_D);
	
	/*
	 * usages :
	 * board.gpio.on(68);
	 * board.led.off(1);
	 * 
	 * pEncoder = board.encoder;
	 * encoder.get(pEncoder);
	 * encoder.onTick(pEncoder);
	 */
}

