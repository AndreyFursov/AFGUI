/*
 * guiText.c
 *
 *  Created on: 27.12.2012
 *      Author: Andrey
 */
#include "gui.h"



void guiDrawString(char * text, V_FONT *font, uint16_t len, uint16_t Xpos, uint16_t Ypos)
{
	uint32_t i, index;
	//pos = Xpos;
	i = 0;
	while (i < len
			&& (uint8_t)text[i] > font->Offset)
	{
		index = (uint8_t)text[i] - font->Offset;
		if (index > font->NumSymb) index = 0x3F-32;
		LCD_DrawChar(Xpos, Ypos, index);
		if (font->Width)
			Xpos += font->Width;
		else
			Xpos += (font->tableSymbWidth[index]+font->SymbolSpace);
		i++;
	}
}

uint32_t uint8toString(char * str, uint8_t value, uint16_t len, uint8_t format)
{
	uint8_t temp, index, bin, flag;
	index = 0;
	flag = 0;
	temp = 100;
	while (index < (len-1) && temp > 0)
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
	str[index] = 0;
	return (uint32_t)index;
}

uint32_t int16toString(char * str, int16_t value, uint16_t len, uint8_t format)
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
	str[index] = 0;
	return (uint32_t)index;
}

uint32_t int32toString(
						char * str,			//!< Pointer to output string
						int32_t value, 		//!< Input value
						uint16_t len, 		//!< String length limit
						uint8_t format		//!< Minimum num digit
						)
{
	uint32_t temp, index, bin, flag;
	uint8_t count;

	index = 0;
	flag = 0;
	if (value < 0)
	{
		str[index++] = '-';
		value = -value;
	}
	temp = 1000000000;
	count = 0;
	while (index < (len-1) && temp > 0)
	{
		bin = 0;
		if (format)
		{
			count++;
			if (10-count < format) flag = 1;
		}
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
	str[index] = 0;
	return index;
}

uint32_t uint32toString(char * str, uint32_t value, uint16_t len, uint8_t format)
{
	uint32_t temp, index, bin, flag;

	index = 0;
	flag = 0;
	temp = 1000000000;
	while (index < (len-1) && temp > 0)
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
	str[index] = 0;
	return index;
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

uint32_t uint32toTime(char * str, uint32_t value, uint16_t len, uint8_t format)
{
	// format == 0 hh:mm:ss
	// format == 1 (h):mm:ss



	uint32_t hour, i;
	uint8_t min;
	uint8_t sec;

	hour = value/3600;
	min = (value-hour*3600)/60;
	sec = value - min*60 - hour*3600;
	i = uint32toString(str, hour, len, 0);
	if (i < len) str[i++] = ':';
	if (i < len) str[i++] = min/10 + 0x30;
	if (i < len) str[i++] = (min - (min/10)*10) + 0x30;
	if (i < len) str[i++] = ':';
	if (i < len) str[i++] = sec/10 + 0x30;
	if (i < len) str[i++] = (sec - (sec/10)*10) + 0x30;
	if (i < len) str[i] = 0;
	return i;

}
