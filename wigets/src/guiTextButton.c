/*
 * guiTextButton.c
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#include "gui.h"

void defaultTextButtonInit(TEXT_BUTTON * button, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	//unsigned int textWidth;

	button->wmObj.xPos 			= x;
	button->wmObj.yPos 			= y;
	button->wmObj.Width 		= width;
	button->wmObj.Height 		= height;


	button->wmObj.Color 		= LCD_COLOR_GREYL;

	button->wmObj.BorderColor 	= LCD_COLOR_GREYL;
	button->wmObj.BorderWidth	= 1;

	button->wmObj.Visible 		= 0;
	button->wmObj.Enable 		= 0;

	button->wmTxt.TextColor 	= LCD_COLOR_BLACK;
	button->wmTxt.TextAlignH	= H_ALIGN_CENTER;
	button->wmTxt.TextAlignV	= V_ALIGN_CENTER;
	button->wmTxt.TextRotate	= ROTATE_0;
	button->wmTxt.TextDirection	= DIR_LEFT_TO_RIGHT;
	button->wmTxt.TextFlip		= FLIP_NO;
	button->wmTxt.TextLen 		= 0;
	button->fOnTouch			= 0;
	button->fOnUntouch			= 0;
	wmTouchInit(&button->wmTouch);
};

void ButtonTextInit(TEXT_BUTTON * button, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)
{
	//uint16_t xPosText, yPosText, i;

	wmTextInit(&button->wmTxt, text, vFont, rot, flip, align_h, align_v);
	wmTextPositionInit(&button->wmTxt,
						button->wmObj.xPos + button->wmObj.BorderWidth,
						button->wmObj.yPos + button->wmObj.BorderWidth,
						button->wmObj.Width - 2*button->wmObj.BorderWidth,
						button->wmObj.Height - 2*button->wmObj.BorderWidth
						);

}

void TextButtonDraw(TEXT_BUTTON * button)
{

	if (button->wmObj.Visible)
	{
		TextButtonStateRefresh(button);

		// Back
		LCD_SetTextColor(button->wmObj.Color);
		LCD_DrawFillRect(button->wmObj.xPos + button->wmObj.BorderWidth,
						button->wmObj.yPos + button->wmObj.BorderWidth,
						button->wmObj.Width - button->wmObj.BorderWidth - button->wmObj.BorderWidth,
						button->wmObj.Height - button->wmObj.BorderWidth - button->wmObj.BorderWidth);

		// Text
		LCD_SetFont(button->wmTxt.vFont);
		if (button->wmObj.Enable)
			LCD_SetColors(button->wmTxt.TextColor, button->wmObj.Color);
		else
			LCD_SetColors(LCD_COLOR_GREYD, button->wmObj.Color);
		LCD_DrawString(button->wmTxt.Text, button->wmTxt.TextLen, button->wmTxt.TextPosX, button->wmTxt.TextPosY);
	}
}

void TextButtonTouchControl(TEXT_BUTTON * button,  int16_t xTouch, int16_t yTouch)
{
	wmTouchControl(&button->wmObj, &button->wmTouch, xTouch, yTouch);

	if (button->wmTouch.Changed)
	{
		button->wmTouch.Changed = 0;
		TextButtonStateRefresh(button);

		if (button->fOnTouch && button->wmTouch.JustPressed)
		{
			button->wmTouch.JustPressed = 0;
			button->fOnTouch();
		}
		if (button->fOnUntouch && button->wmTouch.JustReleased)
		{
			button->wmTouch.JustReleased = 0;
			button->fOnUntouch();
		}
	}

	if (button->fOnTouch && button->wmTouch.Pressed  && button->wmTouch.Hold)
	{
		button->fOnTouch();
	}
}

void TextButtonStateRefresh(TEXT_BUTTON * button)
{
	uint16_t  colorTL, colorBR;

	if (button->wmObj.Visible)
	{
		if (button->wmTouch.Pressed)
		{
//			colorBR = guiChangeColorLight(button->wmObj.Color, 150);
//			colorTL = guiChangeColorLight(button->wmObj.Color, 50);
			colorBR = LCD_COLOR_WHITE;
			colorTL = LCD_COLOR_GREYD;
		}
		else
		{
//			colorTL = guiChangeColorLight(button->wmObj.Color, 150);
//			colorBR = guiChangeColorLight(button->wmObj.Color, 50);
			colorTL = LCD_COLOR_WHITE;
			colorBR = LCD_COLOR_GREYD;
		}

		// Bot-Right Dark Border
		LCD_SetTextColor(colorBR);
		//bot
		LCD_DrawFillRect(button->wmObj.xPos+1,
						button->wmObj.yPos + button->wmObj.Height - button->wmObj.BorderWidth,
						button->wmObj.Width-1,
						button->wmObj.BorderWidth);
		// right
		LCD_DrawFillRect(button->wmObj.xPos + button->wmObj.Width - button->wmObj.BorderWidth,
						button->wmObj.yPos+1,
						button->wmObj.BorderWidth,
						button->wmObj.Height-1);

		// Top-Left Light Border
		LCD_SetTextColor(colorTL);
		// top
		LCD_DrawFillRect(button->wmObj.xPos,
						button->wmObj.yPos,
						button->wmObj.BorderWidth,
						button->wmObj.Height-1);
		// left
		LCD_DrawFillRect(button->wmObj.xPos,
						button->wmObj.yPos,
						button->wmObj.Width-1,
						button->wmObj.BorderWidth);
	}
}

