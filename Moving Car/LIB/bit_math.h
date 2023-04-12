/*
 * bit_math.h
 *
 *  Created on: Apr 10, 2023
 *      Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER | ( 1 << BIT_NUMBER ) )
#define CLR_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER & ~( 1 << BIT_NUMBER ) )
#define TOG_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER ^ ( 1 << BIT_NUMBER ) )
#define GET_BIT( REGISTER, BIT_NUMBER )		( ( REGISTER & ( 1 << BIT_NUMBER ) ) >> BIT_NUMBER ) // ( ( REGISTER >> BIT_NUMBER ) & 1 )

#define WRITE_BIT(REGISTER,BIT_NUMBER, BIT_VAL) ((BIT_VAL) ? ((REGISTER) |= (1UL << (BIT_NUMBER))) : ((REGISTER) &= ~(1UL << (BIT_NUMBER))))
#endif /* BIT_MATH_H_ */
