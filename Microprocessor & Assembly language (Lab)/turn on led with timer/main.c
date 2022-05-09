#include "LPC17xx.h"
#define MR0_Value 50000000
#define PR0_Value 0

void Init()
{
	LPC_PINCON->PINSEL3 = (3<<12);
	LPC_TIM1->CTCR = 0;
	LPC_TIM1->PR = PR0_Value;
	LPC_TIM1->MR0 = MR0_Value;
	LPC_TIM1->MCR = 3;
	LPC_TIM1->EMR = (3<<4);
	
	NVIC_EnableIRQ(TIMER1_IRQn);
	LPC_TIM1->TCR = 1;

	
}
void TIMER1_IRQHandler(){
	LPC_TIM1->IR = 1;
	if(LPC_TIM1->MR0 == MR0_Value)
	{
		LPC_TIM1->MR0 = 25000000
		LPC_GPIO2->FIOPIN = 1;
		
	}
	else {
		LPC_TIM1->MR0 = MR0_Value;
		LPC_GPIO2->FIOPIN = 0;

	}
	
}

int main()
{
	LPC_GPIO2->FIODIR |= 0xff;
	Init();
	
	while(1)
	{
	}
}