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
 * file                   : i2c_util.c
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
 * Brief Description      : This File contains I2C start function.
 *
 ******************************************************************************** 
 *
 * Detail Description     : This function generates I2C start condition by making
 *                          Master Transmit mode. It also configures data register
 *                          with calling address.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "i2c_init.h"
#include "rappid_ref.h"




void i2c_0_start_fnc(void)
{
    while (I2C_0.IBSR.B.IBB == 1 ) {;} //wait in loop for IBB flag to clear
    I2C_0.IBCR.R = 0x38;//Master,Transmit, Noack selected
    //Generate start condition
    I2C_0.IBDR.R = I2C_0.IBAD.R;// send the calling address to the data register
}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

