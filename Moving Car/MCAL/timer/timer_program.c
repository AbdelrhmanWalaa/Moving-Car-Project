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
#include <math.h>

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

u16 u16_g_overflowNumbers = 0;
u16 u16_g_overflowTicks = 0;

u16 u16_g_overflow2Ticks = 0;
u16 u16_g_overflow2Numbers = 0;

void (*void_g_pfOvfInterruptAction)(void) = NULL;

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
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT);
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(TMR_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for timer0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TMR_U8_TOIE0_BIT);
		break;
	case DISABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT);
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT);
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
		f64 d64_a_delay = (u16_a_interval / SECOND_OPERATOR);
		/*Compare the desired delay by the maximum delay for each overflow*/
		if (d64_a_delay < MAX_DELAY)
		{
			/*just on overflow is required*/
			TMR_U8_TCNT0_REG = (u8)((MAX_DELAY - d64_a_delay) / TICK_TIME);
			u16_g_overflowNumbers = 1;
		}
		else if (d64_a_delay == MAX_DELAY)
		{
			TMR_U8_TCNT0_REG = 0x00;
			u16_g_overflowNumbers = 1;
		}
		else
		{
			u16_g_overflowNumbers = ceil(d64_a_delay / MAX_DELAY);
//            u8_g_tmr0InitialVal = (u8)(MAX_COUNTS - ((d64_a_delay / TICK_TIME) / u16_g_overflowNumbers));
            TMR_U8_TCNT0_REG = (u8)((MAX_COUNTS) - ((d64_a_delay - (MAX_DELAY * (u16_g_overflowNumbers - 1.0))) / TICK_TIME)); // in decimal  (0 - 255)
		}
		u16_g_overflowTicks = 0;
		TMR_tmr0Start(1024);
		/*Polling the overflowNumbers and the overflow flag bit*/
		while (u16_g_overflowNumbers > u16_g_overflowTicks)
		{
			while ((TMR_U8_TIFR_REG & (1 << 0)) == 0);
			TMR_U8_TIFR_REG |= (1 << 0);
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
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT);
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT);
		break;
	case 8:
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT);
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT);
		break;
	case 64:
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT);
		break;
	case 256:
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT);
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT);
		break;
	case 1024:
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT);
		break;
	default:
		return TIMER_ERROR;
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
	CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS00_BIT);
	CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS01_BIT);
	CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_CS02_BIT);
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
/*EN_TMR_ERROR_T TMR_tmr0CleareCompMatInit(u8 u8_a_outCompValue)
{
	if (u8_a_outCompValue > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		*//*load the out compare value with the OCR0*//*
		TMR_U8_OCR0_REG = u8_a_outCompValue;
		*//*initial value for the timer/counter register.*//*
		TMR_U8_TCNT0_REG = 0x00;
		*//* select the CTC mode for the timer0.*//*
		CLR_BIT(TMR_U8_TCCR0_REG, TMR_U8_WGM00_BIT);
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_WGM01_BIT);
		*//*must be set for the non_PWM mode;*//*
		SET_BIT(TMR_U8_TCCR0_REG, TMR_U8_FOC0_BIT);
	}
	return TIMER_OK;

}*/

/**************************************************************************************************/

/**
 * @brief Initializes timer2 at normal mode
 *
 * This function initializes/selects the timer_2 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TMR_INTERRPUT_T TMR_a_interrputEnable value to set the interrupt bit for timer_2 in the TIMSK reg.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr2NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable)
{
	switch (TMR_a_interrputEnable)
	{
	case ENABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM20_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM21_BIT);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(TMR_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for timer0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TMR_U8_TOIE2_BIT);
		break;
	case DISABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM20_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM21_BIT);
		break;
	default:
		return TIMER_ERROR;
	}
	return TIMER_OK;
}

/*************************************************************************************************/

/**
 * @brief Creates a delay using timer_2 in overflow mode
 *
 * This function Creates the desired delay on timer_2 normal mode.
 * @param[in] u16 u16_a_interval value to set the desired delay.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */


EN_TMR_ERROR_T TMR_tmr2Delay(u16 u16_a_interval)
{
	if (u16_a_interval > MAX_TIMER_DELAY)
		return TIMER_ERROR;
	else
	{
		/* Clear the TCCR Register*/
		TMR_U8_TCCR2_REG = 0x00;
		/*Get the time in second*/
		f64 d64_a_delay = (u16_a_interval / SECOND_OPERATOR);
		/*Compare the desired delay by the maximum delay for each overflow*/
		if (d64_a_delay < MAX_DELAY)
		{
			/*just on overflow is required*/
			TMR_U8_TCNT2_REG = (u8)((MAX_DELAY - d64_a_delay) / TICK_TIME);
			u16_g_overflow2Numbers = 1;
		}
		else if (d64_a_delay == MAX_DELAY)
		{
			TMR_U8_TCNT2_REG = 0x00;
			u16_g_overflow2Numbers = 1;
		}
		else
		{
			u16_g_overflowNumbers = ceil(d64_a_delay / MAX_DELAY);
            TMR_U8_TCNT2_REG = (u8)((MAX_COUNTS) - ((d64_a_delay - (MAX_DELAY * (u16_g_overflowNumbers - 1.0))) / TICK_TIME)); // in decimal  (0 - 255)
		}
		u16_g_overflow2Ticks = 0;
		TMR_tmr2Start(1024);
	}
	return TIMER_OK;
}

/***************************************************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_2.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */

EN_TMR_ERROR_T TMR_tmr2Start(u16 u16_a_prescaler)
{
	switch (u16_a_prescaler)
	{
	case 1:
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		break;
	case 8:
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		break;
	case 32:
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
	case 64:
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
	case 128:
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		break;
	case 256:
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		break;
	case 1024:
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
		break;
	default:
		return TIMER_ERROR;
	}
	return TIMER_OK;

}
/**************************************************************************************************/
/**
 * @brief Stop the timer by setting the prescaler to be 000--> timer is stopped.
 *
 * This function Clear the prescaler for timer_2.
 * @param[in] void.
 *
 * @return void
 */


void TMR_tmr2Stop(void)
{
	/* Stop the timer by clearing the prescaler*/
	CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS20_BIT);
	CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS21_BIT);
	CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_CS22_BIT);
}
/**************************************************************************************************/
/**
 * @brief timer compare match mode.
 *
 * This function set the compare value for timer_2.
 * @param[in] u8 u8_a_outCompValue value at which the matching will occur.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TMR_ERROR_T TMR_tmr2CleareCompMatInit(u8 u8_a_outCompValue)
{
	if (u8_a_outCompValue > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		*//*load the out compare value with the OCR0*//*
		TMR_U8_OCR2_REG = u8_a_outCompValue;
		*//*initial value for the timer/counter register.*//*
		TMR_U8_TCNT2_REG = 0x00;
		*//* select the CTC mode for the timer0.*//*
		CLR_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM20_BIT);
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_WGM21_BIT);
		*//*must be set for the non_PWM mode;*//*
		SET_BIT(TMR_U8_TCCR2_REG, TMR_U8_FOC2_BIT);
	}
	return TIMER_OK;

}*/

/**************************************************************************************************/

/**
 * @brief Initializes timer1 at normal mode
 *
 * This function initializes/selects the timer_1 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TMR_INTERRPUT_T TMR_a_interrputEnable value to set the interrupt bit for timer_1 in the TIMSK reg.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TMR_ERROR_T TMR_tmr1NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable)
{
	switch (TMR_a_interrputEnable)
	{
	case ENABLED:
		*//* select the normal mode for the timer, timer is not start yet.*//*
		CLR_BIT(TMR_U8_TCCR1A_REG, TMR_U8_WGM10_BIT);
		CLR_BIT(TMR_U8_TCCR1A_REG, TMR_U8_WGM11_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_WGM12_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_WGM13_BIT);
		*//*must be set for the non_PWM mode*//*
		SET_BIT(TMR_U8_TCCR1A_REG, TMR_U8_FOC1A_BIT);
		SET_BIT(TMR_U8_TCCR1A_REG, TMR_U8_FOC1B_BIT);
		*//*Enable the global interrupt enable bit.*//*
		SET_BIT(TMR_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
		*//* Enable the interrupt for timer0 overflow.*//*
		SET_BIT(TMR_U8_TIMSK_REG, TMR_U8_TOIE1_BIT);
		break;
	case DISABLED:
		*//* select the normal mode for the timer, timer is not start yet.*//*
		CLR_BIT(TMR_U8_TCCR1A_REG, TMR_U8_WGM10_BIT);
		CLR_BIT(TMR_U8_TCCR1A_REG, TMR_U8_WGM11_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_WGM12_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_WGM13_BIT);
		*//*must be set for the non_PWM mode*//*
		SET_BIT(TMR_U8_TCCR1A_REG, TMR_U8_FOC1A_BIT);
		SET_BIT(TMR_U8_TCCR1A_REG, TMR_U8_FOC1B_BIT);
		break;
	default:
		return TIMER_ERROR;
	}
	return TIMER_OK;
}*/

/**********************************************************************************************************************/
/**
 * @brief timer_1 compare match mode.
 *
 * This function initializes the compare match mode for timer_1.
 * @param[in] void.
 *
 * @return void
 */
/*void TMR_tmr1CleareCompMatInit(void)
{
	*//*Enable CTCA and CTCB interrupt  OCIE1A = 4, OCIE1B = 3*//*
	SET_BIT(TMR_U8_TIMSK_REG, TMR_U8_OCIE1A_BIT);
	SET_BIT(TMR_U8_TIMSK_REG, TMR_U8_OCIE1B_BIT);
	*//*CTC mode WGM12 = 3*//*
	SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_WGM12_BIT);
}*/
/*********************************************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_1.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TMR_ERROR_T TMR_tmr1Start(u16 u16_a_prescaler)
{
	*//*select the required prescaler value*//*
	switch (u16_a_prescaler)
	{
	case 1:
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS11_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS12_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS10_BIT);
		break;
	case 8:
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS10_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS12_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS11_BIT);
		break;
	case 64:
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS12_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS11_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS10_BIT);
		break;
	case 256:
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS11_BIT);
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS10_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS12_BIT);
		break;
	case 1024:
		CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS11_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS12_BIT);
		SET_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS10_BIT);
		break;
	default:
		return TIMER_ERROR;
	}
	return TIMER_OK;
}*/
/**************************************************************************************************/
/*
void TMR_tmr1Stop(void)
{
 Stop the timer by clearing the prescaler

	CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS10_BIT);
	CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS11_BIT);
	CLR_BIT(TMR_U8_TCCR1B_REG, TMR_U8_CS12_BIT);
}
*/

/******************** Inside the DC Motor Module***************************************/

/*EN_TMR_ERROR_T TMR_tmr1CreatePWM(u8 u8_a_dutyCycle)
{
	if (u8_a_dutyCycle > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		TMR_tmr1CleareCompMatchInit();
		TMR_tmr1Start(NO_PRESCALER);
		if (u8_a_dutyCycle > 100)
		{
			u8_a_dutyCycle = 100;
		}
		*//*macros*//*
		f64 val = (u8_a_dutyCycle / 100.0);
		u16 max = (1 << 16) - 1;
		f64 res = val * max;
		TMR_U16_OCR1A_REG = res;
		TMR_U16_OCR1B_REG = max;
	}
	return TIMER_OK;
}*/

/*******************************************************************************************************************************************************************/


/*******************************************************************************************************************************************************************/
/*
 Name: void_g_pfOvfInterruptAction
 Input: Pointer to function OVFInterruptAction taking void and returning void
 Output: EN_TMR_ERROR_T Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Timer ( TimerId ),
			  the address is passed through a pointer to function ( OVFInterruptAction ), and then pass this address to ISR function.
*/


EN_TMR_ERROR_T TMR_ovfSetCallback(void (*void_a_pfOvfInterruptAction) (void))
{
	// Check if the Pointer to Function is not equal to NULL 
	if (void_a_pfOvfInterruptAction != NULL)
	{
		// Store the passed address of function ( in APP Layer ) through pointer to function ( OVFInterruptAction ) into Global Array of Pointers to Functions ( OVFInterruptsAction ) in the passed index ( TimerId ). 
		void_g_pfOvfInterruptAction = void_a_pfOvfInterruptAction;
		return TIMER_OK;
	}
	else
	{
		return TIMER_ERROR;
	}
}

ISR(TMR_ovfVect)
{
	u16_g_overflow2Ticks++;
	if (u16_g_overflow2Numbers > u16_g_overflow2Ticks)
	{
		u16_g_overflow2Ticks = 0;
		TMR_tmr2Stop();
		if (void_g_pfOvfInterruptAction != NULL)
			void_g_pfOvfInterruptAction();
	}

}
