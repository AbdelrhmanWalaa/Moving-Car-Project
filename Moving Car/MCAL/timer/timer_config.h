/*
 * TIMER_Config.h
 *
 *     Created on: Apr 11, 2023
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all Timers (TIMER) pre-build configurations, through which user can configure before using the TIMER peripheral.
 *  MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/* ***********************************************************************************************/
/* TIMER Configurations' Definitions */

/*#define ISR(INT_VECT)	void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)*/

/*
 * 8-bit Timer/Counter0 Configurations' Definitions
 */

/* TIMER0 Waveform Generation Modes */
#define TIMER_U8_TIMER_0_NORMAL_MODE                            0
#define TIMER_U8_TIMER_0_PWM_PHASE_CORRECT_MODE                    1
#define TIMER_U8_TIMER_0_CTC_MODE                                2
#define TIMER_U8_TIMER_0_FAST_PWM_MODE                            3

/* TIMER0 Compare Match Output Modes */
#define TIMER_U8_TIMER_0_DISCONNECT_OC0_PIN                        0
#define TIMER_U8_TIMER_0_TOG_OC0_PIN                            1
#define TIMER_U8_TIMER_0_CLR_OC0_PIN                            2
#define TIMER_U8_TIMER_0_SET_OC0_PIN                            3

/* TIMER0 Interrupt Sources */
#define TIMER_U8_TIMER_0_NO_INTERRUPT                            0
#define TIMER_U8_TIMER_0_COMP_INTERRUPT                            1
#define TIMER_U8_TIMER_0_OVF_INTERRUPT                            2

/* TIMER0 Clock Sources */
#define TIMER_U8_TIMER_0_NO_CLOCK_SOURCE                        0
#define TIMER_U8_TIMER_0_NO_PRESCALER                            1
#define TIMER_U8_TIMER_0_8_PRESCALER                            2
#define TIMER_U8_TIMER_0_64_PRESCALER                            3
#define TIMER_U8_TIMER_0_256_PRESCALER                            4
#define TIMER_U8_TIMER_0_1024_PRESCALER                            5
#define TIMER_U8_TIMER_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE        6
#define TIMER_U8_TIMER_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE        7

/* End of Timer/Counter0 Configurations' Definitions */

/* ***********************************************************************************************/

/*
 * 16-bit Timer/Counter1 Configurations' Definitions
 */

/* TIMER1 Waveform Generation Modes */
#define TIMER_U8_TIMER_1_NORMAL_MODE                            0
#define TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_8_BIT_MODE            1
#define TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_9_BIT_MODE            2
#define TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_10_BIT_MODE            3
#define TIMER_U8_TIMER_1_CTC_OCR1A_TOP                            4
#define TIMER_U8_TIMER_1_FAST_PWM_8_BIT_MODE                    5
#define TIMER_U8_TIMER_1_FAST_PWM_9_BIT_MODE                    6
#define TIMER_U8_TIMER_1_FAST_PWM_10_BIT_MODE                    7
#define TIMER_U8_TIMER_1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_TOP    8
#define TIMER_U8_TIMER_1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_TOP    9
#define TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_ICR1_TOP                10
#define TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_OCR1A_TOP            11
#define TIMER_U8_TIMER_1_CTC_ICR1_TOP                            12
#define TIMER_U8_TIMER_1_FAST_PWM_ICR1_TOP                        13
#define TIMER_U8_TIMER_1_FAST_PWM_OCR1A_TOP                        14

/* TIMER1 Compare Match Output Modes - Channel A */
#define TIMER_U8_TIMER_1_DISCONNECT_OC1A_PIN                    0
#define TIMER_U8_TIMER_1_TOG_OC1A_PIN                            1
#define TIMER_U8_TIMER_1_CLR_OC1A_PIN                            2
#define TIMER_U8_TIMER_1_SET_OC1A_PIN                            3

/* TIMER1 Compare Match Output Modes - Channel B */
#define TIMER_U8_TIMER_1_DISCONNECT_OC1B_PIN                    0
#define TIMER_U8_TIMER_1_TOG_OC1B_PIN                            1
#define TIMER_U8_TIMER_1_CLR_OC1B_PIN                            2
#define TIMER_U8_TIMER_1_SET_OC1B_PIN                            3

/* TIMER1 Interrupt Sources */
#define TIMER_U8_TIMER_1_NO_INTERRUPT                            0
#define TIMER_U8_TIMER_1_CAPT_INTERRUPT                            1
#define TIMER_U8_TIMER_1_COMP_A_INTERRUPT                        2
#define TIMER_U8_TIMER_1_COMP_B_INTERRUPT                        3
#define TIMER_U8_TIMER_1_OVF_INTERRUPT                            4

/* TIMER1 Clock Sources */
#define TIMER_U8_TIMER_1_NO_CLOCK_SOURCE                        0
#define TIMER_U8_TIMER_1_NO_PRESCALER                            1
#define TIMER_U8_TIMER_1_8_PRESCALER                            2
#define TIMER_U8_TIMER_1_64_PRESCALER                            3
#define TIMER_U8_TIMER_1_256_PRESCALER                            4
#define TIMER_U8_TIMER_1_1024_PRESCALER                            5
#define TIMER_U8_TIMER_1_EXTERNAL_CLOCK_SOURCE_FALL_EDGE        6
#define TIMER_U8_TIMER_1_EXTERNAL_CLOCK_SOURCE_RISE_EDGE        7

/* End of Timer/Counter1 Configurations' Definitions */

/* ***********************************************************************************************/

/*
 * 8-bit Timer/Counter2 Configurations' Definitions
 */

/* TIMER2 Waveform Generation Modes */
#define TIMER_U8_TIMER_2_NORMAL_MODE                            0
#define TIMER_U8_TIMER_2_PWM_PHASE_CORRECT_MODE                    1
#define TIMER_U8_TIMER_2_CTC_MODE                                2
#define TIMER_U8_TIMER_2_FAST_PWM_MODE                            3

/* TIMER2 Compare Match Output Modes */
#define TIMER_U8_TIMER_2_DISCONNECT_OC2_PIN                        0
#define TIMER_U8_TIMER_2_TOG_OC2_PIN                            1
#define TIMER_U8_TIMER_2_CLR_OC2_PIN                            2
#define TIMER_U8_TIMER_2_SET_OC2_PIN                            3

/* TIMER2 Interrupt Sources */
#define TIMER_U8_TIMER_2_NO_INTERRUPT                            0
#define TIMER_U8_TIMER_2_COMP_INTERRUPT                            1
#define TIMER_U8_TIMER_2_OVF_INTERRUPT                            2

/* TIMER2 Clock Sources */
#define TIMER_U8_TIMER_2_NO_CLOCK_SOURCE                        0
#define TIMER_U8_TIMER_2_NO_PRESCALER                            1
#define TIMER_U8_TIMER_2_8_PRESCALER                            2
#define TIMER_U8_TIMER_2_32_PRESCALER                            3
#define TIMER_U8_TIMER_2_64_PRESCALER                            4
#define TIMER_U8_TIMER_2_128_PRESCALER                            5
#define TIMER_U8_TIMER_2_256_PRESCALER                            6
#define TIMER_U8_TIMER_2_1024_PRESCALER                            7

/* End of Timer/Counter2 Configurations' Definitions */

/* ***********************************************************************************************/
/* TIMER Configurations */

/*
 * 8-bit Timer/Counter0 Configurations
 */

/* TIMER0 Waveform Generation Mode Select */
/* Options: TIMER_U8_TIMER_0_NORMAL_MODE
 *          TIMER_U8_TIMER_0_PWM_PHASE_CORRECT_MODE
 *          TIMER_U8_TIMER_0_CTC_MODE
 *          TIMER_U8_TIMER_0_FAST_PWM_MODE
 */
#define TIMER_U8_TIMER_0_MODE_SELECT            TIMER_U8_TIMER_0_NORMAL_MODE

/* TIMER0 Compare Match Output Mode Select */
/* Options: TIMER_U8_TIMER_0_DISCONNECT_OC0_PIN                     // Any Mode
 *          TIMER_U8_TIMER_0_TOG_OC0_PIN                            // Non-PWM Modes only
 *          TIMER_U8_TIMER_0_CLR_OC0_PIN                            // Any Mode ( PWM -> Non-Inverting Mode )
 *          TIMER_U8_TIMER_0_SET_OC0_PIN                            // Any Mode ( PWM -> Inverting Mode )
 */
#define TIMER_U8_TIMER_0_COMP_OUTPUT_MODE        TIMER_U8_TIMER_0_DISCONNECT_OC0_PIN

/* TIMER0 Interrupt Select */
/* Options: TIMER_U8_TIMER_0_NO_INTERRUPT
 * 			TIMER_U8_TIMER_0_COMP_INTERRUPT
 * 			TIMER_U8_TIMER_0_OVF_INTERRUPT
 */
#define TIMER_U8_TIMER_0_INTERRUPT_SELECT        TIMER_U8_TIMER_0_NO_INTERRUPT

/* TIMER0 Clock Select */
/* Options: TIMER_U8_TIMER_0_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter0 stopped )
 * 			TIMER_U8_TIMER_0_NO_PRESCALER							// CLK IO/1   ( No prescaling )
 * 			TIMER_U8_TIMER_0_8_PRESCALER							// CLK IO/8   ( From prescaler )
 * 			TIMER_U8_TIMER_0_64_PRESCALER							// CLK IO/64  ( From prescaler )
 * 			TIMER_U8_TIMER_0_256_PRESCALER							// CLK IO/256 ( From prescaler )
 * 			TIMER_U8_TIMER_0_1024_PRESCALER							// CLK IO/1024( From prescaler )
 * 			TIMER_U8_TIMER_0_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		// External clock source on T0 pin. Clock on falling edge.
 * 			TIMER_U8_TIMER_0_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		// External clock source on T0 pin. Clock on rising edge.
 */
#define TIMER_U8_TIMER_0_CLOCK_SELECT            TIMER_U8_TIMER_0_NO_CLOCK_SOURCE

/* TIMER0 Other Configurations */
#define TIMER_U8_TIMER_0_PRELOAD_VALUE            0
#define TIMER_U8_TIMER_0_COMPARE_VALUE            0
#define TIMER_U16_TIMER_0_NUM_OF_OVERFLOWS        1

/* End of Timer/Counter0 Configurations */

/* ***********************************************************************************************/

/*
 * 16-bit Timer/Counter1 Configurations
 */

/* TIMER1 Waveform Generation Mode Select */
/* Options: TIMER_U8_TIMER_1_NORMAL_MODE							// Overflow Value ( TOP ) = 0xFFFF
 *			TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_8_BIT_MODE			// Overflow Value ( TOP ) = 0x00FF
 *			TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_9_BIT_MODE			// Overflow Value ( TOP ) = 0x01FF
 *			TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_10_BIT_MODE			// Overflow Value ( TOP ) = 0x03FF
 *			TIMER_U8_TIMER_1_CTC_OCR1A_TOP							// Overflow Value ( TOP ) = OCR1A
 *			TIMER_U8_TIMER_1_FAST_PWM_8_BIT_MODE					// Overflow Value ( TOP ) = 0x00FF
 *			TIMER_U8_TIMER_1_FAST_PWM_9_BIT_MODE					// Overflow Value ( TOP ) = 0x01FF
 *			TIMER_U8_TIMER_1_FAST_PWM_10_BIT_MODE					// Overflow Value ( TOP ) = 0x03FF
 *			TIMER_U8_TIMER_1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_TOP	// Overflow Value ( TOP ) = ICR1
 *			TIMER_U8_TIMER_1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_TOP	// Overflow Value ( TOP ) = OCR1A
 *			TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_ICR1_TOP				// Overflow Value ( TOP ) = ICR1
 *			TIMER_U8_TIMER_1_PWM_PHASE_CORRECT_OCR1A_TOP			// Overflow Value ( TOP ) = OCR1A
 *			TIMER_U8_TIMER_1_CTC_ICR1_TOP							// Overflow Value ( TOP ) = ICR1
 *			TIMER_U8_TIMER_1_FAST_PWM_ICR1_TOP						// Overflow Value ( TOP ) = ICR1
 *			TIMER_U8_TIMER_1_FAST_PWM_OCR1A_TOP						// Overflow Value ( TOP ) = OCR1A
 */
#define TIMER_U8_TIMER_1_MODE_SELECT            TIMER_U8_TIMER_1_NORMAL_MODE

/* TIMER1 Compare Match Output Mode Select - Channel A */
/* Options: TIMER_U8_TIMER_1_DISCONNECT_OC1A_PIN                	// Any Mode
 *          TIMER_U8_TIMER_1_TOG_OC1A_PIN                        	// Selected Modes only
 *          TIMER_U8_TIMER_1_CLR_OC1A_PIN                        	// Any Mode ( PWM -> Non-Inverting Mode )
 *          TIMER_U8_TIMER_1_SET_OC1A_PIN                        	// Any Mode ( PWM -> Inverting Mode )
 */
#define TIMER_U8_TIMER_1_COMP_OUTPUT_MODE_A        TIMER_U8_TIMER_1_DISCONNECT_OC1A_PIN

/* TIMER1 Compare Match Output Mode Select - Channel B */
/* Options: TIMER_U8_TIMER_1_DISCONNECT_OC1B_PIN 					// Any Mode
 * 			TIMER_U8_TIMER_1_TOG_OC1B_PIN                   		// Non-PWM Modes only
 *          TIMER_U8_TIMER_1_CLR_OC1B_PIN                           // Any Mode ( PWM -> Non-Inverting Mode )
 *          TIMER_U8_TIMER_1_SET_OC1B_PIN                           // Any Mode ( PWM -> Inverting Mode )
 */
#define TIMER_U8_TIMER_1_COMP_OUTPUT_MODE_B        TIMER_U8_TIMER_1_DISCONNECT_OC1A_PIN

/* TIMER1 Interrupt Select */
/* Options: TIMER_U8_TIMER_1_NO_INTERRUPT
 * 			TIMER_U8_TIMER_1_CAPT_INTERRUPT
 * 			TIMER_U8_TIMER_1_COMP_A_INTERRUPT
 * 			TIMER_U8_TIMER_1_COMP_B_INTERRUPT
 * 			TIMER_U8_TIMER_1_OVF_INTERRUPT
 */
#define TIMER_U8_TIMER_1_INTERRUPT_SELECT        TIMER_U8_TIMER_1_NO_INTERRUPT

/* TIMER1 Clock Select */
/* Options: TIMER_U8_TIMER_1_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter1 stopped )
 * 			TIMER_U8_TIMER_1_NO_PRESCALER							// CLK IO/1   ( No prescaling )
 * 			TIMER_U8_TIMER_1_8_PRESCALER							// CLK IO/8   ( From prescaler )
 * 			TIMER_U8_TIMER_1_64_PRESCALER							// CLK IO/64  ( From prescaler )
 * 			TIMER_U8_TIMER_1_256_PRESCALER							// CLK IO/256 ( From prescaler )
 * 			TIMER_U8_TIMER_1_1024_PRESCALER							// CLK IO/1024( From prescaler )
 * 			TIMER_U8_TIMER_1_EXTERNAL_CLOCK_SOURCE_FALL_EDGE		// External clock source on T1 pin. Clock on falling edge.
 * 			TIMER_U8_TIMER_1_EXTERNAL_CLOCK_SOURCE_RISE_EDGE		// External clock source on T1 pin. Clock on rising edge.
 */
#define TIMER_U8_TIMER_1_CLOCK_SELECT            TIMER_U8_TIMER_1_NO_CLOCK_SOURCE

/* TIMER1 Other Configurations */
#define TIMER_U16_TIMER_1_PRELOAD_VALUE            0
#define TIMER_U16_TIMER_1_COMPARE_VALUE_A        0
#define TIMER_U16_TIMER_1_COMPARE_VALUE_B        0
#define TIMER_U16_TIMER_1_INPUT_CAPTURE_VALUE    0
#define TIMER_U16_TIMER_1_NUM_OF_OVERFLOWS        1

/* End of Timer/Counter1 Configurations */

/* ***********************************************************************************************/

/*
 * 8-bit Timer/Counter2 Configurations
 */

/* TIMER2 Waveform Generation Mode Select */
/* Options: TIMER_U8_TIMER_2_NORMAL_MODE
 *          TIMER_U8_TIMER_2_PWM_PHASE_CORRECT_MODE
 *          TIMER_U8_TIMER_2_CTC_MODE
 *          TIMER_U8_TIMER_2_FAST_PWM_MODE
 */
#define TIMER_U8_TIMER_2_MODE_SELECT            TIMER_U8_TIMER_2_NORMAL_MODE

/* TIMER2 Compare Match Output Mode Select */
/* Options: TIMER_U8_TIMER_2_DISCONNECT_OC2_PIN						// Any Mode
 *          TIMER_U8_TIMER_2_TOG_OC2_PIN							// Non-PWM Modes only
 *          TIMER_U8_TIMER_2_CLR_OC2_PIN							// Any Mode ( PWM -> Non-Inverting Mode )
 *          TIMER_U8_TIMER_2_SET_OC2_PIN							// Any Mode ( PWM -> Inverting Mode )
 */
#define TIMER_U8_TIMER_2_COMP_OUTPUT_MODE        TIMER_U8_TIMER_2_DISCONNECT_OC2_PIN

/* TIMER2 Interrupt Select */
/* Options: TIMER_U8_TIMER_2_NO_INTERRUPT
 * 			TIMER_U8_TIMER_2_COMP_INTERRUPT
 * 			TIMER_U8_TIMER_2_OVF_INTERRUPT
 */
#define TIMER_U8_TIMER_2_INTERRUPT_SELECT        TIMER_U8_TIMER_2_NO_INTERRUPT

/* TIMER2 Clock Select */
/* Options: TIMER_U8_TIMER_2_NO_CLOCK_SOURCE						// No clock source ( Timer/Counter2 stopped )
 * 			TIMER_U8_TIMER_2_NO_PRESCALER							// CLK T2S/1   ( No prescaling )
 * 			TIMER_U8_TIMER_2_8_PRESCALER							// CLK T2S/8   ( From prescaler )
 * 			TIMER_U8_TIMER_2_32_PRESCALER							// CLK T2S/32  ( From prescaler )
 * 			TIMER_U8_TIMER_2_64_PRESCALER							// CLK T2S/64  ( From prescaler )
 * 			TIMER_U8_TIMER_2_128_PRESCALER							// CLK T2S/128 ( From prescaler )
 * 			TIMER_U8_TIMER_2_256_PRESCALER							// CLK T2S/256 ( From prescaler )
 * 			TIMER_U8_TIMER_2_1024_PRESCALER							// CLK T2S/1024( From prescaler )
 */
#define TIMER_U8_TIMER_2_CLOCK_SELECT            TIMER_U8_TIMER_2_NO_CLOCK_SOURCE

/* TIMER2 Other Configurations */
#define TIMER_U8_TIMER_2_PRELOAD_VALUE            0
#define TIMER_U8_TIMER_2_COMPARE_VALUE            0
#define TIMER_U16_TIMER_2_NUM_OF_OVERFLOWS        1

/* End of Timer/Counter2 Configurations */

/* ***********************************************************************************************/

/*
 * TIMER Other Configurations
 */

/* Timers Flags */
#define TIMER_U8_FLAG_DOWN                    0
#define TIMER_U8_FLAG_UP                        1

/* End of Configurations */

/* ***********************************************************************************************/

#endif /* TIMER_CONFIG_H_ */