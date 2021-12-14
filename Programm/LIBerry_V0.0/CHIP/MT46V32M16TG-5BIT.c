#include "main.h"

#if defined MT46V32M16TG_5BIT   // chip

#include "MT46V32M16TG-5BIT.h"
//------------------------------------------
FMC_SDRAM_CommandTypeDef command;
HAL_StatusTypeDef hal_stat;
//------------------------------------------
void IS42S16100H_7TL_init(SDRAM_HandleTypeDef *hsdram)
{
	__IO uint32_t tmpmrd=0;
	/* Step 1:  Configure a clock configuration enable command */
	command.CommandMode =   FMC_SDRAM_CMD_CLK_ENABLE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;

	 /* Send the command */
	hal_stat = HAL_SDRAM_SendCommand(hsdram,&command,SDRAM_TIMEOUT);  //SDRAM_TIMEOUT=0xFFFF
    if(hal_stat!=0) {PIN_HIGH(GPIOB,7);}

	/* Step 2: Insert 100 us minimum delay */
	/* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
	HAL_Delay(1);

	/* Step 3: Configure a PALL (precharge all) command */
	command.CommandMode = FMC_SDRAM_CMD_PALL;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;

	 /* Send the command */
	hal_stat = HAL_SDRAM_SendCommand(hsdram,&command,SDRAM_TIMEOUT);
if(hal_stat!=0) {PIN_HIGH(GPIOB,7);}




	/* Step 4 : Configure a Auto-Refresh command */
	command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	command.AutoRefreshNumber = 8;
	command.ModeRegisterDefinition = 0;

	 /* Send the command */
	hal_stat = HAL_SDRAM_SendCommand(hsdram,&command,SDRAM_TIMEOUT);
if(hal_stat!=0) {PIN_HIGH(GPIOB,7);}

	/* Step 5: Program the external memory mode register */
	tmpmrd = (uint32_t) SDRAM_MODEREG_BURST_LENGTH_1 |
					            SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
											SDRAM_MODEREG_CAS_LATENCY_2 |
											SDRAM_MODEREG_OPERATING_MODE_STANDARD |
											SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
	command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = tmpmrd;

	/* Send the command */
	hal_stat = HAL_SDRAM_SendCommand(hsdram,&command,SDRAM_TIMEOUT);
if(hal_stat!=0) {PIN_HIGH(GPIOB,7);}
   /* Step 8: Set the refresh rate counter */
   /* (15.62 us x Freq) — 20 */
  /* Set the device refresh counter */
    hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));

}
//////////////////////////////////////////////////////////////////////
Data_read IS42S16100H_read(uint16_t data_w,uint32_t byte)
{

#define  BUFFER_SIZE ((uint32_t)0x0100)
#define  WRITE_READ_ADDR ((uint32_t)0x0800)
#define SDRAM_BANK_ADDR  ((uint32_t)0xC0000000)  // 0xC0000000

Data_read test;
test.Error=0;
test.OK=0;

uint8_t error=0;
uint8_t OK=0;

uint32_t aTxBuffer[BUFFER_SIZE];
uint32_t aRxBuffer[BUFFER_SIZE];


//прочитаем в другой буфер данные из памяти SDRAM с адреса 0xC0000800
for (uint32_t uwIndex=0; uwIndex<byte;uwIndex++)
{
	aRxBuffer[uwIndex] = *(__IO uint16_t*) (SDRAM_BANK_ADDR+WRITE_READ_ADDR+4*uwIndex); //4*

		if(aRxBuffer[uwIndex]!= data_w)
	{
		test.Error=test.Error+1;
//					printf("Error %u:=%u:%u\n",test.Error,uwIndex,(aRxBuffer[uwIndex]));  //
	}

		if(aRxBuffer[uwIndex]== data_w)
	{
		test.OK=test.OK+1;
//					printf("D %u:=%u:%u\n",test.OK,uwIndex,(aRxBuffer[uwIndex]));  //
	}

		HAL_Delay(1000);
		return (test);

}
}
//printf("Error_2:=%u\n",error);


/*
//отправим байты в USART
for (uwIndex=0;uwIndex<byte;uwIndex++)
{
  // sprintf(str1,"%03ld: 0x%08lX\r\n",(unsigned long) uwIndex,(unsigned long) aRxBuffer[uwIndex]);
 //  printf("READ2:=%u:%u\n",uwIndex,aRxBuffer[uwIndex]);
 //	 printf("Index_2:=%u:%u\n",uwIndex,str1);

   //HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);

}
*/

////////////////////////////////////////////////////////////////////////



Data_read IS42S16100H_write(uint16_t data_w,uint32_t byte)
{


    #define  BUFFER_SIZE ((uint32_t)0x0100)
	#define  WRITE_READ_ADDR ((uint32_t)0x0800)
	#define SDRAM_BANK_ADDR  ((uint32_t)0xC0000000)  // 0xC0000000

	Data_read test;
	test.Error=0;
	test.OK=0;

	uint8_t error=0;
	uint8_t OK=0;

    uint32_t aTxBuffer[BUFFER_SIZE];
	uint32_t aRxBuffer[BUFFER_SIZE];


 //  byte = 2097152; //4

///////////////////////////////////////////////////////////////// Повторно 5555
			  //запишем данные из буфера в память SDRAM с адреса 0xC0000800
			for (uint32_t uwIndex=0;uwIndex<byte;uwIndex++)   //BUFFER_SIZE
			{
				 *(__IO uint16_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR+4*uwIndex)  = data_w ; //0xAAAAAAAA //aTxBuffer[uwIndex]  //4*
				// FMC_Bank1->BTCR[1] = 0x00F40114;
			}





}

static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset) //Заполнение буфера
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}




/*
   IS42S16100H_7TL_init(&hsdram1);

   #define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)
   uint32_t timeout = SDRAM_TIMEOUT;

  //BSP_SDRAM_Init();
   while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY) && (timeout > 0))
   {
     timeout--;
   }
//

 b = HAL_SDRAM_GetState(&hsdram1);
 uint16_t wBuffer[255]={0};
 uint16_t rBuffer[255]={0};


  if (b==0){printf("SDRAM not yet initialized or disabled\n");}
  if (b==1){printf("SDRAM initialized and ready for use\n");}
  if (b==2){printf("SDRAM internal process is ongoing\n");}
  if (b==3){printf("SDRAM error state\n");}
  if (b==4){printf("SDRAM device write protected\n");}
  if (b==5){printf("SDRAM device precharged\n");}
  else if(b==125)
  {
     printf("Error\n");  //
     PIN_HIGH(GPIOB,0); //read
  }


 ///////////////////////////////////////////////////READ WRITE ONE

for(uint16_t i=0;i<10;i++)
{
	wBuffer[i]=0xAAAA;
}

  for(uint16_t i=0;i<255;i++)
   {
	  G = HAL_SDRAM_Write_16b(&hsdram1,0xC0000000,&wBuffer,i);
	  if(G!=0){fail_signal(GPIOB,7);}  // зажечь красный}
   }


  for(uint16_t i=0;i<255;i++)
  {
     G = HAL_SDRAM_Read_16b(&hsdram1,0xC0000000,&rBuffer,i);
     if(G!=0){fail_signal(GPIOB,14);}  // зажечь красный}

  }






 	 error_1 = IS42S16100H_write_read(data[0],byte);
  	 printf("Error1_:=%u OK:=%u\n",error_1.Error,error_1.OK);  //

     error_2 = IS42S16100H_write_read(data[1],byte);
 	 printf("Error2_:=%u OK:=%u\n",error_2.Error,error_2.OK);  //

 	 error_3 = IS42S16100H_write_read(data[2],byte);
 	 printf("Error3_:=%u OK:=%u\n",error_3.Error,error_3.OK);  //

*/

/*

  if ((HAL_SDRAM_Init(&hsdram1,&Timing)) != HAL_OK)
  {
	  printf("Error1\n");  //
	  PIN_HIGH(GPIOB,14); //Error Read
  }
  else
  {
     printf("INIT_OK\n");  //
     PIN_HIGH(GPIOB,0); //read
  }
//  HAL_SetFMCMemorySwappingConfig(FMC_SWAPBMAP_SDRAM_SRAM);
//	Fill_Buffer(aTxBuffer,BUFFER_SIZE,0x37BA0F68);   //0x37BA0F68

*/


//wHILW

/*

  if( (error_1.Error!=0) | (error_2.Error!=0) | (error_3.Error!=0) )  //| error_2!=0 | error_3!=0  | (error_2.Error!=0) | (error_3.Error!=0)
  {
	fail_signal(GPIOB,14);  // red
  }


if( (error_1.Error==0) | (error_2.Error==0) |(error_3.Error==0) ) //&& error_2==0 && error_3==0   |(error_2.Error==0) |(error_3.Error==0
{
	 fail_signal(GPIOB,0);  // green
}
HAL_Delay(1000);

*/
#endif  //






