#include "LPC17xx.h"

void EINT1_init ()
{

	
	LPC_PINCON->PINSEL4  |= (0x01 << 22); // pin2.13 as EINT3 input
	LPC_SC->EXTMODE|= (1<<1); // edge sensetive
	LPC_SC->EXTPOLAR|= (~(1<<1)); // Falling
	NVIC_SetPriority (EINT1_IRQn,1);
	NVIC_EnableIRQ(EINT1_IRQn);
}

void EINT2_init ()
{
	
	LPC_PINCON->PINSEL4  |= (0x01 << 24); // pin2.13 as EINT3 input
	LPC_SC->EXTMODE|= (1<<2); // edge sensetive
	LPC_SC->EXTPOLAR|= (~(1<<2)); // Falling
	NVIC_SetPriority (EINT2_IRQn,2);
	NVIC_EnableIRQ(EINT2_IRQn);
}





void EINT2_IRQHandler(){
	
	LPC_GPIO2->FIOSET0=2;
	for(int i =0;i<20000000;i++);
	LPC_GPIO2->FIOCLR0 =  2;
	LPC_SC->EXTINT = (1<<2);
	
}
void EINT1_IRQHandler(){
	LPC_GPIO2->FIOSET0=1;
	for(int i =0;i<20000000;i++);
	LPC_GPIO2->FIOCLR0 =  1;
	LPC_SC->EXTINT = (1<<1); 
	
}

int main()
{
	
	LPC_GPIO2->FIODIR=0xff;
	
	
	EINT1_init();
	EINT2_init();
	
	while(1)
	{
	}	
}