#include "LPC17xx.h"
#include <string.h>

char keyValue;
_Bool Flag=1;
int toggle=1;
long int MR0_Value_HIGH =  50000;
long int MR0_Value_LOW  = 450000;
#define PR0_Value 0


int InitGPIO(){
	LPC_GPIO1->FIODIR3 = 0x00;	// KeyBoard Input
	LPC_GPIO2->FIODIR0 = 0xff;	// LED Output	
	LPC_GPIO2->FIOPIN0 = 0x00;	// All LED off
	return 0;
}

void joystick(){
	keyValue = LPC_GPIO1->FIOPIN3 & 0x3e;
		
		if (keyValue==0x3e)		// [00111110] = 3E  , All keys off
		{
			Flag = 0;	
			return;
		}
		else
		{
			if(Flag==1)
				return;
			
			Flag = 1;

			if (keyValue==0x3a)	//[00111010] = 3A --UP--
			{
					
	        if(LPC_TIM1->MR0 == 50000 || LPC_TIM1->MR0 == 450000  )
	          {
	         	MR0_Value_HIGH =  250000;
            MR0_Value_LOW  = 250000;
						LPC_TIM1->MR0 = MR0_Value_HIGH;
							
	           }
	        else if (LPC_TIM1->MR0 == 250000){
		       MR0_Value_HIGH =  450000;
           MR0_Value_LOW  = 50000;
					 LPC_TIM1->MR0 = MR0_Value_HIGH;
	           }
					
						 
			}
			
			else if (keyValue==0x2e)//[00101110] = 2E --DOWN--
			{
					if(LPC_TIM1->MR0 == 450000 || LPC_TIM1->MR0 == 50000)
	            {
	      	    MR0_Value_HIGH =  250000;
              MR0_Value_LOW  = 250000;
							LPC_TIM1->MR0 = MR0_Value_HIGH;
	 	
	           }
	        else if (LPC_TIM1->MR0 == 250000){
	      	    MR0_Value_HIGH =  50000;
              MR0_Value_LOW  = 450000;
					  	LPC_TIM1->MR0 = MR0_Value_HIGH;
				              
	       		}
		    }
}
		}

void Init_Timer(){
	//LPC_PINCON->PINSEL4 = (3<<12);
	LPC_TIM1->CTCR = 0;
	LPC_TIM1->PR = PR0_Value;
	LPC_TIM1->MR0 = MR0_Value_HIGH;
	LPC_TIM1->MCR = 3;
	//LPC_TIM1->EMR = (3<<4);
	NVIC_EnableIRQ(TIMER1_IRQn);
	LPC_TIM1->TCR = 1;                    //Enable Timer1

	
}
void TIMER1_IRQHandler(){
	  LPC_TIM1->IR = 1;                     //Clr INT Flag
	

		if(LPC_TIM1->MR0 == MR0_Value_LOW && toggle==1)  // Switch Cycle To High
	{
		LPC_TIM1->MR0 = MR0_Value_HIGH;     
		LPC_GPIO2->FIOPIN = 1;              // Turn on Led
		
	}
	
	else if(LPC_TIM1->MR0 == MR0_Value_HIGH && toggle==0 ) {
		LPC_TIM1->MR0 = MR0_Value_LOW;     // Switch Cycle To Low
		LPC_GPIO2->FIOPIN = 0;             // Turn off Led
	}


	
	if (toggle == 1) toggle = 0;
	else toggle = 1;
		
	

}




int main(){

	InitGPIO();
	Init_Timer();
	while(1)
	{
		joystick();
	}
}