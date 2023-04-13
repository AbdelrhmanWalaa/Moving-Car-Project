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

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */


ST_DCM_g_Config_t ST_g_carMotors[2] =
{
	{  	 MOT0_EN_PIN_NUMBER_0 ,  MOT0_EN_PIN_NUMBER_1, MOT0_PWM_PIN_NUMBER, MOT0_EN_PORT_NUMBER, MOT0_PWM_PORT_NUMBER},
	{  	 MOT1_EN_PIN_NUMBER_0,  MOT1_EN_PIN_NUMBER_1, MOT1_PWM_PIN_NUMBER, MOT1_EN_PORT_NUMBER, MOT1_PWM_PORT_NUMBER}
};
EN_DCM_FLAG DCM_g_stopFlag = FALSE;


/*******************************************************************************************************************************************************************/

EN_DCM_ERROR_T DCM_motorInit(ST_DCM_g_Config_t* DCM_a_ptrToConfig)
{
	if (DCM_a_ptrToConfig == NULL)
		return DCM_ERROR;
	else
	{
		u8 u8_a_loopCounter;
		for (u8_a_loopCounter = 0; u8_a_loopCounter < MOTORS_NUMBER; u8_a_loopCounter++)
		{
			DIO_init(DCM_a_ptrToConfig[u8_a_loopCounter].DCM_g_motEnPinNumber0,
				DCM_a_ptrToConfig[u8_a_loopCounter].DCM_g_motEnPortNumber,
				DIO_OUT);
			DIO_init(DCM_a_ptrToConfig[u8_a_loopCounter].DCM_g_motEnPinNumber1,
				DCM_a_ptrToConfig[u8_a_loopCounter].DCM_g_motEnPortNumber,
				DIO_OUT);
			DIO_init(DCM_a_ptrToConfig[u8_a_loopCounter].DCM_g_motPWMPinNumber,
				DCM_a_ptrToConfig[u8_a_loopCounter].DCM_g_motEnPortNumber,
				DIO_OUT);
		}

	}
	TMR_u8OVFSetCallBack(DCM_updateStopFlag);
}

/*******************************************************************************************************************************************************************/
EN_DCM_ERROR_T DCM_changeDCMDirection(ST_DCM_g_Config_t* DCM_a_ptrToConfig, EN_DCM_MOTORSIDE DCM_a_motorNum)
{
	if (DCM_a_ptrToConfig == NULL)
		return DCM_ERROR;
	else
	{

		DIO_toggle(DCM_a_ptrToConfig[DCM_a_motorNum].DCM_g_motEnPinNumber0,
			DCM_a_ptrToConfig[DCM_a_motorNum].DCM_g_motEnPortNumber
		);
		DIO_toggle(DCM_a_ptrToConfig[DCM_a_motorNum].DCM_g_motEnPinNumber1,
			DCM_a_ptrToConfig[DCM_a_motorNum].DCM_g_motEnPortNumber
		);
	}
	return DCM_OK;
}
/****************************************************************************************************************************************/

void DCM_vdStopDCM(void)
{
	DIO_write(0, PORT_B, DIO_U8_PIN_LOW);
}

/************************************************************************************************************************************/

EN_DCM_ERROR_T DCM_u8SetDutyCycleOfPWM(u8 DCM_a_dutyCycleValue)
{

	if (DCM_a_dutyCycleValue > MAX_DUTY_CYCLE)
		return DCM_ERROR;
	else
	{
		u8 DCM_a_mappedDuty = DCM_a_dutyCycleValue / PERIOD_TIME;
		u16 u16_onTime = DCM_a_mappedDuty;
		u16 u16_offTime = 10 - DCM_a_mappedDuty;

		while (DCM_g_stopFlag != TRUE)
		{
			DIO_write(0, PORT_B, DIO_U8_PIN_HIGH);
			TMR_tmr2Delay(u16_onTime);
			DIO_write(0, PORT_B, DIO_U8_PIN_LOW);
			TMR_tmr2Delay(u16_offTime);
		}
		DCM_g_stopFlag = FALSE;
	}
}

/****************************************************************************************************************************************/
void DCM_updateStopFlag(void)
{
	DCM_g_stopFlag = TRUE;
}
/****************************************************************************************************************************************/

EN_DCM_ERROR_T DCM_rotateDCM(u8 DCM_a_rotateDirection, u16 DCM_a_rotateSpeed)
{
	DCM_changeDCMDirection(ST_g_carMotors, MOTOR_RIGHT);
	DCM_u8SetDutyCycleOfPWM(ROTATION_DUTY_CYCLE);
	DCM_changeDCMDirection(ST_g_carMotors, MOTOR_RIGHT);
}
/****************************************************************************************************************************************/