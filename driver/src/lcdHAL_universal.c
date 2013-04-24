/*
 * lcdHAL_universal.c
 *
 *  Created on: 10.04.2013
 *      Author: Andrey Fursov
 */



#include "gui.h"
#include "lcdHAL_ILI9320.h"
#include "lcdHAL_HX8347A.h"

//********************************************************
// Prototypes
//********************************************************
void (*fpLCD_SetWindow)(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);
void (*fpLCD_PutPixel)(uint16_t x, uint16_t y);
void (*fpLCD_DrawChar)(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar);
void (*fpLCD_DrawFillRect)(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void (*fpLCD_DrawMonoPict)(const uint32_t *Pict);
void (*fpLCD_WriteBMP)(uint32_t BmpAddress);

V_FONT * LCD_Currentfonts;

//********************************************************
// Functions
//********************************************************





//******************************************************************************
// Font functions
void LCD_SetFont(V_FONT *fonts)
{
  LCD_Currentfonts = fonts;
}

V_FONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}


//******************************************************************************
// Font functions
uint16_t readTypeLCD(void)
{
	uint16_t lcdid = 0;


    lcdid = LCD_ReadReg(0x0000);
	
    if (lcdid == 0)
    {
    	lcdid = LCD_ReadReg(0x0067);
    }

    return lcdid;
}

//******************************************************************************
// Universal Init
void LCD_Init(void)
{
	uint16_t lcdid = 0;
	// pointers = 0;
	fpLCD_SetWindow		= 0;
	fpLCD_PutPixel 		= 0;
	fpLCD_DrawChar 		= 0;
	fpLCD_DrawFillRect 	= 0;
	fpLCD_DrawMonoPict 	= 0;
	fpLCD_WriteBMP 		= 0;

	// color config
	LCD_SetColorMode(colorIndex);


	// config gpio and fsmc
	LCD_CtrlLinesConfig();
	LCD_FSMCConfig();

	// displey reset
    LCD_Reset_Off();
    guiDelay_ms(10);
    LCD_Reset_On();
    guiDelay_ms(10);
    LCD_Reset_Off();
    guiDelay_ms(250);

    // read display type
    lcdid = readTypeLCD();

    if (lcdid == 0x9320)	// ILI9320
    {
    	fpLCD_SetWindow		= &LCD_SetWindow_ILI9320;
    	fpLCD_PutPixel 		= &LCD_PutPixel_ILI9320;
    	fpLCD_DrawChar 		= &LCD_DrawChar_ILI9320;
    	fpLCD_DrawFillRect 	= &LCD_DrawFillRect_ILI9320;
    	fpLCD_DrawMonoPict 	= &LCD_DrawMonoPict_ILI9320;
    	fpLCD_WriteBMP 		= &LCD_WriteBMP_ILI9320;
    	LCD_SetColorGRAM(lcdColorRGB_565);
    	LCD_Init_ILI9320();
    }

    if (lcdid == 0x9325)	// ILI9325
    {


    }

    if (lcdid == 0x1289)	// SSD1289
    {


    }

    if (lcdid == 0x0047)	// HX8347-A
    {
    	fpLCD_SetWindow		= &LCD_SetWindow_HX8347A;
    	fpLCD_PutPixel 		= &LCD_PutPixel_HX8347A;
    	fpLCD_DrawChar 		= &LCD_DrawChar_HX8347A;
    	fpLCD_DrawFillRect 	= &LCD_DrawFillRect_HX8347A;
    	fpLCD_DrawMonoPict 	= &LCD_DrawMonoPict_HX8347A;
    	fpLCD_WriteBMP 		= &LCD_WriteBMP_HX8347A;
    	LCD_SetColorGRAM(lcdColorRGB_666);
    	LCD_Init_HX8347A();
    }

    // displwy clear
	LCD_Clear(LCD_COLOR_GREYL);
	LCD_SetFont(&LCD_DEFAULT_FONT);
}

// вызов функций по указателям
void LCD_SetWindow(uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy)
{
	if (fpLCD_SetWindow != 0)
	{
		(*fpLCD_SetWindow)(startx, starty, endx, endy);
	}
}

void LCD_PutPixel(uint16_t x, uint16_t y)
{
	if (fpLCD_PutPixel != 0)
	{
		(*fpLCD_PutPixel)(x, y);
	}
}

void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar)
{
	if (fpLCD_DrawChar != 0)
	{
		(*fpLCD_DrawChar)(Xpos, Ypos, codeChar);
	}
}

void LCD_DrawFillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	if (fpLCD_DrawFillRect != 0)
	{
		(*fpLCD_DrawFillRect)(Xpos, Ypos, Width, Height);
	}
}

void LCD_DrawMonoPict(const uint32_t *Pict){
	if (fpLCD_DrawMonoPict != 0)
	{
		(*fpLCD_DrawMonoPict)(Pict);
	}
}

void LCD_WriteBMP(uint32_t BmpAddress)
{
	if (fpLCD_WriteBMP != 0)
	{
		(*fpLCD_WriteBMP)(BmpAddress);
	}
}















//********************************************************
//********************************************************
//********************************************************

