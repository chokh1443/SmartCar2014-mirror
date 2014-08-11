
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "board.h"

/**********************  Function Prototype here *************************/

void main(void);

unsigned char newLine[2] = { '\r', '\n' };
/*********************  Initialization Function(s) ************************/

void main(void) {
	Board board;
	sys_init_fnc();
	EnableExternalInterrupts();
	
	initBoard(&board);
	/*
	 * usages :
	 * board.gpio.on(68);
	 * board.led.off(1);
	 */
	
}

