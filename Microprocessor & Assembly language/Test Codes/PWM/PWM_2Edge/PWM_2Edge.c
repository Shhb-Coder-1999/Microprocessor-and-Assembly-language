#include "LPC17xx.h"
// Produce two edge PWM with different start time , periode=1500 uSec 
// All PWM with 500uSec High Time
// Start of PWM1) 300 uSec    PWM2) 500 uSecPWM3) 700 uSec
#define t_100uSec 2500
#define t_300uSec (t_100uSec * 3) 
#define t_500uSec (t_100uSec * 5) 
#define t_700uSec (t_100uSec * 7)
#define t_1500uSec (t_100uSec * 15)

void initPWM1()
{
	LPC_PINCON->PINSEL4 |= (1<<2)|(1<<6) | (1<<10);				//0x444;
	LPC_PWM1->MR0 = t_1500uSec;
	LPC_PWM1->MR1 = t_300uSec;
	LPC_PWM1->MR2 = t_300uSec + t_500uSec;
	LPC_PWM1->MR3 = t_500uSec;
	LPC_PWM1->MR4 = t_500uSec + t_500uSec;
	LPC_PWM1->MR5 = t_700uSec;
	LPC_PWM1->MR6 = t_500uSec + t_700uSec;
	LPC_PWM1->MCR = 0x2;		//Reset Counter When Match0 occured
	LPC_PWM1->PCR = (1<<2)|(1<<4)|(1<<6)|(1<<10)|(1<<12)|(1<<14);	//0x5454; // Select Two Edge & Enable PWM
	LPC_PWM1->LER = 0x7F;		// Update Shadow Reg. MR0-MR6
	LPC_PWM1->TCR = 0x9;		//Counter & PWM Enable
}

int main()
{
	initPWM1();
	while(1);
}	