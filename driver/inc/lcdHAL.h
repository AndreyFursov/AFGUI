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

#define LCD_COLOR_WHITE 		0
#define LCD_COLOR_TEAL	 		1
#define LCD_COLOR_PURPLE 		2
#define LCD_COLOR_BLUE	 		3
#define LCD_COLOR_GREYL 		4
#define LCD_COLOR_GREYD 		5
#define LCD_COLOR_TEALD	 		6
#define LCD_COLOR_PURPLED 		7
#define LCD_COLOR_BLUED	 		8
#define LCD_COLOR_YELLOW	 	9
#define LCD_COLOR_GREEN 		10
#define LCD_COLOR_YELLOWD	 	11
#define LCD_COLOR_GREEND 		12
#define LCD_COLOR_RED		 	13
#define LCD_COLOR_REDD		 	14
#define LCD_COLOR_BLACK 		15

#define COLOR_24B_WHITE 		0x00FFFFFFU
#define COLOR_24B_TEAL	 		0x0000FFFFU
#define COLOR_24B_PURPLE 		0x00FF00FFU
#define COLOR_24B_BLUE	 		0x000000FFU
#define COLOR_24B_GREYL 		0x00C0C0C0U
#define COLOR_24B_GREYD 		0x00808080U
#define COLOR_24B_TEALD	 		0x00008080U
#define COLOR_24B_PURPLED 		0x00800080U
#define COLOR_24B_BLUED	 		0x00000080U
#define COLOR_24B_YELLOW	 	0x00FFFF00U
#define COLOR_24B_GREEN 		0x0000FF00U
#define COLOR_24B_YELLOWD	 	0x00808000U
#define COLOR_24B_GREEND 		0x00008000U
#define COLOR_24B_RED		 	0x00FF0000U
#define COLOR_24B_REDD		 	0x00800000U
#define COLOR_24B_BLACK 		0x00000000U


//******************************************************************************************
// Init
extern void LCD_Init(void);


//******************************************************************************************
// Font functions
extern void LCD_SetFont(V_FONT *fonts);
extern V_FONT *LCD_GetFont(void);


//******************************************************************************************
// LowLevel Function
extern void LCD_SetWindow(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);
extern void LCD_PutPixel(uint16_t x, uint16_t y);
extern void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
extern void LCD_DrawFillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
extern void LCD_DrawMonoPict(const uint32_t *Pict);
extern void LCD_WriteBMP(uint32_t BmpAddress);


#endif /* LCDHAL_H_ */
