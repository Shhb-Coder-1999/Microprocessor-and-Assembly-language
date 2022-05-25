#include "lpc17xx.h"

// Cclk=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define N_Value		1250	
#define PR0_Value		0		


//*************************************************
void  init_timer0( )
{
	LPC_PINCON->PINSEL3 |= ( 0x3<<24); 	// Set pin as Match Out 0 PIN1.28
	LPC_TIM0->PR  = PR0_Value;	//set prescaler to zero 
	LPC_TIM0->MR0 = N_Value;		//Timer Interval
	LPC_TIM0->MCR = 2;				  //Reset on MR0 , No Interrupt
	LPC_TIM0->EMR = (0x3<<4);				// Toggle MR0
	LPC_TIM0->TCR = 1;					//  enable_timer0
}
//**************Main Function  main()
int main (void)
{	    		
  init_timer0( ); // 50uSec
  while (1) 
  {					/* Loop forever */
  }
}
//*************** End Of File
