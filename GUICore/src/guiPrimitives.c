/*
 * lcdHAL.c
 *
 *  Created on: 03.01.2013
 *      Author: Andrey Fursov
 */


#include "gui.h"

#define MAX_POLY_CORNERS   200
#define POLY_Y(Z)          ((int32_t)((Points + Z)->X))
#define POLY_X(Z)          ((int32_t)((Points + Z)->Y))

#define ABS(X)  ((X) > 0 ? (X) : -(X))




//**************************************************************************************
void LCD_Clear(uint16_t Color)
{
	LCD_SetTextColor(Color);
	LCD_DrawFillRect(0, 0, LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT);
}


void LCD_DrawTransparentChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar)
{
	uint32_t width, bitCounter, rawIndex, colIndex;
	const uint8_t * ptrByte;
	V_FONT * LCD_Currentfonts;

	LCD_Currentfonts = LCD_GetFont();

	// Symbol width
	if (codeChar > LCD_Currentfonts->NumSymb) codeChar = 0;
	if (LCD_Currentfonts->Width)
	{
		width = LCD_Currentfonts->Width;
	}
	else
	{
		width = LCD_Currentfonts->tableSymbWidth[codeChar];
	}

//	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	// Draw Char
	ptrByte = &LCD_Currentfonts->table[LCD_Currentfonts->tableSymbIndex[codeChar]];
	for(rawIndex = 0; rawIndex < LCD_Currentfonts->Height; rawIndex++)
	{
		bitCounter = 0;
		for(colIndex = 0; colIndex < width; colIndex++)
		{

			if (bitCounter > 7)
			{
				bitCounter = 0;
				ptrByte++;
			}
			if(*ptrByte & (1<<bitCounter))
			{
				LCD_PutPixel(Xpos+colIndex, Ypos+rawIndex);
			}
			bitCounter++;
		}
		ptrByte++;
	}
}

//**************************************************************************************
// Draw string
void LCD_DrawString(char * text, uint16_t len, uint16_t Xpos, uint16_t Ypos)
{
	uint32_t i, index;
	V_FONT * LCD_Currentfonts;
	LCD_Currentfonts = LCD_GetFont();
	i = 0;
	while (i < len
			&& (uint8_t)text[i] >= LCD_Currentfonts->Offset)
	{
		index = (uint8_t)text[i] - LCD_Currentfonts->Offset;
		if (index > LCD_Currentfonts->NumSymb) index = 0x3F-32;
		LCD_DrawChar(Xpos, Ypos, index);
		if (LCD_Currentfonts->Width)
			Xpos += LCD_Currentfonts->Width;
		else
			Xpos += (LCD_Currentfonts->tableSymbWidth[index]+LCD_Currentfonts->SymbolSpace);
		i++;
	}
}

//**************************************************************************************
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction)
{
	uint16_t len = 1, height = 1;
	if (Direction == LCD_DIR_HORIZONTAL)
	{
		len = Length;
	}
	else
	{
		height = Length;
	}
	LCD_DrawFillRect(Xpos,Ypos,len, height);
}

//**************************************************************************************
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
	LCD_DrawLine(Xpos, Ypos, 				Width, 	LCD_DIR_HORIZONTAL);
	LCD_DrawLine(Xpos, (Ypos+Height-1), 	Width, LCD_DIR_HORIZONTAL);

	LCD_DrawLine(Xpos, 			Ypos, 	Height, LCD_DIR_VERTICAL);
	LCD_DrawLine((Xpos+Width-1), 	Ypos, 	Height, LCD_DIR_VERTICAL);
}

//**************************************************************************************
// from http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
//In summary, when we compare the sum of N odd numbers to this algorithm we have:
// ddF_y = -2 * radius       is connected to last member of sum of N odd numbers.
//                           This member has index equal to value of radius (integral).
//                           Since odd number is 2*n + 1 there is 1 handled elsewhere
//                           or it should be -2*radius - 1
// ddF_x = 0                 should be 1. Because difference between two consecutive odd numbers is 2.
//                           If so f += ddF_y + 1 is f+= ddF_y. Saving one operation.
// f = - radius + 1          Initial error equal to half of "bigger" step.
//                           In case of saving one addition it should be either -radius or -radius + 2.
// In any case there should be addition of 1 driven out of outer loop.
// So.
// f += ddF_y                Adding odd numbers from Nth to 1st.
// f += ddF_x                Adding odd numbers from 1st to Nth. 1 is missing because it can be moved outside of loop.
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t radius)
{
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t y = radius;

	LCD_PutPixel(Xpos, Ypos + radius);
	LCD_PutPixel(Xpos, Ypos - radius);
	LCD_PutPixel(Xpos + radius, Ypos);
	LCD_PutPixel(Xpos - radius, Ypos);

	while(x < y)
	{
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		LCD_PutPixel(Xpos + x, Ypos + y);
		LCD_PutPixel(Xpos - x, Ypos + y);
		LCD_PutPixel(Xpos + x, Ypos - y);
		LCD_PutPixel(Xpos - x, Ypos - y);
		LCD_PutPixel(Xpos + y, Ypos + x);
		LCD_PutPixel(Xpos - y, Ypos + x);
		LCD_PutPixel(Xpos + y, Ypos - x);
		LCD_PutPixel(Xpos - y, Ypos - x);
	}
}


//**************************************************************************************
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	LCD_DrawLine(Xpos, 				Ypos,	Width,	LCD_DIR_HORIZONTAL);
	LCD_DrawLine(Xpos, 	(Ypos+Height-1), 	Width,	LCD_DIR_HORIZONTAL);

	LCD_DrawLine(Xpos, 				Ypos, 	Height, LCD_DIR_VERTICAL);
	LCD_DrawLine((Xpos+Width-1), 	Ypos, 	Height, LCD_DIR_VERTICAL);

	LCD_DrawFillRect(Xpos+1,Ypos+1, Width-2, Height-2);
}

//**************************************************************************************
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t radius)
{
	uint16_t textColor, backColor;
	
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x = 0;
	int16_t y = radius;

	LCD_GetColors(&textColor, &backColor);
	LCD_SetTextColor(backColor);
	LCD_DrawLine(Xpos + x, Ypos - y, 2*y, LCD_DIR_VERTICAL);
//	LCD_DrawLine(Xpos - x, Ypos - y, 2*y, LCD_DIR_VERTICAL);
//	LCD_DrawLine(Xpos + y, Ypos - x, 2*x, LCD_DIR_VERTICAL);
//	LCD_DrawLine(Xpos - y, Ypos - x, 2*x, LCD_DIR_VERTICAL);

//	LCD_PutPixel(Xpos, Ypos + radius);
//	LCD_PutPixel(Xpos, Ypos - radius);
//	LCD_PutPixel(Xpos + radius, Ypos);
//	LCD_PutPixel(Xpos - radius, Ypos);

	while(x < y)
	{
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		LCD_DrawLine(Xpos + x, Ypos - y, 2*y, LCD_DIR_VERTICAL);
		LCD_DrawLine(Xpos - x, Ypos - y, 2*y, LCD_DIR_VERTICAL);
		LCD_DrawLine(Xpos + y, Ypos - x, 2*x, LCD_DIR_VERTICAL);
		LCD_DrawLine(Xpos - y, Ypos - x, 2*x, LCD_DIR_VERTICAL);
	}
	LCD_SetTextColor(textColor);
	LCD_DrawCircle(Xpos, Ypos, radius);
}




//**************************************************************************************
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;

	deltax = ABS(x2 - x1);				/* The difference between the x's */
	deltay = ABS(y2 - y1);				/* The difference between the y's */
	x = x1;											 /* Start x off at the first pixel */
	y = y1;											 /* Start y off at the first pixel */

	if (x2 >= x1)								 /* The x-values are increasing */
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else													/* The x-values are decreasing */
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)								 /* The y-values are increasing */
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else													/* The y-values are decreasing */
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)				 /* There is at least one x-value for every y-value */
	{
		xinc1 = 0;									/* Don't change the x when numerator >= denominator */
		yinc2 = 0;									/* Don't change the y for every iteration */
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;				 /* There are more x-values than y-values */
	}
	else													/* There is at least one y-value for every x-value */
	{
		xinc2 = 0;									/* Don't change the x for every iteration */
		yinc1 = 0;									/* Don't change the y when numerator >= denominator */
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;				 /* There are more y-values than x-values */
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		LCD_PutPixel(x, y);						 /* Draw the current pixel */
		num += numadd;							/* Increase the numerator by the top of the fraction */
		if (num >= den)						 /* Check if numerator >= denominator */
		{
			num -= den;							 /* Calculate the new numerator value */
			x += xinc1;							 /* Change the x as appropriate */
			y += yinc1;							 /* Change the y as appropriate */
		}
		x += xinc2;								 /* Change the x as appropriate */
		y += yinc2;								 /* Change the y as appropriate */
	}
}

//**************************************************************************************
void LCD_PolyLine(pPoint Points, uint16_t PointCount)
{
	int16_t X = 0, Y = 0;

	if(PointCount < 2)
	{
		return;
	}

	while(--PointCount)
	{
		X = Points->X;
		Y = Points->Y;
		Points++;
		LCD_DrawUniLine(X, Y, Points->X, Points->Y);
	}
}

//**************************************************************************************
static void LCD_PolyLineRelativeClosed(pPoint Points, uint16_t PointCount, uint16_t Closed)
{
	int16_t X = 0, Y = 0;
	pPoint First = Points;

	if(PointCount < 2)
	{
		return;
	}
	X = Points->X;
	Y = Points->Y;
	while(--PointCount)
	{
		Points++;
		LCD_DrawUniLine(X, Y, X + Points->X, Y + Points->Y);
		X = X + Points->X;
		Y = Y + Points->Y;
	}
	if(Closed)
	{
		LCD_DrawUniLine(First->X, First->Y, X, Y);
	}
}

//**************************************************************************************
void LCD_ClosedPolyLine(pPoint Points, uint16_t PointCount)
{
	LCD_PolyLine(Points, PointCount);
	LCD_DrawUniLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
}

//**************************************************************************************
void LCD_PolyLineRelative(pPoint Points, uint16_t PointCount)
{
	LCD_PolyLineRelativeClosed(Points, PointCount, 0);
}

//**************************************************************************************
void LCD_ClosedPolyLineRelative(pPoint Points, uint16_t PointCount)
{
	LCD_PolyLineRelativeClosed(Points, PointCount, 1);
}

//**************************************************************************************
void LCD_FillPolyLine(pPoint Points, uint16_t PointCount)
{
	/*	public-domain code by Darel Rex Finley, 2007 */
	uint16_t TextColor, BackColor;
	uint16_t	nodes = 0, nodeX[MAX_POLY_CORNERS], pixelX = 0, pixelY = 0, i = 0,
	j = 0, swap = 0;
	uint16_t	IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;

	IMAGE_LEFT = IMAGE_RIGHT = Points->X;
	IMAGE_TOP= IMAGE_BOTTOM = Points->Y;

	LCD_GetColors(&TextColor, &BackColor);
	for(i = 1; i < PointCount; i++)
	{
		pixelX = POLY_X(i);
		if(pixelX < IMAGE_LEFT)
		{
			IMAGE_LEFT = pixelX;
		}
		if(pixelX > IMAGE_RIGHT)
		{
			IMAGE_RIGHT = pixelX;
		}

		pixelY = POLY_Y(i);
		if(pixelY < IMAGE_TOP)
		{
			IMAGE_TOP = pixelY;
		}
		if(pixelY > IMAGE_BOTTOM)
		{
			IMAGE_BOTTOM = pixelY;
		}
	}

	LCD_SetTextColor(BackColor);

	/*	Loop through the rows of the image. */
	for (pixelY = IMAGE_TOP; pixelY < IMAGE_BOTTOM; pixelY++)
	{
		/* Build a list of nodes. */
		nodes = 0; j = PointCount-1;

		for (i = 0; i < PointCount; i++)
		{
			if (((POLY_Y(i)<(double) pixelY) && (POLY_Y(j)>=(double) pixelY)) || \
					((POLY_Y(j)<(double) pixelY) && (POLY_Y(i)>=(double) pixelY)))
			{
				nodeX[nodes++]=(int) (POLY_X(i)+((pixelY-POLY_Y(i))*(POLY_X(j)-POLY_X(i)))/(POLY_Y(j)-POLY_Y(i)));
			}
			j = i;
		}

		/* Sort the nodes, via a simple "Bubble" sort. */
		i = 0;
		while (i < nodes-1)
		{
			if (nodeX[i]>nodeX[i+1])
			{
				swap = nodeX[i];
				nodeX[i] = nodeX[i+1];
				nodeX[i+1] = swap;
				if(i)
				{
					i--;
				}
			}
			else
			{
				i++;
			}
		}

		/*	Fill the pixels between node pairs. */
		for (i = 0; i < nodes; i+=2)
		{
			if(nodeX[i] >= IMAGE_RIGHT)
			{
				break;
			}
			if(nodeX[i+1] > IMAGE_LEFT)
			{
				if (nodeX[i] < IMAGE_LEFT)
				{
					nodeX[i]=IMAGE_LEFT;
				}
				if(nodeX[i+1] > IMAGE_RIGHT)
				{
					nodeX[i+1] = IMAGE_RIGHT;
				}
				LCD_SetTextColor(BackColor);
				LCD_DrawLine(pixelY, nodeX[i+1], nodeX[i+1] - nodeX[i], LCD_DIR_HORIZONTAL);
				LCD_SetTextColor(TextColor);
				LCD_PutPixel(pixelY, nodeX[i+1]);
				LCD_PutPixel(pixelY, nodeX[i]);
				/* for (j=nodeX[i]; j<nodeX[i+1]; j++) PutPixel(j,pixelY); */
			}
		}
	}

	/* draw the edges */
	LCD_SetTextColor(TextColor);
}


//**************************************************************************************
void LCD_DrawRoundedRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t LineWidth)
{
//	uint32_t i, num;
	uint16_t cxPos, cyPos;
	cxPos = Xpos+Width-LineWidth-1;
	cyPos = Ypos+LineWidth;
	LCD_DrawQuadRound(cxPos, cyPos, LineWidth, 0);
//	cxPos = Xpos+Width-LineWidth;
	cyPos = Ypos+Height-LineWidth;
	LCD_DrawQuadRound(cxPos, cyPos, LineWidth, 1);
	cxPos = Xpos+LineWidth;
//	cyPos = Ypos+Height-LineWidth;
	LCD_DrawQuadRound(cxPos, cyPos, LineWidth, 2);
//	cxPos = Xpos+LineWidth;
	cyPos = Ypos+LineWidth;
	LCD_DrawQuadRound(cxPos, cyPos, LineWidth, 3);

	LCD_DrawFillRect(Xpos+LineWidth, 		Ypos, 						Width-LineWidth-LineWidth, LineWidth);
	LCD_DrawFillRect(Xpos+LineWidth, 		Ypos+Height-LineWidth, 		Width-LineWidth-LineWidth, LineWidth);
	LCD_DrawFillRect(Xpos, 					Ypos+LineWidth, LineWidth, 	Height-LineWidth-LineWidth);
	LCD_DrawFillRect(Xpos+Width-LineWidth,	Ypos+LineWidth, LineWidth, 	Height-LineWidth-LineWidth);


}




//**************************************************************************************
void LCD_DrawQuadRound(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t Quadrant)
{
	int32_t	D;		/* Decision Variable */
	int32_t	CurX;/* Current X Value */
	int32_t	CurY;/* Current Y Value */

	D = 3 - (Radius << 1);
	CurX = 0;
	CurY = Radius;

	while (CurX <= CurY)
	{
		if (Quadrant == 0)
		{
			if(CurY > 0)
			{
				LCD_DrawLine(Xpos + CurX, Ypos-CurY, CurY, LCD_DIR_VERTICAL);
			}

			if(CurX > 0)
			{
				LCD_DrawLine(Xpos + CurY, Ypos-CurX, CurX, LCD_DIR_VERTICAL);
			}
		}
		if (Quadrant == 1)
		{
			if(CurY > 0)
			{
				LCD_DrawLine(Xpos + CurX, Ypos, CurY, LCD_DIR_VERTICAL);
			}

			if(CurX > 0)
			{
				LCD_DrawLine(Xpos + CurY, Ypos, CurX, LCD_DIR_VERTICAL);
			}
		}
		if (Quadrant == 2)
		{
			if(CurY > 0)
			{
				LCD_DrawLine(Xpos - CurX, Ypos, CurY, LCD_DIR_VERTICAL);
			}

			if(CurX > 0)
			{
				LCD_DrawLine(Xpos - CurY, Ypos, CurX, LCD_DIR_VERTICAL);
			}
		}
		if (Quadrant == 3)
		{
			if(CurY > 0)
			{
				LCD_DrawLine(Xpos - CurX, Ypos-CurY, CurY, LCD_DIR_VERTICAL);
			}

			if(CurX > 0)
			{
				LCD_DrawLine(Xpos - CurY, Ypos - CurX, CurX, LCD_DIR_VERTICAL);
			}
		}

		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}
