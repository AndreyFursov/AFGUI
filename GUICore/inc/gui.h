/*
 * gui.h
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#ifndef GUI_H_
#define GUI_H_

#ifndef __stdint_h

#define int8_t 	 	char
#define int16_t 	short
#define int32_t 	int

#define uint8_t 	unsigned char
#define uint16_t 	unsigned short
#define uint32_t 	unsigned int
#endif

#include "guiColor.h"
#include "guiFonts.h"

// Driver
#include "ads7843.h"
#include "mkDriver.h"
#include "lcdHAL.h"

// Core
#include "guiPrimitives.h"
#include "afTime.h"


// Widgets
#include "widget.h"
#include "guiTextButton.h"
#include "guiCheckBox.h"
#include "guiLabel.h"
#include "guiText.h"
#include "guiChart.h"


// Default
#define LCD_DEFAULT_FONT GL_ArialBold_16

// Defines
#define H_ALIGN_LEFT		0
#define H_ALIGN_CENTER		1
#define H_ALIGN_RIGHT		2

#define V_ALIGN_TOP			0
#define V_ALIGN_CENTER		1
#define V_ALIGN_BOTTOM		2

#define DIR_LEFT_TO_RIGHT	0
#define DIR_RIGHT_TO_LEFT	1

#define ROTATE_0			0
#define ROTATE_90			1
#define ROTATE_180			2
#define ROTATE_270			3

#define FLIP_NO				0
#define FLIP_YES			1

#define LCD_DIR_HORIZONTAL	0x0000
#define LCD_DIR_VERTICAL	0x0001




#endif /* GUI_H_ */
