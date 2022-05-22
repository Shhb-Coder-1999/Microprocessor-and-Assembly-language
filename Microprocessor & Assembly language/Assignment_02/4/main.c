#include "LPC17xx.h"

#define PR0_Value    0
#define N_Value     12

void TIMER2_IRQHandler (void)
{
    LPC_TIM2->IR = 1;                               // clear interrupt flag
    LPC_GPIO2->FIOPIN++;

}
//

int init_timer2(void)
{
	  LPC_SC->PCONP |= (1<<22);
    LPC_PINCON->PINSEL0 |= (0x3 << 8);    					// CAP2.0        
    LPC_TIM2->CTCR = 0x1;                          // counter
    LPC_TIM2->PR    =  PR0_Value;                   // set prescalar to 0
    LPC_TIM2->MR2  =  N_Value;                     // TIMER Interval 
	  //LPC_TIM2->CCR = 1;
    LPC_TIM2->MCR =  0x3;                           // Interrupt and Reset On MR0
    NVIC_EnableIRQ(TIMER2_IRQn);                    // enable interrupt
    LPC_TIM2->TCR =  1;                             // enable counter
}

int main(void)
{
    init_timer2();
    LPC_GPIO2->FIODIR = 0xffffffff;
    while(1)
    {
        // Loop forever
    }
}