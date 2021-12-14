#include "main.h"
/////////////////
#ifdef arm4
////////////////////
#include "GPIO_ARM4.h"
//#include "lcd.h"

#include "string.h"
#include "stdio.h"


///////////////////////////////////////////////////////////////////////////////////
 // singl diode 6
void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED)
{
	       GPIOx->BSRR = (uint16_t)(1<<LED);    //i2//   горит
		   HAL_Delay(100);

		   GPIOx->BSRR = (uint32_t)(1<<LED)<< 16U; //0
		   HAL_Delay(100);
}

void Alarm(GPIO_TypeDef *GPIOx)
{
      GPIO_PIN_Mode(GPIOA,6,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);
	  GPIO_PIN_Mode(GPIOA,7,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	  while (1)
	  {
		  PIN_LOW(GPIOA,6);
		  PIN_LOW(GPIOA,7);
		  HAL_Delay(100);

		  PIN_HIGH(GPIOA,6);
		  PIN_HIGH(GPIOA,7);
		  HAL_Delay(100);

	  }
}
////////////////////////////////////////////////////////GPIO PORT
void PORT_HIGH(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = HIGH;   //записать 0xFFFF 1
}
// PORT_HIGE(GPIOD)
void PORT_LOW(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = LOW;   //записать 0xFFFF 0
}

void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data >> 8 ;   //записать 0xFFFF 1
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

	GPIOx-> MODER |= 0x1UL << (Pin*2UL);
}

void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin)    /// PIn-> OUT  (GPIOD,5)
{
	GPIOx->MODER &= ~ (0x1UL << (Pin)*2UL)<< 16U;
}

void delay_nop(int Delay)
{
	for( uint8_t i=0; i<Delay; ++i) asm ( "nop" );
}


////////////////////// PORT_READ//////////////////////////////////////
///////////////////////////////////////////////////////////////
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx,uint16_t dat)
{
	//	dat=GPIOx->IDR;
    //	dat=(GPIOx->IDR & 0b1111111111111001);
		dat=(GPIOx->IDR & 0b1111111111111111);

	/*	uint16_t dat = (GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
		dat |= (GPIOE->IDR & 0xFF) << 8;
	*/

return dat;
}
uint16_t READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin)  // считать с портов  2 байт
{
	uint16_t dat = GPIOx->IDR & (uint16_t)(1<<Pin);
//	(GPIOD->IDR & 0x3) | ((GPIOB->IDR & (1 << 5)) >> (5-2)) | (GPIOD->IDR & 0b11111000);
//	dat |= (GPIOE->IDR & 0xFF) << 8;

	return dat;
}
//////////////////////////////////////////////////////////

void PIN_DOWN(GPIO_TypeDef *GPIOx,uint16_t Pin)
{
	GPIOx->PUPDR |= 0x2UL <<(Pin*2UL);
}

void PIN_PP(GPIO_TypeDef *GPIOx,uint16_t Pin)
{
	GPIOx->PUPDR &= ~(0x2UL <<(Pin*2UL));
}

/*
	GPIOB->CRL	&= ~GPIO_CRL_CNF5;	// Сбрасываем биты CNF для бита 5. Режим 00 - Push-Pull
	GPIOB->CRL 	|= GPIO_CRL_MODE5_0;	// Выставляем бит MODE0 для пятого пина. Режим MODE01 = Max Speed 10MHz

	GPIOB->BSRR = GPIO_BSRR_BR5;		// Сбросили бит.
	GPIOB->BSRR = GPIO_BSRR_BS5;		// Установили бит.
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
  GPIO_PORT_Mode(GPIOC,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW);  // GPIO_MODE_INPUT
  GPIO_PORT_Mode(GPIOD,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW);  // GPIO_MODE_INPUT
  GPIO_PORT_Mode(GPIOE,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW);  // GPIO_MODE_INPUT

  PORT_HIGH(GPIOC);
  PORT_HIGH(GPIOD);
  PORT_HIGH(GPIOE);

    d = PORT_READ_16(GPIOC,0);
    if( d==65535)
    {
  	  Io=1;
    }

    d = PORT_READ_16(GPIOD,0);
    if( d==65535)
    {
  	  Io=Io+1;
    }

    d = PORT_READ_16(GPIOE,0);
     if( d==65535)
     {
  	   Io=Io+1;
     }

    PORT_LOW(GPIOC);
    PORT_LOW(GPIOD);
    PORT_LOW(GPIOE);

  return Io;
}



uint16_t TEST()   /// Test All System
{
	uint16_t Error_All = 0;

   ///////////////////////////////// TEST
  //  if ((Error_All=GPIO_TEST())!= 0x03) Alarm(GPIOA);   //GPIO C,D,E
    ///////////////////////////////// LSD INIT


//    initLCD(&scr);
//    moveXY(&scr,3,0);
//    lsd_print(&scr,"Init - OK");
//    HAL_Delay(1550);
//    display_clear(&scr);
//    printf("LSD initialization\n");

    return Error_All;
}


void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t PIN,uint16_t mode, uint16_t mode2)  //  отключены  PA10-PA15 переферия
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


void GPIO_PORT_Mode(GPIO_TypeDef *GPIOx,uint16_t mode, uint16_t mode2,uint16_t mode3)  //  отключены  PA10-PA15 переферия
{
   GPIO_InitTypeDef gpioInitStruct; //= {0}
 //  PORT_LOW(GPIOx);
   gpioInitStruct.Pin =GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;//PIN;    //
   gpioInitStruct.Mode = mode; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = mode2; //GPIO_PULLDOWN
   gpioInitStruct.Speed = mode3;// GPIO_SPEED_FREQ_LOW// GPIO_SPEED_FREQ_LOW
   HAL_GPIO_Init(GPIOx, &gpioInitStruct);  //
}

/*

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



void GPIO_Mode_C(uint16_t mode)
{
   __HAL_RCC_GPIOC_CLK_ENABLE();
   GPIO_InitTypeDef gpioInitStruct;
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
   gpioInitStruct.Pin =GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;//PIN;    //
   gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = GPIO_NOPULL;
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOC, &gpioInitStruct);  //
}


void GPIO_OUT_D()
{
   __HAL_RCC_GPIOD_CLK_ENABLE();
   GPIO_InitTypeDef gpioInitStruct;
   HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_15, GPIO_PIN_RESET);
   gpioInitStruct.Pin =GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_15;//PIN;    //
   gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = GPIO_NOPULL;
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOD, &gpioInitStruct);  //
}


void GPIO_Mode_E(uint16_t mode)  //    PA14,PA13 Serial
{

   GPIO_InitTypeDef gpioInitStruct;

   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
   gpioInitStruct.Pin =GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
		   |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;//PIN;    //
   gpioInitStruct.Mode = mode; //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = GPIO_NOPULL;
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_LOW;//
   HAL_GPIO_Init(GPIOE, &gpioInitStruct);  //
}
*/

uint32_t reverse(uint32_t data)  //
{
	uint32_t reversed_data=0x0000;
   for(uint8_t i=0; i<32; i++)
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
    for( uint8_t i = 0; i < byte; ++i)
    {
        (data  & 1 )  ? PIN_HIGH(GPIOx,Pin) : PIN_LOW(GPIOx,Pin);
  //      PIN_HIGH(CLK) ;
        data >>= 1;
        delay_nop(1);
  //      PIN_LOW(CLK);
    }
}



__weak void Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while((HAL_GetTick() - tickstart) < wait)
  {
  }
}
#endif /* arm4 */

