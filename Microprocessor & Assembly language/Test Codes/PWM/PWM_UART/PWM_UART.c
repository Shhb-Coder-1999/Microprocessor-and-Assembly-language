#include "LPC17xx.h"

//                ---------------                         --------
//               |               |                       |
//                                -----------------------
//                   150 msec           250 msec           75 msec
//send UART0     S               F                        R

#define MR0_value		11875000		//475 msec
#define MR4_value		10000000		//400 msec  set f.f.
#define MR5_value		3750000			//150 mse	 reset f.f.
#define FOSC		12000000
#define FCCLK         100000000    
#define FPCLK         (FCCLK / 4)    
#define UART0_BPS     38400

void initPWM1(void)
{
	LPC_PINCON->PINSEL4 |= (1<<8); // pwm1.5 => p2.4
	LPC_PWM1->MR0 = MR0_value;
	LPC_PWM1->MR4 = MR4_value;
	LPC_PWM1->MR5 = MR5_value;
	LPC_PWM1->MCR |= (1<<0 | 1<<1 | 1<<12 | 1<<15);  //Int & Reset MR0 , Int MR4,MR5
	LPC_PWM1->PCR |= (1<<5 | 1<<13 );	//enable 2 edge PW5 & En PW5
	LPC_PWM1->LER |= (1<<0 | 1<<4 | 1<<5);
	NVIC_EnableIRQ(PWM1_IRQn);
	LPC_PWM1->TCR |= (1<<0 | 1<<3);  // En Counter & PWM
}
/////////////////USART 0 Init //////////////////////////////
void UART0Init( uint32_t baudrate )
{
   	uint16_t usFdiv;
    LPC_PINCON->PINSEL0 |= (1 << 4);             /* Pin P0.10 used as TXD2 (Com0) */
    LPC_PINCON->PINSEL0 |= (1 << 6);             /* Pin P0.11 used as RXD2 (Com0) */
  	LPC_UART0->LCR = 0x83;        /* 8 bits, no Parity, 1 Stop bit */
    usFdiv = (FPCLK / 16) / UART0_BPS;           
    LPC_UART0->DLM  = usFdiv / 256;
    LPC_UART0->DLL  = usFdiv % 256; 
    LPC_UART0->LCR = 0x03;        /* DLAB = 0 */
    LPC_UART0->FCR = 0x06;        /* Enable and reset TX and RX FIFO. */
    LPC_UART0->TER = 0x80;        
}

void PWM1_IRQHandler(void)
{
	//MR0 Int service
	if((LPC_PWM1->IR>>0 & 0x1) == 0x1)	LPC_UART0->THR = 'S';
  //MR4 Int service	
	if((LPC_PWM1->IR>>8 & 0x1) == 0x1) 	LPC_UART0->THR = 'R';
	//MR5 Int service
	if((LPC_PWM1->IR>>9 & 0x1) == 0x1)	LPC_UART0->THR = 'F';
	LPC_PWM1->IR |= (1<<0 | 1<<8 |  1<<9);
}
////////////////////////////////////////////////////////////////////
int main(void)
{
	UART0Init( 38400 );
	initPWM1();
	while(1);
}
