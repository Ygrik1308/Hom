///*
// * MX60LF8G18AC.C
// *
// *  Created on: 28 Ã´Ã¥Ã¢Ã°. 2020 Ã£.
// *      Author: User356
// */
//
///* Includes ------------------------------------------------------------------*/
////#include "main.h"
#include "main.h"
#if defined K9WAG08U1D    // chip
#include <K9WAG08U1D.h>
#include "stm32f4xx_hal.h"


 extern uint8_t RB_EXTI;



void IN_PORT_K9WAG08U1D()
{

	PORT_OUT(GPIOD);        // I0 (0-7)
	PORT_Data(GPIOD,0x00);


	PIN_IN(RB);
	PIN_IN(RB2);

	PIN_OUT(CE);
	PIN_OUT(CE2);

	PIN_OUT(WE);
	PIN_OUT(CLE);
	PIN_OUT(ALE);
	PIN_OUT(RE);
	PIN_OUT(WP);

	PIN_OUT(start);
	PIN_HIGH(start);
	PIN_LOW(start);


	PIN_HIGH(CE);
	PIN_HIGH(CE2);
}




////////////////////////////////////////////////////////
Address_type create_address(uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)               //2048 - data + 64 -  ,4095
{

//	  HAL_Delay(100);
  Address_type at =
  {
		.column_addr1 =  Column & 0xff,                               								  //++
		.column_addr2 = (Column >> 8 ) & 0x0f,                    									  //++
		.row_addr3    = (Page & 0x3F) | ((Plane & 0x01)<<6)| ((Block & 0x01)<<7)  ,              	  //
     	.row_addr4    = ((Block>>1) & 0xFF),
		.row_addr5    = ((Block & 0x600) >> 9),  //FFF

 };
 // printf("At:=%u;\n", at);
  return at;


}



void write_Logik_All(Address_type address,uint16_t error,uint16_t byte,uint16_t data,uint8_t time)  //write ALL
{
	uint16_t  blok[2048]= {0}; //2048
	uint16_t errorw = 0;
	uint16_t bloks_error=0;
	uint8_t str2[]=	"Write_Error\r";
	address = create_address(0,0,0,0);   //die,plane,block,page,byte      2048,32,2048

 /////////////////////////////////////////////////////////////Ried   (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)
	  	   for(uint16_t h=0; h<2; ++h )         //h  plane
	 	     {
	  		   for(uint16_t k=0; k<2049; ++k )    //k bloks
	  		   {
	  			   for(uint16_t j=0; j<65; ++j )  //j page  32
	  			   {
	  	  	               address = create_address(h,k,j,0);  //?BYTe  (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)
	  	  	               errorw = write_Logik(address,data,byte,time,0);

	  	  	               HAL_Delay(10); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ 

		  	  	              if(errorw!=0)
		  							 {

		  							if(k!=blok[bloks_error])  //buf[bloks_error] /blok
		  								{
		  									bloks_error=bloks_error+1;
		  									blok[bloks_error]=k;
		  								//	buf[bloks_error]=j;  ///blok
//		  									printf("Bad Blocks read:=%u:%u:%u:%u;\n",h,k,j,error); //,j

		  								}
		  							}

	  			   }  //j
	  		   }    //k bloks
	 	   }   //h  plane


	if(errorw>error)
	{
		printf("!!!Write_Error\n");
//	//	HAL_UART_Transmit(&huart1,str2,16,0xFFFF);
//	    Alarm(GPIOA);
	}

	printf("Write_Error:%u\n",bloks_error);
}


void write_Logik_All_Adress(Address_type address,uint16_t error,uint16_t byte,uint16_t data,uint8_t time)  //write ALL
{
	uint16_t  blok[2048]= {0}; //2048
	uint16_t errorw = 0;
	uint16_t bloks_error=0;
	uint8_t str2[]=	"Write_Error\r";
	address = create_address(0,0,0,0);   //die,plane,block,page,byte      2048,32,2048

 /////////////////////////////////////////////////////////////Ried   (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)


	  	  	               errorw = write_Logik(address,data,byte,time,0);


	printf("Write_Error:%u\n",bloks_error);
}



void Read_Logik_All(Address_type address,uint16_t error,uint16_t byte,uint16_t data,uint8_t time)   //Read ALL
{
	uint8_t str2[]=	"Error_Read_erase\r";
	uint16_t errorr_2 = 0;

	uint16_t  blok[2048]= {0}; //2048
	uint16_t  bloks_error=0;

//	address = create_address(0,0,0,0);   //die,plane,block,page,byte

/////////////////////////////////////////////////////////////Read

	  /////////////////////////////////////////////////////////////Ried   (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)
	  	   for(uint16_t h=0; h<2; ++h )         //h  plane
	 	     {
	  		   for(uint16_t k=0; k<2048; ++k )    //k bloks
	  		   {
	  			   for(uint16_t j=0; j<64; ++j )  //j page  32
	  			   {
	  	  	              address = create_address(h,k,j,0);  //?BYTe
	  	  	              errorr_2 = Read_Mode_Logik(address,data,byte,time);    //Address_type address, uint8_t test_data, uint16_t byte, uint8_t time)

	  	  	              if(errorr_2!=0)
	  							 {

	  							if(k!=blok[bloks_error])  //buf[bloks_error] /blok
	  								{
 	  									bloks_error=bloks_error+1;
	  									blok[bloks_error]=k;
	  								//	buf[bloks_error]=j;  ///blok

	  									printf("Bad Blocks read:=%u:%u:%u:%u;\n",h,k,j,errorr_2); //,j

	  								}
	  							}
	  	  	    	   //HAL_Delay(1); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ //6
	  	  	     	   _delay_ms(30);  // Ð¼ÐºÑ�  //10
	  			   }  //j
	  		   }    //k bloks
	 	   }   //h  plane

	if(bloks_error>error)
	{
		printf("!!!!Error Read\n");
	//	HAL_UART_Transmit(&huart1,str2,16,0xFFFF);

		Alarm(GPIOA);
	}

	printf("Read-END.Bad Bloks=%u\n",bloks_error);  //bloks_error
 }

void block_erase_Logik_All(Address_type address, uint16_t error_1,uint16_t time)      //erase All
{

	//   address = create_address(0,0);   //die,plane,block,page,byte      2048,32,2048
       uint32_t error_erase = 0;

     for(uint32_t h=0; h<2; ++h ) //j plane
      {
	   for(uint32_t k=0; k<2049; ++k ) //j bloks
	   {
//		  for(uint16_t j=60; j<64; ++j )  //j page  32
//		  {
           address = create_address(h,k,0,0);  //?2047    (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)
    	   error_erase = block_erase_Logik(address,time,0);
    	   HAL_Delay(5); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ //6  7

//		  } //J
	   }  //k
     }  //h



	    if(error_erase>error_1)
		{
			printf("!!Error erase ALL");
		    Alarm(GPIOC);
		}

		printf("erase-ALL-end\n");
}


void block_erase_Logik_All_adress(Address_type address, uint16_t error_1,uint16_t time)      //erase All
{

	//   address = create_address(0,0);   //die,plane,block,page,byte      2048,32,2048
       uint32_t error_erase = 0;


        error_erase = block_erase_Logik(address,time,0);
		printf("erase-ALL-end\n");
}


//////////////////////////////////////////////////////////////////////////////////////
uint32_t READ_Eror_Data_Logik(Address_type address,uint8_t time)  	        //Read bad Blok  ALL
{

	  uint16_t error=0;

	  uint16_t column_address;
	  uint32_t Row_address;

	  uint16_t blok[2050]= {0};
	  uint32_t  bloks_error=0;



	  /////////////////////////////////////////////////////////////Ried   (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)
	  	   for(uint16_t h=0; h<2; ++h )         //h  plane
	 	     {
	  		   for(uint16_t k=0; k<2049; ++k )    //k bloks
	  		   {
	  			   for(uint16_t j=0; j<64; ++j )  //j page  32
	  			   {
	  	  	              address = create_address(h,k,j,2048);  //?BYTe
	  	  	              error = Read_Mode_Error_Logik(address,64,time);

	  	  	              if(error!=0)
	  							 {

	  	  	          	       //  PIN_HIGH(start);
	  	  	        		   //    PIN_LOW(start);

	  							if(k!=blok[bloks_error])  //buf[bloks_error] /blok
	  								{
	  									bloks_error=bloks_error+1;
	  									blok[bloks_error]=k;
	  								//	buf[bloks_error]=j;  ///blok

	  									printf("Bad Blocks ERROR:=%u:%u:%u:%u;\n",h,k,j,error); //,j

	  								}
	  							}
	  	  	   	   _delay_ms(30);  // Ð¼ÐºÑ� 10
	  			   }  //j
	  		   }    //k bloks
	 	   }   //h  plane


	  	if(bloks_error>320)
	  	{
	  		printf("block_erase more allowed");
	//  		UART_Write("block_erase more allowed");
	  		Alarm(GPIOA);
	  	}
	printf("READ_Eror_END.error:=%u;\n",bloks_error);

		return bloks_error; //bloks_error
}


//////////////////////////////////////////////////////////////////////////////////////
uint32_t READ_Eror_Data_Logik_2(Address_type address,uint8_t time)  	        //Read bad Blok  ALL
{

	  uint16_t error=0;

	  uint16_t column_address;
	  uint32_t Row_address;

	  uint16_t blok[2050]= {0};
	  uint32_t  bloks_error=0;



	  /////////////////////////////////////////////////////////////Ried   (uint16_t Plane,uint16_t Block,uint16_t Page,uint16_t Column)
	  	   for(uint16_t h=0; h<2; ++h )         //h  plane
	 	     {
	  		   for(uint16_t k=0; k<2048; ++k )    //k bloks
	  		   {
	  			   for(uint16_t j=0; j<64; ++j )  //j page  32
	  			   {
	  	  	              address = create_address(h,k,j,2048);  //?BYTe
	  	  	              error = Read_Mode_Error_Logik_2(address,64,time);

	  	  	              if(error!=0)
	  							 {

	  	  	          	       //  PIN_HIGH(start);
	  	  	        		   //    PIN_LOW(start);

	  							if(k!=blok[bloks_error])  //buf[bloks_error] /blok
	  								{
	  									bloks_error=bloks_error+1;
	  									blok[bloks_error]=k;
	  								//	buf[bloks_error]=j;  ///blok

	  									printf("Bad Blocks ERROR:=%u:%u:%u:%u;\n",h,k,j,error); //,j

	  								}
	  							}
	  	  	   	   _delay_ms(10);  // Ð¼ÐºÑ�
	  			   }  //j
	  		   }    //k bloks
	 	   }   //h  plane


	  	if(bloks_error>320)
	  	{
	  		printf("block_erase more allowed");
	//  		UART_Write("block_erase more allowed");
	  		Alarm(GPIOA);
	  	}
	printf("READ_Eror_END._error2:=%u;\n",bloks_error);

		return bloks_error; //bloks_error
}







uint16_t Read_Mode_Logik(Address_type address, uint8_t test_data, uint16_t byte, uint8_t time)  //Read Mode in mass address
{

	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿


	PORT_OUT(GPIOD);
	//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);
	//////////////////////

		PIN_LOW(CE);

		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x00); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr5);
		PIN_HIGH(WE);

		PIN_LOW(ALE);


		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x30);  //Command 30H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PORT_IN(GPIOD);

	    _delay_ms(time);

		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}

		PIN_HIGH(CE);

/////////////////////////////////////////// Ã¯Ã°Ã®Ã¢Ã¥Ã°ÃªÃ 

		uint32_t error=0;
		for (uint16_t i = 0; i<byte ; i++)
		{
      //    printf("%u: %u\n", i, data[i]);		  ///++
      //	UART_Write(buf[i]);                   ///++
	        if(test_data!=data[i])
	        {
	    	  	error=error+1;
	    	//	printf("%u: %u\n", 1, data[i]);		  ///++
	        }
	        if(data[i]==0xAA)
	        {
	    		printf("0xAA\n"); //,j
	        }

		}

//////////////////////////////////////////////////////

		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

		return error;

}

uint32_t Read_Mode_Error_Logik(Address_type address, uint16_t byte,uint8_t time)          //Read Mode in mass blok Error 64 Byte in mass address
{
	//   int var = 0;  // Ã®Ã¡Ã¿Ã§Ã Ã²Ã¥Ã«Ã¼Ã­Ã® Ã±Ã­Ã Ã·Ã Ã«Ã  Ã®Ã¡ÃºÃ¿Ã¢Ã«Ã¿Ã¥Ã¬ Ã¯Ã¥Ã°Ã¥Ã¬Ã¥Ã­Ã­Ã³Ã¾ /


	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿
//	NVIC_EnableIRQ(EXTI1_IRQn);


	PORT_Data(GPIOD,0x54); //Command 00H

	PORT_OUT(GPIOD);
	//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);
	//////////////////////

		PIN_LOW(CE);

		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x00); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr5);
		PIN_HIGH(WE);

		PIN_LOW(ALE);

		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x30);  //Command 30H
		PIN_HIGH(WE);
		PIN_LOW(CLE);



//		while(RB_EXTI==0){};



		PORT_IN(GPIOD);

		_delay_ms(time);         //!!!!!!25mkS max



		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}

		PIN_HIGH(CE);

/////////////////////////////////////////// Ã¯Ã°Ã®Ã¢Ã¥Ã°ÃªÃ 

		uint16_t Test=0xFF;
		uint32_t error=0;
		for (uint16_t i = 0; i<byte ; i++)
		{
    	//	  printf("%u: %u\n", i, data[i]);		  ///++
		//	UART_Write(buf[i]);                   ///++
			if(Test!=data[i]) error=error+1;
		}



//////////////////////////////////////////////////////


//		PORT_Data(GPIOD,0x55); //Command 00H

		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿


//		if(error!=0)
//		{
//			HAL_Delay(100);
//		}

		return (error);

}



uint32_t Read_Mode_Error_Logik_2(Address_type address, uint16_t byte,uint8_t time)          //Read Mode in mass blok Error 64 Byte in mass address
{
	//   int var = 0;  // Ã®Ã¡Ã¿Ã§Ã Ã²Ã¥Ã«Ã¼Ã­Ã® Ã±Ã­Ã Ã·Ã Ã«Ã  Ã®Ã¡ÃºÃ¿Ã¢Ã«Ã¿Ã¥Ã¬ Ã¯Ã¥Ã°Ã¥Ã¬Ã¥Ã­Ã­Ã³Ã¾ /


	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿
//	NVIC_EnableIRQ(EXTI1_IRQn);


//	PORT_Data(GPIOD,0x54); //Command 00H

	PORT_OUT(GPIOD);
	//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE2);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);
	//////////////////////

		PIN_LOW(CE2);

		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x00); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr5);
		PIN_HIGH(WE);

		PIN_LOW(ALE);

		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x30);  //Command 30H
		PIN_HIGH(WE);
		PIN_LOW(CLE);



//		while(RB_EXTI==0){};



		PORT_IN(GPIOD);

		_delay_ms(time);         //!!!!!!25mkS max



		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}

		PIN_HIGH(CE2);

/////////////////////////////////////////// Ã¯Ã°Ã®Ã¢Ã¥Ã°ÃªÃ 

		uint16_t Test=0xFF;
		uint32_t error=0;
		for (uint16_t i = 0; i<byte ; i++)
		{
    	//	  printf("%u: %u\n", i, data[i]);		  ///++
		//	UART_Write(buf[i]);                   ///++
			if(Test!=data[i]) error=error+1;
		}



//////////////////////////////////////////////////////


//		PORT_Data(GPIOD,0x55); //Command 00H

		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿


//		if(error!=0)
//		{
//			HAL_Delay(100);
//		}

		return (error);

}





///////////////////////////////////////////////////////////////////////////////////
uint16_t write_Logik(Address_type address, uint8_t data, uint16_t byte,uint16_t time,uint32_t error) //buf
{


	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿
	PIN_HIGH(start);
	PORT_OUT(GPIOD);
//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);

//////////////////////
		PIN_LOW(start);
		PIN_HIGH(start);
		PIN_LOW(start);


		PIN_LOW(CE);

		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x80); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);    //+


		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.column_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr5);
		PIN_HIGH(WE);


		PIN_LOW(ALE);

	//	_delay_ms(time);         //!!!!!!25mkS max


		for (uint16_t i = 0; i<byte ; i++)
{
		PIN_LOW(WE);
		PORT_Data(GPIOD,data);  //Command 30H  buf[i]
		PIN_HIGH(WE);
}


		PIN_HIGH(CLE);
		PIN_LOW(WE);
	    PORT_Data(GPIOD,0x10);  //Command 10H
		PIN_HIGH(WE);
		PIN_LOW(CLE);


    	_delay_ms(time);

m1:

        PIN_HIGH(CLE);
  		PIN_LOW(WE);
		PORT_Data(GPIOD,0x70);  //Command 70H
		PIN_HIGH(WE);
		PIN_LOW(CLE);


		PORT_IN(GPIOD);

		PIN_LOW(RE);
		uint16_t data_0=PORT_READ_8(GPIOD,0);
		PIN_HIGH(RE);




	   while((data_0 & 0x04)==0)   //data_0 == 0x70
	   {
		   error=error+1;
//		   printf("SR:%u\n", data_0);
		   goto m1;
	   }
		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

      if(error>1)
      {
	  	printf("!!Program Error Write");
  	    Alarm(GPIOA);
      }

	  return error;//data_0

}

uint16_t block_erase_Logik(Address_type address,uint8_t time,uint8_t error) //  address,time,0
{

   //    uint32_t number_of_faulty_pages = 0;
   //    address = create_address(0,0,0,0,0);



	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿
//	PIN_HIGH(start);
	PORT_OUT(GPIOD);
//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);

//////////////////////
//		PIN_LOW(start);
//		PIN_HIGH(start);
//		PIN_LOW(start);
//		PIN_HIGH(start);
//		PIN_LOW(start);

		PIN_LOW(CE);


		PIN_HIGH(CLE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x60); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);    //+
		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.row_addr5);
		PIN_HIGH(WE);
		PIN_LOW(ALE);



		PIN_HIGH(CLE);
		PIN_LOW(WE);
	    PORT_Data(GPIOD,0xD0);  //Command 10H
		PIN_HIGH(WE);
		PIN_LOW(CLE);


m2:
       _delay_ms(time);         //!!!!!!25mkS max    time





		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x70);  //Command 70H
    	PIN_HIGH(WE);
		PIN_LOW(CLE);


		PIN_LOW(RE);
		PORT_IN(GPIOD);
		uint16_t data_0=PORT_READ_8(GPIOD,0);
		PIN_HIGH(RE);




	   if((data_0 & 0x40)!=0)
	   {
		   error=error+1;
//		   printf("SR:%u\n", data_0);
//	  	    Alarm(GPIOA);
		   goto m2;
	   }

		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

	    PIN_HIGH(CE);

	       if(error>1)
	   {
		  	printf("!!Program Error erise");
	  	    Alarm(GPIOA);
	   }


	   error=0;
       return (error) ;   //data_0

	//   printf("SR:%u\n", data_0);		  ///++
	//   HAL_Delay(1); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ 

}

//////////////////////////////////////////////////////////////////////////// ALL
void Test_Logik(Address_type address,uint8_t error, uint16_t byte)       //TEST RW
{
	uint16_t errorw = 0;
	uint16_t errorr	= 0;
	uint8_t str2[]	= "Error W/R Test\r";
	uint8_t str1[]	= "Error Write Test\r";

	uint16_t  blok[2048]= {0}; //2048
	uint16_t  bloks_error=0;

	uint8_t data[2] = { 0xAA, 0x55 };
//	   uint8_t data_read[10] = { 0x00 }; //2048
//	address = create_address(0,0);   //die,plane,block,page,byte      2048,32,2048


 //   write_Logik_All(address,error,byte);

    //	write_Logik_All(address,error,byte);
	//   write_Logik_All(address,error,byte);

	/*
// Ã¯Ã°Ã®Ã¢Ã¥Ã°Ã¥Ã­Ã®
/////////////////////////////////////////////////////////////////Write
	  for(uint16_t m=0; m<2; ++m )          //m die
  {
	   for(uint16_t h=0; h<2; ++h )         //h  plane
	     {
		   for(uint16_t k=0; k<2049; ++k )  //k bloks
		   {
			   for(uint16_t j=0; j<65; ++j )  //j page
			   {
					   address = create_address(m,h,k,j,0);
					   errorw = write_Logik(address,data[0],byte);
			   }  //j
		   }  // k
	     } //h
  }  //m

	  if(errorw != 0)
	{
		printf("Error Write Test\n");
		HAL_UART_Transmit(&huart1,str1,16,0xFFFF);
	    Alarm(GPIOA);
	}
*/
/*
/////////////////////////////////////////////////////////////Read
	for(uint16_t m=0; m<2; ++m )
	{          		//m die
	  for(uint16_t h=0; h<2; ++h )
	  {         	//h  plane
		  for(uint16_t k=0; k<2049; ++k )
		  { 	//k bloks
			  for(uint16_t j=0; j<65; ++j )
			  {  	//j page
				  address = create_address(m,h,k,j,0);
				  errorr = Read_Mode_Logik( address,data[0],byte);

					//	  printf("%u: %u\n", t, data_read[t]);		  ///++
				  if(errorr != 0)
				  {
					   if(k != blok[bloks_error])
					   {
							bloks_error = bloks_error+1;
							blok[bloks_error]=k;
							printf("Bad Blocks_RW:%u:%u:%u=%u;\n",m,h,k,errorr); //,j
					   }
				  }
			  }  //j
		  }  // k
	  } //h
	}  //m
*/
	if(bloks_error>error)
	{
		printf("Error W/R Test\n");
		HAL_UART_Transmit(&huart1,str2,16,0xFFFF);
	    Alarm(GPIOA);
	}

	printf("Write_Error:%u\n",errorw);
	printf("bloks_total:%u\n",bloks_error);
	printf("Error_total: %u\n",errorr);
}
/*
uint16_t write_speed(uint16_t adress_1, uint16_t  adress_2,uint16_t adress_3,
		 uint16_t adress_4, uint16_t adress_5,uint8_t data,uint16_t number_of_bytes)
{


	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

	PORT_OUT(GPIOD);
//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);

//////////////////////

		PIN_LOW(CE);


		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x80); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);    //+


		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_5);
		PIN_HIGH(WE);


		PIN_LOW(ALE);

//		delay_nop(50); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  25


//		PIN_LOW(WE);
//		PORT_Data(GPIOD,data);  //Command 30H
//		PIN_HIGH(WE);




		for (uint16_t i = 0; i<number_of_bytes ; i++)
{
		PIN_LOW(WE);
		PORT_Data(GPIOD,data);  //Command 30H
		PIN_HIGH(WE);
}

		PIN_HIGH(CLE);

		PIN_LOW(WE);
	    PORT_Data(GPIOD,0x10);  //Command 10H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		delay_nop(50);  /// 25


		PIN_HIGH(CLE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x70);  //Command 70H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		PIN_LOW(RE);
		PORT_IN(GPIOD);
		uint16_t data_0=PORT_READ_8(GPIOD,0);
		PIN_HIGH(RE);

	   printf("SR= %u\n",data_0);

		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

	//	  HAL_Delay(1); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ 

	  return 0 ;//data_0

}


uint32_t Read_Mode(uint16_t adress_1, uint16_t  adress_2,uint16_t adress_3,
				 uint16_t adress_4, uint16_t adress_5,uint16_t byte)             //Read Mode speed
{

	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿
////////////////////////////////////////////////////////////////////////////
	   int var = 0;  // Ã®Ã¡Ã¿Ã§Ã Ã²Ã¥Ã«Ã¼Ã­Ã® Ã±Ã­Ã Ã·Ã Ã«Ã  Ã®Ã¡ÃºÃ¿Ã¢Ã«Ã¿Ã¥Ã¬ Ã¯Ã¥Ã°Ã¥Ã¬Ã¥Ã­Ã­Ã³Ã¾ /
	   while ( var == 0 )    // Ã‚Ã»Ã¯Ã®Ã«Ã­Ã Ã¥Ã¬ Ã¯Ã®ÃªÃ  0
	  {
		  var=READ_PIN(RB);
		//  fail_signal(GPIOC,6);
	  }
////////////////////////////////////////////////////////////////////////////


	PORT_OUT(GPIOD);
//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
//////////////////////

		PIN_LOW(CE);
		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x00); //Command 00H

		PIN_HIGH(WE);
		PIN_LOW(CLE);
		PIN_HIGH(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_5);
		PIN_HIGH(WE);

		PIN_HIGH(CLE);
		PIN_LOW(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x30);  //Command 30H
		PIN_HIGH(WE);

		PIN_LOW(CLE);

		PORT_IN(GPIOD);

		delay_nop(25); //RB Ã§Ã Ã¤Ã¥Ã°Ã¦ÃªÃ  25 8 MÃƒÃ¶  Ã¯Ã°Ã¨ 64 250 ÃŒÃƒÃ¶


		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}


		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

		uint16_t Test=0xFF;
		uint32_t error=0;
		for (uint16_t i = 0; i<byte ; i++)
		{
		//	printf("%u: %u\n", i, data[i]);		  ///++
		//	UART_Write(data[i]);                  ///++
			if(Test!=data[i]) error=error+1;

		}

		return error;
}


///////////////////////////////Read exit control
void READ_RB()
{

	 int var = 0;  // Ã®Ã¡Ã¿Ã§Ã Ã²Ã¥Ã«Ã¼Ã­Ã® Ã±Ã­Ã Ã·Ã Ã«Ã  Ã®Ã¡ÃºÃ¿Ã¢Ã«Ã¿Ã¥Ã¬ Ã¯Ã¥Ã°Ã¥Ã¬Ã¥Ã­Ã­Ã³Ã¾ //
    while ( var != 1 )    // Ã‚Ã»Ã¯Ã®Ã«Ã­Ã Ã¥Ã¬ Ã¯Ã®ÃªÃ  0
	  {
		  var=READ_PIN(RB);
	  }

	  delay_nop(100); //24 ÃŒÃƒÃ–

	 while ( var != 1 )    // Ã‚Ã»Ã¯Ã®Ã«Ã­Ã Ã¥Ã¬ Ã¯Ã®ÃªÃ  1 Ã¦Ã¤Â¸Ã¬ 0
	  {
		  var=READ_PIN(RB);
	  }
}
*/
///////////////////////////////Read exit control
uint8_t Command_RESET()
{
	NVIC_EnableIRQ(EXTI1_IRQn);
	uint8_t error=0;


	PORT_OUT(GPIOD);
    PIN_HIGH(start);
    PIN_LOW(start);

    PIN_HIGH(start);

//////////////////////0
	PIN_LOW(CLE);
	PIN_HIGH(CE);
	PIN_HIGH(WE);
	PIN_HIGH(ALE);

	PIN_HIGH(WP);
//////////////////////////
	PIN_LOW(start);

	PIN_LOW(ALE);
	PIN_HIGH(CLE);
	PIN_LOW(CE);


	PIN_LOW(WE);
	PORT_Data(GPIOD,0x00FF);
	PIN_HIGH(WE);

	PIN_HIGH(CE);
	PIN_LOW(CLE);
	PIN_HIGH(ALE);

    if(RB_EXTI>0)
    {
	     printf("RB-ok:=%.2X \n", RB_EXTI);
	     NVIC_DisableIRQ(EXTI1_IRQn);
	 	 NVIC_ClearPendingIRQ(EXTI1_IRQn);
	 	RB_EXTI=0;
    }
    else
    {
    	  printf("RB-error \n");
    	  error=1;
    }


	PORT_IN(GPIOD);    ///go to reset PORT


return (error);

}

/*
void Command(uint16_t Command)
{

	PORT_OUT(GPIOD);

//////////////////////0
	PIN_LOW(CLE);
	PIN_HIGH(CE);
	PIN_HIGH(WE);
	PIN_HIGH(ALE);
//////////////////////////

	PIN_LOW(CE);
    delay_nop(1);      // 2 Ã�Ã‘
    PIN_HIGH(CLE);
    delay_nop(1);      // 2 Ã�Ã‘
	PIN_LOW(ALE);
    delay_nop(1);      // 2 Ã�Ã‘
	PIN_LOW(WE);

	PORT_Data(GPIOD,Command);

    delay_nop(10); // 10 Ã�Ã‘

    PIN_HIGH(WE);
    delay_nop(5);  // 5 Ã�Ã‘
    PIN_HIGH(CE);
    PIN_HIGH(ALE);
    PIN_LOW(CLE);

	PORT_IN(GPIOD);    ///go to reset PORT

}
*/
void Read_ID(uint16_t Command)
{
	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

	PORT_OUT(GPIOD);
 //   PIN_LOW(RE);

    delay_nop(80);
	PIN_HIGH(start);
/////////////////////////init


	PIN_HIGH(RE);
	PIN_LOW(CLE);
	PIN_HIGH(CE);
	PIN_HIGH(WE);
	PIN_LOW(ALE);

	PORT_WriteRandom(GPIOD,Command);  //Ã¯Ã¥Ã°Ã¥Ã£Ã®Ã°Ã¥Ã« Ã¯Ã®Ã°Ã²

	PIN_LOW(start);
//////////////////////////begin

	PIN_HIGH(CLE);
	PIN_LOW(WE);
	PIN_LOW(CE);

	PIN_HIGH(WE);
	PIN_LOW(CLE);
//	PIN_HIGH(CE);

	PORT_Data(GPIOD,0x00);

	PIN_HIGH(ALE);
//	PIN_LOW(CE);
	PIN_LOW(WE);
	PIN_HIGH(WE);

//	PIN_HIGH(CE);
	PIN_LOW(ALE);
//	PIN_LOW(CE);

	//GPIOD->CRL  = 0x44444444;
	PORT_IN(GPIOD);


	//GPIOD->BSRR = (uint32_t)(1<<4)<< 16U; //0
	PIN_LOW(RE);
    uint8_t data1=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);


    PIN_LOW(RE);
	uint8_t data2=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);



	PIN_LOW(RE);
	uint8_t data3=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);


    PIN_LOW(RE);
	uint8_t data4=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);



    PIN_LOW(RE);
	uint8_t data5=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);




	__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

   if( (data1==0xec) && (data2==0xd3) && (data3==0x51) && (data4==0x95) && (data5==0x58) )
   {
	   printf("K9F1G08U0B \n");
   }
   else
   {

	   printf("DD %.2X:=%.2X:%.2X:%.2X:%.2X \n", data1,data2,data3,data4,data5);   //"0x%.4X"
	   printf("!!!No chip ID\n");
	   Alarm(GPIOA);
   }




 //   delay_nop(5);  // 5 Ã�Ã‘
}
/*
void Read_ID_ONFI(uint16_t Command)  //90H
{
	PORT_OUT(GPIOD);

/////////////////////////init
	PIN_LOW(CLE);
	PIN_HIGH(CE);
	PIN_HIGH(WE);
	PIN_LOW(ALE);
	PIN_HIGH(RE);

//////////////////////////begin
	PIN_HIGH(CLE);
	PIN_LOW(CE);
	PIN_LOW(WE);

	PORT_Data(GPIOD,Command);


//	delay_nop(2);      // 2 Ã�Ã‘
	PIN_HIGH(WE);
//	delay_nop(2);      // 2 Ã�Ã‘
	PIN_LOW(CLE);
	PIN_HIGH(ALE);
//	delay_nop(2);      // 2 Ã�Ã‘
	PIN_LOW(WE);
	PORT_Data(GPIOD,0x20);

//	delay_nop(2);      // 2 Ã�Ã‘
	PIN_HIGH(WE);
	PIN_LOW(ALE);
//	delay_nop(1);      // 2 Ã�Ã‘



	PORT_IN(GPIOD);

    PIN_LOW(RE);
	uint8_t data1=PORT_READ_8(GPIOD,0);    //79=0x4F,
	PIN_HIGH(RE);




    PIN_LOW(RE);
	uint8_t data2=PORT_READ_8(GPIOD,0);    // 78=0x4E,
	PIN_HIGH(RE);



	PIN_LOW(RE);
	uint8_t data3=PORT_READ_8(GPIOD,0);    //70=0x46,
	PIN_HIGH(RE);



    PIN_LOW(RE);
	uint8_t data4=PORT_READ_8(GPIOD,0);    //73=0x49
	PIN_HIGH(RE);

   if( (data1==0x4F) && (data2==0x4E) && (data3=0x46) && (data4==0x49) )
   {
	   printf("MX60LF8G18AC  \n");
   }

//    printf("DD1: %u\n", data1);
//    printf("DD2: %u\n", data2);
//    printf("DD3: %u\n", data3);
//    printf("DD4: %u\n", data4);
}

*/
/*
void READ_speed_Data()   //Read ALL
{
	  uint32_t number_of_faulty_pages = 0;
	 for(uint16_t i=0; i<8; ++i )
	 {
		 for(uint16_t j=0; j<256; ++j )
		 {
			 for(uint16_t k=0; k<256; ++k )
			 {
				 uint32_t error=Read_Mode(0x00,0x08,k,j,i,64);

				 if(error!=0)
				 {
					 number_of_faulty_pages++;
					 printf("%u:%u:%u=%u:\n",k,j,i,error);
				 }
			  }
		 }
	 }
	printf("%u\n", number_of_faulty_pages/64);

}

uint16_t block_erase(uint16_t adress_3,uint16_t adress_4,uint16_t adress_5)
{
	__disable_irq (); // Ã§Ã Ã¯Ã°Ã¥Ã²Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿

	PORT_OUT(GPIOD);
//////////////////////
		PIN_LOW(CLE);
		PIN_HIGH(CE);
		PIN_HIGH(WE);
		PIN_LOW(ALE);
		PIN_HIGH(RE);

//////////////////////

		PIN_LOW(CE);


		PIN_HIGH(CLE);
		PIN_LOW(WE);
		PORT_Data(GPIOD,0x60); //Command 00H
		PIN_HIGH(WE);
		PIN_LOW(CLE);

		PIN_HIGH(ALE);    //+

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,adress_5);
		PIN_HIGH(WE);


		PIN_LOW(ALE);

		PIN_HIGH(CLE);

		PIN_LOW(WE);
	    PORT_Data(GPIOD,0xD0);  //Command 10H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		delay_nop(50);  /// 25


		PIN_HIGH(CLE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x70);  //Command 70H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		PIN_LOW(RE);
		PORT_IN(GPIOD);
		uint16_t data_0=PORT_READ_8(GPIOD,0);
		PIN_HIGH(RE);

	   printf("SR= %u\n",data_0);

		__enable_irq ();  // Ã°Ã Ã§Ã°Ã¥Ã¸Ã¨Ã²Ã¼ Ã¯Ã°Ã¥Ã°Ã»Ã¢Ã Ã­Ã¨Ã¿


	  return (data_0) ;   //data_0

}
*/
#endif
