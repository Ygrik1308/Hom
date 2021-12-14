/*
 * flash_Nand_K9F1G08U0B.h
 *
 *  Created on: 23 апр. 2020 г.
 *      Author: User356
 */
#include "main.h"
#if defined K9WAG08U1D
#ifndef _K9F1G08U0B_H_
#define _K9F1G08U0B_H_



UART_HandleTypeDef huart1;







typedef struct
{
	uint8_t	column_addr1;
	uint8_t column_addr2;
	uint8_t row_addr3;
	uint8_t row_addr4;
	uint8_t row_addr5;
} Address_type;

typedef struct
{
	uint16_t Plane_er;
	uint16_t Block_er;
	uint16_t Page_er;
	uint16_t byte_er;
} Address_error;

Address_type create_address(uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column);

//commands
uint8_t Command_RESET();
void IN_PORT_K9WAG08U1D();

//procedures
uint32_t Read_Mode_Error_Logik(Address_type address, uint16_t byte,uint8_t time);          //
uint32_t Read_Mode_Error_Logik_2(Address_type address, uint16_t byte,uint8_t time);
uint16_t write_Logik(Address_type address, uint8_t data, uint16_t byte,uint16_t time,uint32_t error); //buf; //buf	//
uint16_t Read_Mode_Logik(Address_type address, uint8_t test_data, uint16_t byte,uint8_t time);

//function
uint32_t READ_Eror_Data_Logik(Address_type address,uint8_t time);
void write_Logik_All(Address_type address,uint16_t error,uint16_t byte,uint16_t data,uint8_t time);
void write_Logik_All_Adress(Address_type address,uint16_t error,uint16_t byte,uint16_t data,uint8_t time);  //write ALL
void Read_Logik_All(Address_type address,uint16_t error,uint16_t byte,uint16_t data,uint8_t time);
uint16_t block_erase_Logik(Address_type address,uint8_t time,uint8_t error);


void block_erase_Logik_All(Address_type address, uint16_t error_1,uint16_t time);



#endif /* H_K9F1G08U0B_H_ */


#endif
