#include "main.h"
#ifdef AVR//HAL_I2C_MODULE_ENABLED
//#include "lcd.h"
//#include "string.h"
#include "stdio.h"
#include "GPIO_Atmel.h"
#include <avr/io.h>


    
//////////////////////////////////////////////////////////////////////////PIN
void PIN_HIGH(uint8_t volatile  *pReg,uint8_t PIN) //volatile -
{
    *(pReg-1)&= ~(1<<PIN);  //
    *(pReg-1)|=  (1<<PIN) ;
    
    // *((pReg-1))&= ~~(1<<PIN);  //
}

void PIN_LOW(uint8_t volatile  *pReg,uint8_t PIN) //volatile  +
{
    *(pReg-1)&= ~(0<<PIN);  //
    *(pReg-1)|=  (0<<PIN) ;
}

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
#endif /* Atmel*/
