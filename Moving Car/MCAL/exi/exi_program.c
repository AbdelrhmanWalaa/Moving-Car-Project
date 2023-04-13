/*
 * EXI_Program.c
 *
 *     Created on: Apr 25, 2021
 *         Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *    Description: This file contains all External Interrupt (EXI) functions' implementation,
 *                  and ISR functions' prototypes and implementation.
 *  MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */
 
/* MCAL */
#include "exi_private.h"
#include "exi_interface.h"

/* Declaration and Initialization */

/* Global Array of 3 Pointers to Functions ( because we have 3 External Interrupts ),
 * these functions ( in APP Layer ) which those 3 Pointers will hold their addresses;
 * are having void input arguments and void return type. */
static void ( *void_gs_apfInterrupstAction[3] ) ( void ) = { NULL, NULL, NULL };

/**
 * @brief The function enables a specific external interrupt with a specified sense control.
 * 
 * @param[in] u8_a_interruptId This is an input parameter of type u8 (unsigned 8-bit integer) that specifies the interrupt ID.
 * 			  It can have one of three values: EXI_U8_INT0, EXI_U8_INT1, or EXI_U8_INT2, which correspond to external interrupt,
 * @param[in] u8_a_senseControl This parameter is used to specify the sense control of the external interrupt.
 * 			  It can take one of the following values:
 * 
 * @return a u8 value which represents the error state. If the function executes successfully, it will
 * return STD_OK (0). If there is an error, it will return STD_NOK (1).
 */
u8 EXI_enablePIE	 ( u8 u8_a_interruptId, u8 u8_a_senseControl )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;
	
	/* Check 1: InterruptId and the Sense Control are in the valid range */
	if ( ( u8_a_interruptId <= EXI_U8_INT2 ) && ( u8_a_senseControl <= EXI_U8_SENSE_RISING_EDGE ) )
	{
		/* Check 1.1: Required InterruptId */
		switch ( u8_a_interruptId )
		{
			case EXI_U8_INT0:
				/* Enable Interrupt 0 */
				SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT0_BIT );

				/* Check 1.1.1: Required SenseControl */
				switch ( u8_a_senseControl )
				{
					case EXI_U8_SENSE_LOW_LEVEL		: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
					case EXI_U8_SENSE_LOGICAL_CHANGE: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
					case EXI_U8_SENSE_FALLING_EDGE	: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
					case EXI_U8_SENSE_RISING_EDGE	: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC00_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC01_BIT ); break;
				}
			break;

			case EXI_U8_INT1:
				/* Enable Interrupt 1 */
				SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT1_BIT );

				/* Check 1.1.2: Required SenseControl */
				switch( u8_a_senseControl)
				{
					case EXI_U8_SENSE_LOW_LEVEL		: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;
					case EXI_U8_SENSE_LOGICAL_CHANGE: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;
					case EXI_U8_SENSE_FALLING_EDGE	: CLR_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;
					case EXI_U8_SENSE_RISING_EDGE	: SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC10_BIT ); SET_BIT( EXI_U8_MCUCR_REG, EXI_U8_ISC11_BIT ); break;

				}
			break;

			case EXI_U8_INT2:
				/* Enable Interrupt 2 */
				SET_BIT( EXI_U8_GICR_REG, EXI_U8_INT2_BIT );

				/* Check 1.1.3: Required SenseControl */
				switch( u8_a_senseControl )
				{
					case EXI_U8_SENSE_FALLING_EDGE: CLR_BIT( EXI_U8_MCUCSR_REG, EXI_U8_ISC2_BIT ); break;
					case EXI_U8_SENSE_RISING_EDGE :	SET_BIT( EXI_U8_MCUCSR_REG, EXI_U8_ISC2_BIT ); break;
				}
			break;
		}
	}
	/* Check 2: InterruptId or the Sense Control is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptId or Sense Control! */
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;
}

/**
 * @brief The function disables a specified external interrupt.
 * 
 * @param[in] u8_a_interruptId The ID of the interrupt to be disabled. It should be a value between 0 and 2,
 * 			  where 0 represents INT0, 1 represents INT1, and 2 represents INT2.
 * 
 * @return a variable of type u8, which represents the error state of the function. It will return 
 * 		   STD_OK if the function executed successfully, and STD_NOK if there was an error (i.e. the interrupt
 * 		   ID is not in the valid range).
 */
u8 EXI_disablePIE    ( u8 u8_a_interruptId )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;
	
	/* Check 1: InterruptId is in the valid range */
	if ( u8_a_interruptId <= EXI_U8_INT2 )
	{
		/* Check 1.1: Required InterruptId */
		switch ( u8_a_interruptId )
		{
			case EXI_U8_INT0: CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT0_BIT ); break;
			case EXI_U8_INT1: CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT1_BIT ); break;
			case EXI_U8_INT2: CLR_BIT( EXI_U8_GICR_REG, EXI_U8_INT2_BIT ); break;
		}
	}
	/* Check 2: InterruptId is not in the valid range */
	else
	{
		/* Update error state = NOK, wrong InterruptId! */
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;
}

/**
 * @brief function sets a callback function for a specific interrupt and returns an error state.
 * 
 * @param[in] u8_a_interruptId An unsigned 8-bit integer representing the ID of the interrupt. It should be in the range of 0 to 2, inclusive.
 * @param[in] pf_a_interruptAction A pointer to a function that will be executed when the specified interrupt occurs.
 * 
 * @return a u8 value which represents the error state. It can be either STD_OK (0) or STD_NOK (1).
 */
u8 EXI_intSetCallBack( u8 u8_a_interruptId, void ( *pf_a_interruptAction ) ( void ) )
{
	/* Define local variable to set the error state = OK */
	u8 u8_l_errorState = STD_OK;

	/* Check 1: InterruptId is in the valid range, and Pointer to Function is not equal to NULL */
	if( ( u8_a_interruptId <= EXI_U8_INT2 ) && ( pf_a_interruptAction != NULL ) )
	{
		/* Store the passed address of function ( in APP Layer ) through pointer to function
		 * ( INTInterruptAction ) into Global Array of Pointers to Functions ( INTInterruptsAction )
		 * in the passed index ( InterruptId ). */
		void_gs_apfInterrupstAction[u8_a_interruptId] = pf_a_interruptAction;
	}
	/* Check 2: InterruptId is not in the valid range, or Pointer to Function is equal to NULL */
	else
	{
		/* Update error state = NOK, wrong InterruptId, or Pointer to Function is NULL! */
		u8_l_errorState = STD_NOK;
	}
	
	return u8_l_errorState;
}


/**
 * ISR function prototypes for External Interrupt Request 0 ( INT0 )
 * */
void __vector_1( void )		__attribute__((signal));

/**
 * ISR function prototypes for External Interrupt Request 1 ( INT1 )
 * */
void __vector_2( void )		__attribute__((signal));

/**
 * ISR function prototypes for External Interrupt Request 2 ( INT2 )
 * */
void __vector_3( void )		__attribute__((signal));


/**
 * ISR function implementation of INT0
 * */
void __vector_1( void )
{
	/* Check: INT0 index of the Global Array is not equal to NULL */
	if ( void_gs_apfInterrupstAction[EXI_U8_INT0] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		void_gs_apfInterrupstAction[EXI_U8_INT0]();
	}	
}

/**
 * ISR function implementation of INT1
 * */
void __vector_2( void )
{
	/* Check: INT1 index of the Global Array is not equal to NULL */
	if( void_gs_apfInterrupstAction[EXI_U8_INT1] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		void_gs_apfInterrupstAction[EXI_U8_INT1]();
	}	
}


/**
 * ISR function implementation of INT2
 * */
void __vector_3( void )
{
	/* Check: INT2 index of the Global Array is not equal to NULL */
	if( void_gs_apfInterrupstAction[EXI_U8_INT2] != NULL )
	{
		/* Call Back the function ( in APP Layer ), which its address is stored in the Global Array of Pointers to Functions ( INTInterruptsAction ) */
		void_gs_apfInterrupstAction[EXI_U8_INT2]();
	}	
}