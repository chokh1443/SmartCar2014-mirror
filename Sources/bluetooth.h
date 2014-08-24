#pragma once

#include "UART_drv_api.h"
#include "typedefs.h"
#include "smartcar.h"

void sendBTNewLine(void);
void sendBTChar(const char * arr, unsigned long length);
void sendBTInt(int integer);
void sendBTPID(Motor * motor);
