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


ST_DCM_g_Config_t st_g_carMotors[2] =
{
	{ MOT0_EN_PIN_NUMBER_0, MOT0_EN_PIN_NUMBER_1, MOT0_PWM_PIN_NUMBER, MOT0_EN_PORT_NUMBER, MOT0_PWM_PORT_NUMBER },
	{ MOT1_EN_PIN_NUMBER_0, MOT1_EN_PIN_NUMBER_1, MOT1_PWM_PIN_NUMBER, MOT1_EN_PORT_NUMBER, MOT1_PWM_PORT_NUMBER }
};

EN_DCM_FLAG en_g_stopFlag = FALSE;

u8 * u8_g_shutdownFlag = NULL;

/* ***********************************************************************************************/

/**
 * @brief Initialize the DC Motors by initializing their pins.
 *
 * @param u8_a_shutdownFlag Pointer to the Shutdown flag variable that acts as a main kill switch.
 *
 * @return EN_DCM_ERROR_T Returns DCM_OK if initialization is successful, or DCM_ERROR if initialization failed.
 *
 */
EN_DCM_ERROR_T DCM_motorInit(u8 ** u8_a_shutdownFlag)
{
    u8_g_shutdownFlag = *u8_a_shutdownFlag;
	/*if (st_g_carMotors == NULL)
		return DCM_ERROR;
	else
	{*/
    u8 u8_a_loopCounter;
    for (u8_a_loopCounter = 0; u8_a_loopCounter < MOTORS_NUMBER; u8_a_loopCounter++)
    {
        DIO_init(st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber0,
            st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
            DIO_OUT);
        DIO_init(st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber1,
            st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
            DIO_OUT);
        DIO_init(st_g_carMotors[u8_a_loopCounter].DCM_g_motPWMPinNumber,
            st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
            DIO_OUT);
			
		DIO_write(st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber0,
			st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
			DIO_U8_PIN_HIGH);
		DIO_write(st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPinNumber1,
			st_g_carMotors[u8_a_loopCounter].DCM_g_motEnPortNumber,
			DIO_U8_PIN_LOW);	
			
    }
//	}
    TIMER_ovfSetCallback(DCM_updateStopFlag);
    return DCM_OK;
}


/**
 * @brief Changes the direction of the motor rotation for the specified motor.
 *
 * @param en_a_motorNum The motor number whose direction needs to be changed.
 * @return EN_DCM_ERROR_T DCM_OK if the operation is successful, DCM_ERROR otherwise.
 */
EN_DCM_ERROR_T DCM_changeDCMDirection(EN_DCM_MOTORSIDE en_a_motorNum)
{
	//if (en_a_motorNum > 2)
		//return DCM_ERROR;
	//else
	//{

		DIO_toggle(st_g_carMotors[en_a_motorNum].DCM_g_motEnPinNumber0,
			st_g_carMotors[en_a_motorNum].DCM_g_motEnPortNumber
		);
		DIO_toggle(st_g_carMotors[en_a_motorNum].DCM_g_motEnPinNumber1,
			st_g_carMotors[en_a_motorNum].DCM_g_motEnPortNumber
		);
	//}
	return DCM_OK;
}

/**
 * @brief Stops the DC motors by setting the PWM output pins to low and resetting the stop flag.
 */
void DCM_stopDCM(void)
{
	DIO_write(st_g_carMotors[0].DCM_g_motPWMPinNumber, st_g_carMotors[0].DCM_g_motPWMPortNumber, DIO_U8_PIN_LOW);
	DIO_write(st_g_carMotors[1].DCM_g_motPWMPinNumber, st_g_carMotors[1].DCM_g_motPWMPortNumber, DIO_U8_PIN_LOW);
    en_g_stopFlag = FALSE;
}

/* ***********************************************************************************************/

/**
 * @brief Sets the duty cycle of the PWM for the motor.
 *
 * This function sets the duty cycle of the PWM for the motor. The duty cycle value
 * provided should be between 0 and 100, where 0 indicates a duty cycle of 0% and 100
 * indicates a duty cycle of 100%.
 *
 * @param u8_a_dutyCycleValue The duty cycle value for the motor.
 * @return EN_DCM_ERROR_T The error status of the function.
 *      - DCM_OK: The function executed successfully.
 *      - DCM_ERROR: The duty cycle value provided was out of range.
 */
EN_DCM_ERROR_T DCM_setDutyCycleOfPWM(u8 u8_a_dutyCycleValue)
{

	if (u8_a_dutyCycleValue > MAX_DUTY_CYCLE)
		return DCM_ERROR;
	else
	{
		u8 DCM_a_mappedDuty = u8_a_dutyCycleValue / PERIOD_TIME;
		u16 u16_onTime = DCM_a_mappedDuty;
		u16 u16_offTime = 10 - DCM_a_mappedDuty;

		while (en_g_stopFlag != TRUE && (u8_g_shutdownFlag == NULL || *u8_g_shutdownFlag == 0))
		{
			DIO_portWrite(st_g_carMotors[0].DCM_g_motEnPortNumber, DIO_U8_PORT_HIGH, DIO_MASK_BITS_0_1);
			TIMER_timer0Delay(u16_onTime);
			DIO_portWrite(st_g_carMotors[0].DCM_g_motEnPortNumber, DIO_U8_PORT_LOW, DIO_MASK_BITS_0_1);
			TIMER_timer0Delay(u16_offTime);
		}
		en_g_stopFlag = FALSE;
	}
    return DCM_OK;
}

/**
 * @brief Updates the stop flag.
 *
 * This function is called by the timer overflow callback function to update the stop flag.
 * It sets the `en_g_stopFlag` variable to TRUE, which is used by other functions to stop the
 * motor movement.
 */
void DCM_updateStopFlag(void)
{
	en_g_stopFlag = TRUE;
}

/**
 * @brief Rotates the DC motor.
 *
 * This function rotates the DC motor by changing its direction to right,
 * setting the duty cycle of the PWM signal to a predefined value,
 * and then changing the direction of the motor again to right.
 *
 * @return EN_DCM_ERROR_T DCM_OK if the operation is successful, DCM_ERROR otherwise.
 */
EN_DCM_ERROR_T DCM_rotateDCM()
{
    if(u8_g_shutdownFlag != NULL && *u8_g_shutdownFlag == 1) return DCM_ERROR;
	DCM_changeDCMDirection(MOTOR_RIGHT);
	DCM_setDutyCycleOfPWM (ROTATION_DUTY_CYCLE);
	DCM_changeDCMDirection(MOTOR_RIGHT);
    return DCM_OK;
}