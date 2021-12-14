#include "main.h"
#ifdef gpio_cpp

//#include "lcd.h"
//#include "string.h"
//#include "stdio.h"
//#include "GPIO_ARM3.h"
///////////////////////////////////////LED

#include "GPIO.hpp"
//#include "STM32F407xx.h"





void Alarm(GPIO_TypeDef GPIOx)
{

//    GPIO_PIN_Mode(GPIOA,6,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);
//	  GPIO_PIN_Mode(GPIOA,7,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	  while (1)
	  {
//		  PIN_LOW(GPIOA,6);
//		  PIN_LOW(GPIOA,7);
//		  HAL_Delay(100);
//
//		  PIN_HIGH(GPIOA,6);
//		  PIN_HIGH(GPIOA,7);
//		  HAL_Delay(100);

	  }
}

////////////////////////////////////////////////////////GPIO PIN
void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin)   //  PIn-> 1 (GPIOD, GPIO_Pin_0)
{
	GPIOx->BSRR = (uint16_t)(1<<Pin);  //1
}

void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin)   //
{
	GPIOx->BSRR = (uint32_t)(1<<Pin)<< 16U; //0
}

////////////////////////////////////////////////////////// PIN
void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin)    /// PIn-> OUT  (GPIOD,5)
{

//	GPIOx-> MODER |= 0x1UL << (Pin*2UL);
	if(Pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(Pin*4));  	//2
		GPIOx->CRL |= 0x03<<(Pin*4); //mask  //2
	}
	if(Pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<(Pin*4)-8U);
		GPIOx->CRH |= 0x03<<(Pin*4)-8U; //mask
	}

}

void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin)    /// PIn-> OUT  (GPIOD,5)
{
//	GPIOx->MODER &= ~ (0x1UL << (Pin)*2UL)<< 16U;

	//pin_configuration(GPIOx, pin, 0x04 );
	if(Pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(Pin*4));
		GPIOx->CRL |= 0x04<<(Pin*4); //mask
	}
	if(Pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<(Pin*4));
		GPIOx->CRH |= 0x04<<(Pin*4); //mask
	}
}

void delay_nop(int Delay)
{
	for( uint8_t i=0; i<Delay; ++i) asm ( "nop" );
}
#endif /* uart_rs485 */
