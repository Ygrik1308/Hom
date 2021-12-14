#include "main.h"

 #ifndef _jtag_H
 #define _jtag_H


#define JTAG_PORT (GPIOC->ODR)
#define JTAG_PIN  (GPIOC->IDR)

#define TRST   0  //0  Grey
#define TCK    1  //1  Violet
#define TMS    2  //2  Blue
#define TDI    3  //3  Green
#define TDO    4  //4  Yellow

#define JTAG_INSTRUCTION_SIZE  32  // 8  //32
#define JTAG_TDO_BUFFER_LENGTH 4  //4



typedef struct{
	    		uint8_t data[4];
			   }JtagData;


typedef struct{
  	            GPIO	J_TRST;
	            GPIO    J_TCK;
	            GPIO    J_TMS;
	            GPIO    J_TDI;
	            GPIO    J_TDO;
				uint8_t data[4];
			  }Jtagsdata;


void jtag_tick( uint16_t jtag_buffer );

uint8_t jtag_tick_and_read( uint16_t jtag_buffer, uint8_t out_data ); //uint8_t & out_data

JtagData jtag( uint32_t instruction );
JtagData jtag_ID( uint32_t instruction );

uint16_t reverse_2bytes( uint16_t data );

uint8_t reverse_byte( uint8_t data );
JtagData jtag_ID( uint32_t instruction );
void jtag_init(GPIO_TypeDef *GPIOx);

/////////////////////////////////////////////////struktur



JtagData jtags_ID( uint32_t TDO_BUFFER_LENGTH, uint32_t  INSTRUCTION_SIZE, Jtagsdata G);
void jtags_tick( Jtagsdata G  );
uint8_t jtags_tick_and_read( Jtagsdata G , uint8_t out_data );

#endif /* LED_H */
