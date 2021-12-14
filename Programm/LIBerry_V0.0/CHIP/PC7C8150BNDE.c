///*
// * PC7C8150BNDE.c
// *
// *  Created on: 8 ???. 2020 ?.
// *      Author: user26
// */
//
///*
// * PIC8150BNDE.C
// *
// *  Created on: 8 ???. 2020 ?.
// *      Author: user26
// */

#include "main.h"
#if defined PIC8150BNDE

#include "PCI7C8150BNDE.h"

void _PCI_CLK()
{
	PIN_HIGH(CLK_PCI);
	PIN_LOW (CLK_PCI);

}


void IN_PORT()
{
for(uint8_t i=0;i<32;i++){PINS_OUT(data_PCI[i]);}  //data/addres  //data_D[i]);PINS_OUT(data_E[i])
for(uint8_t i=1;i<9;i++) {PINS_OUT(singl_PCI[i]);}  					 //PCI
for(uint8_t i=0;i<4;i++) {PINS_OUT(Comsnd_PCI[i]);}

PIN_IN(GNT);
jtag_init();

PIN_HIGH(FRAME);

}

void TEST_PCI()
{
//	   PINS_data(Comsnd_PCI,0x0,5);    //

	uint8_t df=100;
	PINS_data(Comsnd_PCI,Interrupt_Acknowledge,4);    //Send comand 0x00


	for(uint8_t i=0;i<5;i++)
	{
		_PCI_CLK();
		if (READ_PIN(GNT) == 0) // waiting for
		{
			goto m1;
		}
		fail_signal(GPIOA,LED1);
	}
 Alarm(GPIOA);

m1:	PIN_LOW(FRAME);
    _PCI_CLK();
   PINS_data(Comsnd_PCI,Interrupt_Acknowledge,4);    //Send comand 0x00
   PINS_data(data_PCI,0x0,32);   					 //ADDR
   _PCI_CLK();


/*
	while((READ_PIN(DEVSEL))!=0 | (++i<5)){_PCI_CLK();} //waiting for 0
	while((READ_PIN(IRDY))!=0   | (++i<5)){_PCI_CLK();} //waiting for 0
*/

}

#endif /* CHIP_PIC8150BNDE_PIC8150BNDE_H_ */
