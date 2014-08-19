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
	board.addCameraHandler(bind(this, (ThisCall)Camera_onTick));
	
	/*PIT.CH[1].LDVAL.R  = 0x00000FA0; 4000 ~ 12000*/
	Camera_setInterval(this, 12000);
}
uint16_t * Camera_get(Camera * this){
	return this->rawData;
}

void Camera_setInterval(Camera * this, uint32_t value){
	PIT.CH[1].LDVAL.R = value;
}
void Camera_onTick(Camera * this) {
	
	if (this->count == 0 || this->count == 1) {
		board.gpio.on(CAMERA_PINS[this->id].SI);
	} else {
		board.gpio.off(CAMERA_PINS[this->id].SI);
	}

	board.gpio.on(CAMERA_PINS[this->id].CLK);

	this->rawData[this->count] = A2D_GetSingleCh_10bit(CAMERA_PINS[this->id].CH);

	board.gpio.off(CAMERA_PINS[this->id].CLK);

	this->count = ++this->count % 128;
}
