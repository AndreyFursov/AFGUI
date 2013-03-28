/*
 * guiUpDownBox.h
 *
 *  Created on: 22.03.2013
 *      Author: Andrey Fursov
 */

#ifndef GUIUPDOWNBOX_H_
#define GUIUPDOWNBOX_H_

#include "gui.h"

typedef struct
{
	WM_OBJ	wmObj;
	TEXT_BUTTON btnUp;
	TEXT_BUTTON btnDown;
	GUI_LABEL	wmLblHead;
	GUI_LABEL	wmLblEdit;

	char 		strValue[16];

	int32_t 	Value;
	int32_t 	ValueMax;
	int32_t 	ValueMin;
	int32_t 	ValueInc;
	int32_t 	ValueFastInc;
	uint8_t 	Format;
	unsigned 	CycleUpDown		: 1;
} GUI_UPDOWN_BOX;

extern void defaultUpDownBoxInit(GUI_UPDOWN_BOX * udBox, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void UpDownBoxLblTextInit(GUI_UPDOWN_BOX * udBox, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void UpDownBoxEditTextInit(GUI_UPDOWN_BOX * udBox, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void UpDownBoxTextPosInit(GUI_UPDOWN_BOX * udBox);
extern void UpDownBoxSetValue(GUI_UPDOWN_BOX * udBox, int32_t curValue, int32_t maxValue, int32_t minValue);
extern void UpDownBoxDraw(GUI_UPDOWN_BOX * udBox);
extern void UpDownTouchControl(GUI_UPDOWN_BOX * udBox, int16_t xTouch, int16_t yTouch);
extern void UpDownBoxSetValue(GUI_UPDOWN_BOX * udBox, int32_t curValue, int32_t maxValue, int32_t minValue);

#endif /* GUIUPDOWNBOX_H_ */
