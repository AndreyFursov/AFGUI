/*
 * ads7843.c
 *
 *  Created on: 11.01.2013
 *      Author: Andrey Fursov
 */


#include "stm32f2xx_conf.h"
#include "ads7843.h"

int16_t ax, bx, ay, by;

void touchSetCoef(int16_t _ax, int16_t _bx, int16_t _ay, int16_t _by)
{
	ax = _ax;
	bx = _bx;
	ay = _ay;
	by = _by;
}

void touchGetCoef(int16_t *_ax, int16_t *_bx, int16_t *_ay, int16_t *_by)
{
	*_ax = ax;
	*_bx = bx;
	*_ay = ay;
	*_by = by;
}

uint16_t touchVerifyCoef(void)
{
	uint16_t ret = 0;
	if (ax == 0 || ax == 0xFFFF
		|| bx == 0xFFFF
		|| ay == 0 || ay == 0xFFFF
		|| by == 0xFFFF)
	ret = 1;
	return ret;
}


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

 	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;			// PC13 touch
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


int16_t touchGetX(void)
{
	uint16_t LSB, MSB;
	int16_t ret = 4095;

	if (GPIO_ReadInputDataBit (GPIOD, GPIO_Pin_12) == 0)
	{
		TP_Select();
		ret = 0x2F;
		while(--ret);
		// x
		SPI_I2S_SendData(SPI2, 0x9400);
		/* Wait to receive a byte */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		MSB=SPI_I2S_ReceiveData(SPI2);
		SPI_I2S_SendData(SPI2, 0);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		/* Return the byte read from the SPI bus */
		LSB=SPI_I2S_ReceiveData(SPI2);

		ret=0x0F;
		while(--ret);
		TP_Deselect();

		ret = ( ((MSB<<4) & 0x0FF0) | ((LSB>>12) & 0x000F) )<<1;
	}

	return ret;
}

int16_t touchGetY(void)
{
	uint16_t LSB, MSB;
	int16_t ret = 4095;

	if (GPIO_ReadInputDataBit (GPIOD, GPIO_Pin_12) == 0)
	{
		TP_Select();
		ret = 0x2F;
		while(--ret);
		// y
		SPI_I2S_SendData(SPI2, 0xD400);
		/* Wait to receive a byte */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		MSB=SPI_I2S_ReceiveData(SPI2);
		SPI_I2S_SendData(SPI2, 0);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		/* Return the byte read from the SPI bus */
		LSB=SPI_I2S_ReceiveData(SPI2);
		ret=0x0F;
		while(--ret);
		TP_Deselect();

		ret = ( ((MSB<<4) & 0x0FF0) | ((LSB>>12) & 0x000F) )<<1;
	}
	return ret;
}


void touchGetSense(int16_t * x, int16_t * y)
{
	uint32_t i=0x0f;
	uint16_t MSB, LSB;
	int16_t datax, datay;
	
	if (GPIO_ReadInputDataBit (GPIOD, GPIO_Pin_12) == 0)
	{
	
		TP_Select();
		while(--i);


		// x
		SPI_I2S_SendData(SPI2, 0x9400);
		/* Wait to receive a byte */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		MSB=SPI_I2S_ReceiveData(SPI2);
		SPI_I2S_SendData(SPI2, 0);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		/* Return the byte read from the SPI bus */
		LSB=SPI_I2S_ReceiveData(SPI2);
		datax = ( ((MSB<<4) & 0x0FF0) | ((LSB>>12) & 0x000F) )<<1;
		datax = (datax/ax)+bx;
		//datax = (datax/11)-17;

		// y
		SPI_I2S_SendData(SPI2, 0xD400);
		/* Wait to receive a byte */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		MSB=SPI_I2S_ReceiveData(SPI2);
		SPI_I2S_SendData(SPI2, 0);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) { ; }
		/* Return the byte read from the SPI bus */
		LSB=SPI_I2S_ReceiveData(SPI2);
		datay = ( ((MSB<<4) & 0x0FF0) | ((LSB>>12) & 0x000F) )<<1;
		//datay = 256 - (datay/15);
		datay = (datay/ay)+by;

		i=0x0F;
		while(--i);
		TP_Deselect();
	}
	else
	{
		datax = 4095;
		datay = 4095;
	}
	
	

	*x = datax;
	*y = datay;
}

uint16_t getTouchState(void)
{
	uint16_t ret = 0;
	
	if (GPIO_ReadInputDataBit (GPIOD, GPIO_Pin_12) == 0)
		ret = 1;
	return ret;
}

