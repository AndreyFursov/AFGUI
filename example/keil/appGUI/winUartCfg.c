/*
 * winUartCfg.c
 *
 *  Created on: 24.05.2013
 *      Author: Andrey Fursov
 */


#include "gui.h"
#include "HMI_Control.h"

#define WINUARTCFG_NUM_TXTBTN	2
#define WINUARTCFG_NUM_LABEL 	1
#define WINUARTCFG_NUM_CHBOX 	1
#define WINUARTCFG_NUM_RGROUP 	1
#define WINUARTCFG_NUM_BUTTON 	5


// настраиваемые параметоры
// номер USART
// скорость
// 485
// четность


const char * wUartCfgBtnStr[] =
{
	"ОК",
	"Отмена",
};

const char * wUartCfgLblStr[] =
{
	"Настройка USART"
};

const char * wUartRg1Str[] =
{
	"Выбор USART",
	"USART 1",
	"USART 2",
	"USART 3",
	"UART 4",
};
const char * wUartRg2Str[] =
{
	"Четность",
	"Нет",
	"Чет",
	"Нечет"
};
const char * wUartcBoxStr[] =
{
	"RS-485",
};
const char * wUartudBoxHeadStr[] =
{
	"Скорость",
};


//*************************************************
// local prototypes
void btnUartCfg_CancelClick(void);
void btnUartCfg_OKClick(void);

//*************************************************
// functions

void winUartCfgInit(GUI_ELEMENTS * gui)
{
	uint16_t i;
	uint16_t x, y, width, height, space, row_y, col_x;


	// button init
	height = 24;
	width = 60;
	y = 235-height;
	space = (320 - WINUARTCFG_NUM_TXTBTN*width)/(WINUARTCFG_NUM_TXTBTN+1);
	x = space;

	for (i = 0; i < WINUARTCFG_NUM_TXTBTN; i++)
	{
		defaultTextButtonInit(&gui->textButton[i], x, y, width, height);
		ButtonTextInit(&gui->textButton[i], (char *)wUartCfgBtnStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_CENTER);
		gui->textButton[i].wmObj.Color = LCD_COLOR_GREYL;
		gui->textButton[i].wmObj.Enable = 1;
		gui->textButton[i].wmObj.Visible = 1;
		x += (width + space);
	}
	if (i < MAX_NUM_TXT_BUTTON-1)
	{
		gui->textButton[WINUARTCFG_NUM_TXTBTN].wmObj.Visible = 0;
	}


	gui->textButton[0].fOnUntouch = &btnUartCfg_OKClick;
	gui->textButton[1].fOnUntouch = &HMIBtn_Exit;


	// label init
	y = 1;
	x = 5;
	width = 319 - x;
	height = 16;
	for (i = 0; i < WINUARTCFG_NUM_LABEL; i++)
	{
		labelInit(&gui->label[i], x, y, width, height);
		//gui->label[i].wmTxt.TextColor = labelTextColor[i];
		//gui->label[i].wmObj.BorderColor = labelTextColor[i];
		gui->label[i].wmObj.BorderWidth = 0;
		gui->label[i].wmObj.Visible = 1;
		gui->label[i].wmObj.Enable = 1;
		wmTextInit(&gui->label[i].wmTxt, (char *)wUartCfgLblStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_LEFT, V_ALIGN_CENTER);
		wmObjTextInit(&gui->label[i].wmObj,  &gui->label[i].wmTxt);
		y += height + 1;
	}
	if (i < MAX_NUM_LABEL-1)
	{
		gui->label[i].wmObj.Visible = 0;
	}

	// радио-группа порт

	y = 20;
	width = 120;
	space = (320 - width*2)/3;
	x = space;
	height = 16*5+26;
	i = 0;
	defaultRadioGroupInit(&gui->radioGroup[i], x, y, width, height);
	defaultRadioGroupItemInit(&gui->radioGroup[i], 4, 0);
	RadioGroupTextInit(&gui->radioGroup[i], (char *)wUartRg1Str[0], &GL_ArialNarrow_15);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg1Str[1], &GL_ArialNarrow_15, 0);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg1Str[2], &GL_ArialNarrow_15, 1);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg1Str[3], &GL_ArialNarrow_15, 2);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg1Str[4], &GL_ArialNarrow_15, 3);
	gui->radioGroup[i].wmObj.Visible = 1;
	gui->radioGroup[i].wmObj.Enable = 1;
	i++;

	// радио-группа четность
	x += width + space;
	col_x = x;
	//height = 16*4+25;

	defaultRadioGroupInit(&gui->radioGroup[i], x, y, width, height);
	defaultRadioGroupItemInit(&gui->radioGroup[i], 3, 0);
	RadioGroupTextInit(&gui->radioGroup[i], (char *)wUartRg2Str[0], &GL_ArialNarrow_15);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg2Str[1], &GL_ArialNarrow_15, 0);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg2Str[2], &GL_ArialNarrow_15, 1);
	RadioGroupItemInit(&gui->radioGroup[i], (char *)wUartRg2Str[3], &GL_ArialNarrow_15, 2);
	gui->radioGroup[i].wmObj.Visible = 1;
	gui->radioGroup[i].wmObj.Enable = 1;
	i++;

	if (i < MAX_NUM_RADIO_GROUP-1)
	{
		gui->radioGroup[i].wmObj.Visible = 0;
	}

	// check-box
	x = space;
	y += height + 25;
	height = 16;
	row_y = y;

	//width = 100;

	for (i = 0; i < 1; i++)
	{
		defaultCheckInit(&gui->checkBox[i], x, y, width, height);
		CheckBoxTextInit(&gui->checkBox[i], (char *)wUartcBoxStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_LEFT, V_ALIGN_CENTER);
		gui->checkBox[i].wmObj.Enable = 1;
		gui->checkBox[i].wmObj.Visible = 1;

		//y  += height + 5;
	}
	if (i < MAX_NUM_CHECK_BOX-1)
	{
		gui->checkBox[i].wmObj.Visible = 0;
	}

	// up-down box
	y = row_y - 20;
	x = col_x;
	height = 32 + 15;

	for (i = 0; i < 1; i++)
	{
		UpDownBoxLblTextInit(&gui->udBox[i], (char *)wUartudBoxHeadStr[i], &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_CENTER, V_ALIGN_BOTTOM);
		UpDownBoxEditTextInit(&gui->udBox[i], gui->udBox[i].strValue, &GL_ArialNarrow_15, ROTATE_0, FLIP_NO, H_ALIGN_RIGHT, V_ALIGN_CENTER);
		defaultUpDownBoxInit(&gui->udBox[i], x, y, width, height);
		gui->udBox[i].CycleUpDown = 0;

		UpDownBoxSetValue(&gui->udBox[i], 9600, 115200, 1200);
		gui->udBox[i].ValueInc = 1200;

		UpDownBoxTextPosInit(&gui->udBox[i]);
		gui->udBox[i].wmObj.Enable = 1;
		gui->udBox[i].wmObj.Visible = 1;
		y  += height + 5;
	}
	if (i < MAX_NUM_UDBOX-1)
	{
		gui->udBox[i].wmObj.Visible = 0;
	}

	// chart
	gui->chart[0].wmObj.Visible = 0;
};




void btnUartCfg_CancelClick(void)
{

	HMI_ChangeWindow(winMain);

}

void btnUartCfg_OKClick(void)
{

	HMI_ChangeWindow(winMain);

}
