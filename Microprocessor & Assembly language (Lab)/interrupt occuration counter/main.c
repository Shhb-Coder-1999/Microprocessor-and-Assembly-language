#include "LPC17xx.h"
int i=0;

int InitGPIO()
{
	LPC_GPIO2->FIODIR0 = 0xff;
	LPC_GPIOINT->IO2IntEnF = ( 1 << 10 );
	NVIC_EnableIRQ(EINT3_IRQn);// ACTIVATION OF INTERRUPTION
	return 0;
	
}
void EINT3_IRQHandler(void){
	i++;
	LPC_GPIOINT->IO2IntClr = (1 << 10 );
	LPC_GPIO2->FIOPIN0=i;
	
}

int main()
{
	InitGPIO();
	while(1)
	{
	}
}