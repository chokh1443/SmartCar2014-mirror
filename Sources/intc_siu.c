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
 * file                   : intc_siu.c
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
 * Brief Description      : This  file contains  the interrupt service routine  for the SIU
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when SIU function is defined
 *                         in INTC peripheral.This file contains the Interrupt
 *                         handlers routines for SIU. In Interrupt handlers
 *                         routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_siu.h"


/************************* INTERRUPT HANDLERS ************************/

void INTC_ENCODER (void)
{
    SIU.ISR.R = 0x000000FF;

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

