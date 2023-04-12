/*
 * DIO_Config.h
 *
 *     Created on: Apr 10, 2023
 *         Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 *    Description: This file contains all Digital Input Output (DIO) pre-build configurations,
 *                 through which user can configure before using the DIO peripheral.
 *  MCU Datasheet: AVR ATmega32
 *                 https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_

#define DIO_MIN_PIN_NO 0
#define DIO_MAX_PIN_NO 7

/*********************************************************************************************************************/
/** ATmega32 Pinouts:
 *
 *     Created on: Mar 31, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa */
/*

							  PDIP
						  -------------
		   (XCK/T0) PB0 -| 1		40 |- PA0 (ADC0)
			   (T1)	PB1	-| 2		39 |- PA1 (ADC1)
		(INT2/AIN0)	PB2	-| 3		38 |- PA2 (ADC2)
		 (OC0/AIN1)	PB3	-| 4		37 |- PA3 (ADC3)
			   (SS)	PB4	-| 5		36 |- PA4 (ADC4)
			 (MOSI)	PB5	-| 6		35 |- PA5 (ADC5)
			 (MISO)	PB6	-| 7		34 |- PA6 (ADC6)
			  (SCK)	PB7	-| 8		33 |- PA7 (ADC7)
				  RESET -| 9		32 |- AREF
					VCC	-| 10		31 |- GND
					GND	-| 11		30 |- AVCC
				  XTAL2	-| 12		29 |- PC0 (TOSC2)
				  XTAL1	-| 13		28 |- PC1 (TOSC1)
			  (RXD)	PD0 -| 14		27 |- PC2 (TDI)
			  (TXD)	PD1 -| 15		26 |- PC3 (TDO)
			 (INT0)	PD2 -| 16		25 |- PC4 (TMS)
			 (INT1)	PD3 -| 17		24 |- PC5 (TCK)
			 (OC1B)	PD4 -| 18		23 |- PC6 (SDA)
			 (OC1A)	PD5 -| 19		22 |- PC7 (SCL)
			  (ICP)	PD6 -| 20		21 |- PD7 (OC2)
					 	  -------------
 */

/*********************************************************************************************************************/

#endif /* DIO_CONFIG_H_ */