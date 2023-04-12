/*
 * app_interface.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 *  Description: This file contains all Application (APP) functions' prototypes and definitions (Macros) to avoid magic numbers.
 */ 

#ifndef APP_H_
#define APP_H_

/*******************************************************************************************************************************************************************/
/* APP Includes */
/* LIB */
#include "../LIB/std.h"
#include "../LIB/bit_math.h"

/* MCAL */
#include "../MCAL/gli/gli_interface.h"
#include "../MCAL/exi/exi_interface.h"
#include "../MCAL/timer/timer_interface.h"

/* HAL */
#include "../HAL/led/led_interface.h"
#include "../HAL/dcm/dcm_interface.h"

/*******************************************************************************************************************************************************************/
/* APP Macros */

/* APP Modes */
#define APP_CAR_STOP			0
#define APP_CAR_START			1
#define APP_CAR_MOVE_FWD_LD		2
#define APP_CAR_ROT_90_DEG		3
#define APP_CAR_MOVE_FWD_SD		4

/*******************************************************************************************************************************************************************/
/* APP Functions' Prototypes */

void APP_initialization( void );
void APP_startProgram  ( void );
void APP_startCar	   ( void );
void APP_stopCar	   ( void );

/*******************************************************************************************************************************************************************/

#endif /* APP_H_ */