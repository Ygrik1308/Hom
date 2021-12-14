#include "main.h"
#ifdef gpio_cpp

#ifndef _GPIO_HPP
#define _GPIO_HPP


#define ADDR  0b00100111 // 0b10010000//(0x27 << 1)                   //0b10010000
#define LM75_TEMP_VAL_LEN 9


///////////////////////////////////////LED
#define LED1 6
#define LED2 7
//////////////////////////////////////

#define HIGE 0xFFFF;
#define LOW  0x0000;



int Array_CNF[8]  = {2, 6, 10, 14, 18, 22, 26, 30};
int Array_MODE[8] = {0, 4, 8 , 12, 16, 20, 24, 28};
#define D ((GPIO_TypeDef *)(0x40000000UL + 0x00010000UL) + 0x00001400UL) //GPIOD


#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */
//#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { \
//                                        __IO uint32_t tmpreg = 0x00U; \
//                                        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);\
//                                        /* Delay after an RCC peripheral clock enabling */ \
//                                        tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);\
//                                        UNUSED(tmpreg); \
//                                          } while(0U)


/////////////////////////////////////////////////////////////////////////////



void Alarm(GPIO_TypeDef GPIOx);
void PIN_HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_OUT(GPIO_TypeDef *GPIOx,uint16_t Pin);
void PIN_IN(GPIO_TypeDef *GPIOx,uint16_t Pin);
void delay_nop(int Delay);


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
#endif /* gpio_cpp */
