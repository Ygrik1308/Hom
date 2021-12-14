/*
 * RAM_CY.C
 *
 *  Created on: 20 ???. 2020 ?.
 *      Author: user26
 */

#include "main.h"
/////////////////////////////////////////////
#if defined RAM_CY    // chip
///////////////////////////////////////
/*
uint32_t TEST_lowByte_RAM(RAM chip)
{
	uint16_t Test  = 0;
	uint32_t error = 0;
	uint16_t data = 0;

	uint32_t a_tic=0x0000;
    LCD1602 scr;

    uint32_t ad_max= 144;// 262144; //262144 max

	data = 0x5555;






	for(uint32_t addr = 0; addr <ad_max ; addr++)  /// dataWrite   pow(2,19)  //262  //262144 max
	{
		dataWrite(chip,addr,data);
	//	delay_nop(1);
	}

//	  HAL_Delay(1);


	for(uint32_t addr = 0; addr <ad_max ; addr++)  // dataRead  pow(2,19) // 262
	{
		Test=dataRead(chip,addr);
		if(Test!=data) error=error+1;
//		printf("TEST: %u\n", Test);
//		printf("ERror: %u\n", error);
	//	delay_nop(1);

	}

if(error!=0)
{
	Alarm(GPIOA);
}

	  HAL_Delay(1);



	data = 0x5555;
	for(uint32_t addr = 0; addr < pow(2,19); addr++)  //
	{
		dataWrite(addr,data);

		a_tic=a_tic+1;

		asm("nop");
 	    printf("Test: %d\n", a_tic);

	}

	for(uint32_t addr = 0; addr < pow(2,19); addr++)  //
	{
		Test=dataRead(addr);
		if(Test!=data) error=error+1;
	}


	delay_nop(50);			// 4 tact


return error;
}

//	  PINS_data(chip.m.Data,data,16);							 // data send 16 //	  setData(data);


void dataWrite(RAM chip,uint32_t addr, uint16_t data)   // записать данные одиночно по адресу
{

  	CHIP_RAM_init(chip);

	 PINS_data(chip.RAM1.Address,addr,12);   //m.Address
	 for(uint32_t i=0;i<16;i++){PINS_IN(chip.RAM1.Data[i]);}

   PINS_LOW(chip.p.nCE);

	  PINS_HIGH(chip.p.nOE); //
	  PINS_LOW(chip.p.BHE);
	  PINS_LOW(chip.p.BLE);

	  PINS_LOW(chip.p.nWE);
  for(uint32_t i=0;i<16;i++){PINS_OUT(chip.m.Data[i]);}      // data out 16 //	  dataOut();  	  /// PIN data to Out

//  GPIOD->MODER |=(0x55555555 & 0xFFFFFF7);  //OUT
//  GPIOB->MODER |= 0x1UL << (10*2UL);

//////////////////////////////////////////////////PIN DATA
  GPIOD->ODR |=(data & 0xFFFB);
  GPIOB->ODR |=(data & 0x4)<<8;
//////////////////////////////////////////////////////
  HAL_Delay(50);

  	  PINS_HIGH(chip.p.nWE); // nWE = 1 //	  writeDis();     //end Write

  PINS_HIGH(chip.p.BHE);
  PINS_HIGH(chip.p.BLE);

  PINS_HIGH(chip.p.nCE);


}

uint16_t dataRead(RAM chip,uint32_t addr)
{
  uint16_t result = 0;

  PINS_data(chip.m.Address,addr,12);					 //
  for(uint32_t i=0;i<16;i++){PINS_IN(chip.m.Data[i]);}   // 16 // 	//  PORT_IN(GPIOD);

//  PORT_PP(GPIOD);
//  PIN_PP(GPIOB,10);

  PINS_LOW(chip.p.nCE);    									 //

      PINS_HIGH(chip.p.nWE); //
  	  PINS_LOW(chip.p.BHE);
  	  PINS_LOW(chip.p.BLE);

  PINS_LOW(chip.p.nOE);   	 							 //readEn();    				//  resolution Read // nOE = 0
  	  HAL_Delay(50);
	  result = ((GPIOD->IDR) & 0xFFFB)|((GPIOB->IDR & 0x400)>>8); //& mask

	  //result=PORTS_READ(chip.m.Data,16);  				//	  result=readData();     //read data

  PINS_HIGH(chip.p.nOE);  								// readDis();    				//  resolution Read
	  PINS_HIGH(chip.p.BHE);
	  PINS_HIGH(chip.p.BLE);

  PINS_HIGH(chip.p.nCE);
 return result;
}
*/
#endif /* RAM_CY */
