#include "LPC17xx.h"
#define MR0_val 1375000
long int MR5_val = (1375000*30)/100;
long int MR6_val = (1375000*45)/100;
#define PR0_Value 0
int i=0;

int init_MR_Val();

void initPWM1()
{
	LPC_PINCON->PINSEL4 |= (1<<10);				//PWM1.6;
	LPC_PWM1->MR0 = MR0_val;
	LPC_PWM1->MR5 = MR5_val;
	LPC_PWM1->MR6 = MR5_val + MR6_val;
	LPC_PWM1->MCR = 0x3;		//Reset Counter & INT When Match0 occured
	LPC_PWM1->PCR = (1<<6)|(1<<14);	 // Select Two Edge & Enable PWM for PWM6
	LPC_PWM1->LER = 0x61;		// Update Shadow Reg. MR0 & MR5 & MR6 -  (0000-0000-0110-0001)
	LPC_PWM1->PR = PR0_Value;																											
	NVIC_EnableIRQ(PWM1_IRQn);
	LPC_PWM1->TCR = 0x9;		//Counter & PWM Enable
}


void PWM1_IRQHandler()
{
	LPC_PWM1->IR = (1<<0);  //clr flag
	//i++;
	//LPC_GPIO0->FIOPIN0=i;
	init_MR_Val();
	
}

int init_MR_Val(){
	  i++;
	  LPC_GPIO2->FIOPIN0 = i;
	
	  char port = LPC_GPIO0->FIOPIN0 & 0x0F;
	  int high_Val;
		
	
	  if (port == 1) high_Val      = 10;
	  else if (port == 2) high_Val = 20;
   	else if (port == 3) high_Val = 30;
	  else if (port == 4) high_Val = 40;
	  else if (port == 5) high_Val = 50;
	  else if (port == 6) high_Val = 60;
	  else if (port == 7) high_Val = 70;
	  else if (port == 8) high_Val = 80;
	  else if (port == 9) high_Val = 90;
	  else high_Val = 50;
	
	  MR5_val = (MR0_val*(100-high_Val)/2) / 100;
    MR6_val = (MR0_val*high_Val) / 100 ;
	
		LPC_PWM1->MR5 = MR5_val;
	  LPC_PWM1->MR6 = MR5_val + MR6_val;
	  LPC_PWM1->LER = 0x61;	
	
}


int main()
{
	initPWM1();
	while(1);
}