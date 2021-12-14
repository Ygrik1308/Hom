///*
// * MX60LF8G18AC.C
// *
// *  Created on: 20 мая. 2020 г.
// *      Author: Tarasov
// */

#include "main.h"
#if defined MT29F32G08AFABAWP    // chip

/* Includes ------------------------------------------------------------------*/
//#include "main.h"
#include "MT29F32G08AFABAWP.h"
#include "delay.h"
#include "lcd.h"


    #define RB     GPIOE,1  // INPUT

    #define WE     GPIOC,0  // OUTPUT  серый
    #define CE     GPIOC,1  // OUTPUT  фиолетовый
    #define CLE    GPIOC,2  // OUTPUT  синий
    #define ALE    GPIOC,3  // OUTPUT  зелёный
    #define RE     GPIOC,4  // OUTPUT  желтый
    #define WP     GPIOC,5  // OUTPUT  белый
    #define START  GPIOC,7  // OUTPUT  red

	#define PORT   GPIOD    // OUTPUT/INPUT PIN0...7
///////////////////////////////////////////////////////

////////////////////////////////////////////////////////

 void init_PORT_MT29F32G08AFABAWP()
  {

	   PORT_OUT(PORT);
       PIN_OUT(START);

       PIN_IN(RB);

	   PIN_OUT(WE);
	   PIN_OUT(CE);
	   PIN_OUT(CLE);
	   PIN_OUT(ALE);
	   PIN_OUT(RE);
	   PIN_OUT(WP);

	   PIN_HIGH(WE);
	   PIN_HIGH(CLE);
	   PIN_HIGH(ALE);
	   PIN_HIGH(CE);
	   PIN_HIGH(RE);
	   PIN_HIGH(WP);

	   printf("OUT initialization\n");
	   HAL_Delay(500);

  }

void MT29F32G08AFABAWP_TEST()
{

	   Command_RESET();      // || Command(0x00FF);        //RESET работает больше 8 MГц на STM
	   Read_ID_ONFI(0x90);     //READ ID
	   delay_nop(80);
	   Read_ID(0x90);     //READ ID

}

Address_type create_address( uint16_t die,                 //0-1
							 uint16_t plane,			   //0-1
							 uint16_t block,               //2048
							 uint16_t page,                //128
							 uint16_t colum )              //1024 - data + 64 -  ,4095
{

//	  HAL_Delay(100);
  Address_type at = {
		.one_addr1 		= colum & 0xff,                                   //++
		.two_addr2 		= ((( colum >> 8 ) & 0xff) |(0>>7)|(0>>6)|(0>>5)),                          //++
		.three_addr3    = (( plane & 0x01 ) << 7)  | (page & 0x127),    //
		.four_addr4     = ( block  & 0xff ),
		.five_addr5     = (( block >> 8 ) & 0x07 ) | (( die & 0x01 ) << 3 )  //9
	};
  return at;

}


void write_Logik_All(Address_type address,uint16_t error,uint16_t byte)  //write ALL
{
	uint16_t errorw = 0;
//	   uint16_t errorr = 0;
	uint8_t str2[]=	"Write_Error\r";
//	   uint16_t  blok[2048]= {0}; //2048
//	   uint16_t  bloks_error=0;


	uint8_t data[2] = { 0xAA, 0x55 };
//	   uint8_t data_read[10] = { 0x00 }; //2048
	address = create_address(0,0,0,0,0);   //die,plane,block,page,byte      2048,32,2048
// проверено
/////////////////////////////////////////////////////////////////Write
	for(uint16_t m=0; m<2; ++m ) // //m die
	{
	   for(uint16_t h=0; h<2; ++h )  //h  plane
	   {
		   for(uint16_t k=0; k<8192; ++k ) //k bloks
		   {
			   for(uint16_t j=0; j<129; ++j )  // //j page
			   {
				   address = create_address(m,h,k,j,0);
				   errorw = write_Logik(address,data[0],byte);
			   }  //j
		   }  // k
	   } //h
	}  //m

	if(errorw>error)
	{
		printf("Write_Error\n");
		HAL_UART_Transmit(&huart1,str2,16,0xFFFF);
	    Alarm(GPIOC);
	}

	printf("Write_Error:%u\n",errorw);
}

void Read_Logik_All(Address_type address,uint16_t error,uint16_t byte)   //Read ALL
{
	uint8_t str2[]=	"Error_Read_erase\r";
	uint16_t errorr = 0;

	uint16_t  blok[2048]= {0}; //2048
	uint16_t  bloks_error=0;

	address = create_address(0,0,0,0,0);   //die,plane,block,page,byte

/////////////////////////////////////////////////////////////Read
		for(uint16_t m=0; m<2; ++m ) // //m die
			{
				  for(uint16_t h=0; h<2; ++h )  //h  plane
				  {
				   for(uint16_t k=0; k<8192; ++k ) //k bloks
				   {
					   for(uint16_t j=0; j<129; ++j )  // //j page
					   {
						 address = create_address(m,h,k,j,0);
				         errorr = Read_Mode_Logik( address,0xFF,byte);

					//	  printf("%u: %u\n", t, data_read[t]);		  ///++
				   if(errorr != 0)
				   {
					   if(k!=blok[bloks_error])
					   {
						   bloks_error=bloks_error+1;
						   blok[bloks_error]=k;
						   printf("Bad Blocks_erase:%u:%u:%u=%u;\n",m,h,k,errorr); //,j
					   }
				   }
			   }  //j
		   }  // k
		} //h
	}  //m

	if(bloks_error>error)
	{
		printf("Error Read erase\n");
		HAL_UART_Transmit(&huart1,str2,16,0xFFFF);
	    Alarm(GPIOC);
	}


 }

void block_erase_Logik_All(Address_type address, uint16_t error_1)      //erase All
{

	   address = create_address(0,0,0,0,0);   //die,plane,block,page,byte      2048,32,2048
       uint32_t error_erase = 0;


	  for(uint16_t m=0; m<2; ++m )          //m die
  {
	   for(uint16_t h=0; h<2; ++h )         //h  plane
	     {
		   for(uint16_t k=0; k<2049; ++k )  //k bloks
		   {
			   for(uint16_t j=0; j<65; ++j )  //j page
			   {
				    address = create_address(m,h,k,0,0);
				    error_erase = block_erase_Logik(address);
			   }  //j
		   }  // k
	     } //h
  }  //m

	    if(error_erase>error_1)
		{
			printf("Error erase ALL");
		    Alarm(GPIOC);
		}

		printf("erase-ALL\n");
}

//////////////////////////////////////////////////////////////////////////////////////
uint32_t READ_Eror_Data_Logik(Address_type address,uint8_t *buf)  	        //Read bad Blok  ALL
{
	//  uint32_t number_of_faulty_pages = 0;
	//  uint8_t data_read[number_of_bytes] = { 0x00 };
	  uint16_t error=0;
	  address = create_address(0,0,0,0,0);

	  uint16_t blok[10]= {0};
	  uint32_t  bloks_error=0;

	  /////////////////////////////////////////////////////////////Ried
	  	  for(uint16_t m=0; m<2; ++m )          //m die
	    {
	  	   for(uint16_t h=0; h<2; ++h )         //h  plane
	 	     {
	  		   for(uint16_t k=0; k<8192; ++k )    //k bloks
	  		   {
	  			   for(uint16_t j=0; j<129; ++j )  //j page  129
	  			   {
	  	  	              address = create_address(m,h,k,j,4320);  //?2047
	  	  	              error = Read_Mode_Error_Logik(address,224);

	  	  	              if(error!=0)
	  							 {
	  							   	 // number_of_faulty_pages++;
	  								 //printf("%u:%u:%u:%u=%u:\n",m,h,k,j,error);
	  							if(k!=blok[bloks_error])  //buf[bloks_error] /blok
	  								{
	  									bloks_error=bloks_error+1;
	  									blok[bloks_error]=k;
	  									buf[bloks_error]=k;  ///blok

	  									printf("Bad Blocks:%u:%u:%u=%u;\n",m,h,k,error); //,j
	  								}
	  							}

	  				   }  //j
	  		   }  //k
	 	    } //h
	    }  //m

	  	if(bloks_error>80)
	  	{
	  		printf("block_erase more allowed");
	//  		UART_Write("block_erase more allowed");
	  		Alarm(GPIOC);
	  	}
	printf("READ_Eror_END\n");

		return bloks_error; //bloks_error
}

uint16_t Read_Mode_Logik(Address_type address, uint8_t Test, uint16_t byte)  //Read Mode in mass address
{

	__disable_irq (); // запретить прерывания

	   int var = 0;  /* обязательно сначала объявляем переменную */
	   while ( var == 0 )    // Выполнаем пока 0
	  {
		  var=READ_PIN(RB);
		//  fail_signal(GPIOC,6);
	  }

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
		PORT_Data(GPIOD,address.one_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.two_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.three_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.four_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.five_addr5);
		PIN_HIGH(WE);

		PIN_HIGH(CLE);
		PIN_LOW(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x30);  //Command 30H
		PIN_HIGH(WE);

		PIN_LOW(CLE);

		PORT_IN(GPIOD);

		delay_nop(25); //RB задержка 25 8 MГц  при 64 250 МГц


		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}

/////////////////////////////////////////// проверка

		uint32_t error=0;
		for (uint16_t i = 0; i<byte ; i++)
		{
       //   printf("%u: %u\n", i, data[i]);		  ///++
      //	UART_Write(buf[i]);                   ///++
	        if(Test!=data[i])
	        {
	    	  	error=error+1;
	        }
	     }



//////////////////////////////////////////////////////

		__enable_irq ();  // разрешить прерывания

		return error;

}

uint32_t Read_Mode_Error_Logik(Address_type address, uint16_t byte)          //Read Mode in mass blok Error 64 Byte in mass address
{

	__disable_irq (); // запретить прерывания

	   int var = 0;  /* обязательно сначала объявляем переменную */
	   while ( var == 0 )    // Выполнаем пока 0
	  {
		  var=READ_PIN(RB);
		//  fail_signal(GPIOC,6);
	  }

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
		PORT_Data(GPIOD,address.one_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.two_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.three_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.four_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.five_addr5);
		PIN_HIGH(WE);

		PIN_HIGH(CLE);
		PIN_LOW(ALE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x30);  //Command 30H
		PIN_HIGH(WE);

		PIN_LOW(CLE);

		PORT_IN(GPIOD);

//		delay_nop(25); //      25   RB задержка 25 8 MГц  при 64 250 МГц
//	    _delay_ms(15);   //?

		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}

/////////////////////////////////////////// проверка

		uint16_t Test=0xFF;
		uint32_t error=0;
		for (uint16_t i = 0; i<byte ; i++)
		{
		//	printf("%u: %u\n", i, data[i]);		  ///++
		//	UART_Write(buf[i]);                   ///++
			if(Test!=data[i]) error=error+1;

		}

//////////////////////////////////////////////////////

		__enable_irq ();  // разрешить прерывания

		return (error);

}

///////////////////////////////////////////////////////////////////////////////////
uint16_t write_Logik(Address_type address, uint8_t buf, uint16_t byte) //*buf
{


	__disable_irq (); // запретить прерывания

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
		PORT_Data(GPIOD,address.one_addr1);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.two_addr2);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.three_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.four_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.five_addr5);
		PIN_HIGH(WE);


		PIN_LOW(ALE);

//		delay_nop(50); //RB задержка 25

/*
		PIN_LOW(WE);
		PORT_Data(GPIOD,data);  //Command 30H
		PIN_HIGH(WE);
*/



		for (uint16_t i = 0; i<byte ; i++)
{
		PIN_LOW(WE);
		PORT_Data(GPIOD,buf);  //Command 30H  buf[i]
		PIN_HIGH(WE);
}

		PIN_HIGH(CLE);

		PIN_LOW(WE);
	    PORT_Data(GPIOD,0x10);  //Command 10H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


//		delay_nop(50);  /// 50     ----25


		PIN_HIGH(CLE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x70);  //Command 70H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		PIN_LOW(RE);
		PORT_IN(GPIOD);
		uint16_t data_0=PORT_READ_8(GPIOD,0);
		PIN_HIGH(RE);

	   uint32_t error=0;
	   if((data_0 & 0x01) != 0)
	   {
		   error=error+1;
		   printf("SR:%u\n", data_0);		  ///++

	   }
		__enable_irq ();  // разрешить прерывания

	//	  HAL_Delay(1); //RB задержка
	    _delay_ms(15);   //?

	  return error;//data_0

}

uint16_t block_erase_Logik(Address_type address) //
{

   //    uint32_t number_of_faulty_pages = 0;
   //    address = create_address(0,0,0,0,0);



	__disable_irq (); // запретить прерывания

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
		PORT_Data(GPIOD,address.three_addr3);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.four_addr4);
		PIN_HIGH(WE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,address.five_addr5);
		PIN_HIGH(WE);


		PIN_LOW(ALE);

		PIN_HIGH(CLE);

		PIN_LOW(WE);
	    PORT_Data(GPIOD,0xD0);  //Command 10H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		delay_nop(25);  /// 25


		PIN_HIGH(CLE);

		PIN_LOW(WE);
		PORT_Data(GPIOD,0x70);  //Command 70H
		PIN_HIGH(WE);

		PIN_LOW(CLE);


		PIN_LOW(RE);
		PORT_IN(GPIOD);
		uint16_t data_0=PORT_READ_8(GPIOD,0);
		PIN_HIGH(RE);

	   uint32_t error=0;
	   if((data_0 & 0x01) != 0)
	   {
		   error=error+1;
	   }


		__enable_irq ();  // разрешить прерывания


	  return (error) ;   //data_0

	 //  printf("SR:%u\n", data_0);		  ///++
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
	address = create_address(0,0,0,0,0);   //die,plane,block,page,byte      2048,32,2048

	write_Logik_All(address,error,byte);

	Read_Logik_All(address,error,byte);

/*
// проверено
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
*/


	  if(errorw != 0)
	{
		printf("Error Write Test\n");
		HAL_UART_Transmit(&huart1,str1,16,0xFFFF);
	    Alarm(GPIOC);
	}


/////////////////////////////////////////////////////////////Read
	for(uint16_t m=0; m<2; ++m )  //m die
	{
	  for(uint16_t h=0; h<2; ++h )  //h  plane
	  {
		  for(uint16_t k=0; k<2049; ++k )  //k bloks
		  {
			  for(uint16_t j=0; j<65; ++j ) //j page
			  {
				  address = create_address(m,h,k,j,0);
				  errorr = Read_Mode_Logik( address,data[0],byte);

					//	  printf("%u: %u\n", t, data_read[t]);		  ///++
				  if(errorr != 0) {
					   if(k != blok[bloks_error]) {
							bloks_error = bloks_error+1;
							blok[bloks_error]=k;
							printf("Bad Blocks_RW:%u:%u:%u=%u;\n",m,h,k,errorr); //,j
					   }
				  }
			  }  //j
		  }  // k
	  } //h
	}  //m

	if(bloks_error>error)
	{
		printf("Error W/R Test\n");
	    Alarm(GPIOC);
	}




	printf("Write_Error:%u\n",errorw);
	printf("bloks_total:%u\n",bloks_error);
	printf("Error_total: %u\n",errorr);
}

uint16_t write_speed(uint16_t adress_1, uint16_t  adress_2,uint16_t adress_3,
		 uint16_t adress_4, uint16_t adress_5,uint8_t data,uint16_t number_of_bytes)
{


	__disable_irq (); // запретить прерывания

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

//		delay_nop(50); //RB задержка 25

/*
		PIN_LOW(WE);
		PORT_Data(GPIOD,data);  //Command 30H
		PIN_HIGH(WE);
*/



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

		__enable_irq ();  // разрешить прерывания

	//	  HAL_Delay(1); //RB задержка

	  return 0 ;//data_0

}


uint32_t Read_Mode(uint16_t adress_1, uint16_t  adress_2,uint16_t adress_3,
				 uint16_t adress_4, uint16_t adress_5,uint16_t byte)             //Read Mode speed
{

	__disable_irq (); // запретить прерывания
////////////////////////////////////////////////////////////////////////////
	   int var = 0;  /* обязательно сначала объявляем переменную */
	   while ( var == 0 )    // Выполнаем пока 0
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

		delay_nop(25); //RB задержка 25 8 MГц  при 64 250 МГц


		uint16_t data[byte];

		for (uint16_t i = 0; i<byte ; i++)
		{
			PIN_LOW(RE);
			data[i]=PORT_READ_8(GPIOD,0);
			PIN_HIGH(RE);
		}


		__enable_irq ();  // разрешить прерывания

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

	 int var = 0;  /* обязательно сначала объявляем переменную */
    while ( var != 1 )    // Выполнаем пока 0
	  {
		  var=READ_PIN(RB);
	  }

	  delay_nop(100); //24 МГЦ

	 while ( var != 1 )    // Выполнаем пока 1 ждём 0
	  {
		  var=READ_PIN(RB);
	  }
}
///////////////////////////////Read exit control
void Command_RESET()
{

	PORT_OUT(GPIOD);

   int var = 0;  /* обязательно сначала объявляем переменную */
   while ( var == 0 )    // Выполнаем пока 0
  {
	  var=READ_PIN(RB);
	  fail_signal(GPIOA,6);
  }

//////////////////////0
	PIN_LOW(CLE);
	PIN_HIGH(CE);
	PIN_HIGH(WE);
	PIN_HIGH(ALE);
//////////////////////////


	PIN_LOW(CE);
    delay_nop(1);      // 2 НС
    PIN_HIGH(CLE);
    delay_nop(1);      // 2 НС
	PIN_LOW(ALE);
    delay_nop(1);      // 2 НС
	PIN_LOW(WE);

	PORT_Data(GPIOD,0x00FF);


	//delay_nop(10); // 10 НС
    // _delay_ms(10);


    PIN_HIGH(WE);
    var=READ_PIN(RB);


    //delay_nop(5);  // 5 НС
    PIN_HIGH(CE);
    PIN_HIGH(ALE);   //???
    PIN_LOW(CLE);

/*
    while ( var == 1 )    // Выполнаем пока 1 ждём 0
	  {
		  var=READ_PIN(RB);
		  fail_signal(GPIOC,7);
	  }
*/
	PORT_IN(GPIOD);    ///go to reset PORT
	printf("RB-ok \n");
}


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
    delay_nop(1);      // 2 НС
    PIN_HIGH(CLE);
    delay_nop(1);      // 2 НС
	PIN_LOW(ALE);
    delay_nop(1);      // 2 НС
	PIN_LOW(WE);

	PORT_Data(GPIOD,Command);

    delay_nop(10); // 10 НС

    PIN_HIGH(WE);
    delay_nop(5);  // 5 НС
    PIN_HIGH(CE);
    PIN_HIGH(ALE);
    PIN_LOW(CLE);

	PORT_IN(GPIOD);    ///go to reset PORT

}

void Read_ID(uint16_t Command)
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


//	delay_nop(2);      // 2 НС
	PIN_HIGH(WE);
//	delay_nop(2);      // 2 НС
	PIN_LOW(CLE);
	PIN_HIGH(ALE);
//	delay_nop(2);      // 2 НС
	PIN_LOW(WE);
	PORT_Data(GPIOD,0x00);

//	delay_nop(2);      // 2 НС
	PIN_HIGH(WE);
	PIN_LOW(ALE);
//	delay_nop(1);      // 2 НС



	PORT_IN(GPIOD);

    PIN_LOW(RE);
	uint8_t data0=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);

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

    PIN_LOW(RE);
	uint8_t data6=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);

    PIN_LOW(RE);
	uint8_t data7=PORT_READ_8(GPIOD,0);
	PIN_HIGH(RE);


	   if( (data0==0x2C) && (data1==0x48) && (data2==0x00) && (data3==0x26) && (data4==0x89) && (data5==0x00) && (data6==0x00) && (data7==0x00) )
	   {
		   printf("MT29F32G08AFABA\n");
	   }


    printf("D0: %.2X\n", data0);
    printf("D1: %.2X\n", data1);
    printf("D2: %.2X\n", data2);
    printf("D3: %.2X\n", data3);
    printf("D4: %.2X\n", data4);
    printf("D5: %.2X\n", data5);
    printf("D6: %.2X\n", data6);
    printf("D7: %.2X\n", data7);

}

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


//	delay_nop(2);      // 2 НС
	PIN_HIGH(WE);
//	delay_nop(2);      // 2 НС
	PIN_LOW(CLE);
	PIN_HIGH(ALE);
//	delay_nop(2);      // 2 НС
	PIN_LOW(WE);
	PORT_Data(GPIOD,0x20);

//	delay_nop(2);      // 2 НС
	PIN_HIGH(WE);
	PIN_LOW(ALE);
//	delay_nop(1);      // 2 НС



	PORT_IN(PORT);

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

	PIN_LOW(RE);
	uint8_t data5=PORT_READ_8(GPIOD,0);    //73=0x49
    PIN_HIGH(RE);
//
//	PIN_LOW(RE);
//	uint8_t data6=PORT_READ_8(GPIOD,0);    //73=0x49
//	PIN_HIGH(RE);
//
//	PIN_LOW(RE);
//	uint8_t data7=PORT_READ_8(GPIOD,0);    //73=0x49
//	PIN_HIGH(RE);


   if( (data1==0x4F) && (data2==0x4E) && (data3==0x46) && (data4==0x49) )
   {
	   printf("Read ID 20h\n");
   }

    printf("DD1: %.2X\n", data1);   //"0x%.4X"
    printf("DD2: %.2X\n", data2);
    printf("DD3: %.2X\n", data3);
    printf("DD4: %.2X\n", data4);
    printf("DD5: %.2X\n", data5);
//    printf("DD6: %u\n", data6);
//    printf("DD7: %u\n", data7);

}


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
	__disable_irq (); // запретить прерывания

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

		__enable_irq ();  // разрешить прерывания


	  return (data_0) ;   //data_0

}





/*
	  Address_type Addres={0,0,0,0,0};
	  create_address Type={0,0,0,0,0};

	  uint32_t Adress_logics[]={
			       Addres.column_addr1 = Type.byte & 0xff,
			       Addres.column_addr2 = ( Type.byte >> 8 ) & 0x0f,
				   Addres.row_addr3 = (( Type.page & 0x3f ) | (( Type.plane & 0x01 ) << 6) | ( Type.block & 0x01 ) << 7 ),
				   Addres.row_addr4 = ( Type.block >> 1 ) & 0xff,
				   Addres.row_addr5 = ((Type.block >> 9 ) & 0x03 ) | (( Type.die & 0x01 ) << 2 )
	  	  	  	  	  	  	  	};

	  Type.byte=0;	 //1-й байт
	  Type.page=0;   //1-я страница
	  Type.block=0;  //1-й блок
	  Type.plane=0;  //1-я сторона
	  Type.die=0;    //1-я область
*/

/*

uint32_t Adress_logics[]={
		       Addres.column_addr1 = Type.byte & 0xff,
		       Addres.column_addr2 = ( Type.byte >> 8 ) & 0x0f,
			   Addres.row_addr3 = (( Type.page & 0x3f ) | (( Type.plane & 0x01 ) << 6) | ( Type.block & 0x01 ) << 7 ),
			   Addres.row_addr4 = ( Type.block >> 1 ) & 0xff,
			   Addres.row_addr5 = ((Type.block >> 9 ) & 0x03 ) | (( Type.die & 0x01 ) << 2 )
	  	  	  	  	  	  	};

*/
/*
 * //Address_type Addres={0,0,0,0,0};
//create_address Type={0,0,0,0,0};


//  Type.page=2048;
//  Adress_logics[0]=500;

//uint32_t error=Read_Mode(Adress_logics[0],Adress_logics[1],Adress_logics[2],
//				Adress_logics[3],Adress_logics[4],bytes);   //(0x00,0x08,0,0,0,1);

//create_address(0,0,0,0x800,0);

//   uint32_t error=Read_Mode(0x00,0x08,0,0,0,1);
//    READ_speed_Data();

// uint16_t SR= write( address, data, number_of_bytes );



 //	  Random_Inpurt( address, data_read,number_of_bytes);
//	  for (uint16_t i = 0; i<number_of_bytes ; i++)
//	  	{
//	  	  printf("Data: %u \n",data_read[0]);
//	  	}



 //     create_address(0,0,0,0,2048);   // Преверяем регистр
//	  Random_Inpurt( address, data_read,number_of_bytes);

//	  for (uint16_t i = 0; i<number_of_bytes ; i++)
//	  	{
//	  	  printf("Ibit: %u \n",data_read[0]);
//	  	}


 */
/*
 */
#endif


