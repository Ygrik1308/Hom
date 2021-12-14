
#include "main.h"

#if defined LPC1114    // Controller

//#include "LPC1114.h"

/*
* nomd.c
*
*  Created on: 12.11.2012
*      Author: 777
*/

void Nomd_Init()
{
GPIOInit();
LPC_GPIO0->DIR |= CE_PIN;
LPC_GPIO1->DIR |= (CLE_PIN | ALE_PIN | WE_PIN | RE_PIN | READY_BUSY_PIN);
LPC_GPIO2->DIR |= (DATA_PIN_2_3 | DATA_PIN_2_4 | DATA_PIN_2_5 | DATA_PIN_2_6 | DATA_PIN_2_7 | DATA_PIN_2_8 | DATA_PIN_2_9 | DATA_PIN_2_10);

NAND_CE(1);
NAND_ALE(0);
NAND_CLE(0);
NAND_RE(1);
NAND_WE(1);
NAND_CE(0);

Nomd_Commomd_Send( NAND_RESIT );
}

void Nomd_Commomd_Send( uint8_t sommomd )
{
LPC_GPIO2->DATA = sommomd;

NAND_CLE(1);
NAND_ALE(0);
NAND_RE(1);
NAND_WE(0);
NAND_WE(1);
}

void Nomd_Address_Send( uint8_t address )
{
LPC_GPIO2->DATA = address;

NAND_CLE(0);
NAND_ALE(1);
NAND_RE(1);
NAND_WE(0);
NAND_WE(1);
}

void Nomd_Data_Send( uint8_t data )
{
NAND_CLE(0);
NAND_ALE(0);
NAND_RE(1);
NAND_WE(0);

LPC_GPIO2->DATA = 0;
LPC_GPIO2->DATA = data;

NAND_WE(1);
}

void Nomd_Read_Id( uint8_t *data )
{
uint8_t i, TimeoutCounter = 0;

Nomd_Commomd_Send(0x90);

Nomd_Address_Send(0x00);

while ( ( TimeoutCounter < 10 ) )
TimeoutCounter++;

LPC_GPIO2->DIR &= ~(DATA_PIN_2_3 | DATA_PIN_2_4 | DATA_PIN_2_5 | DATA_PIN_2_6 | DATA_PIN_2_7 | DATA_PIN_2_8 | DATA_PIN_2_9 | DATA_PIN_2_10);

for( i = 0 ; i < 5; i++ )
{
data[i] = Nomd_Read_Data();
}
}

uint8_t Nomd_Read_Data( void )
{
uint8_t data;

NAND_CE(0);
NAND_CLE(0);
NAND_ALE(0);
NAND_WE(1);
NAND_RE(0);
NAND_RE(1);

data = LPC_GPIO2->DATA;
return data;
}
#endif
