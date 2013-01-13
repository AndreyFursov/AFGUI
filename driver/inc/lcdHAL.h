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
