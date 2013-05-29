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

	uint8_t		table[320];
	int16_t 	numPoint;
	uint16_t 	xGridSpace;
	uint16_t 	yGridSpace;

	uint16_t 	LineColor;

	unsigned 	Dot_nLine	: 1;	// Dot/Line


} GUI_CHART;

extern void defaultChartInit(GUI_CHART * chart, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void chartSetData(GUI_CHART * chart, int16_t * data, uint16_t numData);
extern void guiChartDraw(GUI_CHART * chart);
extern void guiChartRefresh(GUI_CHART * chart, uint16_t _color);


#endif /* GUICHART_H_ */
