#include "zp_testSegment.h"
#include "zp_pin.h"
#include "gpio_drv.h"


void printSegmentTick(void) {
	/*
	 * ���׸�Ʈ ������ִ� �Լ�
	 * �� �Լ��� Ÿ�̸� ���ͷ�Ʈ���� ��� ȣ��
	 * �ܺο� ��Ʈ�� �ִٰ� ���� zpSegFromStruct ->�̸��� �˾Ƽ� �ٲ�
	 */

	static int seq = 0;
	int zpSegment[3]; //���⿡ ���� ��� �ִٰ� �����ϰ� �ۼ�. ���߿� ���� �ٶ�
	int setVal[3];
	int i;
	

	//zpSegment[0] = zpSegFromStruct->first; //������ �׳� ���� ��
	//zpSegment[1] = zpSegFromStruct->second; //������ �׳� ���� ��
	//zpSegment[2] = zpSegFromStruct->third; //������ �׳� ���� ��

	if (seq == 0) {
		for(i =0; i < 3; i++){
			setVal[i] = zpSegment[i] % 10000 / 1000;
		}
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
	} else if (seq == 1) {
		for(i =0; i < 3; i++){
			setVal[i] = zpSegment[i] % 1000 / 100;
		}
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
	} else if (seq == 2) {
		for(i =0; i < 3; i++){
			setVal[i] = zpSegment[i] % 100 / 10;
		}
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
	} else if (seq == 3) {
		for(i =0; i < 3; i++){
			setVal[i] = zpSegment[i] % 10;
		}
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
	}
	seq = ++seq%4;
	
}

void setSegmentNumber(int* num) {
	static const int SEG_ID[3][4] = {
		{DO_SEG1_A, DO_SEG1_B, DO_SEG1_C, DO_SEG1_D},
		{DO_SEG2_A, DO_SEG2_B, DO_SEG2_C, DO_SEG2_D},
		{DO_SEG3_A, DO_SEG3_B, DO_SEG3_C, DO_SEG3_D}
	};
	int i, k;
	for(k = 0; k < 3; k++){
		for(i = 0; i < 4; i++){
			GPIO_SetState(SEG_ID[k][i], (0x01<<i) & num[k]);
		}
	}
}

void setSegmentSelect(int seq) {
	static const int SEG_ID[3][4] = {
		{DO_SEG1_A, DO_SEG1_B, DO_SEG1_C, DO_SEG1_D},
		{DO_SEG2_A, DO_SEG2_B, DO_SEG2_C, DO_SEG2_D},
		{DO_SEG3_A, DO_SEG3_B, DO_SEG3_C, DO_SEG3_D}
	};
	int i, j;
	for(i = 0; i < 4; i++){
		if(seq == i){
			for(j = 0; j < 3; j++){
				GPIO_SetState(SEG_ID[j][i], 1);
			}
		} else {
			for(j = 0; j < 3; j++){
				GPIO_SetState(SEG_ID[j][i], 0);
			}
		}
	}
}

