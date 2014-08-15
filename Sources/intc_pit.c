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
 * Project Last Save Date : 11-Aug-2014 21:57:30
 *
 * Created on Date        : 11-Aug-2014 21:57:40
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

/************************* INTERRUPT HANDLERS ************************/
void PIT_TIMER (void)
{
	ON_DISPLAY();
    PIT.CH[0].TFLG.R = 0x00000001;
}


void PIT_ENCODER (void)
{
    PIT.CH[1].TFLG.R = 0x00000001;
}


void PIT_CAMERA (void)
{
	ON_CAMERA();
    PIT.CH[2].TFLG.R = 0x00000001;
}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

