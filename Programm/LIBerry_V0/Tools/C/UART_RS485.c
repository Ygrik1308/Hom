#include "main.h"
/////////////////////////
#ifdef uart
////////////////////////
#include "UART_RS485.h"
/////////////////////////////////////////////////////////////ID STM
/////////////////////////////////////////////////////////
int UART_Writ_Reed_255(int err,USART_TypeDef *USARTX)   // check channel 255
{

	uint8_t d2=0;

/*
	for(uint8_t d1=1; d1<255; d1++)  //1
	{

      // отослать данное назад
      while ((USARTX->SR & USART_SR_TXE) == 0){}
      USART2->DR = d1;
      printf("Отправлено\n");


//	     uint8_t d1=0x31;
//	     if ((USART2->SR & USART_SR_TXE) == 0) {}
//	     USART2->DR = d1;

*/




      // получить данное
      for(uint8_t k=0; k<2; k++)  //1
  	{
       if ((USARTX->SR & USART_SR_RXNE) == 0){}
       d2 = USARTX->DR;
     //  printf("Принято\n");
       printf("Read: %d\n", d2);
  	}

/*
       if(d1!=d2)
       {
    	err=err+1;
       }

       if(d1==d2)
       {
	    HAL_Delay(40);
       }

	}
*/
	   return err;
}

/////////////////////////////   // read channel 255 
int UART_Reed(uint8_t d2)  
{
    d2=0;
// получить данное
//  for(uint8_t k=0; k<20; k++)  //1
//	{
    if ((USART1->SR & USART_SR_RXNE) == 0) {}
    uint8_t d = USART1->DR;
//   if ((USART2->SR & USART_SR_RXNE) == 0){}
//   d2 = USART2->DR;
//	}
  return d2;
}

/////////////////////////////////////////////////
void UART_Write(uint8_t d1)
{
// 	const int buffer_length = 7+1;
// 	char str[buffer_length];
// 	snprintf(str, buffer_length, "0x%.4X",d1); //2X


	// отослать данное назад
//     while ((USART1->SR & USART_SR_TXE) == 0)
//     {USART1->DR=d1;}

     while ((USART1->SR & USART_SR_TXE) == 0) {}
     USART1->DR = d1;


//    for (unsigned int i=0;i<strlen(str);i++)
// 	  {
//        USART1->DR = str[i];  //d1
// 	  }
}


/////////////////////////////////////////////////
void send_UART_485(Uart_485 datar)
{

//	Uart_485 d;
//	d.ID_address=0x05;
//	d.function_uart=request
//    uint8_t ID_address;
//    uint8_t function_uart;
//	int data_send[7];  //  doubleuint16_t timing;  //
//    uint16_t CRC_UART;
//    uint16_t time;
//	int send[7]={0x00,0x01,0x02,0x03,0x04,0x05,0x06};


 //HAL_GPIO_WritePin();
//	timing=0x0000;
	int data[7]={0,1,2,3,4,5,6,7};


/*
	uart.ID_address=0x10;
	uart.CRC_UART=0;
	uart.function_uart=0;
//	uart.data_send = data;
	uart.time=0;
*/

//	int CRC_UART=data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7];

	// data[0] == data + sizeof(int) * 0

	// отослать данное назад
     while ((USART2->SR & USART_SR_TXE) == 0){}
     USART2->DR = datar.ID_address & datar.time & datar.function_uart;

}

void read_write_UART()
{
	if ((USART1->SR & USART_SR_RXNE) == 0) {}
	uint8_t d = USART1->DR;

	// отослать данное назад
	if ((USART1->SR & USART_SR_TXE) == 0) {}
	USART1->DR = d;
}
/*
/////////////////////////////////////////////////
void send__read_UART( )
{// получить данное

if ((USART1->SR & USART_SR_RXNE) == 0) {}
uint8_t d = USART1->DR;

// отослать данное назад
if ((USART1->SR & USART_SR_TXE) == 0) {}
USART1->DR = d;

		moveXY(&scr,6,0);
		writeLCD_DEC(&scr,d);
		f1(0x0000, 0x00);
		d=100;
		break;
	case '2':    //2   250 МГЦ
		moveXY(&scr,6,0);
		writeLCD_DEC(&scr,d);
//		f2();
		d=100;
		break;
	case '3':    // 3 // 100
		moveXY(&scr,6,0);
		writeLCD_DEC(&scr,d);
		d=100;
		break;
	case '4':    // 4 //	   // 750
		moveXY(&scr,6,0);
		writeLCD_DEC(&scr,d);
		d=100;
		break;
	case '5':    // 5 // MUX to OUT
		moveXY(&scr,6,0);
		writeLCD_DEC(&scr,d);
		d=100;
		break;
	case '6':    // 6 // REGISTER READ
	{
		moveXY(&scr,5,1);
		//	writeLCD_DEC(&scr,error);   //reverse_8
		d=100;
	}break;
	case '7':    // 7 // REGISTER send
		moveXY(&scr,6,0);
		writeLCD_DEC(&scr,d);
		d=100;
		break;
	case '0':    // 0
		moveXY(&scr,6,0);
		lsd_print(&scr,"RM0");
		d=100;
		//	 	default:
		break;
	} //SWiTH
}

*/
#endif /* uart_rs485 */
