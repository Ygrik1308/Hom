/*
 * PIC8150BNDE.h
 *
 *  Created on: 8 ???. 2020 ?.
 *      Author: user26
 */

//GPIO Singl_A[14]={GPIOA,0, GPIOA,1, GPIOA,2, GPIOA,3,   GPIOA,4, GPIOA,5,   reserv,   reserv,   GPIOA,8, reserv, reserv,    GPIOA,11, GPIOA,12, reserv,   reserv,    GPIOA,15};    //     //9_PIN
//														  LED1    LED2                  UART_TX   UART_RX                     Jtag_TMS  Jtag_TCK
//
//
//GPIO Singl_B[14]={GPIOB,0, GPIOB,1, reserv,  reserv,   GPIOB,4, GPIOB,5,   reserv,   reserv,   GPIOB,8, GPIOB,9,	GPIOB,10, GPIOB,11,	GPIOB,12, GPIOB,13, GPIOB,14,  GPIOB,15};       //										                                           //13_PIN
//		            IRDY     TRDY     BOOT1    Jtag_TDO     ?     CBE3       I2C1_SDL  I2C1_SDA  GNT      REQ 	    FRAME     CBE0      CBE1      CBE2	    CLK_PCI	   DEVSEL
//
//
//GPIO Singl_C[13]={GPIOC,0,  		//TRST         //11_PIN
//		          GPIOC,1,   		//TCK
//				  GPIOC,2,   		//TMS
//				  GPIOC,3,   		//TDI
//				  GPIOC,4,   		//TDO
//			      GPIOC,5,
//			      GPIOC,6,
//			      GPIOC,7,
//			      GPIOC,8,
//			      GPIOC,9,
//				  reserv,		  //SPI3_SCK
//				  reserv,		  //SPI3_MISO
//				  reserv,		  //SPI3_MOSI
//				  GPIOC,13};      //
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// data /Address
//GPIO data_D[15] ={GPIOD,0,       // d0 16_pin
//			      GPIOD,1,
//			      GPIOD,2,
//			      GPIOD,3,
//			      GPIOD,4,
//			      GPIOD,5,
//			      GPIOD,6,
//			      GPIOD,7,
//			      GPIOD,8,
//			      GPIOD,9,
//			      GPIOD,10,
//			      GPIOD,11,
//			      GPIOD,12,
//			      GPIOD,13,
//			      GPIOD,14,
//			      GPIOD,15};  // d15
//
//GPIO data_E[15] ={GPIOE,0,   // d0 16_pin
//			      GPIOE,1,
//			      GPIOE,2,
//			      GPIOE,3,
//			      GPIOE,4,
//			      GPIOE,5,
//			      GPIOE,6,
//			      GPIOE,7,
//			      GPIOE,8,
//		          GPIOE,9,
//		   	      GPIOE,10,
//			      GPIOE,11,
//			      GPIOE,12,
//			      GPIOE,13,
//			      GPIOE,14,
//			      GPIOE,15};  // d15

//



#include "main.h"
#if defined PIC8150BNDE

#ifndef _PCI7C8150BNDE_H_
#define _PCI7C8150BNDE_H_


//#define ddd(argument)  OUT(argument)




//////////////////////////////////////////////////Standart
 #define reserv 0,0

 #define UART_TX GPIOA,9
 #define UART_RX GPIOA,10

 //#define LED1 GPIOA,6
 //#define LED2 GPIOA,7


 #define Jtag_TMS GPIOA,13
 #define Jtag_TCK GPIOA,14
 #define Jtag_TDO GPIOB,3

 #define SPI3_SCK  GPIOC,10
 #define SPI3_MISO GPIOC,11
 #define SPI3_MOSI GPIOC,12


#define I2C1_SDL GPIOB,6
#define I2C1_SDA GPIOB,7
/////////////////////////////////////////////////Standart

//////////////////////////////////////////////////PCI
#define REQ      GPIOB,8  //0 + OUT
#define GNT      GPIOB,9  //1 + IN pull-up resistor 10k

#define FRAME    GPIOB,10  //2
#define CBE0     GPIOB,11  //3 green
#define CBE1     GPIOB,12  //4 BLuE
#define CBE2     GPIOB,13  //4 Violet
#define CBE3     GPIOB,5   //4 Red

#define CLK_PCI  GPIOB,14  //4 +

#define IRDY     GPIOB,0
#define TRDY     GPIOB,1
#define DEVSEL   GPIOB,2


//////////////////////////////////////////////////
enum
{
// (Commands)
	Interrupt_Acknowledge = 0, 		//
	Special_Cycle = 1, 		//
	I_O_Read  = 4,
	I_O_Write = 3,
};



GPIO data_PCI[32]={GPIOD,0, GPIOD,1, GPIOD,2, GPIOD,3, GPIOD,4, GPIOD,5, GPIOD,6, GPIOD,7, GPIOD,8, GPIOD,9, GPIOD,10, GPIOD,11, GPIOD,12, GPIOD,13, GPIOD,14, GPIOD,15, GPIOE,0, GPIOE,1, GPIOE,2, GPIOE,3, GPIOE,4, GPIOE,5, GPIOE,6, GPIOE,7, GPIOE,8, GPIOE,9, GPIOE,10, GPIOE,11, GPIOE,12, GPIOE,13, GPIOE,14, GPIOE,15 };
GPIO singl_PCI[]= {GNT,REQ,FRAME,CBE0,CBE1,CBE2,IRDY,TRDY,CLK_PCI};
GPIO Comsnd_PCI[]={CBE0,CBE1,CBE2,CBE3};

//////////////////////////////////////////////////PCI


void PCI_CLK();
void TEST_PCI();





#endif /* CHIP_PIC8150BNDE_PIC8150BNDE_H_ */
#endif /* CHIP_PIC8150BNDE_PIC8150BNDE_H_ */

//#endif /* CHIP_PIC8150BNDE_PIC8150BNDE_H_ */
