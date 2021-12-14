#include "main.h"
/////////////////////////////////////////////
#if defined JTAG_ID_TEST    // chip
///////////////////////////////////////////
#include "jtag.h"

 void jtag_init(GPIO_TypeDef *GPIOx)
 {
  PIN_OUT(GPIOx,TRST);  // 10  //0 +
  PIN_OUT(GPIOx,TCK);   // 11  //1 +  желтый
  PIN_OUT(GPIOx,TMS);   // 12  //2 +  зелёный
  PIN_OUT(GPIOx,TDI);   // 13  //3 +  фиолетовы
  PIN_IN (GPIOx,TDO);   // 14  //4  + �?иний

  PIN_LOW(GPIOx,TRST); //   10  //0 +
  PIN_LOW(GPIOx,TCK);   // 11  //1 +  желтый
  PIN_LOW(GPIOx,TMS);   // 12  //2 +  зелёный
  PIN_LOW(GPIOx,TDI);   // 13  //3 +  фиолетовы
 }
/*
#define TRST   0  //0  Grey
#define TCK    1  //1  Violet
#define TMS    2  //2  Blue
#define TDI    3  //3  Green
#define TDO    4  //4  Yellow
*/
// const uint8_t expected_data[JTAG_TDO_BUFFER_LENGTH] = { 0x3F, 0x40, 0x70, 0x09 }; // Atmega1281

void jtag_tick( uint16_t jtag_buffer )
{
    jtag_buffer &= ~(1<<TCK);
    JTAG_PORT = jtag_buffer;

    delay_nop(4);  //4

    jtag_buffer |= (1<<TCK);
    JTAG_PORT = jtag_buffer;

    delay_nop(4);

}

uint8_t jtag_tick_and_read( uint16_t jtag_buffer, uint8_t out_data ) //uint8_t & out_data
{
    out_data <<= 1;
    JTAG_PORT = jtag_buffer & ~(1<<TCK);

    delay_nop(4);

    out_data |= (JTAG_PIN >> TDO) & 0x01;
    JTAG_PORT = jtag_buffer | (1<<TCK);

    delay_nop(4);
    return out_data;
}

JtagData jtag( uint32_t instruction )
{
    uint16_t jtag_buffer = (1<<TRST) | (1<<TCK);
    const uint16_t tms = 1<<TMS;

    uint8_t data[JTAG_TDO_BUFFER_LENGTH];
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i ) data[i] = 0x00;

    for( uint8_t i=0; i<5; ++i ) jtag_tick( jtag_buffer | tms ); // TMS reset   <5
//
    jtag_tick( jtag_buffer );
    jtag_tick( jtag_buffer | tms ); // select DR scan
    jtag_tick( jtag_buffer | tms ); // select IR scan
    jtag_tick( jtag_buffer );   // capture IR
    jtag_tick( jtag_buffer );   // shift IR

    for( uint8_t i=0; i<JTAG_INSTRUCTION_SIZE-1; ++i ){
        jtag_tick ( jtag_buffer | (( instruction & 0x01 ) << TDI));  // shift IR
        instruction >>= 1;
    } // the last bit goes with tms
    jtag_tick( jtag_buffer | ((( instruction & 0x01 ) << TDI) | tms) ); // Exit1 IR
    jtag_tick( jtag_buffer | tms );                        // Update IR
//
    jtag_tick( jtag_buffer ); // idle

    jtag_tick( jtag_buffer | tms ); // select DR scan
    jtag_tick( jtag_buffer );   // capture DR
    jtag_tick( jtag_buffer );   // shift DR

    for(uint8_t i=0; i<8; ++i) data[0] = jtag_tick_and_read( jtag_buffer, data[0] );
    for(uint8_t i=0; i<8; ++i) data[1] = jtag_tick_and_read( jtag_buffer, data[1] );
    for(uint8_t i=0; i<8; ++i) data[2] = jtag_tick_and_read( jtag_buffer, data[2] );
    for(uint8_t i=0; i<7; ++i) data[3] = jtag_tick_and_read( jtag_buffer, data[3] );
    data[3] = jtag_tick_and_read( jtag_buffer | tms, data[3] ); // the last bit goes with tms

    for(uint8_t i=0; i<5; ++i) jtag_tick( jtag_buffer | tms ); // TMS reset  //  <5
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i )
    {
        data[i] = reverse_byte( data[i] );
    }

    JTAG_PORT = (1<<TMS) | (1<<TCK) | (1<<TRST) | (1<<TDI);

	JtagData jdata;
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i )
    	jdata.data[i] = data[i];
    return jdata;
}


JtagData jtag_ID( uint32_t instruction )
{
    uint16_t jtag_buffer = (1<<TRST) | (1<<TCK);
    const uint16_t tms = 1<<TMS;

    uint8_t data[JTAG_TDO_BUFFER_LENGTH];
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i ) data[i] = 0x00;

    for( uint8_t i=0; i<5; ++i ) jtag_tick( jtag_buffer | tms ); // TMS reset   <5

    jtag_tick( jtag_buffer ); // idle

    jtag_tick( jtag_buffer | tms ); // select DR scan
    jtag_tick( jtag_buffer );   // capture DR
    jtag_tick( jtag_buffer );   // shift DR

    for(uint8_t i=0; i<8; ++i) data[0] = jtag_tick_and_read( jtag_buffer, data[0] );
    for(uint8_t i=0; i<8; ++i) data[1] = jtag_tick_and_read( jtag_buffer, data[1] );
    for(uint8_t i=0; i<8; ++i) data[2] = jtag_tick_and_read( jtag_buffer, data[2] );
    for(uint8_t i=0; i<7; ++i) data[3] = jtag_tick_and_read( jtag_buffer, data[3] );
    data[3] = jtag_tick_and_read( jtag_buffer | tms, data[3] ); // the last bit goes with tms

    for(uint8_t i=0; i<5; ++i) jtag_tick( jtag_buffer | tms ); // TMS reset  //  <5
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i )
    {
        data[i] = reverse_byte( data[i] );
    }

    JTAG_PORT = (1<<TMS) | (1<<TCK) | (1<<TRST) | (1<<TDI);

	JtagData jdata;
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i )
    	jdata.data[i] = data[i];
    return jdata;
}




uint16_t reverse_2bytes( uint16_t data )
{
    uint16_t reversed_data = 0x0000;
    for( uint8_t i=0; i<16; ++i )
    {
        reversed_data <<= 1;
        reversed_data |= data & 1;
        data >>= 1;
    }
    return reversed_data;
}

uint8_t reverse_byte( uint8_t data )
{
    uint8_t reversed_data = 0x00;
    for( uint8_t i=0; i<8; ++i )
    {
        reversed_data <<= 1;
        reversed_data |= data & 1;
        data >>= 1;
    }
    return reversed_data;
}



//////////////////////////////////////////////////////////////////////////////////////////struktur
//////////////////////////////////////////////////////////////////////////////////////////Structur
void jtags_init(Jtagsdata G)
{
	  PINS_OUT(G.J_TRST);  // 10  //0 +
	  PINS_OUT(G.J_TCK);   // 11  //1 +  желтый
	  PINS_OUT(G.J_TMS);   // 12  //2 +  зелёный
	  PINS_OUT(G.J_TDI);   // 13  //3 +  фиолетовы
	  PINS_IN (G.J_TDO);   // 14  //4  + �?иний

	  PINS_LOW(G.J_TRST); //   10  //0 +
	  PINS_LOW(G.J_TCK);   // 11  //1 +  желтый
	  PINS_LOW(G.J_TMS);   // 12  //2 +  зелёный
	  PINS_LOW(G.J_TDI);   // 13  //3 +  фиолетовы
}

JtagData jtags_ID(uint32_t TDO_BUFFER_LENGTH, uint32_t  INSTRUCTION_SIZE, Jtagsdata G )
{
//    uint16_t jtag_buffer = (1<<TRST) | (1<<TCK);
//    const uint16_t tms = 1<<TMS;

    uint8_t data[JTAG_TDO_BUFFER_LENGTH];
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i ) data[i] = 0x00;

    for( uint8_t i=0; i<5; ++i ) jtags_tick(G); // TMS reset   <5

    jtags_tick( G ); // idle

    jtags_tick( G ); // select DR scan | tms
    jtags_tick( G );   // capture DR
    jtags_tick( G );   // shift DR

    for(uint8_t i=0; i<8; ++i) data[0] = jtags_tick_and_read( G , data[0] );
    for(uint8_t i=0; i<8; ++i) data[1] = jtags_tick_and_read( G , data[1] );
    for(uint8_t i=0; i<8; ++i) data[2] = jtags_tick_and_read( G , data[2] );
    for(uint8_t i=0; i<7; ++i) data[3] = jtags_tick_and_read( G , data[3] );

    data[3] = jtags_tick_and_read( G , data[3] ); // the last bit goes with tms

    for(uint8_t i=0; i<5; ++i) jtags_tick( G ); // TMS reset  //  <5
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i )
    {
        data[i] = reverse_byte( data[i] );
    }

    PINS_HIGH(G.J_TMS);
    PINS_HIGH(G.J_TCK);
    PINS_HIGH(G.J_TRST);
    PINS_HIGH(G.J_TDI);

	JtagData jdata;
    for( uint8_t i=0; i<JTAG_TDO_BUFFER_LENGTH; ++i )
    	jdata.data[i] = data[i];
    return jdata;
}


void jtags_tick(  Jtagsdata G  )
{
//    jtag_buffer &= ~(1<<TCK);

    PINS_LOW(G.J_TCK);
    PINS_HIGH(G.J_TRST);
    PINS_HIGH(G.J_TMS);

 //   JTAG_PORT = jtag_buffer;

    delay_nop(4);  //4

    PINS_LOW(G.J_TCK);
    PINS_HIGH(G.J_TRST);
    PINS_HIGH(G.J_TMS);


//    jtag_buffer |= (1<<TCK);
//    JTAG_PORT = jtag_buffer;

    delay_nop(4);

}


uint8_t jtags_tick_and_read( Jtagsdata G , uint8_t out_data ) //uint8_t & out_data
{
    out_data <<= 1;
    PINS_LOW(G.J_TCK);
//    JTAG_PORT = jtag_buffer & ~(1<<TCK);

    delay_nop(4);


//    PINS_IN(G.J_TDO);
    out_data |= READS_PIN(G.J_TDO)& 0x01;
//    out_data |=  ;

    PINS_HIGH(G.J_TCK);

//    JTAG_PORT = jtag_buffer | (1<<TCK);

    delay_nop(4);
    return out_data;
}






////TEST
//JtagData jdata =  jtag( 0x02620018);  //0x01
//
//                jtag( 0x83e70b13);  //0x01
//JtagData jdata =  jtag( 0x95a4f1e0);  //0x01
//
//	//JtagData jdata = { 0x01, 0x55, 0xAA, 0xFF };
//	char str[20];
//	sprintf(str, "%.2X %.2X %.2X %.2X",jdata.data[0],
//									   jdata.data[1],
//									   jdata.data[2],
//									   jdata.data[3]);
//
//	moveXY(&scr,0,1);
//	lsd_print(&scr, str);
//	HAL_Delay(500);







/*
  JtagData jdata =  jtag( 0x02620018);  //0x01

                  jtag( 0x83e70b13);  //0x01
JtagData jdata =  jtag( 0x95a4f1e0);  //0x01

	//JtagData jdata = { 0x01, 0x55, 0xAA, 0xFF };
	char str[20];
	sprintf(str, "%.2X %.2X %.2X %.2X",jdata.data[0],
									   jdata.data[1],
									   jdata.data[2],
									   jdata.data[3]);

	moveXY(&scr,0,1);
	lsd_print(&scr, str);
	HAL_Delay(500);

*/

#endif //jtag

