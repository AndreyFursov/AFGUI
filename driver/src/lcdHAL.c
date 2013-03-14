/*
 * lcdHAL.c
 *
 *  Created on: 08.01.2013
 *      Author: Andrey Fursov
 */

#include "gui.h"

const uint16_t std16Palette[] = 
{
			//					  R G B
	((0x000000>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x000000>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x000000 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< White			0x000000
	((0x00FFFF>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x00FFFF>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x00FFFF )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Teal			0x00FFFF
	((0xFF00FF>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0xFF00FF>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0xFF00FF )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Purple			0xFF00FF
	((0x0000FF>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x0000FF>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x0000FF )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Blue			0x0000FF

	((0xC0C0C0>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0xC0C0C0>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0xC0C0C0 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Light gray		0xC0C0C0
	((0x808080>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x808080>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x808080 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark gray		0x808080
	((0x008080>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x008080>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x008080 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark teal		0x008080
	((0x800080>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x800080>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x800080 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark purple	0x800080

	((0x000080>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x000080>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x000080 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark blue		0x000080
	((0xFFFF00>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0xFFFF00>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0xFFFF00 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Yellow			0xFFFF00
	((0x00FF00>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x00FF00>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x00FF00 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Green			0x00FF00
	((0x808000>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x808000>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x808000 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark Yllow		0x808000

	((0x008000>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x008000>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x008000 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark green		0x008000
	((0xFF0000>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0xFF0000>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0xFF0000 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Red			0xFF0000
	((0x800000>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x800000>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x800000 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET,	//!< Dark red		0x800000
	((0x000000>>24)&COLOR_RED_MASK)<<COLOR_RED_OFFSET | ((0x000000>>16)&COLOR_GREEN_MASK)<<COLOR_GREEN_OFFSET | ((0x000000 )&COLOR_BLUE_MASK)<<COLOR_BLUE_OFFSET	//!< Black			0x000000
};

V_FONT * LCD_Currentfonts;
volatile uint16_t TextColor;
volatile uint16_t BackColor;


//********************************************************
// Functions
//********************************************************

//******************************************************************************
// Color function

//! Set color for Text (Line) and Back
/**


*/
void LCD_SetColors(volatile uint16_t _TextColor, volatile uint16_t _BackColor)
{
  TextColor = _TextColor;
  BackColor = _BackColor;
}

void LCD_GetColors(volatile uint16_t *_TextColor, volatile uint16_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}

void LCD_SetTextColor(volatile uint16_t Color)
{
  TextColor = Color;
}

void LCD_SetBackColor(volatile uint16_t Color)
{
  BackColor = Color;
}

//******************************************************************************
// Font functions
void LCD_SetFont(V_FONT *fonts)
{
  LCD_Currentfonts = fonts;
}

V_FONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}






void LCD_SetWindow (uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy)
{
	if (startx > LCD_PIXEL_WIDTH-1 || endx > LCD_PIXEL_WIDTH-1
		|| starty > LCD_PIXEL_HEIGHT-1 || endy > LCD_PIXEL_HEIGHT-1 )
	{
		startx = 0;
		endx = 0;
		starty = 0;
		endy = 0;
	}
	LCD_WriteReg(0x0002,startx>>8);
	LCD_WriteReg(0x0003,startx);
	LCD_WriteReg(0x0004,endx>>8);
	LCD_WriteReg(0x0005,endx);
	LCD_WriteReg(0x0006,starty>>8);
	LCD_WriteReg(0x0007,starty);
	LCD_WriteReg(0x0008,endy>>8);
	LCD_WriteReg(0x0009,endy);
}


//********************************************************
//********************************************************
//********************************************************

void LCD_PutPixel(uint16_t x, uint16_t y)
{
	LCD_SetWindow (x,y, x, y);
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(TextColor);
	LCD_WriteRAM(0);
}



void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar)
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
				LCD_WriteRAM(0);
			}
			else
			{
				LCD_WriteRAM(BackColor);
				LCD_WriteRAM(0);
			}
			bitCounter++;
		}
		// Add space
		for (i = 0; i < LCD_Currentfonts->SymbolSpace; i++)
		{
			LCD_WriteRAM(BackColor);
			LCD_WriteRAM(0);
		}
	}
}

void LCD_DrawFillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t i, num;

	LCD_SetWindow (Xpos,Ypos,Xpos+Width-1,Ypos+Height-1);
	LCD_WriteRAM_Prepare();

	num = Width*Height;
	for(i = 0; i < num; i++)
	{
		LCD_WriteRAM(TextColor);
		LCD_WriteRAM(0);
	}
}


void LCD_DrawMonoPict(const uint32_t *Pict)
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
				LCD_WriteRAM(BackColor);
				LCD_WriteRAM(0);
			}
			else
			{
				LCD_WriteRAM(TextColor);
				LCD_WriteRAM(0);
			}
		}
	}
}

void LCD_WriteBMP(uint32_t BmpAddress)
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


void LCD_WriteBitmap(uint16_t * data, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
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
// LCD DEM240320H_TMH-PW-N (A-TOUCH) HX8347A initialization
//********************************************************

//********************************************************

void LCD_Init(void)
{
	volatile uint32_t lcdid = 0;

//	uint32_t i;
	uint16_t regValue;
	regValue = 0xA8;
	LCD_CtrlLinesConfig();
	LCD_FSMCConfig();

    LCD_Reset_Off();
    guiDelay_ms(10);
    LCD_Reset_On();
    guiDelay_ms(10);
    LCD_Reset_Off();
    guiDelay_ms(250);

	// Gamms set
	LCD_WriteReg(0x0046,0x0095);
	LCD_WriteReg(0x0047,0x0051);
	LCD_WriteReg(0x0048,0x0000);
	LCD_WriteReg(0x0049,0x0036);
	LCD_WriteReg(0x004A,0x0011);
	LCD_WriteReg(0x004B,0x0066);
	LCD_WriteReg(0x004C,0x0014);
	LCD_WriteReg(0x004D,0x0077);
	LCD_WriteReg(0x004E,0x0013);
	LCD_WriteReg(0x004F,0x004C);
	LCD_WriteReg(0x0050,0x0046);
	LCD_WriteReg(0x0051,0x0046);

	// 240x320 Window setting
	LCD_WriteReg(0x0002,0x0000);
	LCD_WriteReg(0x0003,0x0000);
	LCD_WriteReg(0x0004,0x0000);
	LCD_WriteReg(0x0005,0x00EF);
	LCD_WriteReg(0x0006,0x0000);
	LCD_WriteReg(0x0007,0x0000);
	LCD_WriteReg(0x0008,0x0001);
	LCD_WriteReg(0x0009,0x003F);
	LCD_WriteReg(0x0090,0x007F);

	// Display setting
	LCD_WriteReg(0x0001,0x0006);
	LCD_WriteReg(0x0016,regValue);
	LCD_WriteReg(0x0023,0x0095);
	LCD_WriteReg(0x0024,0x0095);
	LCD_WriteReg(0x0025,0x00FF);
	LCD_WriteReg(0x0027,0x0006);
	LCD_WriteReg(0x0028,0x0006);
	LCD_WriteReg(0x0029,0x0006);
	LCD_WriteReg(0x002A,0x0006);
	LCD_WriteReg(0x002C,0x0006);
	LCD_WriteReg(0x002D,0x0006);
	LCD_WriteReg(0x003A,0x0001);
	LCD_WriteReg(0x003B,0x0001);
	LCD_WriteReg(0x003C,0x00F0);
	LCD_WriteReg(0x003D,0x0000);
	guiDelay_ms(100);
	LCD_WriteReg(0x0010,0x00A6);

	// Power Supply Setting
	LCD_WriteReg(0x0019,0x0049);
	guiDelay_ms(100);
	LCD_WriteReg(0x0093,0x000C);
	guiDelay_ms(200);
	LCD_WriteReg(0x0020,0x0040);
	LCD_WriteReg(0x001D,0x0007);
	LCD_WriteReg(0x001E,0x0000);
	LCD_WriteReg(0x001F,0x0004);
	LCD_WriteReg(0x0044,0x004D);
	LCD_WriteReg(0x0045,0x0011);
	guiDelay_ms(200);
	LCD_WriteReg(0x001C,0x0004);
	guiDelay_ms(200);
	LCD_WriteReg(0x0043,0x0080);
	guiDelay_ms(100);
	LCD_WriteReg(0x001B,0x0018);
	guiDelay_ms(200);
	LCD_WriteReg(0x001B,0x0010);
	guiDelay_ms(200);

	// Display On setting
	LCD_WriteReg(0x0026,0x0004);
	guiDelay_ms(200);
	LCD_WriteReg(0x0026,0x0024);
	guiDelay_ms(40);
	LCD_WriteReg(0x0026,0x002C);
	guiDelay_ms(200);
	LCD_WriteReg(0x0026,0x003C);
	LCD_WriteReg(0x0035,0x0038);
	LCD_WriteReg(0x0036,0x0078);
	LCD_WriteReg(0x003E,0x0038);
	LCD_WriteReg(0x0040,0x000F);
	LCD_WriteReg(0x0041,0x00F0);

	// Set Spulse Rpulse
	LCD_WriteReg(0x0057,0x0002);
	LCD_WriteReg(0x0056,0x0084);
	LCD_WriteReg(0x0057,0x0000);

	LCD_Clear(LCD_COLOR_GREYL);
	LCD_SetFont(&LCD_DEFAULT_FONT);
}
