/*
 * winMain.c
 *
 *  Created on: 09.05.2013
 *      Author: Andrey Fursov
 */
#include "gui.h"
#include "HMI_Control.h"

#define WINMAIN_NUM_TXTBTN 	5
#define WINMAIN_NUM_LABEL 	2
#define WINMAIN_NUM_BUTTON 5
#define WINMAIN_NUM_BUTTON 5
#define WINMAIN_NUM_BUTTON 5

const char * wMainBtnStr[] =
{
	"Пуск",
	"Стоп",
	"Меню",
	"График",
	"Справка"

};

const char * wMainLblStr[] =
{
	"Тестовое приложение для AFGUI",
	"Пример применения"
};
char lblDateTimeStr[20];

uint16_t labelTextColor[] = 
{
	LCD_COLOR_BLACK,
	LCD_COLOR_BLUED,
};


//*********************************************************
// local prototypes
void btnMain_Start(void);
void btnMain_Stop(void);
void btnMain_Menu(void);
void btnMain_Plot(void);
void btnMain_Help(void);




void winMainInit(GUI_ELEMENTS * gui)
{
	uint16_t i;
	uint16_t x, y, width, height, space;
	
	
	// button init
	y = 5;
	space = 5;
	height = 24;
	x = space;
	width = (320 - (WINMAIN_NUM_TXTBTN+1)*space)/WINMAIN_NUM_TXTBTN;
		
	for (i = 0; i < WINMAIN_NUM_TXTBTN; i++)
	{
		defaultTextButtonInit(&gui->textButton[i], x, y, width, height);
		ButtonTextInit(&gui->textButton[i], (char *)wMainBtnStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
		gui->textButton[i].wmObj.Color = LCD_COLOR_GREYL;
		gui->textButton[i].wmObj.Enable = 1;
		gui->textButton[i].wmObj.Visible = 1;
		x += (width + space);
	}
	gui->textButton[i].wmObj.Visible = 0;

	gui->textButton[0].wmObj.Color = LCD_COLOR_GREEN;
	gui->textButton[1].wmObj.Color = LCD_COLOR_RED;
	
	// button func
	gui->textButton[2].fOnUntouch = &btnMain_Menu;
	gui->textButton[3].fOnUntouch = &btnMain_Plot;

	// label init
	y = 100;
	x = 0;
	width = 320;
	height = 20;
	for (i = 0; i < WINMAIN_NUM_LABEL; i++)
	{
		labelInit(&gui->label[i], x, y, width, height);
		gui->label[i].wmTxt.TextColor = labelTextColor[i];
		gui->label[i].wmObj.BorderColor = labelTextColor[i];
		gui->label[i].wmObj.BorderWidth = 2;
		gui->label[i].wmObj.Visible = 1;
		gui->label[i].wmObj.Enable = 1;
		wmTextInit(&gui->label[i].wmTxt, (char *)wMainLblStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
		wmObjTextInit(&gui->label[i].wmObj,  &gui->label[i].wmTxt);
		y += height + 1;
	}
	
// 	// date time label
// 	width = 110;
// 	height = 17;
// 	x = 320 - width;
// 	y = 240 - height;
// 	labelInit(&gui->label[i], x, y, width, height);
// 	gui->label[i].wmObj.BorderColor = LCD_COLOR_GREYD;
// 	gui->label[i].wmObj.BorderWidth = 1;
// 	gui->label[i].wmObj.Visible = 1;
// 	gui->label[i].wmObj.Enable = 1;
// 	gui->label[i].wmObj.Transparent = 0;
// 	wmTextInit(&gui->label[i].wmTxt, lblDateTimeStr, &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_RIGHT, V_ALIGN_CENTER);
// 	wmObjTextInit(&gui->label[i].wmObj,  &gui->label[i].wmTxt);
// 	i++;	
	
	
	gui->label[i].wmObj.Visible = 0;
	
	// radioGroup
	gui->radioGroup[0].wmObj.Visible = 0;

	// check box
	gui->checkBox[0].wmObj.Visible = 0;

	// up down box
	gui->udBox[0].wmObj.Visible = 0;

	// chart
	gui->chart[0].wmObj.Visible = 0;


};



void btnMain_Menu(void)
{
	HMI_ChangeWindow(winUartCfg);
}

void btnMain_Plot(void)
{
	HMI_ChangeWindow(winPlot);
}
