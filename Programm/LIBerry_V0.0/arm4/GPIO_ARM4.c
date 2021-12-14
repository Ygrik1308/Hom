#include "main.h"
/////////////////////////////////////////
#if defined arm4    // Controller
////////////////////////////////////////
#include "string.h"
#include "stdio.h"
#include "GPIO_ARM4.h"
#include "delay.h"

#define SDIN GPIOD,0
#define SCLK GPIOC,0
#define SYNC GPIOC,1

///////////////////////////////////////////////////////////////////////////////////
 // singl diode 6
void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED)
{

	PIN_OUT(GPIOx,LED);

	GPIOx->BSRR = (uint16_t)(1<<LED);    //i2//   Р вЂњРЎвЂњР вЂ™Р в‚¬Р вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™Р’В°Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ 

           HAL_Delay(200);
		   GPIOx->BSRR = (uint32_t)(1<<LED)<< 16U; //0
		   HAL_Delay(200);
}

void Alarm(GPIO_TypeDef *GPIOx)
{
      GPIO_PIN_Mode(GPIOA,6,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);
	  GPIO_PIN_Mode(GPIOA,7,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	  while (1)
	  {
		  PIN_LOW(GPIOA,6);
		  PIN_LOW(GPIOA,7);

		  //_delay_ms(10);

		   HAL_Delay(100);

		  PIN_HIGH(GPIOA,6);
		  PIN_HIGH(GPIOA,7);
		  HAL_Delay(100);
		  //_delay_ms(10);



	  }
}
////////////////////////////////////////////////////////GPIO PORT
void PORT_HIGH(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = HIGH;   //Р вЂњРЎвЂњР вЂ™Р’В§Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™РЎпїЅ 0xFFFF 1
}
// PORT_HIGE(GPIOD)
void PORT_LOW(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = LOW;   //Р вЂњРЎвЂњР вЂ™Р’В§Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™РЎпїЅ 0xFFFF 0
}

void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data,uint16_t mask)
{
	GPIOx->ODR |= (data & mask) ;   //Р вЂњРЎвЂњР вЂ™Р’В§Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™РЎпїЅ 0xFFFF 1  >> 8
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

void PIN_INVERS(GPIO_TypeDef *GPIOx,uint16_t Pin)
{
	uint8_t a=READ_PIN(GPIOx,Pin);
	if ( a== 1)
	{
		GPIOx->BSRR = (uint32_t)(1<<Pin)<< 16U;  // 0
	}
	else
	{
		GPIOx->BSRR = (uint16_t)(1<<Pin);   //1
	}
}
////////////////////////////////////////////////////////// PIN
void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin)    /// PIn-> OUT  (GPIOD,5)
{

	GPIOx-> MODER |= 0x1UL << (Pin*2UL);
}

void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin)    /// PIn-> OUT  (GPIOD,5)
{
	GPIOx->MODER  &= ~(0x1UL << (Pin*2UL));

}

//////////////////////////////////////////////////////////

void PIN_DOWN(GPIO_TypeDef *GPIOx,uint16_t Pin)
{
	GPIOx->PUPDR |= 0x02 <<(Pin*2UL);
}

void PIN_PP(GPIO_TypeDef *GPIOx,uint16_t Pin)
{
	GPIOx->PUPDR |= 0x01<<(Pin*2UL);
//	GPIOx->PUPDR &= ~(0x2UL <<(Pin*2UL));
}
////////////////////////////////////////////

void delay_nop(int Delay)
{
	for( uint32_t i=0; i<Delay; ++i) asm ( "nop" );
}
////////////////////// PORT_READ//////////////////////////////////////
///////////////////////////////////////////////////////////////
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx)
{
	    uint16_t dat=0;
	//	dat=GPIOx->IDR;
    //	dat=(GPIOx->IDR & 0b1111111111111001);
		dat=(GPIOx->IDR & 0b1111111111111111);

	/*	uint16_t dat = (GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
		dat |= (GPIOE->IDR & 0xFF) << 8;
	*/

return dat;
}
_Bool READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin)  // Р вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В·Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™РЎпїЅ Р вЂњРЎвЂњР вЂ™Р’В± Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™Р’В°Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™РЎС›  2 Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р’В©Р вЂњРЎвЂњР вЂ™Р вЂ 
{
	_Bool dat = GPIOx->IDR & (uint16_t)(1<<Pin);
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


/*
void someFunction(option1,option2,option3,option4,option5,option6,option7,option8);
*/


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
	//	dat |= (GPIOE->IDR & 0xFF) << 8;


return data;
}


/*
	GPIOB->CRL	&= ~GPIO_CRL_CNF5;	// Р вЂњРЎвЂњР Р†Р вЂљРїС—Р…Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р’В°Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В»Р вЂњРЎвЂњР вЂ™РЎС›Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В¬ Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В» CNF Р вЂњРЎвЂњР вЂ™Р’В¤Р вЂњРЎвЂњР вЂ™Р’В«Р вЂњРЎвЂњР вЂ™РЎвЂ” Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В  5. Р вЂњРЎвЂњР С—РЎвЂ”Р вЂ¦Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В¦Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В¬ 00 - Push-Pull
	GPIOB->CRL 	|= GPIO_CRL_MODE5_0;	// Р вЂњРЎвЂњР Р†Р вЂљРЎв„ўР вЂњРЎвЂњР вЂ™Р’В»Р вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™РЎС›Р вЂњРЎвЂњР вЂ™Р’В«Р вЂњРЎвЂњР вЂ™РЎвЂ”Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В¬ Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ  MODE0 Р вЂњРЎвЂњР вЂ™Р’В¤Р вЂњРЎвЂњР вЂ™Р’В«Р вЂњРЎвЂњР вЂ™РЎвЂ” Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™РЎвЂ”Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™Р в‚¬Р вЂњРЎвЂњР вЂ™Р’В® Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В­Р вЂњРЎвЂњР вЂ™Р’В . Р вЂњРЎвЂњР С—РЎвЂ”Р вЂ¦Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В¦Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В¬ MODE01 = Max Speed 10MHz

	GPIOB->BSRR = GPIO_BSRR_BR5;		// Р вЂњРЎвЂњР Р†Р вЂљРїС—Р…Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р’В°Р вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В«Р вЂњРЎвЂњР вЂ™Р Рѓ Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ .
	GPIOB->BSRR = GPIO_BSRR_BS5;		// Р вЂњРЎвЂњР Р†Р вЂљРЎС™Р вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р’В­Р вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™РЎС›Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В«Р вЂњРЎвЂњР вЂ™Р Рѓ Р вЂњРЎвЂњР вЂ™Р Р‹Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р вЂ .
*/

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
////////////////////////////////
 PORT_OUT(GPIOC);  // GPIO_MODE_INPUT
 PORT_OUT(GPIOD);  // GPIO_MODE_INPUT
 PORT_OUT(GPIOE);  // GPIO_MODE_INPUT

 PORT_HIGH(GPIOC);
 PORT_HIGH(GPIOD);
 PORT_HIGH(GPIOE);

    d = PORT_READ_16(GPIOC);
    if( d==65535)
    {
  	  Io=1;
    }

    d = PORT_READ_16(GPIOD);
    if( d==65535)
    {
  	  Io=Io+1;
    }

    d = PORT_READ_16(GPIOE);
     if( d==65535)
     {
  	   Io=Io+1;
     }

    PORT_LOW(GPIOC);
    PORT_LOW(GPIOD);
    PORT_LOW(GPIOE);

  return Io;
}

/*
uint16_t TEST(LCD1602 *scr,char *text,uint8_t N)   /// Test All System
{
	uint16_t Error_All = 0;
	system_GPIO();
	PIN_OUT(GPIOA,6);
	PIN_OUT(GPIOA,7);
    ///////////////////////////////// TEST
//      if ((Error_All=GPIO_TEST())!= 0x03) Alarm(GPIOA);   //GPIO C,D,E

	///////////////////////////////// LSD INIT


//	    printf("ID_I2C:%u=%u\n",N,I2C_ID[0]);
//	    uint8_t iD=I2C_ID[0];
if(N>0)
{
//	initLCD_I2C(0x27);
//    moveXY_I2C(iD,1,1);
//	i2c_lsd_print(iD,text);

	initLCD(scr);
    moveXY(scr,0,0);
    lsd_print(scr,text);
    HAL_Delay(2000);
//    display_clear(scr);
    printf("LSD initialization\n");
}


    return Error_All;

    ///////////////////////////////// Indicator init

}
*/
void PORT_IN(GPIO_TypeDef *GPIOx)
{
	GPIOx->MODER  = 0x00000000;  //44444444
}

void PORT_OUT(GPIO_TypeDef *GPIOx)
{
	GPIOx->MODER = 0x55555555;  //33333333
}


void PORT_PP(GPIO_TypeDef *GPIOx)
{
	GPIOx->PUPDR |= 0x55555555;  //33333333
}


void PORT_WriteRandom(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data ;   //Р вЂњРЎвЂњР вЂ™Р’В§Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™РЎпїЅ 0xFFFF 1
	//GPIOx->ODR = (data & 0b0000000001111111)|((data & 0b0000000100000000)<<1) ;   //Р вЂњРЎвЂњР вЂ™Р’В§Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™Р’В±Р вЂњРЎвЂњР вЂ™Р’В Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™РЎпїЅ 0xFFFF 1
	//HAL_Delay(100);
}


void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t PIN,uint16_t mode, uint16_t mode2)  //  Р вЂњРЎвЂњР вЂ™Р’В®Р вЂњРЎвЂњР вЂ™Р вЂ Р вЂњРЎвЂњР вЂ™Р вЂћР вЂњРЎвЂњР вЂ™Р’В«Р вЂњРЎвЂњР вЂ™РЎвЂўР вЂњРЎвЂњР вЂ™Р’В·Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В­Р вЂњРЎвЂњР вЂ™Р’В»  PA10-PA15 Р вЂњРЎвЂњР вЂ™Р вЂЎР вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В°Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™РўвЂ�Р вЂњРЎвЂњР вЂ™РўС’Р вЂњРЎвЂњР вЂ™Р’В°Р вЂњРЎвЂњР вЂ™Р РѓР вЂњРЎвЂњР вЂ™РЎвЂ”
{
   GPIO_InitTypeDef gpioInitStruct; //= {0}

 //  PIN_LOW(GPIOx,PIN);
 // HAL_GPIO_WritePin(GPIOx,(((uint16_t)0x0001)*Pin), GPIO_PIN_RESET);
   gpioInitStruct.Pin =(1<<PIN); //PIN;    // ((uint16_t)0x0001)
   gpioInitStruct.Mode = mode;   //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = mode2;  //GPIO_PULLDOWN
//   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOx, &gpioInitStruct);  //
}


uint32_t reverse(uint32_t data,uint16_t byte)  //
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
//uint16_t reverse_16(uint16_t data)  //
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
//
//uint8_t reverse_8(uint8_t data)  //
//{
//	uint8_t reversed_data=0x0;
//   for(uint8_t i=0; i<8; i++)
//   {
//	   reversed_data <<= 1;
//	   reversed_data |= data & 1;
//	   data >>= 1;
//    }
//   return reversed_data;
//}





void send_1wire(uint32_t data, uint8_t byte,GPIO_TypeDef *GPIOx ,uint16_t Pin)
{

    PIN_LOW(SYNC);
    PIN_LOW(SCLK);

	PIN_HIGH(SYNC);
    PIN_HIGH(SCLK);

    PIN_LOW(SYNC);
    PIN_LOW(SCLK);


for( uint8_t i = 0; i < byte; ++i)
    {
	    PIN_HIGH(SCLK);

        (data  & 1 )  ? PIN_HIGH(GPIOx,Pin) : PIN_LOW(GPIOx,Pin);
        data >>= 1;

        PIN_LOW(SCLK);

    }

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


}
inline void PINS_HIGH (GPIO Port)  // set addres
{

	Port.A->BSRR = (uint16_t)(1<<Port.P);  //1
}

inline void PINS_LOW (GPIO Port)  // set addres
{

	Port.A->BSRR = (uint32_t)(1<<Port.P)<< 16U; //0
}
inline void PINS_OUT(GPIO Port)  // set addres
{

	Port.A-> MODER |= 0x1UL << ((Port.P)*2UL);
}

inline void PINS_IN(GPIO Port)    /// PIn-> OUT  (GPIOD,5)
{
	Port.A->MODER  &= ~(0x1UL << ((Port.P)*2UL));

}
inline void PINS_data (GPIO *Port,uint32_t ddata,uint32_t bytes)  // set addres massiv
{
	//GPIO send[]={};

	for(uint8_t i = 0; i < bytes; ++i)
	{
		//PINS_HIGH(Port[i]);

		(ddata  & 1 )  ? PINS_HIGH(Port[i]) : PINS_LOW(Port[i]);
		ddata >>= 1;
		delay_nop(1);
	}

}


//////////////////////////////////////////////////////////////////
inline _Bool READS_PIN(GPIO Port)  // Р вЂњР’В±Р вЂњР’В·Р вЂњР РѓР вЂњР вЂ Р вЂњР’В Р вЂњР вЂ Р вЂњРЎпїЅ Р вЂњР’В± Р вЂњР вЂЎР вЂњР’В®Р вЂњР’В°Р вЂњР вЂ Р вЂњР’В®Р вЂњРЎС›  2 Р вЂњР Р‹Р вЂњР’В Р вЂњР’В©Р вЂњР вЂ 
{
	_Bool dat = (Port.A)->IDR & (uint16_t)(1<<(Port.P));
	return dat;
}


//////////////////////////////////////////////////////////////////
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

uint16_t PORTS_READ(GPIO *Data,uint32_t byte)  // Р вЂњР’В±Р вЂњР’В·Р вЂњР РѓР вЂњР вЂ Р вЂњР’В Р вЂњР вЂ Р вЂњРЎпїЅ Р вЂњР’В± Р вЂњР вЂЎР вЂњР’В®Р вЂњР’В°Р вЂњР вЂ Р вЂњР’В®Р вЂњРЎС›  2 Р вЂњР Р‹Р вЂњР’В Р вЂњР’В©Р вЂњР вЂ 
{
	_Bool a=0;
	uint8_t data=0;

	for(uint16_t i = 0; i < byte; ++i)
	{
		data <<= 1;  //<<
		a = READS_PIN(Data[i]);
		data|=(a & 1);
	}


	return data;
}

void PINS_1wire_clk(uint32_t data, uint8_t byte,GPIO Port,GPIO CLK,GPIO nCS,uint8_t Type_send) // ��������� � ����
{

//	PINS_LOW(nCS);

for( uint8_t i = 0; i < byte; ++i)
    {
	    PINS_LOW(CLK);

        (data  & 1)  ? PINS_HIGH(Port) : PINS_LOW(Port);  //
        data >>= 1;  //>>

       PINS_HIGH(CLK);

    }

//PINS_HIGH(nCS);

}



#endif  //arm 4

