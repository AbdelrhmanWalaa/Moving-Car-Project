/*
 * gli_program.c
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Global Interrupt (GLI) functions' implementation.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "gli_private.h"
#include "gli_interface.h"

/*******************************************************************************************************************************************************************/
/**
 * @brief The function enables the global interrupt enable bit.
 */
vd GLI_enableGIE ( void )
{
	SET_BIT( GLI_U8_SREG_REG, GLI_U8_I_BIT );
}

/*******************************************************************************************************************************************************************/
/**
 * @brief The function disables the global interrupt enable bit.
 */
vd GLI_disableGIE( void )
{
	CLR_BIT( GLI_U8_SREG_REG, GLI_U8_I_BIT );
}

/*******************************************************************************************************************************************************************/