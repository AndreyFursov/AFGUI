/*
 * lcdHAL.h
 *
 *  Created on: 18.12.2012
 *      Author: Andrey
 */

#ifndef GUIPRIMITIVES_H_
#define GUIPRIMITIVES_H_

#include "gui.h"


// GPIO config
// LCD reset


//*********************************************************************************
// global extern

typedef struct
{
	int16_t X;
	int16_t Y;
} Point, * pPoint;



#define ASSEMBLE_RGB(R ,G, B)    ((((R)& 0xFC) << 8) | (((G) & 0xFC) << 2) | (((B) & 0xF0) >> 4))
#define MAX_POLY_CORNERS   200


typedef struct
{
	unsigned clRed		: 6;
	unsigned clGreen	: 6;
	unsigned clBlue		: 4;
} RGB16;

typedef struct
{
	unsigned clRed		: 6;
	unsigned clGreen	: 6;
	unsigned clBlue		: 6;
} RGB32;


//*****************************************************************************
// PROTOTIPES



// high level primitives


//
//extern void LCD_ClearLine(uint16_t Line);

//extern void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
extern void LCD_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width);
extern void LCD_WindowModeDisable(void);
extern void LCD_ASCII(V_FONT * vFont);

//**************************************************************************
extern void LCD_DrawTransparentChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
extern void LCD_Clear(uint16_t Color);
extern void LCD_DrawString(char * text, uint16_t len, uint16_t Xpos, uint16_t Ypos);
extern void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction);
extern void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width);
extern void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
extern void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
extern void LCD_DrawQuadRound(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t Quadrant);
extern void LCD_DrawRoundedRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t LineWidth);
extern void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
extern void LCD_PolyLine(pPoint Points, uint16_t PointCount);
extern void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount);
extern void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount);
extern void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount);
extern void LCD_FillPolyLine(pPoint Points, uint16_t PointCount);

//**************************************************************************





#endif /* LCDHAL_H_ */
