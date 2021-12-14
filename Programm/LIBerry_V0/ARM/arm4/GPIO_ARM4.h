#include "conf.h"
#ifdef arm4

#ifndef _GPIO_ARM4_H
#define _GPIO_ARM4_H


///////////////////////////////////////LED

#define LED1 6
#define LED2 7
//////////////////////////////////////



#define HIGH 0xFFFF;
#define LOW  0x0000;



void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED);  //blink
void Alarm(GPIO_TypeDef *GPIOx);

void PORT_HIGH(GPIO_TypeDef *GPIOx);    //
void PORT_LOW(GPIO_TypeDef *GPIOx);
void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data);

void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin);

uint8_t  PORT_READ_8(GPIO_TypeDef *GPIOx,uint16_t dat);     //not
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx,uint16_t dat);   //ok

uint16_t READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin);

uint16_t reverse_16(uint16_t data);  //


void delay_nop(int Delay);

void PIN_DOWN(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_PP(GPIO_TypeDef *GPIOx,uint16_t Pin);

void system_GPIO();
void MoV_GPIO(GPIO_TypeDef *GPIOx,uint16_t MODE,uint16_t PP);

//void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t Pin,uint16_t mode);
void GPIO_PORT_Mode(GPIO_TypeDef *GPIOx,uint16_t mode, uint16_t mode2,uint16_t mode3);
void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t PIN,uint16_t mode, uint16_t mode2);  //  отключены  PA10-PA15 переферия


void GPIO_Mode_A(uint16_t mode) ; //periferia
void GPIO_OUT_B();                //periferia
void GPIO_Mode_C(uint16_t mode) ; //IN/OUT
void GPIO_OUT_D();
void GPIO_Mode_E(uint16_t mode);


int GPIO_TEST();
uint16_t TEST();

uint8_t reverse_8(uint8_t data);  //
uint32_t reverse(uint32_t data);  //


void send_1wire(uint32_t data, uint8_t byte,GPIO_TypeDef *GPIOx ,uint16_t Pin);
__weak void Delay(uint32_t Delay);
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
#endif /* arm4 */
