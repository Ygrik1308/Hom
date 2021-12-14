///*
// * IS42S16100H_7TL.C
// *
// *  Created on: 20 мая. 2020 г.
// *      Author: Tarasov
// */
//
///* Includes ------------------------------------------------------------------*/

#include "main.h"

#if defined AD9764  // chip
#include "GPIO_ARM4.h"
#include "mathematics.h"
#include "AD9764.h"



//#define ddd(argument)  OUT(argument)
void INT_AD9764()
{
	PORT_OUT(GPIOD);
}





#endif
