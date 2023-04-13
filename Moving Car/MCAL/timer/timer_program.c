/*
 * TMR_Program.c
 *
 *     Created on: Apr 11, 2023
 *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
 *    Description: This file contains all Timers (TMR) functions' implementation, and ISR functions' prototypes and implementation.
 *		MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
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


/**
 * @brief Creates a delay using timer_0 in overflow mode
 *
 * This function Creates the desired delay on timer_0 normal mode.
 * @param[in] u16 u16_a_interval value to set the desired delay.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */


EN_TMR_ERROR_T TMR_tmr0Delay(u16 u16_a_interval)
{
	if (u16_a_interval > MAX_TIMER_DELAY)
		return TIMER_ERROR;
	else
	{
		/* Clear the TCCR Register*/
		TMR_U8_TCCR0_REG = 0x00;
		/*Get the time in second*/
		dbl d32_a_delay = (u16_a_interval / SECOND_OPERATOR);
		/*Compare the desired delay by the maximum delay for each overflow*/
		if (d32_a_delay < MAX_DELAY)
		{
			/*just on overflow is required*/
			TMR_U8_TCNT0_REG = (u8)((MAX_DELAY - d32_a_delay) / TICK_TIME);
			u16_g_overflowNumbers = 1;
		}
		else if (d32_a_delay == MAX_DELAY)
		{
			TMR_U8_TCNT0_REG = 0x00;
			u16_g_overflowNumbers = 1;
		}
		else
		{
			u16_g_overflowNumbers = ceil(d32_a_delay / MAX_DELAY);
			TMR_U8_TCNT0_REG = (u8)(MAX_COUNTS - ((d32_a_delay / TICK_TIME) / u16_g_overflowNumbers));
			u8_g_tmr0InitialVal = TMR_U8_TCNT0_REG;
		}
		u16_g_overflowTicks = 0;
		TMR_tmr0Start(1024);
		/*Polling the overflowNumbers and the overflow flag bit*/
		while (u16_g_overflowNumbers > u16_g_overflowTicks)
		{
			while ((TMR_U8_TIFR_REG & (1 << 0)) == 0);
			TMR_U8_TIFR_REG |= (1 << 0); +
				u16_g_overflowTicks++;
		}
		/*stop the timer*/
		TMR_tmr0Stop();
	}
	return TIMER_OK;
}

/***************************************************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_0.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */

EN_TMR_ERROR_T TMR_tmr0Start(u16 u16_a_prescaler)
{
	switch (u16_a_prescaler)
	{
	case 1:
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS01);
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS00);
		break;
	case 8:
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS00);
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS01);
		break;
	case 64:
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS01);
		SET_BIT(TMR_U8_TCCR0_REG, CS00);
		break;
	case 256:
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS01);
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS00);
		SET_BIT(TMR_U8_TCCR0_REG, CS02);
		break;
	case 1024:
		CLEARE_BIT(TMR_U8_TCCR0_REG, CS01);
		SET_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS00);
		break;
	default:
		return TIMER_ERROR;
		break;
	}
	return TIMER_OK;

}
/**************************************************************************************************/
/**
 * @brief Stop the timer by setting the prescaler to be 000--> timer is stopped.
 *
 * This function Clear the prescaler for timer_0.
 * @param[in] void.
 *
 * @return void
 */


void TMR_tmr0Stop(void)
{
	/* Stop the timer by clearing the prescaler*/
	CLEARE_BIT(TMR_U8_TCCR0_REG, CS00);
	CLEARE_BIT(TMR_U8_TCCR0_REG, CS01);
	CLEARE_BIT(TMR_U8_TCCR0_REG, CS02);
}
/**************************************************************************************************/
/**
 * @brief timer compare match mode.
 *
 * This function set the compare value for timer_0.
 * @param[in] u8 u8_a_outCompValue value at which the matching will occur.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr0CleareCompMatInit(u8 u8_a_outCompValue)
{
	if (u8_a_outCompValue > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		/*load the out compare value with the OCR0*/
		TMR_U8_OCR0_REG = u8_a_outCompValue;
		/*initial value for the timer/counter register.*/
		TMR_U8_TCNT0_REG = 0x00;
		/* select the CTC mode for the timer0.*/
		CLEARE_BIT(TMR_U8_TCCR0_REG, WGM00);
		SET_BIT(TMR_U8_TCCR0_REG, WGM01);
		/*must be set for the non_PWM mode;*/
		SET_BIT(TMR_U8_TCCR0_REG, FOC0);
	}
	return TIMER_OK;

}