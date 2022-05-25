#include "lpc17xx.h"

// Cclk=100Mhz  , Pclk_Timer2=100MHz/2=50 MHz
#define MR3_Value		50*27000				//2500000	//
#define PR3_Value		0		

//*********** Function name:		Timer2_IRQHandler

void TIMER2_IRQHandler (void) 
{  
  LPC_TIM2->IR = (1<<3);			/* clear interrupt flag */
	LPC_GPIO0->FIOPIN=(LPC_GPIO0->FIOPIN<<4);
  return;
}
//*************************************************
void  init_timer2( )		 // 10ms
{
	LPC_SC->PCONP=(1<<22);				//power on timer 2
	LPC_SC->PCLKSEL1|= (1<<13);   // set clk timer2 as cpuclk/2	
	LPC_TIM2->PR  = PR3_Value;		//set prescaler to zero 
	LPC_TIM2->MR3 = MR3_Value;		//Timer Interval
	LPC_TIM2->MCR = (0x3<<9);				    // Interrupt and Reset on MR3
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->TCR = 1;						//  enable_timer0
}
//**************Main Function  main()
int main (void)
{	    		
  LPC_GPIO0->FIODIR = 0xFFFFFFFF;		/* P0.0...P0.32 defined as Outputs */
  LPC_GPIO0->FIOPIN = 0x1;		/* P0.0...P0.32 defined as Outputs */
  init_timer2( ); // 10ms
  while (1) 
  {					/* Loop forever */
	}
} 
//*************** End Of File
