
#ifdef jtag
#include "main.h"

 #ifndef _jtag_H
 #define _jtag_H


typedef struct{
	uint8_t data[4];
}JtagData;

void jtag_tick( uint16_t jtag_buffer );

uint8_t jtag_tick_and_read( uint16_t jtag_buffer, uint8_t out_data ); //uint8_t & out_data

JtagData jtag( uint32_t instruction);

uint16_t reverse_2bytes( uint16_t data );

uint8_t reverse_byte( uint8_t data );



#endif /* jtag.h */

#endif /* jtag */
