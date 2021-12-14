/* $Id: delay_basic.h,v 1.1 2007/05/13 21:23:20 joerg_wunsch Exp $ */

#ifndef _UTIL_DELAY_BASIC_H_
#define _UTIL_DELAY_BASIC_H_ 1

#include <inttypes.h>



#if !defined(__DOXYGEN__)
static inline void _delay_loop_1(uint8_t __count) __attribute__((always_inline));
static inline void _delay_loop_2(uint16_t __count) __attribute__((always_inline));
#endif


void _delay_loop_1(uint8_t __count)
{
	asm volatile (
		"1: dec %0" "\n\t"
		"brne 1b"
		: "=r" (__count)
		: "0" (__count)
	);
}


void _delay_loop_2(uint16_t __count)
{

////	asm ( "nop" );
//	asm  ("1: sbiw %0,1" "\n\t"   //volatile
//				  "brne 1b"
//				  : "=w" (__count)
//			      : "0"  (__count)    );

//    asm volatile (
//        "1: sbiw %0,1" "\n\t"
//        "brne 1b"
//        : "=w" (__count)
//        : "0" (__count)
//    );

}

#endif /* _UTIL_DELAY_BASIC_H_ */
