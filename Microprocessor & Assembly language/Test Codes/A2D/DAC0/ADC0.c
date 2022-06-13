//برنامه بنويسيد که يک متغير را هر 500 ميکروثانيه يک واحد اضافه
// و به خروجي آنالوگ منتقل کند
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */

#define MR0_Value		12500
#define PR0_Value		0		// pll0=2*M*f/N=2*100*12MHz/6=400MHz , Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
int		i;

//*************************************************
 void InitDAC()
 {
	LPC_PINCON->PINSEL1|= 0x00200000;		// (0x2 << 20); // select  as Aout (DAC) output of d2a port0.26
 }
//*********** Function name:		Timer0_IRQHandler

void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	i=i+1;
	LPC_DAC->DACR= (i<<6);
}
//*************************************************
void  init_timer0( )		 // 10ms
{
	
	LPC_TIM0->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM0->MR0 = MR0_Value;		//Timer Interval
	LPC_TIM0->MCR = 3;				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_TIM0->TCR = 1;							
}

int main (void) {                       /* Main Program                       */

	InitDAC();
	init_timer0();
	while(1)
	{


	}
}
	
  

