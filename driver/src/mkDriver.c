/*
 * mkDriver.c
 *
 *  Created on: 08.01.2013
 *      Author: Andrey Fursov
 */

#include "stm32f2xx_conf.h"
#include "gui.h"

typedef struct
{
  volatile uint16_t LCD_REG;
  volatile uint16_t LCD_RAM;
} LCD_TypeDef;



//********************************************************
// Macro
//********************************************************
// LCD reset



// for ~RS on address line a19
#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0001fffe))
// for ~RS on address line a0
//#define LCD_BASE           ((uint32_t)(0x60000000 | 0x00000000))

#define LCD                ((LCD_TypeDef *)LCD_BASE)

// #ifdef TNKERNEL_PORT_CORTEXM3
// #include "tn.h"
// #define delayms	tn_task_sleep
// #else
// #define delayms	Delay_ms
// #endif
void  Delay_ms(uint32_t _time);
#define delayms	Delay_ms

//********************************************************
// Prototypes
//********************************************************

void LCD_Reset_Off(void)
{
	GPIO_SetBits( GPIOC, GPIO_Pin_3);
}

void LCD_Reset_On(void)
{
	GPIO_ResetBits( GPIOC, GPIO_Pin_3);
}

//#define LCD_Reset_Off() GPIO_SetBits( GPIOC, GPIO_Pin_3)
//#define LCD_Reset_On() GPIO_ResetBits( GPIOC, GPIO_Pin_3)


void  guiDelay_ms(uint32_t _time)
{
	delayms(_time);

}
//******************************************************************************
// Low level function

//********************************************************
// delay
void  Delay_ms(uint32_t _time)
{
	if (_time >= (0xFFFFFFFF/37500)) _time = 0xFFFFFFFF;
	_time *= 37500;
	while (_time--);
}



void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
	volatile uint16_t i = 5;
  /* Write 16-bit Index (then Read Reg) */
	LCD->LCD_REG = LCD_Reg;
	while(i--);
	/* Read 16-bit Reg */
	return (LCD->LCD_RAM);
}

void LCD_WriteRAM_Prepare(void)
{
  LCD->LCD_REG = 0x0022;;
}

void LCD_WriteRAM(uint16_t RGB_Code)
{
  /* Write 16-bit GRAM Reg */
  LCD->LCD_RAM = RGB_Code;
}

/**
@function LCD_ReadRAM
@return ¬озвращает содержимое пам€ти в регистре 0x22
*/
uint16_t LCD_ReadRAM(void)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = 0x0022; /* Select GRAM Reg */
  /* Read 16-bit Reg */
  return LCD->LCD_RAM;
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
//	p.FSMC_AddressSetupTime = 3;//-
//	p.FSMC_AddressHoldTime = 0;//
//	p.FSMC_DataSetupTime = 9;
//	p.FSMC_BusTurnAroundDuration = 0;
//	p.FSMC_CLKDivision = 1;
//	p.FSMC_DataLatency = 0;//-
//	p.FSMC_AccessMode = FSMC_AccessMode_A;
	p.FSMC_AddressSetupTime = 3;		// 0-15
	p.FSMC_AddressHoldTime = 0;			// 1-15 na
	p.FSMC_DataSetupTime = 9;			// 1-256
	p.FSMC_BusTurnAroundDuration = 0;	// 0-15
	p.FSMC_CLKDivision = 1;				// 1-16
	p.FSMC_DataLatency = 0;				// 2-17 na
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

