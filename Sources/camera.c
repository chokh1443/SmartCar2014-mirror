#include "camera.h"
#include "adc_drv.h"

void Camera_onTick(Camera * this);

struct {
	uint8_t CLK;
	uint8_t SI;
} CAMERA_PINS[2] = {
	{DO_CAM1_CLK, DO_CAM1_SI},
	{DO_CAM2_CLK, DO_CAM2_SI}
};

void Camera_init(Camera * this, uint8_t id) {
	board.addCameraHandler(bind(this, (ThisCall)Camera_onTick));
}
uint16_t * Camera_get(Camera * this){
	
}
void Camera_onTick(Camera * this) {
	static uint8_t count = 0;
	
	if (count == 0 || count == 1) {
		board.gpio.on(DO_CAM1_SI);
	} else {
		board.gpio.off(DO_CAM1_SI);
	}
	
	board.gpio.on(DO_CAM1_CLK);

	this->rawData[count] = A2D_GetSingleCh_10bit(ADC_CAM1);
	
	board.gpio.off(DO_CAM1_CLK);

	count = ++count % 128;
}
