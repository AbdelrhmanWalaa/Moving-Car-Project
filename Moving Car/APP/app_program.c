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
		//LED_vdInitialization();
		
		/* MCAL Initialization */
		GLI_vdEnableGIE();
		
		EXI_u8INTSetCallBack( EXI_U8_INT0, &APP_stopCar );
		EXI_u8EnablePIE( EXI_U8_INT0, EXI_U8_SENSE_FALLING_EDGE );
		
		EXI_u8INTSetCallBack( EXI_U8_INT1, &APP_startCar );
		EXI_u8EnablePIE( EXI_U8_INT1, EXI_U8_SENSE_FALLING_EDGE );	
}

/*******************************************************************************************************************************************************************/
/*

*/
void APP_startProgram  ( void )
{
	/* Toggle forever */
	while(1)
	{	
		switch( u8_gs_appMode )
		{
			case APP_CAR_STOP:
			
				// stop Car
				
				break;
				
			case APP_CAR_START:
				
				// delay 1 sec.
				// start Car
				
				u8_gs_appMode = APP_CAR_MOVE_FWD_LD;
				break;
			
			case APP_CAR_MOVE_FWD_LD:
				
				// move fwd for 3 sec. with duty cycle 50%
				
				u8_gs_appMode = APP_CAR_ROT_90_DEG;
				break;
				
			case APP_CAR_ROT_90_DEG:
				
				// delay 0.5 sec.
				// rotate 90 degrees
				// delay 0.5 sec.
			
				u8_gs_appMode = APP_CAR_MOVE_FWD_SD;
				break;
				
			case APP_CAR_MOVE_FWD_SD:
							
				// move fwd for 2 sec. with duty cycle 30%
							
				u8_gs_appMode = APP_CAR_ROT_90_DEG;
				break;
		}
	}
}

/*******************************************************************************************************************************************************************/
/*

*/
void APP_startCar	   ( void )
{
	u8_gs_appMode = APP_CAR_START	
}

/*******************************************************************************************************************************************************************/
/*

*/
void APP_stopCar	   ( void )
{
	u8_gs_appMode = APP_CAR_STOP;	
}

/*******************************************************************************************************************************************************************/
