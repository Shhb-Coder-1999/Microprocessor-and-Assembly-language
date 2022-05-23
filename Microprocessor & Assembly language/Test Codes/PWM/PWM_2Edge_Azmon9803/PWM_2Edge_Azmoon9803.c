#include "LPC17xx.h"
// Produce two edge PWM with different start time , periode=2000 usec 
#define MR0_value 2000*25		//2000 usec
#define MR1_value 30*25 
#define MR2_value 130*25 
#define MR4_value 130*25 
#define MR5_value 30*25 

void PWM1_IRQHandler (void) 
{  
		
		LPC_PWM1->LER = 0x14;		// Load Shadow MR1 , MR4 in MRx
		LPC_PWM1->IR = 0x1;			/* Clear Interrupt Flag */
  	LPC_PWM1->MR2 = MR1_value+ ( (LPC_GPIO0->FIOPIN0&0x0f)*100*25)   ;
  	LPC_PWM1->MR4 = MR5_value+ ( (LPC_GPIO0->FIOPIN0&0x0f)*100*25)   ;
    
	return;
}

void initPWM1()
{
	LPC_PINCON->PINSEL4 |= ( (0x01<<2) | (0x01<<8)) ;
	LPC_PWM1->MR0 = MR0_value;
	LPC_PWM1->MR1 = MR1_value;
	LPC_PWM1->MR2 = MR2_value;
	LPC_PWM1->MR4 = MR4_value;
	LPC_PWM1->MR5 = MR5_value;
	LPC_PWM1->MCR = 0x3;
	LPC_PWM1->PCR = 0x2424;
	LPC_PWM1->LER = 0x37;
	LPC_PWM1->TCR = 0x9;
		NVIC_EnableIRQ(PWM1_IRQn);

}

int main()
{
	initPWM1();
	while(1);
}	
