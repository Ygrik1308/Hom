/*
 * ARM3_PLUS.h
 *
 *  Created on: 1 нояб. 2020 г.
 *      Author: HP
 */
#include "main.h"


//////////////////////////////////
#ifdef arm3_CPP
//////////////////////////////////
#ifndef ARM_ARM3_ARM3_PLUS_H_
#define ARM_ARM3_ARM3_PLUS_H_
/////////////////////////////////////////////////////////////////////////////////////////
namespace stm103
{
/////////////////////////////////////////////////////////////////////////////////////////////////////
class ARM3
{
public:
	typedef enum
	{
		pA = 0x1,    //103VE
		pB = 0x2,    //103VE
		pC = 0x4,    //103VE
		pD=  0x8,    //103VE
		pE = 0x10,   //103VE
		pG = 0x20    //103ZET
	}RCC_senD;

	typedef enum
	{
		rcca = 0x1UL << (2U),    //103VE
		rccb = 0x1UL << (3U),    //103VE
		rccc = 0x1UL << (4U),    //103VE
		rccd = 0x1UL << (5U),    //103VE
		rcce = 0x1UL << (6U),    //103VE
		rccg = 0x1UL << (8U)     //103ZET
	}_rcc;

////////////////////////////////////////////////////////PIN_HIGH
	void HIGH(GPIO_TypeDef *GPIOx,uint16_t Pin)   //  PIn-> 1 (GPIOD, GPIO_Pin_0)
	{
		GPIOx->BSRR = (uint16_t)(1<<Pin);  //1
	}
////////////////////////////////////////////////////////PIN_LOW
	void LOW(GPIO_TypeDef *GPIOx,uint16_t Pin)   //
	{
		GPIOx->BSRR = (uint32_t)(1<<Pin)<< 16U; //0
	}
////////////////////////////////////////////////////////PIN_OUT
	void OUT(GPIO_TypeDef *GPIOx,uint16_t pin)
	{
	//	pin_configuration(GPIOx, pin, 0x03 );

		if(pin<=7)
		{
			GPIOx->CRL &= ~(0x0f<<(pin*4));  	//2
			GPIOx->CRL |= 0x03<<(pin*4); //mask  //2
		}
		if(pin>7)
		{
			GPIOx->CRH &= ~(0x0f<<( pin-8)*4);  // 8
			GPIOx->CRH |=   0x03<<((pin-8)*4);      //mask
		}
	}
////////////////////////////////////////////////////////PIN_IN
	void IN(GPIO_TypeDef *GPIOx,uint16_t pin)
	{
		//pin_configuration(GPIOx, pin, 0x04 );
		if(pin<=7)
		{
			GPIOx->CRL &= ~(0x0f<<(pin*4));
			GPIOx->CRL |= 0x04<<(pin*4); //mask
		}
		if(pin>7)
		{
			GPIOx->CRH &= ~(0x0f<<(pin*4));
			GPIOx->CRH |= 0x04<<(pin*4); //mask
		}

	}
/////////////////////////////////////////////////////PIN_READ
	bool READ(GPIO_TypeDef *GPIOx,uint16_t Pin)  // считать с портов  2 байт
	{
		uint16_t dat = GPIOx->IDR & (uint16_t)(1<<Pin);
		return dat;
	}

	////////////////////////////////////////////////////////////////PORT_HIGH
		void PORT_HIGH(GPIO_TypeDef *GPIOx)
		{
			GPIOx->BSRR = 0xFFFF;   //записать 0xFFFF 1
		}
	////////////////////////////////////////////////////////////////PORT_LOW
		void PORT_LOW(GPIO_TypeDef *GPIOx)
		{
			GPIOx->BRR = 0x0000;   //записать 0xFFFF 0
		}
	////////////////////////////////////////////////////////////////PORT_IN
		void PORT_IN(GPIO_TypeDef *GPIOx)
		{
			GPIOx->CRL  = 0x44444444;
		}
	////////////////////////////////////////////////////////////////PORT_OUT
		void PORT_OUT(GPIO_TypeDef *GPIOx)
		{
			GPIOx->CRL  = 0x33333333;
		}
	////////////////////////////////////////////////////////////////PORT_DATA
		void PORT_DATA(GPIO_TypeDef *GPIOx,uint16_t data)
		{
			GPIOx->ODR = data ;   //записать 0xFFFF 1
		}
//////////////////////////////////////////////////////////////////Structur
		void OUTS(GPIO p)
		{
		//	pin_configuration(GPIOx, pin, 0x03 );

			if(p.PIN<=7)
			{
				p.GPIO->CRL &= ~(0x0f<<(p.PIN*4));  	//2
				p.GPIO->CRL |=   0x03<<(p.PIN*4); //mask  //2
			}
			if(p.PIN>7)
			{

				p.GPIO->CRH &= ~(0x0f<<((p.PIN-8)*4));  	//2
				p.GPIO->CRH |=   0x03<<((p.PIN-8)*4);

		//		p.GPIO->CRH &= ~(0x1<<(p.PIN*2)<<8U);
		//		p.GPIO->CRH |= 0x02<<((p.PIN*2)<<8U); //mask
				  HAL_Delay(100);
			}
		}

		void INS(GPIO p)
		{
			//pin_configuration(GPIOx, pin, 0x04 );
			if(p.PIN<=7)
			{
				p.GPIO->CRL &= ~(0x0f<<(p.PIN*4));
				p.GPIO->CRL |= 0x04<<(p.PIN*4); //mask
			}
			if(p.PIN>7)
			{
				p.GPIO->CRH &= ~(0x0f<<(p.PIN*4));
				p.GPIO->CRH |= 0x04<<(p.PIN*4); //mask
			}

		}

		void HIGHS(GPIO p)   //  PIn-> 1 (GPIOD, GPIO_Pin_0)
		{
			p.GPIO->BSRR = (uint16_t)(1<<p.PIN);  //1
		}

		void LOWS(GPIO p)   //
		{
			p.GPIO->BSRR = (uint32_t)(1<<p.PIN)<< 16U; //0
		}
};  //ARM3_PIN
/////////////////////////////////////////////////////////////////////////////////////////////////////
class Tools : public ARM3
{
	//ARM3_PIN PIN;

public:
	int   number;
//////////////////////////////////////////////////////////////delay_nop
	void delay_nop(int Delay)
	{
		for( uint8_t i=0; i<Delay; ++i) asm ( "nop" );
	}
/////////////////////////////////////////////////////////////Alarm
	void Alarm(GPIO_TypeDef *GPIOx)
	{
		OUT(GPIOx,6);
		OUT(GPIOx,7);


		  while (1)
		  {
			  LOW(GPIOx,6);
			  LOW(GPIOx,7);
			  HAL_Delay(100);

			  HIGH(GPIOx,6);
			  HIGH(GPIOx,7);
			  HAL_Delay(100);
		  }
	}
/////////////////////////////////////////////////////////////////fail_signal
	void fail_signal(GPIO_TypeDef *GPIOx,uint16_t LED)
	{
		OUT(GPIOx,LED);

			HIGH(GPIOx,LED);
		//       GPIOx->BSRR = (1 << LED);  //i2//   горит
		       HAL_Delay(400);

		   LOW(GPIOx,LED);
	      //    GPIOx->BRR = (1 << LED);  //i2//  не горит
	           HAL_Delay(400);
	}
///////////////////////////////////////////////////////////////// CLOK
	void clocking(uint8_t Rcc)
	{
		if(Rcc&(1<<0)){RCC->APB2ENR |= rcca;} //RCC_APB2ENR_IOPAEN; 103
		if(Rcc&(1<<1)){RCC->APB2ENR |= rccb;} //RCC_APB2ENR_IOPBEN; 103
		if(Rcc&(1<<2)){RCC->APB2ENR |= rccc;} //RCC_APB2ENR_IOPCEN; 103
		if(Rcc&(1<<3)){RCC->APB2ENR |= rccd;} //RCC_APB2ENR_IOPDEN;	103
		if(Rcc&(1<<4)){RCC->APB2ENR |= rcce;} //RCC_APB2ENR_IOPEEN; 103
		if(Rcc&(1<<5)){RCC->APB2ENR |= rccg;} //RCC_APB2ENR_IOPEEN; 103
	}

///////////////////////////////////////////////////////////////// GPIO INIT
	uint16_t GPIO_Init()   /// Test All System
	{
		uint16_t Error_All = 0;
		clocking(pA+pB+pC+pD+pE+pG);
		OUT(GPIOC,6);
		OUT(GPIOC,7);

	    return Error_All;
	}
///////////////////////////////////////////////////////////////////////Structur
	void send_1wire(uint8_t data, uint8_t byte,GPIO p)
	{
	    for( uint8_t i = 0; i < byte; ++i)
	    {
	    	data >>= 1;  // >>
	        (data  & 1 )  ? HIGHS(p) : LOWS(p);
	        HAL_Delay(1);
	    }
	}
};  //ARM3_Tools
////////////////////////////////class I2C////////////////////////////////////////////////////////////
class _I2C : public Tools
{
/////////////////////////////////////////////////////////////////////////////////////////////// WIRE
		#define I2C_TIMEOUT_BUSY_FLAG     25U         /*!< Timeout 25 ms             */
		#define I2C_FLAG_BUSY             0x00100002U
		#define I2C_NO_OPTION_FRAME       0xFFFF0000U /*!< XferOptions default value */
		#define I2C_STATE_MSK             ((uint32_t)((uint32_t)((uint32_t)HAL_I2C_STATE_BUSY_TX | (uint32_t)HAL_I2C_STATE_BUSY_RX) & (uint32_t)(~((uint32_t)HAL_I2C_STATE_READY)))) /*!< Mask State define, keep only RX and TX bits            */
		#define I2C_STATE_MASTER_BUSY_RX  ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))            /*!< Master Busy RX, combinaison of State LSB and Mode enum */

 public:
//-1-//init test I2C
	   StatusTypeDef Init(I2C_HandleTypeDef *hi2c,PIN_I2C  port)
	 {
		  hi2c->Instance = port.I2C_typ;   //I2C2								    ////  I2C1  - PB6,PB7 |I2C2 -
		  hi2c->Init.ClockSpeed = 100000; 		 				    ////  I2C_ClockSpeed (Hz)
		  hi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;  				    ////  I2C_ DutyCycle 2 and 16/9
		  hi2c->Init.OwnAddress1 = 0;								////  primary slave address  // основной ведомый адрес
		  hi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;      ////  I2C_ADDRESSINGMODE_7BIT | I2C_ADDRESSINGMODE_10BIT
		  hi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		  hi2c->Init.OwnAddress2 = 0;
		  hi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		  hi2c->Init.NoStretchMode =   I2C_NOSTRETCH_DISABLE;

	  uint32_t freqrange;
	  uint32_t pclk1;

	  if (hi2c == NULL){return HAL_ERROR;}  // Check the I2C handle allocation //

	  /* Check the parameters */
	  	  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
	  	  assert_param(IS_I2C_CLOCK_SPEED(hi2c->Init.ClockSpeed));
	  	  assert_param(IS_I2C_DUTY_CYCLE(hi2c->Init.DutyCycle));
	  	  assert_param(IS_I2C_OWN_ADDRESS1(hi2c->Init.OwnAddress1));
	  	  assert_param(IS_I2C_ADDRESSING_MODE(hi2c->Init.AddressingMode));
	  	  assert_param(IS_I2C_DUAL_ADDRESS(hi2c->Init.DualAddressMode));
	  	  assert_param(IS_I2C_OWN_ADDRESS2(hi2c->Init.OwnAddress2));
	  	  assert_param(IS_I2C_GENERAL_CALL(hi2c->Init.GeneralCallMode));
	  	  assert_param(IS_I2C_NO_STRETCH(hi2c->Init.NoStretchMode));

	  //	hi2c->State= HAL_I2C_STATE_BUSY; // = 1
	  //    I2C2->CR1

	  if (hi2c->State == HAL_I2C_STATE_RESET)
	  {
	    hi2c->Lock = HAL_UNLOCKED;  	    // Allocate lock resource and initialize it //
	    I2C_MspInit(hi2c,port);
	  }

	  hi2c->State = HAL_I2C_STATE_BUSY;     // An internal process is ongoing
	  hi2c->Instance->CR1 &= ~(1 << 0);	    //, I2C_CR1_PE)  //	  0x1UL << I2C_CR1_PE_Pos
	  //__HAL_I2C_DISABLE(hi2c1); 			// Disable the selected I2C peripheral //

	  //Reset I2C//
	  hi2c->Instance->CR1 |=  I2C_CR1_SWRST;
	  hi2c->Instance->CR1 &= ~I2C_CR1_SWRST;

	  // Get PCLK1 frequency //
	  pclk1 = HAL_RCC_GetPCLK1Freq();

	  // Check the minimum allowed PCLK1 frequency //
	  if (I2C_MIN_PCLK_FREQ(pclk1, hi2c->Init.ClockSpeed) == 1U){return HAL_ERROR;}

	  // Calculate frequency range //
	  freqrange = I2C_FREQRANGE(pclk1);
	  //--------------------------- I2Cx CR2 Configuration ----------------------//
	  	  MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_FREQ, freqrange);  // Configure I2Cx: Frequency range // Частотный диапазон
	  //---------------------------- I2Cx TRISE Configuration --------------------//
	  	  MODIFY_REG(hi2c->Instance->TRISE, I2C_TRISE_TRISE, I2C_RISE_TIME(freqrange, hi2c->Init.ClockSpeed)); // Configure I2Cx: Rise Time //  Время нарастания
	  //---------------------------- I2Cx CCR Configuration ----------------------//
	      MODIFY_REG(hi2c->Instance->CCR, (I2C_CCR_FS | I2C_CCR_DUTY | I2C_CCR_CCR), I2C_SPEED(pclk1, hi2c->Init.ClockSpeed, hi2c->Init.DutyCycle)); 	  // Configure I2Cx: Speed // Скорость
	  //---------------------------- I2Cx CR1 Configuration ----------------------//
     	  MODIFY_REG(hi2c->Instance->CR1, (I2C_CR1_ENGC | I2C_CR1_NOSTRETCH), (hi2c->Init.GeneralCallMode | hi2c->Init.NoStretchMode)); 	  // Configure I2Cx: Generalcall and NoStretch mode //
	  //---------------------------- I2Cx OAR1 Configuration ---------------------//
    	  MODIFY_REG(hi2c->Instance->OAR1, (I2C_OAR1_ADDMODE | I2C_OAR1_ADD8_9 | I2C_OAR1_ADD1_7 | I2C_OAR1_ADD0), (hi2c->Init.AddressingMode | hi2c->Init.OwnAddress1));  	  // Configure I2Cx: Own Address1 and addressing mode //
	  //---------------------------- I2Cx OAR2 Configuration ---------------------//
     	  MODIFY_REG(hi2c->Instance->OAR2, (I2C_OAR2_ENDUAL | I2C_OAR2_ADD2), (hi2c->Init.DualAddressMode | hi2c->Init.OwnAddress2));  	  // Configure I2Cx: Dual mode and Own Address2 //
	  // Enable the selected I2C peripheral //
    	  hi2c->Instance->CR1 |= (1 << 0);  	  // SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE)
//	  __HAL_I2C_ENABLE(hi2c1);

	  hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
	  hi2c->State = HAL_I2C_STATE_READY;
	  hi2c->PreviousState = I2C_STATE_NONE;   //((uint32_t)(HAL_I2C_MODE_NONE))       HAL_I2C_MODE_NONE               = 0x00U,
	  hi2c->Mode = HAL_I2C_MODE_NONE;

 //     if ((hi2c1) != HAL_OK)  {Alarm(GPIOA);}

	  return HAL_OK;
	}
//-2 -//INIT GPIO
	   void I2C_MspInit(I2C_HandleTypeDef* hi2c,PIN_I2C I2_PORT)
	{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(hi2c->Instance==(I2_PORT.I2C_typ))  //
	  {
	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    /**I2C1 GPIO Configuration
	    PB6     ------> I2C1_SCL
	    PB7     ------> I2C1_SDA
	    */
//	    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	    GPIO_InitStruct.Pin = ((uint16_t)(1<<I2_PORT.I2C_N1.PIN))|((uint16_t)(1<<I2_PORT.I2C_N2.PIN));
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  //Standart_Mode = 1000nS, Fast_Mode = 300nS, 1/42MHz = 24nS
	  //   I2C1->TRISE = 42; //(1000nS/24nS)+1
	  //  RCC->APB1ENR |=	RCC_APB1ENR_I2C2EN;
	  // SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);

		  if(hi2c->Instance==I2C1)
	     {
	          __HAL_RCC_I2C1_CLK_ENABLE();
		  }
		  if(hi2c->Instance==I2C2)
		  {
			  __HAL_RCC_I2C2_CLK_ENABLE();
		  }
	  }
    }
//-3-//
       StatusTypeDef Wire(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
	{
	  uint32_t tickstart = HAL_GetTick();   // Init tickstart for timeout management

	  if (hi2c->State == HAL_I2C_STATE_READY)
	  {

		    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)     // Wait until BUSY flag is reset
		    {
		      return HAL_BUSY;
		    }

	    /* Process Locked */
		    __HAL_LOCK(hi2c);

	    /* Check if the I2C is already enabled */
	    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
	    {
	      /* Enable I2C peripheral */
//-	      __HAL_I2C_ENABLE(hi2c);
		  hi2c->Instance->CR1 |= (1 << 0);  	  // SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE)
	    }

	    /* Disable Pos */
	    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

	    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
	    hi2c->Mode        = HAL_I2C_MODE_MASTER;
	    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

	    /* Prepare transfer parameters */
	    hi2c->pBuffPtr    = pData;
	    hi2c->XferCount   = Size;
        hi2c->XferSize    = hi2c->XferCount;
	    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

	    /* Send Slave Address */
	    if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
        {
	      return HAL_ERROR;
	    }

	    /* Clear ADDR flag */
	    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

	    while (hi2c->XferSize > 0U)
	    {
	      /* Wait until TXE flag is set */
	      if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
	      {
	        if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	        {
	          /* Generate Stop */
	          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
	        }
	        return  HAL_ERROR; //ERROR;
	      }

	      /* Write data to DR */
	      hi2c->Instance->DR = *hi2c->pBuffPtr;

	      /* Increment Buffer pointer */
          hi2c->pBuffPtr++;

	      /* Update counter */
	      hi2c->XferCount--;
	      hi2c->XferSize--;

	      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U))
	      {
	        /* Write data to DR */
	        hi2c->Instance->DR = *hi2c->pBuffPtr;

	        /* Increment Buffer pointer */
	        hi2c->pBuffPtr++;

	        /* Update counter */
	        hi2c->XferCount--;
	        hi2c->XferSize--;
	      }

	      /* Wait until BTF flag is set */
	      if (I2C_WaitOnBTFFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
	      {
	        if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
	        {
	          /* Generate Stop */
	          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
	        }
	        return HAL_ERROR;
	      }
	    }

	    /* Generate Stop */
	    SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

	    hi2c->State = HAL_I2C_STATE_READY;
	    hi2c->Mode = HAL_I2C_MODE_NONE;

       /* Process Unlocked */
	    __HAL_UNLOCK(hi2c);

      return HAL_OK;
	  }
	  else
	  {
	    return HAL_BUSY;
	  }
  }
//-4-//
       StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart)
	{
		// Wait until flag is set //
	  while (__HAL_I2C_GET_FLAG(hi2c, Flag) == Status)
	  {
	    // Check for the Timeout //
	    if (Timeout != HAL_MAX_DELAY)
	    {
	      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
	      {
	        hi2c->PreviousState     = I2C_STATE_NONE;
	        hi2c->State             = HAL_I2C_STATE_READY;
	        hi2c->Mode              = HAL_I2C_MODE_NONE;
	        hi2c->ErrorCode         |= HAL_I2C_ERROR_TIMEOUT;

         // Process Unlocked //
	        __HAL_UNLOCK(hi2c);

	        return HAL_ERROR;
	      }
	    }
	  }
	  return HAL_OK;
	}
//-5-//
	   StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart)
	 {
	   // Declaration of temporary variable to prevent undefined behavior of volatile usage //
	   uint32_t CurrentXferOptions = hi2c->XferOptions;

	   // Generate Start condition if first transfer //
	   if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
	   {
	     // Generate Start ///
	     SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
	   }
	   else if (hi2c->PreviousState == I2C_STATE_MASTER_BUSY_RX)
	   {
	     // Generate ReStart //
	     SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
	   }
	   else
	   {
	     // Do nothing //
	   }

	   // Wait until SB flag is set //
	   if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
	   {
	     if (hi2c->Instance->CR1 & I2C_CR1_START)
	     {
	       hi2c->ErrorCode = HAL_I2C_WRONG_START;
	     }
	     return HAL_TIMEOUT;
	   }

	   if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
	   {
	     // Send slave address //
	     hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);
	   }
	   else
	   {
	     // Send header of slave address //
	     hi2c->Instance->DR = I2C_10BIT_HEADER_WRITE(DevAddress);

	     // Wait until ADD10 flag is set //
	     if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10, Timeout, Tickstart) != HAL_OK)
	     {
	       return HAL_ERROR;
	     }

	     // Send slave address //
	     hi2c->Instance->DR = I2C_10BIT_ADDRESS(DevAddress);
	   }

	   // Wait until ADDR flag is set //
	   if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
	   {
	     return HAL_ERROR;
	   }

	   return HAL_OK;
	 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-6-//
      static StatusTypeDef I2C_WaitOnTXEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
      {
        while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == RESET)
        {
          // Check if a NACK is detected //
          if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
          {
            return HAL_ERROR;
          }

          // Check for the Timeout //
          if (Timeout != HAL_MAX_DELAY)
          {
            if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
            {
              hi2c->PreviousState       = I2C_STATE_NONE;
              hi2c->State               = HAL_I2C_STATE_READY;
              hi2c->Mode                = HAL_I2C_MODE_NONE;
              hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

              // Process Unlocked //
              __HAL_UNLOCK(hi2c);

              return HAL_ERROR;
            }
          }
        }
        return HAL_OK;
      }
//-7-//
       static StatusTypeDef I2C_WaitOnBTFFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
      {
        while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == RESET)
        {
          // Check if a NACK is detected //
          if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
          {
            return HAL_ERROR;
          }

          // Check for the Timeout //
          if (Timeout != HAL_MAX_DELAY)
          {
            if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
            {
              hi2c->PreviousState       = I2C_STATE_NONE;
              hi2c->State               = HAL_I2C_STATE_READY;
              hi2c->Mode                = HAL_I2C_MODE_NONE;
              hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

              // Process Unlocked //
              __HAL_UNLOCK(hi2c);

              return HAL_ERROR;
            }
          }
        }
        return HAL_OK;
      }
//-8-//
       static StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart)
      {
        while (__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET)
        {
          if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
          {
            // Generate Stop //
            SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

            // Clear AF Flag //
            __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

            hi2c->PreviousState       = I2C_STATE_NONE;
            hi2c->State               = HAL_I2C_STATE_READY;
            hi2c->Mode                = HAL_I2C_MODE_NONE;
            hi2c->ErrorCode           |= HAL_I2C_ERROR_AF;

            // Process Unlocked //
            __HAL_UNLOCK(hi2c);

            return HAL_ERROR;
          }

          // Check for the Timeout //
          if (Timeout != HAL_MAX_DELAY)
          {
            if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
            {
              hi2c->PreviousState       = I2C_STATE_NONE;
              hi2c->State               = HAL_I2C_STATE_READY;
              hi2c->Mode                = HAL_I2C_MODE_NONE;
              hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

              // Process Unlocked //
              __HAL_UNLOCK(hi2c);

              return HAL_ERROR;
            }
          }
        }
        return HAL_OK;
      }
//-9-//
       static StatusTypeDef I2C_IsAcknowledgeFailed(I2C_HandleTypeDef *hi2c)
      {
        if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
        {
          // Clear NACKF Flag //
          __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_AF;

          // Process Unlocked //
          __HAL_UNLOCK(hi2c);

          return HAL_ERROR;
        }
        return HAL_OK;
      }
//-10-//
        void  I2C_IDReady(PIN_I2C i2c, uint8_t *ID)
 {

        uint8_t b=255;
         uint8_t c=0;
         uint8_t error=0;

         //uint8_t  ID[3];

         for(uint8_t i=0;i<127;i++)
  {
       b=I2C_IsDeviceReady(&i2c.hi2c,i,1,100);
     //  b=HAL_I2C_IsDeviceReady(&pin_I2C.hi2c,i,1,100);
	  if(b==0)
	  {
		  ID[c]=i;
		  printf("ID:%x=%u \n",i,b);
		  c=c+1;
	  }
	  if(b==1)
	  {

	      error++;
	  }
  }
         printf("Error:%u Id:%u\n",error,c);
 //        return ID;
 }
//-11-//
        StatusTypeDef I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout)
 {
        /* Get tick */
        uint32_t tickstart = HAL_GetTick();
        uint32_t I2C_Trials = 1U;
        FlagStatus tmp1;
        FlagStatus tmp2;

        if (hi2c->State == HAL_I2C_STATE_READY)
        {
          /* Wait until BUSY flag is reset */
          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
          {
            return HAL_BUSY;
          }

          /* Process Locked */
       //??   __HAL_LOCK(hi2c);

          /* Check if the I2C is already enabled */
          if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
          {
            /* Enable I2C peripheral */
            __HAL_I2C_ENABLE(hi2c);
          }

          /* Disable Pos */
          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

          hi2c->State = HAL_I2C_STATE_BUSY;
          hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
          hi2c->XferOptions = I2C_NO_OPTION_FRAME;

          do
          {
            /* Generate Start */
            SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

            /* Wait until SB flag is set */
            if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, tickstart) != HAL_OK)
            {
              if (hi2c->Instance->CR1 & I2C_CR1_START)
              {
                hi2c->ErrorCode = HAL_I2C_WRONG_START;
              }
              return HAL_TIMEOUT;
            }

            /* Send slave address */
            hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);

            /* Wait until ADDR or AF flag are set */
            /* Get tick */
            tickstart = HAL_GetTick();

            tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR);
            tmp2 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF);
            while ((hi2c->State != HAL_I2C_STATE_TIMEOUT) && (tmp1 == RESET) && (tmp2 == RESET))
            {
              if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
              {
                hi2c->State = HAL_I2C_STATE_TIMEOUT;
              }
              tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR);
              tmp2 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF);
            }

            hi2c->State = HAL_I2C_STATE_READY;

            /* Check if the ADDR flag has been set */
            if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR) == SET)
            {
              /* Generate Stop */
              SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

              /* Clear ADDR Flag */
              __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

              /* Wait until BUSY flag is reset */
              if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
              {
                return HAL_ERROR;
              }

              hi2c->State = HAL_I2C_STATE_READY;

              // Process Unlocked //
       //       __HAL_UNLOCK(hi2c);

              return HAL_OK;
            }
            else
            {
              // Generate Stop //
              SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

              // Clear AF Flag //
              __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

              /* Wait until BUSY flag is reset */
              if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
              {
                return HAL_ERROR;
              }
            }
            // Increment Trials //
            I2C_Trials++;
          }
          while (I2C_Trials < Trials);

          hi2c->State = HAL_I2C_STATE_READY;

          /* Process Unlocked */
          __HAL_UNLOCK(hi2c);

          return HAL_ERROR;
        }
        else
        {
          return HAL_BUSY;
        }
  }
 };  //I2cd
/////////////////////////////////////////////////////////////////////////////////////////////////////
class UARt : public Tools //: public Tools
{
public:
//-1-//INIT set
	   void MX_USART2_UART_Init(UART_HandleTypeDef *huart2)
	{
		huart2->Instance = USART2;
		huart2->Init.BaudRate = 115200;  //115200
		huart2->Init.WordLength = UART_WORDLENGTH_8B;
		huart2->Init.StopBits = UART_STOPBITS_1;
		huart2->Init.Parity = UART_PARITY_NONE;
		huart2->Init.Mode = UART_MODE_TX_RX;
		huart2->Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart2->Init.OverSampling = UART_OVERSAMPLING_16;

	 if (UART_Init(huart2) != HAL_OK)
		{
		 Alarm(GPIOC);
		// Error_Handler();
		}
	}
//-2-//INIT
	   StatusTypeDef UART_Init(UART_HandleTypeDef *huart2)
	 {
	   /* Check the UART handle allocation */
	   if (huart2 == NULL)
	   {
	     return HAL_ERROR;
	   }

	   /* Check the parameters */
	   if (huart2->Init.HwFlowCtl != UART_HWCONTROL_NONE)
	   {
	     /* The hardware flow control is available only for USART1, USART2 and USART3 */
	     assert_param(IS_UART_HWFLOW_INSTANCE(huart->Instance));
	     assert_param(IS_UART_HARDWARE_FLOW_CONTROL(huart->Init.HwFlowCtl));
	   }
	   else
	   {
	     assert_param(IS_UART_INSTANCE(huart->Instance));
	   }
	   assert_param(IS_UART_WORD_LENGTH(huart->Init.WordLength));

	   if (huart2->gState == HAL_UART_STATE_RESET)
	   {
	     /* Allocate lock resource and initialize it */
		   huart2->Lock = HAL_UNLOCKED;


//	     /* Init the low level hardware : GPIO, CLOCK */
	     HAL_UART_MspInit(huart2);
	   }

	   huart2->gState = HAL_UART_STATE_BUSY;

	   /* Disable the peripheral */
	   __HAL_UART_DISABLE(huart2);

	   /* Set the UART Communication parameters */
	    UART_SetConfig(huart2);

	   /* In asynchronous mode, the following bits must be kept cleared:
	      - LINEN and CLKEN bits in the USART_CR2 register,
	      - SCEN, HDSEL and IREN  bits in the USART_CR3 register.*/
	   CLEAR_BIT(huart2->Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
	   CLEAR_BIT(huart2->Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

	   /* Enable the peripheral */
	   __HAL_UART_ENABLE(huart2);

	   /* Initialize the UART state */
	   huart2->ErrorCode = HAL_UART_ERROR_NONE;
	   huart2->gState = HAL_UART_STATE_READY;
	   huart2->RxState = HAL_UART_STATE_READY;

	   return HAL_OK;
	 }

///////////////////////////////////////////////////////////
	void HAL_UART_MspInit(UART_HandleTypeDef* huart)
	{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(huart->Instance==USART2)
	  {
	  /* USER CODE BEGIN USART1_MspInit 0 */

	  /* USER CODE END USART1_MspInit 0 */
	    /* Peripheral clock enable */
	    __HAL_RCC_USART2_CLK_ENABLE();

	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    /**USART1 GPIO Configuration
	    PA9     ------> USART1_TX
	    PA10     ------> USART1_RX
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_2;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    /* USART1 interrupt Init */
	    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(USART2_IRQn);

	  }

	}
////////////////////////////////////////////////////////////////
	static void UART_SetConfig(UART_HandleTypeDef *huart)
	{
	  uint32_t tmpreg;
	  uint32_t pclk;

	  /* Check the parameters */
	  assert_param(IS_UART_BAUDRATE(huart->Init.BaudRate));
	  assert_param(IS_UART_STOPBITS(huart->Init.StopBits));
	  assert_param(IS_UART_PARITY(huart->Init.Parity));
	  assert_param(IS_UART_MODE(huart->Init.Mode));

	  /*-------------------------- USART CR2 Configuration -----------------------*/
	  /* Configure the UART Stop Bits: Set STOP[13:12] bits
	     according to huart->Init.StopBits value */
	  MODIFY_REG(huart->Instance->CR2, USART_CR2_STOP, huart->Init.StopBits);

	  /*-------------------------- USART CR1 Configuration -----------------------*/
	  /* Configure the UART Word Length, Parity and mode:
	     Set the M bits according to huart->Init.WordLength value
	     Set PCE and PS bits according to huart->Init.Parity value
	     Set TE and RE bits according to huart->Init.Mode value
	     Set OVER8 bit according to huart->Init.OverSampling value */


	  tmpreg = (uint32_t)huart->Init.WordLength | huart->Init.Parity | huart->Init.Mode;
	  MODIFY_REG(huart->Instance->CR1,
	             (uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE),
	             tmpreg);


	  /*-------------------------- USART CR3 Configuration -----------------------*/
	  /* Configure the UART HFC: Set CTSE and RTSE bits according to huart->Init.HwFlowCtl value */
	  MODIFY_REG(huart->Instance->CR3, (USART_CR3_RTSE | USART_CR3_CTSE), huart->Init.HwFlowCtl);


	  if(huart->Instance == USART1)
	  {
	    pclk = HAL_RCC_GetPCLK2Freq();
	  }
	  else
	  {
	    pclk = HAL_RCC_GetPCLK1Freq();
	  }

	  /*-------------------------- USART BRR Configuration ---------------------*/
	  huart->Instance->BRR = UART_BRR_SAMPLING16(pclk, huart->Init.BaudRate);
	}
////////////////////////////////////////////////////////////////
    uint16_t UART_protocol_controller(protocol d_prot,uint16_t t)
	{
/////////////////////////////////////////////////////0
		d_prot.WR = UART_Reed();
///////////////////////////////////////////////////write command
		if(d_prot.WR == writt)   //56
		{
			UART_Write_HEX(received_writt);            ///rd_1
			d_prot.comand = UART_Reed();
			switch (d_prot.comand)
			{
		    case write_help:
		    	UART_Write_HEX(0x15);
		    break;

		    case write_test_controlle:
		    	UART_Write_HEX(0x16);
		    break;
			}

		}
///////////////////////////////////////////////////read command
		else if(d_prot.WR==readd)
		{
			UART_Write_HEX(received_readd);            ///rd_1

		}
///////////////////////////////////////////////////no command
		else
		{
			t=t+1;
			return (t);
		}
	}
//////////////////////////////////////////////////////////////read
	uint8_t UART_Reed()
	 {
		 uint8_t d2=100;
      //   const int buffer_length = 8;   //7+1
	  //   char str[buffer_length];

		// получить данное
//	   for(uint8_t k=0; k<20; k++)  //1
//	 	{}

	    if ((USART2->SR & USART_SR_RXNE) == 0){}
	   // for (unsigned int i=0;i<strlen(str);i++)
	      d2 = USART2->DR;

	    //	snprintf(str, buffer_length, "%.2X",d2); //4X

	  //	for (unsigned int i=0;i<strlen(str);i++)


	     uint8_t t= HexToDec(d2);

	      return(t);

	 }
////////////////////////////////////////////////////////write

    uint8_t HexToDec(char hexval)
	      {
	      if (hexval<58) {return hexval-48;} //Это цифра. Код нуля - 48, вычитаем 48, получаем просто цифру
	      return hexval-55; //Иначе буква, Код А - 65, вычитаем 55, т.к. А=10.
	      }

	void UART_Write_HEX(uint8_t d1)
	 {
	  	const int buffer_length = 8;   //7+1
	  	char str[buffer_length];
	  	snprintf(str, buffer_length, "%.2X",d1); //4X

//

       for (unsigned int i=0;i<strlen(str);i++)
	      {
    	      while ((USART2->SR & USART_SR_TXE) == 0){} 	// проверка статуса
	          USART2->DR = str[i];  //d1
	       }


//	         USART1->DR = str[i];  //d1
//		     for (unsigned int i=0;i<strlen(str);i++)
//		  	  {}
	 }

	void UART_Write(uint8_t d1)
	{
	      while ((USART2->SR & USART_SR_TXE) == 0){} 	// проверка статуса
	      USART2->DR = d1;  //d1
	}

//////////////////////////////////////////////////
	void UART_print(char *str)
	{
		  for (unsigned int i=0;i<strlen(str);i++)
		  {
			  UART_Write(str[i]);
		  }
	}


  /*
	state	= 0x01,
	request = 0x21,
	sleping	= 0x25,
	test    = 0x26
  */
//////////////////////////////////// - Team write
//-2//

};
///////////////////////////////////////////////////////////////////////////
class _LCD1602 : public Tools
{
public:

//#define LCD_CLEARDISPLAY 0x01

I2C_HandleTypeDef hi2c1;
	typedef struct
	{
		I2C_HandleTypeDef *hi2c; //*hi2c
	    uint16_t DevAddress;
	    LCD_TYPE LCD_Type;
	}LCD1602;


void lcd_ON(I2C_HandleTypeDef *hi2c,char *text,uint8_t in_lcd,uint8_t addres) //20x4
{

//		uint8_t Error_All = 2;

    if(in_lcd==1)
{
    LCD1602 scr;
 	scr.hi2c = hi2c;
	scr.DevAddress = (addres);   // 0x27<< 1   // //LED1

	initLCD(&scr);

   	moveXY(&scr,0,0);  //1-положение
  	lsd_print(&scr,text);

   	moveXY(&scr,0,1);  //1-положение
  	lsd_print(&scr,"#2_0123456789102");

    HAL_Delay(1550);
    printf("LSD initialization\n");
}

    else if(in_lcd==0)
  	     {
  	    	 printf("NO_LSD\n");
  	     }

    HAL_Delay(1000);
  //  display_clear(&scr);
}

void sendData(LCD1602 *scr , uint8_t *pData)
{
  *pData |= (1<<2);// устанавливаем стробирующий сигнал E в 1
  while(HAL_I2C_Master_Transmit(scr->hi2c,scr->DevAddress,pData,1,1000)!=HAL_OK)

  {}
  HAL_Delay(5);
  *pData &=~(1<<2);// устанавливаем стробирующий сигнал E в 0
  while(HAL_I2C_Master_Transmit(scr->hi2c,scr->DevAddress,pData,1,1000)!=HAL_OK)
  {}
  HAL_Delay(5);
}
// initLCD функция начальной инициализации дисплея
// выполняет инструкции инициализации дисплея для четырехбитного интерфейса в соответствии с плгоритмом из datasheet
//void initLCD(LCD1602 *scr)

void initLCD(LCD1602 *scr)
{
  uint8_t buf;
  buf = 0x30; // 0b00110000   Function set

  HAL_Delay(20);   //ждем 15ms пока устанавливается питающее напряжение (например после включения устройства)

  sendData(scr,&buf); //отправляем байт данныx buf
  sendData(scr,&buf); //три раза
  sendData(scr,&buf); //в соответствии с инструкцией по инициализации дисплея

  buf = 0x20; // 0b00100000 выбор 4х битного интерфейса
  sendData(scr,&buf);

  // выбор количетва строк дисплея и шрифт 0x00101000 (смотри datasheet к дисплею)
  // команда отправляется за два раза, так как четырехбитный интерфейс
  buf = 0x20; //  0x20 в двоичном виде 0010 0000: 0010-первый полубайт команды, 0000 - сигналы rs,rw,e,led
  sendData(scr,&buf);
  buf = 0xC0; //1100 0000 N=1 две строки F=1 (5*10), 0000 - сигналы rs,rw,e,led  //0xC0  0x86
  sendData(scr,&buf);


  //display off
  buf =0;
  sendData(scr,&buf);
  buf = 0x80;
  sendData(scr,&buf);
  //display clear
  buf =0;
  sendData(scr,&buf);
  buf = 0x10;
  sendData(scr,&buf);

  //I/D - установка направления движения курсора после ввода символа. (1 - влево, 0 - вправо)
  //S - сдвиг курсора сопровождается сдвигом символов.
  buf = 0;
  sendData(scr,&buf);
  buf = 0x30;
  sendData(scr,&buf);

  //включаем дисплей
  buf =0;
  sendData(scr,&buf);
  buf = 0xC8;
  sendData(scr,&buf);

}
//writeLCD выводим символ s на экран scr
void writeLCD(LCD1602 *scr, uint8_t s)
{
    uint8_t command;
    command = ((s&0xf0)|0x09);    //формируем верхний полубайт в команду для дисплея
    sendData(scr,&command);

    command = ((s&0x0f)<<4)|0x09; // формируем нижний полубайт в команду для дисплея
    sendData(scr,&command);

}

//writeLCD выводим данные s на экран scr
void writeLCD_DEC(LCD1602 *scr, uint8_t d)
{
	char str3[4];
	snprintf(str3,4, "%.3d",d);

   for (unsigned int i=0;i<strlen(str3);i++)
	  {
	  	  writeLCD(scr,str3[i]);
	  }
}

//writeLCD выводим данные s на экран scr
void writeLCD_16_HEX(LCD1602 *scr, uint16_t d)
{
	//char str3[5];

	const int buffer_length = 6+1;
	char str[buffer_length];

	snprintf(str, buffer_length, "0x%.4X",d); //2X

   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}


//writeLCD выводим данные s на экран scr
void writeLCD_HEX(LCD1602 *scr, uint8_t d)  // t =  number of bytes
{
	//char str3[5];

	const int buffer_length = 6+1;   // 4
	char str[buffer_length];

	snprintf(str, buffer_length, "0x%.2X",d); //2X  4

   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}


//writeLCD выводим данные s 2 байта
void writeLCD_2HEX(LCD1602 *scr, uint32_t d)
//                               unsigned int d_high, unsigned int d_low
{
	const int buffer_length = 10+1;
	char str[buffer_length];
	snprintf(str, buffer_length, "0x%.8X",d);
	//snprintf(str, 6, "0x%.2X%.2X", d_high, d_low);


   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}


void lsd_print(LCD1602 *scr,char *str)
{
  for (unsigned int i=0;i<strlen(str);i++)
  {
    writeLCD(scr,str[i]);
  }
}




//  moveXY переместить курсор в позицию X, Y
void moveXY(LCD1602 *scr,uint8_t x,uint8_t y)  //uint8_t x, uint8_t y
{
	uint8_t command, adr;
	// проверим не выходит ли x и y за пределы максимальных значений
	// у дисплея две строчки по 40 символов в каждой согласно даташиту

	if (x>scr->LCD_Type.x){ x = scr->LCD_Type.x;}  //39
	if (y>scr->LCD_Type.y){ y = scr->LCD_Type.y;}


	// переведем координаты x и y в адрес памяти DDRAM согласно инструкции к дисплею
	if (y>1) y=1;    //(y>1) y=1;
	if (x>39) x = 39; //(x>39) x = 39;
	//
	if (y==0)
		adr = x;
	if (y==1)
		adr =     x+0x40;
	if (y==2)
			adr = x+0x40;  //adr = x+0x40;
	if (y==3)
			adr = x+0x40;  //adr = x+0x40;


	// так как используем четырехбитный интрефейс, сформируем две команды для перемещения в нужную позицию DDRAM
	command = ((adr&0xf0)|0x80)|0x08; //adr&0xf0 выделяем старшую тетраду, |0x80 устанавливаем старший бит в 1(DB7=1 согласно инструкции)|0x08 добавляем 8(1000 - Led,E,Rw,Rs) в млаюшую тетраду
	sendData(scr,&command);

	command = (adr<<4)|0x08;
	sendData(scr,&command);

}
//mперемещает дисплей на одну позицию враво
void moveDisplayRight(LCD1602 *scr)
{
	uint8_t command;
	command = 0x18;
	sendData(scr,&command);

	command = 0xC8;
	sendData(scr,&command);
}
// сдвиг в лево moveDispayLeft РїРµСЂРµРјРµС‰Р°РµС‚ РґРёСЃРїР»РµР№ РЅР° РѕРґРЅСѓ РїРѕР·РёС†РёСЋ РІР»РµРІРѕ
void moveDisplayLeft(LCD1602 *scr)
{
	uint8_t command;
		command = 0x18;
		sendData(scr,&command);

		command = 0x88;
		sendData(scr,&command);
}



//display OFF
void display_clear(LCD1602 *scr)
{

	uint8_t command;

	command = 0x00;
	sendData(scr,&command);

	command = 0x10;  //LCD_DISPLAYOFF
	sendData(scr,&command);

	HAL_Delay(1000);

	display_ON(scr);


}

void display_ON(LCD1602 *scr)
{
	uint8_t command;

	command = 0x00;
	sendData(scr,&command);

	command = 0xC8;  //LCD_DISPLAYOFF
	sendData(scr,&command);

	 HAL_Delay(1000);
}

//display clear
void display_OFF(LCD1602 *scr)
{

	uint8_t command;

	command = 0x00;
	sendData(scr,&command);

	command = 0x04;  //LCD_DISPLAYOFF
	sendData(scr,&command);

	 HAL_Delay(1000);

}

};

} //namespace stm103





#endif /* ARM_ARM3_ARM3_PLUS_H_ */
#endif /* arm3_CPP */
