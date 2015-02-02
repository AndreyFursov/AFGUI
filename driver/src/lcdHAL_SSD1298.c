/*
 * lcdHAL_SSD1298.c
 *
 *  Created on: 10.04.2013
 *      Author: Andrey Fursov
 */

#include "gui.h"
#include "lcdHAL_SSD1298.h"

extern V_FONT * LCD_Currentfonts;
extern volatile uint32_t TextColor;
extern volatile uint32_t BackColor;



void LCD_SetWindow_SSD1298(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy)
{
	if (startx > LCD_PIXEL_WIDTH-1 || endx > LCD_PIXEL_WIDTH-1
		|| starty > LCD_PIXEL_HEIGHT-1 || endy > LCD_PIXEL_HEIGHT-1 )
	{
		startx = 0;
		endx = 0;
		starty = 0;
		endy = 0;
	}
	LCD_WriteReg(0x0044,(starty&0xFF) | endy<<8);    /* Horizontal RAM start and end address */
	LCD_WriteReg(0x0045,startx);    /* Vretical RAM start address */
	LCD_WriteReg(0x0046,endx);    /* Vretical RAM end address */ 
//                LCD_WriteReg(0x004e,0x0000);    /* set GDDRAM x address counter */
//                LCD_WriteReg(0x004f,0x0000);    /* set GDDRAM y address counter */   
	/*
	LCD_WriteReg(0x52, startx);
	LCD_WriteReg(0x53, endx);
	LCD_WriteReg(0x50, starty);
	LCD_WriteReg(0x51, endy);
	*/
	
    LCD_WriteReg(0x004e, starty );      
	LCD_WriteReg(0x004f, startx );          
}

//********************************************************

void LCD_PutPixel_SSD1298(uint16_t x, uint16_t y)
{
	LCD_SetWindow(x, y, x, y);
	LCD_WriteRAM_Prepare();
	//LCD_WriteRAM(TextColor>>16);
	LCD_WriteRAM(TextColor);
}



void LCD_DrawChar_SSD1298(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar)
{
	uint32_t index = 0, i = 0, numByte, width, bitCounter, ptrByte;
	// Symbol width
	if (codeChar > LCD_Currentfonts->NumSymb) codeChar = 0;
	if (LCD_Currentfonts->Width)
	{
		width = LCD_Currentfonts->Width;
		LCD_SetWindow(Xpos, Ypos, Xpos+width-1, Ypos+LCD_Currentfonts->Height-1);
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
				//LCD_WriteRAM(TextColor>>16);
				LCD_WriteRAM(TextColor);
			}
			else
			{
				//LCD_WriteRAM(BackColor>>16);
				LCD_WriteRAM(BackColor);
			}
			bitCounter++;
		}
		// Add space
		for (i = 0; i < LCD_Currentfonts->SymbolSpace; i++)
		{
			//LCD_WriteRAM(BackColor>>16);
			LCD_WriteRAM(BackColor);
		}
	}
}

void LCD_DrawFillRect_SSD1298(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t i, num;

	LCD_SetWindow (Xpos,Ypos,Xpos+Width-1,Ypos+Height-1);
	LCD_WriteRAM_Prepare();

	num = Width*Height;
	for(i = 0; i < num; i++)
	{
		//LCD_WriteRAM(TextColor>>16);
		LCD_WriteRAM(TextColor);
	}
}


void LCD_DrawMonoPict_SSD1298(const uint32_t *Pict)
{
	uint32_t index = 0, i = 0;
	//LCD_SetCursor(0, 0);

	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for(index = 0; index < 2400; index++)
	{
		for(i = 0; i < 32; i++)
		{
			if((Pict[index] & (1 << i)) == 0x00)
			{
				//LCD_WriteRAM(BackColor>>16);
				LCD_WriteRAM(BackColor);
			}
			else
			{
				//LCD_WriteRAM(TextColor>>16);
				LCD_WriteRAM(TextColor);
			}
		}
	}
}

void LCD_WriteBMP_SSD1298(uint32_t BmpAddress)
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
		LCD_WriteRAM(0);
		BmpAddress += 2;
	}


}


void LCD_WriteBitmap_SSD1298(uint16_t * data, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t num, i;
	LCD_SetWindow (Xpos, Ypos, Xpos+Width-1, Ypos+Height-1);
	LCD_WriteRAM_Prepare();

	num = (uint32_t)Width*(uint32_t)Height;
	for(i = 0; i < num; i++)
	{
		LCD_WriteRAM(data[i]);
		LCD_WriteRAM(0);
	}
}











//********************************************************


//********************************************************
// LCD DEM240320H_TMH-PW-N (A-TOUCH) SSD1298 initialization
//********************************************************

//********************************************************

void LCD_Init_SSD1298(void)
{
	uint16_t x;
	LCD_WriteReg(0x0028,0x0006);
	LCD_WriteReg(0x0000,0x0001);
	LCD_WriteReg(0x0003,0xaea4);    /* power control 1---line frequency and VHG,VGL voltage */
	LCD_WriteReg(0x000c,0x0004);    /* power control 2---VCIX2 output voltage */
	LCD_WriteReg(0x000d,0x000c);    /* power control 3---Vlcd63 voltage */
	LCD_WriteReg(0x000e,0x2800);    /* power control 4---VCOMA voltage VCOML=VCOMH*0.9475-VCOMA */
	LCD_WriteReg(0x001e,0x00b5);    /* POWER CONTROL 5---VCOMH voltage */   
	x = 0x3b3f;
	x = 0x393f;
	LCD_WriteReg(0x0001,x); 
	LCD_WriteReg(0x0002,0x0600);
	LCD_WriteReg(0x0010,0x0000);
	//LCD_WriteReg(0x0011,0x6830);
	x = 0x6838;
	LCD_WriteReg(0x0011,x);
	LCD_WriteReg(0x0005,0x0000);
	LCD_WriteReg(0x0006,0x0000);
	LCD_WriteReg(0x0016,0xef1c);  
	LCD_WriteReg(0x0007,0x0033);    /* Display control 1 */
	/* when GON=1 and DTE=0,all gate outputs become VGL */
	/* when GON=1 and DTE=0,all gate outputs become VGH */
	/* non-selected gate wires become VGL */     
	LCD_WriteReg(0x000b,0x0000);
	LCD_WriteReg(0x000f,0x0000);
	LCD_WriteReg(0x0041,0x0000);
	LCD_WriteReg(0x0042,0x0000);
	LCD_WriteReg(0x0048,0x0000);
	LCD_WriteReg(0x0049,0x013f);
	LCD_WriteReg(0x004a,0x0000);
	LCD_WriteReg(0x004b,0x0000); 
	LCD_WriteReg(0x0044,0xef00);    /* Horizontal RAM start and end address */
	LCD_WriteReg(0x0045,0x0000);    /* Vretical RAM start address */
	LCD_WriteReg(0x0046,0x013f);    /* Vretical RAM end address */ 
	LCD_WriteReg(0x004e,0x0000);    /* set GDDRAM x address counter */
	LCD_WriteReg(0x004f,0x0000);    /* set GDDRAM y address counter */   
	/* y control */
	LCD_WriteReg(0x0030,0x0707);
	LCD_WriteReg(0x0031,0x0202);
	LCD_WriteReg(0x0032,0x0204);
	LCD_WriteReg(0x0033,0x0502);
	LCD_WriteReg(0x0034,0x0507);
	LCD_WriteReg(0x0035,0x0204);
	LCD_WriteReg(0x0036,0x0204);
	LCD_WriteReg(0x0037,0x0502);
	LCD_WriteReg(0x003a,0x0302);
	LCD_WriteReg(0x003b,0x0302); 
	LCD_WriteReg(0x0023,0x0000);
	LCD_WriteReg(0x0024,0x0000);
	LCD_WriteReg(0x0025,0x8000);
	LCD_WriteReg(0x0026,0x7000);
	LCD_WriteReg(0x0020,0xb0eb);
	LCD_WriteReg(0x0027,0x007c);
}
