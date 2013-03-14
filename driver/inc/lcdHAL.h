/*
 * lcdHAL.h
 *
 *  Created on: 08.01.2013
 *      Author: Andrey Fursov
 */

#ifndef LCDHAL_H_
#define LCDHAL_H_

#define LCD_PIXEL_WIDTH		320
#define LCD_PIXEL_HEIGHT	240

#define LCD_COLOR_RED		 	0xFC00
#define LCD_COLOR_REDD		 	0x8000
#define LCD_COLOR_GREEN 		0x03F0
#define LCD_COLOR_GREEND 		0x0200
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

//******************************************************************************************
// Init
extern void LCD_Init(void);

//******************************************************************************************
// Color function
extern void LCD_SetColors(volatile uint16_t _TextColor, volatile uint16_t _BackColor);
extern void LCD_GetColors(volatile uint16_t *_TextColor, volatile uint16_t *_BackColor);
extern void LCD_SetTextColor(volatile uint16_t Color);
extern void LCD_SetBackColor(volatile uint16_t Color);
// Font functions
extern void LCD_SetFont(V_FONT *fonts);
extern V_FONT *LCD_GetFont(void);


//******************************************************************************************
// LowLevel Function
extern void LCD_PutPixel(uint16_t x, uint16_t y);
extern void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
extern void LCD_DrawFillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
extern void LCD_DrawMonoPict(const uint32_t *Pict);
extern void LCD_WriteBMP(uint32_t BmpAddress);


#endif /* LCDHAL_H_ */
