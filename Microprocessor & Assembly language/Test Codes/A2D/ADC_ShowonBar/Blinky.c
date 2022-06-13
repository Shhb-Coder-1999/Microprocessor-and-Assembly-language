/******************************************************************************/
/* Blinky.c: LED Flasher and graphic demo                                     */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "stdlib.h"
#include "GLCD.h"


int main (void) {                       /* Main Program                       */

	char snum[10];
	unsigned int i;

  SystemInit();
//  SysTick_Config(25000000/100);  /* Generate interrupt every 10 ms     */

  GLCD_Init   ();
  GLCD_Clear  (White);
	GLCD_SetTextColor (Yellow);
	GLCD_SetBackColor (Black);
//	GLCD_DisplayString (2,2,"Laki");
	
	LPC_PINCON->PINSEL3= (0x3 << 30); // select ad5 as input of a2d
	LPC_SC->PCONP |= (1<<12);		// power on a2d
	LPC_ADC->ADCR =  0x00200320;	// select chanel & maual start of conversion
	while(1){	
	LPC_ADC->ADCR |= 0x01000000;	// start of conversion
	
	do{
		i=LPC_ADC->ADDR5;
	}	while ( (i & 0x80000000) ==0); // check for end of conversion
	
	i=(i>>4) & 0xfff;
	sprintf (snum,"%4d",i);

	GLCD_DisplayString (1,1,snum);
	GLCD_Bargraph (10,100,300,20,i/4);
}
	
  
}
