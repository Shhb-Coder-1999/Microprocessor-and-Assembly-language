#include "LPC17xx.h"

int toggle = 1;
#define MR_Value 200
#define PR0_Value 0


void Init_Timer2(){	
	LPC_SC->PCLKSEL1 |= (0x3<<12);									//set timer clk = 1/8 cpu clk - user manual page 58
	LPC_TIM2->PR = PR0_Value;											//set prescaler to zero	
	LPC_TIM2->MR2 = MR_Value;								      //Timer interval
	LPC_TIM2->MCR = (0x3<<6);											//011 intrrupt and reset on MR2 - user manual page 505 
	LPC_TIM2->EMR=(0x3<<8);                          //toggle MR2 - user manual page 507
  NVIC_EnableIRQ(TIMER2_IRQn);                  
	LPC_TIM2->TCR = 1;                            //enable Timer
}

void TIMER2_IRQHandler(){	
	LPC_TIM1->IR = 1;
	
	if(toggle==1)
	{
    LPC_GPIO0->FIOPIN1 = 1;	
		toggle=0;
	}
	else  {
		LPC_GPIO0->FIOPIN1 = 2;
		toggle=1;
	}
	
	
}


int main(){
	LPC_GPIO0->FIODIR |= (3<<8);
	
  
	Init_Timer2();
	while(1)
	{

	}
}