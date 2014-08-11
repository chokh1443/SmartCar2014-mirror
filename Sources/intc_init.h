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
 * file                   : intc_init.h
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
 * Brief Description      : This file contains the function prototype for intc source file.
 *
 *
 *######################################################################
*/

#ifndef  _INTC_INIT_H
#define  _INTC_INIT_H
/********************  Dependent Include files here **********************/

#include "jdp.h"



/**********************  Function Prototype here *************************/

extern void intc_init_fnc (void);
extern void en_int_fnc (vuint32_t priority);


#endif  /*_INTC_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

