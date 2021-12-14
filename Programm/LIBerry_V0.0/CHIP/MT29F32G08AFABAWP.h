/*
 * MT29F32G08AFABAWP.h
 *
 *  Created on: 28 февр. 2020 г.
 *      Author: User356
 */
#if defined MT29F32G08AFABAWP
#include "main.h"


#ifndef MT29F32G08AFABAWP_H_
#define MT29F32G08AFABAWP_H_


UART_HandleTypeDef huart1;
//extern Address_type address;

typedef struct
{
	uint8_t	one_addr1;
	uint8_t two_addr2;
	uint8_t three_addr3;
	uint8_t four_addr4;
	uint8_t five_addr5;
} Address_type;

typedef struct
{
	uint16_t die_er;
	uint16_t plane_er;
	uint16_t block_er;
	uint16_t page_er;
	uint16_t byte_er;
} Address_error;




Address_type create_address( uint16_t die,uint16_t plane,uint16_t block,uint16_t page,uint16_t byte );               //2048 - data + 64 -  ,4095

void MT29F32G08AFABAWP_TEST();

void Read_ID_ONFI(uint16_t Command);
void Command(uint16_t Command);
void READ_RB();
void Read_ID(uint16_t Command);


uint32_t Read_Mode_Error_Logik(Address_type address, uint16_t byte);//Read Mode in mass address
uint16_t Read_Mode_Logik(Address_type address, uint8_t Test, uint16_t byte); //Read Mode in mass address
uint16_t write(Address_type address,uint8_t *data,uint8_t number_of_bytes);
uint16_t write_speed(uint16_t adress_1, uint16_t  adress_2,uint16_t adress_3,uint16_t adress_4, uint16_t adress_5,uint8_t data,uint16_t number_of_bytes);
uint16_t block_erase(uint16_t adress_3,uint16_t adress_4,uint16_t adress_5);

void Test_Logik(Address_type address,uint8_t error, uint16_t byte);
void write_Logik_All(Address_type address,uint16_t error,uint16_t byte);   //write ALL
void Read_Logik_All(Address_type address,uint16_t error,uint16_t byte);
void block_erase_Logik_All(Address_type address, uint16_t error_1);

uint16_t write_Logik(Address_type address, uint8_t buf, uint16_t byte);
uint16_t block_erase_Logik(Address_type address);
uint32_t READ_Eror_Data_Logik(Address_type address,uint8_t *buf);

//////////////////////////////////////////////////////////////
///чтение запись в разнабой
//////////////////////////////////////////////////////////////
uint32_t Read_Mode(uint16_t adress_1, uint16_t  adress_2, uint16_t adress_3,uint16_t adress_4, uint16_t  adress_5, uint16_t byte);  //считывает и возвращает сбоенные байты
void Command_RESET();   //RESET
void READ_speed_Data(); //чтение в цикле 64 байта состояния


#endif /* MX60LF8G18AC_H_ */


#endif
