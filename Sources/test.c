#include "test.h"

void enterTest(SmartCar * smartCar, uint8_t);
void segmentTest(SmartCar * smartCar);
void servoTest(SmartCar * smartCar);
void motorTest(SmartCar * smartCar);
void ledTest(SmartCar * smartCar);
void cameraTest(SmartCar * smartCar);

void test(SmartCar * smartCar) {
	uint8_t menu = 0;

	board.led.off(1);
	board.led.off(2);
	board.led.off(3);
	board.led.off(4);

	while (1) {
		Segment_print(&smartCar->segment[1], menu);

		switch (board.button.read()) {
		case 1:
			menu++;
			break;
		case 2:
			menu--;
			break;
		case 3:
			enterTest(smartCar, menu);
			break;
		case 4:
			Segment_print(&smartCar->segment[0], 0);
			return;
		}
	}
}
void enterTest(SmartCar * smartCar, uint8_t menu) {
	switch (menu) {
	case 1:
		// segment & barLED
		segmentTest(smartCar);
		break;
	case 2:
		// servo
		servoTest(smartCar);
		break;
	case 3:
		// motor & encoder
		motorTest(smartCar);
		break;
	case 4:
		// led
		ledTest(smartCar);
		break;
	case 5:
		// camera
		cameraTest(smartCar);
		break;
	}
}

void segmentTest(SmartCar * smartCar) {
	uint8_t number[3][4] = 
		{{0,1,2,3}, 
		 {3,4,5,6}, 
		 {6,7,8,9}};
	uint8_t i,j;
	LEDData LED;
	
	while (1) {
		//segment test
		Segment_print(&smartCar->segment[0], (uint16_t) number[0][0]*1000 + number[0][1]*100 + number[0][2]*10 + number[0][3]);
		Segment_print(&smartCar->segment[1], (uint16_t) number[1][0]*1000 + number[1][1]*100 + number[1][2]*10 + number[1][3]);
		Segment_print(&smartCar->segment[2], (uint16_t) number[2][0]*1000 + number[2][1]*100 + number[2][2]*10 + number[2][3]);
		
		for(i=0;i<3;i++){
			for(j=0;j<4;j++){
				if(number[i][j] > 9){
					number[i][j] = 0;
				} else{
					number[i][j]++;
				}
			}
		}
		
		//BARLED TEST
		//On
		for(i=0;i<8;i++){
			LEDData_add(&LED,i);
		}
		
		BarLED_print(&smartCar->barLED[0], LED);
		
		//Just interval
		for(i=0;i<10000;i++); 
		
		//OFF
		LED.len = 0;
		BarLED_print(&smartCar->barLED[0], LED);
		
		for(i=0;i<10000;i++); // Just interval
		
		//button4 is clicked, and segment test end
		if (board.button.isClick(4)) {
			Segment_print(&smartCar->segment[0], 0);
			Segment_print(&smartCar->segment[1], 0);
			Segment_print(&smartCar->segment[2], 0);
			
			return;
		}
	}
}
void servoTest(SmartCar * smartCar) {
	uint8_t i=30, j;
	
	while(1){
		Servo_runAs(&smartCar->servo, i);
		
		for(j=0;j<10000;j++); 
		
		Servo_runAs(&smartCar->servo, i);
		
		for(j=0;j<10000;j++);
		
		i = i + 10;
		
		//button4 is clicked, and servo test end
		if (board.button.isClick(4)) {
			return;
		}
	}
}
void motorTest(SmartCar * smartCar) {
	uint8_t speed=30;
	
	Motor_Enable(&smartCar->motor);
	
	while(1){
		Motor_runAs(&smartCar->motor, speed);
		
		Segment_print(&smartCar->segment[0], smartCar->motor.targetSpeed);
		Segment_print(&smartCar->segment[1], smartCar->encoder.speed);
		
		switch (board.button.read()) {
		// fast
		case 1:
			speed++;
			break;
		// slow
		case 2:
			speed--;
			break;
		//reverse
		case 3:
			-(speed);
			break;
		//motor test end
		case 4:
			return;
		}
	}
}
void ledTest(SmartCar * smartCar) {
	
}
void cameraTest(SmartCar * smartCar) {
	
}
