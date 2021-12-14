#include "main.h"
/////////////////////////
#if defined arm3
//////////////////////////
//#include "stm32f1xx_hal.h"
//#include "stm32f1xx_conf.h"
//#include "stdio.h"
//#include "string.h"
//#include "STM32F103xE.h"
//#include "lcd.h"

#ifndef _GPIO_ARM3_H
#define _GPIO_ARM3_H

#define LED1 GPIOC,6  // OUTPUT
#define LED2 GPIOC,7  // OUTPUT


#define ADDR  0b00100111 // 0b10010000//(0x27 << 1)                   //0b10010000
#define LM75_TEMP_VAL_LEN 9



#define HIGE 0xFFFF;
#define LOW  0x0000;


void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED);
void Alarm(GPIO_TypeDef *GPIOx);

void PORT_HIGH(GPIO_TypeDef *GPIOx);    //
void PORT_LOW(GPIO_TypeDef *GPIOx);


void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_LOW(GPIO_TypeDef *GPIOx,uint16_t Pin);
uint8_t send_1read(uint8_t byte,GPIO_TypeDef *GPIOx ,uint16_t Pin);

void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin);

void delay_nop(int Delay);

void system_GPIO();


_Bool READ_PIN(GPIO_TypeDef *GPIOx,uint16_t Pin);
uint16_t PORT_READ_16(GPIO_TypeDef *GPIOx,uint16_t dat);
uint8_t PORT_READ_8(GPIO_TypeDef *GPIOx,uint8_t dat);

void GPIO_PIN_Mode(GPIO_TypeDef *GPIOx,uint16_t Pin,uint16_t mode1,uint16_t mode2);
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
void PORT_WriteRandom(GPIO_TypeDef *GPIOx,uint16_t data);
uint8_t PORT_READ_8_RANDOM(GPIO_TypeDef *GPIOx,uint8_t dat);
//////////////////////////////////////////////////////////////
uint32_t reverse_32(uint32_t data,uint32_t byte);


//typedef enum
//{
// D0=0x00,
// D1=0x01,
// D2=0x02,
// D3=0x03,
// D4=0x04,
// D5=0x05,
// D6=0x06,
// D7=0x07
//}Array;

typedef struct
{
	GPIO_TypeDef *A;
	uint32_t      P;
} GPIO;

typedef struct
{
	GPIO LED0;
	GPIO LED_GND;
}LET_TYPE;

extern GPIO type;

typedef enum
{
	high=1,
	low=0
};


void Alarm_PIN();
void OK();

_Bool READS_PIN(GPIO Port);  // считать с портов  2 байт
void PINS_HIGH (GPIO Port);

void PINS_LOW (GPIO Port);
void PINS_OUT (GPIO Port);
void PINS_IN(GPIO Port);  // set addres
uint8_t  READS_DATA(GPIO *Port,uint32_t byte);
uint16_t PORTS_READ(GPIO *Data,uint32_t byte);

uint16_t READS_DATA_CLK(GPIO Port,uint32_t data,uint32_t byte,GPIO CLK);
void PINS_data (GPIO *Port,uint32_t ddata,uint32_t bytes);

void PINS_PP(GPIO Port);

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

#endif  //Arm3

