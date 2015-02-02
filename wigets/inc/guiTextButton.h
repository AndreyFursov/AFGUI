/*
 * guiTextButton.h
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#ifndef GUITEXTBUTTON_H_
#define GUITEXTBUTTON_H_

#include "gui.h"

typedef struct
{

	WM_OBJ		wmObj;
	WM_TEXT		wmTxt;
	WM_TOUCH 	wmTouch;
	void (*fOnTouch)();
	void (*fOnUntouch)();
} TEXT_BUTTON;

typedef struct
{
	int 		ID;
	TEXT_BUTTON	btn;
	char 		symCode;
} STEXT_BUTTON;

extern void defaultTextButtonInit(TEXT_BUTTON * button, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void ButtonTextInit(TEXT_BUTTON * button, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void TextButtonDraw(TEXT_BUTTON * button);
extern void TextButtonStateRefresh(TEXT_BUTTON * button);
extern void TextButtonTouchControl(TEXT_BUTTON * button,  int16_t xTouch, int16_t yTouch);

extern int STextButtonTouchControl(STEXT_BUTTON * sBtn,  int16_t xTouch, int16_t yTouch);

#endif /* GUITEXTBUTTON_H_ */
