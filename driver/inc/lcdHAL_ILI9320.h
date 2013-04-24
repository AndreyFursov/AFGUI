/*
 * lcdHAL_ILI9320.h
 *
 *  Created on: 10.04.2013
 *      Author: Andrey Fursov
 */

#ifndef LCDHAL_ILI9320_H_
#define LCDHAL_ILI9320_H_

//******************************************************************************************
// Init
extern void LCD_Init_ILI9320(void);


//******************************************************************************************
// LowLevel Function

extern void LCD_SetWindow_ILI9320(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);
extern void LCD_PutPixel_ILI9320(uint16_t x, uint16_t y);
extern void LCD_DrawChar_ILI9320(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
extern void LCD_DrawFillRect_ILI9320(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
extern void LCD_DrawMonoPict_ILI9320(const uint32_t *Pict);
extern void LCD_WriteBMP_ILI9320(uint32_t BmpAddress);


#endif /* LCDHAL_ILI9320_H_ */
