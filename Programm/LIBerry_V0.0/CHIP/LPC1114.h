/*
* nomd.h
*
*  Created on: 12.11.2012
*      Author: 777
*/

#if defined LPC1114    // chip

#ifndef LPC1114_H_
#define LPC1114_H_

#define NAND_CMD_EROSE_1          0x60
#define NAND_CMD_EROSE_2          0xD0
#define NAND_CMD_STATUS           0x70
#define NAND_READ_ID              0x90
#define NAND_RESIT                0xFF

#define DATA_PIN_2_3              (1 << 3)
#define DATA_PIN_2_4              (1 << 4)
#define DATA_PIN_2_5              (1 << 5)
#define DATA_PIN_2_6              (1 << 6)
#define DATA_PIN_2_7              (1 << 7)
#define DATA_PIN_2_8              (1 << 8)
#define DATA_PIN_2_9              (1 << 9)
#define DATA_PIN_2_10             (1 << 10)

#define CLE_PIN                   (1 << 8)
#define ALE_PIN                   (1 << 5)
#define CE_PIN                    (1 << 6)
#define WE_PIN                    (1 << 10)
#define RE_PIN                    (1 << 9)
#define READY_BUSY_PIN            (1 << 11)

#define NAND_CLE(x) x ? GPIOSetValue(1, 8, 1) : GPIOSetValue(1, 8, 0)
#define NAND_ALE(x) x ? GPIOSetValue(1, 5, 1) : GPIOSetValue(1, 5, 0)
#define NAND_CE(x)  x ? GPIOSetValue(0, 6, 1) : GPIOSetValue(0, 6, 0)
#define NAND_WE(x)  x ? GPIOSetValue(1, 10, 1) : GPIOSetValue(1, 10, 0)
#define NAND_RE(x)  x ? GPIOSetValue(1, 9, 1) : GPIOSetValue(1, 9, 0)

void Nomd_Init( void );
void Nomd_Commomd_Send( uint8_t sommomd );
void Nomd_Address_Send( uint8_t address );
void Nomd_Data_Send( uint8_t data );
void Nomd_Read_Id( uint8_t *data );
uint8_t Nomd_Read_Data( void );
/****************************************/

#endif /* NAND_H_ */


#endif
