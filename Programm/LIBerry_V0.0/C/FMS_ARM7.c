#include "main.h"
/////////////////////////////////////////////
#if defined FMS_ARM7    // chip
///////////////////////////////////////
#include "FMS_ARM7.h"

//------------------------------------------
FMC_SDRAM_CommandTypeDef command;
HAL_StatusTypeDef hal_stat;
//------------------------------------------
void FMC_init(SDRAM_HandleTypeDef *hsdram)
{
	__IO uint32_t tmpmrd=0;
	/* Step 1:  Configure a clock configuration enable command */
	command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;

	 /* Send the command */
	hal_stat = HAL_SDRAM_SendCommand(hsdram,&command,SDRAM_TIMEOUT);  //SDRAM_TIMEOUT=0xFFFF
	if(hal_stat!=0) Alarm(GPIOB);  // зажечь красный}


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
	HAL_Delay(1);

	/* Step 4 : Configure a Auto-Refresh command */
	command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
	command.AutoRefreshNumber = 8;
	command.ModeRegisterDefinition = 0;

	 /* Send the command */
	hal_stat = HAL_SDRAM_SendCommand(hsdram,&command,SDRAM_TIMEOUT);
	if(hal_stat!=0) Alarm(GPIOB);  // зажечь красный}

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
	if(hal_stat!=0) Alarm(GPIOB);  // зажечь красный}

	/* Step 8: Set the refresh rate counter */
   /* (15.62 us x Freq) — 20 */
  /* Set the device refresh counter */
    hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));

}


void FMC_write(uint16_t data_w)
{

    #define  BUFFER_SIZE ((uint32_t)0x0100)
	#define  WRITE_READ_ADDR ((uint32_t)0x0800)
	#define SDRAM_BANK_ADDR  ((uint32_t)0xC0000000)  // 0xC0000000

//	uint8_t error=0;

	//	uint32_t aTxBuffer[BUFFER_SIZE];
	//	uint32_t aRxBuffer[BUFFER_SIZE]={0};


	uint32_t byte = 10;

///////////////////////////////////////////////////////////////// Повторно 5555
			  //запишем данные из буфера в память SDRAM с адреса 0xC0000800
			for (uint32_t uwIndex=0;uwIndex<byte;uwIndex++)   //BUFFER_SIZE
			{
				 *(__IO uint16_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR+4*uwIndex)  = data_w ; //0xAAAAAAAA //aTxBuffer[uwIndex]  //4*
				// FMC_Bank1->BTCR[1] = 0x00F40114;
			}
}

uint8_t FMC_read(uint16_t data_w)
{

#define  BUFFER_SIZE ((uint32_t)0x0100)
#define  WRITE_READ_ADDR ((uint32_t)0x0800)
#define SDRAM_BANK_ADDR  ((uint32_t)0xC0000000)  // 0xC0000000

uint8_t test;
uint8_t Error=0;
//test.OK=0;

uint8_t error=0;
uint8_t OK=0;
uint32_t byte=10;

uint32_t aTxBuffer[BUFFER_SIZE];
uint32_t aRxBuffer[BUFFER_SIZE];


//прочитаем в другой буфер данные из памяти SDRAM с адреса 0xC0000800
for (uint32_t uwIndex=0; uwIndex<byte;uwIndex++)
{
	aRxBuffer[uwIndex] = *(__IO uint16_t*) (SDRAM_BANK_ADDR+WRITE_READ_ADDR+4*uwIndex); //4*

		if(aRxBuffer[uwIndex]!= data_w)
	{
		Error=Error+1;
//					printf("Error %u:=%u:%u\n",test.Error,uwIndex,(aRxBuffer[uwIndex]));  //
	}

//		if(aRxBuffer[uwIndex]== data_w)
//	{
//		test.OK=test.OK+1;
////					printf("D %u:=%u:%u\n",test.OK,uwIndex,(aRxBuffer[uwIndex]));  //
//	}

		HAL_Delay(1000);
		return (Error);

}
}


//  	 IS42S16100H_7TL_init(&hsdram1);
//  	 HAL_Delay(1000);
//     HAL_Delay(1000);
//	 uint16_t error_1 = IS42S16100H_write_read(data[0]);
//	 uint16_t error_2 = IS42S16100H_write_read(data[1]);
//	 uint16_t error_3 = IS42S16100H_write_read(data[2]);
//
//	 printf("Error_ALL:=%u:%u:%u\n",error_1,error_2,error_3);  //
//	Fill_Buffer(aTxBuffer,BUFFER_SIZE,0x37BA0F68);   //0x37BA0F68
//HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
//	  if(error_1!=0 | error_2!=0 | error_3!=0)
//	  {
//		fail_signal(GPIOB,14);  // зажечь красный
//	  }
//
//
// if(error_1==0 && error_2==0 && error_3==0)
// {
//	 fail_signal(GPIOB,0);  // зажечь красный
// }
//	  if(error_1!=0 | error_2!=0 | error_3!=0)
//	  {
//		fail_signal(GPIOB,14);  // зажечь красный
//	  }
//
//
// if(error_1==0 && error_2==0 && error_3==0)
// {
//	 fail_signal(GPIOB,0);  // зажечь красный
// }



#endif //FMS_ARM7
