#include "lpc17xx.h"
#define high 14875
#define period 42500
#define Baudrate 38400
#define pclk 25000000 
//pwm5 -- > p2.4
//uart0 --> p0.0
int a[2] = {0x55 , 0x3A},i,b;
void init()
{
  i = 0;
  b = 0;
  NVIC_EnableIRQ(PWM1_IRQn);
  LPC_PWM1->LER |= (0x1) | (1<<5);
  LPC_PWM1->MR0 = period;
  LPC_PWM1->MR5 = high;
  LPC_PWM1->MCR |= 0x3 | 1<<15;
  LPC_PINCON->PINSEL4 |= 1<<8;
  LPC_PWM1->PCR |= 1<<13;
  

  LPC_PINCON->PINSEL0 |= 0x01<<4; //txd0 -- p0.2
  LPC_PINCON->PINSEL0 |= 0x01<<30; //txd1 -- p0.15
  LPC_PINCON->PINSEL0 |= 0x01<<20; //txd2 -- p0.10
  LPC_PINCON->PINSEL0 |= 0x10; //txd3 -- p0.0
  LPC_UART0->LCR = 0x80;
  LPC_UART0->DLM = ((pclk / 16) / Baudrate) / 256;
  LPC_UART0->DLL = ((pclk / 16) / Baudrate) % 256;
  LPC_UART0->LCR = 0x03;
}
void Send(char temp)
{
  while(!(LPC_UART0->LSR & 0x20));
  LPC_UART0->THR = temp;
}
void PWM1_IRQHandler()
{
  //3A
  if(LPC_PWM1->IR == 0x200)
  {
    LPC_PWM1->IR = 1<<9;
    Send(a[1]);
  }
  //55
  else
  {
    LPC_PWM1->IR = 0x1;
    Send(a[0]);
  }
}
int main()
{
  init();
  LPC_PWM1->TCR = 0x9;
  while(1);
}