
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
void start(SmartCar * smartCar);
void set_Line(uint16_t inputLine[][], uint16_t setLine[][]);
void fix_Line(uint16_t line[][]);
void insert_Line(uint16_t input[][], uint16_t map[][][]);
void check_direction(uint16_t standard[][], uint16_t map[][][]);

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

//camera inputing	time = 0.04~0.06s(about 50ms)
//servo motor moving time = 0.2s(200ms)
//we have about 4 data for moving servo motor
//make map useing 5 camera data

void start(void){
	SmartCar smartCar;
	SmartCar_init(&smartCar);
	uint8_t i, j;					// 0 left, 1 right
	
	uint16_t standardOfLine[2][128];// standard for checking Line.
	uint16_t bufferOfLine[2][128];  // Line buffer
	uint16_t map[2][5][128];	 	// map is queue(size 5).
	
	//set standard Line
	set_Line(Camera_get(smartCar.camera),standardOfLine);
	
	
		
}

//setLine
void set_Line(uint16_t inputLine[][], uint16_t setLine[][]){
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

//check standard Line and fix some value	
void fix_Line(uint16_t line[][]){
	uint8_t check_point=0;
	uint8_t i,j;

	// left camera fixing. throw array 121~127.
	for(i=0;i<12;i++){
		check_point = 0;
		
		for(j=0;j<10;j++){
			if(line[0][(i*10)+j]==1){
				check_point++;
			}
		}
		
		// 0100011000 (1 == Line) 
		if(check_point < 4){ 			// under 30%	
			for(j=0;j<10;j++){
				line[0][(i*10)+j] = 0;
			}
		// 0011111111 
		} else if(check_point < 9){ 	// under 80%
			for(j=0;j<7;j++){
				check_point = 0;
				check_point = line[0][(i*10)+j]+line[0][(i*10)+j+1]
				                    +line[0][(i*10)+j+2]+line[0][(i*10)+j+3]; 
				if(check_point < 2){	// line data push to right
					line[0][(i*10)+j] = 0;
					line[0][(i*10)+j+1] = 0;
					line[0][(i*10)+j+2] = 0;
					line[0][(i*10)+j+3] = 1;
				}
			}					
		} else{							// over 80%
			if(check_point != 10){
				for(j=0;j<10;j++){
					line[0][(i*10)+j] = 1;
				}
			}
		}		
	}
	
	// right camera fixing. throw array 121~127
	for(i=12;i>0;i--){
		check_point = 0;
		
		for(j=0;j<10;j++){
			if(line[1][(i*10)-j] == 1){
				cehck_point++;
			}
		}
		
		if(check_point < 4){
			for(j=0;j<10;j++){
				line[1][(i*10)-j] = 0;
			}
		} else if(check_point < 9){
			for(j=0;j<7;j++){
				check_point = 0;
				check_point = line[1][(i*10)-j] + line[1][(i*10)-j-1]
				                    + line[1][(i*10)-j-2] + line[1][(i*10)-j];
				if(check_point < 2){
					line[1][(i*10)-j] = 0;
					line[1][(i*10)-j-1] = 0;
					line[1][(i*10)-j-2] = 0;
					line[1][(i*10)-j-3] = 1;
				}
			}
		} else {
			if(check_point != 10){
				for(j=0;j<10;j++){
					line[1][(i*10)-j] = 1;
				}
			}
		}
	}
}

