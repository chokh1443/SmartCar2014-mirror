#include "test.h"
#include "utils.h"
#include "algorithm.h"


void enterTest(SmartCar * smartCar, uint8_t);
void segmentTest(SmartCar * smartCar);
void servoTest(SmartCar * smartCar);
void motorTest(SmartCar * smartCar);
void cameraTest(SmartCar * smartCar);

LEDData getLine(Camera * camera);

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
			if (menu > 4 || menu < 1) {
				menu = 1;
				continue;
			}
			enterTest(smartCar, menu);
			Segment_print(&smartCar->segment[0], 0);
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
		// camera
		cameraTest(smartCar);
		break;
	}
}

void segmentTest(SmartCar * smartCar) {
	int16_t segmentInput[3] = { (uint16_t) 1234, (uint16_t) 4567,
			(uint16_t) 7890 };
	uint8_t tempOfcalc[4] = { 0, 0, 0, 0 };
	uint8_t i, j;

	while (1) {
		for (i = 0; i < 2; i++) {
			BarLED_print(&smartCar->barLED[i], smartCar->barLED[i].data);
		}
		for (i = 0; i < 3; i++) {
			Segment_print(&smartCar->segment[i], segmentInput[i]);
		}

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
				smartCar->barLED[i].data.len = 0;
			}
			break;

			//add each segment value
		case 3:
			for (i = 0; i < 4; i++) {
				tempOfcalc[i] = 0;
			}

			for (i = 0; i < 3; i++) {
				tempOfcalc[0] = (uint8_t) ((segmentInput[i] / 1000) % 10);
				tempOfcalc[1] = (uint8_t) ((segmentInput[i] / 100) % 10);
				tempOfcalc[2] = (uint8_t) ((segmentInput[i] / 10) % 10);
				tempOfcalc[3] = (uint8_t) (segmentInput[i] % 10);

				for (j = 0; j < 4; j++) {
					if (tempOfcalc[j] > 9) {
						tempOfcalc[j] = 0;
					} else {
						tempOfcalc[j]++;
					}

				}

				segmentInput[i] = (uint16_t) tempOfcalc[0] * 1000;
				segmentInput[i] = segmentInput[i]
						+ (uint16_t) tempOfcalc[1] * 100;
				segmentInput[i] = segmentInput[i]
						+ (uint16_t) tempOfcalc[2] * 10;
				segmentInput[i] = segmentInput[i] + (uint16_t) tempOfcalc[3];
			}
			break;

			//segment Test end
		case 4:
			for (i = 0; i < 3; i++) {
				segmentInput[i] = 0;
				Segment_print(&smartCar->segment[i], segmentInput[i]);
			}

			for (i = 0; i < 2; i++) {
				smartCar->barLED[i].data.len = 0;
			}
			return;
		}
	}
}
void servoTest(SmartCar * smartCar) {
	smartCar->servo.steer = 0;
	while (1) {
		Servo_runAs(&smartCar->servo, smartCar->servo.steer);

		Segment_print(&smartCar->segment[1], smartCar->servo.steer);

		switch (board.button.read()) {
		case 1:
			if (smartCar->servo.steer < 100) {
				smartCar->servo.steer = smartCar->servo.steer + 10;
			} else {
				smartCar->servo.steer = 100;
			}
			break;
		case 2:
			if (smartCar->servo.steer > -100) {
				smartCar->servo.steer = smartCar->servo.steer - 10;
			} else {
				smartCar->servo.steer = -100;
			}
			break;
		case 3:
			smartCar->servo.steer = -smartCar->servo.steer;
			break;
		case 4:
			smartCar->servo.steer = 0;
			Servo_runAs(&smartCar->servo, smartCar->servo.steer);
			Segment_print(&smartCar->segment[1], smartCar->servo.steer);
			return;
		}
	}
}
void motorTest(SmartCar * smartCar) {
	int16_t speed = 30;

	Motor_Enable(&smartCar->motor);

	while (1) {
		Motor_runAs(&smartCar->motor, speed);

		Segment_print(&smartCar->segment[0], smartCar->motor.targetSpeed);

		Segment_print(&smartCar->segment[1], Encoder_get(&smartCar->encoder));

		switch (board.button.check()) {
		case 1: // fast
			if (speed < 100) {
				speed = speed + 10;
			} else {
				speed = 100;
			}
			break;

		case 2: // slow
			if (speed > -100) {
				speed = speed - 10;
			} else {
				speed = -100;
			}
			break;

		case 3: // reverse
			speed = -speed;
			break;

		case 4: //motor test end
			speed = 0;
			Motor_Disable(&smartCar->motor);
			Segment_print(&smartCar->segment[0], speed);
			Segment_print(&smartCar->segment[1], speed);
			return;
		}
	}
}

void cameraTest(SmartCar * smartCar) {
	/*	       ��������					��������
	 *   	\         /        \           /
	 * 		left camera         right camera
	 *
	 * 				 Bar LED show(1 is on)
	 * 	  0000011110000000    00000011110000000
	 *
	 * 	  	1 BarLED is same 8 camera sensor
	 */
	uint8_t i, j;

	while (1) {
		BarLED_print(&smartCar->barLED[i], smartCar->barLED[i].data);
		
		switch (board.button.read()) {
		case 1:
			for (i = 0; i < 2; i++) {
				for (j = 0; j < 16; j++) {
					LEDData_add(&smartCar->barLED[i].data, j);
				}
			}
			break;
		case 2:
			for (i = 0; i < 2; i++) {
				smartCar->barLED[i].data.len = (uint8_t) 0;
			}
			break;
		case 3:

			break;
		case 4:
			BarLED_print(&smartCar->barLED[i], smartCar->barLED[i].data);
					
			Segment_print(&smartCar->segment[0], 0);
			Segment_print(&smartCar->segment[1], 0);
			return;
		}
	}
	/*	while (1) {
	 for (i = 0; i < 2; i++) {
	 BarLED_print(&smartCar->barLED[i], smartCar->barLED[i].data);
	 }

	 for (i = 0; i < 2; i++) {
	 smartCar->barLED[i].data = getLine(&smartCar->camera[i]);
	 }

	 // end camera test
	 if (board.button.isClick(4)) {
	 for (i = 0; i < 2; i++) {
	 for (j = 0; j < 16; j++) {
	 smartCar->barLED[i].data.data[j] = (uint8_t) 0;
	 }
	 smartCar->barLED[i].data.len = (uint8_t) 0;

	 BarLED_print(&smartCar->barLED[i], smartCar->barLED[i].data);
	 }
	 Segment_print(&smartCar->segment[0], 0);
	 Segment_print(&smartCar->segment[1], 0
	 );
	 
	 return;
	 }
	 }
	 */}

// input getLine Algorithm to camera
LEDData getLine(Camera * camera) {
	LEDData led;
	uint16_t * data = Camera_get(camera);
	//DifferentialData differentialData;
	uint8_t result[128];
	uint8_t i, j, temp = 0;

	//getDifferentialData(data, &differentialData);
	//binarization(&differentialData, result);

	for (i = 0; i < 16; i++) {
		led.data[i] = 0;
	}
	led.len = 0;

	for (i = 0; i < 16; i++) {
		temp = 0;

		for (j = 0; j < 8; j++) {
			if (result[i * 16 + j] == 1) {
				temp++;
			}
		}

		if (temp > 3) {
			LEDData_add(&led, i);
		}
	}

	return led;
}

