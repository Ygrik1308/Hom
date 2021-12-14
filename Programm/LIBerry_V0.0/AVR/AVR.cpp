
#define F_CPU 16000000UL  // clock speed
#include <avr/io.h>
#include <util/delay.h>

#include <iostream>
#include <fstream>
#include <string>

#include "../h/utils.hpp"


// On-board led
#define led1 &DDRG,3                     //PING 4  PORTG,
#define led2 &DDRG,4                     //PING 5  PORTG,
// On-board buttons
#define Button_DN  GPIOG,0                //PING 0
#define Button_OK  GPIOG,1                //PING 1
#define Button_UP  GPIOG,2                //PING 3



#define IORESET             &GPIOD,0    //
#define SCLK                &GPIOD,1    //
#define nCS                 &GPIOD,2    //
#define SDO                 &GPIOD,3
#define SDIO                &GPIOD,4
#define nWR                 &GPIOD,5
#define nRD                 &GPIOD,6

#define ADDR5               &GPIOL,0
#define ADDR4               &GPIOL,1
#define ADDR3               &GPIOL,2
#define ADDR2               &GPIOL,3
#define ADDR1               &GPIOL,4
#define ADDR0               &GPIOL,5

void set_data_as_input()  { DDRA = 0x00; }
void set_data_as_output() { DDRA = 0xFF; }



class chip // имя класса
{
public: // спецификатор доступа
    void port_init() // функция (метод класса) выводящая сообщение на экран
    {
    	std::ofstream out("E:\\hello.txt", std::ios::app);
    	if (out.is_open())
    	{
    	    //out << "Welcome to CPP" << std::endl;
    	}
    	out.close();
    }

}; // конец объявления класса CppStudio



/*
void sp_instruction_byte( uint8_t address )
{
for( uint8_t i = 0; i < 8; ++i )
{
( address & 0x80 ) ? PIN_HIGH( SDIO ) : PIN_LOW( SDIO );
PIN_HIGH(SCLK);
address <<= 1;
PIN_LOW(PORTJ,6);   //?????
}
}

uint32_t sp_read( uint8_t address, const uint8_t number_of_bytes_to_read = 1 )
{
uint32_t data = 0;
PIN_LOW( nCS );
PINS_OUT( DDRJ, SDIO );  // set as output
PIN_HIGH( address, 7 );  // read
sp_instruction_byte( address );
PINS_IN( DDRJ, SDIO );  // set as input
for( uint8_t i = 0; i < number_of_bytes_to_read * 8; ++i ) {
PIN_HIGH( SCLK );
data <<= 1;
PIN_LOW( SCLK );
//       data |= READ( SDIO );  !!
}
PIN_HIGH( nCS );
return data;
}

void sp_write( uint8_t address, uint32_t data,const uint8_t number_of_bytes_to_write = 1 )
{
PIN_LOW( nCS );
//    PIN_OUT( DDRJ, SDIO );    // set as output
//    PINS_IN( address, 7 );  // write
sp_instruction_byte( address );
uint32_t mask = 0;
switch( number_of_bytes_to_write )
{
case 1: mask = 0x00000080; break;
case 2: mask = 0x00008000; break;
case 3: mask = 0x00800000; break;
case 4: mask = 0x80000000; break;
}
for( uint8_t i = 0; i < number_of_bytes_to_write * 8; ++i )
{
( data & mask ) ? PIN_HIGH( SDIO ) : PIN_LOW( SDIO );
PIN_HIGH( SCLK );
data <<= 1;
PIN_LOW( SCLK );
}
//   PINS_IN( DDRJ, SDIO );  // set as input
PIN_HIGH( nCS );
}

void btn_dn_routine()
{
// DDRA  = 0xFF;
// PORTA = 0x58;

set_data_as_input();

_delay_us( 1 );
PIN_LOW( nRD );
_delay_us( 1 );
PIN_HIGH( nRD );
}

void btn_ok_routine()
{
//    PINS_DECLARATION
toggle_bits(led1);   //Edited
sp_write( 0x00,0x00000058,4);
}

void btn_up_routine()
{
//    PINS_DECLARATION
toggle_bits(led2);

sp_read( 0x00, 4 );
sp_read( 0x0b, 2 );
}
*/


/*
int main( void )
{
    //PINS_DECLARATION
    init();


    while( 1 )
    {
        bool button_was_pressed = false;
        for( uint8_t d = 0; d < 255; d++ )
        {
            if( ( PING & ( 1 << Button_DN ) ) == 0 )
            {
                d = 0;
                if( !button_was_pressed )
                {
                    button_was_pressed = true;
                    //                   btn_dn_routine();
                }
            }
            if( ( PING & ( 1 << Button_OK ) ) == 0 )
            {
                d = 0;
                if( !button_was_pressed ) {
                    button_was_pressed = true;
                    //                  btn_ok_routine();
                }
            }
            if( ( PING & ( 1 << Button_UP ) ) == 0 )
            {
                d = 0;
                if( !button_was_pressed )
                {
                    button_was_pressed = true;
                    //                   btn_up_routine();
                }
            }
  //          toggle_bits(led2);
  
        }         //for
        
        

        
        
    }    //while

} //main
*/

//    BUTTON_PROCESSING_LOOP_START();
/*    PROCESS_BUTTON( IS_LOW( Button_UP ), btn_up_routine );
PROCESS_BUTTON( IS_LOW( Button_OK ), btn_ok_routine );
PROCESS_BUTTON( IS_LOW( Button_DN ), btn_dn_routine );
BUTTON_PROCESSING_LOOP_END();
*/
