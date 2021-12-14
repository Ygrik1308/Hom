#include "main.h"
/////////////////////////////////////////////
#if defined SPI    // chip
///////////////////////////////////////
#include "SPI.h"
void SPI_PIN(TypeSPI SP)
{



}

void initspi_AD(TypeSPI *SP) // 6_pin
{
	PINS_OUT(SP->nCS);  //nCS
	PINS_OUT(SP->SPI_SCLK);  //nCS
	PINS_OUT(SP->SPI_SDIO);  //nCS
	PINS_OUT(SP->I_RESET);   //nCS
	PINS_OUT(SP->TX_ENABL);
	PINS_IN(SP->SPI_SDO);    //nCS

////////////////////////////////////////////////
	PINS_HIGH(SP->nCS);      //nCS
	PINS_LOW(SP->SPI_SCLK);  //nCS
	PINS_LOW(SP->SPI_SDIO);  //nCS
	PINS_LOW(SP->I_RESET);   //nCS
	PINS_LOW(SP->TX_ENABL);
}
////////////////////////////////////////////////////////////
void SPI_INIT_4pin_Reset(TypeSPI SP)  //MOSI,MISO,CS,RESET
{
	PINS_OUT(SP.I_RESET);  //nCS
	PINS_OUT(SP.nCS);  //nCS
	PINS_OUT(SP.SPI_SCLK);  //nCS
	PINS_OUT(SP.SPI_SDIO);  //nCS

	PINS_LOW(SP.I_RESET);  //nCS
	PINS_HIGH(SP.nCS);  //nCS
	PINS_LOW(SP.SPI_SCLK);  //nCS
	PINS_LOW(SP.SPI_SDIO);  //nCS

}
//////////////////////////////////////////////////////////////
void reset_SPI(TypeSPI SP)
{
	  PINS_OUT(SP.I_RESET);
	  PINS_HIGH(SP.I_RESET);    //go to SPI
	  delay_nop(255);
	  PINS_LOW(SP.I_RESET);    //go to SPI
	  HAL_Delay(500);
}
///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void SPI_INIT_4pin(TypeSPI2 SP)  //MOSI,MISO,SCLK,CS,
{
	PINS_OUT(SP.nCS);   //
	PINS_OUT(SP.MOSI);  //
	PINS_OUT(SP.CLK);  //

	PINS_IN (SP.MISO);  //

	PINS_HIGH(SP.nCS);  //
	PINS_LOW(SP.MOSI);  //
	PINS_LOW(SP.CLK);  //

}
//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////Work
void read_SPI_AD(TypeSPI spi,uint8_t *DefAddres) //read REGISTER// SPI_SDIO->OUT_>IN
{
	  uint8_t Addres[21]=   {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x14,0x1F}; /// ГѓпїЅГ‚ВїГѓпїЅГ‚ВµГѓвЂ�ГўвЂљВ¬ГѓпїЅГ‚ВІГѓвЂ�Гўв‚¬В№ГѓпїЅГ‚В№ ГѓвЂ�ГЇВїВЅГѓвЂ�Гўв‚¬ВЎГѓпїЅГ‚ВёГѓвЂ�Гўв‚¬ЕЎГѓвЂ�Гўв‚¬В№ГѓпїЅГ‚ВІГѓпїЅГ‚В°ГѓпїЅГ‚ВµГѓвЂ�Гўв‚¬ЕЎГѓвЂ�ГЇВїВЅГѓвЂ�ГЇВїВЅ ГѓпїЅГ‚ВїГѓвЂ�ГўвЂљВ¬ГѓпїЅГ‚В°ГѓпїЅГ‚ВІГѓпїЅГ‚ВёГѓпїЅГ‚В»ГѓвЂ�Г…вЂ™ГѓпїЅГ‚ВЅГѓпїЅГ‚Вѕ ГѓпїЅГ‚ВѕГѓвЂ�ГЇВїВЅГѓвЂ�Гўв‚¬ЕЎГѓпїЅГ‚В°ГѓпїЅГ‚В»ГѓвЂ�Г…вЂ™ГѓпїЅГ‚ВЅГѓвЂ�Гўв‚¬В№ГѓпїЅГ‚Вµ ГѓпїЅГ‚В°ГѓпїЅГ‚ВґГѓвЂ�ГўвЂљВ¬ГѓпїЅГ‚ВµГѓвЂ�ГЇВїВЅГѓпїЅГ‚В° ГѓпїЅГ‚ВїГѓпїЅГ‚ВѕГѓпїЅГ‚ВїГѓвЂ�ГўвЂљВ¬ГѓпїЅГ‚В°ГѓпїЅГ‚ВІГѓпїЅГ‚ВёГѓвЂ�Гўв‚¬ЕЎГѓвЂ�Г…вЂ™ ГѓпїЅГ‚В»ГѓпїЅГ‚ВёГѓпїЅГ‚В±ГѓпїЅГ‚Вѕ ГѓвЂ�Гўв‚¬ВЎГѓпїЅГ‚ВёГѓвЂ�Гўв‚¬ЕЎГѓпїЅГ‚В°ГѓвЂ�Гўв‚¬ЕЎГѓвЂ�Г…вЂ™ ГѓпїЅГ‚ВѕГѓпїЅГ‚ВґГѓпїЅГ‚ВЅГѓпїЅГ‚ВѕГѓпїЅГ‚В№ ГѓпїЅГ‚ВїГѓпїЅГ‚ВїГѓпїЅГ‚ВѕГѓвЂ�ГЇВїВЅГѓвЂ�Гўв‚¬В№ГѓпїЅГ‚В»ГѓпїЅГ‚ВєГѓпїЅГ‚ВѕГѓпїЅГ‚В№
	  uint8_t OutAddres[22]={0};
	 ////////////////////////////////////////////////////////////
	for(uint8_t i=0;i<21;i++)   //21
	{
	  PINS_LOW(spi.SPI_SDIO);
	  PINS_OUT(spi.SPI_SDIO);


	  PINS_LOW(spi.nCS);                   ///////+


	  PINS_LOW(spi.SPI_SCLK);
	  delay_nop(3);
	  PINS_HIGH(spi.SPI_SDIO);     //READ
	  PINS_HIGH(spi.SPI_SCLK);
	  delay_nop(5);

	  PINS_LOW(spi.SPI_SCLK);
	  delay_nop(3);
	  PINS_LOW(spi.SPI_SDIO);      //N1
	  PINS_HIGH(spi.SPI_SCLK);
	  delay_nop(5);

	  PINS_LOW(spi.SPI_SCLK);
	  delay_nop(3);
	  PINS_LOW(spi.SPI_SDIO);      //N0
	  PINS_HIGH(spi.SPI_SCLK);
	  delay_nop(5);

	   uint16_t address=Addres[i];  // 0x1
	   for(uint8_t i=0;i<13;i++)
	 {
		 PINS_LOW(spi.SPI_SCLK);
		 (address  & 16)  ? PINS_HIGH(spi.SPI_SDIO) : PINS_LOW(spi.SPI_SDIO);
	     address <<=1;  //>>
		 delay_nop(2);
		 PINS_HIGH(spi.SPI_SCLK);
		 delay_nop(4);
	 }

	   PINS_IN(spi.SPI_SDIO);
	   uint8_t d = READS_DATA_CLK(spi.SPI_SDIO,0,8,spi.SPI_SCLK);
	   PINS_HIGH(spi.nCS);

	   OutAddres[i] = d;

/*
if(i!=21)
{
	  if(DefAddres[i]!=OutAddres[i])
	  {
		  Alarm(GPIOA);
	  }

}
else
   {
	   printf("Versia:=%x\n",d);
   }
*/
       printf("%u:=%x\n",i,d);
	}
	   delay_nop(100);
}









/*
void Write_SPI_AD(AD9715BCPZ spi,uint8_t address,uint8_t data_in)
{
	  PINS_LOW(spi.SDIO0);
	  PINS_OUT(spi.SDIO0);

	  PINS_LOW(spi.CS0);                   ///////+

	  PINS_LOW(spi.SCL0);
	  delay_nop(3);
	  PINS_LOW(spi.SDIO0);     //READ- HIGH / Write- LOW
	  PINS_HIGH(spi.SCL0);
	  delay_nop(5);
///////////////////////////////////N1=N0- 1 byte
	  PINS_LOW(spi.SCL0);
	  delay_nop(3);
	  PINS_LOW(spi.SDIO0);      //N1
	  PINS_HIGH(spi.SCL0);
	  delay_nop(5);

	  PINS_LOW(spi.SCL0);
	  delay_nop(3);
	  PINS_LOW(spi.SDIO0);      //N0
	  PINS_HIGH(spi.SCL0);
	  delay_nop(5);
////////////////////////////////////////////////// write address
     for(uint8_t i=0;i<5;i++)
    {
		 PINS_LOW(spi.SCL0);
		 (address  & 16)  ? PINS_HIGH(spi.SDIO0) : PINS_LOW(spi.SDIO0);
	     address <<=1;  //>>
		 delay_nop(2);
		 PINS_HIGH(spi.SCL0);
		 delay_nop(4);
     }
///////////////////////////////////////////////// read data registr
	    for(uint8_t i=0;i<8;i++)
	 {
		 PINS_LOW(spi.SCL0);
		 (data_in  & 128)  ? PINS_HIGH(spi.SDIO0) : PINS_LOW(spi.SDIO0);
		 data_in <<=1;  //>>
		 delay_nop(2);
		 PINS_HIGH(spi.SCL0);
		 delay_nop(4);
	 }

//	   uint8_t d = READS_DATA(spi.SDIO0,0,8,spi.SCL0);
	   PINS_HIGH(spi.CS0);
//////////////////////////////////////////////// end
	   delay_nop(100);
}




//////////////////////////////////////////////////////////////////////////////////////////function

uint32_t readspi_AD(TypeSPI *SPI,uint8_t byte,uint8_t address,uSPI_3_INITint8_t mask)
{
uint8_t f=0;
uint8_t ff=0;

ff = 0x80 | (address & 0x0F)|(0<<5)|(0<<6);    //r7 // 0x0F
//ff=reverse_8(ff);

PINS_LOW(SPI->nCS);

//	f=PINS_data_clk_BI(SPI,ff,byte);
	PINS_data_clk(SPI,ff,byte);   //
	PINS_LOW(SPI->SPI_SDIO);  //nCS
    delay_nop(10);
	f=PINS_read_clk(SPI,32,mask);    //16
PINS_HIGH(SPI->nCS);

return (f);
}

void writespi_AD(TypeSPI *SPI,uint8_t byte,uint8_t address,uint8_t mask)
{
uint8_t ff=0;

ff =(0<<7) | (address & 0x0F)|(0<<5)|(0<<6);    //r7
ff=reverse_8(ff);

PINS_LOW(SPI->nCS);

    PINS_data_clk(SPI,ff,byte);   //
	PINS_LOW(SPI->SPI_SDIO);  //nCS
    delay_nop(1);
	PINS_data_clk(SPI,0x2,32);   // 32

PINS_HIGH(SPI->nCS);
}

/////////////////////////////////////////////////////////////////////////////////

uint32_t PINS_read_clk(TypeSPI *SPI,uint16_t bytes,uint8_t mask)  // set addres
{
	//GPIO send[]={};
	uint8_t d=0;


	for(uint8_t i = 0; i < bytes; ++i)
	{
		PINS_HIGH(SPI->SPI_SCLK);
		d=READS_PIN(SPI->SPI_SDO);
		d >>= 1;
		PINS_LOW(SPI->SPI_SCLK);
		delay_nop(2);
	}

return(d);

}


void PINS_data_clk(TypeSPI *SPI,uint32_t ddata,uint16_t bytes)  // set addres
{

	for(uint8_t i = 0; i < bytes; ++i)
	{
		PINS_HIGH(SPI->SPI_SCLK);
		(ddata  & 1 )  ? PINS_HIGH(SPI->SPI_SDIO) : PINS_LOW(SPI->SPI_SDIO);
		ddata >>= 1;
//		delay_nop(2);
		PINS_LOW(SPI->SPI_SCLK);
		delay_nop(2);
	}
}

uint32_t PINS_data_clk_BI(TypeSPI *SPI,uint32_t ddata,uint16_t bytes)  // set addres
{
	uint8_t f=0;
	uint8_t ff=0;

	ff = 0x80 | (ddata & 0x0F)|(0<<5)|(0<<6);    //r7
	ff=reverse_8(ff);
	PINS_OUT(SPI->SPI_SDIO);  //nCS

	PINS_LOW(SPI->nCS);

	for(uint8_t i = 0; i < bytes; ++i)
	{
		PINS_HIGH(SPI->SPI_SCLK);
		(ff  & 1 )  ? PINS_HIGH(SPI->SPI_SDIO) : PINS_LOW(SPI->SPI_SDIO);
		ff >>= 1;
		PINS_LOW(SPI->SPI_SCLK);
		delay_nop(2);
	}

	PINS_LOW(SPI->SPI_SDIO);
	PINS_IN(SPI->SPI_SDIO);  //nCS

	for(uint8_t i = 0; i < 32; ++i) //32
	{
		PINS_HIGH(SPI->SPI_SCLK);
		f=READS_PIN(SPI->SPI_SDO);
		f >>= 1;
		PINS_LOW(SPI->SPI_SCLK);
		delay_nop(2);
	}
	PINS_HIGH(SPI->nCS);

	PINS_OUT(SPI->SPI_SDIO);  //nCS

return(f);

}



void initspi()
{
	PIN_OUT(SCLK);
	PIN_OUT(nCS);
	PIN_OUT(nOE);
	PIN_IN(SDIO_1);

}
*/

void spiWriteByte(TypeSPI2 SPIS, uint16_t addr, uint8_t val2wr)
{

	volatile uint16_t loc_addr	= addr & 0x1FFF;
	volatile uint16_t mask;
//	PIN_LOW(nOE);
	
	//nCS0();
	//PIN_LOW(nCS);

	mask = 0x8000;
	for(uint8_t i = 0; i < 8; i++)
	{
		(loc_addr & mask) ? sdio1() : sdio0();
		sclkPulse();
		mask >>= 1;
	}
	_delay_us(20);
	mask = 0x80;
	for(uint8_t i = 0; i < 8; i++)
	{
		(val2wr & mask) ? sdio1() : sdio0();
		sclkPulse();
		mask >>= 1;
	}
//	PIN_HIGH(nCS);
}

/*
uint8_t spiReadData(uint16_t addr)
{
	volatile uint8_t result = 0;
	volatile uint16_t mask=0x8000;
	volatile uint16_t loc_addr = mask | (addr & 0x1FFF);


	PIN_LOW(nOE);
	//nCS0();
	PIN_LOW(nCS);
	;
	for(uint8_t i = 0; i < BYTELEN*2; i++)
	{
		(loc_addr & mask) ? sdio1() : sdio0();
		asm("nop");
		sclkPulse();
		mask >>= 1;
	}
	_delay_us(20);
	
	sdioZ();
	for(uint8_t i = 0; i < BYTELEN-1; i++)
	{
//		sclk1();
		PIN_HIGH(SCLK);
		_delay_us(10);

		if(READ_PIN(SDIO_1)==1)  //  GPIOD->IDR & (1 << 11)
		result |= 1;
		result <<= 1;

		PIN_LOW(SCLK);
		//sclk0();
		_delay_us(10);
	}

	PIN_HIGH(SCLK);
//	sclk1();
	_delay_us(10);

	if((READ_PIN(SDIO_1))==1)
		result |= 1;
	PIN_LOW(SCLK);
//	sclk0();
	_delay_us(10);
	PIN_HIGH(nCS);
	//nCS1();
	return result;
}
*/

#endif /* SPI */
