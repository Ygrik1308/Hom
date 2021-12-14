#include "main.h"

#if defined xxxxx  // chip
#include "RS232.h"

typedef struct
{
	uint8_t pollingMode, flushFilter;
    float sensorAcqTime, intervalRespTime;
} __attribute__ ((packed)) AcqParams;




void ID_Sendrequest()
{
	_Structur data_ID={0};
	_Structur sendata = {0x500,0x01,0x4DFE};
	CommProtocol_SendData(sendata,1);
	CommProtocol_readData(data_ID,1);
	printf("ID_comand:%u\n",data_ID.command);
	printf("ID_DATA:%u\n"  ,data_ID.data);
	printf("ID_CRC:%u\n"   ,data_ID.CRC_);
}

//
// Put together the frame to send to the unit
//

uint16_t CommProtocol_SendData(_Structur data,uint8_t byte)   // check channel 255
{

/////////////////////////////////////////ERRoR
	_Bool	err_ORE=0;   //<<3 Ã�Å¾Ã‘Ë†Ã�Â¸Ã�Â±Ã�ÂºÃ�Â° Ã�Â¿Ã�ÂµÃ‘â‚¬Ã�ÂµÃ�Â¿Ã�Â¾Ã�Â»Ã�Â½Ã�ÂµÃ�Â½Ã�Â¸Ã‘ï¿½. Ã�Â¤Ã�Â»Ã�Â°Ã�Â³ Ã‘Æ’Ã‘ï¿½Ã‘â€šÃ�Â°Ã�Â½Ã�Â°Ã�Â²Ã�Â»Ã�Â¸Ã�Â²Ã�Â°Ã�ÂµÃ‘â€šÃ‘ï¿½Ã‘ï¿½ Ã�Â² Ã‘ï¿½Ã�Â»Ã‘Æ’Ã‘â€¡Ã�Â°Ã�Âµ, Ã�ÂµÃ‘ï¿½Ã�Â»Ã�Â¸ Ã�Â² Ã�Â¿Ã‘â‚¬Ã�Â¸Ã�ÂµÃ�Â¼Ã�Â½Ã‘â€¹Ã�Â¹ Ã�Â±Ã‘Æ’Ã‘â€žÃ�ÂµÃ‘â‚¬Ã�Â½Ã‘â€¹Ã�Â¹ Ã‘â‚¬Ã�ÂµÃ�Â³Ã�Â¸Ã‘ï¿½Ã‘â€šÃ‘â‚¬ Ã�Â¿Ã�Â¾Ã‘ï¿½Ã‘â€šÃ‘Æ’Ã�Â¿Ã�Â¸Ã�Â»Ã�Â¾ Ã�Â½Ã�Â¾Ã�Â²Ã�Â¾Ã�Âµ Ã�Â´Ã�Â°Ã�Â½Ã�Â½Ã�Â¾Ã�Âµ, Ã�Â° Ã�Â¿Ã‘â‚¬Ã�ÂµÃ�Â´Ã‘â€¹Ã�Â´Ã‘Æ’Ã‘â€°Ã�ÂµÃ�Âµ Ã‘ï¿½Ã‘â€¡Ã�Â¸Ã‘â€šÃ�Â°Ã�Â½Ã�Â¾ Ã�Â½Ã�Âµ Ã�Â±Ã‘â€¹Ã�Â»Ã�Â¾. Ã�Â¢.Ã�Âµ. Ã�Â¿Ã‘â‚¬Ã�Â¸ Ã�Â¿Ã�Â¾Ã‘â€šÃ�ÂµÃ‘â‚¬Ã�Âµ Ã�Â´Ã�Â°Ã�Â½Ã�Â½Ã�Â¾Ã�Â³Ã�Â¾.
	_Bool	err_NE=0;	 //<<2 Ã�Â¤Ã�Â»Ã�Â°Ã�Â³ Ã‘Æ’Ã‘ï¿½Ã‘â€šÃ�Â°Ã�Â½Ã�Â°Ã�Â²Ã�Â»Ã�Â¸Ã�Â²Ã�Â°Ã�ÂµÃ‘â€šÃ‘ï¿½Ã‘ï¿½ Ã�Â¿Ã‘â‚¬Ã�Â¸ Ã�Â²Ã‘â€¹Ã�Â´Ã�ÂµÃ�Â»Ã�ÂµÃ�Â½Ã�Â¸Ã�Â¸ Ã‘Ë†Ã‘Æ’Ã�Â¼Ã�Â° Ã�Â²Ã�Â¾ Ã�Â²Ã‘â€¦Ã�Â¾Ã�Â´Ã�Â½Ã�Â¾Ã�Â¼ Ã‘ï¿½Ã�Â¸Ã�Â³Ã�Â½Ã�Â°Ã�Â»Ã�Âµ. Ã�ï¿½Ã�Â°Ã�Â»Ã�Â¸Ã‘â€¡Ã�Â¸Ã�Âµ Ã‘Ë†Ã‘Æ’Ã�Â¼Ã�Â° Ã�Â¾Ã�Â¿Ã‘â‚¬Ã�ÂµÃ�Â´Ã�ÂµÃ�Â»Ã‘ï¿½Ã�ÂµÃ‘â€šÃ‘ï¿½Ã‘ï¿½ Ã�ÂºÃ�Â°Ã�Âº Ã‘ï¿½Ã�Â»Ã�Â¸Ã‘Ë†Ã�ÂºÃ�Â¾Ã�Â¼ Ã‘â€¡Ã�Â°Ã‘ï¿½Ã‘â€šÃ�Â¾Ã�Âµ Ã�Â¿Ã�ÂµÃ‘â‚¬Ã�ÂµÃ�ÂºÃ�Â»Ã‘Å½Ã‘â€¡Ã�ÂµÃ�Â½Ã�Â¸Ã�Âµ Ã�Â²Ã‘â€¦Ã�Â¾Ã�Â´Ã�Â½Ã�Â¾Ã�Â³Ã�Â¾ Ã‘ï¿½Ã�Â¸Ã�Â³Ã�Â½Ã�Â°Ã�Â»Ã�Â°.
	_Bool	err_FE=0;	 //<<1 Ã�Å¾Ã‘Ë†Ã�Â¸Ã�Â±Ã�ÂºÃ�Â° Ã�Â¿Ã‘â‚¬Ã�Â¸Ã�ÂµÃ�Â¼Ã�Â° Ã‘â€žÃ‘â‚¬Ã�ÂµÃ�Â¹Ã�Â¼Ã�Â° (Ã�ÂºÃ�Â°Ã�Â´Ã‘â‚¬Ã�Â°). Ã�â€™Ã�Â¾Ã�Â·Ã�Â½Ã�Â¸Ã�ÂºÃ�Â°Ã�ÂµÃ‘â€š, Ã�ÂºÃ�Â¾Ã�Â³Ã�Â´Ã�Â° Ã�Â½Ã�Âµ Ã�Â±Ã‘â€¹Ã�Â» Ã�Â²Ã‘â€¹Ã�Â´Ã�ÂµÃ�Â»Ã�ÂµÃ�Â½ Ã‘ï¿½Ã‘â€šÃ�Â¾Ã�Â¿-Ã�Â±Ã�Â¸Ã‘â€š. Ã�Â¢.Ã�Âµ. Ã�Â¿Ã�Â¾Ã‘ï¿½Ã�Â»Ã�Âµ Ã�Â¿Ã‘â‚¬Ã�Â¸Ã�ÂµÃ�Â¼Ã�Â° Ã‘ï¿½Ã‘â€šÃ�Â°Ã‘â‚¬Ã‘â€šÃ�Â¾Ã�Â²Ã�Â¾Ã�Â³Ã�Â¾ Ã�Â±Ã�Â¸Ã‘â€šÃ�Â° Ã�Â¸  8 Ã�Â±Ã�Â¸Ã‘â€šÃ�Â¾Ã�Â² Ã�Â´Ã�Â°Ã�Â½Ã�Â½Ã‘â€¹Ã‘â€¦ Ã�Â½Ã�Â° Ã�Â¼Ã�ÂµÃ‘ï¿½Ã‘â€šÃ�Âµ Ã‘ï¿½Ã‘â€šÃ�Â¾Ã�Â¿Ã�Â¾Ã�Â²Ã�Â¾Ã�Â³Ã�Â¾ Ã�Â±Ã�Â¸Ã‘â€šÃ�Â° UART Ã‘ï¿½Ã‘â€¡Ã�Â¸Ã‘â€šÃ�Â°Ã�Â» Ã‘ï¿½Ã�Â¸Ã�Â³Ã�Â½Ã�Â°Ã�Â» Ã�Â½Ã�Â¸Ã�Â·Ã�ÂºÃ�Â¾Ã�Â³Ã�Â¾ Ã‘Æ’Ã‘â‚¬Ã�Â¾Ã�Â²Ã�Â½Ã‘ï¿½.
	_Bool	err_PE=0;    //<<0 error parity.
	uint16_t error;
/////////////////////////////////////////
	uint8_t	status=0;
/////////////////////////////////////////

	for(uint16_t d1=0; d1<byte; d1++)  //1
	{

	  status=USART2->SR;
	  while((status)!=0xC0) //??
	  {
		  if((err_PE  & (status<<0))==1){printf("ERROR_PE\n") ;error++;}
		  if((err_FE  & (status<<1))==1){printf("ERROR_FE\n") ;error++;}
		  if((err_NE  & (status<<2))==1){printf("ERROR_NE\n") ;error++;}
		  if((err_ORE & (status<<3))==1){printf("ERROR_ORE\n");error++;}
	  } // buffer registr empty


// send
//      while ((USART2->SR & USART_SR_TXE) == 0){}
//      USART_SR_TXE=  0x1UL << (7U)
      USART2->DR = data.command;
      USART2->DR = data.data;
      USART2->DR = data.CRC_;

      printf("UART_SEND\n");
	}
	if(error>255){Alarm(GPIOA);}

	return (error);

}

void CommProtocol_readData(_Structur *data,uint8_t byte)
{
/////////////////////////////////////////ERRoR
	_Bool	err_ORE=0;   //<<3 Ã�Å¾Ã‘Ë†Ã�Â¸Ã�Â±Ã�ÂºÃ�Â° Ã�Â¿Ã�ÂµÃ‘â‚¬Ã�ÂµÃ�Â¿Ã�Â¾Ã�Â»Ã�Â½Ã�ÂµÃ�Â½Ã�Â¸Ã‘ï¿½. Ã�Â¤Ã�Â»Ã�Â°Ã�Â³ Ã‘Æ’Ã‘ï¿½Ã‘â€šÃ�Â°Ã�Â½Ã�Â°Ã�Â²Ã�Â»Ã�Â¸Ã�Â²Ã�Â°Ã�ÂµÃ‘â€šÃ‘ï¿½Ã‘ï¿½ Ã�Â² Ã‘ï¿½Ã�Â»Ã‘Æ’Ã‘â€¡Ã�Â°Ã�Âµ, Ã�ÂµÃ‘ï¿½Ã�Â»Ã�Â¸ Ã�Â² Ã�Â¿Ã‘â‚¬Ã�Â¸Ã�ÂµÃ�Â¼Ã�Â½Ã‘â€¹Ã�Â¹ Ã�Â±Ã‘Æ’Ã‘â€žÃ�ÂµÃ‘â‚¬Ã�Â½Ã‘â€¹Ã�Â¹ Ã‘â‚¬Ã�ÂµÃ�Â³Ã�Â¸Ã‘ï¿½Ã‘â€šÃ‘â‚¬ Ã�Â¿Ã�Â¾Ã‘ï¿½Ã‘â€šÃ‘Æ’Ã�Â¿Ã�Â¸Ã�Â»Ã�Â¾ Ã�Â½Ã�Â¾Ã�Â²Ã�Â¾Ã�Âµ Ã�Â´Ã�Â°Ã�Â½Ã�Â½Ã�Â¾Ã�Âµ, Ã�Â° Ã�Â¿Ã‘â‚¬Ã�ÂµÃ�Â´Ã‘â€¹Ã�Â´Ã‘Æ’Ã‘â€°Ã�ÂµÃ�Âµ Ã‘ï¿½Ã‘â€¡Ã�Â¸Ã‘â€šÃ�Â°Ã�Â½Ã�Â¾ Ã�Â½Ã�Âµ Ã�Â±Ã‘â€¹Ã�Â»Ã�Â¾. Ã�Â¢.Ã�Âµ. Ã�Â¿Ã‘â‚¬Ã�Â¸ Ã�Â¿Ã�Â¾Ã‘â€šÃ�ÂµÃ‘â‚¬Ã�Âµ Ã�Â´Ã�Â°Ã�Â½Ã�Â½Ã�Â¾Ã�Â³Ã�Â¾.
	_Bool	err_NE=0;	 //<<2 Ã�Â¤Ã�Â»Ã�Â°Ã�Â³ Ã‘Æ’Ã‘ï¿½Ã‘â€šÃ�Â°Ã�Â½Ã�Â°Ã�Â²Ã�Â»Ã�Â¸Ã�Â²Ã�Â°Ã�ÂµÃ‘â€šÃ‘ï¿½Ã‘ï¿½ Ã�Â¿Ã‘â‚¬Ã�Â¸ Ã�Â²Ã‘â€¹Ã�Â´Ã�ÂµÃ�Â»Ã�ÂµÃ�Â½Ã�Â¸Ã�Â¸ Ã‘Ë†Ã‘Æ’Ã�Â¼Ã�Â° Ã�Â²Ã�Â¾ Ã�Â²Ã‘â€¦Ã�Â¾Ã�Â´Ã�Â½Ã�Â¾Ã�Â¼ Ã‘ï¿½Ã�Â¸Ã�Â³Ã�Â½Ã�Â°Ã�Â»Ã�Âµ. Ã�ï¿½Ã�Â°Ã�Â»Ã�Â¸Ã‘â€¡Ã�Â¸Ã�Âµ Ã‘Ë†Ã‘Æ’Ã�Â¼Ã�Â° Ã�Â¾Ã�Â¿Ã‘â‚¬Ã�ÂµÃ�Â´Ã�ÂµÃ�Â»Ã‘ï¿½Ã�ÂµÃ‘â€šÃ‘ï¿½Ã‘ï¿½ Ã�ÂºÃ�Â°Ã�Âº Ã‘ï¿½Ã�Â»Ã�Â¸Ã‘Ë†Ã�ÂºÃ�Â¾Ã�Â¼ Ã‘â€¡Ã�Â°Ã‘ï¿½Ã‘â€šÃ�Â¾Ã�Âµ Ã�Â¿Ã�ÂµÃ‘â‚¬Ã�ÂµÃ�ÂºÃ�Â»Ã‘Å½Ã‘â€¡Ã�ÂµÃ�Â½Ã�Â¸Ã�Âµ Ã�Â²Ã‘â€¦Ã�Â¾Ã�Â´Ã�Â½Ã�Â¾Ã�Â³Ã�Â¾ Ã‘ï¿½Ã�Â¸Ã�Â³Ã�Â½Ã�Â°Ã�Â»Ã�Â°.
	_Bool	err_FE=0;	 //<<1 Ã�Å¾Ã‘Ë†Ã�Â¸Ã�Â±Ã�ÂºÃ�Â° Ã�Â¿Ã‘â‚¬Ã�Â¸Ã�ÂµÃ�Â¼Ã�Â° Ã‘â€žÃ‘â‚¬Ã�ÂµÃ�Â¹Ã�Â¼Ã�Â° (Ã�ÂºÃ�Â°Ã�Â´Ã‘â‚¬Ã�Â°). Ã�â€™Ã�Â¾Ã�Â·Ã�Â½Ã�Â¸Ã�ÂºÃ�Â°Ã�ÂµÃ‘â€š, Ã�ÂºÃ�Â¾Ã�Â³Ã�Â´Ã�Â° Ã�Â½Ã�Âµ Ã�Â±Ã‘â€¹Ã�Â» Ã�Â²Ã‘â€¹Ã�Â´Ã�ÂµÃ�Â»Ã�ÂµÃ�Â½ Ã‘ï¿½Ã‘â€šÃ�Â¾Ã�Â¿-Ã�Â±Ã�Â¸Ã‘â€š. Ã�Â¢.Ã�Âµ. Ã�Â¿Ã�Â¾Ã‘ï¿½Ã�Â»Ã�Âµ Ã�Â¿Ã‘â‚¬Ã�Â¸Ã�ÂµÃ�Â¼Ã�Â° Ã‘ï¿½Ã‘â€šÃ�Â°Ã‘â‚¬Ã‘â€šÃ�Â¾Ã�Â²Ã�Â¾Ã�Â³Ã�Â¾ Ã�Â±Ã�Â¸Ã‘â€šÃ�Â° Ã�Â¸  8 Ã�Â±Ã�Â¸Ã‘â€šÃ�Â¾Ã�Â² Ã�Â´Ã�Â°Ã�Â½Ã�Â½Ã‘â€¹Ã‘â€¦ Ã�Â½Ã�Â° Ã�Â¼Ã�ÂµÃ‘ï¿½Ã‘â€šÃ�Âµ Ã‘ï¿½Ã‘â€šÃ�Â¾Ã�Â¿Ã�Â¾Ã�Â²Ã�Â¾Ã�Â³Ã�Â¾ Ã�Â±Ã�Â¸Ã‘â€šÃ�Â° UART Ã‘ï¿½Ã‘â€¡Ã�Â¸Ã‘â€šÃ�Â°Ã�Â» Ã‘ï¿½Ã�Â¸Ã�Â³Ã�Â½Ã�Â°Ã�Â» Ã�Â½Ã�Â¸Ã�Â·Ã�ÂºÃ�Â¾Ã�Â³Ã�Â¾ Ã‘Æ’Ã‘â‚¬Ã�Â¾Ã�Â²Ã�Â½Ã‘ï¿½.
	_Bool	err_PE=0;    //<<0 error parity.
	uint16_t error;
/////////////////////////////////////////
	uint8_t	status=0;
/////////////////////////////////////////

	  status=USART2->SR;
	  while((status)!=0x20)  //??
	  {
		  if((err_PE  & (status<<0))==1){printf("ERROR_PE\n") ;error++;}
		  if((err_FE  & (status<<1))==1){printf("ERROR_FE\n") ;error++;}
		  if((err_NE  & (status<<2))==1){printf("ERROR_NE\n") ;error++;}
		  if((err_ORE & (status<<3))==1){printf("ERROR_ORE\n");error++;}
	  }

  for(uint8_t k=0; k<byte; k++)  //1
	{
	  data->command = USART2->DR;
	  data->data = USART2->DR;
	  data->CRC_ = USART2->DR;
	}
	if(error>255){Alarm(GPIOA);}

	printf("UART_read\n");

}

// function to calculate CRC-16 
uint16_t RS_CRC(void * data, uint32_t len)
{ 
uint8_t * dataPtr = (uint8_t *)data;
uint32_t index = 0;
// Update the CRC for transmitted and received data using 
// the CCITT 16bit algorithm (X^16 + X^12 + X^5 + 1). 
uint16_t crc = 0;
while(len--) 
{ 
crc = (unsigned char)(crc >> 8) | (crc << 8); 
crc ^= dataPtr[index++]; 
crc ^= (unsigned char)(crc & 0xff) >> 4; 
crc ^= (crc << 8) << 4; 
crc ^= ((crc & 0xff) << 4) << 1; 
} 
return crc; 
} 


#endif