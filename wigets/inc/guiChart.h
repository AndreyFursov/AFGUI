/*
 * guiChart.h
 *
 *  Created on: 02.01.2013
 *      Author: Andrey
 */

#ifndef GUICHART_H_
#define GUICHART_H_

#include "gui.h"

typedef struct
{

	WM_OBJ		wmObj;
	WM_TEXT		wmTxt;
	WM_TOUCH 	wmTouch;

	unsigned 	Dot	: 1;	// Dot/Line
	uint16_t *	table;
	uint16_t *	chartWidth;
	uint16_t *	chartHeight;



} GUI_CHART;

extern void defaultChartInit(GUI_CHART * chart, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void ChartTextInit(GUI_CHART * chart, uint8_t *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void guiChartDraw(GUI_CHART * chart);



#endif /* GUICHART_H_ */
