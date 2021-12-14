#include "main.h"

#if defined MT46V32M16TG_5BIT

#ifndef __MT46V32M16TG-5BIT_H
#define __MT46V32M16TG-5BIT_H
//————————————————

#include "stm32f7xx_hal.h"
#include "string.h"
#include "stdint.h"
//————————————————
#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
#define SDRAM_BANK_ADDR ((uint32_t)0xC0000000)   //0xC0000000
//————————————————

typedef struct
{
	uint8_t	Error;
	uint8_t OK;
} Data_read;

void IS42S16100H_7TL_init(SDRAM_HandleTypeDef *hsdram);
Data_read IS42S16100H_write_read(uint16_t data_w,uint32_t byte);

//————————————————
#endif /* __IS42S16100H_7TL_H */


#endif  //IS42S16100H_7TL_H
