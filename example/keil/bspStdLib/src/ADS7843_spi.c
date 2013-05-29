
#include "globals.h"
#include "ADS7843_spi.h"




void TP_SPI_Config(void)
{
	//NVIC_InitTypeDef nvic_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	#ifdef STM32F1xx_HD
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOB |  RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG, GPIO_Pin_11 | GPIO_Pin_15);

   // Isakov
 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;			// кнопка на PC13
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);

 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;			// beep
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	/* Enable the RTC Interrupt */
	nvic_InitStruct.NVIC_IRQChannel = RTC_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 0;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_InitStruct);

   //Isakov

	/* Configure SPI pins: SCK and MOSI with default alternate function (not remapped) push-pull */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_SD_SCK | GPIO_Pin_SD_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIO_SD, &GPIO_InitStructure);

	/* Configure MISO as Input with internal pull-up */
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_SD_MISO;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIO_SD, &GPIO_InitStructure);	 

	/* Configure SD_CS pin */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SD_CS; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_Init(GPIO_SD_CS, &GPIO_InitStructure);

	/* SPI1 configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_CalculateCRC(SPI2, DISABLE);
	SPI_Cmd(SPI2, ENABLE);
	SPI_SSOutputCmd(SPI2, DISABLE);

	SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);
	#endif
	
	//stm32f2
	#ifdef STM32F2XX
	// GPIO Config
	RCC_AHB1PeriphClockCmd  (	RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD,  
  								ENABLE) ;
	RCC_APB1PeriphClockCmd  (	RCC_APB1Periph_SPI2,  
  								ENABLE) ;
								
	GPIO_PinAFConfig(PORT_TP_SPI, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(PORT_TP_SPI, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(PORT_TP_SPI, GPIO_PinSource15, GPIO_AF_SPI2);

	TP_Deselect();
	
	// spi out
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_TP_SCK | GPIO_Pin_TP_MOSI | GPIO_Pin_TP_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(PORT_TP_SPI, &GPIO_InitStructure);
	// spi cs
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_TP_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(PORT_TP_SPI, &GPIO_InitStructure);

	
	// TP interrupt
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	// SPI1 configuration 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_CalculateCRC(SPI2, DISABLE);
	SPI_Cmd(SPI2, ENABLE);
	SPI_SSOutputCmd(SPI2, DISABLE);

	SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);
	
								
								
								
	#endif
	TP_Deselect();

}

unsigned int TP_SPI_RW( unsigned int c )
{
	uint32_t i=0x0f;
	unsigned int MSB, LSB, data;
	TP_Select();
	while(--i);
	/* Send byte through the SPI1 peripheral */
// 	SPI_I2S_SendData(SPI2, c);
// 	/* Wait to receive a byte */
// 	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
// 	MSB=SPI_I2S_ReceiveData(SPI2);
// //	i=0xff;
// //	while(--i);
// 	SPI_I2S_SendData(SPI2, 0);
// 	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
// 	/* Return the byte read from the SPI bus */
// 	LSB=SPI_I2S_ReceiveData(SPI2);
// 	data=(((MSB<<4)&0x0FF0) | ((LSB>>12)&0x000F))<<1;

	SPI_I2S_SendData(SPI2, c);
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
	MSB=SPI_I2S_ReceiveData(SPI2);
//	i=0xff;
//	while(--i);
	SPI_I2S_SendData(SPI2, 0);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
	/* Return the byte read from the SPI bus */
	LSB=SPI_I2S_ReceiveData(SPI2);
	data=(((MSB<<4)&0x0FF0) | ((LSB>>12)&0x000F))<<1;



	i=0x0F;
	while(--i);
	TP_Deselect();

	return data;
}

void touchGetSense(int16_t * x, int16_t * y)
{
	uint32_t i=0x0f;
	uint16_t MSB, LSB, MSB2, LSB2;
	uint16_t datax, datay;
	TP_Select();
	while(--i);
	
	SPI_I2S_SendData(SPI2, 0x9300);
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
	MSB=SPI_I2S_ReceiveData(SPI2);
// 	i=0xff;
// 	while(--i);
	// Read MSB
	SPI_I2S_SendData(SPI2, 0x9300);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
	LSB=SPI_I2S_ReceiveData(SPI2);

	// restart
	SPI_I2S_SendData(SPI2, 0xD300);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
	MSB2=SPI_I2S_ReceiveData(SPI2);
	// Read MSB
	SPI_I2S_SendData(SPI2, 0xD300);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
	LSB2=SPI_I2S_ReceiveData(SPI2);
	// Read LSB
// 	SPI_I2S_SendData(SPI2, 0x00);
// 	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
// 	LSB2=SPI_I2S_ReceiveData(SPI2);

	datax=((MSB<<4)&0x0FF0) | ((LSB>>12)&0x0F);
	datay=((MSB2<<4)&0x0FF0) | ((LSB2>>12)&0x0F);



	i=0x0F;
	while(--i);
	TP_Deselect();

	*x = ((datax/11)-17);	
	*y = (256-(datay/15));
	
	
	
	
}


