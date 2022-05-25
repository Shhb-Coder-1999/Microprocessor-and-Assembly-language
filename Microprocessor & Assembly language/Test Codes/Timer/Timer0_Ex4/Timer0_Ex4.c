#include "lpc17xx.h"
char timer0_counter = 0;
#define MR0_Value_L_H		200
#define PR0_Value		0		// pll0=2*M*f/N=2*100*12MHz/6=400MHz , Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
//*********** Function name:		Timer0_IRQHandler
void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	LPC_TIM0->MR0 = MR0_Value_L_H;
}
//*************************************************
void  init_timer0( )		 // 10ms
{
	timer0_counter = 0;
	LPC_TIM0->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM0->MR0 = MR0_Value_L_H;		//Timer Interval
	LPC_TIM0->MCR = 0x2;				    // Reset on MR0
	LPC_TIM0->EMR = 0x30;		// Toggle MR0
	LPC_PINCON->PINSEL3 |= ( 0x3<<24); 	// Set pin as Match Out 0 PIN1.28
	LPC_SC->PCONP |= (1<<1);      //Power on Timer0 (Timer 0,1 Power On as default)
//	NVIC_EnableIRQ(TIMER0_IRQn);
}
//**************Main Function  main()
int main (void)
{	    		
  init_timer0( ); // 10ms
	LPC_TIM0->TCR = 1;							
  while (1) 
  {					/* Loop forever */
  }
}

//*************** End Of File
