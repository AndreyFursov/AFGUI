/*
 * guiEditBox.c
 *
 *  Created on: 18 янв. 2015 г.
 *      Author: Andrey Fursov
 */

#include "gui.h"

void defaultEditBoxInit(GUI_EDIT_BOX * pEditBox, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	int i;

	pEditBox->wmObj.xPos 		= x;
	pEditBox->wmObj.yPos 		= y;
	pEditBox->wmObj.Width 		= width;
	pEditBox->wmObj.Height 		= height;


	pEditBox->wmObj.Color 		= LCD_COLOR_WHITE;

	pEditBox->wmObj.BorderColor = LCD_COLOR_GREYL;
	pEditBox->wmObj.BorderWidth	= 1;

	pEditBox->wmObj.Visible 	= 0;
	pEditBox->wmObj.Enable 		= 0;
	pEditBox->wmObj.Selected	= 0;

	pEditBox->wmObj.Visual3D 	= 1;
	pEditBox->curPosition 		= 0;
	pEditBox->modeInsert 		= 0;
	pEditBox->fAddSymbol		= 0;
	wmTouchInit(&pEditBox->wmTouch);
};

void EditBoxTextInit(GUI_EDIT_BOX * pEditBox, char *text, V_FONT * vFont, uint16_t maxStrLength, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)
{
	pEditBox->maxStringLength = maxStrLength;
	wmTextInit(&pEditBox->wmTxt, text, vFont, rot, flip, align_h, align_v);
	EditBoxTextPosInit(pEditBox);
}

// надо дорабатывать
int EditBoxAddSymbol(GUI_EDIT_BOX * pEditBox, char symbol)
{
	int i;
	if (pEditBox->modeInsert)
	{

	}
	else
	{
		if (symbol > 0x20 && pEditBox->curPosition < pEditBox->maxStringLength)
		{
			pEditBox->wmTxt.Text[pEditBox->curPosition] = symbol;
			pEditBox->wmTxt.TextLen++;
		}
		else
		{
			if (symbol == 0x08)
			{
				for (i = pEditBox->curPosition; i < pEditBox->wmTxt.TextLen; i++)
				{
					pEditBox->wmTxt.Text[i] = pEditBox->wmTxt.Text[i+1];
				}
				pEditBox->wmTxt.TextLen--;
			}
		}
		pEditBox->curPosition = pEditBox->wmTxt.TextLen - 1;
	}
	EditBoxTextPosInit(pEditBox);

	return 0;
}

// добавляем символ в конец строки
int EditBoxAppendSymbol(GUI_EDIT_BOX * pEditBox, char symbol)
{
	int i;
	if (pEditBox->curPosition < pEditBox->maxStringLength-2 && symbol > 0x20)
	{
		pEditBox->wmTxt.Text[pEditBox->curPosition++] = symbol;
		if (pEditBox->wmObj.Selected)
			pEditBox->wmTxt.Text[pEditBox->curPosition] = '|';
		pEditBox->wmTxt.Text[pEditBox->curPosition + 1] = 0;
		

	}
	else
	{
		if (symbol == 0x08)
		{
			if (pEditBox->wmTxt.TextLen > 1 && pEditBox->curPosition)
			{
				if (pEditBox->curPosition < pEditBox->maxStringLength - 1
					|| pEditBox->wmTxt.Text[pEditBox->curPosition] == '|')
				{
					pEditBox->wmTxt.Text[pEditBox->curPosition-1] = '|';
					pEditBox->wmTxt.Text[pEditBox->curPosition--] = 0;
				}
				else
				{
					pEditBox->wmTxt.Text[pEditBox->curPosition] = '|';
					pEditBox->wmTxt.Text[pEditBox->curPosition+1] = 0;
				}
			}
		}
	}
	pEditBox->wmTxt.TextLen = pEditBox->curPosition + 1;
	EditBoxTextPosInit(pEditBox);

	return 0;
}

void EditBoxTextPosInit(GUI_EDIT_BOX * pEditBox)
{
	wmTextPositionInit(&pEditBox->wmTxt,
						pEditBox->wmObj.xPos + pEditBox->wmObj.BorderWidth,
						pEditBox->wmObj.yPos + pEditBox->wmObj.BorderWidth,
						pEditBox->wmObj.Width - 2*pEditBox->wmObj.BorderWidth,
						pEditBox->wmObj.Height - 2*pEditBox->wmObj.BorderWidth
						);

}

/*! Переносит фокус ввода на текущий объект
 * \param [in] *pEditBox - указатель на объект GUI_EDIT_BOX
 * \return возвращает длину строки
 */
int EditBoxSelect(GUI_EDIT_BOX * pEditBox)
{
	pEditBox->wmObj.Selected = 1;

	if (pEditBox->wmTxt.TextLen < pEditBox->maxStringLength - 2)
	{
		pEditBox->curPosition = pEditBox->wmTxt.TextLen;
		if (pEditBox->wmTxt.Text[pEditBox->wmTxt.TextLen-1] != '|')
		{
			pEditBox->wmTxt.Text[pEditBox->wmTxt.TextLen++] = '|';
			if (pEditBox->wmTxt.TextLen < pEditBox->maxStringLength - 1)
				pEditBox->wmTxt.Text[pEditBox->wmTxt.TextLen] = 0;
			EditBoxTextPosInit(pEditBox);
			EditBoxDraw(pEditBox);
		}
	}

	return pEditBox->wmTxt.TextLen;
}

/*! Снимает фокус ввода с текущего объекта
 * \param [in] *pEditBox - указатель на объект GUI_EDIT_BOX
 * \return возвращает длину строки
 */
int EditBoxUnselect(GUI_EDIT_BOX * pEditBox)
{
	int i;
	pEditBox->wmObj.Selected = 0;


	if (pEditBox->wmTxt.Text[pEditBox->curPosition] == '|')
	{
		pEditBox->wmTxt.Text[--pEditBox->wmTxt.TextLen] = 0;
		EditBoxTextPosInit(pEditBox);
	}

	return pEditBox->wmTxt.TextLen;
}



void EditBoxDraw(GUI_EDIT_BOX * pEditBox)
{
	int i;
	if (pEditBox->wmObj.Visible)
	{
		// Borders
		LCD_SetTextColor(pEditBox->wmObj.BorderColor);
		if (pEditBox->wmObj.BorderWidth)
		{
			if (pEditBox->wmObj.Visual3D == 1)
			{
				for (i = 0; i < pEditBox->wmObj.BorderWidth; i++)
				{
					LCD_SetTextColor(LCD_COLOR_GREYD);
					// Top Border
					LCD_DrawLine(pEditBox->wmObj.xPos, pEditBox->wmObj.yPos, pEditBox->wmObj.Width-i-1, LCD_DIR_HORIZONTAL);
					// Left Border
					LCD_DrawLine(pEditBox->wmObj.xPos, pEditBox->wmObj.yPos, pEditBox->wmObj.Height-i, LCD_DIR_VERTICAL);

					if (i == pEditBox->wmObj.BorderWidth-1 && pEditBox->wmObj.Color == LCD_COLOR_WHITE)
						LCD_SetTextColor(LCD_COLOR_GREYL);
					else
						LCD_SetTextColor(LCD_COLOR_WHITE);
					// Bottom Border
					LCD_DrawLine(pEditBox->wmObj.xPos+1+i, pEditBox->wmObj.yPos+pEditBox->wmObj.Height-i-1, pEditBox->wmObj.Width-i-2, LCD_DIR_HORIZONTAL);
					// Right Border
					LCD_DrawLine(pEditBox->wmObj.xPos+pEditBox->wmObj.Width-i-1, pEditBox->wmObj.yPos+i+1, pEditBox->wmObj.Height-i-2, LCD_DIR_VERTICAL);
				}
			}
			else
			{
				// Top Border
				LCD_DrawFillRect(pEditBox->wmObj.xPos, pEditBox->wmObj.yPos, pEditBox->wmObj.Width, pEditBox->wmObj.BorderWidth);
				// Left Border
				LCD_DrawFillRect(pEditBox->wmObj.xPos, pEditBox->wmObj.yPos, pEditBox->wmObj.BorderWidth, pEditBox->wmObj.Height);
				// Bottom Border
				LCD_DrawFillRect(pEditBox->wmObj.xPos, pEditBox->wmObj.yPos+pEditBox->wmObj.Height-pEditBox->wmObj.BorderWidth, pEditBox->wmObj.Width, pEditBox->wmObj.BorderWidth);
				// Right Border
				LCD_DrawFillRect(pEditBox->wmObj.xPos+pEditBox->wmObj.Width-pEditBox->wmObj.BorderWidth, pEditBox->wmObj.yPos, pEditBox->wmObj.BorderWidth, pEditBox->wmObj.Height);
			}
		}
		// Back
		if (pEditBox->wmObj.Transparent == 0)
		{
			LCD_SetTextColor(pEditBox->wmObj.Color);
			LCD_DrawFillRect(pEditBox->wmObj.xPos + pEditBox->wmObj.BorderWidth,
							pEditBox->wmObj.yPos + pEditBox->wmObj.BorderWidth,
							pEditBox->wmObj.Width - 2*pEditBox->wmObj.BorderWidth,
							pEditBox->wmObj.Height - 2*pEditBox->wmObj.BorderWidth
							);
		}
		// Text
		LCD_SetFont(pEditBox->wmTxt.vFont);
		if (pEditBox->wmObj.Enable)
			LCD_SetColors(pEditBox->wmTxt.TextColor, pEditBox->wmObj.Color);
		else
			LCD_SetColors(guiChangeColorLight(pEditBox->wmObj.Color, 120), pEditBox->wmObj.Color);

		LCD_DrawString(pEditBox->wmTxt.Text, pEditBox->wmTxt.TextLen, pEditBox->wmTxt.TextPosX, pEditBox->wmTxt.TextPosY);
	}
}


void EditBoxValueRedraw(GUI_EDIT_BOX * pEditBox)
{

}



int EditBoxTouchControl(GUI_EDIT_BOX * pEditBox, int16_t xTouch, int16_t yTouch)
{
	int newData = 0;
	wmTouchControl(&pEditBox->wmObj, &pEditBox->wmTouch, xTouch, yTouch);
	if (pEditBox->wmTouch.JustReleased)
	{
		pEditBox->wmTouch.JustReleased = 0;
		pEditBox->curPosition = pEditBox->wmTxt.TextLen - 1;
		if (&pEditBox->fOnUntouch)
			pEditBox->fOnUntouch(pEditBox);
	}
	return (int)pEditBox;
}
