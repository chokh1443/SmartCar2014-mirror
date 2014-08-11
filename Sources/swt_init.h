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
 * file                   : swt_init.h
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
 * Brief Description      : File contains declarations for Watchdog initialization function
 *                          and Service Routine.
 *
 *
 *######################################################################
*/

#ifndef  _SWT_INIT_H
#define  _SWT_INIT_H
/********************  Dependent Include files here **********************/

#include "jdp.h"

/**********************  Function Prototype here *************************/

void swt_init_fnc (void);
void swt_srvc_seq_fnc (void);


#endif  /*_SWT_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

