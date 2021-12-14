#include "main.h"
#ifdef AVR//HAL_I2C_MODULE_ENABLED


#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

//#include "lcd.h"
//#include "string.h"
#include "stdio.h"
#include "GPIO_Atmel.h"
#include <avr/io.h>

#if defined (__AVR_ATmega2560__)
#define GPIOA    _SFR_IO8(0X01)     //DDR
#define GPIOB    _SFR_IO8(0x04)     //DDR
#define GPIOC    _SFR_IO8(0x07)     //DDR
#define GPIOD    _SFR_IO8(0x0A)     //DDR
#define GPIOE    _SFR_IO8(0x0D)     //DDR
#define GPIOF    _SFR_IO8(0x10)     //DDR
#define GPIOG    _SFR_IO8(0x13)     //DDR
#define GPIOK    _SFR_MEM8(0x107)   //DDR
#define GPIOL    _SFR_MEM8(0x10A)   //DDR
#define GPIOJ    _SFR_MEM8(0x104)   //DDR
#define GPIOH    _SFR_MEM8(0x101)   //DDR
#endif

#if defined (__AVR_ATmega1281__)
#define GPIOA    _SFR_IO8(0X01)     //DDR  
#define GPIOB    _SFR_IO8(0x04)     //DDR
#define GPIOC    _SFR_IO8(0x07)     //DDR
#define GPIOD    _SFR_IO8(0x0A)     //DDR
#define GPIOE    _SFR_IO8(0x0D)     //DDR
#define GPIOF    _SFR_IO8(0x10)     //DDR
#define GPIOG    _SFR_IO8(0x13)    //DDR
#endif
///////////////////////////////////////LED
#define LED1 6
#define LED2 7
//////////////////////////////////////
#define HIGE 0xFF;
#define LOW  0x00;

//int Array_CNF[8]  = { 2, 6, 10, 14, 18, 22, 26, 30 };
//int Array_MODE[8] = { 0, 4, 8, 12, 16, 20, 24, 28 };


#define PINS_HIGH( register, bit ) register |= (1<<bit)
#define PINS_LOW( register, bit ) register &= ~(1<<bit)
/////////////////////////////////////////////////////////////////////////////
/*
//струтура для хранения настроек вывода - номера и порта
typedef struct outputs
{
    uint8_t pin;
    volatile uint8_t *portReg;
}outputs_t;
*/

typedef struct outputss
{
    volatile uint8_t  *PORT;      //PORT
    volatile uint8_t  *DDR;       //PORT
    volatile uint8_t  *IN;       //PORT
             uint8_t  PIN;
} GPIO_TypeDef;

    #define GPIOA &PORTA,&DDRA,&PINA
    #define GPIOB &PORTB,&DDRB,&PINB
    #define GPIOC &PORTC,&DDRC,&PINC
    #define GPIOD &PORTD,&DDRD,&PIND
    #define GPIOE &PORTE,&DDRE,&PINE
    #define GPIOG &PORTG,&DDRG,&PING

    GPIO_TypeDef PORT_A;
    GPIO_TypeDef PORT_B;
    GPIO_TypeDef PORT_C;
    GPIO_TypeDef PORT_D;
    GPIO_TypeDef PORT_E;
    GPIO_TypeDef PORT_G;


///////////////////////////////////////////////////////////////////////////PIN
//установить на выходе 1
void PIN_HIGH(GPIO_TypeDef *out)
{
    (*(out->PORT)) |= (1 <<out->PIN);
}

//установить на выходе 0
void PIN_LOW(GPIO_TypeDef *out)
{
    (*(out->PORT)) &= ~(1 <<out->PIN);
}

void PIN_IN(GPIO_TypeDef *out) //volatile  +
{
    *(out->DDR) &= ~(1<<out->PIN);  //
}

void PIN_OUT(GPIO_TypeDef *out) //volatile  +
{
    *(out->DDR) |= (1<<out->PIN);  //
}

//////////////////////////////////////////////////////////////////////////PORT
void PORT_OUT(GPIO_TypeDef *out) //volatile
{
    *(out->DDR) = 0xFF;  //
}

void PORT_IN(GPIO_TypeDef *out) //volatile
{
    *(out->DDR) = 0x00;  //
}
///////////////////////////////////////////////////////////////////////////////////

void Alarm_PIN()
{
    
    GPIO_TypeDef LEDD1,LEDD2;   //C
   
    LEDD1   ={GPIOG,4};
    LEDD2   ={GPIOG,5};    



    PIN_OUT(&LEDD1);
    PIN_OUT(&LEDD2);


    while (1)
    {
       PIN_HIGH(&LEDD1);
       PIN_HIGH(&LEDD2);
        _delay_ms(100);

        PIN_LOW(&LEDD1);
        PIN_LOW(&LEDD2);
        _delay_ms(100);
    }
}























/*
typedef struct
{
    GPIO_TypeDef *A;
    uint8_t      P;
} GPIO;
*/

/*
//это макросы для доступа к регистрам порта
#define PortReg(port) (*(port))
#define DirReg(port) (*((port) - 1))
#define PinReg(port) (*((port) - 2))

/*
//функция инициализации
void OUT_Init(outputs_t *out, uint8_t pin, volatile uint8_t *port, uint8_t level)
{
    //сохраняем настройки в структуру
    out->pin = pin;
    out->portReg = port;

    //конфигурируем вывод на выход
    (*(port-1)) |= (1<<pin);

    //задаем логический уровень
    if (level) {
        (*port) |= (1<<pin);
    }
    else{
        (*port) &= ~(1<<pin);
    }
}
*/






/*
//////////////////////////////////////////////////////////////////////////PIN
void PIN_HIGH(uint8_t volatile  *pReg,uint8_t PIN) //volatile 
{
   *(pReg-2)&= ~(1<<PIN);  //
   *(pReg-2)|=  (1<<PIN) ; //
   
    // *((pReg-1))&= ~~(1<<PIN);  //
}

void PIN_LOW(uint8_t volatile  *pReg,uint8_t PIN) //volatile  
{
    *(pReg-1)&= ~(0<<PIN);  //
    *(pReg-1)|=  (0<<PIN);
}
/*
void PIN_IN(uint8_t volatile  *pReg,uint8_t PIN) //volatile  +
{
    *(pReg) &= ~(1<<PIN);  //
}

void PIN_OUT(uint8_t volatile  *pReg,uint8_t PIN) //volatile  +
{
    *(pReg) |= (1<<PIN);  //
}

//////////////////////////////////////////////////////////////////////////PORT
void PORT_OUT(uint8_t volatile  *pReg) //volatile
{
    *(pReg) = 0xFF;  //
}

void PORT_IN(uint8_t volatile  *pReg) //volatile
{
    *(pReg) = 0x00;  //
}
/*
void PORT_HIGH(uint8_t volatile  *pReg) //volatile
{
    *(pReg-1) = 0xFF;  //
}
void PORT_LOW(uint8_t volatile  *pReg) //volatile
{
    *(pReg-1) = 0x00;  //
}

void PORT_DATA(uint8_t volatile  *pReg,uint8_t data) //volatile
{
    *(pReg) = data;  //
}
*/







/*
#define PINA     _SFR_IO8(0X00) //PIN
#define PORTA    _SFR_IO8(0X02) //PORT
#define PINB     _SFR_IO8(0X03) //PIN
#define PORTB    _SFR_IO8(0x05) //PORT
*/




void PIN_OUT(uint8_t volatile  *pReg,uint8_t PIN);

#endif /* Atmel*/
