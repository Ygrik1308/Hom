#include "main.h"
////////////////////////////////////////////
#if defined arm3    // Controller
///////////////////////////////////////////
#include "lcd.h"


#include "string.h"
#include "stdio.h"
#include "lcd.h"


int Array_CNF[8]  = {2, 6, 10, 14, 18, 22, 26, 30};
int Array_MODE[8] = {0, 4, 8 , 12, 16, 20, 24, 28};
#define D ((GPIO_TypeDef *)(0x40000000UL + 0x00010000UL) + 0x00001400UL) //GPIOD

void Alarm_PIN()
{
//LED.LED0 = {};
//LED.LED_GND = {GPIOD,8};

	PIN_OUT(GPIOD,9);
	PIN_OUT(GPIOD,8);

	PIN_LOW(GPIOD,8);


  while (1)
  {
		  PIN_HIGH(GPIOD,9);
		  HAL_Delay(100);

		  PIN_LOW(GPIOD,9);
		  HAL_Delay(100);
  }
}


void OK()
{
//LED.LED0 = {};
//LED.LED_GND = {GPIOD,8};
	  while (1)
	  {
	PIN_OUT(GPIOD,9);
	PIN_OUT(GPIOD,8);

	PIN_LOW(GPIOD,8);
	PIN_HIGH(GPIOD,9);
	  }
}


void Alarm(GPIO_TypeDef *GPIOx)
{
      GPIO_PIN_Mode(GPIOx,6,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);
	  GPIO_PIN_Mode(GPIOx,7,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

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
void Alarm_One(GPIO_TypeDef *GPIOx,uint16_t PIN)
{
  	  GPIO_PIN_Mode(GPIOx,PIN,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	  while (1)
	  {
		  PIN_LOW(GPIOx,PIN);
		  HAL_Delay(100);

		  PIN_HIGH(GPIOx,PIN);
		  HAL_Delay(100);
	  }
}

///////////////////////////////////////////////////////////////////////////////////
 // singl diode 6
void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED)
{
	       GPIO_PIN_Mode(GPIOx,LED,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	       GPIOx->BSRR = (1 << LED);  //i2//   горит
	       HAL_Delay(400);

           GPIOx->BRR = (1 << LED);  //i2//  не горит
           HAL_Delay(400);
}
void delay_nop(int Delay)
{
	for( uint8_t i=0; i<Delay; ++i) asm ( "nop" );
}



////////////////////////////////////////////////////////////////////////////////////////////////////PIN
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
void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t pin)
{

	if(pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(pin*4));
		GPIOx->CRL |= 0x03<<(pin*4);
	}
	if(pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<((pin-8U)<<2u)); //*4 ((pin<<16)*4))  //<<2u == *4
		GPIOx->CRH |= 0x03<<((pin-8U)<<2u);  //0x03
	}
	//pin_configuration(GPIOx, pin, 0x03 );
}
void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t pin)
{
	if(pin<=7)
	{
		GPIOx->CRL &= ~(0x0f<<(pin*4));
		GPIOx->CRL |= 0x04<<(pin*4);
	}
	if(pin>7)
	{
		GPIOx->CRH &= ~(0x0f<<((pin-8U)<<2u)); //*4 ((pin<<16)*4))  //<<2u == *4
		GPIOx->CRH |= 0x04<<((pin-8U)<<2u);  //0x03
	}
}

void PIN_DOWN(GPIO_TypeDef *GPIOx,uint16_t Pin)  // no verified
{
	if(Pin<=7)
	{
//	GPIOE->CRL &= ~GPIO_CRL_CNF0;
//	GPIOE->CRL |= GPIO_CRL_CNF0_1;
//	GPIOE->ODR &= ~GPIO_ODR_ODR0;
	}
	if(Pin>7)
	{
	GPIOE->CRL &= ~(0x3UL <<(Pin*4)<<2);
	GPIOE->CRL |=  (0x2UL <<(Pin*4)<<2);
	GPIOE->ODR |=  (0x1UL << Pin);
	}
}

void PIN_PP(GPIO_TypeDef *GPIOx,uint16_t Pin)   //verified
{
if(Pin<=7)
{

	GPIOx->CRL &= ~(0x3UL<<(Pin*4)<<2);
	GPIOx->CRL |=  (0x2UL<<(Pin*4)<<2);
	GPIOx->ODR |=  (0x1UL << Pin);
}
if(Pin>7)
{
	GPIOx->CRH &= ~(0x3UL<<(Pin-8u)*4<<2);    //((Port.P-8U)<<2u))
	GPIOx->CRH |=  (0x2UL<<(Pin-8u)*4<<2);
	GPIOx->ODR |=  (0x1UL << Pin);
}

}

_Bool READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin)  // считать с портов  2 байт
{
	_Bool dat = GPIOx->IDR & (uint16_t)(1<<Pin);
//	(GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
//	dat |= (GPIOE->IDR & 0xFF) << 8;

	return dat;
}
//////////////////////////////////////////////////////////////////////////////////PORT

void PORT_IN(GPIO_TypeDef *GPIOx)
{
	GPIOx->CRL  = 0x44444444;
	GPIOx->CRH  = 0x44444444;
}


void PORT_OUT(GPIO_TypeDef *GPIOx)
{
	GPIOx->CRL  = 0x33333333;
	GPIOx->CRH  = 0x33333333;
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

void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data ;   //записать 0xFFFF 1
}


void PORT_Write8(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data & 0b0000000011111111;   //записать 0xFFFF 1
}

void PORT_WriteRandom(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data ;   //записать 0xFFFF 1
	//GPIOx->ODR = (data & 0b0000000001111111)|((data & 0b0000000100000000)<<1) ;   //записать 0xFFFF 1
	//HAL_Delay(100);
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

uint8_t PORT_READ_8_RANDOM(GPIO_TypeDef *GPIOx,uint8_t dat)
{
	//	uint16_t dat=0;
	//	dat=GPIOx->IDR &  0b0000000011111111;
    //	dat=(GPIOx->IDR & 0b1111111111111001);
	//	dat=(GPIOx->IDR & 0b1111111111111111);
	//	dat=(GPIOx->IDR & 0b1111111111111111);

	    dat = (GPIOD->IDR & 0x7F) | ((GPIOD->IDR & 0x100)<<1);
	//	dat |= (GPIOE->IDR & 0xFF) << 8;


return dat;
}

uint16_t PORT_READ(GPIO_TypeDef *GPIOx,uint8_t bit)
{
		uint16_t data=0;
		uint16_t mask=0;

		switch (bit)
		{
		    case 1:
		    	mask = 0x1; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;
		    case 2:
		    	mask = 0x3; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0010
		        break;
		    case 3:
		    	mask = 0x7; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0010
		        break;
		    case 4:
		    	mask = 0xF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;
		    case 5:
		    	mask = 0x1F; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0010
		        break;
		    case 6:
		    	mask = 0x3F; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0010
		        break;
		    case 7:
		    	mask = 0x7F; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0010
		        break;
		    case 8:
		    	mask = 0xFF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 9:
		    	mask = 0x1FF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 10:
		    	mask = 0x3FF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 11:
		    	mask = 0x7FF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 12:
		    	mask = 0xFFF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 13:
		    	mask = 0x3FF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 14:
		    	mask = 0x7FF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;

		    case 15:
		    	mask = 0xFFFF; // Р вЂњРІР‚пїЅР вЂєРІР‚В Р вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР’В Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљР Р‹Р вЂњРЎвЂ™Р вЂ™Р вЂ¦Р вЂњРІР‚пїЅР Р†Р вЂљРІвЂћвЂ“Р вЂњРЎвЂ™Р вЂ™РІвЂћвЂ“ Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРЎвЂ™Р вЂ™РЎвЂ�Р вЂњРІР‚пїЅР Р†Р вЂљРЎв„ўР вЂњРЎвЂ™Р вЂ™Р’ВµР вЂњРІР‚пїЅР Р†РІР‚С™Р’В¬Р вЂњРЎвЂ™Р вЂ™Р’В°Р вЂњРЎвЂ™Р вЂ™Р’В» Р вЂњРЎвЂ™Р вЂ™РўвЂ�Р вЂњРЎвЂ™Р вЂ™Р’В»Р вЂњРІР‚пїЅР С—РЎвЂ”Р вЂ¦ 0000 0001
		        break;
		}

		data = (GPIOx->IDR & mask ); //& mask

	// dat = (GPIOD->IDR & 0x7F) | ((GPIOD->IDR & 0x100)<<1);
	// dat |= (GPIOE->IDR & 0xFF) << 8;


return data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void system_GPIO()
{
	   __HAL_RCC_GPIOA_CLK_ENABLE();
	   __HAL_RCC_GPIOB_CLK_ENABLE();
	   __HAL_RCC_GPIOC_CLK_ENABLE();
	   __HAL_RCC_GPIOD_CLK_ENABLE();
	   __HAL_RCC_GPIOE_CLK_ENABLE();

}


int GPIO_TEST() // Test GPIO OUT ON/OFF
{
	 uint16_t Io = 0;
	 uint16_t d  = 0;
     uint16_t test_read=0;
     uint32_t Error=0;
////////////////////////////////
 while(1)
{

 PORT_OUT(GPIOC);  // GPIO_MODE_INPUT
 PORT_IN(GPIOE);  // GPIO_MODE_INPUT

     test_read=0;
     Error=0;

 for(uint32_t dt=1;dt<=0x4000;dt=dt*2)   //14 bit
 {
	 PORT_Data(GPIOC,dt);
	 HAL_Delay(300);
//	 test_read = PORT_READ(GPIOE,15);
//	 if(test_read!=dt)
//	 {
//		 Error=Error+1;
//	 }
 }
    printf("Error_C: %u\n", Error);

    PORT_IN(GPIOC);  // GPIO_MODE_INPUT
    PORT_OUT(GPIOE);  // GPIO_MODE_INPUT
    test_read=0;
    Error=0;

	for(uint32_t dt=1;dt<=0x10000;dt=dt*2)    //16 bit
	{
		PORT_Data(GPIOE,dt);  //dt
		HAL_Delay(300);
//	 test_read = PORT_READ(GPIOE,15);
//	 if(test_read!=dt)
//	 {
//		 Error=Error+1;
//	 }
	}
    printf("Error_E: %u\n", Error);

    PORT_IN(GPIOA);  // GPIO_MODE_INPUT
    PORT_OUT(GPIOB);  // GPIO_MODE_INPUT
    test_read=0;
    Error=0;

	for(uint32_t dt=1;dt<=0x10000;dt=dt*2)    //16 bit
	{
		PORT_Data(GPIOB,dt);  //dt
		HAL_Delay(300);
//	 test_read = PORT_READ(GPIOE,15);
//	 if(test_read!=dt)
//	 {
//		 Error=Error+1;
//	 }
	}
    printf("Error_B: %u\n", Error);

    PORT_OUT(GPIOA);  // GPIO_MODE_INPUT
    PORT_IN(GPIOB);  // GPIO_MODE_INPUT
    test_read=0;
    Error=0;

	for(uint32_t dt=1;dt<=0x10000;dt=dt*2)    //16 bit
	{
		PORT_Data(GPIOA,dt);  //dt
		HAL_Delay(300);
//	 test_read = PORT_READ(GPIOE,15);
//	 if(test_read!=dt)
//	 {
//		 Error=Error+1;
//	 }
	}
    printf("Error_A: %u\n", Error);
}






// d = PORT_READ_16(GPIOC);
//    if( d==65535)
//    {
//  	  Io=1;
//    }
//
//    d = PORT_READ_16(GPIOD);
//    if( d==65535)
//    {
//  	  Io=Io+1;
//    }
//
//    d = PORT_READ_16(GPIOE);
//     if( d==65535)
//     {
//  	   Io=Io+1;
//     }
//
//    PORT_LOW(GPIOC);
//    PORT_LOW(GPIOD);
//    PORT_LOW(GPIOE);






  return Io;
}



void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t Pin,uint16_t mode1,uint16_t mode2)  //  отключены  PA10-PA15 переферия
{
   GPIO_InitTypeDef gpioInitStruct; //= {0}

   PIN_LOW(GPIOx,Pin);
  // HAL_GPIO_WritePin(GPIOx,(((uint16_t)0x0001)*Pin), GPIO_PIN_RESET);
   gpioInitStruct.Pin =((uint16_t)0x0001)*(1<<Pin);

 //   gpioInitStruct.Pin =GPIO_PIN_6|GPIO_PIN_7;//PIN;    //
   gpioInitStruct.Mode = mode1; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = mode1; //
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOx, &gpioInitStruct);  //
}


//uint32_t reverse_32(uint16_t data)  //32bit  revers 4 byt
//{
//	uint16_t reversed_data=0x0000;
//   for(uint8_t i=0; i<16; i++)
//   {
//	   reversed_data <<= 1;
//	   reversed_data |= data & 1;
//	   data >>= 1;
//    }
//return reversed_data;
//}


uint32_t reverse(uint32_t data,uint32_t byte)  //
{
	uint32_t reversed_data=0x0000;
   for(uint8_t i=0; i<byte; i++)
   {
	   reversed_data <<= 1;
	   reversed_data |= data & 1;
	   data >>= 1;
    }
return reversed_data;
}

uint16_t reverse_16(uint16_t data)  //
{
	uint16_t reversed_data=0x0000;
   for(uint8_t i=0; i<16; i++)
   {
	   reversed_data <<= 1;
	   reversed_data |= data & 1;
	   data >>= 1;
    }
return reversed_data;
}

uint8_t reverse_8(uint8_t data)  //
{
	uint8_t reversed_data=0x0;
   for(uint8_t i=0; i<8; i++)
   {
	   reversed_data <<= 1;
	   reversed_data |= data & 1;
	   data >>= 1;
   }
   return reversed_data;
}


void send_1wire(uint32_t data, uint8_t byte,GPIO_TypeDef *GPIOx ,uint16_t Pin)
{
/*
    PIN_LOW(SYNC);
    PIN_LOW(SCLK);

	PIN_HIGH(SYNC);
    PIN_HIGH(SCLK);

    PIN_LOW(SYNC);
    PIN_LOW(SCLK);
*/

for( uint8_t i = 0; i < byte; ++i)
    {
	//    PIN_HIGH(SCLK);

        (data  & 1 )  ? PIN_HIGH(GPIOx,Pin) : PIN_LOW(GPIOx,Pin);
        data >>= 1;

      //  PIN_LOW(SCLK);

    }
/*
////////////////////////////////////////////////////////////////C0
	PIN_HIGH(SCLK);
	PIN_HIGH(SDIN);
	PIN_LOW(SCLK);
///////////////////////////////////////////////////////////////C1
	PIN_HIGH(SCLK);
	PIN_HIGH(SDIN);
	PIN_LOW(SCLK);


	PIN_HIGH(SCLK);
    PIN_HIGH(SYNC);
*/
}



///////////////////////////////////////////////////////////////////////PINS
void Alarms_One(GPIO Port,GPIO GND)
{
//  	  GPIO_PIN_Mode(Port.A,Port.P,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);
	  PINS_OUT(Port);
	  PINS_LOW(GND);
	  PINS_OUT(GND);


	  while (1)
	  {
		  PINS_LOW(Port);
		  HAL_Delay(100);

		  PINS_HIGH(Port);
		  HAL_Delay(100);
	  }
}

///////////////////////////////////////////////////////////////////////
void PINS_HIGH (GPIO Port)  // set addres
{

	Port.A->BSRR = (uint16_t)(1<<Port.P);  //1
  //  HAL_Delay(100);

}

void PINS_LOW (GPIO Port)  // set addres
{

	Port.A->BSRR = (uint32_t)(1<<Port.P)<< 16U; //0
}
/////////////////////////////////////////////////////////////////////////
void PINS_OUT(GPIO Port)  // set addres
{
	if(Port.P<=7)
	{
		Port.A->CRL &= ~(0x0f<<(Port.P*4));
		Port.A->CRL |= 0x03<<(Port.P*4);
	}
	if(Port.P>7)
	{
		Port.A->CRH &= ~(0x0f<<((Port.P-8U)<<2u)); //*4 ((pin<<16)*4))  //<<2u == *4
		Port.A->CRH |= 0x03<<((Port.P-8U)<<2u);  //0x03

//		Port.A->CRH &= ~(0x0f<<(Port.P*4));
//		Port.A->CRH |= 0x03<<(Port.P*4);
	}
//	Port.A-> MODER |= 0x1UL << ((Port.P)*2UL);
}

void PINS_IN(GPIO Port)  // set addres
{
	if(Port.P<=7)
	{
		Port.A->CRL &= ~(0x0f<<(Port.P*4));
		Port.A->CRL |= 0x04<<(Port.P*4);
	}
	if(Port.P>7)
	{
		Port.A->CRH &= ~(0x0f<<((Port.P-8U)<<2u));   // CLR MODE CNF
		Port.A->CRH |= 0x04<<((Port.P-8U)<<2u);      //
	}

}
/////////////////////////////////////////////////////////////////////////////
void PINS_PP(GPIO Port)   //verified
{
if(Port.P<=7)
{
	Port.A->CRL &= ~(0x0f<<(Port.P*4));          // CLR MODE
//	Port.A->CRH &= ~(0x3UL<<((Port.P*4)<<2));    // CLR MODE

	Port.A->CRL &= ~(0x3UL<<(Port.P*4)<<2);
	Port.A->CRL |=  (0x2UL<<(Port.P*4)<<2);



}
if(Port.P>7)
{
	Port.A->CRH &= ~(0x0f<<((Port.P-8U)<<2u));   // CLR MODE CNF
//	Port.A->CRH &= ~(0x3UL<<((Port.P-8U)<<2u));    // CLR MODE

	Port.A->CRH &= ~(0x3UL<<(Port.P-8u)*4<<2);    //CLR CNF
	Port.A->CRH |=  (0x2UL<<(Port.P-8u)*4<<2);	  //SET CNF= 0x02


}
 Port.A->ODR |=  (0x1UL << Port.P);
}
/////////////////////////////////////////////////////////////////////////////
void PINS_DOWN(GPIO Port)   //verified
{
if(Port.P<=7)
{
	Port.A->CRL &= ~(0x3UL<<(Port.P*4)<<2);
	Port.A->CRL |=  (0x2UL<<(Port.P*4)<<2);

	Port.A->CRH &= ~(0x3UL<<((Port.P*4)<<2u));    // CLR MODE

}
if(Port.P>7)
{
	Port.A->CRH &= ~(0x3UL<<(Port.P-8u)*4<<2);    //CLR CNF
	Port.A->CRH |=  (0x2UL<<(Port.P-8u)*4<<2);	  //SET CNF= 0x02

	Port.A->CRH &= ~(0x3UL<<((Port.P-8U)<<2u));    // CLR MODE
}
    Port.A->ODR &= ~(0x1UL << Port.P);
}

//////////////////////////////////////////////////////////////////////////////
void PORTS_OUT_M(GPIO Port,uint16_t mask)  // set addres
{
	Port.A->CRL  |= (0x33333333  & mask & 0x00FF);
	Port.A->CRH  |= (0x33333333  & mask & 0xFF00);
}

void PORTS_IN_M(GPIO Port,uint16_t mask)  // set addres
{
	Port.A->CRL  &= ~(0x00000000  | mask | 0x00FF);
	Port.A->CRH  &= ~(0x00000000  | mask | 0xFF00);
}

//////////////////////////////////////////////////////////////////
void PINS_data (GPIO *Port,uint32_t ddata,uint32_t bytes)  // set addres
{
	//GPIO send[]={};

	for(uint32_t i = 0; i < bytes; ++i)
	{
		//PINS_HIGH(Port[i]);

		(ddata  & 1 )  ? PINS_HIGH(Port[i]) : PINS_LOW(Port[i]);
		ddata >>= 1;
		delay_nop(1);
	}
}

_Bool READS_PIN(GPIO Port)  //
{
	_Bool dat = (Port.A)->IDR & (uint16_t)(1<<(Port.P));
	return dat;
}
uint16_t READS_DATA_CLK(GPIO Port,uint32_t data,uint32_t byte,GPIO CLK)  // Р вЂњР’В±Р вЂњР’В·Р вЂњР РѓР вЂњР вЂ Р вЂњР’В Р вЂњР вЂ Р вЂњРЎпїЅ Р вЂњР’В± Р вЂњР вЂЎР вЂњР’В®Р вЂњР’В°Р вЂњР вЂ Р вЂњР’В®Р вЂњРЎС›  2 Р вЂњР Р‹Р вЂњР’В Р вЂњР’В©Р вЂњР вЂ 
{
	_Bool a;


	for(uint8_t i = 0; i < byte; ++i)
	{
		PINS_LOW(CLK);
		data <<= 1;  //<<
		a = READS_PIN(Port);
		data|=(a & 1);
		delay_nop(2);
		PINS_HIGH(CLK);
		delay_nop(4);
	}

	return data;
}
inline uint8_t READS_DATA(GPIO *Port,uint32_t byte)  // Р вЂњР’В±Р вЂњР’В·Р вЂњР РѓР вЂњР вЂ Р вЂњР’В Р вЂњР вЂ Р вЂњРЎпїЅ Р вЂњР’В± Р вЂњР вЂЎР вЂњР’В®Р вЂњР’В°Р вЂњР вЂ Р вЂњР’В®Р вЂњРЎС›  2 Р вЂњР Р‹Р вЂњР’В Р вЂњР’В©Р вЂњР вЂ 
{
	_Bool a;
	uint32_t data=0;
	uint32_t b=0;

	for(uint8_t i = 0; i < byte; ++i)
	{

		//data <<= 1;  //<<
		a = READS_PIN(Port[i]);
		data|=(a << i);
		//data|=(a & 1);
//		delay_nop(2);
	}
	b = reverse(data, byte);
	return b;
}

uint16_t PORTS_READ(GPIO *Data,uint32_t byte)  // Р вЂњР’В±Р вЂњР’В·Р вЂњР РѓР вЂњР вЂ Р вЂњР’В Р вЂњР вЂ Р вЂњРЎпїЅ Р вЂњР’В± Р вЂњР вЂЎР вЂњР’В®Р вЂњР’В°Р вЂњР вЂ Р вЂњР’В®Р вЂњРЎС›  2 Р вЂњР Р‹Р вЂњР’В Р вЂњР’В©Р вЂњР вЂ 
{
	_Bool a=0;
	uint16_t data=0;

	for(uint16_t i = 0; i < byte; ++i)
	{
		//data <<= 1;  //<<
		a = READS_PIN(Data[i]);
		data|=(a << i);
	}


	return data;
}

void PINS_1wire_clk(uint32_t data, uint8_t byte,GPIO Port,GPIO CLK)
{

for( uint8_t i = 0; i < byte; ++i)
    {
	    PINS_LOW(CLK);

        (data  & 1 )  ? PINS_HIGH(Port) : PINS_LOW(Port);
        data >>= 1;

       PINS_HIGH(CLK);

    }

}


//////////////////////////////////////////////////////////////////////////////////////////



//void PIN_DOWN(GPIO_TypeDef *GPIOx,uint16_t Pin)
//{
//	GPIOx->PUPDR |= 0x02 <<(Pin*2UL);
//}
//
//void PIN_PP(GPIO_TypeDef *GPIOx,uint16_t Pin)
//{
//	GPIOx->PUPDR |= 0x01<<(Pin*2UL);
////	GPIOx->PUPDR &= ~(0x2UL <<(Pin*2UL));
//}




/*


 for(uint32_t i=0;i<16;i++){PINS_OUT(p.X1[i]);}      // 16
  PINS_data(p.X1,0xFFFF,16);

  for(uint32_t i=0;i<14;i++){PINS_OUT(p.X2[i]);}      // 16
  PINS_data(p.X2,0x4000,14);

  for(uint32_t i=0;i<10;i++){PINS_OUT(p.X3[i]);}      // 16
  PINS_data(p.X3,0x0200,10);



uint8_t send_1read(uint8_t byte,GPIO_TypeDef *GPIOx ,uint16_t Pin)
{

	uint8_t Write_d=0;
	uint8_t data=0;

    for( uint8_t i = 0; i < byte-1; ++i)
    {
    	PIN_HIGH(sck);
    	Write_d<<= 1;
    	data = READ_PIN(SO);
       	Write_d |=data & 1  ;
       	PIN_LOW(sck);

    }
    return Write_d;
}


*/
#endif  //Arm3




/*
   ///Работа с COM PORTOM
      d_UART=read_UART(0);   //Прием посылка

	     switch (d_UART)
	{

	  	case 49:    // 1  TEST
			      HAL_UART_Transmit(&huart1,str0,16,0xFFFF);
			      error=READ_Eror_Data_Logik(address,blok_in);
	  			  Test_Logik(address,error,2);
	  		      block_erase_Logik_All(address,error);
	  		      Read_Logik_All(address,error,2);
			      HAL_UART_Transmit(&huart1,str11,16,0xFFFF);

			      d_UART=100;
				  printf("mode 1\n");
		 	break;

	  	case 50:    // 2   block_erase_Logik_All

		    HAL_UART_Transmit(&huart1,str12,16,0xFFFF);
	  		block_erase_Logik_All(address,6);
	  		HAL_UART_Transmit(&huart1,str13,16,0xFFFF);
	  		//block_erase_Logik(address);
	  		//block_erase(192,118,3);
	  		//address = create_address(0,1,1027,29,2048);

	  		d_UART=100;
			printf("mode 2\n");

		 break;

	  	case 51:    // 3   Read  //

	  		Read_Logik_All(address, 6,2);   // 6 Error 2 byte

	  //		Test_Logik( address,6,2);   // 6 Error 2 byte
	  //		SR = write_speed(0,0x08,2048,0,2,data_send,64);   //08
      //		SR = write_Logik(address, 0xAA ,1);



	//  		error=READ_Eror_Data_Logik(address,blok_in);
	//		HAL_UART_Transmit(&huart1,error,16,0xFFFF);

//	  	  	error=Read_Mode(0x00,0x08,221,1,2,64);
	  	  //  error=Read_Mode(0x00,0x08,2,0,0,number_of_bytes);   //(0x00,0x08,0,0,0,1);

	  	  d_UART=100;
			printf("mode 3\n");

		 break;

	  	case 52:    // 4 //

	  		write_Logik_All(address,6,2);
		  //	READ_speed_Data();  //
	  	  //	address = create_address(0,0,1,0,0);
	  	 //	uint8_t errorw2 = write_Logik(address,0xAA,2);
	  	 //	uint8_t errorr2 = Read_Mode_Logik( address,0xAA,2);


	  		printf("mode 4\n");
	  		d_UART=100;
		 break;


	  	case 53:    // 5 // Read_Mode_Logik

	  //	    Test_Logik( address, data_read,error,number_of_bytes);


	  	    printf("mode 5\n");
	  	  d_UART=100;
		 break;

	  	case 54:    // 6 // write_Logik

	//  		write_Logik(address, data_send ,number_of_bytes);
	  	    printf("mode 6\n");

	  	  d_UART=100;
		 break;


	  	case 55:    // 7 //

//	  	address = create_address(0,0,0,0,0);
//		READ_Eror_Data_Logik(address,blok);

		d_UART=100;
		 break;



	  	case 48:    // 0

	  printf("Data: \n");
	  d_UART=100;
	  break;
	}
////END COM PORT

	  delay_nop(50);
*/
