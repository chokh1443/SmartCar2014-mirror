#include "camera.h"
#include "adc_drv.h"
#include "typedefs.h"

void Camera_init(Camera * this) {
	board.addCameraHandler(bind(this, (ThisCall)Camera_onTick));
	this->pins->CLS = 0;
	this->pins->SI = 0;
}

void Camera_onTick(Camera * this) {
	static uint8_t count = 0;
	
	if (count == 0 || count == 1) {
		board.gpio.on(DO_CAM1_SI);
	} else {
		board.gpio.off(DO_CAM1_SI);
	}
	
	board.gpio.on(DO_CAM1_CLK);
	if(count > 5 && count < 128){
		this->rawData[count] = A2D_GetSingleCh_10bit(ADC_CAM1);
	}
	
	board.gpio.off(DO_CAM1_CLK);

	count = ++count % 128;
}
