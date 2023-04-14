 /*
  * dcm_interface.h
  *
  *     Created on: Apr 11, 2023
  *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
  *    Description: This file contains all Direct Current Motor (DCM) functions' prototypes and definitions (Macros) to avoid magic numbers.
  *		MCU Datasheet: AVR ATmega32 - https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
  */

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

/* ***********************************************************************************************/
/* DCM Includes */

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/timer/timer_interface.h"

/* ***********************************************************************************************/
/* DCM Macros */
/* ***********************************************************************************************/
/* DCM Macros */
#define MOTORS_NUMBER                 2
#define ZERO_SPEED					  0
#define MAX_DUTY_CYCLE			      100
#define PERIOD_TIME					  10
#define ROTATION_DUTY_CYCLE           50


typedef struct {
	u8 DCM_g_motEnPinNumber0;
	u8 DCM_g_motEnPinNumber1;
	u8 DCM_g_motPWMPinNumber;
	EN_DIO_PORT_T DCM_g_motEnPortNumber;
	u8 DCM_g_motPWMPortNumber;
}ST_DCM_g_Config_t;


typedef enum {
	DCM_OK,
	DCM_ERROR
}EN_DCM_ERROR_T;

typedef enum {
	MOTOR_RIGHT,
	MOTOR_LEFT
}EN_DCM_MOTORSIDE;

typedef enum {
	FALSE,
	TRUE
}EN_DCM_FLAG;
/* ***********************************************************************************************/
/* DCM Functions' Prototypes */

EN_DCM_ERROR_T DCM_motorInit(u8 ** u8_a_shutdownFlag);

EN_DCM_ERROR_T DCM_rotateDCM(void);

EN_DCM_ERROR_T DCM_changeDCMDirection(EN_DCM_MOTORSIDE en_a_motorNum);

EN_DCM_ERROR_T DCM_setDutyCycleOfPWM(u8 u8_a_dutyCycleValue);

void DCM_stopDCM(void);

void DCM_updateStopFlag(void);

//u8 DCM_u8GetDutyCycleOfPWM(u8* Cpy_pu8ReturnedDutyCycleValue);
/* ***********************************************************************************************/

/* ***********************************************************************************************/

#endif /* DCM_INTERFACE_H_ */