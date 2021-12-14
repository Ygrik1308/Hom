#include "main.h"
////////////////////////////////////////////
#if defined arm3    // Controller
///////////////////////////////////////////
#ifndef H_ARM3_PIN_H_
#define H_ARM3_PIN_H_


typedef struct
{
////////////////////////////////////////////X1
	GPIO D0;
	GPIO D1;
	GPIO D2;
	GPIO D3;
	GPIO D4;
	GPIO D5;
	GPIO D6;
	GPIO D7;
	GPIO D8;
	GPIO D9;
	GPIO D10;
	GPIO D11;
	GPIO D12;
	GPIO D13;
	GPIO D14;
	GPIO D15;
//////////////////////////////////////////////X2
	GPIO D16;
	GPIO D17;
	GPIO D18;
	GPIO D19;
	GPIO D20;
	GPIO D21;
	GPIO D22;
	GPIO D23;
	GPIO D24;
	GPIO D25;
	GPIO D26;
	GPIO D27;
	GPIO D28;
	GPIO D29;
	GPIO D30;
	GPIO D31;
//////////////////////////////////////////////X3
	GPIO D32;
	GPIO D33;
	GPIO D34;
	GPIO D35;
	GPIO D36;
	GPIO D37;
	GPIO D38;
	GPIO D39;
	GPIO D40;
	GPIO D41;
	GPIO D42;
	GPIO D43;
	GPIO D44;
	GPIO D45;
	GPIO D46;
	GPIO D47;
///////////////////////////////////////////////X4
	GPIO Data_X1[16];
	GPIO Data_X2[16];
	GPIO Data_X3[16];
///////////////////////////////////////////////LCD
	GPIO led_0;
	GPIO led_GND0;

}ARM3_pin;

ARM3_pin init_ARM3();



#endif /* H_ARM3_PIN_H_ */

#endif  //Arm3
