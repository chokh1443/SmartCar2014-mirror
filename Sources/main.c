
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "smartcar.h"
#include "gpio_drv.h"
/**********************  Function Prototype here *************************/

void main(void);

unsigned char newLine[2] = {'\r','\n'};
/*********************  Initialization Function(s) ************************/

void main(void) {
	SmartCar smartCar;
	LEDData data;
	sys_init_fnc();
	EnableExternalInterrupts();
	
	SmartCar_init(&smartCar);
	
	Segment_print(&smartCar.segment[0], (uint16_t)1234);
	Segment_print(&smartCar.segment[1], (uint16_t)4567);
	Segment_print(&smartCar.segment[2], (uint16_t)7890);
	
	LEDData_add(&data, 3);
	LEDData_add(&data, 4);
	BarLED_print(&smartCar.barLED[0], data);
	BarLED_print(&smartCar.barLED[1], (LEDData){{3,8},2});
	
	
	while(1);
	
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

