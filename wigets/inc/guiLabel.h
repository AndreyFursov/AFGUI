/*
 * guiLabel.h
 *
 *  Created on: 21.12.2012
 *      Author: Andrey
 */

#ifndef GUILABEL_H_
#define GUILABEL_H_

#include "gui.h"

typedef struct
{

	WM_OBJ	wmObj;
	WM_TEXT	wmTxt;

} GUI_LABEL;

extern void labelInit(GUI_LABEL * label, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void defaultLabelInit(GUI_LABEL * label, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t * text);
extern void guiLabelDraw(GUI_LABEL * label);


#endif /* GUILABEL_H_ */
