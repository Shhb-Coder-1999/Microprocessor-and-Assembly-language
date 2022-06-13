#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */

#define MR0_Value		12500
#define PR0_Value		0		// pll0=2*M*f/N=2*100*12MHz/6=400MHz , Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
int		i,j,Sum;

void InitADC()
 {
	LPC_PINCON->PINSEL3= (0x3 << 30); // select ad5 as input of a2d port1.31
	LPC_SC->PCONP |= (1<<12);		// power on a2d
	LPC_ADC->ADCR =  0x0020031C;	// select chanel 2,3,4& maual start of conversion
//	LPC_ADC->ADCR |= 0x01000000;	// start of conversion

 }
//*************************************************
 void InitDAC()
 {
	LPC_PINCON->PINSEL1|= 0x00200000;		// (0x2 << 20); // select  as Aout (DAC) output of d2a port0.26
 }
//*********** Function name:		Timer0_IRQHandler

void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	Sum=0;
	LPC_ADC->ADCR |= (1<<16);	// Burst mode
//	LPC_ADC->ADCR |= (1<<24);	// start of conversion
	for(i=0;i<3;i++)
     {	
			 if(i==2) LPC_ADC->ADCR &= ~(1<<16);	// Cancle Burst mode
			while ( LPC_ADC->ADGDR && (1<<31) ==0);
			Sum+= LPC_ADC->ADGDR>>4;
		 } 
	
		 
	j++;
	LPC_DAC->DACR= (j<<4)|0x00010000;

  return;
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

	InitADC();
	InitDAC();
	init_timer0();
	LPC_GPIO0->FIODIRL=0x0fff;
			while(1)
	{


	}
}
	
  

