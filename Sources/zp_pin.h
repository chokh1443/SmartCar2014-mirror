#pragma once


//default 
#define ADC_POT         0//PB4_potvalue
#define ADC_POT_GPIO    20//PB4_potvalue
#define ADC_PHOTO       1//PB5_photoSensor
#define ADC_PHOTO_GPIO  21//PB5_photoSensor
#define DI_S1           64//PE0_Switch1_Input
#define DI_S2           65//PE1_Switch2_Input
#define DI_S3           66//PE2_Switch3_Input
#define DI_S4           67//PE3_Switch4_Input
#define DO_LED1         68//PE4_LED1_Output
#define DO_LED2         69//PE5_LED2_Output
#define DO_LED3         70//PE6_LED3_Output
#define DO_LED4         71//PE7_LED3_Output

//camera
#define DO_CAM_CLK      62//PD14_CAM_CLK
#define DO_CAM_SI       63//PD15_CAM_SI
#define ADC_CAM1        14//PD10_CAM1_AO
#define ADC_CAM1_GPIO   58//PD10_CAM1_AO
#define ADC_CAM2        15//PD11_CAM2_AO
#define ADC_CAM2_GPIO   59//PD11_CAM2_AO

//motor
#define DO_ENABLE       5//PA5_MOTOR_EN
#define ADC_AIFB        4//PD0_MOTORA_IFB
#define ADC_AIFB_GPIO   48//PD0_MOTORA_IFB
#define ADC_BIFB        5//PD1_MOTORB_IFB
#define ADC_BIFB_GPIO   49//PD1_MOTORB_IFB
#define PWM_AIN1        1//PA1_MOTORA_IN1
#define PWM_AIN1_GPIO   1//PA1_MOTORA_IN1
#define DO_AIN2         3//PA3_MOTORA_IN2
#define PWM_BIN1        2//PA2_MOTORB_IN1
#define PWM_BIN1_GPIO   2//PA2_MOTORB_IN1
#define DO_BIN2         4//PA4_MOTORB_IN2

//servo
#define PWM_SERVO       0//PA0_SERVO_PWM
#define PWM_SERVO_GPIO  0//PA0_SERVO_PWM

//encoder
#define DI_ENC_A_INTC   14//PA14_ENC_INTC
#define DI_ENC_B        15//PA15_ENC_SI

//segment
#define DO_SEG1_A       80//PF0_SEG1_OUTA
#define DO_SEG1_B       81//PF1_SEG1_OUTB
#define DO_SEG1_C       82//PF2_SEG1_OUTC
#define DO_SEG1_D       83//PF3_SEG1_OUTD
#define DO_SEG2_A       84//PF4_SEG2_OUTA
#define DO_SEG2_B       85//PF5_SEG2_OUTB
#define DO_SEG2_C       86//PF6_SEG2_OUTC
#define DO_SEG2_D       87//PF7_SEG2_OUTD
#define DO_SEG3_A       88//PF8_SEG3_OUTA
#define DO_SEG3_B       89//PF9_SEG3_OUTB
#define DO_SEG3_C       90//PF10_SEG3_OUTC
#define DO_SEG3_D       91//PF11_SEG3_OUTD


#define DO_SEG1_1       96//PG0_SEG1_SEL1
#define DO_SEG1_2       97//PG1_SEG1_SEL2
#define DO_SEG1_3       98//PG2_SEG1_SEL3
#define DO_SEG1_4       99//PG3_SEG1_SEL4
#define DO_SEG2_1       100//PG4_SEG2_SEL1
#define DO_SEG2_2       101//PG5_SEG2_SEL2
#define DO_SEG2_3       102//PG6_SEG2_SEL3
#define DO_SEG2_4       103//PG7_SEG2_SEL4
#define DO_SEG3_1       104//PG8_SEG3_SEL1
#define DO_SEG3_2       105//PG9_SEG3_SEL2
#define DO_SEG3_3       106//PG10_SEG3_SEL3
#define DO_SEG3_4       107//PG11_SEG3_SEL4

//bar LED
#define DO_BAR1_A       29//PB13_BAR1_A
#define DO_BAR1_B       30//PB14_BAR1_B
#define DO_BAR1_C       31//PB15_BAR1_C
#define DO_BAR1_ON      108//PG12_BAR1_ON

#define DO_BAR2_A       36//PC4_BAR2_A
#define DO_BAR2_B       37//PC5_BAR2_B
#define DO_BAR2_C       38//PC6_BAR2_C
#define DO_BAR2_ON      109//PG13_BAR2_ON

#define DO_BAR3_A       39//PC7_BAR3_A
#define DO_BAR3_B       40//PC8_BAR3_B
#define DO_BAR3_C       41//PC9_BAR3_C
#define DO_BAR3_ON      110//PG14_BAR3_ON

#define DO_BAR4_A       45//PC13_BAR4_A
#define DO_BAR4_B       46//PC14_BAR4_B
#define DO_BAR4_C       47//PC15_BAR4_C
#define DO_BAR4_ON      111//PG15_BAR1_ON
      


//void initPin(void);
