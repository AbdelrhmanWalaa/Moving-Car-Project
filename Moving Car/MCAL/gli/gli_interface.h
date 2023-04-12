/*
 * gli_interface.h
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Global Interrupt (GLI) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef GLI_INTERFACE_H_
#define GLI_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* GLI Includes */

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/*******************************************************************************************************************************************************************/
/* GLI Functions' Prototypes */

vd GLI_enableGIE ( void );
vd GLI_disableGIE( void );

/*******************************************************************************************************************************************************************/

#endif /* GLI_INTERFACE_H_ */