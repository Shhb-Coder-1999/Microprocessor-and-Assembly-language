#include "LPC17xx.h"


#define MR2_Value_High 2440
#define MR2_Value_Low 1220
#define PR0_Value 0


void Init_Timer2(){
	LPC_SC->PCONP |= (1<<22);
	LPC_PINCON->PINSEL0 |= (0x3<<16);							//set pin as match out 2 pin0.8 - user manual page 117
	//LPC_SC->PCLKSEL1 |= (0x3<<12);									//set timer clk = 1/8 cpu clk - user manual page 58
	LPC_TIM2->PR = PR0_Value;											//set prescaler to zero
	LPC_TIM2->MR2 = MR2_Value_High;								//Timer interval
	LPC_TIM2->MCR = (0x3<<6);											//011 intrrupt and reset on MR2 - user manual page 505 
	LPC_TIM2->EMR=(0x3<<8);                       //toggle MR2 - user manual page 507
  NVIC_EnableIRQ(TIMER2_IRQn);                  
	LPC_TIM2->TCR = 1;                            //enable Timer
	
}
void TIMER2_IRQHandler(){
	  LPC_TIM2->IR =  1<<2;                     //Clr INT Flag
	
	  if(LPC_TIM2->MR2 == MR2_Value_High)
	{
		LPC_TIM2->MR2 = MR2_Value_Low;
		
	}
	else if (LPC_TIM2->MR2 == MR2_Value_Low) {
		LPC_TIM2->MR2 = MR2_Value_High;

	}
}



int main(){

	Init_Timer2();
	while(1)
	{

	}
}