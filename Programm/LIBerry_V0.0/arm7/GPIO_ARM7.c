//////////////////////////////////////////
#include "main.h"
//////////////////////////////////////////
#if defined arm7
/////////////////////////////////////////
#include "string.h"
#include "stdio.h"
#include "GPIO_ARM7.h"
///////////////////////////////////////////////////////////////////////////////////
 // singl diode 6
void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED)
{
      GPIO_PIN_Mode(GPIOx,LED,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	       GPIOx->BSRR = (uint16_t)(1<<LED);    //i2//   �����

		   HAL_Delay(300);
	   //    delay_nop(30000);

		   GPIOx->BSRR = (uint32_t)(1<<LED)<< 16U; //0
		   HAL_Delay(300);
	    //   delay_nop(30000);
}

void Alarm(GPIO_TypeDef *GPIOx)
{
      GPIO_PIN_Mode(GPIOx,6,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);
	  GPIO_PIN_Mode(GPIOx,7,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL);

	  while (1)
	  {
		  PIN_LOW(GPIOx,7);
		  HAL_Delay(100);

		  PIN_HIGH(GPIOx,7);
		  HAL_Delay(100);

	  }
}
////////////////////////////////////////////////////////GPIO PORT
void PORT_HIGH(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = HIGH;   //�������� 0xFFFF 1
}
// PORT_HIGE(GPIOD)
void PORT_LOW(GPIO_TypeDef *GPIOx)
{
	GPIOx->BSRR = LOW;   //�������� 0xFFFF 0
}

void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data ;   //�������� 0xFFFF 1  >> 8
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
uint16_t READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin)  // ������� � ������  2 ����
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
	GPIOB->CRL	&= ~GPIO_CRL_CNF5;	// ���������� ���� CNF ��� ���� 5. ����� 00 - Push-Pull
	GPIOB->CRL 	|= GPIO_CRL_MODE5_0;	// ���������� ��� MODE0 ��� ������ ����. ����� MODE01 = Max Speed 10MHz

	GPIOB->BSRR = GPIO_BSRR_BR5;		// �������� ���.
	GPIOB->BSRR = GPIO_BSRR_BS5;		// ���������� ���.
*/

void system_GPIO()
{
	   __HAL_RCC_GPIOA_CLK_ENABLE();
	   __HAL_RCC_GPIOB_CLK_ENABLE();
	   __HAL_RCC_GPIOC_CLK_ENABLE();
	   __HAL_RCC_GPIOD_CLK_ENABLE();
	   __HAL_RCC_GPIOE_CLK_ENABLE();
	   __HAL_RCC_GPIOF_CLK_ENABLE();
	   __HAL_RCC_GPIOG_CLK_ENABLE();


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



//uint16_t TEST()   /// Test All System
//{
//	uint16_t Error_All = 0;
//	system_GPIO();
//   ///////////////////////////////// TEST
//  //  if ((Error_All=GPIO_TEST())!= 0x03) Alarm(GPIOA);   //GPIO C,D,E
//    ///////////////////////////////// LSD INIT
////    initLCD(&scr);
// //   moveXY(&scr,3,0);
// //   lsd_print(&scr,"Init - OK");
////    HAL_Delay(1550);
////    display_clear(&scr);
////    printf("LSD initialization\n");
//    return Error_All;
//}

void PORT_IN(GPIO_TypeDef *GPIOx)
{
	GPIOx->MODER  = 0x00000000;  //44444444
}

void PORT_OUT(GPIO_TypeDef *GPIOx)
{
	GPIOx->MODER = 0x55555555;  //33333333
}


void PORT_WriteRandom(GPIO_TypeDef *GPIOx,uint16_t data)
{
	GPIOx->ODR = data ;   //�������� 0xFFFF 1
	//GPIOx->ODR = (data & 0b0000000001111111)|((data & 0b0000000100000000)<<1) ;   //�������� 0xFFFF 1
	//HAL_Delay(100);
}



void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t PIN,uint16_t mode, uint16_t mode2)  //  ���������  PA10-PA15 ���������
{
   GPIO_InitTypeDef gpioInitStruct; //= {0}

 //  PIN_LOW(GPIOx,PIN);
 // HAL_GPIO_WritePin(GPIOx,(((uint16_t)0x0001)*Pin), GPIO_PIN_RESET);
   gpioInitStruct.Pin =(1<<PIN); //PIN;    // ((uint16_t)0x0001)
   gpioInitStruct.Mode = mode;   //GPIO_MODE_OUTPUT_PP
   gpioInitStruct.Pull = mode2; // GPIO_PULLDOWN
   gpioInitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH ;//GPIO_SPEED_FREQ_LOW
   HAL_GPIO_Init(GPIOx, &gpioInitStruct);  //
}


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
    for( uint8_t i = 0; i < byte; ++i)
    {
        (data  & 1 )  ? PIN_HIGH(GPIOx,Pin) : PIN_LOW(GPIOx,Pin);
  //      PIN_HIGH(CLK) ;
        data >>= 1;
        delay_nop(1);
  //      PIN_LOW(CLK);
    }
}
//////////////////////////////////////////////////////////////////////////////////
void PINS_HIGH (GPIO Port)  // set addres
{

	Port.A->BSRR = (uint16_t)(1<<Port.P);  //1
}

void PINS_LOW (GPIO Port)  // set addres
{

	Port.A->BSRR = (uint32_t)(1<<Port.P)<< 16U; //0
}


void PINS_OUT(GPIO Port)  // set addres
{

	Port.A-> MODER |= 0x1UL << ((Port.P)*2UL);

}




void OUT2(GPIO Port, GPIO Port2, ...)  // set addres
{

	Port.A-> MODER |= 0x1UL << ((Port.P)*2UL);
//	...-> MODER |= 0x1UL << ((...)*2UL);

 //   delay_nop(1);
	//GPIOx-> MODER |= 0x1UL << (Pin*2UL);
	//GPIOx->ODR = ( addr & 0xFFFF)|(1<<Pin);          //mask PORTD0,PORTC1,PORTC3..PORT7 = 0 and addr->PORTC0..PORTC14  (GPIO1->ODR & ~0x7FFF) |
}



void PINS_data (GPIO *Port,uint32_t ddata,uint16_t bytes)  // set addres
{
	//GPIO send[]={};
	//bytes=bytes+1;

	for(uint16_t i = 0; i < bytes; ++i)
	{
		//PINS_HIGH(Port[i]);

		(ddata  & 1 )  ? PINS_HIGH(Port[i]) : PINS_LOW(Port[i]);
		ddata >>= 1;
		delay_nop(1);
	}

}


void PINS_IN(GPIO Port)  // set addres
{
	Port.A->MODER &= ~ (0x1UL << (Port.P)*2UL)<< 16U;
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

_Bool READS_PIN(GPIO Port)  //
{
	_Bool dat = (Port.A)->IDR & (uint16_t)(1<<(Port.P));
	return dat;
}

uint8_t READS_DATA(GPIO *Port,uint32_t byte)  // Р вЂњР’В±Р вЂњР’В·Р вЂњР РѓР вЂњР вЂ Р вЂњР’В Р вЂњР вЂ Р вЂњРЎпїЅ Р вЂњР’В± Р вЂњР вЂЎР вЂњР’В®Р вЂњР’В°Р вЂњР вЂ Р вЂњР’В®Р вЂњРЎС›  2 Р вЂњР Р‹Р вЂњР’В Р вЂњР’В©Р вЂњР вЂ 
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


/*
Addres create_address(Addres AA)               //2048 - data + 64 -  ,4095
{

//	  HAL_Delay(100);
  Address_type at =
  {
		  AA.A0                                     //++
	};
  return at;

}
*/
/*
Addres create_address(Addres AA)               //2048 - data + 64 -  ,4095
{


}

*/
#endif  //arm7
