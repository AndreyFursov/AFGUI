//*********************************************
// Fursov Andrey
// mc: STM32F205VET
// tft: DEM240320H (display electronic gmbh)
// tft controller: hx8347a
//
//
//
//*********************************************
#include "stm32f2xx_conf.h"
#include "gui.h"
//#include "guiFonts.h"


//***********************************************************************************
// P R O T O T I P E S
//***********************************************************************************
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(uint16_t RGB_Code);
uint16_t LCD_ReadRAM(void);
void LCD_SetWindows (uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy);


typedef struct
{
  volatile uint16_t LCD_REG;
  volatile uint16_t LCD_RAM;
} LCD_TypeDef;



//********************************************************
// Macro
//********************************************************
// LCD reset
#define LCD_Reset_Off() GPIO_SetBits( GPIOC, GPIO_Pin_3)
#define LCD_Reset_On() GPIO_ResetBits( GPIOC, GPIO_Pin_3)

#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0001fffe))
#define LCD                ((LCD_TypeDef *)LCD_BASE)

#ifdef TNKERNEL_PORT_CORTEXM3
#include "tn.h"
#define delay_ms	tn_task_sleep
#else
#define delay_ms	Delay_ms
#endif

//********************************************************
// Variables
//********************************************************
V_FONT * LCD_Currentfonts;
volatile uint16_t TextColor;
volatile uint16_t BackColor;






//********************************************************
// Prototypes
//********************************************************
void  Delay_ms(uint32_t _time);

//********************************************************
// Functions
//********************************************************

//******************************************************************************
// Color function
void LCD_SetColors(volatile uint16_t _TextColor, volatile uint16_t _BackColor)
{
  TextColor = _TextColor;
  BackColor = _BackColor;
}

void LCD_GetColors(volatile uint16_t *_TextColor, volatile uint16_t *_BackColor)
{
  *_TextColor = TextColor; *_BackColor = BackColor;
}

void LCD_SetTextColor(volatile uint16_t Color)
{
  TextColor = Color;
}

void LCD_SetBackColor(volatile uint16_t Color)
{
  BackColor = Color;
}

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



//********************************************************
// delay
void  Delay_ms(uint32_t _time)
{
	if (_time >= (0xFFFFFFFF/37500)) _time = 0xFFFFFFFF;
	_time *= 37500;
	while (_time--);
}



//******************************************************************************
// Low level function
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  /* Read 16-bit Reg */
  return (LCD->LCD_RAM);
}

void LCD_WriteRAM_Prepare(void)
{
  LCD->LCD_REG = 0x0022;
}

void LCD_WriteRAM(uint16_t RGB_Code)
{
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
}

uint16_t LCD_ReadRAM(void)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = 0x0022; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  return LCD->LCD_RAM;
}

void LCD_SetWindows (uint16_t startx, uint16_t starty, uint16_t endx, uint16_t endy)
{
	if (startx > LCD_PIXEL_WIDTH-1 || endx > LCD_PIXEL_WIDTH-1
		|| starty > LCD_PIXEL_HEIGHT-1 || endy > LCD_PIXEL_HEIGHT-1 )
	{
		startx = 0;
		endx = 0;
		starty = 0;
		endy = 0;
	}
	LCD_WriteReg(0x0002,startx>>8);
	LCD_WriteReg(0x0003,startx);
	LCD_WriteReg(0x0004,endx>>8);
	LCD_WriteReg(0x0005,endx);
	LCD_WriteReg(0x0006,starty>>8);
	LCD_WriteReg(0x0007,starty);
	LCD_WriteReg(0x0008,endy>>8);
	LCD_WriteReg(0x0009,endy);
}


//********************************************************
//********************************************************
//********************************************************

void LCD_PutPixel(uint16_t x, uint16_t y)
{
	LCD_SetWindows (x,y, x, y);
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(TextColor);
	LCD_WriteRAM(0);
}



void LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, uint16_t codeChar)
{
	uint32_t index = 0, i = 0, numByte, width, bitCounter, ptrByte;
	// Symbol width
	if (LCD_Currentfonts->Width)
	{
		width = LCD_Currentfonts->Width;
		LCD_SetWindows(Xpos, Ypos, Xpos+width, Ypos+LCD_Currentfonts->Height-1);
	}
	else
	{
		width = LCD_Currentfonts->tableSymbWidth[codeChar];
		LCD_SetWindows(Xpos, Ypos, Xpos+width+LCD_Currentfonts->SymbolSpace-1, Ypos+LCD_Currentfonts->Height-1);
	}
	numByte = LCD_Currentfonts->Height * ((width+7)/8);

	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	// Draw Char
	for(index = 0; index < numByte; index++)
	{
		bitCounter = 0;
		for(i = 0; i < width; i++)
		{

			if (bitCounter > 7)
			{
				bitCounter = 0;
				index++;
			}
			ptrByte = LCD_Currentfonts->table[LCD_Currentfonts->tableSymbIndex[codeChar]+index];
			if(ptrByte & (1<<bitCounter))
			{
				LCD_WriteRAM(TextColor);
				LCD_WriteRAM(0);
			}
			else
			{
				LCD_WriteRAM(BackColor);
				LCD_WriteRAM(0);
			}
			bitCounter++;
		}
		// Add space
		for (i = 0; i < LCD_Currentfonts->SymbolSpace; i++)
		{
			LCD_WriteRAM(BackColor);
			LCD_WriteRAM(0);
		}
	}
}

void LCD_DrawFillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint32_t i, num;

	LCD_SetWindows (Xpos,Ypos,Xpos+Width-1,Ypos+Height-1);
	LCD_WriteRAM_Prepare();

	num = Width*Height;
	for(i = 0; i < num; i++)
	{
		LCD_WriteRAM(TextColor);
		LCD_WriteRAM(0);
	}
}


void LCD_DrawMonoPict(const uint32_t *Pict)
{
	uint32_t index = 0, i = 0;
	//LCD_SetCursor(0, 0);

	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for(index = 0; index < 2400; index++)
	{
		for(i = 0; i < 32; i++)
		{
			if((Pict[index] & (1 << i)) == 0x00)
			{
				LCD_WriteRAM(BackColor);
				LCD_WriteRAM(0);
			}
			else
			{
				LCD_WriteRAM(TextColor);
				LCD_WriteRAM(0);
			}
		}
	}
}

void LCD_WriteBMP(uint32_t BmpAddress)
{
	uint32_t index = 0, size = 0;
	/* Read bitmap size */
	size = *(volatile uint16_t *) (BmpAddress + 2);
	size |= (*(volatile uint16_t *) (BmpAddress + 4)) << 16;
	/* Get bitmap data address offset */
	index = *(volatile uint16_t *) (BmpAddress + 10);
	index |= (*(volatile uint16_t *) (BmpAddress + 12)) << 16;
	size = (size - index)/2;
	BmpAddress += index;
	/* Set GRAM write direction and BGR = 1 */
	/* I/D=00 (Horizontal : decrement, Vertical : decrement) */
	/* AM=1 (address is updated in vertical writing direction) */
	//LCD_WriteReg(LCD_REG_3, 0x1008);

	LCD_WriteRAM_Prepare();

	for(index = 0; index < size; index++)
	{
		LCD_WriteRAM(*(volatile uint16_t *)BmpAddress);
		LCD_WriteRAM(0);
		BmpAddress += 2;
	}

	/* Set GRAM write direction and BGR = 1 */
	/* I/D = 01 (Horizontal : increment, Vertical : decrement) */
	/* AM = 1 (address is updated in vertical writing direction) */
	//LCD_WriteReg(LCD_REG_3, 0x1018);
}













//********************************************************


//********************************************************
// LCD DEM240320H_TMH-PW-N (A-TOUCH) HX8347A initialization
//********************************************************

//********************************************************

void LCD_Init(void)
{
	volatile uint32_t lcdid = 0;
	
//	uint32_t i;
	uint16_t regValue;
	regValue = 0xA8;
	LCD_CtrlLinesConfig();
	LCD_FSMCConfig();
	
    LCD_Reset_Off();
    delay_ms(10);
    LCD_Reset_On();
    delay_ms(10);
    LCD_Reset_Off();
    delay_ms(250);

	// Gamms set
	LCD_WriteReg(0x0046,0x0095);
	LCD_WriteReg(0x0047,0x0051);
	LCD_WriteReg(0x0048,0x0000);
	LCD_WriteReg(0x0049,0x0036);
	LCD_WriteReg(0x004A,0x0011);
	LCD_WriteReg(0x004B,0x0066);
	LCD_WriteReg(0x004C,0x0014);
	LCD_WriteReg(0x004D,0x0077);
	LCD_WriteReg(0x004E,0x0013);
	LCD_WriteReg(0x004F,0x004C);
	LCD_WriteReg(0x0050,0x0046);
	LCD_WriteReg(0x0051,0x0046);
	
	// 240x320 Window setting
	LCD_WriteReg(0x0002,0x0000);
	LCD_WriteReg(0x0003,0x0000);
	LCD_WriteReg(0x0004,0x0000);
	LCD_WriteReg(0x0005,0x00EF);
	LCD_WriteReg(0x0006,0x0000);
	LCD_WriteReg(0x0007,0x0000);
	LCD_WriteReg(0x0008,0x0001);
	LCD_WriteReg(0x0009,0x003F);
	LCD_WriteReg(0x0090,0x007F);
	
	// Display setting
	LCD_WriteReg(0x0001,0x0006);
	LCD_WriteReg(0x0016,regValue);
	LCD_WriteReg(0x0023,0x0095);
	LCD_WriteReg(0x0024,0x0095);
	LCD_WriteReg(0x0025,0x00FF);
	LCD_WriteReg(0x0027,0x0006);
	LCD_WriteReg(0x0028,0x0006);
	LCD_WriteReg(0x0029,0x0006);
	LCD_WriteReg(0x002A,0x0006);
	LCD_WriteReg(0x002C,0x0006);
	LCD_WriteReg(0x002D,0x0006);
	LCD_WriteReg(0x003A,0x0001);
	LCD_WriteReg(0x003B,0x0001);
	LCD_WriteReg(0x003C,0x00F0);
	LCD_WriteReg(0x003D,0x0000);
	delay_ms(100);
	LCD_WriteReg(0x0010,0x00A6);
	
	// Power Supply Setting
	LCD_WriteReg(0x0019,0x0049);
	delay_ms(100);
	LCD_WriteReg(0x0093,0x000C);
	delay_ms(200);
	LCD_WriteReg(0x0020,0x0040);
	LCD_WriteReg(0x001D,0x0007);
	LCD_WriteReg(0x001E,0x0000);
	LCD_WriteReg(0x001F,0x0004);
	LCD_WriteReg(0x0044,0x004D);
	LCD_WriteReg(0x0045,0x0011);
	delay_ms(200);
	LCD_WriteReg(0x001C,0x0004);
	delay_ms(200);
	LCD_WriteReg(0x0043,0x0080);
	delay_ms(100);
	LCD_WriteReg(0x001B,0x0018);
	delay_ms(200);
	LCD_WriteReg(0x001B,0x0010);
	delay_ms(200);
	
	// Display On setting
	LCD_WriteReg(0x0026,0x0004);
	delay_ms(200);
	LCD_WriteReg(0x0026,0x0024);
	delay_ms(40);
	LCD_WriteReg(0x0026,0x002C);
	delay_ms(200);
	LCD_WriteReg(0x0026,0x003C);
	LCD_WriteReg(0x0035,0x0038);
	LCD_WriteReg(0x0036,0x0078);
	LCD_WriteReg(0x003E,0x0038);
	LCD_WriteReg(0x0040,0x000F);
	LCD_WriteReg(0x0041,0x00F0);
	
	// Set Spulse Rpulse
	LCD_WriteReg(0x0057,0x0002);
	LCD_WriteReg(0x0056,0x0084);
	LCD_WriteReg(0x0057,0x0000);

	LCD_Clear(LCD_COLOR_GREYL);
	LCD_SetFont(&LCD_DEFAULT_FONT);
}








//******************************************************************************
// GPIO Configuration for LCD
void LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Enable GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE 
												 , ENABLE);

	// GPIO Configuration ------------------------------------------------------
	// SRAM Data lines,	NOE and NWE configuration
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
									GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
									GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
									GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
									GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);

	// reset configuration 
	LCD_Reset_On();
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOC, &GPIO_InitStructure);
}



//******************************************************************************
// FSMC Configuration for LCD on A16
void LCD_FSMCConfig(void)
{
	FSMC_NORSRAMInitTypeDef	FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef	p;
	 
	// Enable FSMC clock
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
	
	// FSMC_Bank1_NORSRAM1 configuration 
	p.FSMC_AddressSetupTime = 3;//-
	p.FSMC_AddressHoldTime = 0;//
	p.FSMC_DataSetupTime = 9;
	p.FSMC_BusTurnAroundDuration = 0;
	p.FSMC_CLKDivision = 1;
	p.FSMC_DataLatency = 0;//-
	p.FSMC_AccessMode = FSMC_AccessMode_A;
	
	// 	 Color LCD configuration ------------------------------------
	// 		 LCD configured as follow:
	// 				- Data/Address MUX = Disable
	// 				- Memory Type = SRAM
	// 				- Data Width = 16bit
	// 				- Write Operation = Enable
	// 				- Extended Mode = Enable
	// 				- Asynchronous Wait = Disable 
	FSMC_NORSRAMInitStructure.FSMC_Bank 				= FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux 		= FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType			= FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth 		= FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode 		= FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait 	= FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity 	= FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode 			= FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive 	= FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation 		= FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal 			= FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode 		= FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst 			= FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct 	= &p;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);	 

	// Enable FSMC NOR/SRAM Bank1 
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}











