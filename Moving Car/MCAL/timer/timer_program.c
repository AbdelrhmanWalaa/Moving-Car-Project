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

u8 u8_g_tmr0InitialVal = 0;
u8 u8_g_tmr2InitialVal = 0;
u16 u16_g_overflowNumbers = 0;
u16 u16_g_overflowTicks = 0;

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
		CLR_BIT(TMR_U8_TCCR0_REG, WGM00);
		CLR_BIT(TMR_U8_TCCR0_REG, WGM01);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for timer0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TOIE0);
		break;
	case DISABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR0_REG, WGM00);
		CLR_BIT(TMR_U8_TCCR0_REG, WGM01);
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
			TMR_U8_TCNT0_REG = (u8)(MAX_COUNTS - ((d64_a_delay / TICK_TIME) / u16_g_overflowNumbers));
			u8_g_tmr0InitialVal = TMR_U8_TCNT0_REG;
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
		CLR_BIT(TMR_U8_TCCR0_REG, CS01);
		CLR_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS00);
		break;
	case 8:
		CLR_BIT(TMR_U8_TCCR0_REG, CS00);
		CLR_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS01);
		break;
	case 64:
		CLR_BIT(TMR_U8_TCCR0_REG, CS02);
		SET_BIT(TMR_U8_TCCR0_REG, CS01);
		SET_BIT(TMR_U8_TCCR0_REG, CS00);
		break;
	case 256:
		CLR_BIT(TMR_U8_TCCR0_REG, CS01);
		CLR_BIT(TMR_U8_TCCR0_REG, CS00);
		SET_BIT(TMR_U8_TCCR0_REG, CS02);
		break;
	case 1024:
		CLR_BIT(TMR_U8_TCCR0_REG, CS01);
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
	CLR_BIT(TMR_U8_TCCR0_REG, CS00);
	CLR_BIT(TMR_U8_TCCR0_REG, CS01);
	CLR_BIT(TMR_U8_TCCR0_REG, CS02);
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
		CLR_BIT(TMR_U8_TCCR0_REG, WGM00);
		SET_BIT(TMR_U8_TCCR0_REG, WGM01);
		/*must be set for the non_PWM mode;*/
		SET_BIT(TMR_U8_TCCR0_REG, FOC0);
	}
	return TIMER_OK;

}

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
		CLR_BIT(TMR_U8_TCCR2_REG, WGM20);
		CLR_BIT(TMR_U8_TCCR2_REG, WGM21);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for timer0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TOIE2);
		break;
	case DISABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR2_REG, WGM20);
		CLR_BIT(TMR_U8_TCCR2_REG, WGM21);
		break;
	default:
		return TIMER_ERROR;
		break;
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
			u16_g_overflowNumbers = 1;
		}
		else if (d64_a_delay == MAX_DELAY)
		{
			TMR_U8_TCNT2_REG = 0x00;
			u16_g_overflowNumbers = 1;
		}
		else
		{
			u16_g_overflowNumbers = ceil(d64_a_delay / MAX_DELAY);
			TMR_U8_TCNT2_REG = (u8)(MAX_COUNTS - ((d64_a_delay / TICK_TIME) / u16_g_overflowNumbers));
			u8_g_tmr2InitialVal = TMR_U8_TCNT2_REG;
		}
		u16_g_overflowTicks = 0;
		TMR_tmr2Start(1024);
		/*Polling the overflowNumbers and the overflow flag bit*/
		while (u16_g_overflowNumbers > u16_g_overflowTicks)
		{
			while ((TMR_U8_TIFR_REG & (1 << TOV2)) == 0);
			TMR_U8_TIFR_REG |= (1 << TOV2);
			u16_g_overflowTicks++;
		}
		/*stop the timer*/
		TMR_tmr2Stop();
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
		CLR_BIT(TMR_U8_TCCR2_REG, CS21);
		CLR_BIT(TMR_U8_TCCR2_REG, CS22);
		SET_BIT(TMR_U8_TCCR2_REG, CS20);
		break;
	case 8:
		CLR_BIT(TMR_U8_TCCR2_REG, CS20);
		CLR_BIT(TMR_U8_TCCR2_REG, CS22);
		SET_BIT(TMR_U8_TCCR2_REG, CS21);
		break;
	case 32:
		CLR_BIT(TMR_U8_TCCR2_REG, CS22);
		SET_BIT(TMR_U8_TCCR2_REG, CS21);
		SET_BIT(TMR_U8_TCCR2_REG, CS20);
	case 64:
		SET_BIT(TMR_U8_TCCR2_REG, CS22);
		CLR_BIT(TMR_U8_TCCR2_REG, CS21);
		CLR_BIT(TMR_U8_TCCR2_REG, CS20);
	case 128:
		CLR_BIT(TMR_U8_TCCR2_REG, CS22);
		CLR_BIT(TMR_U8_TCCR2_REG, CS21);
		SET_BIT(TMR_U8_TCCR2_REG, CS20);
		break;
	case 256:
		SET_BIT(TMR_U8_TCCR2_REG, CS21);
		CLR_BIT(TMR_U8_TCCR2_REG, CS20);
		SET_BIT(TMR_U8_TCCR2_REG, CS22);
		break;
	case 1024:
		SET_BIT(TMR_U8_TCCR2_REG, CS21);
		SET_BIT(TMR_U8_TCCR2_REG, CS22);
		SET_BIT(TMR_U8_TCCR2_REG, CS20);
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
 * This function Clear the prescaler for timer_2.
 * @param[in] void.
 *
 * @return void
 */


void TMR_tmr2Stop(void)
{
	/* Stop the timer by clearing the prescaler*/
	CLR_BIT(TMR_U8_TCCR2_REG, CS20);
	CLR_BIT(TMR_U8_TCCR2_REG, CS21);
	CLR_BIT(TMR_U8_TCCR2_REG, CS22);
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
EN_TMR_ERROR_T TMR_tmr2CleareCompMatInit(u8 u8_a_outCompValue)
{
	if (u8_a_outCompValue > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		/*load the out compare value with the OCR0*/
		TMR_U8_OCR2_REG = u8_a_outCompValue;
		/*initial value for the timer/counter register.*/
		TMR_U8_TCNT2_REG = 0x00;
		/* select the CTC mode for the timer0.*/
		CLR_BIT(TMR_U8_TCCR2_REG, WGM20);
		SET_BIT(TMR_U8_TCCR2_REG, WGM21);
		/*must be set for the non_PWM mode;*/
		SET_BIT(TMR_U8_TCCR2_REG, FOC2);
	}
	return TIMER_OK;

}

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
EN_TMR_ERROR_T TMR_tmr1NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable)
{
	switch (TMR_a_interrputEnable)
	{
	case ENABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR1A_REG, WGM10);
		CLR_BIT(TMR_U8_TCCR1A_REG, WGM11);
		CLR_BIT(TMR_U8_TCCR1B_REG, WGM12);
		CLR_BIT(TMR_U8_TCCR1B_REG, WGM13);
		/*must be set for the non_PWM mode*/
		SET_BIT(TMR_U8_TCCR1A_REG, FOC1A);
		SET_BIT(TMR_U8_TCCR1A_REG, FOC1B);
		/*Enable the global interrupt enable bit.*/
		SET_BIT(SREG, GLOBAL_INTERRUPT_ENABLE_BIT);
		/* Enable the interrupt for timer0 overflow.*/
		SET_BIT(TMR_U8_TIMSK_REG, TOIE1);
		break;
	case DISABLED:
		/* select the normal mode for the timer, timer is not start yet.*/
		CLR_BIT(TMR_U8_TCCR1A_REG, WGM10);
		CLR_BIT(TMR_U8_TCCR1A_REG, WGM11);
		CLR_BIT(TMR_U8_TCCR1B_REG, WGM12);
		CLR_BIT(TMR_U8_TCCR1B_REG, WGM13);
		/*must be set for the non_PWM mode*/
		SET_BIT(TMR_U8_TCCR1A_REG, FOC1A);
		SET_BIT(TMR_U8_TCCR1A_REG, FOC1B);
		break;
	default:
		return TIMER_ERROR;
		break;
	}
	return TIMER_OK;
}
/**********************************************************************************************************************/
/**
 * @brief timer_1 compare match mode.
 *
 * This function initializes the compare match mode for timer_1.
 * @param[in] void.
 *
 * @return void
 */
void TMR_tmr1CleareCompMatInit(void)
{
	/*Enable CTCA and CTCB interrupt  OCIE1A = 4, OCIE1B = 3*/
	SET_BIT(TMR_U8_TIMSK_REG, OCIE1A);
	SET_BIT(TMR_U8_TIMSK_REG, OCIE1B);
	/*CTC mode WGM12 = 3*/
	SET_BIT(TMR_U8_TCCR1B_REG, WGM12);
}
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
EN_TMR_ERROR_T TMR_tmr1Start(u16 u16_a_prescaler)
{
	/*select the required prescaler value*/
	switch (u16_a_prescaler)
	{
	case 1:
		CLR_BIT(TMR_U8_TCCR1B_REG, CS11);
		CLR_BIT(TMR_U8_TCCR1B_REG, CS12);
		SET_BIT(TMR_U8_TCCR1B_REG, CS10);
		break;
	case 8:
		CLR_BIT(TMR_U8_TCCR1B_REG, CS10);
		CLR_BIT(TMR_U8_TCCR1B_REG, CS12);
		SET_BIT(TMR_U8_TCCR1B_REG, CS11);
		break;
	case 64:
		CLR_BIT(TMR_U8_TCCR1B_REG, CS12);
		SET_BIT(TMR_U8_TCCR1B_REG, CS11);
		SET_BIT(TMR_U8_TCCR1B_REG, CS10);
		break;
	case 256:
		CLR_BIT(TMR_U8_TCCR1B_REG, CS11);
		CLR_BIT(TMR_U8_TCCR1B_REG, CS10);
		SET_BIT(TMR_U8_TCCR1B_REG, CS12);
		break;
	case 1024:
		CLR_BIT(TMR_U8_TCCR1B_REG, CS11);
		SET_BIT(TMR_U8_TCCR1B_REG, CS12);
		SET_BIT(TMR_U8_TCCR1B_REG, CS10);
		break;
	default:
		return TIMER_ERROR;
		break;
	}
	return TIMER_OK;
}
/**************************************************************************************************/
void TMR_tmr1Stop(void)
{
	/* Stop the timer by clearing the prescaler*/
	CLR_BIT(TMR_U8_TCCR1B_REG, CS10);
	CLR_BIT(TMR_U8_TCCR1B_REG, CS11);
	CLR_BIT(TMR_U8_TCCR1B_REG, CS12);
}

/******************** Inside the DC Motor Module***************************************/

EN_TMR_ERROR_T TMR_tmr1CreatePWM(u8 u8_a_dutyCycle)
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
		/*macros*/
		f64 val = (u8_a_dutyCycle / 100.0);
		u16 max = (1 << 16) - 1;
		f64 res = val * max;
		TMR_U16_OCR1A_REG = res;
		TMR_U16_OCR1B_REG = max;
	}
	return TIMER_OK;
}
/*******************************************************************************************************************************************************************/


/*******************************************************************************************************************************************************************/
/*
 Name: TMR_u8OVFSetCallBack
 Input: u8 TimerId and Pointer to function OVFInterruptAction taking void and returning void
 Output: u8 Error or No Error
 Description: Function to receive an address of a function ( in APP Layer ) to be called back in ISR function of the passed Timer ( TimerId ),
			  the address is passed through a pointer to function ( OVFInterruptAction ), and then pass this address to ISR function.
*/

/*
u8 TMR_u8OVFSetCallBack	     ( u8 Cpy_u8TimerId, void ( *Cpy_pfOVFInterruptAction ) ( void ) )
{
	// Define local variable to set the error state = OK
	u8 Loc_u8ErrorState = STD_OK;

	// Check 1: TimertId is in the valid range, and Pointer to Function is not equal to NULL
	if ( ( Cpy_u8TimerId <= TMR_U8_TMR2 ) && ( Cpy_pfOVFInterruptAction != NULL ) )
	{
		// Store the passed address of function ( in APP Layer ) through pointer to function ( OVFInterruptAction ) into Global Array of Pointers to Functions ( OVFInterruptsAction ) in the passed index ( TimerId ).
		Glb_ApfOVFInterruptsAction[Cpy_u8TimerId] = Cpy_pfOVFInterruptAction;
	}
	// Check 2: TimertId is not in the valid range, or Pointer to Function is equal to NULL
	else
	{
		// Update error state = NOK, wrong TimertId or Pointer to Function is NULL!
		Loc_u8ErrorState = STD_NOK;
	}

	return Loc_u8ErrorState;
}
*/
/*******************************************************************************************************************************************************************/
/*******************************************************************************************************************************************************************/
/*******************************************************************************************************************************************************************/

