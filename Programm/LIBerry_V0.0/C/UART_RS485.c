#include "main.h"
#if defined UART    // Controller

/////////////////////////////////////////////////////////////ID STM
/*	volatile uint32_t *UniqueID = (uint32_t *)0x1FFFF7E8;
	volatile uint32_t __UniqueID[3];
	__UniqueID[0] = UniqueID[0];
	__UniqueID[1] = UniqueID[1];
	__UniqueID[2] = UniqueID[2];
*/


/////////////////////////////////////////////////////////
int UART_Writ_Reed_255(int err)   // check channel 255 
{

	uint8_t d2=0;


	for(uint8_t d1=0; d1<255; d1++)  //1
	{

      // отослать данное назад
      while ((USART2->SR & USART_SR_TXE) == 0){}
      USART2->DR = d1;
      printf("Отправлено\n");



      // получить данное
      for(uint8_t k=0; k<20; k++)  //1
  	{
       if ((USART2->SR & USART_SR_RXNE) == 0){}
       d2 = USART2->DR;
       printf("Принято\n");
  	}


       if(d1!=d2)
       {
    	err=err+1;
       }

       if(d1==d2)
       {
	    HAL_Delay(40);
       }

	}

	   return err;
}

/////////////////////////////   // read channel 255 
int UART_Reed(uint8_t d2)  
{
    d2=0;
// получить данное
  for(uint8_t k=0; k<20; k++)  //1
	{
   if ((USART2->SR & USART_SR_RXNE) == 0){}
   d2 = USART2->DR;
	}
  return d2;
}

/////////////////////////////////////////////////
void UART_Write(uint16_t d1)
{
	/*
	for(uint8_t d1=0; d1<255; d1++)  //1
	{

      // отослать данное назад
      if ((USART2->SR & USART_SR_TXE) == 0){}
      USART2->DR = d1;
 //     printf("Отправлено\n");

	}

*/


	const int buffer_length = 7+1;
 	char str[buffer_length];
 	snprintf(str, buffer_length, "D- %.2X",d1); //2X


	// отослать данное назад
     if ((USART1->SR & USART_SR_TXE) == 0){}


//    for (unsigned int i=0;i<strlen(str);i++)
 //	  {
        USART1->DR = d1;  //d1
        printf("STR:%u;\n",d1);
    //    printf("Bad Blocks:%u:%u:%u=%u;\n",m,h,k,error);
// 	  }


}


/////////////////////////////////////////////////
void send_UART_485()
{
	Uart_485 datar =
	{
		.time=0x0000,
		.ID_address=0x10,
		.function_uart=request,
		.data_send={0x00,0x01,0x02,0x03,0x04,0x05,0x06},
	};

//	int send[7]={0x00,0x01,0x02,0x03,0x04,0x05,0x06};


 //HAL_GPIO_WritePin();
//	timing=0x0000;
/*	Uart_485.ID_address=0x10;
	function_485=2;
	int data[8]={0,1,2,3,4,5,6,7};
	int CRC_UART=data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7];
*/
	// data[0] == data + sizeof(int) * 0

	// отослать данное назад
     while ((USART2->SR & USART_SR_TXE) == 0){}
     USART2->DR = datar.time & datar.ID_address  & datar.function_uart;

}

void read_write_UART()
{
	if ((USART1->SR & USART_SR_RXNE) == 0) {}
	uint8_t d = USART1->DR;

	// отослать данное назад
	if ((USART1->SR & USART_SR_TXE) == 0) {}
	USART1->DR = d;
}


uint8_t read_UART(uint8_t d)
{
	if ((USART1->SR & USART_SR_RXNE) == 0) {}
     d = USART1->DR;

     if  ((USART1->SR & USART_SR_RXNE) == 0) {}
     USART1->DR = 59;

 	return d;
}


/*
/////////////////////////////////////////////////
void UART( )
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



#endif
