/*
 * mkDriver.h
 *
 *  Created on: 08.01.2013
 *      Author: Andrey Fursov
 */

#ifndef MKDRIVER_H_
#define MKDRIVER_H_

// hardware init
extern void  guiDelay_ms(uint32_t _time);

extern void LCD_CtrlLinesConfig(void);
extern void LCD_FSMCConfig(void);
extern void LCD_Reset_Off(void);
extern void LCD_Reset_On(void);


void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);
void LCD_SetWindows (uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);


#endif /* MKDRIVER_H_ */
