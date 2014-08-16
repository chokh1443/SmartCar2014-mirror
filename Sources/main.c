
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "smartcar.h"
#include "gpio_drv.h"
/**********************  Function Prototype here *************************/

void main(void);
void testServo(Servo * servo, Segment * segment, Segment * step);

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
	
	Motor_Enable(&smartCar.motor);
	Motor_runAs(&smartCar.motor, 50);
	
	while(1){
		int16_t speed = Encoder_get(&smartCar.encoder), i;
		Segment_print(&smartCar.segment[0], speed);
		
		BarLED_print(&smartCar.barLED[0], (LEDData){{speed/10},1});
	}
	//testServo(&smartCar.servo, &smartCar.segment[0], &smartCar.segment[2]);
	
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

void testServo(Servo * servo, Segment * segment, Segment * step) {
	int value = 0;
	int value2 = 2000;
	int flag = 1;
	while (1) {
		if (flag) {
			if (!board.gpio.get(DI_S1)) {
				value += 10;
				flag = 0;
			}
			if (!board.gpio.get(DI_S2)) {
				value -= 10;
				flag = 0;
			}
			
			if (!board.gpio.get(DI_S3)) {
				value2 += 100;
				flag = 0;
			}
			if (!board.gpio.get(DI_S4)) {
				value2 -= 100;
				flag = 0;
			}
		}
		if (board.gpio.get(DI_S1) && board.gpio.get(DI_S2) && board.gpio.get(DI_S3) && board.gpio.get(DI_S4)) {
			flag = 1;
		}
		Servo_runAs(servo, value);
		
		
		Segment_print(segment, value+1000);
		Segment_print(step, value2);
	}
}

