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
 * file                   : linflex_var.c
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
 * Brief Description      : This File Contains macro and externally defined variables
 *                          for Linflex register
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File Contains transmit and receive buffer initialization.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "typedefs.h"



vuint8_t Uart0_TxBuffer[1]= {0U };
        /* Transmit Queue Uart0 Variable declaration   */
vuint8_t Uart0_RxBuffer[1]= {0U };
        /* Receive Queue Uart0 Variable declaration   */
vuint8_t Uart1_TxBuffer[1]= {0U };
        /* Transmit Queue Uart1 Variable declaration   */
vuint8_t Uart1_RxBuffer[1]= {0U };
        /* Receive Queue Uart1 Variable declaration   */
vuint32_t Linflex_0_TXBuffer[1]= {0U };
        /* Transmit Queue LINFLEX_0 Variable declaration   */
vuint32_t Linflex_0_RXBuffer[1]= {0U };
        /* Receive Queue LINFLEX_0 Variable declaration   */
vuint32_t Linflex_1_TXBuffer[1]= {0U };
        /* Transmit Queue LINFLEX_1 Variable declaration   */
vuint32_t Linflex_1_RXBuffer[1]= {0U };
        /* Receive Queue LINFLEX_1 Variable declaration   */

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

