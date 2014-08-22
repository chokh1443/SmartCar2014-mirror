/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : zpSmartCar
 *
 * Project File           : zpSmartCar.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.2.1.5
 *
 * file                   : intc_pit.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 16-Aug-2014 01:46:51
 *
 * Created on Date        : 16-Aug-2014 01:46:53
 *
 * Brief Description      : This  file contains  the interrupt service routine  for the Periodic Interrupt Timer
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when PIT(Periodic Interrupt
 *                         Timer) function is defined in INTC peripheral.This
 *                         file contains the Interrupt handlers routines for PIT.
 *                         In Interrupt handlers routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_pit.h"
#include "board.h"


/************************* INTERRUPT HANDLERS ************************/

void PIT_ENCODER (void)
{
	static uint16_t count = 0;
	ON_ENCODER();
	ON_MOTOR();
//	if(count++ > 10){
//		ON_MOTOR();
//		count = 0;
//	}

    PIT.CH[0].TFLG.R = 0x00000001;

}


void PIT_CAMERA (void)
{
    ON_CAMERA();
    PIT.CH[1].TFLG.R = 0x00000001;

}


void PIT_DISPLAY (void)
{
    ON_DISPLAY();
    PIT.CH[2].TFLG.R = 0x00000001;

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

