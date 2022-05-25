#include "lpc17xx.h"

// Cclk=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define N_Value		1250	
#define PR2_Value		24		


//*************************************************
void  init_timer2( )
{
	LPC_PINCON->PINSEL0 |= ( 0x3<<18); 	// Set MAT2.3 as Output on PIN0.9
	LPC_TIM2->PR  = PR2_Value;	//set prescaler to zero 
	LPC_TIM2->MR2 = N_Value;		//Timer Interval
	LPC_TIM2->MCR = (2<<9);				  //Reset on MR3
	LPC_TIM2->EMR = (0x3<<10);				// Toggle MR3
	LPC_TIM2->TCR = 1;					//  enable_timer0
}
//**************Main Function  main()
int main (void)
{	    		
  init_timer2( ); // 50uSec
  while (1) 
  {					/* Loop forever */
  }
}
//*************** End Of File
