/*
 * colors.h
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#ifndef COLORS_H_
#define COLORS_H_

#define LCD_COLOR_RED		 	0xFC00
#define LCD_COLOR_GREEN 		0x03F0
#define LCD_COLOR_BLUE	 		0x000F
#define LCD_COLOR_BLACK 		0x0000
#define LCD_COLOR_WHITE 		0xFFFF
#define LCD_COLOR_GREYL 		0xA28A
#define LCD_COLOR_GREYD 		0x6186
#define LCD_COLOR_YELLOW	 	0xFFF0
#define LCD_COLOR_ORANGE	 	0xFD10
#define LCD_COLOR_LIME	 		0x7FF0

#define COLOR_RED_MASK			0xFC00
#define COLOR_GREEN_MASK		0x03F0
#define COLOR_BLUE_MASK			0x000F

#define COLOR_RED_OFFSET		0x000A
#define COLOR_GREEN_OFFSET		0x0004
#define COLOR_BLUE_OFFSET		0x0000

typedef struct
{
	unsigned BLUE	: 4;
	unsigned GREEN	: 6;
	unsigned RED	: 6;
} GUI_COLOR;


extern uint16_t guiChangeColorLight(uint16_t color, uint16_t percent);

#endif /* COLORS_H_ */
