#include "lpc17xx.h"
// Cclk=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define MR0_Value 8	 //
#define PR0_Value		0		
#define MR1_Value 8+14

//*********** Function name:		Timer3_IRQHandler

void TIMER3_IRQHandler (void) 
{  
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
	LPC_TIM3->IR = 2;			/* clear interrupt flag */
	LPC_GPIO0->FIOPIN++;
  return;
}
//*************************************************
void  init_timer3( )		 
{
	LPC_PINCON->PINSEL1 |= (0x3<<14);
	LPC_TIM3->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM3->MR0 = MR0_Value;		//Timer Interval
	LPC_TIM3->MR1 = MR1_Value;		//Timer Interval
	LPC_TIM3->MCR = (3<<3) | (1);				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER3_IRQn);
	LPC_TIM3->CTCR = 1;						//  Counter with both edge of cap3.0
	LPC_TIM3->TCR = 1;						//  enable_timer0
}
//**************Main Function  main()
int main (void)
{	    		
  LPC_GPIO0->FIODIR = 0xFFFFFFFF;		
  init_timer3( ); 
  while (1) 
  {					/* Loop forever */
  }
}