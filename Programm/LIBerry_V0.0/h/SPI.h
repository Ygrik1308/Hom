#include "main.h"
/////////////////////////////////////////////
#if defined SPI    // chip
///////////////////////////////////////
#ifndef H_SPI_H_
#define H_SPI_H_

//#include "GPIO_ARM3.h"


//#define CTRLPORT	    PORTD
//#define CTRLDDR		DDRD
//#define CTRLPIN		PIND
//#define BYTELEN		8



typedef struct  //AD
{
	GPIO nCS;		//CS
	GPIO SPI_SCLK;	//CLOK
	GPIO SPI_SDIO;	//MISO
	GPIO SPI_SDO;   //MOSI
	GPIO I_RESET;   //Reset
	GPIO TX_ENABL;	//CS
} TypeSPI;



typedef struct
{
	GPIO nCS;		//CS
	GPIO CLK;	    //CLOK
	GPIO MOSI;	 	//MOSO  OUT
	GPIO MISO;   	//MISO	 IN
	GPIO RESET;     //Reset
} TypeSPI2;



void initspi_AD(TypeSPI *SPI);
void SPI_INIT_4pin(TypeSPI2 SP);

//     GPIO SPI[]={nCS,SPI_SCLK,SPI_SDIO,SPI_SDO};


//#define SCLK		GPIOC,10
//#define SDIO_1		GPIOC,11
////#define nCS		    GPIOC,12
//#define nOE			GPIOC,8







/*
#define DB_PIN0		PINE		// D07...D00
#define DB_DDR0		DDRE
#define DB_PIN1		PINB		// D11...D08
#define DB_DDR1		DDRB
*/

/*
void sdio0()
{
//	CTRLPORT &= ~(1 << SDIO);
	PIN_HIGH(SDIO_1);
	PIN_OUT(SDIO_1);
//	CTRLDDR |=  (1 << SDIO);
}
void sdio1()
{
	PIN_LOW(SDIO_1);
	PIN_OUT(SDIO_1);
//	CTRLPORT |=  (1 << SDIO);
//	CTRLDDR |=  (1 << SDIO);
}

void sdioZ() //inline
{
	PIN_LOW(SDIO_1);
	PIN_IN(SDIO_1);
//	CTRLPORT &= ~(1 << SDIO);
//	CTRLDDR &= ~(1 << SDIO);
}



void sclkPulse()
{
	PIN_HIGH(SCLK);
	_delay_us(5);
	PIN_LOW(SCLK);
	_delay_us(5);
}

inline uint16_t parallelReadData()
{
	uint16_t result = ((DB_PIN1 & 0x0F) << 8) | DB_PIN0;
	return result;
}
*/
void spiWriteByte(TypeSPI2 SPIS, uint16_t addr, uint8_t val2wr);

/*
uint32_t readspi_AD(TypeSPI *SPI,uint8_t byte,uint8_t command,uint8_t mask);
void PINS_data_clk(TypeSPI *SPI,uint32_t ddata,uint16_t bytes); // set addres
uint32_t PINS_read_clk(TypeSPI *SPI,uint16_t bytes,uint8_t mask);
uint32_t PINS_data_clk_BI(TypeSPI *SPI,uint32_t ddata,uint16_t bytes);
*/
#endif /* H_SPI_H_ */
#endif /* SPI */
