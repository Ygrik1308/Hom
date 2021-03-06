//********************************************************************
//
// Author        : ADI 
//
// Date          : December 2002
//
// File          : Adc832.c
//
// Hardware      : ADuC832
//
// Description   : This program demonstrates the SAR ADC functions. 
//	Software communicates with a terminal at 9600 baud. Program guides 
//	user through selection of options ending with a command list. Then 
//	continuous conversions are started and displayed. While measurements 
//	are output the user can issue single key commands to change settings. 
//	Also included are a help and wait option.
//		
//********************************************************************

//#include<ADuC832.h>		// SFR definition file.

#include"lib832.h"	//Function and variable declaration file.
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

void PrintHelp(void);

void adc832_INIT(void)
	{
	char 	c1;		    //Temporary variable.
	char	cXRef;		//External ref flag ('R' pressed).
	char	cGain;		//Gain calibration flag ('G' pressed).
	char	cSys;		//System calibration flag ('S' pressed).
	int	piV[14];	//Conversion results.

	cXRef = 0;

	UrtCfg(0x03,0x8508);	//UrtCfg configures UART.
	PllWcd(0);		        //PllWcd writes CD bits.
	printf("%04x \n",AdcRd());
	AdcCfg(0x80);
	AdcGet(0);

	PrintHelp();

	while(1)
		{
 /*
		if(UrtBsy()&1)		//If key pressed.
  			{	// Act on command.
  			while((c1 = _getkey())=='w');	//Wait if 'w'.
    			if(c1=='s' || c1=='S' || c1=='g' || c1=='G')
      				{	//Calibrate.
	    			if(c1=='s')		cSys = 0;      				
       				else if(c1=='S')	cSys = 1;      				
       				else if(c1=='g')	cGain = 0;      				
       				else if(c1=='G')	cGain = 1; 
       		     		AdcCal(4*cSys+2*cGain+1);
       	      			while(AdcBsy())	printf(".");
        		      	}
        	        if(c1=='r' || c1=='R')
        			{	
 	       			if(c1=='r')	cXRef = 0;
 	       			else	cXRef = 1;
	       		        AdcCfg(0x80+0x40*cXRef);
				}
			else if(c1=='h')	PrintHelp();
      			}
       		for(c1=0; c1<11;c1++)
 			{
   			if(c1==6)	c1 = 8;
   			AdcGo(c1,1);
     			while(AdcBsy())	printf(".");
			piV[c1] = AdcRd();     
			printf("%05d ",piV[c1]);
  			}
    		printf(" %c%c%c\n",cSys?'S':'s',cGain?'G':'g',
      			cXRef?'R':'r');
 */
   	}
}  //main

void PrintHelp(void)
	{
	printf("To change settings during conversions press one of:\n");
	printf("\t s for internal calibration.\n");
	printf("\t S for system calibration.\n");
	printf("\t g for zero calibration.\n");
	printf("\t G for gain calibration.\n");
	printf("\t r for internal reference.\n");
	printf("\t R for external reference.\n");
	printf("\t w to wait.\n");
	printf("\t h for this help screen.\n");
	printf("\tResults line will show 12 measured values in hex format\n");
	printf("\tplus  s or S, g or G and r or R depending on selection.\n");
	printf("Press a key to end help.\n\n");
	_getkey();
	}
