/*
 * BTN_Config.h
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Button (BTN) pre-build configurations, through which user can configure before using the BTN peripheral.
 */

#ifndef BTN_CONFIG_H_
#define BTN_CONFIG_H_

/*******************************************************************************************************************************************************************/
/* BTN(s) Configurations */

/* The Port connected to BTN(s) */
/* Options: DIO_U8_PORTA
			DIO_U8_PORTB
			DIO_U8_PORTC
			DIO_U8_PORTD
 */
#define BTN_U8_PORT			DIO_U8_PORTA

/* The Pins connected to BTN(s) */
/* Options: DIO_U8_PIN0
			DIO_U8_PIN1
			DIO_U8_PIN2
			DIO_U8_PIN3
			DIO_U8_PIN4
			DIO_U8_PIN5
			DIO_U8_PIN6
			DIO_U8_PIN7
 */
#define BTN_U8_1_PIN		DIO_U8_PIN0
#define BTN_U8_2_PIN		DIO_U8_PIN1
#define BTN_U8_3_PIN		DIO_U8_PIN2
#define BTN_U8_4_PIN		DIO_U8_PIN3
#define BTN_U8_5_PIN		DIO_U8_PIN4
#define BTN_U8_6_PIN		DIO_U8_PIN5
#define BTN_U8_7_PIN		DIO_U8_PIN6
#define BTN_U8_8_PIN		DIO_U8_PIN7

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* BTN_CONFIG_H_ */