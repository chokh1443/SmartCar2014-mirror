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
	uint8_t i, j;
	uint16_t segmentInput[3] = { { 0123 }, { 3456 }, { 6789 } };
	uint8_t tempOfcalc[4] = { 0, 0, 0, 0 };

	while (1) {
		//segment test

		//BARLED TEST
		//button4 is clicked, and segment test end
		switch (board.button.read()) {
		//BarLED ON
		case 1:
			for (i = 0; i < 16; i++) {
				LEDData_add(&smartCar->barLED[0].data, i);
				LEDData_add(&smartCar->barLED[1].data, i);
			}
			break;

			//BarLED OFF
		case 2:
			for (i = 0; i < 2; i++) {
				smartCar->barLED[2].data.len = 0;
			}
			break;

			//add each segment value
		case 3:
			for (i = 0; i < 3; i++) {
				tempOfcalc[0] = (uint8_t) (segmentInput[i] / 1000);
				tempOfcalc[1] = (uint8_t) ((segmentInput[i] % 1000) / 100);
				tempOfcalc[2] = (uint8_t) ((segmentInput[i] % 100) / 10);
				tempOfcalc[3] = (uint8_t) (segmentInput[i] % 10);

				for (j = 0; j < 4; j++) {
					if (tempOfcalc[j] > 9) {
						tempOfcalc[j] = 0;
					} else {
						tempOfcalc[j]++;
					}

				}

				for (j = 0; j < 4; j++) {
					segmentInput[i] = tempOfcalc[j];
				}
			}
			break;

			//segment Test end
		case 4:
			return;
		}

		BarLED_print(&smartCar->barLED[0], smartCar->barLED[0].data);
		BarLED_print(&smartCar->barLED[1], smartCar->barLED[1].data);

		for (i = 0; i < 3; i++) {
			Segment_print(&smartCar->segment[i], segmentInput[i]);
		}
	}
}
void servoTest(SmartCar * smartCar) {
	uint8_t degree = 0;

	while (1) {
		Servo_runAs(&smartCar->servo, degree);

		//button4 is clicked, and servo test end
		switch (board.button.read()) {
		// degree up
		case 1:
			degree = degree+10;
			break;
		// degree down
		case 2:
			degree = degree-10;
			break;
		// reverse degree
		case 3:
			degree = -(degree);
			break;
		// end servo test
		case 4:
			return;
		}
	}
}
void motorTest(SmartCar * smartCar) {
	uint8_t speed = 30;

	Motor_Enable(&smartCar->motor);

	while (1) {
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
			//reverse motor speed
		case 3:
			speed = -speed;
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
	uint16_t *(line[2]);
	uint8_t i, j, k;
	uint8_t check_point[2], check_line;
	while (1) {
		//get camera data
		line[0] = Camera_get(&smartCar->camera[0]);
		line[1] = Camera_get(&smartCar->camera[1]);

		// set check_point(for checking line)
		for (i = 0; i < 2; i++) {
			check_point[i] = 0;
			for (j = 0; j < 128; j++) {
				check_point[i] = check_point[i] + line[i][j];
			}
		}

		for (i = 0; i < 2; i++) {
			check_point[i] = check_point[i] / 128;
		}

		// check line by check_point
		for (k = 0; k < 2; k++) {
			for (i = 0; i < 16; i++) {
				check_line = 0;

				for (j = 0; j < 8; j++) {
					if (line[k][i * 16 + j] > check_point[k]) {
						check_line++;
					}
				}

				if (check_line > 4) { // over 50%, check line
					LEDData_add(&smartCar->barLED[k].data, i);
				}

			}
		}

		/*	       ¡á¡á¡á¡á					¡á¡á¡á¡á   
		 *   	\         /        \           /
		 * 		left camera         right camera
		 * 		
		 * 				 Bar LED show(1 is on)	
		 * 	  0000011110000000    00000011110000000
		 * 	  
		 * 	  	1 BarLED is same 8 camera sensor
		 */
		for (i = 0; i < 2; i++) {
			BarLED_print(&smartCar->barLED[i],smartCar->barLED[i].data);
		}

		// end camera test
		if (board.button.isClick(4)) {
			return;
		}
	}
}
