
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"
#include "smartcar.h"

#include "algorithm.h"
#include "test.h"
#include "preset.h"

/**********************  Function Prototype here *************************/

void main(void);




/*********************  Initialization Function(s) ************************/

void main(void) {
	SmartCar smartCar;
	sys_init_fnc();
	EnableExternalInterrupts();
	UartBufInit();
	SmartCar_init(&smartCar);

	while(1){
		switch(board.button.read()){
		case 1:
			test(&smartCar);
			break;
		case 2:
			start(&smartCar);
			break;
		case 3:
			preset(&smartCar);
			break;
		}
	}

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

