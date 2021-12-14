//  ******************************************************************************
//  * @file           : main.c
//  * @brief          : Main program body
//  ******************************************************************************
//  * @attention
//  *
//  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
//  * All rights reserved.</center></h2>
//  *
//  * This software component is licensed by ST under BSD 3-Clause license,
//  * the "License"; You may not use this file except in compliance with the
//  * License. You may obtain a copy of the License at:
//  *                        opensource.org/licenses/BSD-3-Clause
//  *
//  ******************************************************************************
#include "main.h"
#include "ARM3_PLUS.h"


uint8_t str2[]="USART!!!!\r\n";
char str0[]="Mode_Test";
uint16_t dT=0;

UART_HandleTypeDef huart2;
ADC_HandleTypeDef  hadc1;

stm103::Tools      tools;
stm103::ARM3       arm;
stm103::_I2C       i2c;
stm103::UARt       uart2;
stm103::_LCD1602   lsd;

//S1 f1() { S1 s; return s; }

typedef struct
{
	GPIO CS;
	GPIO nOE;
	GPIO CLK;
	GPIO nRes;
	GPIO REG;
}tesmatik;
///////////////////////////////////////set port init
PIN_I2C pin_I2C=
{
  .I2C_N1={GPIOB,6},  //10/6
  .I2C_N2={GPIOB,7},  //11/7
  .I2C_typ=I2C1,      //I2C2/I2C1
};

void SystemClock_Config(void);
static void MX_ADC1_Init(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	 MX_ADC1_Init();
	_delay_ms(10);
///////////////////////////////////////////////////////////////////////Port Init
    tools.GPIO_Init();  				   //     GPIO_Init();
///////////////////////////////////////////////////////////////////////I2C Init
    if(i2c.Init(&pin_I2C.hi2c,pin_I2C)!= HAL_OK){printf("I2C=Error \n");}  // I2C2  //	PIN_I2C port_I2C={.I2C_N1={GPIOB,6},.I2C_N2={GPIOB,7}};
///////////////////////////////////////////////////////////////////////ID I2C read id
    uint8_t ID[2]={0};
    i2c.I2C_IDReady(pin_I2C,ID);
//////////////////////////////////////////////////////////LCD
    lsd.lcd_ON(&pin_I2C.hi2c,str0,1,ID[1]);         // ID[1]=0x4e   //ID[0]  LCD_TYPE lcd_type={20,4};
///////////////////////////////////////////////////////////////////////
//    uart2.MX_USART2_UART_Init(&huart2);
/*
//protocol_mas masdata={.data={0x1,10,15,25}};
protocol d_prot =
{
		.WR=0,
		.status=0,
		.comand=0,
		.r_3=16,
		.r_4=17,
		.r_5=10,
		.CRC_Cmd=0x12,
		.byte=8,
		.CRC_data=0x15,
		.mas_data={0x1,0x10,0x15,0x25}
};
//////////////////////////////////////////////////////Tesmatik
//tesmatik testd={.CS={GPIOC,8},.nOE={GPIOA,12},.CLK={GPIOA,10},.nRes={GPIOA,8},.REG={GPIOC,6}};
*/
 /////////////////////////////////////////////////////ADC


//////////////////////////////////////////

//  for(uint32_t i=0;i<Address_number;i++){PINS_OUT( p.Address[i]);}        // 16
//  for(uint32_t i=0;i<Data_number;i++){PINS_OUT( p.DDQSA[i]);}             // 16
//arm.OUTS(IDT::Triangle::);
//arm.PINS_OUT(testd.CLK);
//arm.PINS_OUT(testd.nRes);
//arm.PINS_OUT(testd.REG);
//
//arm.PINS_LOW(testd.nRes);
//arm:PINS_HIGH(testd.nRes);
//
//arm.PINS_LOW(testd.nOE);
//uint8_t data1=0xD5;
//uint8_t dat=data1;



/*
for(uint8_t i=0;i<9;i++)
	  {
	      arm.PINS_LOW(testd.CS);
		  arm.PINS_LOW(testd.CLK);
		  HAL_Delay(1);

		  (dat  & 1 )  ? arm.PINS_HIGH(testd.REG) : arm.PINS_LOW(testd.REG);
		   dat >>= 1;  // >>
		  HAL_Delay(1);

//	  tools.send_1wire(0xFF,8,testd.REG);
//	  arm.PINS_HIGH(testd.REG);

		  arm.PINS_HIGH(testd.CLK);
		  arm.PINS_HIGH(testd.CS);
		  HAL_Delay(1);
	  }
*/



  while (1)
  {

	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1,100);
	  dT=(uint32_t)HAL_ADC_GetValue(&hadc1);
	  printf("ADC:=%u \n",dT);

	 // uart2.UART_Write(received_writt);

 //     uart2.UART_protocol_controller(d_prot,0);
	  tools.fail_signal(GPIOC,6);
	  tools.fail_signal(GPIOC,7);
  }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}



static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}



void Error_Handler(void)
{}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
