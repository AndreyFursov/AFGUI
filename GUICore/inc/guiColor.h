/*
 * colors.h
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#ifndef COLORS_H_
#define COLORS_H_


typedef struct
{
	unsigned BLUE	: 4;
	unsigned GREEN	: 6;
	unsigned RED	: 6;
} GUI_COLOR;


extern uint16_t guiChangeColorLight(uint16_t color, uint16_t percent);
enum LCD_COLOR_MODE {colorIndex, colorRGB};
enum LCD_COLOR_GRAM {lcdColorRGB_565, lcdColorRGB_666, lcdColorARGB_a888};

//******************************************************************************************
// Color function
extern void LCD_SetColorMode(enum LCD_COLOR_MODE _colorMode);
extern void LCD_SetColorGRAM(enum LCD_COLOR_GRAM _colorGRAM);
extern enum LCD_COLOR_MODE LCD_GetColorMode(void);
extern enum LCD_COLOR_GRAM LCD_GetColorGRAM(void);

extern void LCD_SetColors(volatile uint16_t _TextColor, volatile uint16_t _BackColor);
extern void LCD_GetColors(volatile uint16_t *_TextColor, volatile uint16_t *_BackColor);
extern void LCD_SetTextColor(volatile uint16_t Color);
extern void LCD_SetBackColor(volatile uint16_t Color);



#define COLOR_RED_MASK_565		0xF8
#define COLOR_GREEN_MASK_565	0xFC
#define COLOR_BLUE_MASK_565		0xF8

#define COLOR_RED_OFFSET_565	0x08
#define COLOR_GREEN_OFFSET_565	0x03
#define COLOR_BLUE_OFFSET_565	0x03

#define COLOR_RED_MASK_666		0xFC
#define COLOR_GREEN_MASK_666	0xFC
#define COLOR_BLUE_MASK_666		0xFC

#define COLOR_RED_OFFSET_666	24
#define COLOR_GREEN_OFFSET_666	18
#define COLOR_BLUE_OFFSET_666	12

#endif /* COLORS_H_ */
