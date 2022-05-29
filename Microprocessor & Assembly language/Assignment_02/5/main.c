#include "LPC17xx.h"
void EINT3_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 26); // pin2.13 as EINT3 input
	LPC_SC->EXTMODE|= (1<<3); // edge sensetive
	LPC_SC->EXTPOLAR|= (1<<3); // Rising
	NVIC_SetPriority (EINT1_IRQn,1);
	NVIC_EnableIRQ(EINT1_IRQn);
}

void EINT2_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 24); // pin2.13 as EINT3 input
	LPC_SC->EXTMODE|= (1<<2); // edge sensetive
	LPC_SC->EXTPOLAR|= (~(1<<2)); // Falling
	NVIC_SetPriority (EINT2_IRQn,1);
	NVIC_EnableIRQ(EINT2_IRQn);
}

int init_timer2(int power_bit)
{
	  LPC_SC->PCONP = (power_bit<<22);                      
}

void EINT2_IRQHandler(){
	init_timer2(0);             // Power OFF Timer2
	LPC_SC->EXTINT = (1<<2);    //clr flag
	
}
void EINT3_IRQHandler(){
  init_timer2(1);              // Power ON Timer2
	LPC_SC->EXTINT = (1<<1);      //clr flag
}
int main()
{
	EINT3_init();
	EINT2_init();
	
	while(1)
	{
	}	
}