#include "LPC17xx.h"
#define MR0_val 1375000  //5MHz * 275ms
#define MR5_val (1375000*30)/100 // 30%
#define MR6_val (1375000*45)/100  //  45%

void initPWM1()
{
	LPC_PINCON->PINSEL4 |= (1<<10);				//PWM1.6;
	LPC_PWM1->MR0 = MR0_val;
	LPC_PWM1->MR5 = MR5_val;
	LPC_PWM1->MR6 = MR5_val + MR6_val;
	LPC_PWM1->MCR = 0x2;		//Reset Counter When Match0 occured
	LPC_PWM1->PR = 4;  //    25MHz/(4+1) = 5MHz
	LPC_PWM1->PCR = (1<<6)|(1<<14);	 // Select Two Edge & Enable PWM for PWM6
	LPC_PWM1->LER = 0x61;		// Update Shadow Reg. MR0 & MR5 & MR6 -  (0000-0000-0110-0001)
	//LPC_PWM1->LER = ( 0x3 << 5 ) | ( 1 << 0 ) ;
	LPC_PWM1->TCR = 0x9;		//Counter & PWM Enable
}

int main()
{
	initPWM1();
	while(1);
}