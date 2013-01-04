/*
 * driverTemplate.c
 *
 *  Created on: 03.01.2013
 *      Author: Andrey
 */

#include "gui.h"


//***********************************************************************************
// P R O T O T I P E S
//***********************************************************************************
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);
void LCD_SetWindows (uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);



