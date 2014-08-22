#pragma once

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"

#include "UART_drv_api.h"

#include "smartcar.h"
#include "gpio_drv.h"
#include "test.h"
#include "utils.h"
#include "preset.h"

typedef struct {
	int16_t data[128];
	Range range;
} DifferentialData;

void getDifferentialData(uint16_t * data, DifferentialData * result);
void binarization(DifferentialData * differentialData, uint8_t * result);


