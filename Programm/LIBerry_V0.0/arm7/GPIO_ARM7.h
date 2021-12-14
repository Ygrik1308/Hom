//////////////////////////////////////////
#include "main.h"
//////////////////////////////////////////
#if defined arm7
//////////////////
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_conf.h"


#ifndef _GPIO_ARM7_H
#define _GPIO_ARM7_H


///////////////////////////////////////LED
#define LED1 6
#define LED2 7
//////////////////////////////////////

//void setAddr(GPIO_TypeDef *GPIOx,uint16_t Pin);  // set addres ,uint32_t addr

#define HIGH 0xFFFF;
#define LOW  0x0000;



typedef struct
{
	GPIO_TypeDef *A;
	uint16_t      P;
} GPIO;









void PORT_OUT(GPIO_TypeDef *GPIOx);

void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED);  //blink
void Alarm(GPIO_TypeDef *GPIOx);

void PORT_HIGH(GPIO_TypeDef *GPIOx);    //
void PORT_LOW(GPIO_TypeDef *GPIOx);
void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data);

void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PORT_IN(GPIO_TypeDef *GPIOx);



uint8_t  PORT_READ_8(GPIO_TypeDef *GPIOx,uint8_t dat);     //not
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx,uint16_t dat);   //ok
uint8_t PORT_READ_8_RANDOM(GPIO_TypeDef *GPIOx,uint8_t dat);

uint16_t READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PORT_WriteRandom(GPIO_TypeDef *GPIOx,uint16_t data);


uint16_t reverse_16(uint16_t data);  //



void delay_nop(int Delay);


void PIN_DOWN(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_PP(GPIO_TypeDef *GPIOx,uint16_t Pin);

void system_GPIO();
void MoV_GPIO(GPIO_TypeDef *GPIOx,uint16_t MODE,uint16_t PP);

//void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t Pin,uint16_t mode);
//void GPIO_PORT_Mode(GPIO_TypeDef *GPIOx,uint16_t mode, uint16_t mode2,uint16_t mode3);
void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t PIN,uint16_t mode, uint16_t mode2);  //  отключены  PA10-PA15 переферия


void GPIO_Mode_A(uint16_t mode) ; //periferia
void GPIO_OUT_B();                //periferia
void GPIO_Mode_C(uint16_t mode) ; //IN/OUT
void GPIO_OUT_D();
void GPIO_Mode_E(uint16_t mode);


int GPIO_TEST();


uint8_t reverse_8(uint8_t data);  //
uint32_t reverse(uint32_t data,uint32_t byte); //


void send_1wire(uint32_t data, uint8_t byte,GPIO_TypeDef *GPIOx ,uint16_t Pin);
 //inline
//////////////////////////////////////////////

typedef enum
{
 D0=0x00,
 D1=0x01,
 D2=0x02,
 D3=0x03,
 D4=0x04,
 D5=0x05,
 D6=0x06,
 D7=0x07
}Array;


//////////////////////////////////////////////////////////////////////////////pins
void PINS_data (GPIO *Port,uint32_t ddata, uint16_t bytes);
void PINS_OUT(GPIO Port);
void PINS_IN(GPIO Port);
void PINS_LOW (GPIO Port);
void PINS_HIGH (GPIO Port);
_Bool READS_PIN(GPIO Port);
uint8_t READS_DATA(GPIO *Port,uint32_t byte);

/*
typedef struct
{
	GPIO_TypeDef *A0;
	GPIO_TypeDef *A1;
	GPIO_TypeDef *A2;
	GPIO_TypeDef *A3;
	GPIO_TypeDef *A4;
	GPIO_TypeDef *A5;
	GPIO_TypeDef *A6;
	GPIO_TypeDef *A7;
	GPIO_TypeDef *A8;
	GPIO_TypeDef *A9;
	GPIO_TypeDef *A10;
	GPIO_TypeDef *A11;
	GPIO_TypeDef *A12;
} PORT;
*/
/*
typedef struct
{
	uint16_t p0;
	uint16_t p1;
	uint16_t p2;
	uint16_t p3;
	uint16_t p4;
	uint16_t p5;
	uint16_t p6;
	uint16_t p7;
	uint16_t p8;
	uint16_t p9;
	uint16_t p10;
	uint16_t p11;
	uint16_t p12;
	uint16_t p13;
	uint16_t p14;
	uint16_t p15;
} PIN;
*/

/*
typedef struct
{
	GPIO A0 ;
	GPIO A1 ;
	GPIO A2 ;
	GPIO A3 ;
	GPIO A4 ;
	GPIO A5 ;
	GPIO A6 ;
	GPIO A7 ;
	GPIO A8 ;
	GPIO A9 ;
	GPIO A10;
	GPIO A11;
	GPIO A12;
} Addres;
*/



//extern LCD1602 scr;


#endif

/*
#define outp(val, port) (port) = (val)
#define inp(port) (port)
#define outp(val, port) (port) = (val)
#define inb(port) (port)
#define outb(port, val) (port) = (val)
#define sbi(port, bit) (port) |= (1 << (bit))
#define cbi(port, bit) (port) &= ~(1 << (bit))
*/


/*
typedef enum
{
D1 = (GPIOD,0),
 D1=0x01,
 D2=0x02,
 D3=0x03,
 D4=0x04,
 D5=0x05,
 D6=0x06,
 D7=0x07
}Array;

*/
#endif  //arm7
