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

} TEXT_BUTTON;

extern void defaultTextButtonInit(TEXT_BUTTON * button, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void ButtonTextInit(TEXT_BUTTON * button, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void TextButtonDraw(TEXT_BUTTON * button);
extern void TextButtonStateRefresh(TEXT_BUTTON * button);

#endif /* GUITEXTBUTTON_H_ */
