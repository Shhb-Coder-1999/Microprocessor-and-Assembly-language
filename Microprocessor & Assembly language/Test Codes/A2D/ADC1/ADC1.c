// برنامه اي بنويسيد که هر 500 ميکرو ثانيه مقدار وردي 5 آنالوگ را به ديجيتال تبديل
// کرده و در پورت 0 نشان دهيد. همينطور 3 برابر آن را به خروجي آنالوگ منتقل کند
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#define MR0_Value		12500	// 500uSec
#define PR0_Value		0		// pll0=2*M*f/N=2*100*12MHz/6=400MHz , Cclk=PLL0/4=100Mhz  , Pclk_Timer0=100MHz/4=25 MHz
int		i;
//*************************************************
 void InitDAC()
 {
	LPC_PINCON->PINSEL1|= (0x2 << 20); // select  as Aout (DAC) output of d2a port0.26
 }
//*************************************************
 void InitADC()
 {
	LPC_PINCON->PINSEL3= (0x3 << 30); // select ad5 as input of a2d port1.31
	LPC_SC->PCONP |= (1<<12);		// power on a2d
	LPC_ADC->ADCR =  (0x1<<5)|(0x3<<8)|(0x1<<21);	// select chanel & ClkDiv & PDN=1
	LPC_ADC->ADCR |= (0x1<<24);	// start of conversion
 }
//*********** Function name:		Timer0_IRQHandler
void TIMER0_IRQHandler (void) 
{  
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	LPC_DAC->DACR= ((LPC_ADC->ADDR5*3)&0xffff);   

	LPC_GPIO0->FIOPINL=((LPC_ADC->ADDR5)>>4)& 0xfff;
	LPC_ADC->ADCR |= (0x1<<24);	// start of conversion
  return;
}
//*************************************************
void  init_timer0( )		 // 500us
{
	LPC_TIM0->PR  = PR0_Value;		//set prescaler to zero 
	LPC_TIM0->MR0 = MR0_Value;		//Timer Interval
	LPC_TIM0->MCR = 3;				    // Interrupt and Reset on MR0
	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_TIM0->TCR = 1;							
}
int main (void) {                       /* Main Program                       */
	InitADC();
	init_timer0();
	LPC_GPIO0->FIODIRL=0x0fff;
	while(1)
	{
	}
}
	
  

