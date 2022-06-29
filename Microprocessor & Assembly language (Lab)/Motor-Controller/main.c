#include "LPC17xx.h"
#include "math.h"

#define T_MR0_Value 3750000							// 375000000  		// 15 / (1 / 25MHz) = 375 * 10^6 // 15 sec Interrupt to measure temperature


#define Auto 0										// Automatic mode
#define Manual 1									// Manual mode

#define MR0_feq_50 500000					// (1 / 50) / (1 / 25 MHz) = 500000
#define MR0_feq_40 625000					// (1 / 40) / (1 / 25 MHz) = 625000

#define min_Duty 0.4
#define max_Duty 1

int State = Manual , P_MR0_Value ;
double V_ref = 3.3, Temperature , Units , Digital_Data, Duty_cycle=0.4 ;
_Bool ON = 0 ;

_Bool KeyFlag=0;
int key;
char keyValue;

// ----------------------------------- .:: Functions ::. -------------------------------------------------
int InitGPIO(void);
void keyBoardFunction(void);
void TIMER0_IRQHandler (void);
void Init_Timer0(void);
void InitADC(void);
void ADC_IRQHandler(void);
void Init_PWM(int MR0_value,int MR1_Value);

// ----------------------------------- .:: KeyBoard ::. -------------------------------------------------

int InitGPIO(void)
{
	LPC_GPIO1->FIODIR3 &= ~((1<<25) | (1<<26) | (1<<27) | (1<<28));	// JoyStick KeyBoard Input
	LPC_GPIO2->FIODIR0 = 1;
	return 0;
}

void keyBoardFunction(void)
{
	keyValue = LPC_GPIO1->FIOPIN3 & 0x3e;
	

	if (keyValue==0x3e)		// [00111110] = 3E  , All keys off
	{
		KeyFlag = 0;	
		return;
	}
	else
	{
		if(KeyFlag==1)
			return;
		
		KeyFlag = 1;
		
		if (keyValue==0x3c)	//[00111100] = 3C   // SELECT Manual or Automatic
		{
			if (State == Auto)
			{
				State = Manual;
				LPC_TIM0->TCR = 0;																	// Disable Timer0

			}
			else		// Manual bude
			{
				State = Auto;
				P_MR0_Value = MR0_feq_50;
				Init_Timer0();                              	  // Enable Timer0
				ON = 0;
			}
		}
		if (State == Manual && keyValue==0x3a)	//[00111010] = 3A  // State = Manual : TURN ON or TURN OFF
		{
			if(ON == 1) // ON bude va mikhaym OFF konim
			{
				Init_PWM(P_MR0_Value , 0);															// PWM is ON but there is no pulse for motor

				ON = 0;
			}
			else																			// OFF bude va mikhaym ON konim
			{
				P_MR0_Value = MR0_feq_50;
				Init_PWM(P_MR0_Value, Duty_cycle * P_MR0_Value );
				LPC_PWM1->TCR = 9;                      							//Enable counter & PWM1
				ON = 1;
			}
		}
		else if (State == Manual && ON == 1 && keyValue==0x36)	//[00110110] = 36 // State = Manual and ON : Slower
		{
			if(min_Duty < Duty_cycle)
			{
				Duty_cycle -= 0.1;
				LPC_PWM1->MR1 = Duty_cycle * LPC_PWM1->MR0;
				LPC_PWM1->LER = (1<<0)|(1<<1);   			// update shadow reg MR0,MR1      0000 0000 0000 0011
			}
		
		}
		else if (State == Manual && ON == 1 && keyValue==0x2e)	//[00101110] = 2E // State = Manual and ON : Faster
		{
			if( Duty_cycle < max_Duty)
			{
				Duty_cycle += 0.1;
				LPC_PWM1->MR1 = Duty_cycle * LPC_PWM1->MR0 ;
				LPC_PWM1->LER = (1<<0)|(1<<1);   			//update shadow reg MR0,MR1      0000 0000 0000 0011
			}
				
		}
		
		return;
	}
}

// ----------------------------------- .:: Timer ::. -------------------------------------------------




double power=0.2;
double old_tmp=0;

void Init_Timer0(void)
{
    LPC_TIM0->MR0 = T_MR0_Value;                  			// TIMER Interval
    LPC_TIM0->MCR = 0x3;                                // Interrupt and Reset On MR0
    NVIC_EnableIRQ(TIMER0_IRQn);                 				// Enabling Interupt
    LPC_TIM0->TCR = 1;                              	// Enable Timer0
}

void TIMER0_IRQHandler (void)
{
	LPC_TIM0->IR = 1;																			// clear interrupt flag
	
	Digital_Data = ((LPC_ADC->ADDR1)>>4) & 0xfff;					// clear flag Done ADDR1 and save result of conversion
	
  Units = (pow(2,12))-1;             										// Units = 4096 - 1 = 4095 
  
	Temperature = (Digital_Data * 100) / Units;						// determine Temperature between 0 to 100
	
	LPC_ADC->ADCR |= (1<<24);															// start of conversion A2D
	
	
	if(Temperature <26)																	
	{
		Init_PWM(MR0_feq_50,0);														// PWM is ON but there is no pulse for motor
	}
	else if (26 <= Temperature)				// Duty cycle = 40%
	{
		if (Temperature - old_tmp >=4){
			power+=0.2;
		}
		
		Init_PWM(MR0_feq_50,power*MR0_feq_50);	
		LPC_PWM1->TCR = (1<<0) | (1<<3);										// Enable counter & PWM1										
	}
	
	old_tmp=Temperature;
}

// ----------------------------------- .:: A2D ::. -------------------------------------------------
void InitADC(void)
{
	LPC_PINCON->PINSEL1 |= (1<<16);												// select AD1 port 0.24                                          *page 117
	LPC_SC->PCONP |= (1<<12);															// power on A2D			                                             *page 64
	LPC_ADC->ADCR = 0;
	LPC_ADC->ADCR |= (1<<1) | (0x3<<8) | (1<<21); 				// select chanel 1 and clkDiv to 3 and set PDN to 1    *page 58
}


// ----------------------------------- .:: PWM ::. -------------------------------------------------
void Init_PWM(int MR0_value,int MR1_Value)
{
	LPC_PINCON->PINSEL4 |= (1<<0) ;												// enable output pwm1.1 -> port2.0   *page 119

	LPC_PWM1->MR0 = MR0_value;
	LPC_PWM1->MR1 = MR1_Value;
	LPC_PWM1->MCR = 0x02; 								  							// reset counter when equal to MR0																											
	LPC_PWM1->PCR = (0x01<<9);  													// one edge and enable PWM output
	LPC_PWM1->LER = (1<<0)|(1<<1);   											//update shadow reg MR0,MR1      0000 0000 0000 0011
	
}

// ------------------------------------------------------------------------------------



int main()
{
	InitGPIO();
	InitADC();
	
	while(1)
	{
		keyBoardFunction();
		
		
	}
}
