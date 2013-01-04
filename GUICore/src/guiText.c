/*
 * guiText.c
 *
 *  Created on: 27.12.2012
 *      Author: Andrey
 */
#include "gui.h"

void guiDrawString(uint8_t * text, V_FONT *font, uint16_t len, uint16_t Xpos, uint16_t Ypos)
{
	uint32_t i, index;
	//pos = Xpos;
	for (i = 0; i < len; i++)
	{
		index = text[i] - font->Offset;
		if (index > font->NumSymb) index = 0x3F-32;
		LCD_DrawChar(Xpos, Ypos, index);
		if (font->Width)
			Xpos += font->Width;
		else
			Xpos += (font->tableSymbWidth[index]+font->SymbolSpace);
	}
}

void int16toString(uint8_t *str, int16_t value, uint16_t len, uint8_t format)
{
	int16_t temp, index, bin, flag;
	index = 0;
	flag = 0;
	if (value < 0)
	{
		str[index++] = '-';
		value = -value;
	}
	temp = 10000;
	while (index < (len-1) && value >= 0 && temp > 0)
	{
		bin = 0;
		while (value >= temp)
		{
			flag = 1;
			value -= temp;
			bin++;
		}
		if (flag || (temp == 1))
			str[index++] = bin + 0x30;
		temp /= 10;
	}
	str[index++] = 0;
}

void LCD_ASCII(V_FONT * vFont)
{
	uint16_t i, xPos, yPos, width;
	xPos = 0; yPos = 0;

	for (i = 0; i < vFont->NumSymb; i++)
	{
		//LCD_DisplayChar(xPos, yPos, (uint8_t)i);
		LCD_DrawChar(xPos, yPos, i);
		if (vFont->Width)
			width = vFont->Width;
		else
			width = vFont->tableSymbWidth[i]+1;

			xPos += width;
		if ((xPos + width) > (LCD_PIXEL_WIDTH ))
		{
			xPos = 0;
			yPos += vFont->Height;
			if ((yPos + vFont->Height) > ((LCD_PIXEL_HEIGHT)))
			{
				i = 256;
			}
		}
	}
}
