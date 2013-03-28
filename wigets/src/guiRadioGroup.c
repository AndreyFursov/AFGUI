/*
 * guiRadioGroup.c
 *
 *  Created on: 24.03.2013
 *      Author: Andrey Fursov
 */


#include "gui.h"

void defaultRadioGroupInit(GUI_RADIO_GROUP * radioGroup, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	radioGroup->wmObj.xPos 		= x;
	radioGroup->wmObj.yPos 		= y;
	radioGroup->wmObj.Width 	= width;
	radioGroup->wmObj.Height 	= height;


	radioGroup->wmObj.Color 	= LCD_COLOR_GREYL;

	radioGroup->wmObj.BorderColor = LCD_COLOR_GREYD;
	radioGroup->wmObj.BorderWidth = 1;

	radioGroup->wmObj.Visible 	= 1;
	radioGroup->wmObj.Enable 	= 1;
};

void defaultRadioGroupItemInit(GUI_RADIO_GROUP * radioGroup, uint8_t numItem, uint8_t itemSelected)
{
	if (numItem <= 8)
		radioGroup->NumItem = numItem;
	else
		radioGroup->NumItem = 0;

	radioGroup->ItemSelected = itemSelected;
}

void RadioGroupTextInit(GUI_RADIO_GROUP * radioGroup, char *text, V_FONT * vFont)
{
	wmTextInit(&radioGroup->wmTxt, text, vFont, ROTATE_0, FLIP_NO, H_ALIGN_LEFT, V_ALIGN_TOP);

	wmTextPositionInit(&radioGroup->wmTxt,
						radioGroup->wmObj.xPos + radioGroup->wmObj.BorderWidth + 5,
						radioGroup->wmObj.yPos + radioGroup->wmObj.BorderWidth,
						radioGroup->wmObj.Width - 2*radioGroup->wmObj.BorderWidth - 5,
						radioGroup->wmObj.Height - 2*radioGroup->wmObj.BorderWidth
						);
}

void RadioGroupItemInit(GUI_RADIO_GROUP * radioGroup, char *text, V_FONT * vFont, uint8_t index)
{
	uint16_t itemHeight, startY, heightForItem;
	int16_t space;

	// item Height
	itemHeight = vFont->Height;
	if (itemHeight < 16) itemHeight = 16;

	// height for item
	heightForItem = radioGroup->wmObj.Height - radioGroup->wmTxt.vFont->Height - 10 - radioGroup->wmObj.BorderWidth;
	startY = radioGroup->wmObj.yPos + radioGroup->wmTxt.vFont->Height + 10;
	space = heightForItem/(radioGroup->NumItem ) - itemHeight;


	if (space < 1)
	{
		space = 1;
		radioGroup->NumItem = heightForItem/(itemHeight + space);
	}

	// item init
	if (index >= radioGroup->NumItem)
		index = 0;
	else
	{
		wmTextInit(&radioGroup->Item[index].wmTxt, text, vFont, ROTATE_0, FLIP_NO, H_ALIGN_LEFT, V_ALIGN_CENTER);
		radioGroup->Item[index].wmTxt.TextColor = LCD_COLOR_BLACK;

		radioGroup->Item[index].wmObj.xPos = radioGroup->wmObj.xPos + 5;
		radioGroup->Item[index].wmObj.yPos = startY + (itemHeight + space)*index;
		radioGroup->Item[index].wmObj.Width = radioGroup->wmObj.Width - 10;
		radioGroup->Item[index].wmObj.Height = itemHeight;

		wmTextPositionInit(&radioGroup->Item[index].wmTxt,
							radioGroup->Item[index].wmObj.xPos + 17,
							radioGroup->Item[index].wmObj.yPos,
							radioGroup->Item[index].wmObj.Width - 17,
							radioGroup->Item[index].wmObj.Height
							);
	}
}

void RadioGroupDraw(GUI_RADIO_GROUP * radioGroup)
{
	uint16_t i;
	if (radioGroup->wmObj.Visible)
	{

		// check symbol
		// top left bot right
		LCD_SetTextColor(LCD_COLOR_GREYD);
		LCD_DrawLine(radioGroup->wmObj.xPos, radioGroup->wmObj.yPos + 5, radioGroup->wmObj.Width, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(radioGroup->wmObj.xPos, radioGroup->wmObj.yPos + 5, radioGroup->wmObj.Height-6, LCD_DIR_VERTICAL);
		LCD_DrawLine(radioGroup->wmObj.xPos, radioGroup->wmObj.yPos + radioGroup->wmObj.Height-1, radioGroup->wmObj.Width-1, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(radioGroup->wmObj.xPos+radioGroup->wmObj.Width-1, radioGroup->wmObj.yPos+5, radioGroup->wmObj.Height-6, LCD_DIR_VERTICAL);

		// top left bot right
		LCD_SetTextColor(LCD_COLOR_WHITE);
		LCD_DrawLine(radioGroup->wmObj.xPos+1, radioGroup->wmObj.yPos + 6, radioGroup->wmObj.Width-2, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(radioGroup->wmObj.xPos+1, radioGroup->wmObj.yPos + 6, radioGroup->wmObj.Height-7, LCD_DIR_VERTICAL);
		LCD_DrawLine(radioGroup->wmObj.xPos+2, radioGroup->wmObj.yPos + radioGroup->wmObj.Height, radioGroup->wmObj.Width-1, LCD_DIR_HORIZONTAL);
		LCD_DrawLine(radioGroup->wmObj.xPos+radioGroup->wmObj.Width, radioGroup->wmObj.yPos+7, radioGroup->wmObj.Height-6, LCD_DIR_VERTICAL);

		// Text
		LCD_SetFont(radioGroup->wmTxt.vFont);
		if (radioGroup->wmObj.Enable)
			LCD_SetColors(radioGroup->wmTxt.TextColor, radioGroup->wmObj.Color);
		else
			LCD_SetColors(guiChangeColorLight(radioGroup->wmTxt.TextColor, 120), radioGroup->wmObj.Color);;
		LCD_DrawString(radioGroup->wmTxt.Text, radioGroup->wmTxt.TextLen, radioGroup->wmTxt.TextPosX, radioGroup->wmTxt.TextPosY);




		// Items text
		for (i = 0; i < radioGroup->NumItem; i++)
		{
			// check symbol

			// Top-Left Border
			LCD_SetTextColor(LCD_COLOR_GREYD);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos, radioGroup->Item[i].wmObj.yPos, 15, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos, radioGroup->Item[i].wmObj.yPos+1, 15-1, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos, radioGroup->Item[i].wmObj.yPos, 15, LCD_DIR_VERTICAL);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos+1, radioGroup->Item[i].wmObj.yPos, 15-1, LCD_DIR_VERTICAL);


			// Bot-Right Dark Border
			LCD_SetTextColor(LCD_COLOR_WHITE);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos+1, radioGroup->Item[i].wmObj.yPos+15-1, 15-1, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos+15-1, radioGroup->Item[i].wmObj.yPos+1, 15-1, LCD_DIR_VERTICAL);
			LCD_SetTextColor(radioGroup->Item[i].wmObj.BorderColor);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos+2, radioGroup->Item[i].wmObj.yPos+15-2, 15-3, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(radioGroup->Item[i].wmObj.xPos+15-2, radioGroup->Item[i].wmObj.yPos+2, 15-3, LCD_DIR_VERTICAL);
			// Center
			if (radioGroup->wmObj.Enable)
				LCD_SetTextColor(LCD_COLOR_WHITE);
			else
				LCD_SetTextColor(LCD_COLOR_GREYL);
			LCD_DrawFillRect(radioGroup->Item[i].wmObj.xPos+2,radioGroup->Item[i].wmObj.yPos+2,15-4,15-4);
			if (radioGroup->ItemSelected == i)
			{
				if (radioGroup->wmObj.Enable)
					LCD_SetTextColor(LCD_COLOR_BLACK);
				else
					LCD_SetTextColor(LCD_COLOR_GREYD);
				LCD_DrawFillRect(radioGroup->Item[i].wmObj.xPos+4,radioGroup->Item[i].wmObj.yPos+4,15-8,15-8);
			}


			LCD_SetFont(radioGroup->Item[i].wmTxt.vFont);
			if (radioGroup->wmObj.Enable)
				LCD_SetColors(radioGroup->wmTxt.TextColor, radioGroup->wmObj.Color);
			else
				LCD_SetColors(guiChangeColorLight(radioGroup->wmTxt.TextColor, 120), radioGroup->wmObj.Color);
			LCD_DrawString(radioGroup->Item[i].wmTxt.Text, radioGroup->Item[i].wmTxt.TextLen, radioGroup->Item[i].wmTxt.TextPosX, radioGroup->Item[i].wmTxt.TextPosY);
		}
	}
}

void RadioGroupStateRefresh(GUI_RADIO_GROUP * radioGroup)
{
	uint16_t i;
	if (radioGroup->wmObj.Visible)
	{
		// Items text
		for (i = 0; i < radioGroup->NumItem; i++)
		{
			// check symbol

			// Center
			if (radioGroup->wmObj.Enable)
				LCD_SetTextColor(LCD_COLOR_WHITE);
			else
				LCD_SetTextColor(LCD_COLOR_GREYL);
			LCD_DrawFillRect(radioGroup->Item[i].wmObj.xPos+2,radioGroup->Item[i].wmObj.yPos+2,15-4,15-4);
			if (radioGroup->ItemSelected == i)
			{
				if (radioGroup->wmObj.Enable)
					LCD_SetTextColor(LCD_COLOR_BLACK);
				else
					LCD_SetTextColor(LCD_COLOR_GREYD);
				LCD_DrawFillRect(radioGroup->Item[i].wmObj.xPos+4,radioGroup->Item[i].wmObj.yPos+4,15-8,15-8);
			}
		}
	}
}

void RadioGroupTouchControl(GUI_RADIO_GROUP * radioGroup, int16_t xTouch, int16_t yTouch)
{
	uint16_t i;

	if (radioGroup->wmObj.Enable)
	{
		// Items text
		for (i = 0; i < radioGroup->NumItem; i++)
		{
			radioGroup->Item[i].wmObj.Enable = 1;
			radioGroup->Item[i].wmObj.Visible = 1;
			wmTouchControl(&radioGroup->Item[i].wmObj, &radioGroup->Item[i].wmTouch, xTouch, yTouch);
			if (radioGroup->Item[i].wmTouch.JustReleased)
			{
				radioGroup->Item[i].wmTouch.JustReleased = 0;
				radioGroup->ItemSelected = i;
				RadioGroupStateRefresh(radioGroup);
			}
		}
	}
}
