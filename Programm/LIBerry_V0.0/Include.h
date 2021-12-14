#include "main.h"

 #ifndef _include_H
 #define _include_H

/////////////////////////////////////////////

#ifdef GPIO_ARM3
	#include "GPIO_ARM3.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef UART_RS485
	#include "UART_RS485.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef lcd
	#include "lcd.h"
#endif /* HAL_RCC_MODULE_ENABLED */



#endif /* LED_H */
