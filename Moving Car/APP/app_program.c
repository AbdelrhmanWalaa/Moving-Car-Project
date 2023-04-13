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

/*******************************************************************************************************************************************************************/
/* Declaration and Initialization */

/* Global variable to store appMode */
static u8 u8_gs_appMode = APP_CAR_STOP;

/*******************************************************************************************************************************************************************/ 
/*

*/
void APP_initialization( void )
{
	/* HAL Initialization */
	LED_arrayInit( PORT_A, DIO_MASK_BITS_0_1_2_3 );

	/* MCAL Initialization */
	GLI_enableGIE();
		
	EXI_intSetCallBack( EXI_U8_INT0, &APP_stopCar );
	EXI_enablePIE( EXI_U8_INT0, EXI_U8_SENSE_FALLING_EDGE );
		
	EXI_intSetCallBack( EXI_U8_INT1, &APP_startCar );
	EXI_enablePIE( EXI_U8_INT1, EXI_U8_SENSE_FALLING_EDGE );
		
	TMR_tmr0NormalModeInit( DISABLED );
}



void APP_startProgram  ( void )
{
	/* Toggle forever */
	while(1)
	{	
		switch( u8_gs_appMode )
		{
			case APP_CAR_STOP:
			
				// stop Car
				LED_arrayOn( PORT_A, DIO_MASK_BITS_3 );
								
				break;
				
			case APP_CAR_START:
				
				// delay 1 sec.
				TMR_tmr0Delay( 1000 );
				// start Car
				
				if ( u8_gs_appMode != APP_CAR_STOP )
				{
					u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
				}
				break;
			
			case APP_CAR_MOVE_FWD_LD:
				
				LED_arrayOn( PORT_A, DIO_MASK_BITS_0 );
				// move fwd for 3 sec. with duty cycle 50%
				//DCM_rotateDCM()
				
				if ( u8_gs_appMode != APP_CAR_STOP )
				{
					u8_gs_appMode = APP_CAR_ROT_90_DEG;
				}
				break;
				
			case APP_CAR_ROT_90_DEG:
				
				LED_arrayOn( PORT_A, DIO_MASK_BITS_2 );
				// delay 0.5 sec.
				TMR_tmr0Delay( 500 );
				
				// rotate 90 degrees
				TMR_tmr0Delay( 620 );
				
				// delay 0.5 sec.
				TMR_tmr0Delay( 500 );
				
				if ( u8_gs_appMode != APP_CAR_STOP )
				{
					u8_gs_appMode = APP_CAR_MOVE_FWD_SD;
				}				
				break;
				
			case APP_CAR_MOVE_FWD_SD:
				
				LED_arrayOn( PORT_A, DIO_MASK_BITS_1 );
				
				// move fwd for 2 sec. with duty cycle 30%
				TMR_tmr0Delay( 2000 );
				
				if ( u8_gs_appMode != APP_CAR_STOP )
				{		
					u8_gs_appMode = APP_CAR_ROT_90_DEG;
				}
				break;
		}
	}
}


void APP_startCar	   ( void )
{
	u8_gs_appMode = APP_CAR_START;	
}


void APP_stopCar	   ( void )
{
	u8_gs_appMode = APP_CAR_STOP;
}