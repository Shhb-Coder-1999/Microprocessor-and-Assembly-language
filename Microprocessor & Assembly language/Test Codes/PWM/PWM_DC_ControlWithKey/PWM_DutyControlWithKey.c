#include "LPC17xx.h"
#define t_1ms 25000
char key;
void PWM1_IRQHandler()
{
	key=LPC_GPIO0->FIOPIN0&0x0f;
	if(key>10)key=10;
	LPC_PWM1->MR1 = (t_1ms * key) / 10;
	LPC_PWM1->LER = 0x2;
	LPC_PWM1->IR = 0x2;
	return;
}
void initPWM1()
{
	LPC_PINCON->PINSEL4 |= 0x1;
	LPC_PWM1->MR0 = t_1ms;
	LPC_PWM1->MR1 = (t_1ms*10)/100;;
	LPC_PWM1->MCR = 0xA;
	LPC_PWM1->PCR = 0x200;
	LPC_PWM1->LER = 0x3;
	NVIC_EnableIRQ(PWM1_IRQn);
	LPC_PWM1->TCR = 0x9;
}
int main()
{
	initPWM1();
	LPC_GPIO0->FIODIR0=0x00; // 8 bit 7-0 port0 as input
	while(1);
}
