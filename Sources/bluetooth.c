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

void sendBTInt2(int integer){
	const static unsigned char int2chrArr[10] = {'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9'};
	if(integer < 0){
		UartTxMsg((unsigned char *)("-"), 1);
		integer *= -1;
	}
	UartTxMsg((unsigned char *)(int2chrArr + integer/10),1);
	UartTxMsg((unsigned char *)(int2chrArr + integer%10),1);
}
void sendBTInt4(int integer){
	const static unsigned char int2chrArr[10] = {'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9'};
	if(integer < 0){
		UartTxMsg((unsigned char *)("-"), 1);
		integer *= -1;
	}
	UartTxMsg((unsigned char *)(int2chrArr + integer/1000),1);
	UartTxMsg((unsigned char *)(int2chrArr + integer%1000/100),1);
	UartTxMsg((unsigned char *)(int2chrArr + integer%100/10),1);
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
void sendBTCamera(Camera * camera) {
	static int a=0,b=0;
	int i;
	
	sendBTInt(camera->id);
	sendBTChar("\t",1);
	if(camera->id == 0){
		a=++a%12;
		sendBTInt2(a);
	} else if(camera->id == 1){
		b=++b%12;
		sendBTInt2(b);
	}
	sendBTChar("\t",1);
	for(i = a*10 ; i < (a*10+10) ; i++){
		sendBTInt4(camera->rawData[i]);
		sendBTChar("\t",1);
	}
	sendBTNewLine();
}
