 /*
  * DCM_Interface.h
  *
  *     Created on: Apr 11, 2023
  *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
  *    Description: This file contains all Direct Current Motor (DCM) functions' prototypes and definitions (Macros) to avoid magic numbers.
  *		MCU Datasheet: AVR ATmega32
  *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
  */

#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

/*******************************************************************************************************************************************************************/
/* DCM Includes */

/* LIB */
#include "../../LIB/std.h"
#include "../../LIB/bit_math.h"

/* MCAL */
#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/timer/timer_interface.h"

/*******************************************************************************************************************************************************************/
/* DCM Macros */

/* DCM Directions of Rotation */
#define DCM_U8_CLOCKWISE_DIRECTION				0
#define DCM_U8_COUNTER_CLOCKWISE_DIRECTION		1

/* DCM Normal Mode: Speed is constant. */
#define DCM_U8_NO_SPEED							0
/* DCM Speed Mode : Speed is variable. Top Speed that can be generated is 1023, using the 16 bit TMR1 register ( Fast PWM 10-Bit Mode ). */
#define DCM_U16_TOP_SPEED						0x03FF

/*******************************************************************************************************************************************************************/
/* DCM Functions' Prototypes */

//EN_DCM_ERROR_T DCM_rotateDCM(u8 DCM_a_rotateDirection, u16 DCM_a_rotateSpeed);
//
//EN_DCM_ERROR_T DCM_changeDCMDirection(void);
//
//EN_DCM_ERROR_T DCM_u8SetDutyCycleOfPWM(u8 DCM_a_dutyCycleValue);
//
//EN_DCM_ERROR_T DCM_vdStopDCM(void);
//
//EN_DCM_ERROR_T DCM_motorInit(ST_DCM_g_Config_t* DCM_a_ptrToConfig);


//u8 DCM_u8GetDutyCycleOfPWM(u8* Cpy_pu8ReturnedDutyCycleValue);
/**************************************************************************************************************************************************************************/
typedef struct {
	u8 DCM_g_mot0EnPinNumber0;
	u8 DCM_g_mot0EnPinNumber1;
	u8 DCM_g_mot0PWMPinNumber0;
	u8 DCM_g_mot1EnPinNumber0;
	u8 DCM_g_mot1EnPinNumber1;
	u8 DCM_g_mot1PWMPinNumber1;
	u8 DCM_g_initialDutyCycleValue;
}ST_DCM_g_Config_t;




/*******************************************************************************************************************************************************************/

#endif /* DCM_INTERFACE_H_ */