/*
 * HMI_Control.h
 *
 *  Created on: 08.05.2013
 *      Author: Andrey Fursov
 */

#ifndef HMI_CONTROL_H_
#define HMI_CONTROL_H_

#define MAX_NUM_TXT_BUTTON	16
#define MAX_NUM_CHECK_BOX 	8
#define MAX_NUM_LABEL		8
#define MAX_NUM_RADIO_GROUP 2
#define MAX_NUM_UDBOX		2
#define MAX_NUM_CHART 		1

typedef struct
{
	TEXT_BUTTON textButton[MAX_NUM_TXT_BUTTON];
	GUI_CHECK_BOX checkBox[MAX_NUM_CHECK_BOX];
	GUI_LABEL label[MAX_NUM_LABEL];
	GUI_RADIO_GROUP radioGroup[MAX_NUM_RADIO_GROUP];
	GUI_UPDOWN_BOX	udBox[MAX_NUM_UDBOX];
	GUI_CHART chart[MAX_NUM_CHART];
	int16_t xTouch;
	int16_t yTouch;

} GUI_ELEMENTS;

enum WINDOW_ID {winInit, winMain, winUartCfg, winMenu, winPlot};
#include "winMain.h"
#include "winUartCfg.h"
#include "winPlot.h"
//*******************************************************************
// prototypes
//*******************************************************************
extern void HMI_Control(void);
extern void HMI_ChangeWindow(enum WINDOW_ID);
extern void HMI_OnPaint(void);
extern void HMI_TouchCtrl(void);

extern void HMIBtn_Exit(void);


#endif /* HMI_CONTROL_H_ */
