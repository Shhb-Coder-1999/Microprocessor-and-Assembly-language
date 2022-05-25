#include "lpc17xx.h"
// Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/8=12.5 MHz
#define Value_L		337500		//Pclk=12.5MHz    Low Time=27 msec
#define Value_H		125000		//Pclk=12.5MHz    High Time=10 msec
#define PR0_Value		0		
//*********** Function name:		Timer0_IRQHandler
void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
	if(LPC_TIM0->MR0 == Value_H) LPC_TIM0->MR0 = Value_L;
	else LPC_TIM0->MR0 = Value_H;
}
//*************************************************
void  init_timer0( )		 // 10ms
{
	
	LPC_PINCON->PINSEL3 |= ( 0x3<<24); 	// Set pin as Match Out 0 PIN1.28
	LPC_SC->PCLKSEL0 |= (0x3<<2);		// set timer clock = 1/8 cpu clock
	LPC_TIM0->PR  = PR0_Value;		  //set prescaler to zero 
	LPC_TIM0->MR0 = Value_L;		    //Timer Interval
	LPC_TIM0->MCR = 0x3;				    // Interrupt and Reset 0n MR0
	LPC_TIM0->EMR = 0x3<<4;						// Toggle MR0   00110000
	NVIC_EnableIRQ(TIMER0_IRQn);
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
