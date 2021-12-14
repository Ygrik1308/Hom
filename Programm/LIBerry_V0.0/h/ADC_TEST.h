/*
 * ADC_TEST.h
 *
 *  Created on: 14 дек. 2021 г.
 *      Author: HP
 */
#include "main.h"
/////////////////////////////////////////////
#if defined TEST_ADC    // chip
///////////////////////////////////////
ADC_HandleTypeDef hadc1;
DAC_HandleTypeDef hdac;
LCD1602 scr;

void ADC_ref(void);
void ADC_test_paint_255_INL(uint16_t p,uint16_t h,LCD1602 scr);
void ADC1_Read(); //PA0

#endif //FMS_ARM7
