*
* TMR_Program.c
*
* Created on : Apr 11, 2023
* Author : Mahmoud Mowafey - https ://github.com/Mahmoud-Mowafy
	*Description : This file contains all Timers(TMR) functions' implementation, and ISR functions' prototypes and implementation.
	* MCU Datasheet : AVR ATmega32
	* https ://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
	*/

	/* MCAL */
#include "timer_private.h"
#include "timer_config.h"
#include "timer_interface.h"

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */


/*******************************************************************************************************************************************************************/
/* ***************************************************************************************************************** */


/**
 * @brief Initializes timer0 at normal mode
 *
 * This function initializes/selects the timer_0 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TMR_INTERRPUT_T TMR_a_interrputEnable value to set the interrupt bit for timer_0 in the TIMSK reg.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
	EN_TMR_ERROR_T TMR_tmr0NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable)
{
	switch (TMR_a_interrputEnable)
	{
	case ENABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLEARE_BIT(TMR_U8_TCCR0_REG, WGM00);
		CLEARE_BIT(TMR_U8_TCCR0_REG, WGM01);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for timer0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TOIE0);
		break;
	case DISABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLEARE_BIT(TMR_U8_TCCR0_REG, WGM00);
		CLEARE_BIT(TMR_U8_TCCR0_REG, WGM01);
		break;
	default:
		return TIMER_ERROR;
		break;
	}
	return TIMER_OK;
}