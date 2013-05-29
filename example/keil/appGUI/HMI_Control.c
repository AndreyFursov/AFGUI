/*
 * HMI_Control.c
 *
 *  Created on: 08.05.2013
 *      Author: Andrey Fursov
 */
#include "gui.h"
#include "HMI_Control.h"

GUI_ELEMENTS gui;
enum WINDOW_ID windowID = winInit;



void HMI_Control(void)
{
	// Touch control
	touchGetSense(&gui.xTouch, &gui.yTouch);
	if (windowID == winInit)
	{
		HMI_ChangeWindow(winMain);
	}
	else
	{
		HMI_TouchCtrl();
	}
}

void HMI_ChangeWindow(enum WINDOW_ID winID)
{
	LCD_Clear(LCD_COLOR_GREYL);
	windowID = winID;
	switch(winID)
	{
		case winInit:
			windowID = winMain;
			break;
		case winMain:
			winMainInit(&gui);
			break;
		case winUartCfg:
			winUartCfgInit(&gui);
			break;
		case winPlot:
			winPlotInit(&gui);
			break;

		default:
			windowID = winInit;
			break;
	}
	HMI_OnPaint();
}

void HMI_OnPaint(void)
{
	uint16_t i;

	// button draw
	i = 0;
	while (gui.textButton[i].wmObj.Visible && i < MAX_NUM_TXT_BUTTON)
	{
		TextButtonDraw(&gui.textButton[i++]);
	}

	// label draw
	i = 0;
	while (gui.textButton[i].wmObj.Visible && i < MAX_NUM_LABEL)
	{
		guiLabelDraw(&gui.label[i++]);
	}

	// radio group draw
	i = 0;
	while (gui.radioGroup[i].wmObj.Visible && i < MAX_NUM_RADIO_GROUP)
	{
		RadioGroupDraw(&gui.radioGroup[i++]);
	}

	// check box draw
	i = 0;
	while (gui.checkBox[i].wmObj.Visible && i < MAX_NUM_RADIO_GROUP)
	{
		CheckBoxDraw(&gui.checkBox[i++]);
	}

	// updown box draw
	i = 0;
	while (gui.udBox[i].wmObj.Visible && i < MAX_NUM_UDBOX)
	{
		UpDownBoxDraw(&gui.udBox[i++]);
	}

	// chart box draw
	i = 0;
	while (gui.chart[i].wmObj.Visible && i < MAX_NUM_CHART)
	{
		guiChartDraw(&gui.chart[i++]);
	}


}

void HMI_TouchCtrl(void)
{
	uint16_t i;

	// button touch
	i = 0;
	while (gui.textButton[i].wmObj.Visible && i < MAX_NUM_TXT_BUTTON)
	{
		if (gui.textButton[i].wmObj.Enable)
		{
			wmTouchControl(&gui.textButton[i].wmObj, &gui.textButton[i].wmTouch, gui.xTouch, gui.yTouch);
			TextButtonStateRefresh(&gui.textButton[i]);
			if (gui.textButton[i].wmTouch.JustReleased && gui.textButton[i].fOnUntouch != 0)
			{
				gui.textButton[i].wmTouch.JustReleased = 0;
				gui.textButton[i].fOnUntouch();
				break;
			}
		}
		i++;
	}

	// radioGroup touch
	i = 0;
	while (gui.radioGroup[i].wmObj.Visible && i < MAX_NUM_RADIO_GROUP)
	{
		if (gui.radioGroup[i].wmObj.Enable)
			RadioGroupTouchControl(&gui.radioGroup[i], gui.xTouch, gui.yTouch);
		i++;
	}

	// check box touch
	i = 0;
	while (gui.checkBox[i].wmObj.Visible && i < MAX_NUM_CHECK_BOX)
	{
		if (gui.checkBox[i].wmObj.Enable)
			CheckBoxTouchControl(&gui.checkBox[i], gui.xTouch, gui.yTouch);
		i++;
	}

	// updown box touch
	i = 0;
	while (gui.udBox[i].wmObj.Visible && i < MAX_NUM_UDBOX)
	{
		if (gui.udBox[i].wmObj.Enable)
			UpDownTouchControl(&gui.udBox[i], gui.xTouch, gui.yTouch);
		i++;
	}

	// chart
	i = 0;
	while (gui.chart[i].wmObj.Visible && i < MAX_NUM_CHART)
	{
//		if (gui.chart[i].wmObj.Enable)
//			guiChartTouchControl(&gui.chart[i], gui.xTouch, gui.yTouch);
		i++;
	}

}



void HMIBtn_Exit(void)
{
	HMI_ChangeWindow(winMain);
}


