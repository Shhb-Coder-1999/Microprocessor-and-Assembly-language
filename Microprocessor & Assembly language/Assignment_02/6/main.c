#include "LPC17xx.h"
int div;

void EINT0_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 20);     // pin2.10 as EINT0 input - user manual page 119
	LPC_SC->EXTMODE|= 1;                      // edge sensetive
	LPC_SC->EXTPOLAR|= ~(1);                  // Falling
	NVIC_SetPriority (EINT1_IRQn,1);
	NVIC_EnableIRQ(EINT1_IRQn);
}

void EINT2_init ()
{
	LPC_PINCON->PINSEL4  |= (0x01 << 24);   // pin2.12 as EINT2 input - user manual page 119
	LPC_SC->EXTMODE|= (1<<2);               // edge sensetive
	LPC_SC->EXTPOLAR|= (1<<2);              //  Rising
	NVIC_SetPriority (EINT2_IRQn,1);
	NVIC_EnableIRQ(EINT2_IRQn);
}

int init_timer2(int cpu_clk)
{
    switch (cpu_clk) {
    case 8:
        div = 3;
        break;
    case 2:
        div=2;
        break;
    default:
			  div=1;  
        break;
    }
	  LPC_SC->PCONP = (1<<22);                        //Power on Timer2 - user manual page 64
   	LPC_PINCON->PINSEL0 |= (0x3<<16);						   	//set pin as match out 2 pin0.8 - user manual page 117
    LPC_SC->PCLKSEL1 |= (div<<12);									//set timer cpu clk - user manual page 58                     
}


void EINT2_IRQHandler(){
	init_timer2(8);             // clk = 1/8 cpu clk
	LPC_SC->EXTINT = (1<<2);    //clr flag
	
}
void EINT0_IRQHandler(){
  init_timer2(2);              // clk = 1/2 cpu clk
	LPC_SC->EXTINT = (1<<1);      //clr flag
}

int main()
{
	EINT0_init();
	EINT2_init();
	
	while(1)
	{
	}	
}