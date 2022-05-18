#include "LPC17xx.h"

#define N_Value	400
#define	PR0_Value	0

void init_timer2()
{
	LPC_PINCON->PINSEL0 |= (0x3<<16);							//set pin as match out 2 pin0.8 - user manual page 117
	LPC_SC->PCLKSEL1 |= (0x3<<2);									//set timer clk = 1/8 cpu clk - user manual page 58
	LPC_TIM2->PR = PR0_Value;											//set prescaler to zero
	LPC_TIM2->MR2 = N_Value;											//Timer interval -> 250,000
	LPC_TIM2->MCR = (0x2<<6);											//010 No intrrupt (toggle) and reset on MR2 - user manual page 505 
	LPC_TIM2->EMR = (3<<8);												//toggle MR2 - user manual page 507
	LPC_TIM2->TCR = 1;														//enable timer 2
}

int main(void)
{
 	init_timer2();
	while(1)
	{
		//loop for ever
	}
	
}