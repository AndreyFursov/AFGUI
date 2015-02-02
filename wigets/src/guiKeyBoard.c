/*
 * guiKeyBoard.c
 *
 *  Created on: 16.01.2015
 *      Author: Andrey Fursov
 */

#include "gui.h"


void defaultKeyBoardInit(GUI_KEYBOARD * pKeyBoard, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	pKeyBoard->wmObj.xPos 			= x;
	pKeyBoard->wmObj.yPos 			= y;
	pKeyBoard->wmObj.Width 			= width;
	pKeyBoard->wmObj.Height 		= height;

	pKeyBoard->wmObj.Color 			= LCD_COLOR_GREYL;

	pKeyBoard->wmObj.BorderColor 	= LCD_COLOR_GREYD;
	pKeyBoard->wmObj.BorderWidth	= 1;

	pKeyBoard->wmObj.Visible 		= 0;
	pKeyBoard->wmObj.Enable 		= 0;
};

void KeyBoardCodeInit(GUI_KEYBOARD * pKeyBoard, char * pCode)
{
	pKeyBoard->code = pCode;
};


void KeyBoardInit(GUI_KEYBOARD * pKeyBoard, STEXT_BUTTON * pSbtn, V_FONT * vFont, char ** pName, uint8_t numColumn, uint8_t numRow)
{
	int i, j, k;
	uint16_t bx, by, bh, bw;

	// сохраняем данные в структуру клавиатуры
	pKeyBoard->numColumn = numColumn;
	pKeyBoard->numRow = numRow;
	pKeyBoard->sBtn = pSbtn;
	pKeyBoard->name = pName;
	pKeyBoard->numKey = (uint16_t)numColumn * numRow;

	// рассчитываем данные кнопок
	bw = pKeyBoard->wmObj.Width/numColumn - 2;
	bh = pKeyBoard->wmObj.Height/numRow - 2;
	bx = pKeyBoard->wmObj.xPos + 1;
	by = pKeyBoard->wmObj.yPos + 1;
	k = 0;

	for (i = 0; i < numRow; i++)	// строки
	{

		for (j = 0; j < numColumn; j++)	// столбцы
		{
			// инициализация положения
			defaultTextButtonInit(&pSbtn[k].btn, bx, by, bw, bh);
			// инициализация текста
			ButtonTextInit(&pSbtn[k].btn, pName[k], vFont, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);

			k++;
			// смещение по оси X
			bx += bw + 1;
		}
		// смещение по оси Y
		by += bh + 1;
		bx = pKeyBoard->wmObj.xPos + 1;
	}

	//pKeyBoard->wmTxt.TextColor = LCD_COLOR_BLACK;
}

void KeyBoardDraw(GUI_KEYBOARD * pKeyBoard)
{
	int i;
	for (i = 0; i < pKeyBoard->numKey; i++)	// строки
	{
		if (pKeyBoard->wmObj.Visible && pKeyBoard->wmObj.Enable)
		{
			pKeyBoard->sBtn[i].btn.wmObj.Visible = 1;
			pKeyBoard->sBtn[i].btn.wmObj.Enable = 1;
			TextButtonDraw(&pKeyBoard->sBtn[i].btn);
		}
		else
		{
			pKeyBoard->sBtn[i].btn.wmObj.Visible = 0;
			pKeyBoard->sBtn[i].btn.wmObj.Enable = 0;
		}
	}
}

void KeyBoardRefresh(GUI_KEYBOARD * pKeyBoard)
{
	int i;
	for (i = 0; i < pKeyBoard->numKey; i++)	// строки
	{
		TextButtonStateRefresh(&pKeyBoard->sBtn[i].btn);
	}
}

void KeyBoardTouchControl(GUI_KEYBOARD * pKeyBoard, int16_t xTouch, int16_t yTouch)
{
	int i;
	for (i = 0; i < pKeyBoard->numKey; i++)	// строки
	{
		//TextButtonTouchControl(&pKeyBoard->sBtn[i].btn, xTouch, yTouch);
		STextButtonTouchControl(&pKeyBoard->sBtn[i], xTouch, yTouch);
	}
}
