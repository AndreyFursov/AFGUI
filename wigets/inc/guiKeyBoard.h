/*
 * guiKeyBoard.h
 *
 *  Created on: 16.01.2015
 *      Author: Andrey Fursov
 */

#ifndef GUIKEYBOARD_H_
#define GUIKEYBOARD_H_

#include "gui.h"
typedef struct
{
	WM_OBJ			wmObj;
	STEXT_BUTTON 	* sBtn;		// указатель на массив кнопок
	char 			** name;	// подпись кнопки
	char 			* code;		// код нажатия
	V_FONT 			* vFont;	// указатель на шрифт
	uint8_t 		numColumn;	// количество столбцов
	uint8_t 		numRow;		// количество строк
	uint16_t		numKey;		// общее кол-во кнопок
} GUI_KEYBOARD;

extern void defaultKeyBoardInit(GUI_KEYBOARD * pKeyBoard, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void KeyBoardInit(GUI_KEYBOARD * pKeyBoard, STEXT_BUTTON * pSbtn, V_FONT * vFont, char ** pCode, uint8_t numColumn, uint8_t numRow);
extern void KeyBoardDraw(GUI_KEYBOARD * pKeyBoard);
extern void KeyBoardTouchControl(GUI_KEYBOARD * pKeyBoard, int16_t xTouch, int16_t yTouch);
extern void KeyBoardStateRefresh(GUI_KEYBOARD * pKeyBoard);
extern void KeyBoardRefresh(GUI_KEYBOARD * pKeyBoard);
extern void KeyBoardCodeInit(GUI_KEYBOARD * pKeyBoard, char * pCode);


#endif /* GUICHECKBOX_H_ */
