/*
 * lcdHAL_HX8347A.h
 *
 *  Created on: 10.04.2013
 *      Author: Andrey Fursov
 */

#ifndef LCDHAL_HX8347A_H_
#define LCDHAL_HX8347A_H_

//******************************************************************************************
// Init
extern void LCD_Init_HX8347A(void);

//******************************************************************************************
// Color function
extern uint16_t * getPaletteAdr0_HX8347A(void);
extern uint16_t * getPaletteAdr1_HX8347A(void);


//******************************************************************************************
// LowLevel Function
extern void LCD_SetWindow_HX8347A(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);
extern void LCD_PutPixel_HX8347A(uint16_t x, uint16_t y);
extern void LCD_DrawChar_HX8347A(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
extern void LCD_DrawFillRect_HX8347A(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
extern void LCD_DrawMonoPict_HX8347A(const uint32_t *Pict);
extern void LCD_WriteBMP_HX8347A(uint32_t BmpAddress);


#endif /* LCDHAL_HX8347A_H_ */
