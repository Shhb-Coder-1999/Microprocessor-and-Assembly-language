/******************************************************************************/
/* GLCD.c: Functions for Graphic LCD (320x240 pixels) driving for NXP LPC17xx */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2009 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdlib.h>
#include <string.h>

#ifndef _GLCD_H
#define _GLCD_H


/*********************** Hardware specific configuration **********************/

/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N    18

/*---------------------- Graphic LCD size definitions ------------------------*/

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

/*--------------- Graphic LCD interface hardware definitions -----------------*/

#define SSP_START   (0x70)              /* Start byte for SSP transfer        */
#define SSP_RD      (0x01)              /* WR bit 1 within start              */
#define SSP_WR      (0x00)              /* WR bit 0 within start              */
#define SSP_DATA    (0x02)              /* RS bit 1 within start byte         */
#define SSP_INDEX   (0x00)              /* RS bit 0 within start byte         */
 
/*---------------------------- Global variables ------------------------------*/

/******************************************************************************/


/************************ Local auxiliary functions ***************************/

/*******************************************************************************
* Delay in while loop cycles                                                   *
*   Parameter:    cnt:    number of while cycles to delay                      *
*   Return:                                                                    *
*******************************************************************************/

static void delay (int cnt) {

  cnt <<= DELAY_2N;
  while (cnt--);
}


/*******************************************************************************
* Send 1 byte over serial communication                                        *
*   Parameter:    byte:   byte to be sent                                      *
*   Return:                                                                    *
*******************************************************************************/

static __inline unsigned char ssp_send (unsigned char byte) {

  LPC_SSP1->DR = byte;
  while (LPC_SSP1->SR & (1 << 4));      /* Wait for transfer to finish        */
  return (LPC_SSP1->DR);                /* Return received value              */
}


/*******************************************************************************
* Write command to LCD controller                                              *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_cmd (unsigned char c) {

  LPC_GPIO0->FIOPIN &= ~(1 << 6);
  ssp_send(SSP_START | SSP_WR | SSP_INDEX);   /* Write : RS = 0, RW = 0       */
  ssp_send(0);
  ssp_send(c);
  LPC_GPIO0->FIOPIN |=  (1 << 6);
}


/*******************************************************************************
* Write data to LCD controller                                                 *
*   Parameter:    c:      data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_dat (unsigned short c) {

  LPC_GPIO0->FIOPIN &= ~(1 << 6);
  ssp_send(SSP_START | SSP_WR | SSP_DATA);    /* Write : RS = 1, RW = 0       */
  ssp_send((c >>   8));                       /* Write D8..D15                */
  ssp_send((c & 0xFF));                       /* Write D0..D7                 */
  LPC_GPIO0->FIOPIN |=  (1 << 6);
}


/*******************************************************************************
* Read data from LCD controller                                                *
*   Parameter:                                                                 *
*   Return:               read data                                            *
*******************************************************************************/

static __inline unsigned short rd_dat (void) {
  unsigned short val = 0;

  LPC_GPIO0->FIOPIN &= ~(1 << 6);
  ssp_send(SSP_START | SSP_RD | SSP_DATA);    /* Read: RS = 1, RW = 1         */
  ssp_send(0);                                /* Dummy read                   */
  val   = ssp_send(0);                        /* Read D8..D15                 */
  val <<= 8;
  val  |= ssp_send(0);                        /* Read D0..D7                  */
  LPC_GPIO0->FIOPIN |=  (1 << 6);
  return (val);
}

/*******************************************************************************
* Write to LCD register                                                        *
*   Parameter:    reg:    register to be read                                  *
*                 val:    value to write to register                           *
*******************************************************************************/

static __inline void wr_reg (unsigned char reg, unsigned short val) {

  wr_cmd(reg);
  wr_dat(val);
}


/*******************************************************************************
* Read from LCD register                                                       *
*   Parameter:    reg:    register to be read                                  *
*   Return:               value read from register                             *
*******************************************************************************/

static unsigned short rd_reg (unsigned char reg) {

  wr_cmd(reg);
  return (rd_dat());
}


/************************ Exported functions **********************************/

/*******************************************************************************
* Initialize the Graphic LCD controller                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_init (void) { 
  static unsigned short driverCode;

  /* Configure the LCD Control pins ------------------------------------------*/
  LPC_PINCON->PINSEL9 &= ~(3 << 24);    /* Pin P4.28 used for backlight       */
  LPC_GPIO4->FIODIR   |=  (1 << 28);    /* Pin P2.28 is output                */
  LPC_PINCON->PINSEL9 &= ~(3 << 26);    /* Pin P4.29 used for LCD CS          */
  LPC_GPIO4->FIODIR   |=  (1 << 29);    /* Pin P2.29 is output                */
  LPC_GPIO4->FIOPIN   |=  (1 << 29);    /* Pin P2.29 is high                  */

  /*-- SSP Configuration -----------------------------------------------------*/
  LPC_SC->PCONP       |=  (1 << 10);    /* Enable power to SSP1 block         */
  LPC_SC->PCLKSEL0    |=  (2 << 20);    /* SSP1 clock = CCLK / 2              */
  LPC_GPIO0->FIODIR   |=  (1 <<  6);    /* Pin P0.6 is GPIO output (SSEL1)    */
  LPC_GPIO0->FIOSET    =  (1 <<  6);    /* Set P0.6 high                      */
  LPC_PINCON->PINSEL0 &= ~0x000FC000;
  LPC_PINCON->PINSEL0 |=  0x000A8000;   /* Select SSP mode for SSP pins       */

  LPC_SSP1->CR0        =  (   1 << 7) | /* CPHA = 1                           */
                          (   1 << 6) | /* CPOL = 1                           */
                          (   0 << 4) | /* Frame format = SPI                 */
                          ((8-1)<< 0) ; /* Data size = 8 bits                 */
  LPC_SSP1->CPSR       =  2;            /* Clock Rate = 18MHz                 */
  LPC_SSP1->CR1        =  (   1 << 1);  /* Enable SSP1                        */

  delay(5);                             /* Delay 50 ms                        */
  driverCode = rd_reg(0x00);

  /* Start Initial Sequence --------------------------------------------------*/
  wr_reg(0xE5, 0x8000);                 /* Set the internal vcore voltage     */
  wr_reg(0x00, 0x0001);                 /* Start internal OSC                 */
  wr_reg(0x01, 0x0100);                 /* Set SS and SM bit                  */
  wr_reg(0x02, 0x0700);                 /* Set 1 line inversion               */
  wr_reg(0x03, 0x1030);                 /* Set GRAM write direction and BGR=1 */
  wr_reg(0x04, 0x0000);                 /* Resize register                    */
  wr_reg(0x08, 0x0202);                 /* 2 lines each, back and front porch */
  wr_reg(0x09, 0x0000);                 /* Set non-disp area refresh cyc ISC  */
  wr_reg(0x0A, 0x0000);                 /* FMARK function                     */
  wr_reg(0x0C, 0x0000);                 /* RGB interface setting              */
  wr_reg(0x0D, 0x0000);                 /* Frame marker Position              */
  wr_reg(0x0F, 0x0000);                 /* RGB interface polarity             */

  /* Power On sequence -------------------------------------------------------*/
  wr_reg(0x10, 0x0000);                 /* Reset Power Control 1              */
  wr_reg(0x11, 0x0000);                 /* Reset Power Control 2              */
  wr_reg(0x12, 0x0000);                 /* Reset Power Control 3              */
  wr_reg(0x13, 0x0000);                 /* Reset Power Control 4              */
  delay(20);                            /* Discharge cap power voltage (200ms)*/
  wr_reg(0x10, 0x17B0);                 /* SAP, BT[3:0], AP, DSTB, SLP, STB   */
  wr_reg(0x11, 0x0137);                 /* DC1[2:0], DC0[2:0], VC[2:0]        */
  delay(5);                             /* Delay 50 ms                        */
  wr_reg(0x12, 0x0139);                 /* VREG1OUT voltage                   */
  delay(5);                             /* Delay 50 ms                        */
  wr_reg(0x13, 0x1D00);                 /* VDV[4:0] for VCOM amplitude        */
  wr_reg(0x29, 0x0013);                 /* VCM[4:0] for VCOMH                 */
  delay(5);                             /* Delay 50 ms                        */
  wr_reg(0x20, 0x0000);                 /* GRAM horizontal Address            */
  wr_reg(0x21, 0x0000);                 /* GRAM Vertical Address              */

  /* Adjust the Gamma Curve --------------------------------------------------*/
  wr_reg(0x30, 0x0006);
  wr_reg(0x31, 0x0101);
  wr_reg(0x32, 0x0003);
  wr_reg(0x35, 0x0106);
  wr_reg(0x36, 0x0B02);
  wr_reg(0x37, 0x0302);
  wr_reg(0x38, 0x0707);
  wr_reg(0x39, 0x0007);
  wr_reg(0x3C, 0x0600);
  wr_reg(0x3D, 0x020B);
  
  /* Set GRAM area -----------------------------------------------------------*/
  wr_reg(0x50, 0x0000);                 /* Horizontal GRAM Start Address      */
  wr_reg(0x51, (HEIGHT-1));             /* Horizontal GRAM End   Address      */
  wr_reg(0x52, 0x0000);                 /* Vertical   GRAM Start Address      */
  wr_reg(0x53, (WIDTH-1));              /* Vertical   GRAM End   Address      */
  wr_reg(0x60, 0x2700);                 /* Gate Scan Line                     */
  wr_reg(0x61, 0x0001);                 /* NDL,VLE, REV                       */
  wr_reg(0x6A, 0x0000);                 /* Set scrolling line                 */

  /* Partial Display Control -------------------------------------------------*/
  wr_reg(0x80, 0x0000);
  wr_reg(0x81, 0x0000);
  wr_reg(0x82, 0x0000);
  wr_reg(0x83, 0x0000);
  wr_reg(0x84, 0x0000);
  wr_reg(0x85, 0x0000);

  /* Panel Control -----------------------------------------------------------*/
  wr_reg(0x90, 0x0010);
  wr_reg(0x92, 0x0000);
  wr_reg(0x93, 0x0003);
  wr_reg(0x95, 0x0110);
  wr_reg(0x97, 0x0000);
  wr_reg(0x98, 0x0000);

  /* Set GRAM write direction and BGR = 1
     I/D=10 (Horizontal : increment, Vertical : increment)
     AM=1 (address is updated in vertical writing direction)                  */
  wr_reg(0x03, 0x1038);

  wr_reg(0x07, 0x0173);                 /* 262K color and display ON          */
  LPC_GPIO4->FIOPIN   |=  (1 << 28);    /* Turn backlight on                  */
}


/*******************************************************************************
* Clear display                                                                *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_clear (unsigned short color) {
  unsigned int   i;

  wr_reg(0x20, 0);
  wr_reg(0x21, 0);
  wr_cmd(0x22);
  for(i = 0; i < (WIDTH*HEIGHT); i++)
    wr_dat(color);
}


/*******************************************************************************
* Display graphical bitmap image at position x horizontally and y vertically   *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bitmap:   address at which the bitmap data resides         *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_bitmap (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) {
  unsigned int   i;
  unsigned int   len = w*h;
  unsigned short *bitmap_ptr = (unsigned short *)bitmap;

  wr_reg(0x50, y);                      /* Horizontal GRAM Start Address      */
  wr_reg(0x51, y+h-1);                  /* Horizontal GRAM End   Address (-1) */
  wr_reg(0x52, x);                      /* Vertical   GRAM Start Address      */
  wr_reg(0x53, x+w-1);                  /* Vertical   GRAM End   Address (-1) */

  wr_reg(0x20, y);
  wr_reg(0x21, x);

  wr_cmd(0x22);
  for (i = 0; i < len; i++) {
    wr_dat(*bitmap_ptr++);
  }
}


#endif /* _GLCD_H */

/******************************************************************************/
