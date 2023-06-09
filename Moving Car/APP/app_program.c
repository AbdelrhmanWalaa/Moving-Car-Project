/*
 * app_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 *  Description: This file contains all Application (APP) functions' implementation.
 */

/* APP */
#include "app_config.h"
#include "app_interface.h"

/* *******************************************************************************************************************/

/* Declaration and Initialization */

/* Global variable to store appMode */
static u8 u8_gs_appMode = APP_CAR_STOP;
static u8 u8_gs_diagonalFlag = APP_LONG_DGNL;

u8 u8_g_suddenBreakFlag = APP_BREAK_FLAG_DOWN;
u8 *u8Ptr_g_suddenBreakPtr = &u8_g_suddenBreakFlag;

/* *******************************************************************************************************************/

/**
* @brief Initializes the application by initializing MCAL and HAL.
* This function initializes the General Interrupt Enable (GIE), sets up callback functions
* for interrupt service routines, initializes the timers and buttons, initializes an LED array,
* initializes the DC motor, and sets the application mode to "Car Stop".
* @return None
*/
void APP_initialization(void)
{
	/* MCAL Initialization */
	GLI_enableGIE();

	EXI_intSetCallBack( EXI_U8_INT0, &APP_stopCar );
	EXI_enablePIE( EXI_U8_INT0, EXI_U8_SENSE_FALLING_EDGE );

	EXI_intSetCallBack( EXI_U8_INT1, &APP_startCar );
	EXI_enablePIE( EXI_U8_INT1, EXI_U8_SENSE_FALLING_EDGE );

	TIMER_timer0NormalModeInit( DISABLED, &u8Ptr_g_suddenBreakPtr);
	TIMER_timer2NormalModeInit( ENABLED, &u8Ptr_g_suddenBreakPtr);
	
	/* HAL Initialization */
	BTN_init( APP_STOP_BTN , PORT_D );
	BTN_init( APP_START_BTN, PORT_D );
	LED_arrayInit( PORT_A, DIO_MASK_BITS_0_1_2_3 );
	DCM_motorInit(&u8Ptr_g_suddenBreakPtr);
	
	u8_gs_appMode = APP_CAR_STOP;
}

/**
 * @brief This function starts the car program and keeps it running indefinitely.
 * The function uses a while loop to continuously check for the required app mode.
 * The app mode is checked using a switch statement, which contains various cases
 * that correspond to the different modes of operation for the car program. Each
 * case contains a series of steps to be executed to perform the desired action
 * for that mode.
 * @return void
 * */
void APP_startProgram(void)
{
    /* Toggle forever */
    while (1)
	 {
		/* Check 1: Required appMode */
        switch ( u8_gs_appMode )
		{
            case APP_CAR_STOP:

				/* Step A1: Turn on red LED, and turn off other LEDs */
				LED_arrayOff( PORT_A, DIO_MASK_BITS_0_1_2 );
				LED_on( PORT_A, APP_STOP_LED );
				/* Step A2: Stop both motors */
				DCM_stopDCM();

				break;

            case APP_CAR_START:
			
                /* Step B1: Delay 1 sec. */
                TIMER_timer0Delay( APP_STARTING_DELAY );

				/* Check 1.1: appMode is not "CAR_STOP" mode */
                if ( u8_gs_appMode != APP_CAR_STOP )
				{
					/* Step B2: Update appMode to "CAR_MOVE_FWD_LD" mode */
                    u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
                }
                break;

            case APP_CAR_MOVE_FWD_LD:
			
				/* Step C1: Update diagonalFlag to "LONG_DGNL" */
				u8_gs_diagonalFlag = APP_LONG_DGNL;
                /* Step C2: Turn on green(LD) LED, and turn off other LEDs */
				LED_arrayOff( PORT_A, DIO_MASK_BITS_1_2_3 );
				LED_on( PORT_A, APP_MOVE_FWD_LD_LED );
				/* Step C3: Car moves for 3 sec. with 50% of speed */
				TIMER_timer2Delay( APP_FWD_LD_DURATION );
				DCM_setDutyCycleOfPWM( APP_FWD_LD_DUTY );
				DCM_stopDCM();

				/* Check 1.2: appMode is not "CAR_STOP" mode */
                if ( u8_gs_appMode != APP_CAR_STOP )
				{
					/* Step C4: Update appMode to "CAR_ROT_90_DEG" mode */
                    u8_gs_appMode = APP_CAR_ROT_90_DEG;
                }
                break;

            case APP_CAR_ROT_90_DEG:

				/* Step D1: Turn on yellow LED, and turn off other LEDs */
               	LED_arrayOff( PORT_A, DIO_MASK_BITS_0_1_3 );
				LED_on( PORT_A, APP_ROTATE_LED );
                /* Step D2: Delay 0.5 sec. */
                TIMER_timer0Delay( APP_ROTATION_DELAY );
				/* Step D3: Car rotates for 620 msec. with 50% of speed */
                TIMER_timer2Delay( APP_ROTATION_DURATION );
				DCM_rotateDCM();
				DCM_stopDCM();
                /* Step D4: Delay 0.5 sec. */
                TIMER_timer0Delay( APP_ROTATION_DELAY );

				/* Check 1.3: appMode is not "CAR_STOP" mode */
                if ( u8_gs_appMode != APP_CAR_STOP )
				{
					/* Step D5: Update appMode to "CAR_MOVE_FWD_SD" or "CAR_MOVE_FWD_LD" modes */
					/* Check 1.3.1: Required diagonalFlag  */
					switch ( u8_gs_diagonalFlag )
					{
						case APP_SHORT_DGNL:
							u8_gs_appMode = APP_CAR_MOVE_FWD_LD; 
							break;
						case APP_LONG_DGNL : 
							u8_gs_appMode = APP_CAR_MOVE_FWD_SD; 
							break;
						default: 
							 u8_gs_diagonalFlag = APP_LONG_DGNL; 
							u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
					}					
                }
                break;

            case APP_CAR_MOVE_FWD_SD:
				
				/* Step E1: Update diagonalFlag to "SHORT_DGNL" */
				u8_gs_diagonalFlag = APP_SHORT_DGNL;				
				/* Step E2: Turn on green(SD) LED, and turn off other LEDs */
                LED_arrayOff( PORT_A, DIO_MASK_BITS_0_2_3 );
                LED_on( PORT_A, APP_MOVE_FWD_SD_LED );
                /* Step E3: Car moves for 2 sec. with 30% of speed */
                TIMER_timer2Delay( APP_FWD_SD_DURATION );
				DCM_setDutyCycleOfPWM( APP_FWD_SD_DUTY );

				/* Check 1.4: appMode is not "CAR_STOP" mode */
                if ( u8_gs_appMode != APP_CAR_STOP )
				{
					/* Step E4: Update appMode to "CAR_ROT_90_DEG" mode */
                    u8_gs_appMode = APP_CAR_ROT_90_DEG;
                }
                break;
				
            default:
                u8_gs_appMode = APP_CAR_STOP;
				u8_gs_diagonalFlag = APP_LONG_DGNL;
                break;
        }
    }
}

/* ISR Callback function for starting the car */
void APP_startCar( void )
{
    if(u8_gs_appMode != APP_CAR_STOP) return;
	/* Update appMode to "CAR_START" mode */
    u8_gs_diagonalFlag = APP_LONG_DGNL;
    u8_g_suddenBreakFlag = APP_BREAK_FLAG_DOWN;
    u8_gs_appMode = APP_CAR_START;
}

/* ISR Callback function for stopping the car immediately */
void APP_stopCar( void )
{
	/* Update appMode to "CAR_STOP" mode */
    u8_g_suddenBreakFlag = APP_BREAK_FLAG_UP;
    u8_gs_appMode = APP_CAR_STOP;
}