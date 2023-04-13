/*
 * TMR_Interface.h
 *
 *     Created on: Apr 11, 2023
 *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
 *    Description: This file contains all Timers (TMR) functions' prototypes and definitions (Macros) to avoid magic numbers.
 *		MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

/* ****************************************************************/
/* TMR Includes */

/* STD LIB */
#include <math.h>

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/* ****************************************************************/
/* TMR Macros */

/* The 3 Timers counted from 0 to 2 */
#define TMR_U8_TMR0							0
#define TMR_U8_TMR1 						1
#define TMR_U8_TMR2 						2

/* The 3 Timers Channels counted from 0 to 2 */
#define TMR_U8_NO_CHANNEL					0
#define TMR_U8_TMR_1_CHANNEL_A				1
#define TMR_U8_TMR_1_CHANNEL_B				2

/* The 3 Timers Interrupts counted from 0 to 2 */
#define TMR_U8_CAPT_INTERRUPT				0
#define TMR_U8_COMP_INTERRUPT				1
#define TMR_U8_OVF_INTERRUPT				2

/* The 3 Timers Compare Match Output Modes counted from 0 to 2 */
#define TMR_U8_TOG_OCR_PIN					0
#define TMR_U8_CLR_OCR_PIN					1
#define TMR_U8_SET_OCR_PIN					2

/* ****************************************************************/


#define OC0_PIN_DIR                         DDRB
#define OC0_PIN                              3
#define GLOBAL_INTERRUPT_ENABLE_BIT      7

#define MAX_TIMER_DELAY					 (MAX_DELAY * 65535)
#define MAX_DELAY				 		 (0.032768f) // in sec
#define MAX_COUNTS						   256
#define TICK_TIME						 (0.000128f) // in sec
#define SECOND_OPERATOR					 (1000.0f)

#define NO_PRESCALER						1 
/* ****************************************************************/
	/*error definitions*/
typedef enum {
	TIMER_OK,
	TIMER_ERROR
}EN_TMR_ERROR_T;

typedef enum {
	ENABLED,
	DISABLED
}EN_TMR_INTERRPUT_T;
/* **********************************************************************/
/*  TMR Functions' prototypes                                           */
/* **********************************************************************/
/**
 * @brief Initializes timer0 at normal mode
 *
 * This function initializes/selects the timer_0 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TMR_INTERRPUT_T TMR_a_interrputEnable value to set the interrupt bit for timer_0 in the TIMSK reg.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr0NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable);
/* ****************************************************************/
/**
 * @brief Creates a delay using timer_0 in overflow mode
 *
 * This function Creates the desired delay on timer_0 normal mode.
 * @param[in] u16 u16_a_interval value to set the desired delay.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr0Delay(u16 interval);
/* ****************************************************************/
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_0.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr0Start(u16 u16_a_prescaler);
/* ****************************************************************/
/**
 * @brief Stop the timer by setting the prescaler to be 000--> timer is stopped.
 *
 * This function Clear the prescaler for timer_0.
 * @param[in] void.
 *
 * @return void
 */

void TMR_tmr0Stop(void);

/* ****************************************************************/
/**
 * @brief timer compare match mode.
 *
 * This function set the compare value for timer_0.
 * @param[in] u8 u8_a_outCompValue value at which the matching will occur.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr0CleareCompMatInit(u8 u8_a_outCompValue );




/**
 * @brief Initializes timer2 at normal mode
 *
 * This function initializes/selects the timer_2 normal mode for the timer, and enable the ISR for this timer.
 * @param[in] EN_TMR_INTERRPUT_T TMR_a_interrputEnable value to set the interrupt bit for timer_2 in the TIMSK reg.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr2NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable );
/**
 * @brief Stop the timer by setting the prescaler to be 000--> timer is stopped.
 *
 * This function Clear the prescaler for timer_2.
 * @param[in] void.
 *
 * @return void
 */
void TMR_tmr2Stop(void);
/**
 * @brief Start the timer by setting the desired prescaler.
 *
 * This function set the prescaler for timer_2.
 * @param[in] u16 u16_a_prescaler value to set the desired prescaler.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr2Start(u16 u16_a_prescaler);
/**
 * @brief Creates a delay using timer_2 in overflow mode
 *
 * This function Creates the desired delay on timer_2 normal mode.
 * @param[in] u16 u16_a_interval value to set the desired delay.
 *
 * @return An EN_TMR_ERROR_T value indicating the success or failure of the operation
 *         (TIMER_OK if the operation succeeded, TIMER_ERROR otherwise)
 */
EN_TMR_ERROR_T TMR_tmr2Delay(u16 interval);
EN_TMR_ERROR_T TMR_tmr2CleareCompMatInit(u8 u8_a_outCompValue );

EN_TMR_ERROR_T TMR_tmr1NormalModeInit(EN_TMR_INTERRPUT_T TMR_a_interrputEnable);
void TMR_tmr1CleareCompMatchInit(void);
EN_TMR_ERROR_T TMR_tmr1Start(u16 u16_a_prescaler);
void TMR_tmr1Stop(void);
EN_TMR_ERROR_T TMR_tmr1CreatePWM(u8 u8_a_dutyCycle);



/*******************************************************************************************************************************************************************/

#endif /* TMR_INTERFACE_H_ */