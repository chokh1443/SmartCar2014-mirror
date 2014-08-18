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
		if (board.gpio.get(DI_S1) == 0) {
			while (board.gpio.get(DI_S1) == 0);
			menu++;
		} else if (board.gpio.get(DI_S2) == 0) {
			while (board.gpio.get(DI_S2) == 0);
			menu--;
		} else if (board.gpio.get(DI_S3) == 0) {
			while (board.gpio.get(DI_S3) == 0);
			enterTest(smartCar, menu);
		} else if (board.gpio.get(DI_S4) == 0) {
			while (board.gpio.get(DI_S4) == 0);
			Segment_print(&smartCar->segment[0], 0);
			return;
		}
		Segment_print(&smartCar->segment[0], menu);
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
	while (1) {
		Segment_print(&smartCar->segment[0], (uint16_t) 1234);
		Segment_print(&smartCar->segment[1], (uint16_t) 4567);
		Segment_print(&smartCar->segment[2], (uint16_t) 7890);

		if (board.gpio.get(DI_S4) == 0) {
			while (board.gpio.get(DI_S4) == 0);
			return;
		}
	}
}
void servoTest(SmartCar * smartCar) {

}
void motorTest(SmartCar * smartCar) {

}
void ledTest(SmartCar * smartCar) {

}
void cameraTest(SmartCar * smartCar) {

}
