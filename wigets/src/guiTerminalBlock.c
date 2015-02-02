/*
 * guiTerminalBlock.c
 *
 *  Created on: 15.06.2013
 *      Author: Andrey Fursov
 */
#include "gui.h"
// default initialization terminal block
void defaultTerminalBlockInit(GUI_TERMINAL_BLOCK * tBlock, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	tBlock->wmObj.xPos 		= x;
	tBlock->wmObj.yPos 		= y;
	tBlock->wmObj.Width 	= width;
	tBlock->wmObj.Height 	= height;

	if (tBlock->vFont == 0)
	{
		tBlock->vFont = &GS_Lucida_12;
	}

	tBlock->TextColor			= LCD_COLOR_WHITE;
	tBlock->wmObj.Color 		= LCD_COLOR_BLACK;
	tBlock->wmObj.BorderColor 	= LCD_COLOR_WHITE;
	tBlock->wmObj.BorderWidth 	= 1;

	tBlock->qString = (tBlock->wmObj.Height - 2*tBlock->wmObj.BorderWidth - 2)/tBlock->vFont->Height;
	tBlock->qSymb = (tBlock->wmObj.Width - 2*tBlock->wmObj.BorderWidth - 2)/(tBlock->vFont->Width + tBlock->vFont->SymbolSpace);
	tBlock->countString = 0;
	tBlock->startString = 0;

	tBlock->wmObj.Visible 	= 0;
	tBlock->wmObj.Enable 	= 0;
};

void TerminalBlockOnPait(GUI_TERMINAL_BLOCK * tBlock)
{
	wmObjOnPaint(&tBlock->wmObj);
	TerminalBlockStringDraw(tBlock);
};

void TerminalBlockStringDraw(GUI_TERMINAL_BLOCK * tBlock)
{
	uint16_t i, x, y, index;
	if (tBlock->wmObj.Visible)
	{
		x = tBlock->wmObj.xPos + tBlock->wmObj.BorderWidth + 1;
		y = tBlock->wmObj.yPos + tBlock->wmObj.BorderWidth + 1;
		index  = tBlock->startString;
		LCD_SetColors(tBlock->TextColor, tBlock->wmObj.Color);
		if (tBlock->strings)
		{
			for (i = 0; i < tBlock->countString; i++)
			{
				guiDrawString(tBlock->strings[index], tBlock->vFont, tBlock->qSymb, x, y);
				y += tBlock->vFont->Height;
				index++;
				if (index >= tBlock->qString) index = 0;
			}
		}
	}
}

void TerminalBlockClear(GUI_TERMINAL_BLOCK * tBlock)
{
	tBlock->countString = 0;
	tBlock->startString = 0;
};

uint16_t TerminalBlockSetNewString(GUI_TERMINAL_BLOCK * tBlock)
{
	uint16_t j, curStr;
	if (tBlock->countString < (tBlock->qString-1))
	{
		curStr = tBlock->countString;
		tBlock->countString++;
	}
	else
	{
		curStr = tBlock->startString;
		tBlock->startString++;
	}
	if (tBlock->startString >= tBlock->qString)
		tBlock->startString = 0;
	for (j = 0; j < tBlock->qSymb; j++)
	{
		tBlock->strings[curStr][j] = ' ';
	}
	return curStr;
};

void TerminalBlockAddStrings(GUI_TERMINAL_BLOCK * tBlock, char * str, uint16_t len)
{
	uint16_t i, j, curStr, strPos;
	i = 0;
	strPos = 0;
	curStr = TerminalBlockSetNewString(tBlock);
	while (i < len && str[i] != 0)
	{
		switch(str[i])
		{
		case '\r':
			strPos = 0;
			break;
		case '\n':
			strPos = 0;
			curStr = TerminalBlockSetNewString(tBlock);
			break;
		default:
			if (tBlock->strings)
			{
				if (strPos >= tBlock->qSymb)
				{
					strPos = 0;
					curStr = TerminalBlockSetNewString(tBlock);
				}
				tBlock->strings[curStr][strPos++] = str[i];
			}

			break;
		}
		i++;
	}
}
