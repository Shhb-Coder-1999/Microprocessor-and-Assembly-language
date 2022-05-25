#include "lpc17xx.h"
// Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define N_Value		1250		//Pclk=25MHz    Time=50 uSec
#define PR0_Value		0		
//*************************************************
void  init_timer0( )		 // 10ms
{
	
	LPC_PINCON->PINSEL3 |= ( 0x3<<24); 	// Set pin as Match Out 0 PIN1.28
	LPC_TIM0->PR  = PR0_Value;		  //set prescaler to zero 
	LPC_TIM0->MR0 = N_Value;		    //Timer Interval
	LPC_TIM0->MCR = 0x2;				    // NO Interrupt and Reset 0n MR0
	LPC_TIM0->EMR = 0x30;						// Toggle MR0
	LPC_TIM0->TCR = 1;
}
//**************Main Function  main()
int main (void)
{	    		
  init_timer0(); 
  while (1) 
  {					/* Loop forever */
  }
}
