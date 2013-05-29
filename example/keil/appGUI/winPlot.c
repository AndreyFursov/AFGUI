/*
 * winPlot.c
 *
 *  Created on: 28.05.2013
 *      Author: Andrey Fursov
 */


#include "gui.h"
#include "math.h"
#include "HMI_Control.h"

#define WINPLOT_NUM_TXTBTN	6
#define WINPLOT_NUM_LABEL 	1
#define WINPLOT_NUM_CHBOX 	1
#define WINPLOT_NUM_RGROUP 	1
#define WINPLOT_NUM_BUTTON 	5

GUI_ELEMENTS * wPlotGui;


// настраиваемые параметоры
// номер USART
// скорость
// 485
// четность


const char * wPlotBtnStr[] =
{
	"<",
	">",
	"*",
	"^",
	"v",
	"Выход"
};

const char * wPlotCfgLblStr[] =
{
	"График"
};


float coef_Y = 0.5, coef_X = 2;
uint16_t gWidth, gHeight;


//*************************************************
// local prototypes
void plotDataCalculate(void);
void plotDown(void);
void plotUp(void);
void plotLeft(void);
void plotRight(void);
void plotCenter(void);


//*************************************************
// functions

void winPlotInit(GUI_ELEMENTS * gui)
{
	uint16_t i;
	uint16_t x, y, width, height, space;

	wPlotGui = gui;
	// button init
	y = 16;
	space = 5;
	height = 24;
	x = space;
	width = (320 - (WINPLOT_NUM_TXTBTN+1)*space)/WINPLOT_NUM_TXTBTN;

	for (i = 0; i < WINPLOT_NUM_TXTBTN; i++)
	{
		defaultTextButtonInit(&gui->textButton[i], x, y, width, height);
		ButtonTextInit(&gui->textButton[i], (char *)wPlotBtnStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
		gui->textButton[i].wmObj.Color = LCD_COLOR_GREYL;
		gui->textButton[i].wmObj.Enable = 1;
		gui->textButton[i].wmObj.Visible = 1;
		x += (width + space);
	}
	gui->textButton[i].wmObj.Visible = 0;

	// button func
	gui->textButton[0].fOnUntouch = &plotLeft;
	gui->textButton[1].fOnUntouch = &plotRight;
	gui->textButton[2].fOnUntouch = & plotCenter;
	gui->textButton[3].fOnUntouch = &plotUp;
	gui->textButton[4].fOnUntouch = &plotDown;
	gui->textButton[5].fOnUntouch = &HMIBtn_Exit;

	// label init
	y = 1;
	x = 5;
	width = 100;
	height = 15;
	for (i = 0; i < WINPLOT_NUM_LABEL; i++)
	{
		labelInit(&gui->label[i], x, y, width, height);
		//gui->label[i].wmTxt.TextColor = LCD_COLOR_BLACK;
		//gui->label[i].wmObj.BorderWidth = 0;
		gui->label[i].wmObj.Visible = 1;
		gui->label[i].wmObj.Enable = 1;
		wmTextInit(&gui->label[i].wmTxt, (char *)wPlotCfgLblStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_LEFT, V_ALIGN_CENTER);
		wmObjTextInit(&gui->label[i].wmObj,  &gui->label[i].wmTxt);
		y += height + 1;
	}
	gui->label[i].wmObj.Visible = 0;

	// radioGroup
	gui->radioGroup[0].wmObj.Visible = 0;

	// check box
	gui->checkBox[0].wmObj.Visible = 0;

	// up down box
	gui->udBox[0].wmObj.Visible = 0;

	// chart
	x = 60;
	y = 25+16;
	gHeight  = 240 - y - 18;
	gWidth = 320 - x - 5;
	defaultChartInit(&gui->chart[0], x, y, gWidth, gHeight);
	gui->chart[0].Dot_nLine = 1;

	coef_Y = 0.5;
	coef_X = 2;
	plotDataCalculate();
	gui->chart[0].wmObj.Visible = 1;
	gui->chart[0].wmObj.Enable = 1;
};

void plotDown(void)
{
	coef_Y /= 1.25;
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].wmObj.Color);
	plotDataCalculate();
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].LineColor);

}
void plotUp(void)
{
	coef_Y *= 1.25;
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].wmObj.Color);
	plotDataCalculate();
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].LineColor);
}

void plotLeft(void)
{
	coef_X /= 2;
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].wmObj.Color);
	plotDataCalculate();
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].LineColor);
}

void plotRight(void)
{
	coef_X *= 2;
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].wmObj.Color);
	plotDataCalculate();
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].LineColor);
}

void plotCenter(void)
{
	coef_Y = 0.5;
	coef_X = 2;
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].wmObj.Color);
	plotDataCalculate();
	guiChartRefresh(&wPlotGui->chart[0], wPlotGui->chart[0].LineColor);
}

void plotDataCalculate(void)
{
	uint16_t i;
	for (i = 0; i < gWidth-1; i++)
	{
		wPlotGui->chart[0].table[i] = gHeight/2 + (gHeight*coef_Y-5)*sin(coef_X*3.14159/((float)gWidth)*i);
	}
}
