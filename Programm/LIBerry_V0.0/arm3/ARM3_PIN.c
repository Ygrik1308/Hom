#include "main.h"
////////////////////////////////////////////
#if defined arm3    // Controller
///////////////////////////////////////////
#include "ARM3_PIN.h"
ARM3_pin init_ARM3()
{
	ARM3_pin	p=
	{
////////////////////////////////////////////////X1
		.D0   ={GPIOC,1},  //1
		.D1   ={GPIOC,0},  //2
		.D2   ={GPIOC,3},  //3
		.D3   ={GPIOC,2},  //4
		.D4   ={GPIOC,5},  //5
		.D5   ={GPIOC,4},  //6
		.D6   ={GPIOC,7},  //7
		.D7   ={GPIOC,6},  //8
		.D8   ={GPIOC,9},  //9
		.D9   ={GPIOC,8},  //10
		.D10  ={GPIOC,11}, //11
		.D11  ={GPIOC,10}, //12
		.D12  ={GPIOD,0},  //13
		.D13  ={GPIOE,6},  //14
		.D14  ={GPIOB,1},  //15
		.D15  ={GPIOB,0},  //16
///////////////////////////////////////////////X2
		.D16  ={GPIOE,7},   //1
		.D17  ={GPIOD,7},   //2
		.D18  ={GPIOB,5},   //3
		.D19  ={GPIOB,4},	//4
		.D20  ={GPIOB,7},	//5		//SDA
		.D21  ={GPIOB,6},	//6     //SCL
		.D22  ={GPIOB,9},   //7
		.D23  ={GPIOB,8},   //8
		.D24  ={GPIOB,11},   //9
		.D25  ={GPIOB,10},  //10
		.D26  ={GPIOB,13},  //11
		.D27  ={GPIOB,12},  //12
		.D28  ={GPIOB,15},  //13
		.D29  ={GPIOB,14},	//14
		.D30  ={GPIOD,14},	//15  ??
		.D31  ={GPIOD,15},  //16  ??
///////////////////////////////////////////////X3
		.D32  ={GPIOE,1},   //1
		.D33  ={GPIOE,0},   //2
		.D34  ={GPIOE,3},   //3  - 5
		.D35  ={GPIOE,2},	//4
		.D36  ={GPIOE,5},	//5
		.D37  ={GPIOE,4},	//6
		.D38  ={GPIOC,13},  //7
		.D39  ={GPIOB,2},   //8
		.D40  ={GPIOE,9},  //9
		.D41  ={GPIOE,8},  //10
		.D42  ={GPIOE,11},  //11
		.D43  ={GPIOE,10},  //12  ??
		.D44  ={GPIOE,13},  //13  ??
 		.D45  ={GPIOE,12},	//14  ??
		.D46  ={GPIOE,15},	//15  ??
		.D47  ={GPIOE,14},  //16  ??

		.led_0    = {GPIOD,9},
		.led_GND0 = {GPIOD,8},

		.Data_X1={p.D0,p.D1,p.D2,p.D3,p.D4,p.D5,p.D6,p.D7,p.D8,p.D9,p.D10,p.D11,p.D12,p.D13,p.D14,p.D15},
		.Data_X2={p.D16,p.D17,p.D18,p.D19,p.D20,p.D21,p.D22,p.D23,p.D24,p.D25,p.D26,p.D27,p.D28,p.D29,p.D30,p.D31},
		.Data_X3={p.D32,p.D33,p.D34,p.D35,p.D36,p.D37,p.D38,p.D39,p.D40,p.D41,p.D42,p.D43,p.D44,p.D45,p.D46,p.D47},
	};

return p;
}

void OUT_ARM3(ARM3_pin p)
{
for(uint32_t i=0;i<16;i++){PINS_OUT(p.Data_X1[i]);}        // 16
for(uint32_t i=0;i<16;i++){PINS_OUT(p.Data_X2[i]);}        // 16
for(uint32_t i=0;i<16;i++){PINS_OUT(p.Data_X3[i]);}        // 16
}

#endif  //Arm3
