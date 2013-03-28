/*
 * guiCheckButton.h
 *
 *  Created on: 19.12.2012
 *      Author: Andrey
 */

#ifndef GUICHECKBOX_H_
#define GUICHECKBOX_H_

#include "gui.h"

typedef struct
{
	WM_OBJ	wmObj;
	WM_TEXT	wmTxt;
	WM_TOUCH wmTouch;
	unsigned 	Checked			: 1;
	unsigned 	Docked			: 1;



} GUI_CHECK_BOX;

extern void defaultCheckInit(GUI_CHECK_BOX * checkBox, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void CheckBoxTextInit(GUI_CHECK_BOX * checkBox, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void CheckBoxDraw(GUI_CHECK_BOX * checkBox);
extern void CheckBoxTouchControl(GUI_CHECK_BOX * checkBox, int16_t xTouch, int16_t yTouch);
extern void CheckBoxStateRefresh(GUI_CHECK_BOX * checkBox);

#endif /* GUICHECKBOX_H_ */
