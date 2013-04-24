/*
 * lcdHAL_ILI9320.c
 *
 *  Created on: 08.04.2013
 *      Author: Andrey Fursov
 */

#include "gui.h"
#include "lcdHAL_ILI9320.h"

//#define WIDTH_ILI9320       320                 /* Screen Width (in pixels)           */
//#define HEIGHT_ILI9320      240                 /* Screen Hight (in pixels)           */


extern V_FONT * LCD_Currentfonts;
extern volatile uint32_t TextColor;
extern volatile uint32_t BackColor;



//********************************************************
// Functions
//********************************************************


void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD_WriteReg(0x21, Xpos);
	LCD_WriteReg(0x20, Ypos);
}



void LCD_SetWindow_ILI9320 (uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy)
{
	if (startx > LCD_PIXEL_WIDTH-1 || endx > LCD_PIXEL_WIDTH-1
		|| starty > LCD_PIXEL_HEIGHT-1 || endy > LCD_PIXEL_HEIGHT-1 )
	{
		startx = 0;
		endx = 0;
		starty = 0;
		endy = 0;
	}
	LCD_WriteReg(0x52, startx);
	LCD_WriteReg(0x53, endx);
	LCD_WriteReg(0x50, starty);
	LCD_WriteReg(0x51, endy);
	LCD_SetCursor(startx, starty);	
}


//********************************************************
//********************************************************
//********************************************************

void LCD_PutPixel_ILI9320(uint16_t x, uint16_t y)
{
	LCD_SetWindow (x,y, x, y);
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(TextColor);
}



void LCD_DrawChar_ILI9320(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar)
{
	uint32_t index = 0, i = 0, numByte, width, bitCounter, ptrByte;
	// Symbol width
	if (codeChar > LCD_Currentfonts->NumSymb) codeChar = 0;
	if (LCD_Currentfonts->Width)
	{
		width = LCD_Currentfonts->Width;
		LCD_SetWindow(Xpos, Ypos, Xpos+width, Ypos+LCD_Currentfonts->Height-1);
	}
	else
	{
		width = LCD_Currentfonts->tableSymbWidth[codeChar];
		LCD_SetWindow(Xpos, Ypos, Xpos+width+LCD_Currentfonts->SymbolSpace-1, Ypos+LCD_Currentfonts->Height-1);
	}
	numByte = LCD_Currentfonts->Height * ((width+7)/8);

	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	// Draw Char
	for(index = 0; index < numByte; index++)
	{
		bitCounter = 0;
		for(i = 0; i < width; i++)
		{

			if (bitCounter > 7)
			{
				bitCounter = 0;
				index++;
			}
			ptrByte = LCD_Currentfonts->table[LCD_Currentfonts->tableSymbIndex[codeChar]+index];
			if(ptrByte & (1<<bitCounter))
			{
				LCD_WriteRAM(TextColor);
			}
			else
			{
				LCD_WriteRAM(BackColor);
			}
			bitCounter++;
		}
		// Add space
		for (i = 0; i < LCD_Currentfonts->SymbolSpace; i++)
		{
			LCD_WriteRAM(BackColor);
		}
	}
}

void LCD_DrawFillRect_ILI9320(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t i, num;

	LCD_SetWindow (Xpos,Ypos,Xpos+Width-1,Ypos+Height-1);
	LCD_WriteRAM_Prepare();

	num = Width*Height;
	for(i = 0; i < num; i++)
	{
		LCD_WriteRAM(TextColor);
	}
}


void LCD_DrawMonoPict_ILI9320(const uint32_t *Pict)
{
	uint32_t index = 0, i = 0;

	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for(index = 0; index < 2400; index++)
	{
		for(i = 0; i < 32; i++)
		{
			if((Pict[index] & (1 << i)) == 0x00)
			{
				LCD_WriteRAM(BackColor);
			}
			else
			{
				LCD_WriteRAM(TextColor);
			}
		}
	}
}

void LCD_WriteBMP_ILI9320(uint32_t BmpAddress)
{
	uint32_t index = 0, size = 0;
	/* Read bitmap size */
	size = *(volatile uint16_t *) (BmpAddress + 2);
	size |= (*(volatile uint16_t *) (BmpAddress + 4)) << 16;
	/* Get bitmap data address offset */
	index = *(volatile uint16_t *) (BmpAddress + 10);
	index |= (*(volatile uint16_t *) (BmpAddress + 12)) << 16;
	size = (size - index)/2;
	BmpAddress += index;
	/* Set GRAM write direction and BGR = 1 */
	/* I/D=00 (Horizontal : decrement, Vertical : decrement) */
	/* AM=1 (address is updated in vertical writing direction) */
	//LCD_WriteReg(LCD_REG_3, 0x1008);

	LCD_WriteRAM_Prepare();

	for(index = 0; index < size; index++)
	{
		LCD_WriteRAM(*(volatile uint16_t *)BmpAddress);
		BmpAddress += 2;
	}


}


void LCD_WriteBitmap_ILI9320(uint16_t * data, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t num, i;
	LCD_SetWindow (Xpos, Ypos, Xpos+Width-1, Ypos+Height-1);
	LCD_WriteRAM_Prepare();

	num = (uint32_t)Width*(uint32_t)Height;
	for(i = 0; i < num; i++)
	{
		LCD_WriteRAM(data[i]);
	}
}











//********************************************************


//********************************************************
// LCD DEM240320H_TMH-PW-N (A-TOUCH) HX8347A initialization
//********************************************************

//********************************************************

void LCD_Init_ILI9320(void)
{
//	LCD_WriteReg(0x00,0x0001);
//    guiDelay_ms(150);
//	  guiDelay_ms(50); /* delay 50 ms */

	LCD_WriteReg(0xE5, 0x8000);                 /* Set the internal vcore voltage     */
	LCD_WriteReg(0x00, 0x0001);                 /* Start internal OSC                 */
	LCD_WriteReg(0x01, 0x0000);                 /* Set SS and SM bit                  */
	LCD_WriteReg(0x02, 0x0700);                 /* Set 1 line inversion               */
	LCD_WriteReg(0x03, 0x1030);                 /* Set GRAM write direction and BGR=1 */
	LCD_WriteReg(0x04, 0x0000);                 /* Resize register                    */
	LCD_WriteReg(0x08, 0x0202);                 /* 2 lines each, back and front porch */
	LCD_WriteReg(0x09, 0x0000);                 /* Set non-disp area refresh cyc ISC  */
	LCD_WriteReg(0x0A, 0x0000);                 /* FMARK function                     */
	LCD_WriteReg(0x0C, 0x0000);                 /* RGB interface setting              */
	LCD_WriteReg(0x0D, 0x0000);                 /* Frame marker Position              */
	LCD_WriteReg(0x0F, 0x0000);                 /* RGB interface polarity             */
	
	/* Power On sequence -------------------------------------------------------*/
	LCD_WriteReg(0x10, 0x0000);                 /* Reset Power Control 1              */
	LCD_WriteReg(0x11, 0x0000);                 /* Reset Power Control 2              */
	LCD_WriteReg(0x12, 0x0000);                 /* Reset Power Control 3              */
	LCD_WriteReg(0x13, 0x0000);                 /* Reset Power Control 4              */
	guiDelay_ms(200);                            /* Discharge cap power voltage (200ms)*/
	LCD_WriteReg(0x10, 0x17B0);                 /* SAP, BT[3:0], AP, DSTB, SLP, STB   */
	LCD_WriteReg(0x11, 0x0137);                 /* DC1[2:0], DC0[2:0], VC[2:0]        */
	guiDelay_ms(50);                             /* Delay 50 ms                        */
	LCD_WriteReg(0x12, 0x0139);                 /* VREG1OUT voltage                   */
	guiDelay_ms(50);                             /* Delay 50 ms                        */
	LCD_WriteReg(0x13, 0x1D00);                 /* VDV[4:0] for VCOM amplitude        */
	LCD_WriteReg(0x29, 0x0013);                 /* VCM[4:0] for VCOMH                 */
	guiDelay_ms(50);                             /* Delay 50 ms                        */
	LCD_WriteReg(0x20, 0x0000);                 /* GRAM horizontal Address            */
	LCD_WriteReg(0x21, 0x0000);                 /* GRAM Vertical Address              */
	
	/* Adjust the Gamma Curve --------------------------------------------------*/
	LCD_WriteReg(0x30, 0x0006);
	LCD_WriteReg(0x31, 0x0101);
	LCD_WriteReg(0x32, 0x0003);
	LCD_WriteReg(0x35, 0x0106);
	LCD_WriteReg(0x36, 0x0B02);
	LCD_WriteReg(0x37, 0x0302);
	LCD_WriteReg(0x38, 0x0707);
	LCD_WriteReg(0x39, 0x0007);
	LCD_WriteReg(0x3C, 0x0600);
	LCD_WriteReg(0x3D, 0x020B);
	
	/* Set GRAM area -----------------------------------------------------------*/
	LCD_WriteReg(0x50, 0x0000);                 /* Horizontal GRAM Start Address      */
	LCD_WriteReg(0x51, (LCD_PIXEL_HEIGHT-1));             /* Horizontal GRAM End   Address      */
	LCD_WriteReg(0x52, 0x0000);                 /* Vertical   GRAM Start Address      */
	LCD_WriteReg(0x53, (LCD_PIXEL_WIDTH-1));              /* Vertical   GRAM End   Address      */
	LCD_WriteReg(0x60, 0x2700);                 /* Gate Scan Line                     */
	LCD_WriteReg(0x61, 0x0001);                 /* NDL,VLE, REV                       */
	LCD_WriteReg(0x6A, 0x0000);                 /* Set scrolling line                 */
	
	/* Partial Display Control -------------------------------------------------*/
	LCD_WriteReg(0x80, 0x0000);
	LCD_WriteReg(0x81, 0x0000);
	LCD_WriteReg(0x82, 0x0000);
	LCD_WriteReg(0x83, 0x0000);
	LCD_WriteReg(0x84, 0x0000);
	LCD_WriteReg(0x85, 0x0000);
	
	/* Panel Control -----------------------------------------------------------*/
	LCD_WriteReg(0x90, 0x0010);
	LCD_WriteReg(0x92, 0x0000);
	LCD_WriteReg(0x93, 0x0003);
	LCD_WriteReg(0x95, 0x0110);
	LCD_WriteReg(0x97, 0x0000);
	LCD_WriteReg(0x98, 0x0000);
	
	/* Set GRAM write direction and BGR = 1
	 I/D=10 (Horizontal : increment, Vertical : increment)
	 AM=1 (address is updated in vertical writing direction)                  */
	LCD_WriteReg(0x03, 0x1038);
	LCD_WriteReg(0x07, 0x0173);                 /* 262K color and display ON          */
}
