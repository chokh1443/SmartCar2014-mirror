#include "zp_testBluetooth.h"
#include "UART_drv_api.h"


void sendBlueChar(const char * arr, unsigned long length){
	UartTxMsg((unsigned char *)arr, length);
}
void sendBlueInt(int integer){
	const static unsigned char int2chrArr[10] = {'0', '1', '2', '3', '4',
			'5', '6', '7', '8', '9'};
	if(integer < 0){
		UartTxMsg((unsigned char *)("-"), 1);
		integer *= -1;
	} else {
		UartTxMsg((unsigned char *)(" "), 1);
	}
	UartTxMsg((unsigned char *)(int2chrArr + integer%10000/1000),1);
	UartTxMsg((unsigned char *)(int2chrArr + integer%1000/100),1);
	UartTxMsg((unsigned char *)(int2chrArr + integer%100/10),1);
	UartTxMsg((unsigned char *)(int2chrArr + integer%10),1);
}

void sendBlueArrayDump(const int * arr, int length){
	int i = 0;
	sendBlueNewLine();
	for(i = 0; i < 42; i ++){
		if(arr[i*3] && arr[i*3+1] && arr[i*3+2]){
			UartTxMsg((unsigned char *)("B"),1);
		}	else {
			UartTxMsg((unsigned char *)("W"),1);
		}
	}
	sendBlueNewLine();
}
void sendBlueNewLine() {
	UartTxMsg((unsigned char *)newLine,2);
}
void sendBlueMsg(const char * arr, unsigned long length){
	sendBlueNewLine();
	UartTxMsg((unsigned char *)arr, length);
	sendBlueNewLine();
}
void sendBluePID(int count, int target, int pwm){
	struct Sensor * pSensor = getSensor();
	sendBlueNewLine();
	//"x : t = xx, enc = xx, pwm = xx, mA=xx, mB= xx"
	sendBlueInt(count);
	sendBlueChar(": t=", 4);
	sendBlueInt(target);
	sendBlueChar(", enc=", 6);
	sendBlueInt(pSensor->speed);
	sendBlueChar(", pwm=", 6);
	sendBlueInt(pwm);
	sendBlueChar(", mA=", 5);
	sendBlueInt(pSensor->motorA);
	sendBlueChar(", mB=", 5);
	sendBlueInt(pSensor->motorB);
	sendBlueChar(", pot[0]=", 10);
	sendBlueInt((pSensor->potValue[0]));
	sendBlueChar(", pot[1]=", 10);
	sendBlueInt((pSensor->potValue[1]));
	sendBlueChar(", pot[2]=", 10);
	sendBlueInt((pSensor->potValue[2]));
	sendBlueNewLine();
}
int recvBlueInt(void){
	int ret = 0, sign = 0;
	unsigned char data[2] = {'\0', '\0'};

	while(1)
	{
		UartRxFillBuf();
		if(UartRxBufEmpty())
			continue;
		if(data[0] != '-')
			data[1] = data[0];
		data[0] = UartRxDataByte();
		if(sign == 0)
		{
			if(data[0] == '-')
			{
				sign = -1;
				continue;
			} else {
				sign = 1;
			}
		}
//		if(data[1] == '\r') {
//			if(data[0] == '\n')
//				break;
//			else
//				return -1;
//		}
//		if(data[0] == '\r')
//			continue;
		if(data[0] == '\r' || data[0] == '\n')
			break;
		if('0' <= data[0] && data[0] <= '9')
			ret = ret * 10 + data[0] - '0';
		else
			return -1;
	}
	return ret * sign;
}
