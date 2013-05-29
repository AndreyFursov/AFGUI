#ifndef HX8347_H
#define HX8347_H




typedef struct
{
  __IO uint16_t LCD_REG;
  __IO uint16_t LCD_RAM;
} GL_LCD_TypeDef;

#define LCD_BASE			((uint32_t)(0x60000000 | 0x0001fffe))

#define GL_LCD				((GL_LCD_TypeDef *) GL_LCD_BASE)
#define RCC_AHBPeriph_FSMC	((uint32_t)0x00000100)




#endif
