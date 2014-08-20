#include "preset.h"

void enterPreset(SmartCar * smartCar, int menu);
void presetCamera(SmartCar * smartCar);
void presetChangePIT(SmartCar * smartCar);

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
			menu = 6;
		} else if(menu > 6){
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
		break;
	case 4:
		return;
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
		
		BarLED_print(&smartCar->barLED[0], (LEDData){{pitVal/1000},1});
		
		Segment_print(&smartCar->segment[1], (uint16_t)(minVal[0] < minVal[1]) ? minVal[0] : minVal[1]);
		Segment_print(&smartCar->segment[2], (uint16_t)(maxVal[0] < maxVal[1]) ? maxVal[1] : maxVal[0]);
	}
}
