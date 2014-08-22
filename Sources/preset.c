#include "preset.h"

void enterPreset(SmartCar * smartCar, int menu);
void presetCamera(SmartCar * smartCar);
void presetChangePIT(SmartCar * smartCar);
void presetMotor(SmartCar * smartCar);
void presetKp(SmartCar * smartCar);
void presetKi(SmartCar * smartCar);
void presetKd(SmartCar * smartCar);
void presetCheckPID(SmartCar * smartCar);


void preset(SmartCar * smartCar){
	int menu = 0;
	while(1){
		Segment_print(&smartCar->segment[0], (uint16_t)menu);
		Segment_print(&smartCar->segment[1], (uint16_t)3333);
		Segment_print(&smartCar->segment[2], (uint16_t)3333);

		switch(board.button.read()){
		case 1:
			menu++;
			break;
		case 2:
			menu--;
			break;
		case 3:
			enterPreset(smartCar, menu);
			break;
		case 4:
			return;
		}
		if(menu < 1){
			menu = 7;
		} else if(menu > 7){
			menu = 1;
		}
	}
}


void enterPreset(SmartCar * smartCar, int menu) {
	switch(menu){
	case 1:
		presetCamera(smartCar);
		break;
	case 2:
		presetChangePIT(smartCar);
		break;
	case 3:
		presetMotor(smartCar);
		break;
	case 4:
		presetKp(smartCar);
		break;
	case 5:
		presetKi(smartCar);
		break;
	case 6:
		presetKd(smartCar);
		break;
	case 7:
		presetCheckPID(smartCar);
		break;
	}
}

void presetCamera(SmartCar * smartCar) {
	while(1){
		switch(board.button.read()){
		case 4:
			return;
		}
		
		Segment_print(&smartCar->segment[0], (uint16_t)1);
		Segment_print(&smartCar->segment[1], (uint16_t)0);
		Segment_print(&smartCar->segment[2], (uint16_t)0);
		//FIX ME : BARLED PRINT
		//BarLED_print();
	}
}
void presetChangePIT(SmartCar * smartCar) {
	int minVal[2] = {9999};
	int maxVal[2] = {0};
	uint32_t pitVal = 0;
	
	pitVal = smartCar->cameraPIT;
	while(1){
		minVal[0] = Camera_minValue(&smartCar->camera[0]);
		minVal[1] = Camera_minValue(&smartCar->camera[1]);
		maxVal[0] = Camera_maxValue(&smartCar->camera[0]);
		maxVal[1] = Camera_maxValue(&smartCar->camera[1]);
		
		BarLED_print(&smartCar->barLED[0], (LEDData){{pitVal/1000},1});
		
		Segment_print(&smartCar->segment[1], (uint16_t)(minVal[0] < minVal[1]) ? minVal[0] : minVal[1]);
		Segment_print(&smartCar->segment[2], (uint16_t)(maxVal[0] < maxVal[1]) ? maxVal[1] : maxVal[0]);
		
		switch(board.button.read()){
		case 1:
			pitVal += 1000;
			break;
		case 2:
			pitVal -= 1000;
			break;
		case 4:
			return;
		}
		
		if(pitVal < 4000){
			pitVal = 4000;
		} else if(pitVal > 12000){
			pitVal = 12000;
		}
		
		SmartCar_setCameraPIT(smartCar, pitVal);
	}
}
void presetMotor(SmartCar * smartCar) {
	int16_t speed = 0;
	
	speed = smartCar->motor.targetSpeed;
	while(1){
		Segment_print(&smartCar->segment[1], (uint16_t)smartCar->motor.targetSpeed);
		Segment_print(&smartCar->segment[2], (uint16_t)smartCar->encoder.speed);
		switch(board.button.read()){
		case 1:
			speed += 20;
			break;
		case 2:
			speed -= 20;
			break;
		case 4:
			return;
		}
		
		Motor_runAs(&smartCar->motor, speed);
	}	
}
void presetKp(SmartCar * smartCar) {
	uint32_t kp;
	kp = smartCar->motor.kp;
	while(1){
		Segment_print(&smartCar->segment[1], (uint16_t)smartCar->motor.targetSpeed);
		Segment_print(&smartCar->segment[2], (uint16_t)kp);
		switch(board.button.read()){
		case 1:
			kp += 1;
			break;
		case 2:
			kp -= 1;
			break;
		case 4:
			return;
		}
		if(kp < 1){
			kp = 1;
		} else if (kp > 100){
			kp = 100;
		}
		
		Motor_setkp(&smartCar->motor,kp);
	}
}
void presetKi(SmartCar * smartCar) {
	uint32_t ki;
	ki = smartCar->motor.ki;
	while(1){
		Segment_print(&smartCar->segment[1], (uint16_t)smartCar->motor.targetSpeed);
		Segment_print(&smartCar->segment[2], (uint16_t)ki);
		switch(board.button.read()){
		case 1:
			ki += 1;
			break;
		case 2:
			ki -= 1;
			break;
		case 4:
			return;
		}
		if(ki < 1){
			ki = 1;
		} else if (ki > 100){
			ki = 100;
		}
		
		Motor_setki(&smartCar->motor,ki);
	}
}

void presetKd(SmartCar * smartCar) {
	uint32_t kd;
	kd = smartCar->motor.kd;
	while(1){
		Segment_print(&smartCar->segment[1], (uint16_t)smartCar->motor.targetSpeed);
		Segment_print(&smartCar->segment[2], (uint16_t)kd);
		switch(board.button.read()){
		case 1:
			kd += 1;
			break;
		case 2:
			kd -= 1;
			break;
		case 4:
			return;
		}
		if(kd < 1){
			kd = 1;
		} else if (kd > 100){
			kd = 100;
		}
		
		Motor_setkd(&smartCar->motor,kd);
	}
}

void presetCheckPID(SmartCar * smartCar) {
	int i = 0;
	for( i=0 ; i<16 ; i++){
		LEDData_add(&smartCar->barLED[0].data,i);
		LEDData_add(&smartCar->barLED[1].data,i);
	}
	
	BarLED_print(&smartCar->barLED[0], smartCar->barLED[0].data);
	BarLED_print(&smartCar->barLED[1], smartCar->barLED[1].data);
	Segment_print(&smartCar->segment[1], (uint16_t)smartCar->encoder.speed);
	Segment_print(&smartCar->segment[2], (uint16_t)smartCar->motor.targetSpeed);
	while(1){
		switch(board.button.read()){
		case 4:
			return;
		}
	}
}
