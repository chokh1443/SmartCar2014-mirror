#include "camera.h"
#include "adc_drv.h"

void Camera_onTick(Camera * this);

struct {
	uint8_t CLK;
	uint8_t SI;
	uint8_t CH;
} CAMERA_PINS[2] = {
	{DO_CAM1_CLK, DO_CAM1_SI, ADC_CAM1},
	{DO_CAM2_CLK, DO_CAM2_SI, ADC_CAM2}
};

void Camera_init(Camera * this, uint8_t id) {
	
	this->id = id;
	this->count = 0;
	
	this->clk = 4000;
	this->clk_change = 0;
		
	board.addCameraHandler(bind(this, (ThisCall)Camera_onTick));
	
}
uint16_t * Camera_get(Camera * this){
	return this->rawData;
}

void Camera_onTick(Camera * this) {
	//TODO optimaize. maybe can read camera double speed.
	uint16_t value;
	if (this->count == 0 || this->count == 1) {
		board.gpio.on(CAMERA_PINS[this->id].SI);
	} else {
		board.gpio.off(CAMERA_PINS[this->id].SI);
	}

	board.gpio.on(CAMERA_PINS[this->id].CLK);

	value = A2D_GetSingleCh_10bit(CAMERA_PINS[this->id].CH);
	this->rawData[this->count] = (value * 9 + this->rawData[this->count] * 1) / 10;

	board.gpio.off(CAMERA_PINS[this->id].CLK);

	if((this->count == 127) && (this->clk_change == 1)){
		PIT.CH[1].LDVAL.R  = this->clk;
		this->clk_change = 0;
	}
	this->count = ++this->count % 128;
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
void Camera_setClk(Camera * this, uint16_t value){
	this->clk = value;
	this->clk_change = 1;
}
uint16_t Camera_getClk(Camera * this){
	return this->clk;
}
