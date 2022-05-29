#include "LPC17xx.h"
int toggle =1;

void EINT1_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 22);     // pin2.11 as EINT1 input - user manual page 119
	LPC_SC->EXTMODE|= (1<<1);                 // edge sensetive
	LPC_SC->EXTPOLAR|= ((1<<1));             // Rising              
	//NVIC_SetPriority (EINT1_IRQn,1);
	NVIC_EnableIRQ(EINT1_IRQn);
}


void EINT1_IRQHandler(){
  if (toggle == 1){
		LPC_SC->EXTPOLAR = (~(1<<1));
		LPC_GPIO0->FIODIR2 = 0xFF;
    toggle = 0;	
	}
	else{
		LPC_SC->EXTPOLAR = ((1<<1));
	  LPC_GPIO0->FIODIR2 = 0x00;
		toggle = 1;	
	}
	
	LPC_SC->EXTINT = (1<<1);      //clr flag
	return;
}

int main()
{
	EINT1_init();
	
	while(1)
	{
	}	
}