/*
 * DCM_Program.c
 *
 *     Created on: Apr 11, 2023
 *         Author: Mahmoud Mowafey - https://github.com/Mahmoud-Mowafy
 *  Description: This file contains all Direct Current Motor (DCM) functions' implementation.
 *		MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* HAL */
#include "dcm_config.h"
#include "dcm_interface.h"

/* ***********************************************************************************************/
/* Declaration and Initialization */


ST_DCM_g_Config_t ST_g_carMotors[2] =
{
	{ MOT0_EN_PIN_NUMBER_0, MOT0_EN_PIN_NUMBER_1, MOT0_PWM_PIN_NUMBER, MOT0_EN_PORT_NUMBER, MOT0_PWM_PORT_NUMBER },
	{ MOT1_EN_PIN_NUMBER_0, MOT1_EN_PIN_NUMBER_1, MOT1_PWM_PIN_NUMBER, MOT1_EN_PORT_NUMBER, MOT1_PWM_PORT_NUMBER }
};

EN_DCM_FLAG DCM_g_stopFlag = FALSE;

u8 * u8_g_shutdownFlag = NULL;

/* ***********************************************************************************************/

EN_DCM_ERROR_T DCM_motorInit(u8 ** u8_a_shutdownFlag)
{
    u8_g_shutdownFlag = *u8_a_shutdownFlag;
	/*if (ST_g_carMotors == NULL)
		return DCM_ERROR;
	else
	{*/
    u8 u8_a_loopCounter;
    for (u8_a_loopCounter = 0; u8_a_loopCounter < MOTORS_NUMBER; u8_a_loopCounter++)
    {
        DIO_init(ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber0,
            ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
            DIO_OUT);
        DIO_init(ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber1,
            ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
            DIO_OUT);
        DIO_init(ST_g_carMotors[u8_a_loopCounter].DCM_g_motPWMPinNumber,
            ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
            DIO_OUT);
			
		DIO_write(ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber0,
			ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
			DIO_U8_PIN_HIGH);
		DIO_write(ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber1,
			ST_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
			DIO_U8_PIN_LOW);	
			
    }
//	}
    TIMER_ovfSetCallback(DCM_updateStopFlag);
    return DCM_OK;
}


/*******************************************************************************************************************************************************************/
EN_DCM_ERROR_T DCM_changeDCMDirection(EN_DCM_MOTORSIDE DCM_a_motorNum)
{
	//if (DCM_a_motorNum > 2)
		//return DCM_ERROR;
	//else
	//{

		DIO_toggle(ST_g_carMotors[DCM_a_motorNum].DCM_g_motEnPinNumber0,
			ST_g_carMotors[DCM_a_motorNum].DCM_g_motEnPortNumber
		);
		DIO_toggle(ST_g_carMotors[DCM_a_motorNum].DCM_g_motEnPinNumber1,
			ST_g_carMotors[DCM_a_motorNum].DCM_g_motEnPortNumber
		);
	//}
	return DCM_OK;
}
/* ***********************************************************************************************/

void DCM_stopDCM(void)
{
	DIO_write(ST_g_carMotors[0].DCM_g_motPWMPinNumber, ST_g_carMotors[0].DCM_g_motEnPortNumber, DIO_U8_PIN_LOW);
	DIO_write(ST_g_carMotors[1].DCM_g_motPWMPinNumber, ST_g_carMotors[1].DCM_g_motEnPortNumber, DIO_U8_PIN_LOW);
}

/* ***********************************************************************************************/

EN_DCM_ERROR_T DCM_setDutyCycleOfPWM(u8 DCM_a_dutyCycleValue)
{

	if (DCM_a_dutyCycleValue > MAX_DUTY_CYCLE)
		return DCM_ERROR;
	else
	{
		u8 DCM_a_mappedDuty = DCM_a_dutyCycleValue / PERIOD_TIME;
		u16 u16_onTime = DCM_a_mappedDuty;
		u16 u16_offTime = 10 - DCM_a_mappedDuty;

		while (DCM_g_stopFlag != TRUE && *u8_g_shutdownFlag == 0)
		{
			DIO_portWrite(ST_g_carMotors[0].DCM_g_motEnPortNumber, DIO_U8_PORT_HIGH, DIO_MASK_BITS_0_1);
			TIMER_timer0Delay(u16_onTime);
			DIO_portWrite(ST_g_carMotors[0].DCM_g_motEnPortNumber, DIO_U8_PORT_LOW, DIO_MASK_BITS_0_1);
			TIMER_timer0Delay(u16_offTime);
		}
		DCM_g_stopFlag = FALSE;
	}
    return DCM_OK;
}

/* ***********************************************************************************************/
void DCM_updateStopFlag(void)
{
	DCM_g_stopFlag = TRUE;
}
/* ***********************************************************************************************/

EN_DCM_ERROR_T DCM_rotateDCM()
{
    if(*u8_g_shutdownFlag == 1) return DCM_ERROR;
	DCM_changeDCMDirection(MOTOR_RIGHT);
	DCM_setDutyCycleOfPWM (ROTATION_DUTY_CYCLE);
	DCM_changeDCMDirection(MOTOR_RIGHT);
    return DCM_OK;
}
/* ***********************************************************************************************/