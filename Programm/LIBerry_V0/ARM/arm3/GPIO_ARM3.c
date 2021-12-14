#include "main.h"
//////////////////////////////////
#ifdef arm3
//////////////////////////////////
////#include "lcd.h"
//#include "string.h"
//#include "stdio.h"
//#include "GPIO_ARM3.h"
///////////////////////////////////////LED

#define LED1 6
#define LED2 7
//////////////////////////////////////

#define HIGE 0xFFFF;
#define LOW  0x0000;

int Array_CNF[8]  = {2, 6, 10, 14, 18, 22, 26, 30};
int Array_MODE[8] = {0, 4, 8 , 12, 16, 20, 24, 28};
#define D ((GPIO_TypeDef *)(0x40000000UL + 0x00010000UL) + 0x00001400UL) //GPIOD
//////////////////////////////////
void Alarm(GPIO_TypeDef *GPIOx)
{
	PIN_OUT(GPIOx,6);
	PIN_OUT(GPIOx,7);

	  while (1)
	  {
		  PIN_LOW(GPIOx,6);
		  PIN_LOW(GPIOx,7);
		  HAL_Delay(100);

		  PIN_HIGH(GPIOx,6);
		  PIN_HIGH(GPIOx,7);
		  HAL_Delay(100);
	  }
}
///////////////////////////////////////////////////////////////////////////////////
void clocking(void)
{
	RCC->APB2ENR |= rcca; //RCC_APB2ENR_IOPAEN; 103
	RCC->APB2ENR |= rccb; //RCC_APB2ENR_IOPBEN; 103
	RCC->APB2ENR |= rccc; //RCC_APB2ENR_IOPCEN; 103
	RCC->APB2ENR |= rccd; //RCC_APB2ENR_IOPDEN;	103
	RCC->APB2ENR |= rcce; //RCC_APB2ENR_IOPEEN; 103
	RCC->APB2ENR |= rccg; //RCC_APB2ENR_IOPEEN; 103

}
/////////////////////////////////////////////////////////////
// singl diode 6
void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED)
{
	PIN_OUT(GPIOx,LED);

		   PIN_HIGH(GPIOx,LED);
	//       GPIOx->BSRR = (1 << LED);  //i2//   горит
	       HAL_Delay(400);

		   PIN_LOW(GPIOx,LED);
      //    GPIOx->BRR = (1 << LED);  //i2//  не горит
           HAL_Delay(400);
}
void delay_nop(int Delay)
{
	for( uint8_t i=0; i<Delay; ++i) asm ( "nop" );
}

////////////////////////////////////////////////////////GPIO PORT
void PORT_HIGH(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = HIGE;   //записать 0xFFFF 1
}
// PORT_HIGE(GPIOD)
void PORT_LOW(GPIO_TypeDef *GPIOx)
{
	GPIOx->BRR = LOW;   //записать 0xFFFF 0
}
////////////////////////////////////////////////////////GPIO PIN
void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin)   //  PIn-> 1 (GPIOD, GPIO_Pin_0)
{
	GPIOx->BSRR = (uint16_t)(1<<Pin);  //1

//   GPIOx->BSRR = (uint32_t)GPIO_Pin << 16u;
//	 GPIOx->BRR =

}

void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin)   //
{
	GPIOx->BSRR = (uint32_t)(1<<Pin)<< 16U; //0
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/*
void pin_configuration( GPIO_TypeDef *GPIOx, uint16_t pin, uint16_t mask )
{
	if(pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(pin*4));
		GPIOx->CRL |= mask<<(pin*4);
	}
	if(pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<(pin*4));
		GPIOx->CRH |= mask<<(pin*4);
	}
}
*/
void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t pin)
{
//	pin_configuration(GPIOx, pin, 0x03 );

	if(pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(pin*4));  	//2
		GPIOx->CRL |= 0x03<<(pin*4); //mask  //2
	}
	if(pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<(pin*4));   //<<8U
		GPIOx->CRH |= 0x03<<(pin*4); //mask  <<8U
	}
}
void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t pin)
{
	//pin_configuration(GPIOx, pin, 0x04 );
	if(pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(pin*4));
		GPIOx->CRL |= 0x04<<(pin*4); //mask
	}
	if(pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<(pin*4));
		GPIOx->CRH |= 0x04<<(pin*4); //mask
	}

}

void PORT_IN(GPIO_TypeDef *GPIOx)
{
	GPIOx->CRL  = 0x44444444;
}

void PORT_OUT(GPIO_TypeDef *GPIOx)
{
	GPIOx->CRL  = 0x33333333;
}

void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data ;   //записать 0xFFFF 1
}

void PORT_Write8(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data & 0b0000000011111111;   //записать 0xFFFF 1
}
////////////////////// PORT_READ//////////////////////////////////////
///////////////////////////////////////////////////////////////
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx,uint16_t dat)
{
	//	uint16_t dat=0;
		dat=GPIOx->IDR;
    //	dat=(GPIOx->IDR & 0b1111111111111001);
	//	dat=(GPIOx->IDR & 0b1111111111111111);
	//	dat=(GPIOx->IDR & 0b1111111111111111);

	/*	uint16_t dat = (GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
		dat |= (GPIOE->IDR & 0xFF) << 8;
	*/

return dat;
}
_Bool READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin)  // считать с портов  2 байт
{
	uint16_t dat = GPIOx->IDR & (uint16_t)(1<<Pin);
//	(GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
//	dat |= (GPIOE->IDR & 0xFF) << 8;

	return dat;
}

uint8_t PORT_READ_8(GPIO_TypeDef *GPIOx,uint8_t dat)
{
	//	uint16_t dat=0;
		dat=GPIOx->IDR &  0b0000000011111111;
    //	dat=(GPIOx->IDR & 0b1111111111111001);
	//	dat=(GPIOx->IDR & 0b1111111111111111);
	//	dat=(GPIOx->IDR & 0b1111111111111111);

	/*	uint16_t dat = (GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
		dat |= (GPIOE->IDR & 0xFF) << 8;
	*/

return dat;
}


//////////////////////////////////////////////////////////

void system_GPIO()
{
	   __HAL_RCC_GPIOA_CLK_ENABLE();
	   __HAL_RCC_GPIOB_CLK_ENABLE();
	   __HAL_RCC_GPIOC_CLK_ENABLE();
	   __HAL_RCC_GPIOD_CLK_ENABLE();
	//   __HAL_RCC_GPIOE_CLK_ENABLE();
}


void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t Pin,uint16_t mode1,uint16_t mode2)  //  отключены  PA10-PA15 переферия
{
   GPIO_InitTypeDef gpioInitStruct; //= {0}

   PIN_LOW(GPIOx,Pin);
  // HAL_GPIO_WritePin(GPIOx,(((uint16_t)0x0001)*Pin), GPIO_PIN_RESET);
   gpioInitStruct.Pin =((uint16_t)0x0001)*(1<<Pin);

 //   gpioInitStruct.Pin =GPIO_PIN_6|GPIO_PIN_7;//PIN;    //
   gpioInitStruct.Mode = mode1; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = mode1;
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOx, &gpioInitStruct);  //
}


void GPIO_PORT_Mode(GPIO_TypeDef *GPIOx,uint16_t mode, uint16_t mode2)  //  отключены  PA10-PA15 переферия
{
   GPIO_InitTypeDef gpioInitStruct; //= {0}
//   PORT_LOW(GPIOx);
   gpioInitStruct.Pin = GPIO_PIN_All;//PIN;    //
   gpioInitStruct.Mode = mode; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = mode2; //GPIO_PULLDOWN
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOx, &gpioInitStruct);  //
}



uint16_t GPIO_Init()   /// Test All System
{
	uint16_t Error_All = 0;
	clocking();
	PIN_OUT(GPIOC,6);
	PIN_OUT(GPIOC,7);
    return Error_All;
}




void GPIO_Mode_A(uint16_t mode)  //    PA14,PA13 Serial
{

   GPIO_InitTypeDef gpioInitStruct;

   HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15, GPIO_PIN_RESET);
   gpioInitStruct.Pin =GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;//PIN;    //
   gpioInitStruct.Mode = mode; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = GPIO_NOPULL;
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOA, &gpioInitStruct);  //
}



void GPIO_OUT_B()  // В проекте PB2 => На земле.
{
   GPIO_InitTypeDef gpioInitStruct;
   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_15, GPIO_PIN_RESET);
   gpioInitStruct.Pin =GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_15;//PIN;    //
   gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = GPIO_NOPULL;
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOB, &gpioInitStruct);  //
}
/////////////////////////////////////////////////////////////////////////////////
void PINS_OUT(GPIO p)
{
//	pin_configuration(GPIOx, pin, 0x03 );

	if(p.PIN<=7)
	{
		p.GPIO->CRL &= ~(0x0f<<(p.PIN*4));  	//2
		p.GPIO->CRL |= 0x03<<(p.PIN*4); //mask  //2
	}
	if(p.PIN>7)
	{
		p.GPIO->CRH &= ~(0x0f<<(p.PIN*4)<<8U);
		p.GPIO->CRH |= 0x03<<(p.PIN*4)<<8U; //mask
	}
}

void PINS_HIGH(GPIO p)   //  PIn-> 1 (GPIOD, GPIO_Pin_0)
{
	p.GPIO->BSRR = (uint16_t)(1<<p.PIN);  //1
}

void PINS_LOW(GPIO p)   //
{
	p.GPIO->BSRR = (uint32_t)(1<<p.PIN)<< 16U; //0
}



#endif /* arm3 */
