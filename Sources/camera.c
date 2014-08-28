#include "camera.h"
#include "adc_drv.h"
#include "bluetooth.h"

void Camera_onTick(Camera * this);

struct {
	uint8_t CLK;
	uint8_t SI;
	uint8_t CH;
} CAMERA_PINS[2] = {
	{DO_CAM1_CLK, DO_CAM1_SI, ADC_CAM1},
	{DO_CAM2_CLK, DO_CAM2_SI, ADC_CAM2}
};

void Camera_autoSet(Camera * this);

void Camera_init(Camera * this, uint8_t id) {
	
	this->id = id;
	this->count = 0;
		
	board.addCameraHandler(bind(this, (ThisCall)Camera_onTick));
}
uint16_t * Camera_get(Camera * this){
	return this->rawData;
}

void Camera_onTick(Camera * this) {
//	static uint32_t clockSpeed = 4000;
	uint16_t value;
	
	if (this->count == 0 || this->count == 1) {
		 
		board.gpio.on(CAMERA_PINS[this->id].SI);
	} else {
		board.gpio.off(CAMERA_PINS[this->id].SI);
	}

	board.gpio.on(CAMERA_PINS[this->id].CLK);

	value = A2D_GetSingleCh_10bit(CAMERA_PINS[this->id].CH);
	this->sum += value;
	this->rawData[this->count] = (value * 9 + this->rawData[this->count] * 1) / 10;

	board.gpio.off(CAMERA_PINS[this->id].CLK);
	
	if(this->count == 127){
		this->average = this->sum / 128;
		this->sum = 0;
		Camera_autoSet(this);
	}
	
	this->count = ++this->count % 128;
}
void Camera_autoSet(Camera * this){
	if(this->average < 750){
		if(PIT.CH[1].LDVAL.R < 37000) {
			PIT.CH[1].LDVAL.R += 500;
		}
	} else if(this->average > 950){
		if (PIT.CH[1].LDVAL.R > 24000) {
			PIT.CH[1].LDVAL.R -= 1000;
		} else if(PIT.CH[1].LDVAL.R > 2000){
			PIT.CH[1].LDVAL.R -= 500;
		}
	}
}
uint32_t Camera_getInterval(){
	return PIT.CH[1].LDVAL.R;
}
uint16_t Camera_minValue(Camera * this){
	int minVal = 1000;
	int i;
	for( i=10 ; i<118 ; i++){
		if(this->rawData[i] < minVal){
			minVal = this->rawData[i];
		}
	}
	return minVal;
}
uint16_t Camera_maxValue(Camera * this){
	int maxVal = 0;
	int i;
	for( i=10 ; i<118 ; i++){
		if(this->rawData[i] > maxVal){
			maxVal = this->rawData[i];
		}
	}
	return maxVal;
}
