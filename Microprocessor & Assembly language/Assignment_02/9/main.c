#include "lpc17xx.h"

// Cclk=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define MR0_Value 9 
#define PR0_Value		0		

//*********** Function name:		Timer2IRQHandler

void TIMER2_IRQHandler (void) 
{  
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
	LPC_GPIO0->FIOPIN++;
	
	if (LPC_TIM2->CTCR == 1) // change counter input
		LPC_TIM2->CTCR = 5;
	else LPC_TIM2->CTCR = 1;
	
  return;
}
//*************************************************
void  init_timer2( )		 
{
	LPC_SC->PCONP |= (1<<22);
	LPC_PINCON->PINSEL0 |= (0x3<<10) |(0x3<<8) ;   // CAP2.0  & // CAP2.1 
	LPC_TIM2->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM2->MR0 = MR0_Value;		//Timer Interval
	LPC_TIM2->MCR = 3;				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->CTCR = 1;						//  Counter Rising edge of cap2.0
	LPC_TIM2->TCR = 1;						//  enable_timer0
}
//**************Main Function  main()
int main (void)
{	    		
  LPC_GPIO0->FIODIR = 0xFFFFFFFF;		
  init_timer2( ); 
  while (1) 
  {					/* Loop forever */
  }
}