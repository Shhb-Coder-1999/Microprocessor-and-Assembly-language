#include "LPC17xx.h"

#define t_1ms 25000

char dutyCycles[8] = {10, 20, 30, 40, 50, 40, 30, 20};
char counter =1;

void PWM1_IRQHandler()
{
	LPC_PWM1->MR1 = t_1ms * dutyCycles[counter++] / 100;
	if(counter == 8)
		counter = 0;
	LPC_PWM1->LER = 0x2;
	LPC_PWM1->IR = 0x2;
	return;
}

void initPWM1()
{
	LPC_PINCON->PINSEL4 |= 0x1;
	LPC_PWM1->MR0 = t_1ms;
	LPC_PWM1->MR1 = (t_1ms*10)/100;;
	LPC_PWM1->MCR = (1<<1)|(1<<3);
	LPC_PWM1->PCR = (1<<9);
	LPC_PWM1->LER = 0x3;
	NVIC_EnableIRQ(PWM1_IRQn);
	LPC_PWM1->TCR = 0x9;
}

int main()
{
	SystemInit();
	initPWM1();
	while(1);
}
