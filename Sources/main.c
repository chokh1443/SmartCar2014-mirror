
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "smartcar.h"
#include "gpio_drv.h"
#include "test.h"

/**********************  Function Prototype here *************************/

void main(void);
void preset(SmartCar * smartCar);
void start(SmartCar * smartCar);

void testServo(Servo * servo, Segment * segment, Segment * step);
void set_Line(uint16_t inputLine[2][128], uint16_t setLine[2][128]);
void fix_Line(uint16_t line[2][128]);
void insert_Line(uint16_t input[2][128], uint16_t map[10][2][128]);
void check_direction(uint16_t standard[2][128], uint16_t map[10][2][128]);

unsigned char newLine[2] = {'\r','\n'};


/*********************  Initialization Function(s) ************************/

void main(void) {
	SmartCar smartCar;
	LEDData data;
	sys_init_fnc();
	EnableExternalInterrupts();
	
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

//camera inputing	time = 0.04~0.06s(about 50ms)
//servo motor moving time = 0.2s(200ms)
//we have about 4 data for moving servo motor
//make map useing 5 camera data

void start(SmartCar * smartCar){
	uint8_t i, j;					// 0 left, 1 right
	
	while(1){
		
	}
}

void findLine(Camera * camera){
	uint16_t i;
	uint16_t * data = Camera_get(camera);
	
	uint16_t value = data[0];
	for(i = 1; i < 128; i++){
		if(data[i] - data[i-1] > 400){ //XXX			
		}
	}
}

void preset(SmartCar * smartCar){
	
}

//setLine
void set_Line(uint16_t inputLine[2][128], uint16_t setLine[2][128]){
	uint8_t i, j;
	uint16_t standardOfcolor=0; 		// standard for checking color.
	
	for(i=0;i<2;i++){
		for(j=0;j<128;j++){
			standardOfcolor = standardOfcolor + inputLine[i][j]; 
		}
		
		standardOfcolor = standardOfcolor / 128;
		
		for(j=0;j<128;j++){
			if(inputLine[i][j] >= standardOfcolor){
				setLine[i][j] = 0; // white(out or road)
			} else{
				setLine[i][j] = 1; // black(line)
			}	
		}
	}
	fix_Line(setLine);
}

