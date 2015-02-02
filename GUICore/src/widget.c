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
	wmText->TextLen 		= 0;
	wmText->vFont 			= vFont;
	wmText->TextUnderlined 	= 0;
	wmText->TextCrossed		= 0;
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

void wmObjOnPaint(WM_OBJ * wmObj)
{
	if (wmObj->Visible && wmObj->Enable)
	{
		// Border
		LCD_SetTextColor(wmObj->BorderColor);
		// Top Border
		LCD_DrawFillRect(wmObj->xPos, wmObj->yPos, wmObj->Width, wmObj->BorderWidth);
		// Left Border
		LCD_DrawFillRect(wmObj->xPos, wmObj->yPos, wmObj->BorderWidth, wmObj->Height);
		// Bottom Border
		LCD_DrawFillRect(wmObj->xPos, wmObj->yPos+wmObj->Height-wmObj->BorderWidth, wmObj->Width, wmObj->BorderWidth);
		// Right Border
		LCD_DrawFillRect(wmObj->xPos+wmObj->Width-wmObj->BorderWidth, wmObj->yPos, wmObj->BorderWidth, wmObj->Height);

		// back
		LCD_SetTextColor(wmObj->Color);
		LCD_DrawFillRect(wmObj->xPos + wmObj->BorderWidth,
						wmObj->yPos + wmObj->BorderWidth,
						wmObj->Width - 2*wmObj->BorderWidth,
						wmObj->Height - 2*wmObj->BorderWidth
						);
	}
}

void wmTouchInit( WM_TOUCH *wmTouch)
{
	wmTouch->Jitter = 0;
	wmTouch->Pressed = 0;			 	// ������
	wmTouch->JustPressed = 0;		 	// ������ ������ ��� (������������ �������)
	wmTouch->Hold = 0;					// �� ������������
	wmTouch->Short = 0;			   		// �� �������� �������
	wmTouch->HoldCounter = 0;			// ������� ���������
	wmTouch->Changed = 0;				// ��������� ����������
	wmTouch->JustReleased = 0;			// ������ ��� �������� (������������ �������)
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
		//  ������ ��� �� ������
		//------------------------------------------------------------------------------
		if (!wmTouch->Pressed)
		{
			wmTouch->Jitter++;
			// touch == 1 = ������
			if (!touch) wmTouch->Jitter = 0;  // ��������� �������

			if (wmTouch->Jitter == 3)				// ��������� ����������
			{
				wmTouch->Pressed = 1;			 	// ������
				wmTouch->JustPressed = 1;		 	// ������ ������ ��� (������������ �������)
				Beeper_ShortOn(50);
				wmTouch->Hold = 0;					// �� ������������
				wmTouch->Short = 0;			   		// �� �������� �������
				wmTouch->HoldCounter = 0;
				wmTouch->Changed = 1;
			}   // if jitter
		}
		else
		{	// if button pressed

			//------------------------------------------------------------------------------
			//  ������ ������, ��������� �����������
			//------------------------------------------------------------------------------

			wmTouch->Jitter++;
			// �������� ������� 0
			if (touch) wmTouch->Jitter = 0; // ��������� �����

			if (wmTouch->Jitter == 3)			 // ������ ������ ��� ���������
			{
				wmTouch->Pressed = 0;
				if (!wmTouch->Hold)			   	// ���� �� ���� ����������������� 1 ���,
					wmTouch->Short = 1;		   	// �� ���������� ���� "��������� �������"

				wmTouch->JustReleased = 1;		 	// ������ ������ ��� (������������ �������)
				wmTouch->Hold = 0;
				wmTouch->HoldCounter = 0;
				wmTouch->Changed = 1;

			}   // if jitter



			if (wmTouch->HoldCounter >= 30)	   // ��������� ���������
				wmTouch->Hold = 1;
			else
				wmTouch->HoldCounter++;

		}   // if button pressed

	}
	else
	{
		//
		*((uint16_t *)&wmTouch) = 0;
	}

}
