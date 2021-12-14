#ifndef H_DELAY_H_
#define H_DELAY_H_



#define _UTIL_DELAY_H_ 1

#ifndef __DOXYGEN__
#  ifndef __HAS_DELAY_CYCLES
#    define __HAS_DELAY_CYCLES 1
#  endif
#endif  /* __DOXYGEN__ */

#include <inttypes.h>
#include <delay_basic.h>
#include <math.h>



#if !defined(__DOXYGEN__)
static __inline__ void _delay_us(double __us) __attribute__((__always_inline__));
static __inline__ void _delay_ms(double __ms) __attribute__((__always_inline__));
#endif

#ifndef F_CPU
/* prevent compiler error by supplying a default */
#warning "F_CPU not defined for <util/delay.h>"
#define F_CPU 1000000UL
#endif

#ifndef __OPTIMIZE__
# warning "Compiler optimizations disabled; functions from <util/delay.h> won't work as designed"
#endif

#if __HAS_DELAY_CYCLES && defined(__OPTIMIZE__) && \
  !defined(__DELAY_BACKWARD_COMPATIBLE__) &&	   \
  __STDC_HOSTED__
#  include <math.h>
#endif


void
_delay_ms(double __ms)
{
	double __tmp ;
#if __HAS_DELAY_CYCLES && defined(__OPTIMIZE__) && \
  !defined(__DELAY_BACKWARD_COMPATIBLE__) &&	   \
  __STDC_HOSTED__
	uint32_t __ticks_dc;
	extern void __builtin_avr_delay_cycles(unsigned long);
	__tmp = ((F_CPU) / 1e3) * __ms;

	#if defined(__DELAY_ROUND_DOWN__)
		__ticks_dc = (uint32_t)fabs(__tmp);

	#elif defined(__DELAY_ROUND_CLOSEST__)
		__ticks_dc = (uint32_t)(fabs(__tmp)+0.5);

	#else
		//round up by default
		__ticks_dc = (uint32_t)(ceil(fabs(__tmp)));
	#endif

	__builtin_avr_delay_cycles(__ticks_dc);

#else
	uint16_t __ticks;
	__tmp = ((F_CPU) / 4e3) * __ms;
	if (__tmp < 1.0)
		__ticks = 1;
	else if (__tmp > 65535)
	{
		//	__ticks = requested delay in 1/10 ms
		__ticks = (uint16_t) (__ms * 10.0);
		while(__ticks)
		{
			// wait 1/10 ms
			_delay_loop_2(((F_CPU) / 4e3) / 10);
			__ticks --;
		}
		return;
	}
	else
		__ticks = (uint16_t)__tmp;
	_delay_loop_2(__ticks);
#endif
}


void _delay_us(double __us)
{
	double __tmp ;
#if __HAS_DELAY_CYCLES && defined(__OPTIMIZE__) && \
  !defined(__DELAY_BACKWARD_COMPATIBLE__) &&	   \
  __STDC_HOSTED__
	uint32_t __ticks_dc;
	extern void __builtin_avr_delay_cycles(unsigned long);
	__tmp = ((F_CPU) / 1e6) * __us;

	#if defined(__DELAY_ROUND_DOWN__)
		__ticks_dc = (uint32_t)fabs(__tmp);

	#elif defined(__DELAY_ROUND_CLOSEST__)
		__ticks_dc = (uint32_t)(fabs(__tmp)+0.5);

	#else
		//round up by default
		__ticks_dc = (uint32_t)(ceil(fabs(__tmp)));
	#endif

	__builtin_avr_delay_cycles(__ticks_dc);

#else
	uint8_t __ticks;
	double __tmp2 ;
	__tmp = ((F_CPU) / 3e6) * __us;
	__tmp2 = ((F_CPU) / 4e6) * __us;
	if (__tmp < 1.0)
		__ticks = 1;
	else if (__tmp2 > 65535)
	{
		_delay_ms(__us / 1000.0);
	}
	else if (__tmp > 255)
	{
		uint16_t __ticks=(uint16_t)__tmp2;
		_delay_loop_2(__ticks);
		return;
	}
	else
		__ticks = (uint8_t)__tmp;
	_delay_loop_1(__ticks);
#endif
}


#endif /* _UTIL_DELAY_H_ */


