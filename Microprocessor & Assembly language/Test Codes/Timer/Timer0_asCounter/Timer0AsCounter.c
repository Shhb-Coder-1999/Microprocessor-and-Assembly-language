#include "lpc17xx.h"

char timer0_counter = 0;
// Cclk=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define MR0_Value		5	//
#define PR0_Value		0		

//*********** Function name:		Timer0_IRQHandler

void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	LPC_GPIO2->FIOPIN++;
  return;
}
//*************************************************
void  init_timer0( )		 // 10ms
{
	timer0_counter = 0;
	LPC_PINCON->PINSEL3 |= (0x11<<20);
	LPC_TIM0->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM0->MR0 = MR0_Value;		//Timer Interval
	LPC_TIM0->MCR = 3;				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_TIM0->CTCR = 1;						//  Counter with rising edge of cap0.0
	LPC_TIM0->TCR = 1;						//  enable_timer0
}
//**************Main Function  main()
int main (void)
{	    		
  LPC_GPIO2->FIODIR = 0x000000FF;		/* P2.0...P2.7 defined as Outputs */
  init_timer0( ); // 10ms
  while (1) 
  {					/* Loop forever */
  }
}
//*************** End Of File
