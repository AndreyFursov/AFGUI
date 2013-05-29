/*
 * guiUpDownBox.c
 *
 *  Created on: 22.03.2013
 *      Author: Andrey Fursov
 */

#include "gui.h"

void defaultUpDownBoxInit(GUI_UPDOWN_BOX * udBox, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	//unsigned int textWidth;
	uint16_t temp, yd;

	udBox->wmObj.xPos 			= x;
	udBox->wmObj.yPos 			= y;
	udBox->wmObj.Width 			= width;
	udBox->wmObj.Height 		= height;


	udBox->wmObj.Color 			= LCD_COLOR_GREYL;

	udBox->wmObj.BorderColor 	= LCD_COLOR_GREYL;
	udBox->wmObj.BorderWidth	= 1;

	udBox->wmObj.Visible 		= 0;
	udBox->wmObj.Enable 		= 0;
	udBox->CycleUpDown			= 1;

	if (udBox->wmLblHead.wmTxt.vFont == 0 || udBox->wmLblEdit.wmTxt.vFont == 0)
	{
		udBox->wmLblHead.wmTxt.vFont = &GL_ArialNarrow_15;
		udBox->wmLblEdit.wmTxt.vFont = &GL_ArialNarrow_15;
	}

	// upDownButtonInit
	temp = (height - udBox->wmLblHead.wmTxt.vFont->Height - 1)/2;
	yd = y + udBox->wmLblHead.wmTxt.vFont->Height;
	defaultTextButtonInit(&udBox->btnUp, x+width-temp, yd, temp, temp);
	defaultTextButtonInit(&udBox->btnDown, x+width-temp, yd+temp, temp, temp);
	if (udBox->btnUp.wmObj.Height - 2*udBox->btnUp.wmObj.BorderWidth > 14)
	{
		ButtonTextInit(&udBox->btnUp, "^", &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
		ButtonTextInit(&udBox->btnDown, "v", &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
	}
	else
	{
		ButtonTextInit(&udBox->btnUp, "^", &GL_Arial_12, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
		ButtonTextInit(&udBox->btnDown, "v", &GL_Arial_12, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
	}

	// labels position
	labelInit(&udBox->wmLblHead, x, y, width, udBox->wmLblHead.wmTxt.vFont->Height);
	udBox->wmLblHead.wmObj.BorderWidth = 0;
	udBox->wmLblHead.wmObj.Color = LCD_COLOR_GREYL;
	udBox->wmLblHead.wmObj.Visual3D = 0;

	labelInit(&udBox->wmLblEdit, x, yd, width-temp-1, height-(yd-y)-1);
	udBox->wmLblEdit.wmObj.BorderWidth = 2;
	udBox->wmLblEdit.wmObj.Color = LCD_COLOR_WHITE;
	udBox->wmLblEdit.wmObj.Visual3D = 1;
	udBox->wmLblEdit.wmObj.Transparent = 0;

	udBox->btnUp.wmObj.Enable = 1;
	udBox->btnUp.wmObj.Visible = 1;
	udBox->btnDown.wmObj.Enable = 1;
	udBox->btnDown.wmObj.Visible = 1;
	udBox->wmLblHead.wmObj.Enable = 1;
	udBox->wmLblHead.wmObj.Visible = 1;
	udBox->wmLblEdit.wmObj.Enable = 1;
	udBox->wmLblEdit.wmObj.Visible = 1;

	// default Values init
	udBox->Value = 0;
	udBox->ValueMax = 100;
	udBox->ValueMin = 0;
	udBox->ValueInc = 1;
	udBox->ValueFastInc = 5;

	wmTouchInit(&udBox->btnUp.wmTouch);
	wmTouchInit(&udBox->btnDown.wmTouch);
};

void UpDownBoxLblTextInit(GUI_UPDOWN_BOX * udBox, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)
{
	wmTextInit(&udBox->wmLblHead.wmTxt, text, vFont, rot, flip, align_h, align_v);
}

void UpDownBoxEditTextInit(GUI_UPDOWN_BOX * udBox, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)
{
	wmTextInit(&udBox->wmLblEdit.wmTxt, text, vFont, rot, flip, align_h, align_v);
}

void UpDownBoxTextPosInit(GUI_UPDOWN_BOX * udBox)
{
	wmTextPositionInit(&udBox->wmLblHead.wmTxt,
						udBox->wmLblHead.wmObj.xPos + udBox->wmLblHead.wmObj.BorderWidth,
						udBox->wmLblHead.wmObj.yPos + udBox->wmLblHead.wmObj.BorderWidth,
						udBox->wmLblHead.wmObj.Width - 2*udBox->wmLblHead.wmObj.BorderWidth,
						udBox->wmLblHead.wmObj.Height - 2*udBox->wmLblHead.wmObj.BorderWidth
						);

	wmTextPositionInit(&udBox->wmLblEdit.wmTxt,
						udBox->wmLblEdit.wmObj.xPos + udBox->wmLblEdit.wmObj.BorderWidth,
						udBox->wmLblEdit.wmObj.yPos + udBox->wmLblEdit.wmObj.BorderWidth,
						udBox->wmLblEdit.wmObj.Width - 2*udBox->wmLblEdit.wmObj.BorderWidth,
						udBox->wmLblEdit.wmObj.Height - 2*udBox->wmLblEdit.wmObj.BorderWidth
						);
}

extern void UpDownBoxDraw(GUI_UPDOWN_BOX * udBox)
{
	if (udBox->wmObj.Visible)
	{
		// label
		guiLabelDraw(&udBox->wmLblHead);
		guiLabelDraw(&udBox->wmLblEdit);

		// buttons
		TextButtonDraw(&udBox->btnUp);
		TextButtonDraw(&udBox->btnDown);
	}
}

void UpDownBoxSetValue(GUI_UPDOWN_BOX * udBox, int32_t curValue, int32_t maxValue, int32_t minValue)
{
	if (maxValue < minValue) maxValue = minValue;
	if (curValue > maxValue) curValue = maxValue;
	if (curValue < minValue) curValue = minValue;
	udBox->Value = curValue;
	udBox->ValueMax = maxValue;
	udBox->ValueMin = minValue;
	udBox->ValueInc = 1;
	udBox->Format = 0;
	udBox->ValueFastInc = (maxValue - minValue)/20;
	if (udBox->ValueFastInc < 1) udBox->ValueFastInc = 1;
	int32toString(udBox->strValue, udBox->Value, 15, udBox->Format);
}

void UpDownBoxValueRedraw(GUI_UPDOWN_BOX * udBox)
{

}



void UpDownTouchControl(GUI_UPDOWN_BOX * udBox, int16_t xTouch, int16_t yTouch)
{
	uint16_t newData = 0;
	wmTouchControl(&udBox->btnUp.wmObj, &udBox->btnUp.wmTouch, xTouch, yTouch);
	wmTouchControl(&udBox->btnDown.wmObj, &udBox->btnDown.wmTouch, xTouch, yTouch);

	if (udBox->btnUp.wmTouch.Changed)
	{
		udBox->btnUp.wmTouch.Changed = 0;
		TextButtonStateRefresh(&udBox->btnUp);
		if (udBox->btnUp.wmTouch.JustPressed)
		{
			udBox->btnUp.wmTouch.JustPressed = 0;
			if (udBox->Value <= udBox->ValueMax - udBox->ValueInc) udBox->Value += udBox->ValueInc;
			else
				if (udBox->CycleUpDown) udBox->Value = udBox->ValueMin;
			newData = 1;
		}
	}

	if (udBox->btnUp.wmTouch.Pressed  && udBox->btnUp.wmTouch.Hold)
	{
		if (udBox->Value <= udBox->ValueMax - udBox->ValueInc) udBox->Value += udBox->ValueInc;
		else
			if (udBox->CycleUpDown) udBox->Value = udBox->ValueMin;
		newData = 1;
	}

	if (udBox->btnDown.wmTouch.Changed)
	{
		udBox->btnDown.wmTouch.Changed = 0;
		TextButtonStateRefresh(&udBox->btnDown);
		if (udBox->btnDown.wmTouch.JustPressed)
		{
			udBox->btnDown.wmTouch.JustPressed = 0;
			if (udBox->Value >= udBox->ValueMin + udBox->ValueInc) udBox->Value -= udBox->ValueInc;
			else
				if (udBox->CycleUpDown) udBox->Value = udBox->ValueMax;
			newData = 1;
		}
	}

	if (udBox->btnDown.wmTouch.Pressed  && udBox->btnDown.wmTouch.Hold)
	{
		if (udBox->Value >= udBox->ValueMin + udBox->ValueInc) udBox->Value -= udBox->ValueInc;
		else
			if (udBox->CycleUpDown) udBox->Value = udBox->ValueMax;

		newData = 1;

	}

	if (newData)
	{
		int32toString(udBox->strValue, udBox->Value, 15, udBox->Format);
		wmTextPositionInit(&udBox->wmLblEdit.wmTxt,
							udBox->wmLblEdit.wmObj.xPos + udBox->wmLblEdit.wmObj.BorderWidth,
							udBox->wmLblEdit.wmObj.yPos + udBox->wmLblEdit.wmObj.BorderWidth,
							udBox->wmLblEdit.wmObj.Width - 2*udBox->wmLblEdit.wmObj.BorderWidth,
							udBox->wmLblEdit.wmObj.Height - 2*udBox->wmLblEdit.wmObj.BorderWidth
							);

		guiLabelDraw(&udBox->wmLblEdit);
	}
}
