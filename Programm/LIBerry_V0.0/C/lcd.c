#include "main.h"
#ifdef disply//HAL_I2C_MODULE_ENABLED

#include "lcd.h"
#define LCD_CLEARDISPLAY 0x01

// sendData  i2c
// pData -
uint8_t sendData(LCD1602 *scr , uint8_t *pData)
{
  uint8_t Error=0;
  *pData |= (1<<2);//
  while(HAL_I2C_Master_Transmit(scr->hi2c,scr->DevAddress,pData,1,1000)!=HAL_OK) //scr->DevAddress
  {Error=Error+1;}

  HAL_Delay(5); 
  *pData &=~(1<<2);//
  while(HAL_I2C_Master_Transmit(scr->hi2c,scr->DevAddress,pData,1,1000)!=HAL_OK)
  {Error=Error+1;}
  HAL_Delay(5);

  return  Error;
}
// initLCD
//void initLCD(LCD1602 *scr)


void initLCD(LCD1602 *scr)
{
  uint8_t buf;
  uint8_t error;

  buf = 0x30; // 0b00110000   !!0x30

  HAL_Delay(20);   // 15ms
  
  sendData(scr,&buf); // buf
  sendData(scr,&buf); // 
  sendData(scr,&buf); //
  
  buf = 0x20; // 0b00100000
  sendData(scr,&buf);
  

  buf = 0x20; //  0x20  rs,rw,e,led
  sendData(scr,&buf);
  buf = 0x3f;               //0xC0; //1100 0000 N=1 rs,rw,e,led
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
  
  //I/D -
  //S -
  buf = 0;
  sendData(scr,&buf);
  buf = 0x30;
  sendData(scr,&buf);
  
  //
  buf =0;
  sendData(scr,&buf);
  buf = 0xC8;
  sendData(scr,&buf);
  


}
//writeLCD­ scr
void writeLCD(LCD1602 *scr, uint8_t s)
{
    uint8_t command;
    command = ((s&0xf0)|0x09);    //
    sendData(scr,&command);
    
    command = ((s&0x0f)<<4)|0x09; //
    sendData(scr,&command);

}

//writeLCD­ scr
void writeLCD_DEC(LCD1602 *scr, uint8_t d,uint8_t LED)
{
	char str3[4];
	snprintf(str3,LED, "%.2d",d);

   for (unsigned int i=0;i<strlen(str3);i++)
	  {
	  	  writeLCD(scr,str3[i]);
	  }
//   if(d==0);
   {lsd_print(scr,"0"); }//
}



//writeLCD  scr
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



//writeLCD ­ scr
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


//writeLCD ­ scr
void writeLCD_H(LCD1602 *scr, uint8_t d)  // t =  number of bytes
{
	//char str3[5];

	const int buffer_length = 4+1;   // 4
	char str[buffer_length];

	snprintf(str, buffer_length, "%.2X",d); //2X  4

   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}
void writeLCD_4D(LCD1602 *scr, uint16_t d)  // t =  number of bytes uint8_t
{
	//char str3[5];

	const int buffer_length = 6+1;   // 4
	char str[buffer_length];

	snprintf(str, buffer_length, "%.4d",d); //2X  4

   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}

void writeLCD_2D(LCD1602 *scr, uint16_t d)  // t =  number of bytes uint8_t
{
	//char str3[5];

	const int buffer_length = 4+1;   // 4
	char str[buffer_length];

	snprintf(str, buffer_length, "%.2d",d); //2X  4

   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}

void writeLCD_2D_float(LCD1602 *scr, float d)  // t =  number of bytes uint8_t
{
	//char str3[5];

	const int buffer_length = 5+5;   // 4+1
	char str[buffer_length];

	snprintf(str, buffer_length, "%.5f",d); //2X  4

   for (unsigned int i=0;i<strlen(str);i++)
	  {
	  	  writeLCD(scr,str[i]);
	  }
}



//writeLCD  
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




//  moveXY  X, Y
void moveXY(LCD1602 *scr,uint8_t x, uint8_t y)
{
	uint8_t command, adr;
	//
	//
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
//




	//  DDRAM
	command = ((adr&0xf0)|0x80)|0x08; //adr&0xf0
	sendData(scr,&command);

	command = (adr<<4)|0x08;
	sendData(scr,&command);

}
//
void moveDisplayRight(LCD1602 *scr)
{
	uint8_t command;
	command = 0x18;
	sendData(scr,&command);

	command = 0xC8;
	sendData(scr,&command);
}
//
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
////////////////////////////////////////////*
uint8_t TEST(LCD1602 *scr,char *text,uint8_t in_lcd)     /// Test All System
{
	uint8_t Error_All = 2;
	 system_GPIO();
//    PIN_OUT(GPIOC,6);
//    PIN_OUT(GPIOC,7);
   ///////////////////////////////// TEST
 //   if ((Error_All=GPIO_TEST())!= 0x03) Alarm(GPIOA);   //GPIO C,D,E
    ///////////////////////////////// LSD INIT
     if(in_lcd==1)
{
    initLCD(scr);
    moveXY(scr,0,0);
    lsd_print(scr,text);
    HAL_Delay(1550);
//    display_clear(scr);
    printf("LSD initialization\n");
}
     else if(in_lcd==0)
     {
    	 printf("NO_LSD\n");
     }
     return Error_All;
}


GPIO df=
{
 .A=GPIOD,
 .P=6,
};






#endif /* HAL_I2C_MODULE_ENABLED */
