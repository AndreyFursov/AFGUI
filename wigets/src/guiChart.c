/*
 * guiChart.c
 *
 *  Created on: 02.01.2013
 *      Author: Andrey
 */

#include "gui.h"

void defaultChartInit(GUI_CHART * chart, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

	chart->wmObj.xPos 			= x;
	chart->wmObj.yPos 			= y;
	chart->wmObj.Width 			= width;
	chart->wmObj.Height 		= height;


	chart->wmObj.Color 			= LCD_COLOR_BLACK;
	chart->LineColor			= LCD_COLOR_GREEN;

	chart->wmObj.BorderColor 	= LCD_COLOR_WHITE;
	chart->wmObj.BorderWidth	= 1;
	chart->Dot_nLine			= 0;


	chart->wmObj.Visible 		= 0;
	chart->wmObj.Enable 		= 0;
}

void chartSetData(GUI_CHART * chart, int16_t * data, uint16_t numData)
{
	uint16_t i, point;
	if (numData < chart->wmObj.Width-1)
		point = numData;
	else
		point = chart->wmObj.Width-1;
	chart->numPoint = numData;
	for (i = 0; i < point; i++)
	{
		if (data[i] < chart->wmObj.Height-1  && data[i] > 0)
			chart->table[i] = data[i];
		else
		{
			if (data[i] >= chart->wmObj.Height)
				chart->table[i] = chart->wmObj.Height-1;
			else
				chart->table[i] = 0;
		}
	}
}


void guiChartDraw(GUI_CHART * chart)
{
	uint16_t i;
	//uint16_t  xGridSpace, yGridSpace;

	if (chart->wmObj.Visible)
	{
		// Axes
		LCD_SetTextColor(chart->wmObj.BorderColor);

		LCD_DrawLine(chart->wmObj.xPos, chart->wmObj.yPos, 						chart->wmObj.Height, 	LCD_DIR_VERTICAL);
		LCD_DrawLine(chart->wmObj.xPos, chart->wmObj.yPos + chart->wmObj.Height-1, 	chart->wmObj.Width, 	LCD_DIR_HORIZONTAL);
		LCD_SetTextColor(chart->wmObj.Color);
		LCD_DrawFillRect(chart->wmObj.xPos+1, chart->wmObj.yPos, chart->wmObj.Width - 1, chart->wmObj.Height - 1);

		// Grid Lines

		// Graph
		LCD_SetTextColor(chart->LineColor);
		for (i = 0; i <  chart->wmObj.Width-1; i++)
		{
			if (chart->table[i] > chart->wmObj.Height-1) chart->table[i] = chart->wmObj.Height-11;
			if (chart->Dot_nLine)	// dot graph
				LCD_PutPixel(chart->wmObj.xPos+1+i, chart->wmObj.yPos + chart->wmObj.Height - 1 - chart->table[i]);
			else					// line graph (histogram)
				LCD_DrawLine(chart->wmObj.xPos+1+i,
							chart->wmObj.yPos + chart->wmObj.Height - 1 - chart->table[i],
							chart->table[i],
							LCD_DIR_VERTICAL);
		}
	}
}

//void guiChartFastClear(GUI_CHART * chart)
//{
//	uint16_t i;
//	//uint16_t  xGridSpace, yGridSpace;
//
//	if (chart->wmObj.Visible)
//	{
//		// Graph
//		LCD_SetTextColor(chart->wmObj.Color);
//		for (i = 0; i <  chart->wmObj.Width-1; i++)
//		{
//			if (chart->table[i] > chart->wmObj.Height-1) chart->table[i] = chart->wmObj.Height-1;
//			if (chart->Dot_nLine)	// dot graph
//				LCD_PutPixel(chart->wmObj.xPos+1+i, chart->wmObj.yPos + chart->wmObj.Height - 1 - chart->table[i]);
//			else					// line graph (histogram)
//				LCD_DrawLine(chart->wmObj.xPos+1+i,
//							chart->wmObj.yPos + chart->wmObj.Height - 1 - chart->table[i],
//							chart->table[i],
//							LCD_DIR_VERTICAL);
//		}
//	}
//}

void guiChartRefresh(GUI_CHART * chart, uint16_t _color)
{
	uint16_t i;
	//uint16_t  xGridSpace, yGridSpace;


	if (chart->wmObj.Visible)
	{
		// axis
		LCD_SetTextColor(chart->wmObj.BorderColor);
		LCD_DrawLine(chart->wmObj.xPos, chart->wmObj.yPos, 						chart->wmObj.Height, 	LCD_DIR_VERTICAL);
		LCD_DrawLine(chart->wmObj.xPos, chart->wmObj.yPos + chart->wmObj.Height-1, 	chart->wmObj.Width, 	LCD_DIR_HORIZONTAL);

		// Graph
		LCD_SetTextColor(_color);
		for (i = 0; i <  chart->wmObj.Width-1; i++)
		{
			if (chart->table[i] > chart->wmObj.Height-1) chart->table[i] = chart->wmObj.Height-1;
			if (chart->Dot_nLine)	// dot graph
				LCD_PutPixel(chart->wmObj.xPos+1+i, chart->wmObj.yPos + (chart->wmObj.Height - 1) - chart->table[i]);
			else					// line graph (histogram)
				LCD_DrawLine(chart->wmObj.xPos+1+i,
							chart->wmObj.yPos + chart->wmObj.Height - 1 - chart->table[i],
							chart->table[i],
							LCD_DIR_VERTICAL);
		}
	}
}
