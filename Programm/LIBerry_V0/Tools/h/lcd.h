#include "main.h"
///////////////////
#ifdef lcd
#include "i2c.h"
///////////////////
//#include "main.h"
#ifndef _LCD_H
#define _LCD_H


typedef struct
{
	uint8_t  x;  //Length
	uint8_t  y;  //Line
}LCD_TYPE;

typedef struct
{
	I2C_HandleTypeDef *hi2c; //*hi2c
    uint16_t DevAddress;
    LCD_TYPE LCD_Type;
}LCD1602;


struct LCD16020
{
	I2C_HandleTypeDef *hi2c; //*hi2c
    uint16_t DevAddress;
};


extern  struct LCD16020 scr;



// scr.DevAddress = (0x3F<<1);   // 0x27  // //LED1


  void lcd_ON(uint8_t ID,LCD_TYPE lCD);
  void lcd_ON_10(char *text,uint8_t in_lcd);
  //void lcd_ON_10(LCD1602 *scr);
  void initLCD(LCD1602 *scr); //РёРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РґРёСЃРїР»РµСЏ
  void sendData(LCD1602 *scr , uint8_t *pData); //РѕС‚РїСЂР°РІРєР° РєРѕРјР°РЅРґС‹ РїРѕ С‡РµС‚С‹СЂРµС…Р±РёС‚РЅРѕРјСѓ РёРЅС‚РµСЂС„РµР№СЃСѓ


  void writeLCD(LCD1602 *scr, uint8_t s);// РІС‹РІРѕРґ СЃРёРјРІРѕР»Р° s РЅР° РґРёСЃРїР»РµР№
  void lsd_print(LCD1602 *scr,char *str);// РІС‹РІРѕРґ СЃС‚СЂРѕРєРё str РЅР° РґРёСЃРїР»РµР№

  void moveXY(LCD1602 *scr,uint8_t x,uint8_t y); // каретка на X, Y
  void moveDisplayRight(LCD1602 *scr); //сдвиг вправо двух линий
  void moveDisplayLeft(LCD1602 *scr); //сдвиг влево двух линий
  void display_clear(LCD1602 *scr);  // очистка дисплея
  void display_OFF(LCD1602 *scr);    //  выключение подсветки
  void display_ON(LCD1602 *scr);     //  включение подсветки
  void writeLCD_DEC(LCD1602 *scr, uint8_t s); //вывод в DEC
  void writeLCD_HEX(LCD1602 *scr, uint8_t s); //вывод в DEC
  void writeLCD_16_HEX(LCD1602 *scr, uint16_t s); //вывод в DEC

  void writeLCD_2HEX(LCD1602 *scr, uint32_t d); // вывод 2 байта в HEX

  void writeStringLCDww();

  #endif /* LED_H */
#endif /* lsd */
