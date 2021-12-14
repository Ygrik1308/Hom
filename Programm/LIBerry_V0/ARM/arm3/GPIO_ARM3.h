#include "main.h"
//////////////////////////////////
#ifdef arm3
//////////////////////////////////
#ifndef _GPIO_ARM3_H
#define _GPIO_ARM3_H


#define ADDR  0b00100111 // 0b10010000//(0x27 << 1)                   //0b10010000
#define LM75_TEMP_VAL_LEN 9


///////////////////////////////////////LED

#define LED1 6
#define LED2 7
//////////////////////////////////////
typedef struct
{
    GPIO_TypeDef *GPIO;
	uint16_t PIN;
}GPIO;

//#define HIGE 0xFFFF;
//#define LOW  0x0000;


typedef enum
{
	rcca = 0x1UL << (2U),    //103VE
	rccb = 0x1UL << (3U),    //103VE
	rccc = 0x1UL << (4U),    //103VE
	rccd = 0x1UL << (5U),    //103VE
	rcce = 0x1UL << (6U),    //103VE
	rccg = 0x1UL << (8U)     //103ZET
}_rcc;

typedef enum
{
	pA = 0x1,    //103VE
	pB = 0x2,    //103VE
	pC = 0x4,    //103VE
	pD=  0x8,    //103VE
	pE = 0x10,   //103VE
	pG = 0x20    //103ZET
}RCC_senD;



uint16_t GPIO_Init() ;

void PORT_HIGH(GPIO_TypeDef *GPIOx);    //
void PORT_LOW(GPIO_TypeDef *GPIOx);

void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin);

void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin);






//_Bool READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin);
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx,uint16_t dat);
uint8_t PORT_READ_8(GPIO_TypeDef *GPIOx,uint8_t dat);

void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t Pin,uint16_t mode1,uint16_t mode2);
void GPIO_PORT_Mode(GPIO_TypeDef *GPIOx,uint16_t mode, uint16_t mode2);
void PORT_Data(GPIO_TypeDef *GPIOx,uint16_t data);

void GPIO_Mode_A(uint16_t mode);
void GPIO_OUT_B();
void GPIO_OUT_C();
void GPIO_OUT_D();
void GPIO_Mode_E(uint16_t mode);


void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PORT_OUT(GPIO_TypeDef *GPIOx);
void PORT_IN(GPIO_TypeDef *GPIOx);


void PORT_Write8(GPIO_TypeDef *GPIOx,uint16_t data);
//////////////////////////////////////////////
void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED);  //blink
//void Alarm(GPIO_TypeDef *GPIOx);
void delay_nop(int Delay);

void clocking(void);


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


void PINS_OUT(GPIO p);

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
#endif /* arm3 */
