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
/* Options: 0 // PORT A
			1 // PORT B
			2 // PORT C
			3 // PORT D
 */
#define BTN_U8_PORT			0 // enum -> EN_DIO_PORT_T.PORT_A in MCAL/dio/dio_interface.h

/* The Pins connected to BTN(s) */
/* Options: 0 // DIO_U8_PIN0
			1 // DIO_U8_PIN1
			2 // DIO_U8_PIN2
			3 // DIO_U8_PIN3
			4 // DIO_U8_PIN4
			5 // DIO_U8_PIN5
			6 // DIO_U8_PIN6
			7 // DIO_U8_PIN7
 */
#define BTN_U8_1_PIN		0//DIO_U8_PIN0
#define BTN_U8_2_PIN		1//DIO_U8_PIN1
#define BTN_U8_3_PIN		2//DIO_U8_PIN2
#define BTN_U8_4_PIN		3//DIO_U8_PIN3
#define BTN_U8_5_PIN		4//DIO_U8_PIN4
#define BTN_U8_6_PIN		5//DIO_U8_PIN5
#define BTN_U8_7_PIN		6//DIO_U8_PIN6
#define BTN_U8_8_PIN		7//DIO_U8_PIN7

/* End of Configurations */

/*******************************************************************************************************************************************************************/

#endif /* BTN_CONFIG_H_ */