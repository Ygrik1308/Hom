/*
 * CFile1.c
 *
 * Created: 22.11.2020 16:55:31
 *  Author: HP
 */ 
#include "main.h"
#include "Print.h"

#ifndef LCD_I2CH_
#define LCD_I2CH_

enum SPICEMODES
{
// commands
 LCD_CLEARDISPLAY   = 0x01,
 LCD_RETURNHOME     = 0x02,
 LCD_ENTRYMODESET   = 0x04,
 LCD_DISPLAYCONTROL = 0x08,
 LCD_CURSORSHIFT    = 0x10,
 LCD_FUNCTIONSET    = 0x20,
 LCD_SETCGRAMADDR   = 0x40,
 LCD_SETDDRAMADDR   = 0x80
};

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit


void LCD_ini2(void);

class LCD_I2C : public Print
{
	public:
		LCD_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
		void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
		void clear();
		void home();
		void noDisplay();
		void display();
		void noBlink();
		void blink();
		void noCursor();
		void cursor();
		void scrollDisplayLeft();
		void scrollDisplayRight();
		void printLeft();
		void printRight();
		void leftToRight();
		void rightToLeft();
		void shiftIncrement();
		void shiftDecrement();
		void noBacklight();
		void backlight();
		void autoscroll();
		void noAutoscroll();
		void createChar(uint8_t, uint8_t[]);
		void createChar(uint8_t location, const char *charmap);
	// Example: 	const char bell[8] PROGMEM = {B00100,B01110,B01110,B01110,B11111,B00000,B00100,B00000};

		void setCursor(uint8_t, uint8_t);
//	virtual void write(uint8_t);
		void command(uint8_t);
		void init();
		void oled_init();

	////compatibility API function aliases
		void blink_on();						// alias for blink()
		void blink_off();       					// alias for noBlink()
		void cursor_on();      	 					// alias for cursor()
		void cursor_off();      					// alias for noCursor()
		void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
		void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
		void printstr(const char[]);

	////Unsupported API functions (not implemented in this library)
		uint8_t status();
		void setContrast(uint8_t new_val);
		uint8_t keypad();
		void setDelay(int,int);
		void on();
		void off();
		uint8_t init_bargraph(uint8_t graphtype);
		void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
		void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);

	private:

		void init_priv();
		void send(uint8_t, uint8_t);
		void write4bits(uint8_t);
		void expanderWrite(uint8_t);
		void pulseEnable(uint8_t);
		uint8_t _Addr;
		uint8_t _displayfunction;
		uint8_t _displaycontrol;
		uint8_t _displaymode;
		uint8_t _numlines;
		bool _oled = false;
		uint8_t _cols;
		uint8_t _rows;
		uint8_t _backlightval;
};




////class LCD_I2C_Cristal
////{
////	private:
////
////		uint8_t _Addr;
////		uint8_t _cols;
////		uint8_t _rows;
////		uint8_t _backlightval;
////		uint8_t _oled = false;
////
////	public:
////
////
////	void LCD_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
////		{
////		_Addr = lcd_Addr;
////		_cols = lcd_cols;
////		_rows = lcd_rows;
////		_backlightval = LCD_NOBACKLIGHT;
////		}
////
////
////
////	void oled_init()
////	{
////		_oled = true;
////		init_priv();
////	}
////
////	void init_priv()
////	{
////		begin();
////
//////	Wire.begin();
////
//////	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
//////	begin(_cols, _rows);
////}
////
////
////	void begin(uint8_t cols, uint8_t lines, uint8_t dotsize)
////	{
////		if (lines > 1)
////		{
////			_displayfunction |= LCD_2LINE;
////		}
////		_numlines = lines;
////
////	// for some 1 line displays you can select a 10 pixel high font
////	if ((dotsize != 0) && (lines == 1))
////	{
////		_displayfunction |= LCD_5x10DOTS;
////	}
////
////	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
////	// according to datasheet, we need at least 40ms after power rises above 2.7V
////	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
////	_delay_ms(50);
////	// Now we pull both RS and R/W low to begin commands
////	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
////	_delay_ms(1000);
//////
//////  	//put the LCD into 4 bit mode
//////	// this is according to the hitachi HD44780 datasheet
////	// figure 24, pg 46
////
////	  // we start in 8bit mode, try to set 4 bit mode
////   write4bits(0x03 << 4);
////
////   _delay_us(4500);
//// //  delayMicroseconds(4500); // wait min 4.1ms
////
////   // second try
////   write4bits(0x03 << 4);
////   _delay_us(4500);
//// //  delayMicroseconds(4500); // wait min 4.1ms
////
////   // third go!
////   write4bits(0x03 << 4);
////   _delay_us(150);
//////   delayMicroseconds(150);
////
////   // finally, set to 4-bit interface
////   write4bits(0x02 << 4);
////
////
////	// set # lines, font size, etc.
////	command(LCD_FUNCTIONSET | _displayfunction);
////
////	// turn the display on with no cursor or blinking default
////	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
////	display();
////
////	// clear it off
////	clear();
////
////	// Initialize to default text direction (for roman languages)
////	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
////
////	// set the entry mode
////	command(LCD_ENTRYMODESET | _displaymode);
////
////	home();
//
//}
//
//
//};




/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//LCD_I2C::LCD_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
//{
//	_Addr = lcd_Addr;
//	_cols = lcd_cols;
//	_rows = lcd_rows;
//	_backlightval = LCD_NOBACKLIGHT;
//}





#endif /* LCD_H_ */
