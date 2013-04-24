/*
 * guiTextcheckBox.c
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#include "gui.h"

void defaultCheckInit(GUI_CHECK_BOX * checkBox, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	checkBox->wmObj.xPos 		= x;
	checkBox->wmObj.yPos 		= y;
	checkBox->wmObj.Width 		= width;
	checkBox->wmObj.Height 		= height;

	checkBox->wmObj.Color 		= LCD_COLOR_WHITE;

	checkBox->wmObj.BorderColor = LCD_COLOR_GREYL;
	checkBox->wmObj.BorderWidth	= 1;

	checkBox->wmObj.Visible 	= 0;
	checkBox->wmObj.Enable 		= 0;
	checkBox->Checked			= 0;
};

void CheckBoxTextInit(GUI_CHECK_BOX * checkBox, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)
{
	checkBox->wmTxt.TextColor = LCD_COLOR_BLACK;
	wmTextInit(&checkBox->wmTxt, text, vFont, rot, flip, align_h, align_v);
	wmTextPositionInit(&checkBox->wmTxt,
						checkBox->wmObj.xPos + checkBox->wmObj.Height+1,
						checkBox->wmObj.yPos ,
						checkBox->wmObj.Width - checkBox->wmObj.Height - 1,
						checkBox->wmTxt.vFont->Height
						);

}

void CheckBoxDraw(GUI_CHECK_BOX * checkBox)
{
//	uint16_t  colorLight, colorDark;

	if (checkBox->wmObj.Visible)
	{
		//colorLight = guiChangeColorLight(checkBox->wmObj.BorderColor, 150);
		//colorDark = guiChangeColorLight(checkBox->wmObj.BorderColor, 50);

		// check symbol
		// Top-Left Border
		//LCD_SetTextColor(colorDark);
		LCD_SetTextColor(LCD_COLOR_GREYD);
		LCD_DrawLine(checkBox->wmObj.xPos, checkBox->wmObj.yPos, checkBox->wmObj.Height, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(checkBox->wmObj.xPos, checkBox->wmObj.yPos+1, checkBox->wmObj.Height-1, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(checkBox->wmObj.xPos, checkBox->wmObj.yPos, checkBox->wmObj.Height, LCD_DIR_VERTICAL);
		LCD_DrawLine(checkBox->wmObj.xPos+1, checkBox->wmObj.yPos, checkBox->wmObj.Height-1, LCD_DIR_VERTICAL);


		// Bot-Right Dark Border
		//LCD_SetTextColor(colorLight);
		LCD_SetTextColor(LCD_COLOR_WHITE);
		LCD_DrawLine(checkBox->wmObj.xPos+1, checkBox->wmObj.yPos+checkBox->wmObj.Height-1, checkBox->wmObj.Height-1, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(checkBox->wmObj.xPos+checkBox->wmObj.Height-1, checkBox->wmObj.yPos+1, checkBox->wmObj.Height-1, LCD_DIR_VERTICAL);
		LCD_SetTextColor(checkBox->wmObj.BorderColor);
		LCD_DrawLine(checkBox->wmObj.xPos+2, checkBox->wmObj.yPos+checkBox->wmObj.Height-2, checkBox->wmObj.Height-3, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(checkBox->wmObj.xPos+checkBox->wmObj.Height-2, checkBox->wmObj.yPos+2, checkBox->wmObj.Height-3, LCD_DIR_VERTICAL);

		// Center
		if (checkBox->wmObj.Enable)
			LCD_SetTextColor(LCD_COLOR_WHITE);
		else
			LCD_SetTextColor(LCD_COLOR_GREYL);
		LCD_DrawFillRect(checkBox->wmObj.xPos+2,checkBox->wmObj.yPos+2,checkBox->wmObj.Height-4,checkBox->wmObj.Height-4);
		if (checkBox->Checked)
		{
			if (checkBox->wmObj.Enable)
				LCD_SetTextColor(LCD_COLOR_BLACK);
			else
				LCD_SetTextColor(LCD_COLOR_GREYD);
			LCD_DrawFillRect(checkBox->wmObj.xPos+4,checkBox->wmObj.yPos+4,checkBox->wmObj.Height-8,checkBox->wmObj.Height-8);
		}






		// Back
//		LCD_SetTextColor(checkBox->wmObj.Color);
//		LCD_DrawFillRect(checkBox->wmObj.xPos + checkBox->wmObj.BorderWidth,
//						checkBox->wmObj.yPos + checkBox->wmObj.BorderWidth,
//						checkBox->wmObj.Width - checkBox->wmObj.BorderWidth - checkBox->wmObj.BorderWidth - 1,
//						checkBox->wmObj.Height - checkBox->wmObj.BorderWidth - checkBox->wmObj.BorderWidth - 1);

		// Text
		LCD_SetFont(checkBox->wmTxt.vFont);
		if (checkBox->wmObj.Enable)
			LCD_SetColors(checkBox->wmTxt.TextColor, checkBox->wmObj.BorderColor);
		else
			LCD_SetColors(guiChangeColorLight(checkBox->wmTxt.TextColor, 120), checkBox->wmObj.BorderColor);;
		LCD_DrawString(checkBox->wmTxt.Text, checkBox->wmTxt.TextLen, checkBox->wmTxt.TextPosX, checkBox->wmTxt.TextPosY);
	}
}

void CheckBoxStateRefresh(GUI_CHECK_BOX * checkBox)
{
	if (checkBox->wmObj.Visible)
	{
		// Center
		if (checkBox->wmObj.Enable)
			LCD_SetTextColor(LCD_COLOR_WHITE);
		else
			LCD_SetTextColor(LCD_COLOR_GREYL);
		LCD_DrawFillRect(checkBox->wmObj.xPos+2,checkBox->wmObj.yPos+2,checkBox->wmObj.Height-4,checkBox->wmObj.Height-4);
		if (checkBox->Checked)
		{
			if (checkBox->wmObj.Enable)
				LCD_SetTextColor(LCD_COLOR_BLACK);
			else
				LCD_SetTextColor(LCD_COLOR_GREYD);
			LCD_DrawFillRect(checkBox->wmObj.xPos+4,checkBox->wmObj.yPos+4,checkBox->wmObj.Height-8,checkBox->wmObj.Height-8);
		}
	}
}

void CheckBoxTouchControl(GUI_CHECK_BOX * checkBox, int16_t xTouch, int16_t yTouch)
{
	if (checkBox->wmObj.Enable)
	{
		wmTouchControl(&checkBox->wmObj, &checkBox->wmTouch, xTouch, yTouch);
		if (checkBox->wmTouch.JustReleased)
		{
			checkBox->wmTouch.JustReleased = 0;
			if (checkBox->Checked)
				checkBox->Checked = 0;
			else
				checkBox->Checked = 1;
			CheckBoxStateRefresh(checkBox);
		}
	}
}
