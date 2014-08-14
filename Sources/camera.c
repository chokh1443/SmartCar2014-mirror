#include "camera.h"
#include "adc_drv.h"

void Camera_onTick(Camera * this);

struct {
	uint8_t CLK;
	uint8_t SI;
} CAMERA_PINS[2] = {
	{DO_CAM_CLK, DO_CAM_SI},
	{DO_CAM_CLK, DO_CAM_SI}
};

void Camera_init(Camera * this, uint8_t id) {
	board.addCameraHandler(bind(this, (ThisCall)Camera_onTick));
}
void Camera_onTick(Camera * this) {
	static uint8_t count = 0;
	
	if (count == 0 || count == 1) {
		board.gpio.on(DO_CAM_SI);
	} else {
		board.gpio.off(DO_CAM_SI);
	}
	
	board.gpio.on(DO_CAM_CLK);

	this->data[count] = A2D_GetSingleCh_10bit(ADC_CAM1);
	
	board.gpio.off(DO_CAM_CLK);

	count = ++count % 128;
}
