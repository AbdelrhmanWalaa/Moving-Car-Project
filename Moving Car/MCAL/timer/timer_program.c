/*
 * TIMER_Program.c
 *
 *     Created on: Apr 11, 2023
 *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
 *    Description: This file contains all Timers (TIMER) functions' implementation, and ISR functions' prototypes and implementation.
 *		MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "timer_private.h"
#include "timer_config.h"
#include "timer_interface.h"
#include <math.h>

/* ***********************************************************************************************/
/* Declaration and Initialization */

u16 u16_g_overflowNumbers = 0;
u16 u16_g_overflowTicks = 0;

u16 u16_g_overflow2Ticks = 0;
u16 u16_g_overflow2Numbers = 0;

u8 * u8_g_timerShutdownFlag = NULL;

void (*void_g_pfOvfInterruptAction)(void) = NULL;

/* ***********************************************************************************************/


/**
 * @brief Initializes timer0 at normal mode
 *
 * This function initializes/selects the timer_0 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TIMER_INTERRPUT_T en_a_interrputEnable value to set the interrupt bit for timer_0 in the TIMSK reg.
 * @param[in] **u8_a_shutdownFlag double pointer, acts as a main switch for timer 0 operations.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TIMER_ERROR_T TIMER_timer0NormalModeInit(EN_TIMER_INTERRPUT_T en_a_interrputEnable, u8 ** u8_a_shutdownFlag) {
    u8_g_timerShutdownFlag = *u8_a_shutdownFlag;

    switch (en_a_interrputEnable) {
        case ENABLED:
            /* select the normal mode for the timer, timer is not start yet.*/
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_WGM00_BIT);
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_WGM01_BIT);
            /*Enable the global interrupt enable bit.*/
            SET_BIT(TIMER_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
            /* Enable the interrupt for timer0 overflow.*/
            SET_BIT(TIMER_U8_TIMSK_REG, TIMER_U8_TOIE0_BIT);
            break;
        case DISABLED:
            /* select the normal mode for the timer, timer is not start yet.*/
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_WGM00_BIT);
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_WGM01_BIT);
            break;
        default:
            return TIMER_ERROR;
    }
    return TIMER_OK;
}


/**
 * @brief Creates a delay using timer_0 in overflow mode
 *
 * This function Creates the desired delay on timer_0 normal mode.
 * @param[in] u16 u16_a_interval value to set the desired delay.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TIMER_ERROR_T TIMER_timer0Delay(u16 u16_a_interval) {
    if((u8_g_timerShutdownFlag != NULL && *u8_g_timerShutdownFlag == 1)) return TIMER_ERROR; // sudden break flag
    if ( ( u16_a_interval / SECOND_OPERATOR ) > ( MAX_TIMER_DELAY ) ) {
	    return TIMER_ERROR;
    }
    else {
        /* Clear the TCCR Register*/
        TIMER_U8_TCCR0_REG = 0x00;
        /*Get the time in second*/
        f64 d64_a_delay = (u16_a_interval / SECOND_OPERATOR);
        /*Compare the desired delay by the maximum delay for each overflow*/
        if (d64_a_delay < MAX_DELAY) {
            /*just on overflow is required*/
            TIMER_U8_TCNT0_REG = (u8) ((MAX_DELAY - d64_a_delay) / TICK_TIME);
            u16_g_overflowNumbers = 1;
        } else if (d64_a_delay == MAX_DELAY) {
            TIMER_U8_TCNT0_REG = 0x00;
            u16_g_overflowNumbers = 1;
        } else {
            u16_g_overflowNumbers = ceil(d64_a_delay / MAX_DELAY);
//            u8_g_timer0InitialVal = (u8)(MAX_COUNTS - ((d64_a_delay / TICK_TIME) / u16_g_overflowNumbers));
            TIMER_U8_TCNT0_REG = (u8) ((MAX_COUNTS) - ((d64_a_delay - (MAX_DELAY * (u16_g_overflowNumbers - 1.0))) /
                                                       TICK_TIME)); // in decimal  (0 - 255)
        }
        u16_g_overflowTicks = 0;
        TIMER_timer0Start(1024);
        /*Polling the overflowNumbers and the overflow flag bit*/
        while (u16_g_overflowNumbers > u16_g_overflowTicks && (u8_g_timerShutdownFlag == NULL || *u8_g_timerShutdownFlag == 0))
        {
            while ((TIMER_U8_TIFR_REG & (1 << 0)) == 0);
            TIMER_U8_TIFR_REG |= (1 << 0);
            u16_g_overflowTicks++;
        }
        /*stop the timer*/
        TIMER_timer0Stop();
    }
    return TIMER_OK;
}

/* *************************************************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_0.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TIMER_ERROR_T TIMER_timer0Start(u16 u16_a_prescaler) {
    switch (u16_a_prescaler) {
        case 1:
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS01_BIT);
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS02_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS00_BIT);
            break;
        case 8:
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS00_BIT);
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS02_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS01_BIT);
            break;
        case 64:
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS02_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS01_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS00_BIT);
            break;
        case 256:
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS01_BIT);
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS00_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS02_BIT);
            break;
        case 1024:
            CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS01_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS02_BIT);
            SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS00_BIT);
            break;
        default:
            return TIMER_ERROR;
    }
    return TIMER_OK;

}
/* ***********************************************************************************************/

/**
 * @brief Stop the timer by setting the prescaler to be 000--> timer is stopped.
 *
 * This function Clear the prescaler for timer_0.
 * @param[in] void.
 *
 * @return void
 */
void TIMER_timer0Stop(void) {
    /* Stop the timer by clearing the prescaler*/
    CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS00_BIT);
    CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS01_BIT);
    CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_CS02_BIT);
}
/* ***********************************************************************************************/
/**
 * @brief timer compare match mode.
 *
 * This function set the compare value for timer_0.
 * @param[in] u8 u8_a_outCompValue value at which the matching will occur.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TIMER_ERROR_T TIMER_timer0CleareCompMatInit(u8 u8_a_outCompValue)
{
	if (u8_a_outCompValue > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		*//*load the out compare value with the OCR0*//*
		TIMER_U8_OCR0_REG = u8_a_outCompValue;
		*//*initial value for the timer/counter register.*//*
		TIMER_U8_TCNT0_REG = 0x00;
		*//* select the CTC mode for the timer0.*//*
		CLR_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_WGM00_BIT);
		SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_WGM01_BIT);
		*//*must be set for the non_PWM mode;*//*
		SET_BIT(TIMER_U8_TCCR0_REG, TIMER_U8_FOC0_BIT);
	}
	return TIMER_OK;

}*/

/* ***********************************************************************************************/

/**
 * @brief Initializes timer2 at normal mode
 *
 * This function initializes/selects the timer_2 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TIMER_INTERRPUT_T en_a_interrputEnable value to set the interrupt bit for timer_2 in the TIMSK reg.
 * @param[in] **u8_a_shutdownFlag double pointer, acts as a main switch for timer 2 operations.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TIMER_ERROR_T TIMER_timer2NormalModeInit(EN_TIMER_INTERRPUT_T en_a_interrputEnable, u8 ** u8_a_shutdownFlag) {
    u8_g_timerShutdownFlag = *u8_a_shutdownFlag;

    switch (en_a_interrputEnable) {
        case ENABLED:
            /* select the normal mode for the timer, timer is not start yet.*/
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_WGM20_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_WGM21_BIT);
            /*Enable the global interrupt enable bit.*/
            SET_BIT(TIMER_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
            /* Enable the interrupt for timer0 overflow.*/
            SET_BIT(TIMER_U8_TIMSK_REG, TIMER_U8_TOIE2_BIT);
            break;
        case DISABLED:
            /* select the normal mode for the timer, timer is not start yet.*/
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_WGM20_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_WGM21_BIT);
            break;
        default:
            return TIMER_ERROR;
    }
    return TIMER_OK;
}

/* ***********************************************************************************************/

/**
 * @brief Creates a delay using timer_2 in overflow mode
 *
 * This function Creates the desired delay on timer_2 normal mode.
 * @param[in] u16 u16_a_interval value to set the desired delay.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TIMER_ERROR_T TIMER_timer2Delay(u16 u16_a_interval) {
    if ( ( u16_a_interval / SECOND_OPERATOR ) > ( MAX_TIMER_DELAY ) ) {
		 return TIMER_ERROR;
	}       
    else {
        /* Clear the TCCR Register*/
        TIMER_U8_TCCR2_REG = 0x00;
        /*Get the time in second*/
        f64 d64_a_delay = (u16_a_interval / SECOND_OPERATOR);
        /*Compare the desired delay by the maximum delay for each overflow*/
        if (d64_a_delay < MAX_DELAY) {
            /*just on overflow is required*/
            TIMER_U8_TCNT2_REG = (u8) ((MAX_DELAY - d64_a_delay) / TICK_TIME);
            u16_g_overflow2Numbers = 1;
        } else if (d64_a_delay == MAX_DELAY) {
            TIMER_U8_TCNT2_REG = 0x00;
            u16_g_overflow2Numbers = 1;
        } else {
            u16_g_overflow2Numbers = ceil(d64_a_delay / MAX_DELAY);
            TIMER_U8_TCNT2_REG = (u8) ((MAX_COUNTS) - ((d64_a_delay - (MAX_DELAY * (u16_g_overflow2Numbers - 1.0))) /
                                                       TICK_TIME)); // in decimal  (0 - 255)
        }
        u16_g_overflow2Ticks = 0;
        TIMER_timer2Start(1024);
    }
    return TIMER_OK;
}

/* *************************************************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_2.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TIMER_ERROR_T TIMER_timer2Start(u16 u16_a_prescaler) {
    switch (u16_a_prescaler) {
        case 1:
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
            break;
        case 8:
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            break;
        case 32:
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
        case 64:
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
        case 128:
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
            break;
        case 256:
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            break;
        case 1024:
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
            SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
            break;
        default:
            return TIMER_ERROR;
    }
    return TIMER_OK;

}
/* ************************************************************************************************/
/**
 * @brief Stop the timer by setting the prescaler to be 000--> timer is stopped.
 *
 * This function Clear the prescaler for timer_2.
 * @param[in] void.
 *
 * @return void
 */
void TIMER_timer2Stop(void) {
    /* Stop the timer by clearing the prescaler*/
    CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS20_BIT);
    CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS21_BIT);
    CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_CS22_BIT);
}
/* ************************************************************************************************/
/**
 * @brief timer compare match mode.
 *
 * This function set the compare value for timer_2.
 * @param[in] u8 u8_a_outCompValue value at which the matching will occur.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TIMER_ERROR_T TIMER_timer2CleareCompMatInit(u8 u8_a_outCompValue)
{
	if (u8_a_outCompValue > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		*//*load the out compare value with the OCR0*//*
		TIMER_U8_OCR2_REG = u8_a_outCompValue;
		*//*initial value for the timer/counter register.*//*
		TIMER_U8_TCNT2_REG = 0x00;
		*//* select the CTC mode for the timer0.*//*
		CLR_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_WGM20_BIT);
		SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_WGM21_BIT);
		*//*must be set for the non_PWM mode;*//*
		SET_BIT(TIMER_U8_TCCR2_REG, TIMER_U8_FOC2_BIT);
	}
	return TIMER_OK;

}*/

/* ************************************************************************************************/

/**
 * @brief Initializes timer1 at normal mode
 *
 * This function initializes/selects the timer_1 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TIMER_INTERRPUT_T en_a_interrputEnable value to set the interrupt bit for timer_1 in the TIMSK reg.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TIMER_ERROR_T TIMER_tmr1NormalModeInit(EN_TIMER_INTERRPUT_T en_a_interrputEnable)
{
	switch (en_a_interrputEnable)
	{
	case ENABLED:
		*//* select the normal mode for the timer, timer is not start yet.*//*
		CLR_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_WGM10_BIT);
		CLR_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_WGM11_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_WGM12_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_WGM13_BIT);
		*//*must be set for the non_PWM mode*//*
		SET_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_FOC1A_BIT);
		SET_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_FOC1B_BIT);
		*//*Enable the global interrupt enable bit.*//*
		SET_BIT(TIMER_U8_SREG_REG, GLOBAL_INTERRUPT_ENABLE_BIT);
		*//* Enable the interrupt for timer0 overflow.*//*
		SET_BIT(TIMER_U8_TIMSK_REG, TIMER_U8_TOIE1_BIT);
		break;
	case DISABLED:
		*//* select the normal mode for the timer, timer is not start yet.*//*
		CLR_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_WGM10_BIT);
		CLR_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_WGM11_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_WGM12_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_WGM13_BIT);
		*//*must be set for the non_PWM mode*//*
		SET_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_FOC1A_BIT);
		SET_BIT(TIMER_U8_TCCR1A_REG, TIMER_U8_FOC1B_BIT);
		break;
	default:
		return TIMER_ERROR;
	}
	return TIMER_OK;
}*/

/* ********************************************************************************************************************/
/**
 * @brief timer_1 compare match mode.
 *
 * This function initializes the compare match mode for timer_1.
 * @param[in] void.
 *
 * @return void
 */
/*void TIMER_tmr1CleareCompMatInit(void)
{
	*//*Enable CTCA and CTCB interrupt  OCIE1A = 4, OCIE1B = 3*//*
	SET_BIT(TIMER_U8_TIMSK_REG, TIMER_U8_OCIE1A_BIT);
	SET_BIT(TIMER_U8_TIMSK_REG, TIMER_U8_OCIE1B_BIT);
	*//*CTC mode WGM12 = 3*//*
	SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_WGM12_BIT);
}*/
/* *******************************************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_1.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TIMER_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
/*EN_TIMER_ERROR_T TIMER_tmr1Start(u16 u16_a_prescaler)
{
	*//*select the required prescaler value*//*
	switch (u16_a_prescaler)
	{
	case 1:
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS11_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS12_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS10_BIT);
		break;
	case 8:
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS10_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS12_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS11_BIT);
		break;
	case 64:
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS12_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS11_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS10_BIT);
		break;
	case 256:
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS11_BIT);
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS10_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS12_BIT);
		break;
	case 1024:
		CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS11_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS12_BIT);
		SET_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS10_BIT);
		break;
	default:
		return TIMER_ERROR;
	}
	return TIMER_OK;
}*/
/* ************************************************************************************************/
/*
void TIMER_tmr1Stop(void)
{
 Stop the timer by clearing the prescaler

	CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS10_BIT);
	CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS11_BIT);
	CLR_BIT(TIMER_U8_TCCR1B_REG, TIMER_U8_CS12_BIT);
}
*/

/* ****************** Inside the DC Motor Module ***************************************/

/*EN_TIMER_ERROR_T TIMER_tmr1CreatePWM(u8 u8_a_dutyCycle)
{
	if (u8_a_dutyCycle > MAX_COUNTS)
	{
		return TIMER_ERROR;
	}
	else
	{
		TIMER_tmr1CleareCompMatchInit();
		TIMER_tmr1Start(NO_PRESCALER);
		if (u8_a_dutyCycle > 100)
		{
			u8_a_dutyCycle = 100;
		}
		*//*macros*//*
		f64 val = (u8_a_dutyCycle / 100.0);
		u16 max = (1 << 16) - 1;
		f64 res = val * max;
		TIMER_U16_OCR1A_REG = res;
		TIMER_U16_OCR1B_REG = max;
	}
	return TIMER_OK;
}*/


/**
 * @brief Set callback function for timer overflow interrupt
 *
 * @param void_a_pfOvfInterruptAction Pointer to the function to be called on timer overflow interrupt
 * @return EN_TIMER_ERROR_T Returns TIMER_OK if callback function is set successfully, else returns TIMER_ERROR
 */
EN_TIMER_ERROR_T TIMER_ovfSetCallback(void (*void_a_pfOvfInterruptAction)(void)) {
    // Check if the Pointer to Function is not equal to NULL
    if (void_a_pfOvfInterruptAction != NULL) {
        // Store the passed address of function ( in APP Layer ) through pointer to function ( OVFInterruptAction ) into Global Array of Pointers to Functions ( OVFInterruptsAction ) in the passed index ( TimerId ).
        void_g_pfOvfInterruptAction = void_a_pfOvfInterruptAction;
        return TIMER_OK;
    } else {
        return TIMER_ERROR;
    }
}

/**
 * @brief Interrupt Service Routine for Timer Overflow.
 *        This function is executed when Timer2 Overflows.
 *        It increments u16_g_overflow2Ticks counter and checks whether
 *        u16_g_overflow2Numbers is greater than u16_g_overflow2Ticks.
 *        If true, it resets u16_g_overflow2Ticks and stops Timer2.
 *        It then checks whether void_g_pfOvfInterruptAction is not null.
 *        If true, it calls the function pointed to by void_g_pfOvfInterruptAction.
 *
 * @return void
 */
//__attribute__((optimize("O0")))
//ISR(TMR_ovfVect)

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	u16_g_overflow2Ticks++;
	if (u16_g_overflow2Ticks >= u16_g_overflow2Numbers || (u8_g_timerShutdownFlag != NULL && *u8_g_timerShutdownFlag == 1))
	{
		u16_g_overflow2Ticks = 0;
		TIMER_timer2Stop();
		if (void_g_pfOvfInterruptAction != NULL)
			void_g_pfOvfInterruptAction();
	}
}
