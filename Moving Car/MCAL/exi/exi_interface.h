/*
 * exi_interface.h
 *
 *     Created on: Apr 25, 2021
 *         Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 *    Description: This file contains all External Interrupt (EXI) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
#ifndef EXI_INTERFACE_H_
#define EXI_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* EXI Includes */

 /* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/*******************************************************************************************************************************************************************/
/* EXI Macros */

/* The 3 External Interrupts counted from 0 to 2 */
#define EXI_U8_INT0						0
#define EXI_U8_INT1 					1
#define EXI_U8_INT2 					2

/* Interrupts Sense Control */
#define EXI_U8_SENSE_LOW_LEVEL			0
#define EXI_U8_SENSE_LOGICAL_CHANGE		1
#define EXI_U8_SENSE_FALLING_EDGE		2
#define EXI_U8_SENSE_RISING_EDGE		3

/*******************************************************************************************************************************************************************/
/* EXI Functions' Prototypes */

u8 EXI_u8EnablePIE     ( u8 Cpy_u8InterruptId, u8 Cpy_u8SenseControl );
u8 EXI_u8DisablePIE    ( u8 Cpy_u8InterruptId );

u8 EXI_u8INTSetCallBack( u8 Cpy_u8InterruptId, void ( *Cpy_pfINTInterruptAction ) ( void ) );

/*******************************************************************************************************************************************************************/

#endif /* EXTI_INTERFACE_H_ */