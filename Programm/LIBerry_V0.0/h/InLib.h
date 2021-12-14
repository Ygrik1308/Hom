#ifndef InLib_H
#define InLib_H

//#define GPIO_ARM4   					//


#define string							//
#define stdio							//
//#define lcd		    					// LSD

//#define UART_RS485		    			// UART - > COMP

//#define hal_ARM4


//////////////////////////////////////////////////chip
//#define MX60LF8G18AC
//#define K9F1G08U0B



//////////////////////////////////////////////////////////////////
 #ifdef   hal_ARM3
 #include "stm32f1xx_hal.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   hal_ARM4
 #include "stm32f4xx_hal.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   hal_ARM7
 #include "stm32f7xx_hal.h"
 #endif /* HAL_RCC_MODULE_ENABLED */


//////////////////////////////////////////////////////////////////
 #ifdef   K9F1G08U0B
 #include "K9F1G08U0B.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   MX60LF8G18AC
 #include "MX60LF8G18AC.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 ////////////////////////////////////////////
 #ifdef   GPIO_ARM4
 #include "GPIO_ARM4.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   GPIO_ARM3
 #include "GPIO_ARM3.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   GPIO_ARM7
 #include "GPIO_ARM7.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   string
 #include "string.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   stdio
 #include "stdio.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   lcd
 #include "lcd.h"
 #endif /* HAL_RCC_MODULE_ENABLED */

 #ifdef   UART_RS485
 #include "UART_RS485.h"
 #endif /* HAL_RCC_MODULE_ENABLED */



#endif /* __MAIN_H */
