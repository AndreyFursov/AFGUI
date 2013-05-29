//#include 


typedef struct
{
  __IO uint16_t LCD_REG;
  __IO uint16_t LCD_RAM;
} GL_LCD_TypeDef;



//*****************************************************************************
// 
//*****************************************************************************
void hx8347_Init(void)
{
	volatile uint32_t lcdid = 0;
	volatile uint16_t clrColor, red, green, blue, regValue;
	
	regValue = 0xE8;
	LCD_CtrlLinesConfig();
	LCD_FSMCConfig();
	
    Set_Rst();
    delay_ms(10);
    Clr_Rst();
    delay_ms(10);
    Set_Rst();
    delay_ms(250);
	
}