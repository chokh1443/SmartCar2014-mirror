#include "algorithm.h"
#include "bluetooth.h"

//camera inputing	time = 0.04~0.06s(about 50ms)
//servo motor moving time = 0.2s(200ms)
//we have about 4 data for moving servo motor
//make map using 5 camera data

void start(SmartCar * smartCar){
	int16_t handle=0, handle_check=0;
	int16_t speed=200;
	AIData data[2];
	int16_t pos[2];
	
	Servo_runAs(&smartCar->servo, 0);
	Motor_Enable(&smartCar->motor);
	
	
	while(1){
		
		AIData_init(&data[0], &smartCar->camera[0]);
		AIData_init(&data[1], &smartCar->camera[1]);

		binarization(&data[0]);
		binarization(&data[1]);

		pos[0] = findIndexLR(&data[0]);//right camera
		pos[1] = findIndexRL(&data[1]);//left camera
		
		handle = handling(pos[0], pos[1]);

		//current speed
		//Segment_print(&smartCar->segment[0], smartCar->motor.targetSpeed);
		Segment_print(&smartCar->segment[1], handle);
		//Segment_print(&smartCar->segment[2], Camera_getInterval()/100);
		
		Segment_print(&smartCar->segment[0], pos[1]);
		Segment_print(&smartCar->segment[2], pos[0]);
		//print camera status
		dumpData(data[0].arr, &smartCar->barLED[0]);
		dumpData(data[1].arr, &smartCar->barLED[1]);
		
		Servo_runAs(&smartCar->servo, handle);
		Motor_runAs(&smartCar->motor, speed);

		switch (board.button.check()) {
		case 1:
			if(speed < 2000){// max speed = 2000
				speed = speed + 50;
			} else {
				speed = speed;
			}
			break;
		case 2:
			if(speed > 0){// min speed = 0
				speed = speed - 50;
			} else {
				speed = speed;
			}
			break;
		case 4:
			return;
		}
	}
}

int16_t handling(uint16_t right, uint16_t left){
	static int16_t value = 0;
	int16_t handle = 0;
	
	if(left < 100){
		handle -= left/2 + 50;
	} else {
		handle -= -2 * left + 250;
	}
	if(right < 28){
		handle += 2 * right - 6; 
	} else {
		handle += - right / 2 + 114;
	}
	handle = handle * 2;
	
		
	value = (value * 2 + handle * 8) / 10;
	return value;
}

void AIData_init(AIData * this, Camera * camera){
	int16_t min = 0, max = 0;
	uint16_t * data = camera->rawData;
	register uint16_t i;

	this->arr[0] = this->arr[1] - this->arr[0];
	for(i = 1; i < 128; i++){
		this->arr[i] = data[i] - data[i-1];
		
		//for ignore side
		if(i < 8 || i > 120){
			continue;
		}

		if(min > this->arr[i]){
			min = this->arr[i];
		}
		if(max < this->arr[i]){
			max = this->arr[i];
		}
	}
	this->min = min;
	this->max = max;

	//sendBTCamera(camera);
}

void binarization(AIData * data){
	register uint16_t i;
	int16_t lowCrit = data->min*4/5;
	int16_t highCrit = data->max*4/5;
	
	for(i = 0; i < 128; i++){
		if(data->arr[i] > highCrit) {
			data->arr[i] = 0;
		} else if(data->arr[i] < lowCrit){
			data->arr[i] = 1;
		} else {
			data->arr[i] = data->arr[i-1];
		}
	}
	/*
	for(i = 0; i < 128; i++){
		if(data->arr[i] > highCrit) {
			for(j = i; j > 0; j--){
				if(data->arr[j] < lowCrit){
					for(k = j; k < i; k++){
						data->arr[k] = 1;
					}
					break;
				}
			}
		} 
		data->arr[i] = 0;
	}
	*/
}
uint8_t findIndexRL(AIData * data){//left camera
	register uint16_t i;

	uint16_t first = 8, last = 8;
	//for ignore side
	for(i = 8; i < 120; i++){
		if(data->arr[i] == 1){
			last = i;
		} else {
			if(last - first < 2){
				//noize
				
			} else {
				return (last + first)/2;
			}
			first = i;
		}
	}
	return 255;
}


uint8_t findIndexLR(AIData * data){//right camera
	register uint16_t i;

	uint16_t first = 120, last = 120;
	//for ignore side
	for(i = 120; i > 8; i--){
		if(data->arr[i] == 1){
			last = i;
		} else {
			if(first - last < 2){
				//noize
			} else {
				return (last + first)/2;
			}
			first = i;
		}
	}
	return 255;
}

void dumpData(int16_t * data, BarLED * led){
	uint8_t i, j;
	LEDData result;
	result.len = 0;
	for(i = 0; i < 16; i ++){
		for(j = 0; j < 8; j++){
			if(data[i*7 + j + 8] == 1){
				LEDData_add(&result, i);
				break;
			}
		}
	}
	BarLED_print(led, result);
}
