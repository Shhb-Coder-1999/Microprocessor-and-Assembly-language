#include "LPC17xx.h"
//gpio interrupts for ports 0 and 2 are actually tied to external interrupt 3

// ***** EINT3 Initialization function *****
// Setup External Interrupt
void EINT3_init ()
{
	//Set PINSEL4 [21:20] = 01 for P2.10 as gpio
	//LPC_PINCON->PINSEL4 &= ~(0x11 << 20);
	//LPC_PINCON->PINSEL4 |= (0x01 << 20);
	
	LPC_PINCON->PINSEL4  = (0x01 << 26); // pin2.13 as EINT3 input
	LPC_SC->EXTMODE= (1<<3); // edge sensetive
	LPC_SC->EXTPOLAR= (~(1<<3)); // Falling
	NVIC_SetPriority (EINT3_IRQn,1);
	NVIC_EnableIRQ(EINT3_IRQn);
}

// ***** EINT2 Interrupt Handler*****

void GPIO_INT3_init ()
{
	LPC_GPIOINT->IO2IntEnF = ( 1 << 13 ); // port 2 falling edge sensetive as GPIO interrupt
	NVIC_EnableIRQ(EINT3_IRQn);
}




void EINT3_IRQHandler()
{

	
	if ((LPC_GPIOINT->IO2IntStatF & (1<<13))==(1<<13)){
	LPC_GPIO2->FIOPIN0=1; // turn on first led
	LPC_GPIOINT->IO2IntClr = (1 << 13 );  // Clear interrupt
	}
	if (LPC_SC->EXTINT != (1<<3)) {
	LPC_GPIO2->FIOPIN0=2;	 // turn on second led
	LPC_SC->EXTINT = (1<<3); // Clear interrupt
	}
	
}


int main()
{
	EINT3_init();
	GPIO_INT3_init ();
	while(1)
	{
	}
}