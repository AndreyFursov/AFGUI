/*
 * widget.c
 *
 *  Created on: 21.12.2012
 *      Author: Andrey
 */

#include "gui.h"


//*****************************************************************************************
// PROTOTIPES
//*****************************************************************************************
void wmGetTextLenWidth(WM_TEXT *wmText, uint16_t width, uint16_t len);
void wmGetTextPosition(WM_TEXT *wmText, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height);




//******************************************************************************************
void wmObjInit(WM_OBJ * wm, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	wm->xPos = x;
	wm->yPos = y;
	wm->Width = width;
	wm->Height = height;

	if (wm->Color == 0) wm->Color = LCD_COLOR_GREYL;
	if (wm->BorderColor == 0) wm->BorderColor 	= LCD_COLOR_GREYL;
	wm->BorderWidth		= 1;
	wm->Visible 		= 0;
	wm->Enable 			= 0;

};





//******************************************************************************************
void wmTextInit(WM_TEXT * wmText, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)
{
	//uint16_t xPosText, yPosText, i;


	wmText->Text = text;

	if (wmText->TextColor == 0) wmText->TextColor = LCD_COLOR_BLACK;
	wmText->TextAlignH		= align_h;
	wmText->TextAlignV		= align_v;
	wmText->TextRotate		= rot;
	wmText->TextDirection	= DIR_LEFT_TO_RIGHT;
	wmText->TextFlip		= flip;
	wmText->TextLen = 0;
	wmText->vFont = vFont;
}



//******************************************************************************************
void wmObjTextInit(WM_OBJ *wmObj,  WM_TEXT * wmText)
{
	wmTextPositionInit(wmText,
						wmObj->xPos + wmObj->BorderWidth + 1,
						wmObj->yPos + wmObj->BorderWidth,
						wmObj->Width - 2*wmObj->BorderWidth - 2,
						wmObj->Height - 2*wmObj->BorderWidth
						);
}


//******************************************************************************************
void wmTextPositionInit(WM_TEXT *wmText, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height)
{
	// Text Length
	wmGetTextLenWidth(wmText, width, 255);

	// Text Position
	wmGetTextPosition(wmText, xPos, yPos, width, height);

}

//******************************************************************************************
void wmGetTextLenWidth(WM_TEXT *wmText, uint16_t width, uint16_t len)
{
	uint32_t textLength = 0, textWidth = 0, symbCode;
	if (wmText->vFont->Width > 0)
	{
		// monospace font
		while (wmText->Text[textLength]
		            && textLength < len
		            && textWidth + wmText->vFont->Width < width
		            )
		{
			textWidth += wmText->vFont->Width;
			textLength++;
		}
	}
	else
	{
		// proportional font
		symbCode = (uint8_t)wmText->Text[textLength] - wmText->vFont->Offset;
		while (wmText->Text[textLength]
			&& textLength < len
			&& (textWidth + wmText->vFont->tableSymbWidth[symbCode]) < width
			&& symbCode < wmText->vFont->NumSymb
			)
		{
			if (symbCode < wmText->vFont->NumSymb)
			{
				textWidth += (wmText->vFont->tableSymbWidth[symbCode]+wmText->vFont->SymbolSpace);
				textLength++;
			}
			symbCode = (uint8_t)wmText->Text[textLength] - wmText->vFont->Offset;
		}
	}
	wmText->TextLen = textLength;
	wmText->TextWidth = textWidth;
}

//******************************************************************************************
void wmGetTextPosition(WM_TEXT *wmText, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height)
{
	uint16_t i;
	// Text Position
	// Vertical
	if (wmText->TextAlignV == V_ALIGN_TOP)
	{
		wmText->TextPosY = yPos;
	}
	if (wmText->TextAlignV == V_ALIGN_CENTER)
	{
		i = height - wmText->vFont->Height;
		i >>= 1;
		wmText->TextPosY = yPos + i;
	}
	if (wmText->TextAlignV == V_ALIGN_BOTTOM)
	{
		wmText->TextPosY = yPos + height - wmText->vFont->Height;
	}

	// Horizontal
	if (wmText->TextAlignH == H_ALIGN_LEFT)
	{
		wmText->TextPosX = xPos;
	}
	if (wmText->TextAlignH == H_ALIGN_CENTER)
	{
		i = width - wmText->TextWidth;
		i >>= 1;
		wmText->TextPosX = xPos + i;
	}
	if (wmText->TextAlignH == H_ALIGN_RIGHT)
	{
		wmText->TextPosX = xPos + width - wmText->TextWidth;
	}

}

void wmTouchInit( WM_TOUCH *wmTouch)
{
	wmTouch->Jitter = 0;
	wmTouch->Pressed = 0;			 	// Нажата
	wmTouch->JustPressed = 0;		 	// Нажата только что (сбрасывается вручную)
	wmTouch->Hold = 0;					// Не удерживается
	wmTouch->Short = 0;			   		// Не короткое нажатие
	wmTouch->HoldCounter = 0;
	wmTouch->Changed = 0;
	wmTouch->JustReleased = 0;
}

void wmTouchControl(WM_OBJ *wmObj, WM_TOUCH *wmTouch, uint16_t x, uint16_t y)
{
	uint8_t touch = 0;

	if (wmObj->Visible && wmObj->Enable)
	{
		if (	x < wmObj->xPos + wmObj->Width
				&& x > wmObj->xPos
				&& y > wmObj->yPos
				&& y < wmObj->yPos + wmObj->Height
				)
			touch = 1;


		//------------------------------------------------------------------------------
		//  Кнопка еще не нажата
		//------------------------------------------------------------------------------
		if (!wmTouch->Pressed)
		{
			wmTouch->Jitter++;
			// touch == 1 = нажата
			if (!touch) wmTouch->Jitter = 0;  // Подавляем дребезг

			if (wmTouch->Jitter == 3)				// Перестала дребезжать
			{
				wmTouch->Pressed = 1;			 	// Нажата
				wmTouch->JustPressed = 1;		 	// Нажата только что (сбрасывается вручную)
				Beeper_ShortOn(50);
				wmTouch->Hold = 0;					// Не удерживается
				wmTouch->Short = 0;			   		// Не короткое нажатие
				wmTouch->HoldCounter = 0;
				wmTouch->Changed = 1;
			}   // if jitter
		}
		else
		{	// if button pressed

			//------------------------------------------------------------------------------
			//  Кнопка нажата, проверяем удерживание
			//------------------------------------------------------------------------------

			wmTouch->Jitter++;
			// активный уровень 0
			if (touch) wmTouch->Jitter = 0; // Подавляем шорох

			if (wmTouch->Jitter == 3)			 // Кнопку только что отпустили
			{
				wmTouch->Pressed = 0;
				if (!wmTouch->Hold)			   	// Если не было удерживаниядольше 1 сек,
					wmTouch->Short = 1;		   	// то установить флаг "короткого нажатия"

				wmTouch->JustReleased = 1;		 	// Нажата только что (сбрасывается вручную)
				wmTouch->Hold = 0;
				wmTouch->HoldCounter = 0;
				wmTouch->Changed = 1;

			}   // if jitter

			wmTouch->HoldCounter++;

			if (wmTouch->HoldCounter >= 50)	   // Проверяем удерживание
				wmTouch->Hold = 1;

		}   // if button pressed

	}
	else
	{
		*((uint16_t *)wmTouch) = 0;
	}

}
