/*
 * BTN_Program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Button (BTN) functions' implementation.
 */

/* HAL */
#include "btn_config.h"
#include "btn_interface.h"

/*******************************************************************************************************************************************************************/
/*
 Name: BTN_u8GetBTNState
 Input: u8 BTNId and Pointer to u8 ReturnedBTNState
 Output: u8 Error or No Error
 Description: Function to get BTN state.
*/
u8 BTN_u8GetBTNState( u8 Cpy_u8BTNId, u8 *Cpy_pu8ReturnedBTNState )
{
	/* Define local variable to set the error state = OK */
	u8 Loc_u8ErrorState = STD_OK;
	
	/* Check 1: BTNId is in the valid range, and Pointer is not equal to NULL */
	if ( ( Cpy_u8BTNId <= BTN_U8_8 ) && ( Cpy_pu8ReturnedBTNState != NULL ) )
	{
		/* Check 1.1: Required BTNId */
		switch( Cpy_u8BTNId )
		{
			case BTN_U8_1: DIO_read( BTN_U8_1_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_2: DIO_read( BTN_U8_2_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_3: DIO_read( BTN_U8_3_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_4: DIO_read( BTN_U8_4_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_5: DIO_read( BTN_U8_5_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_6: DIO_read( BTN_U8_6_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_7: DIO_read( BTN_U8_7_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
			case BTN_U8_8: DIO_read( BTN_U8_8_PIN, BTN_U8_PORT, Cpy_pu8ReturnedBTNState ); break;
		}		
	}
	/* Check 2: BTNId is not in the valid range, or Pointer is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong BTNId or Pointer is NULL! */
		Loc_u8ErrorState = STD_NOK;
	}
		
	return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/