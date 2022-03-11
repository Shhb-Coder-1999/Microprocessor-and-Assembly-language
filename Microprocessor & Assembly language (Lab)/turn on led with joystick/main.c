#include "LPC17xx.h"

char keyValue;
_Bool Flag=0;
int i=0;

int InitGPIO()
{
	LPC_GPIO1->FIODIR3 = 0x00;	// KeyBoard Input
	LPC_GPIO2->FIODIR0 = 0x1f;	// LED Output	
	LPC_GPIO2->FIOPIN0 = 0x00;	// All LED off
	return 0;
}


void joystick()
{
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
			
			if (keyValue==0x3c)	//[00111100] = 3C
			{
				LPC_GPIO2->FIOPIN0 = 1;
				for(i=0;i<100000;i++);
				LPC_GPIO2->FIOPIN0 = 0;
			}
			
			else if (keyValue==0x3a)	//[00111010] = 3A
			{
				LPC_GPIO2->FIOPIN0 = (1<<1);
				for(i=0;i<100000;i++);
				LPC_GPIO2->FIOPIN0 = 0;
			}
			
			else if (keyValue==0x36)	//[00110110] = 36
			{
				LPC_GPIO2->FIOPIN0 = (1<<2);
				for(i=0;i<100000;i++);
				LPC_GPIO2->FIOPIN0 = 0;
			}
			
			else if (keyValue==0x2e)	//[00101110] = 2E
			{
				LPC_GPIO2->FIOPIN0 = (1<<3);
				for(i=0;i<100000;i++);
				LPC_GPIO2->FIOPIN0 = 0;
			}
			
			else if (keyValue==0x1e)	//[00011110] = 1E
			{
				LPC_GPIO2->FIOPIN0 = (1<<4);
				for(i=0;i<100000;i++);
				LPC_GPIO2->FIOPIN0 = 0;
			}
			
		}
}


int main()
{
	
	InitGPIO();
	
	while(1)
	{
		joystick();
	
	}
}