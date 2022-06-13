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
#define MR0_Value		12500000
#define PR0_Value		0		// pll0=2*M*f/N=2*100*12MHz/6=400MHz , Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
int		i;
	char snum[10];

 InitADC()
 {
	LPC_PINCON->PINSEL3= (0x3 << 30); // select ad5 as input of a2d
	LPC_SC->PCONP |= (1<<12);		// power on a2d
	LPC_ADC->ADCR =  0x00200320;	// select chanel & maual start of conversion
	LPC_ADC->ADCR |= 0x01000000;	// start of conversion

 }
//*********** Function name:		Timer0_IRQHandler

void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	i=((LPC_ADC->ADDR5)>>4)& 0xfff;
	LPC_ADC->ADCR |= 0x01000000;	// start of conversion

  return;
}
//*************************************************
void  init_timer0( )		 // 10ms
{
	
	LPC_TIM0->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM0->MR0 = MR0_Value;		//Timer Interval
	LPC_TIM0->MCR = 3;				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER0_IRQn);
		LPC_TIM0->TCR = 1;							

}

int main (void) {                       /* Main Program                       */

	

//  SystemInit();
//  SysTick_Config(25000000/100);  /* Generate interrupt every 10 ms     */

  GLCD_Init   ();
  GLCD_Clear  (White);
	GLCD_SetTextColor (Yellow);
	GLCD_SetBackColor (Black);
//	GLCD_DisplayString (2,2,"Laki");
	InitADC();
	init_timer0();
	while(1)
	{
	
	sprintf (snum,"%4d",i);
	GLCD_DisplayString (1,1,snum);
	GLCD_Bargraph (10,100,300,20,i/4);

	}
}
	
  

