#include "LPC17xx.h"
//Produce four single edge PWM with 10msec periode and different duty cycle
#define MR0_VALUE	250000	// For 10ms 
#define MR1_VALUE	187500	// For 75% 10ms 
#define MR2_VALUE	80000	// For 32% 10ms 
#define MR3_VALUE	200000	// For 80% 10ms 
#define MR4_VALUE	62500	// For 25% 10ms 
#define Prescaler	0
void init_PWM(){
	//0001-1110-0000-0000
	LPC_PWM1->PCR |= (0x1<<9)|(0x1<<10)|(0x1<<11)|(0x1<<12);	//0x1E00; // Single edge and enable PWM output
	//0000-0000-0000-0010
	LPC_PWM1->MCR = 0x02;					//0x124B; Reset Counter when equal to MR0
	//0000-0000-0001-1111
	LPC_PWM1->LER = 0x1F;			// enable load shadow register
	
	LPC_PWM1->PR = Prescaler;
	LPC_PWM1->MR0 = MR0_VALUE;
	LPC_PWM1->MR1 = MR1_VALUE;
	LPC_PWM1->MR2 = MR2_VALUE;
	LPC_PWM1->MR3 = MR3_VALUE;
	LPC_PWM1->MR4 = MR4_VALUE;
	LPC_PINCON->PINSEL4 |= (0x1<<0)|(0x1<<2)|(0x1<<4)|(0x1<<6);
	LPC_PWM1 -> TCR = 9;	// Enable Counter and PWM1
}

int main(void){
	
//	SystemInit();
	init_PWM();
	while(1)
	{
	}
}

