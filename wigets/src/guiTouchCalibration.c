/*
 * guiTouchCalibration.c
 *
 *  Created on: 23.04.2013
 *      Author: Andrey Fursov
 */
#include "gui.h"
#include "ee_emul.h"

int16_t x, y; 

// variables
uint16_t tcState = 0;

const int16_t xCenter[] = {35, LCD_PIXEL_WIDTH-35, 35, LCD_PIXEL_WIDTH-35}; 
const int16_t yCenter[] = {35, 35, LCD_PIXEL_HEIGHT-35, LCD_PIXEL_HEIGHT-35}; 
int16_t xPos[5], yPos[5], axc[2], ayc[2], bxc[2], byc[2];



// prototypes






// functions

uint16_t touchCalibration(void)
{
	
	static uint16_t flag, counter = 0;
	
	counter++;
	if (counter > 6000)
	{
		touchSetCoef(11, -17, -15, 256);
		tcState = 9;
	}
		
	switch (tcState)
	{
		case 0:	// left top corner draw
			LCD_Clear(LCD_COLOR_WHITE);
			LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
			LCD_SetFont(&GL_ArialNarrow_15);
			LCD_DrawString("Калибровка сенсорного экрана", 50, 50, 112);
			LCD_DrawLine(10, 10+25, 50, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(10+25, 10, 50, LCD_DIR_VERTICAL);
			flag = 0;
			if (getTouchState() == 0)
				tcState++;
			break;

		case 1:
			x = touchGetX();
			y = touchGetY();
			if (x < 4090 && y < 4090)
			{
				xPos[0] = x;
				yPos[0] = y;
				flag = 1;
			}
			else
			{
				if (flag) tcState++;
			}
			break;

		case 2:	// right top corner draw
			LCD_Clear(LCD_COLOR_WHITE);
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&GL_ArialNarrow_15);
			LCD_DrawString("Калибровка сенсорного экрана", 50, 50, 112);
			LCD_DrawLine(LCD_PIXEL_WIDTH-10-50, 10+25, 50, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(LCD_PIXEL_WIDTH-10-25, 10, 50, LCD_DIR_VERTICAL);
			flag = 0;
			if (getTouchState() == 0)
				tcState++;
			break;

		case 3:
			x = touchGetX();
			y = touchGetY();
			if (x < 4090 && y < 4090)
			{
				xPos[1] = x;
				yPos[1] = y;
				flag = 1;
			}
			else
			{
				if (flag) tcState++;
			}
			break;

		case 4:	// left down corner draw
			LCD_Clear(LCD_COLOR_WHITE);
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&GL_ArialNarrow_15);
			LCD_DrawString("Калибровка сенсорного экрана", 50, 50, 112);
			LCD_DrawLine(10, LCD_PIXEL_HEIGHT-10-25, 50, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(10+25, LCD_PIXEL_HEIGHT-10-50, 50, LCD_DIR_VERTICAL);
			flag = 0;
			if (getTouchState() == 0)
				tcState++;
			break;

		case 5:
			x = touchGetX();
			y = touchGetY();
			if (x < 4090 && y < 4090)
			{
				xPos[2] = x;
				yPos[2] = y;
				flag = 1;
			}
			else
			{
				if (flag) tcState++;
			}
			break;

		case 6:	// right down corner draw
			LCD_Clear(LCD_COLOR_WHITE);
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&GL_ArialNarrow_15);
			LCD_DrawString("Калибровка сенсорного экрана", 50, 50, 112);
			LCD_DrawLine(LCD_PIXEL_WIDTH-10-50, LCD_PIXEL_HEIGHT-10-25, 50, LCD_DIR_HORIZONTAL);
			LCD_DrawLine(LCD_PIXEL_WIDTH-10-25, LCD_PIXEL_HEIGHT-10-50, 50, LCD_DIR_VERTICAL);
			flag = 0;
			if (getTouchState() == 0)
				tcState++;
			break;

		case 7:
			x = touchGetX();
			y = touchGetY();
			if (x < 4090 && y < 4090)
			{
				xPos[3] = x;
				yPos[3] = y;
				flag = 1;
			}
			else
			{
				if (flag) tcState++;
			}
			break;
		case 8:	// calculate coef
			axc[0] = (xPos[3] - xPos[0])/(xCenter[3] - xCenter[0]);
			bxc[0] = xCenter[0] - xPos[0]/axc[0];
			ayc[0] = (yPos[3] - yPos[0])/(yCenter[3] - yCenter[0]);
			byc[0] = yCenter[0] - yPos[0]/ayc[0];
		
			axc[1] = (xPos[2] - xPos[1])/(xCenter[2] - xCenter[1]);
			bxc[1] = xCenter[1] - xPos[1]/axc[1];
			ayc[1] = (yPos[2] - yPos[1])/(yCenter[2] - yCenter[1]);
			byc[1] = yCenter[1] - yPos[1]/ayc[1];
			
			touchSetCoef(axc[0], bxc[0], ayc[0], byc[0]);
			touchSaveCoef(axc[0], bxc[0], ayc[0], byc[0]);

			tcState++;
			break;
		case 9:
			break;
		default:
			break;


	}

	return tcState;

}

void touchSaveCoef(int16_t _ax, int16_t _bx, int16_t _ay, int16_t _by)
{
	uint16_t i = 0;
	uint16_t buf[4];
	
	buf[i++] = (uint16_t)_ax;
	buf[i++] = (uint16_t)_bx;
	buf[i++] = (uint16_t)_ay;
	buf[i++] = (uint16_t)_by;
	
	EE_WriteBuf(EE_ADR_COEF, buf, 4);
	touchSetCoef(_ax, _bx, _ay, _by);
	
}

void touchLoadCoef(void)
{
	int16_t coef[4];
	
	EE_ReadBuf(EE_ADR_COEF, (uint16_t *)coef, 4);
	touchSetCoef(coef[0], coef[1], coef[2], coef[3]);
}

