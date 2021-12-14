#include "main.h"
/////////////////////////////////////////////
#if defined TEST_ADC    // chip
///////////////////////////////////////
#include "ADC_TEST.h"

uint32_t dT=255;
uint16_t INL_sr=255;
uint16_t INL[2]={255}; //INT(0)= min INT(1)= max
float LSB=3.3/(4096); //2^12  //double  //float
uint16_t _INL=0;
uint8_t ERrror_INL[34]={0};
uint16_t ideal_DAC[34]={0,124,248,372,496,621,745,869,993,1117,1241,1365,1489,1614,1738,1862,1986,
		                2110,2234,2358,2482,2607,2731,2855,2979,3103,3227,3351,3475,3600,3724,3848,
						3972,4096};
uint16_t INL_mas[1000]={0};
uint8_t INL_s[34]={0};


void ADC_ref(void)
{
	///////////////////////////////////////////////00
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,100);
		  dT=(uint32_t)HAL_ADC_GetValue(&hadc1); //мак 4029 -питание 4096 мак
		  INL[0]=dT;
		  INL[1]=dT;
	////////////////////////////////////////////////test int 255 paint
		  for(uint8_t i;i<255;i++)
		  {
		  	  HAL_ADC_Start(&hadc1);
		  	  HAL_ADC_PollForConversion(&hadc1,100);
		  	  dT=(uint32_t)HAL_ADC_GetValue(&hadc1); //мак 4029 -питание 4096 мак
		  	  if(dT<INL[0]){INL[0]=dT;}//min
		  	  if(dT>INL[1]){INL[1]=dT;}//max
		    //	  printf("ADC:=%u \n",dT);
		  }

		    INL_sr=(INL[1]+INL[0])/2;
		    printf("ADC_min:=%u \n",INL[0]);
		    printf("ADC_max:=%u \n",INL[1]);
		    printf("INL_ref:=%u \n",   4095-INL_sr);  //4095 max
		    printf("INL_ref:=%f \n\n",(4095-INL_sr)*LSB);  //4095 max
}

void ADC_test_paint_255_INL(uint16_t p,uint16_t h,LCD1602 scr)  //p-paint(255) h-delta = 0.1 -> (34)
{
 for(uint8_t b=0;b<h;b++)
 {
 HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
 HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,ideal_DAC[b]);
//////////////////////////////////////////////////////////
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1,100);
	  dT=(uint32_t)HAL_ADC_GetValue(&hadc1); //мак 4029 -питание 4096 мак
      INL[0]=dT;
      INL[1]=dT;
////////////////////////////////////////////////test int 255 paint
	  for(uint16_t i=0;i<p;i++)
	  {
	  	  HAL_ADC_Start(&hadc1);
	  	  HAL_ADC_PollForConversion(&hadc1,100);
	  	  dT=(uint32_t)HAL_ADC_GetValue(&hadc1); //мак 4029 -питание 4096 мак
	  	  if(dT<INL[0]){INL[0]=dT;}//min
	  	  if(dT>INL[1]){INL[1]=dT;}//max

	  	  INL_mas[i]=dT;
	    //	  printf("ADC:=%u \n",dT);
	  }
	  printf("ADC_mas:=%u\n",b);

    for(uint16_t i;i<p;i++)
    {
		printf("%u\n",INL_mas[i]);
    }
	    INL_sr=(INL[1]+INL[0])/2;
	    INL_s[b]=fabs(ideal_DAC[b]-INL_sr); //
/*
	    printf("ADC_min:=%u \n",INL[0]);
	    printf("ADC_max:=%u \n",INL[1]);
	//  printf("ADC_sr:=%u  \n",INL_sr);
        printf("ADC_ideal:=%u  \n",ideal_DAC[b]);

	    printf("INL:=%u \n\n", INL_s[b]);  //4095 max
//	    	    printf("INL(V):=%f \n\n",  (ideal_DAC[b]-INL_sr)*LSB);  //4095 max
*/

	    ERrror_INL[b]=INL_s[b];

	 	if(ERrror_INL[b]>_INL){_INL=ERrror_INL[b];}//min
		    HAL_Delay(100);
}
printf("ERrror_INL:\n");
for(uint8_t i=0;i<h;i++)
{
//		    printf("%u_%u\n",ideal_DAC[i],ERrror_INL[i]);
printf("%u\n",ERrror_INL[i]);

}
printf("\nINL:=%u \n",_INL);
moveXY(&scr,0,0);
lsd_print(&scr,"INL:");

writeLCD_2D(&scr,_INL);
Alarm(GPIOC);
}


void ADC1_Read() //PA0
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,100);
	dT=(uint32_t)HAL_ADC_GetValue(&hadc1); //мак 4029 -питание 4096 мак
	printf("ADC:=%u \n",dT);

	fail_signal(GPIOC,6);
}














#endif //FMS_ARM7
