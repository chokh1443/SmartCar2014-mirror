#include "zp_testSegment.h"
#include "zp_pin.h"
#include "gpio_drv.h"


void printSegmentTick(void) {
	/*
	 * 세그먼트 출력해주는 함수
	 * 이 함수는 타이머 인터럽트에서 계속 호출
	 * 외부에 스트럭 있다고 가정 zpSegFromStruct ->이름은 알아서 바꿔
	 */

	static int seq = 0;
	int zpSegment[3]; //여기에 값이 들어 있다고 가정하고 작성. 나중에 수정 바람
	int setVal[3];
	

	//zpSegment[0] = zpSegFromStruct->first; //변수명 그냥 대충 함
	//zpSegment[1] = zpSegFromStruct->second; //변수명 그냥 대충 함
	//zpSegment[2] = zpSegFromStruct->third; //변수명 그냥 대충 함

	if (seq == 0) {
		setVal[0] = zpSegment[0] % 10000 / 1000;
		setVal[1] = zpSegment[1] % 10000 / 1000;
		setVal[2] = zpSegment[2] % 10000 / 1000;
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
		seq = 1;
	} else if (seq == 1) {
		setVal[0] = zpSegment[0] % 1000 / 100;
		setVal[1] = zpSegment[1] % 1000 / 100;
		setVal[2] = zpSegment[2] % 1000 / 100;
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
		seq = 2;
	} else if (seq == 2) {
		setVal[0] = zpSegment[0] % 100 / 10;
		setVal[1] = zpSegment[1] % 100 / 10;
		setVal[2] = zpSegment[2] % 100 / 10;
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
		seq = 3;
	} else if (seq == 3) {
		setVal[0] = zpSegment[0] % 10;
		setVal[1] = zpSegment[1] % 10;
		setVal[2] = zpSegment[2] % 10;
		setSegmentNumber(setVal);
		setSegmentSelect(seq);
		seq = 0;
	}
	
	
}

void setSegmentNumber(int* num) {
	switch (num[0]) {
	case 0:
		GPIO_SetState(DO_SEG1_A, 0);
		GPIO_SetState(DO_SEG1_B, 0);
		GPIO_SetState(DO_SEG1_C, 0);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 1:
		GPIO_SetState(DO_SEG1_A, 1);
		GPIO_SetState(DO_SEG1_B, 0);
		GPIO_SetState(DO_SEG1_C, 0);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 2:
		GPIO_SetState(DO_SEG1_A, 0);
		GPIO_SetState(DO_SEG1_B, 1);
		GPIO_SetState(DO_SEG1_C, 0);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 3:
		GPIO_SetState(DO_SEG1_A, 1);
		GPIO_SetState(DO_SEG1_B, 1);
		GPIO_SetState(DO_SEG1_C, 0);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 4:
		GPIO_SetState(DO_SEG1_A, 0);
		GPIO_SetState(DO_SEG1_B, 0);
		GPIO_SetState(DO_SEG1_C, 1);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 5:
		GPIO_SetState(DO_SEG1_A, 1);
		GPIO_SetState(DO_SEG1_B, 0);
		GPIO_SetState(DO_SEG1_C, 1);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 6:
		GPIO_SetState(DO_SEG1_A, 0);
		GPIO_SetState(DO_SEG1_B, 1);
		GPIO_SetState(DO_SEG1_C, 1);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 7:
		GPIO_SetState(DO_SEG1_A, 1);
		GPIO_SetState(DO_SEG1_B, 1);
		GPIO_SetState(DO_SEG1_C, 1);
		GPIO_SetState(DO_SEG1_D, 0);
		break;
	case 8:
		GPIO_SetState(DO_SEG1_A, 0);
		GPIO_SetState(DO_SEG1_B, 0);
		GPIO_SetState(DO_SEG1_C, 0);
		GPIO_SetState(DO_SEG1_D, 1);
		break;
	case 9:
		GPIO_SetState(DO_SEG1_A, 1);
		GPIO_SetState(DO_SEG1_B, 0);
		GPIO_SetState(DO_SEG1_C, 0);
		GPIO_SetState(DO_SEG1_D, 1);
		break;
	}

	switch (num[1]) {
	case 0:
		GPIO_SetState(DO_SEG2_A, 0);
		GPIO_SetState(DO_SEG2_B, 0);
		GPIO_SetState(DO_SEG2_C, 0);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 1:
		GPIO_SetState(DO_SEG2_A, 1);
		GPIO_SetState(DO_SEG2_B, 0);
		GPIO_SetState(DO_SEG2_C, 0);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 2:
		GPIO_SetState(DO_SEG2_A, 0);
		GPIO_SetState(DO_SEG2_B, 1);
		GPIO_SetState(DO_SEG2_C, 0);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 3:
		GPIO_SetState(DO_SEG2_A, 1);
		GPIO_SetState(DO_SEG2_B, 1);
		GPIO_SetState(DO_SEG2_C, 0);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 4:
		GPIO_SetState(DO_SEG2_A, 0);
		GPIO_SetState(DO_SEG2_B, 0);
		GPIO_SetState(DO_SEG2_C, 1);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 5:
		GPIO_SetState(DO_SEG2_A, 1);
		GPIO_SetState(DO_SEG2_B, 0);
		GPIO_SetState(DO_SEG2_C, 1);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 6:
		GPIO_SetState(DO_SEG2_A, 0);
		GPIO_SetState(DO_SEG2_B, 1);
		GPIO_SetState(DO_SEG2_C, 1);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 7:
		GPIO_SetState(DO_SEG2_A, 1);
		GPIO_SetState(DO_SEG2_B, 1);
		GPIO_SetState(DO_SEG2_C, 1);
		GPIO_SetState(DO_SEG2_D, 0);
		break;
	case 8:
		GPIO_SetState(DO_SEG2_A, 0);
		GPIO_SetState(DO_SEG2_B, 0);
		GPIO_SetState(DO_SEG2_C, 0);
		GPIO_SetState(DO_SEG2_D, 1);
		break;
	case 9:
		GPIO_SetState(DO_SEG2_A, 1);
		GPIO_SetState(DO_SEG2_B, 0);
		GPIO_SetState(DO_SEG2_C, 0);
		GPIO_SetState(DO_SEG2_D, 1);
		break;
	}
	switch (num[2]) {
	case 0:
		GPIO_SetState(DO_SEG3_A, 0);
		GPIO_SetState(DO_SEG3_B, 0);
		GPIO_SetState(DO_SEG3_C, 0);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 1:
		GPIO_SetState(DO_SEG3_A, 1);
		GPIO_SetState(DO_SEG3_B, 0);
		GPIO_SetState(DO_SEG3_C, 0);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 2:
		GPIO_SetState(DO_SEG3_A, 0);
		GPIO_SetState(DO_SEG3_B, 1);
		GPIO_SetState(DO_SEG3_C, 0);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 3:
		GPIO_SetState(DO_SEG3_A, 1);
		GPIO_SetState(DO_SEG3_B, 1);
		GPIO_SetState(DO_SEG3_C, 0);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 4:
		GPIO_SetState(DO_SEG3_A, 0);
		GPIO_SetState(DO_SEG3_B, 0);
		GPIO_SetState(DO_SEG3_C, 1);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 5:
		GPIO_SetState(DO_SEG3_A, 1);
		GPIO_SetState(DO_SEG3_B, 0);
		GPIO_SetState(DO_SEG3_C, 1);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 6:
		GPIO_SetState(DO_SEG3_A, 0);
		GPIO_SetState(DO_SEG3_B, 1);
		GPIO_SetState(DO_SEG3_C, 1);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 7:
		GPIO_SetState(DO_SEG3_A, 1);
		GPIO_SetState(DO_SEG3_B, 1);
		GPIO_SetState(DO_SEG3_C, 1);
		GPIO_SetState(DO_SEG3_D, 0);
		break;
	case 8:
		GPIO_SetState(DO_SEG3_A, 0);
		GPIO_SetState(DO_SEG3_B, 0);
		GPIO_SetState(DO_SEG3_C, 0);
		GPIO_SetState(DO_SEG3_D, 1);
		break;
	case 9:
		GPIO_SetState(DO_SEG3_A, 1);
		GPIO_SetState(DO_SEG3_B, 0);
		GPIO_SetState(DO_SEG3_C, 0);
		GPIO_SetState(DO_SEG3_D, 1);
		break;
	}
}

void setSegmentSelect(int seq) {
	switch (seq) {
	case 0:
		GPIO_SetState(DO_SEG1_1, 1);
		GPIO_SetState(DO_SEG1_2, 0);
		GPIO_SetState(DO_SEG1_3, 0);
		GPIO_SetState(DO_SEG1_4, 0);
		GPIO_SetState(DO_SEG2_1, 1);
		GPIO_SetState(DO_SEG2_2, 0);
		GPIO_SetState(DO_SEG2_3, 0);
		GPIO_SetState(DO_SEG2_4, 0);
		GPIO_SetState(DO_SEG3_1, 1);
		GPIO_SetState(DO_SEG3_2, 0);
		GPIO_SetState(DO_SEG3_3, 0);
		GPIO_SetState(DO_SEG3_4, 0);
		break;
	case 1:
		GPIO_SetState(DO_SEG1_1, 0);
		GPIO_SetState(DO_SEG1_2, 1);
		GPIO_SetState(DO_SEG1_3, 0);
		GPIO_SetState(DO_SEG1_4, 0);
		GPIO_SetState(DO_SEG2_1, 0);
		GPIO_SetState(DO_SEG2_2, 1);
		GPIO_SetState(DO_SEG2_3, 0);
		GPIO_SetState(DO_SEG2_4, 0);
		GPIO_SetState(DO_SEG3_1, 0);
		GPIO_SetState(DO_SEG3_2, 1);
		GPIO_SetState(DO_SEG3_3, 0);
		GPIO_SetState(DO_SEG3_4, 0);
		break;
	case 2:
		GPIO_SetState(DO_SEG1_1, 0);
		GPIO_SetState(DO_SEG1_2, 0);
		GPIO_SetState(DO_SEG1_3, 1);
		GPIO_SetState(DO_SEG1_4, 0);
		GPIO_SetState(DO_SEG2_1, 0);
		GPIO_SetState(DO_SEG2_2, 0);
		GPIO_SetState(DO_SEG2_3, 1);
		GPIO_SetState(DO_SEG2_4, 0);
		GPIO_SetState(DO_SEG3_1, 0);
		GPIO_SetState(DO_SEG3_2, 0);
		GPIO_SetState(DO_SEG3_3, 1);
		GPIO_SetState(DO_SEG3_4, 0);
		break;
	case 3:
		GPIO_SetState(DO_SEG1_1, 0);
		GPIO_SetState(DO_SEG1_2, 0);
		GPIO_SetState(DO_SEG1_3, 0);
		GPIO_SetState(DO_SEG1_4, 1);
		GPIO_SetState(DO_SEG2_1, 0);
		GPIO_SetState(DO_SEG2_2, 0);
		GPIO_SetState(DO_SEG2_3, 0);
		GPIO_SetState(DO_SEG2_4, 1);
		GPIO_SetState(DO_SEG3_1, 0);
		GPIO_SetState(DO_SEG3_2, 0);
		GPIO_SetState(DO_SEG3_3, 0);
		GPIO_SetState(DO_SEG3_4, 1);
		break;
	}
}

