#include <LPC17xx.H>
int R_ADDR2,R_ADDR5;

void InitDAC()  					//D2A Func
{
	LPC_PINCON->PINSEL1 |= (0x2<<20);  		// Select as Aout (D2A) output of D2A port0.26
}

void InitADC()                                    // A2D Func
{
	LPC_PINCON->PINSEL3 |= 0x3<<30;		//select channel 5  as port 1.31
	LPC_PINCON->PINSEL1 |= 0x3<<18;		//select channel 2  as port 0.25
	LPC_SC->PCONP |= (1<<12);												//power on  A2D
	LPC_ADC->ADCR |= (1<<2)|(1<<5)|(0x3<<8)|(1<<16)|(1<<21); 	// select channel 2,5  && ClkDic  && manual start of conversion , PDN=1
	LPC_ADC->ADINTEN = (1<<5)   ;											// enable INT for channel 5 
	NVIC_EnableIRQ(ADC_IRQn);
	LPC_ADC->ADCR |= (1<<24);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ADC_IRQHandler()
{
		R_ADDR2 = (LPC_ADC->ADDR2);					//   clear done flag  channel 2
		R_ADDR5 = (LPC_ADC->ADDR5);					//   clear done flag channel 5 
		LPC_DAC->DACR = (R_ADDR5 + R_ADDR2)/2;		//  Find Avg & send it to Analog channel
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main (void)
{
	InitADC();
	InitDAC();
	while(1)
	{
		//loop
	}
}