#include "main.h"
/////////////////////////////////////////
#if defined arm4    // Controller
////////////////////////////////////////
#include "stdio.h"
#include "string.h"
#include "LCD.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"


#ifndef _GPIO_ARM4_h
#define _GPIO_ARM4_h


///////////////////////////////////////LED

#define LED1 6
#define LED2 7
//////////////////////////////////////


#define HIGH 0xFFFF;
#define LOW  0x0000;

void PORT_OUT(GPIO_TypeDef *GPIOx);

void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED);  //blink
void Alarm(GPIO_TypeDef *GPIOx);

void PORT_HIGH(GPIO_TypeDef *GPIOx);    //
void PORT_LOW(GPIO_TypeDef *GPIOx);
void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data,uint16_t mask);

void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PIN_INVERS(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PORT_IN(GPIO_TypeDef *GPIOx);


uint8_t  PORT_READ_8(GPIO_TypeDef *GPIOx,uint8_t dat);     //not
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx);   //ok
uint8_t PORT_READ_8_RANDOM(GPIO_TypeDef *GPIOx,uint8_t dat);
uint16_t PORT_READ(GPIO_TypeDef *GPIOx,uint8_t byte);


_Bool READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin);
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


//uint16_t TEST(LCD1602 *scr,char *text,uint8_t N);


uint8_t reverse_8(uint8_t data);  //
uint32_t reverse(uint32_t data,uint16_t byte);  //


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


typedef struct
{
	GPIO_TypeDef *A;
	uint16_t      P;
} GPIO;

typedef enum
{
	LSB=1,       // младший
	MSB=0x8000	 // старший
};

void PINS_data (GPIO *Port,uint32_t ddata,uint32_t bytes);
void PINS_HIGH (GPIO Port);
void PINS_IN(GPIO Port);
void PINS_LOW (GPIO Port);
void PINS_OUT(GPIO Port);
_Bool READS_PIN(GPIO Port);
uint16_t PINS_READ(GPIO Port,uint32_t data,uint32_t byte);
inline uint16_t READS_DATA(GPIO Port,uint32_t data,uint32_t byte,GPIO CLK) ;
void PINS_1wire_clk(uint32_t data, uint8_t byte,GPIO Port,GPIO CLK,GPIO nCS,uint8_t Type_send);

//GPIO ad[]={GPIOF,0, GPIOF,1, GPIOF,2, GPIOF,3, GPIOF,4, GPIOF,5, GPIOF,12, GPIOE,10, GPIOF,14, GPIOF,15, GPIOG,0, GPIOG,1, GPIOG,2 };
//             a0       a1      a2       a3       a4       a5       a6        a7        a8 		  a9	    a10      a11      a12
//for(uint8_t i=0;i<13;i++) {OUT(ad[i]);}



//extern LCD1602 scr;


#endif

#endif  //arm 4




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
