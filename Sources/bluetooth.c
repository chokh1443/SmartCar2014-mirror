#include "bluetooth.h"


void sendBTNewLine(void){
	unsigned char newLine[2] = {'\r','\n'};
	UartTxMsg((unsigned char *)newLine,2);
}
void sendBTChar(const char * arr, unsigned long length){
	UartTxMsg((unsigned char *)arr, length);
}
void sendBTInt(int integer){
	const static unsigned char int2chrArr[10] = {'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9'};
	if(integer < 0){
		UartTxMsg((unsigned char *)("-"), 1);
		integer *= -1;
	}
	if(integer/10 > 1){
		sendBTInt(integer/10);
	}
	UartTxMsg((unsigned char *)(int2chrArr + integer%10),1);
}

void sendBTPID(Motor * motor) {
	static int16_t timer = 0;
	//t=xxxx,e=xxxx,c=xxxx,p=xxx,i=xxx,d=xxx
	int e = (motor->encoder->speed*6);
	sendBTInt(timer);
	sendBTChar("\t",1);
	sendBTInt(e);
	sendBTChar("\t",1);
	sendBTInt(motor->targetSpeed);
	sendBTChar("\t",1);
	sendBTInt(motor->currentSpeed);
	sendBTNewLine();
	timer++;
}
void sendCamera(Camera * camera) {
	uint8_t i;
	for(i = 0 ; i < 128 ; i++){
		sendBTInt(camera->rawData[i]);
	}	
	sendBTNewLine();
}
