/*
 * guiEditBox.h
 *
 *  Created on: 18 џэт. 2015 у.
 *      Author: Andrey Fursov
 */
#ifndef GUIEDITBOX_H_
#define GUIEDITBOX_H_

typedef struct
{
	WM_OBJ		wmObj;
	WM_TEXT		wmTxt;
	WM_TOUCH 	wmTouch;

	uint16_t	maxStringLength;
	uint16_t	curPosition;

	unsigned	modeInsert 	: 1;
	void (*fAddSymbol)(char code);
	int (*fOnUntouch)();


} GUI_EDIT_BOX;

extern void defaultEditBoxInit(GUI_EDIT_BOX * pEditBox, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void EditBoxTextInit(GUI_EDIT_BOX * pEditBox, char *text, V_FONT * vFont, uint16_t maxStrLength, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void EditBoxDraw(GUI_EDIT_BOX * pEditBox);
extern int EditBoxTouchControl(GUI_EDIT_BOX * pEditBox, int16_t xTouch, int16_t yTouch);
extern void EditBoxStateRefresh(GUI_EDIT_BOX * pEditBox);
extern void EditBoxTextPosInit(GUI_EDIT_BOX * pEditBox);
extern int EditBoxAddSymbol(GUI_EDIT_BOX * pEditBox, char symbol);
extern int EditBoxSelect(GUI_EDIT_BOX * pEditBox);
extern int EditBoxUnselect(GUI_EDIT_BOX * pEditBox);
extern int EditBoxAppendSymbol(GUI_EDIT_BOX * pEditBox, char symbol);
#endif /* GUIEDITBOX_H_ */
