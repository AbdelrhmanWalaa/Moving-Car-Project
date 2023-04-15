/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_H_
#define APP_H_

/* ***********************************************************************************************/
/* APP Includes */
/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"

/* MCAL */
#include "../MCAL/dio/dio_interface.h"
#include "../MCAL/gli/gli_interface.h"
#include "../MCAL/exi/exi_interface.h"
#include "../MCAL/timer/timer_interface.h"

/* HAL */
#include "../HAL/btn/btn_interface.h"
#include "../HAL/led/led_interface.h"
#include "../HAL/dcm/dcm_interface.h"

/* ***********************************************************************************************/
/* APP Macros */

/* APP Modes */
#define APP_CAR_STOP			0
#define APP_CAR_START			1
#define APP_CAR_MOVE_FWD_LD		2
#define APP_CAR_ROT_90_DEG		3
#define APP_CAR_MOVE_FWD_SD		4

/* Diagonals Values */
#define APP_SHORT_DGNL			0
#define APP_LONG_DGNL			1

/* ***********************************************************************************************/
/* APP Functions' Prototypes */

/**
 * @brief Initializes the application by initializing MCAL and HAL.
 * This function initializes the General Interrupt Enable (GIE), sets up callback functions
 * for interrupt service routines, initializes the timers and buttons, initializes an LED array,
 * initializes the DC motor, and sets the application mode to "Car Stop".
 * @return None
 */
void APP_initialization( void );

/**
 * @brief This function starts the car program and keeps it running indefinitely.
 * The function uses a while loop to continuously check for the required app mode.
 * The app mode is checked using a switch statement, which contains various cases
 * that correspond to the different modes of operation for the car program. Each
 * case contains a series of steps to be executed to perform the desired action
 * for that mode.
 * @return void
 * */
void APP_startProgram  ( void );

/* ISR Callback function for starting the car */
void APP_startCar	   ( void );

/* ISR Callback function for stopping the car immediately */
void APP_stopCar	   ( void );

/* ***********************************************************************************************/

#endif /* APP_H_ */