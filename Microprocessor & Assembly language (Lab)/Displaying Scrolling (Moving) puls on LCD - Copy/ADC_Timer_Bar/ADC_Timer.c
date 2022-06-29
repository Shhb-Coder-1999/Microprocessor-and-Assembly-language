/******************************************************************************/
/* Blinky.c: LED Flasher and graphic demo                                     */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "stdlib.h"
#include "GLCD.h"
int i=0,j=0,k=0;











#define MR2_Value_High 12500000
#define MR2_Value_Low 1000000
#define PR0_Value 0

struct puls{
	unsigned int x;
	unsigned int y;
	unsigned int INT;
};

int state=1;

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
struct puls verticalline[140];
struct puls squar[319];
void TIMER2_IRQHandler(){
	LPC_TIM2->IR =  1<<2;                     //Clr INT Flag
	
	for (int i =0 ; i<140;i++){
		verticalline[i].y = 60+i;
		verticalline[i].x = 319;
	}
	squar[0].INT = 1;

	if (state) {
		state = 0;
	}
	else
	{
		state = 1;
	}

};





int main (void){                       /* Main Program                       */
	
	
	
	Init_Timer2();
//  SystemInit();
//  SysTick_Config(25000000/100);  /* Generate interrupt every 10 ms     */

  GLCD_Init   ();
  GLCD_Clear  (White);
	GLCD_SetTextColor (Yellow);
	GLCD_SetBackColor (Navy);
	
	while(1)
	{		
		
				
		if (state==1){
			for (j=0 ; j<318;j++){
				squar[j+1]=squar[j]
				squar[j+1].x --;
			}
			squar[0].x = 319;
			squar[0].y = 200;
			
		}
		else {
			for (int j=0 ; j<318;j++){
				squar[j+1]=squar[j]
				squar[j+1].x --;
			}
			squar[0].x = 319;
			squar[0].y = 60;
			
		}
		
		for (int j =0; j<140;j++){
				verticalline[j].x --;
		}		
		
		for(int i=0;i<319;i++){
			if (!squar[i].INT){
				
				GLCD_PutPixel(squar[i].x,squar[i].y);
			}
			else {					
				for (int i =0 ; i<140;i++){		
					GLCD_PutPixel(verticalline[i].x,verticalline[i].y);
				}
			}
		}

	}
		
		
			
		
		
			
			
	}
}
	

                            
/* GLCD RGB color definitions                                                 */

#define Black           0x0000		  /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */


extern void GLCD_Init           (void);
extern void GLCD_WindowMax      (void);
extern void GLCD_PutPixel       (unsigned int x, unsigned int y);  // x=0-319 y=0-239
extern void GLCD_SetTextColor   (unsigned short color);
/*
extern void GLCD_SetBackColor   (unsigned short color);
extern void GLCD_Clear          (unsigned short color);
extern void GLCD_DrawChar       (unsigned int x, unsigned int y, unsigned short *c);
extern void GLCD_DisplayChar    (unsigned int ln, unsigned int col, unsigned char  c);  // ln=0-9 col=0-19
extern void GLCD_DisplayString  (unsigned int ln, unsigned int col, unsigned char *s);	// ln=0-9 col=0-19
extern void GLCD_ClearLn        (unsigned int ln,unsigned int col);	// ln=0-9
extern void GLCD_Bargraph       (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int val);	// x=0-319 y=0-239 , w=0-319 h=0-19 val=0-1024
extern void GLCD_Box       (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
extern void GLCD_Line (unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2); 
extern void LCD_DrawPoint (unsigned short x,unsigned short y ); 
extern void LCD_SetCursor(unsigned short Xpos, unsigned short Ypos);


extern void GLCD_Bitmap         (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);
extern void GLCD_Bmp            (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bmp);

#endif /* _GLCD_H */


