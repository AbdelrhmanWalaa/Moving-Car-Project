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

/**
 * @brief Initialize the DC Motors by initializing their pins.
 *
 * @param u8_a_shutdownFlag Pointer to the Shutdown flag variable that acts as a main kill switch.
 *
 * @return EN_DCM_ERROR_T Returns DCM_OK if initialization is successful, or DCM_ERROR if initialization failed.
 *
 */
EN_DCM_ERROR_T DCM_motorInit(u8 ** u8_a_shutdownFlag);


/**
 * @brief Rotates the DC motor.
 *
 * This function rotates the DC motor by changing its direction to right,
 * setting the duty cycle of the PWM signal to a predefined value,
 * and then changing the direction of the motor again to right.
 *
 * @return EN_DCM_ERROR_T DCM_OK if the operation is successful, DCM_ERROR otherwise.
 */
EN_DCM_ERROR_T DCM_rotateDCM(void);


/**
 * @brief Changes the direction of the motor rotation for the specified motor.
 *
 * @param en_a_motorNum The motor number whose direction needs to be changed.
 * @return EN_DCM_ERROR_T DCM_OK if the operation is successful, DCM_ERROR otherwise.
 */
EN_DCM_ERROR_T DCM_changeDCMDirection(EN_DCM_MOTORSIDE en_a_motorNum);

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
EN_DCM_ERROR_T DCM_setDutyCycleOfPWM(u8 u8_a_dutyCycleValue);

/**
 * @brief Stops the DC motors by setting the PWM output pins to low and resetting the stop flag.
 */
void DCM_stopDCM(void);

/**
 * @brief Updates the stop flag.
 *
 * This function is called by the timer overflow callback function to update the stop flag.
 * It sets the `en_g_stopFlag` variable to TRUE, which is used by other functions to stop the
 * motor movement.
 */
void DCM_updateStopFlag(void);

//u8 DCM_u8GetDutyCycleOfPWM(u8* Cpy_pu8ReturnedDutyCycleValue);
/* ***********************************************************************************************/

/* ***********************************************************************************************/

#endif /* DCM_INTERFACE_H_ */