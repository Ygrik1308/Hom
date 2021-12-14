//////////////////////////////////////////
#include "main.h"
//////////////////////////////////////////
#if defined arm7
/////////////////////////////////////////
#include "NUCl_PIN.h"
Nucleo_pin init_nucleo()
{
	Nucleo_pin	p=
	{
////////////////////////////////////////////////X1.1
		.D0   ={GPIOD,14},  //PD14  D0
		.D1   ={GPIOD,15},  //PD15  D1
		.D2   ={GPIOD,0},	//PD0   D2
		.D3   ={GPIOD,1},	//PD1   D3
		.D4   ={GPIOE,7},	//PE7   D4
		.D5   ={GPIOE,8},	//PE8   D5
		.D6   ={GPIOE,9},   //PE9   D6
		.D7   ={GPIOE,10},  //PE10  D7
		.D8   ={GPIOE,11},  //PE11  D8
		.D9   ={GPIOE,12},  //PE12  D9
		.D10  ={GPIOE,13},  //PE13  D10
		.D11  ={GPIOE,14},  //PE14  D11
		.D12  ={GPIOE,15},  //PE15  D12
		.D13  ={GPIOD,8},	//PD8   D13
		.D14  ={GPIOD,9},	//PD9   D14
		.D15  ={GPIOD,10},  //PD10  D15
///////////////////////////////////////////////X1.2
		.D16  ={GPIOD,3},   //D16   PD3
		.D17  ={GPIOD,4},   //D17   PD4
		.D18  ={GPIOD,5},   //D18   PD5
		.D19  ={GPIOD,6},	//D19   PD6
		.D20  ={GPIOD,7},	//D20   PD7
		.D21  ={GPIOG,3},	//D21   PG3
		.D22  ={GPIOG,9},   //D22   PG9
		.D23  ={GPIOG,10},  //D23   PG10
		.D24  ={GPIOG,12},  //D24   PG12
		.D25  ={GPIOC,10},  //D25   PC10
		.D26  ={GPIOC,11},  //D26   PC11
		.D27  ={GPIOC,12},  //D27   PC12
		.D28  ={GPIOF,6},   //D28   PF6
		.D29  ={GPIOF,7},	//D29   PF7
		.D30  ={GPIOF,8},	//D30   PF8
		.D31  ={GPIOF,9},   //D31   PF9
/////////////////////////////////////////////////////X2
		.D32  ={GPIOF,0},   //D32  PF0 + 1
		.D33  ={GPIOF,1},   //D33  PF1 + 2
		.D34  ={GPIOF,2},   //D34  PF2 + 3
		.D35  ={GPIOF,3},	//D35  PF3 + 4
		.D36  ={GPIOF,4},	//D36  PF4 + 5
		.D37  ={GPIOF,5},	//D37  PF5 + 6
		.D38  ={GPIOF,12},  //D38  PF12 + 7
		.D39  ={GPIOG,2},   //D39  PG2  + 8 +
		.D40  ={GPIOF,14},  //D40  PF14 + 9 +
		.D41  ={GPIOF,13},  //D41  PF13 + 10 +
		.D42  ={GPIOF,15},  //D42  PF15 + 11 +
		.D43  ={GPIOG,0},   //D43  PG0  + 12 +
		.D44  ={GPIOA,4},   //D44  PA4  + 13
		.D45  ={GPIOG,1},	//D44  PG1  + 14 +
		.D46  ={GPIOE,1},	//D45  PE1  + 15
		.D47  ={GPIOE,0},   //D46  PE0  + 16

		.Data_X1={p.D0,p.D1,p.D2,p.D3,p.D4,p.D5,p.D6,p.D7,p.D8,p.D9,p.D10,p.D11,p.D12,p.D13,p.D14,p.D15},
		.Data_X2={p.D16,p.D17,p.D18,p.D19,p.D20,p.D21,p.D22,p.D23,p.D24,p.D25,p.D26,p.D27,p.D28,p.D29,p.D30,p.D31},
		.Data_X3={p.D32,p.D33,p.D34,p.D35,p.D36,p.D37,p.D38,p.D39,p.D40,p.D41,p.D42,p.D43,p.D44,p.D45,p.D46,p.D47},


	};


	for(uint32_t i=0;i<16;i++){PINS_OUT(p.Data_X1[i]);}        // 16
	for(uint32_t i=0;i<16;i++){PINS_OUT(p.Data_X2[i]);}        // 16
	for(uint32_t i=0;i<16;i++){PINS_OUT(p.Data_X3[i]);}        // 16

return p;
}

#endif  //arm7
//Address_type create_address( uint16_t die,                 //0-1
//							 uint16_t plane,			   //0-1
//							 uint16_t block,               //2048
//							 uint16_t page,                //128
//							 uint16_t colum )              //1024 - data + 64 -  ,4095
//{
//
////	  HAL_Delay(100);
//  Address_type at = {
//		.one_addr1 		= colum & 0xff,                                   //++
//		.two_addr2 		= ((( colum >> 8 ) & 0xff) |(0>>7)|(0>>6)|(0>>5)),                          //++
//		.three_addr3    = (( plane & 0x01 ) << 7)  | (page & 0x127),    //
//		.four_addr4     = ( block  & 0xff ),
//		.five_addr5     = (( block >> 8 ) & 0x07 ) | (( die & 0x01 ) << 3 )  //9
//	};
//  return at;
//
//}
