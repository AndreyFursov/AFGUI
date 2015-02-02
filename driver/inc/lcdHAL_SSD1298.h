/*
 * lcdHAL_SSD1298.h
 *
 *  Created on: 10.04.2013
 *      Author: Andrey Fursov
 */

#ifndef LCDHAL_SSD1298_H_
#define LCDHAL_SSD1298_H_

//******************************************************************************************
// Init
extern void LCD_Init_SSD1298(void);

//******************************************************************************************
// Color function
extern uint16_t * getPaletteAdr0_SSD1298(void);
extern uint16_t * getPaletteAdr1_SSD1298(void);


//******************************************************************************************
// LowLevel Function
extern void LCD_SetWindow_SSD1298(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);
extern void LCD_PutPixel_SSD1298(uint16_t x, uint16_t y);
extern void LCD_DrawChar_SSD1298(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
extern void LCD_DrawFillRect_SSD1298(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
extern void LCD_DrawMonoPict_SSD1298(const uint32_t *Pict);
extern void LCD_WriteBMP_SSD1298(uint32_t BmpAddress);


#endif /* LCDHAL_SSD1298_H_ */
