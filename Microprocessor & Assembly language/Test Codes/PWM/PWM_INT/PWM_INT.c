#include "LPC17xx.h"

//#define P1000	250000		// For 100% 10ms 
#define P100	375000		// For 100% 15ms 

#define P20		0.2*P100	// For 20% P100
#define P80		0.8*P100	// For 80% P100
//#define P50		0.5*P100	// For 50% P100 
#define P10		0.1*P100	// For 10% P100 
//#define P5 		0.05*P100	// For 5%  P100
//#define P0 		0			// For 0%  P100

#define Prescaler	0
int DutyCycle1,DutyCycle2;
int dir1, dir2; // 1 is Incremental Pulse and 0 is Decreasing Pulse

void PWM1_IRQHandler (void) 
{  
//	if( (LPC_PWM1->IR & 0x1) == 0x1){ // Interup for MR0
		
		// For PWM1 (OutPut1)
		if (dir1) LPC_PWM1->MR1 = LPC_PWM1->MR1 + P10;
		else 			LPC_PWM1->MR1 = LPC_PWM1->MR1 - P10;
		if (LPC_PWM1->MR1 == P20)			 dir1 = 1;		// Set For Increment
	  else if (LPC_PWM1->MR1 == P80) dir1 = 0;		// Set For Decrement
		

		
		LPC_PWM1->LER = 0x6;		// Load Shadow MRx in MRx
		LPC_PWM1->IR = 0x1;			/* Clear Interrupt Flag */

	return;
}



void init_PWM(){
	LPC_PINCON->PINSEL4 |= 0x5;	// select function 1 for  p2.0 and p2.1 as Pwm1.1 and PWM1.2 Outputs
	//0000-0110-0000-0000
	LPC_PWM1->PCR = 0x600;	// Select One Edge and enable PWM1 , PWM2 Output
	//0001-0000-0000-0011
	LPC_PWM1->MCR = 0x3;		//Enable Interrupt MR0 & Rest TC at MR0
	//0000-0000-0000-0111
	LPC_PWM1->LER = 0x7;	//Update Shadow register MR0,MR1,MR2
	LPC_PWM1->PR = Prescaler;
	
	LPC_PWM1->MR0 = P100;
	LPC_PWM1->MR1 = P20;
//	LPC_PWM1->MR2 = P0;
	NVIC_EnableIRQ(PWM1_IRQn);
	LPC_PINCON->PINSEL4 |= 0x5;
}

int main(void){
	SystemInit();
	dir1 = dir2 = 1;
	init_PWM();
	LPC_PWM1 -> TCR = 9;	// TC Counter Enable & Enable PWM1
	while(1);
}

