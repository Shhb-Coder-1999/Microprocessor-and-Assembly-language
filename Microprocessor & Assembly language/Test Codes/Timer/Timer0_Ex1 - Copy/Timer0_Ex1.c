#include "lpc17xx.h"

// Cclk=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
#define MR0_Value		250000	//
#define PR0_Value		0	
char DutyCycle[10]={10,90,20,80,30,70,40,60,50,50},i;

//*********** Function name:		Timer0_IRQHandler

void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	LPC_TIM0->MR0 = MR0_Value*DutyCycle[i];		//Timer Interval
	i++;
	if(i==10)=i=0;
	LPC_GPIO2->FIOPIN++;
  return;
}
//*************************************************
void  init_timer0( )		 // 10ms
{
	LPC_TIM0->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM0->MCR = 3;				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER0_IRQn);
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
