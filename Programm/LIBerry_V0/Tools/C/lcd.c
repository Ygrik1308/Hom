#include "main.h"
/////////////////////////
#ifdef lcd
////////////////////////
#include "lcd.h"
#include "i2c.h"
//#include "ARM3_PLUS.h"

#define LCD_CLEARDISPLAY 0x01

I2C_HandleTypeDef hi2c1;


void lcd_ON(uint8_t ID,LCD_TYPE lCD) //20x4
{

	LCD1602 scr;

	scr.hi2c=&hi2c1;
	scr.DevAddress=ID<<1;//ID;
	scr.LCD_Type=lCD;//ID;

	initLCD(&scr);

   	moveXY(&scr,0,1);  //1-���������
   	lsd_print(&scr,"#1_45678912345678912");
   	moveXY(&scr,0,2);  //1-���������
   	lsd_print(&scr,"#2_45678912345678912");
   	moveXY(&scr,0,3);  //1-���������
   	lsd_print(&scr,"#3_45678912345678912");
   	moveXY(&scr,0,4);  //1-���������
   	lsd_print(&scr,"#4_45678912345678912");
    HAL_Delay(1550);
    printf("LSD initialization\n");
    HAL_Delay(1000);
    display_clear(&scr);
}
void lcd_ON_10(char *text,uint8_t in_lcd) //20x4
{
/*
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

*/
    if(in_lcd==1)
{
    LCD1602 scr;
 	scr.hi2c = &hi2c1;
	scr.DevAddress = (0x27<< 1);   // 0x27  // //LED1

	initLCD(&scr);

   	moveXY(&scr,0,0);  //1-���������
  	lsd_print(&scr,text);

   	moveXY(&scr,0,1);  //1-���������
  	lsd_print(&scr,"#2_45678912345678912");

 /*  	moveXY(&scr,0,2);  //1-���������
   	lsd_print(&scr,"#2_45678912345678912");
   	moveXY(&scr,0,3);  //1-���������
   	lsd_print(&scr,"#3_45678912345678912");
   	moveXY(&scr,0,4);  //1-���������
   	lsd_print(&scr,"#4_45678912345678912");
*/
    HAL_Delay(1550);
    printf("LSD initialization\n");
}

    else if(in_lcd==0)
  	     {
  	    	 printf("NO_LSD\n");
  	     }


    HAL_Delay(1000);
  //  display_clear(&scr);
}



void sendData(LCD1602 *scr , uint8_t *pData)
{
  *pData |= (1<<2);// ������������� ������������ ������ E � 1
  while(HAL_I2C_Master_Transmit(scr->hi2c,scr->DevAddress,pData,1,1000)!=HAL_OK)

  {}
  HAL_Delay(5); 
  *pData &=~(1<<2);// ������������� ������������ ������ E � 0
  while(HAL_I2C_Master_Transmit(scr->hi2c,scr->DevAddress,pData,1,1000)!=HAL_OK)
  {}
  HAL_Delay(5);
}
// initLCD ������� ��������� ������������� �������
// ��������� ���������� ������������� ������� ��� �������������� ���������� � ������������ � ���������� �� datasheet
//void initLCD(LCD1602 *scr)

void initLCD(LCD1602 *scr)
{
  uint8_t buf;
  buf = 0x30; // 0b00110000   Function set

  HAL_Delay(20);   //���� 15ms ���� ��������������� �������� ���������� (�������� ����� ��������� ����������)
  
  sendData(scr,&buf); //���������� ���� �����x buf
  sendData(scr,&buf); //��� ����
  sendData(scr,&buf); //� ������������ � ����������� �� ������������� �������
  
  buf = 0x20; // 0b00100000 ����� 4� ������� ����������
  sendData(scr,&buf);
  
  // ����� ��������� ����� ������� � ����� 0x00101000 (������ datasheet � �������)
  // ������� ������������ �� ��� ����, ��� ��� ������������� ���������
  buf = 0x20; //  0x20 � �������� ���� 0010 0000: 0010-������ �������� �������, 0000 - ������� rs,rw,e,led
  sendData(scr,&buf);
  buf = 0xC0; //1100 0000 N=1 ��� ������ F=1 (5*10), 0000 - ������� rs,rw,e,led  //0xC0  0x86
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
  
  //I/D - ��������� ����������� �������� ������� ����� ����� �������. (1 - �����, 0 - ������)
  //S - ����� ������� �������������� ������� ��������.
  buf = 0;
  sendData(scr,&buf);
  buf = 0x30;
  sendData(scr,&buf);
  
  //�������� �������
  buf =0;
  sendData(scr,&buf);
  buf = 0xC8;
  sendData(scr,&buf);
  
}
//writeLCD ������� ������ s �� ����� scr
void writeLCD(LCD1602 *scr, uint8_t s)
{
    uint8_t command;
    command = ((s&0xf0)|0x09);    //��������� ������� �������� � ������� ��� �������
    sendData(scr,&command);
    
    command = ((s&0x0f)<<4)|0x09; // ��������� ������ �������� � ������� ��� �������
    sendData(scr,&command);

}

//writeLCD ������� ������ s �� ����� scr
void writeLCD_DEC(LCD1602 *scr, uint8_t d)
{
	char str3[4];
	snprintf(str3,4, "%.3d",d);

   for (unsigned int i=0;i<strlen(str3);i++)
	  {
	  	  writeLCD(scr,str3[i]);
	  }
}

//writeLCD ������� ������ s �� ����� scr
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


//writeLCD ������� ������ s �� ����� scr
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


//writeLCD ������� ������ s 2 �����
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




//  moveXY ����������� ������ � ������� X, Y
void moveXY(LCD1602 *scr,uint8_t x,uint8_t y)  //uint8_t x, uint8_t y
{
	uint8_t command, adr;
	// �������� �� ������� �� x � y �� ������� ������������ ��������
	// � ������� ��� ������� �� 40 �������� � ������ �������� ��������

	if (x>scr->LCD_Type.x){ x = scr->LCD_Type.x;}  //39
	if (y>scr->LCD_Type.y){ y = scr->LCD_Type.y;}


	// ��������� ���������� x � y � ����� ������ DDRAM �������� ���������� � �������
/*
	if (y==1)
		adr = x;
	if (y==2)
		adr = x+0x28;			   //0x28   0x14+0x14   //x+0x28
	if (y==3)
		adr = x+0x14; 	   		//0x14  //x+0x14
	if (y==4)
		adr = x+0x14+0x14+0x14+0x14+4; //+0x40   //x+0x14+0x14+0x14+0x14+4
*/

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






	// ��� ��� ���������� ������������� ���������, ���������� ��� ������� ��� ����������� � ������ ������� DDRAM
	command = ((adr&0xf0)|0x80)|0x08; //adr&0xf0 �������� ������� �������, |0x80 ������������� ������� ��� � 1(DB7=1 �������� ����������)|0x08 ��������� 8(1000 - Led,E,Rw,Rs) � ������� �������
	sendData(scr,&command);

	command = (adr<<4)|0x08;
	sendData(scr,&command);

}
//m���������� ������� �� ���� ������� �����
void moveDisplayRight(LCD1602 *scr)
{
	uint8_t command;
	command = 0x18;
	sendData(scr,&command);

	command = 0xC8;
	sendData(scr,&command);
}
// ����� � ���� moveDispayLeft перемещает дисплей на одну позицию влево
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
#endif /* lsd */
