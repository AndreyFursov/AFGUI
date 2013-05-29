#include "at26df.h"
#include "hw_config.h"
#ifdef STM32F2XX
#include "stm32f2xx_conf.h"
#endif
#ifdef STM32F10X_CL
#include "stm32f10x.h"
#endif


void sFLASH_LowLevel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*!< sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO 
			 and sFLASH_SPI_SCK_GPIO Periph clock enable */
	RCC_AHB1PeriphClockCmd(sFLASH_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK |
												 sFLASH_SPI_SCK_GPIO_CLK, ENABLE);
	
	GPIO_PinAFConfig  (GPIOB, GPIO_PinSource13, GPIO_AF_SPI2 );
	GPIO_PinAFConfig  (GPIOB, GPIO_PinSource14, GPIO_AF_SPI2 );
	GPIO_PinAFConfig  (GPIOB, GPIO_PinSource15, GPIO_AF_SPI2 );
	

	/*!< sFLASH_SPI Periph clock enable */
	if (sFLASH_SPI == SPI1)
		RCC_APB2PeriphClockCmd(sFLASH_SPI_CLK, ENABLE);
	else	
		RCC_APB1PeriphClockCmd(sFLASH_SPI_CLK, ENABLE);
	/*!< Configure sFLASH_SPI pins: SCK */
	GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_SPI pins: MOSI */
	GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
	GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/*!< Configure sFLASH_SPI pins: MISO */
	GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
	GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
	
	/*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
	GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

unsigned char sFLASH_SendByte(unsigned char byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);
	
	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(sFLASH_SPI, byte);
	
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	
	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(sFLASH_SPI);
}



void sFLASH_Init(void)
{
	SPI_InitTypeDef	SPI_InitStructure;

	sFLASH_LowLevel_Init();
		
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< SPI configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL)
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
#else
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
#endif

	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(sFLASH_SPI, &SPI_InitStructure);

	/*!< Enable the sFLASH_SPI	*/
	SPI_Cmd(sFLASH_SPI, ENABLE);
}


unsigned int sFLASH_ReadID(void)
{
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;
	
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	
	/*!< Send "RDID " instruction */
	sFLASH_SendByte(0x9F);
	
	/*!< Read a byte from the FLASH */
	Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	/*!< Read a byte from the FLASH */
	Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	/*!< Read a byte from the FLASH */
	Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
	
	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
	
	return Temp;
}

unsigned int sFLASH_ReadStatus(void)
{
	unsigned int Temp0 = 0;
	
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	
	/*!< Send "RDID " instruction */
	sFLASH_SendByte(sFLASH_CMD_RDSR);
	
	/*!< Read a byte from the FLASH */
	Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	/*!< Read a byte from the FLASH */
	//Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	/*!< Read a byte from the FLASH */
	//Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
	
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
	
	//Temp = Temp0;
	
	return Temp0;
}

void sFLASH_EraseSector(unsigned int SectorAddr)
{
	__IO unsigned int status;
	/*!< Send write enable instruction */
	sFLASH_WriteEnable();
	/*!< Sector Erase */
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	/*!< Send Sector Erase instruction */
	sFLASH_SendByte(sFLASH_CMD_SE);
	/*!< Send SectorAddr high nibble address byte */
	sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
	/*!< Send SectorAddr medium nibble address byte */
	sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
	/*!< Send SectorAddr low nibble address byte */
	sFLASH_SendByte(SectorAddr & 0xFF);
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
}

void sFLASH_EraseBlock4k(unsigned int SectorAddr)
{
	__IO unsigned int status;
	/*!< Send write enable instruction */
	sFLASH_WriteEnable();
	/*!< Sector Erase */
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	/*!< Send Sector Erase instruction */
	sFLASH_SendByte(sFLASH_CMD_4K_ERASE);
	/*!< Send SectorAddr high nibble address byte */
	sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
	/*!< Send SectorAddr medium nibble address byte */
	sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
	/*!< Send SectorAddr low nibble address byte */
	sFLASH_SendByte(SectorAddr & 0xFF);
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
}

void sFLASH_EraseBlock32k(unsigned int SectorAddr)
{
	__IO unsigned int status;
	/*!< Send write enable instruction */
	sFLASH_WriteEnable();
	/*!< Sector Erase */
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	/*!< Send Sector Erase instruction */
	sFLASH_SendByte(sFLASH_CMD_32K_ERASE);
	/*!< Send SectorAddr high nibble address byte */
	sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
	/*!< Send SectorAddr medium nibble address byte */
	sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
	/*!< Send SectorAddr low nibble address byte */
	sFLASH_SendByte(SectorAddr & 0xFF);
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
}

void sFLASH_EraseBulk(void)
{
	/*!< Send write enable instruction */
	sFLASH_WriteEnable();

	/*!< Bulk Erase */
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	/*!< Send Bulk Erase instruction	*/
	sFLASH_SendByte(sFLASH_CMD_BE);
	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
}

void sFLASH_WritePage(unsigned char * pBuffer, unsigned int WriteAddr, unsigned int NumByteToWrite)
{
	/*!< Enable the write access to the FLASH */
	sFLASH_WriteEnable();

	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();
	/*!< Send "Write to Memory " instruction */
	sFLASH_SendByte(sFLASH_CMD_WRITE);
	/*!< Send WriteAddr high nibble address byte to write to */
	sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
	/*!< Send WriteAddr medium nibble address byte to write to */
	sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
	/*!< Send WriteAddr low nibble address byte to write to */
	sFLASH_SendByte(WriteAddr & 0xFF);

	/*!< while there is data to be written on the FLASH */
	while (NumByteToWrite--)
	{
		/*!< Send the current byte */
		sFLASH_SendByte(*pBuffer);
		/*!< Point on the next byte to be written */
		pBuffer++;
	}

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();

	/*!< Wait the end of Flash writing */
	sFLASH_WaitForWriteEnd();
}

void sFLASH_WriteBuffer(unsigned char* pBuffer, unsigned int WriteAddr, unsigned int NumByteToWrite)
{
	unsigned char NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

	Addr = WriteAddr % sFLASH_SPI_PAGESIZE;
	count = sFLASH_SPI_PAGESIZE - Addr;
	NumOfPage =	NumByteToWrite / sFLASH_SPI_PAGESIZE;
	NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

	if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned	*/
	{
		if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
		{
			sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
		}
		else /*!< NumByteToWrite > sFLASH_PAGESIZE */
		{
			while (NumOfPage--)
			{
				sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
				WriteAddr +=	sFLASH_SPI_PAGESIZE;
				pBuffer += sFLASH_SPI_PAGESIZE;
			}

			sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
		}
	}
	else /*!< WriteAddr is not sFLASH_PAGESIZE aligned	*/
	{
		if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
		{
			if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
			{
				temp = NumOfSingle - count;

				sFLASH_WritePage(pBuffer, WriteAddr, count);
				WriteAddr +=	count;
				pBuffer += count;

				sFLASH_WritePage(pBuffer, WriteAddr, temp);
			}
			else
			{
				sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
			}
		}
		else /*!< NumByteToWrite > sFLASH_PAGESIZE */
		{
			NumByteToWrite -= count;
			NumOfPage =	NumByteToWrite / sFLASH_SPI_PAGESIZE;
			NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

			sFLASH_WritePage(pBuffer, WriteAddr, count);
			WriteAddr +=	count;
			pBuffer += count;

			while (NumOfPage--)
			{
				sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
				WriteAddr +=	sFLASH_SPI_PAGESIZE;
				pBuffer += sFLASH_SPI_PAGESIZE;
			}

			if (NumOfSingle != 0)
			{
				sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
			}
		}
	}
}

/**
	* @brief	Reads a block of data from the FLASH.
	* @param	pBuffer: pointer to the buffer that receives the data read from the FLASH.
	* @param	ReadAddr: FLASH's internal address to read from.
	* @param	NumByteToRead: number of bytes to read from the FLASH.
	* @retval None
	*/
void sFLASH_ReadBuffer(unsigned char * pBuffer, unsigned int ReadAddr, unsigned int NumByteToRead)
{
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Read from Memory " instruction */
	sFLASH_SendByte(sFLASH_CMD_READ);

	/*!< Send ReadAddr high nibble address byte to read from */
	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	sFLASH_SendByte(ReadAddr & 0xFF);

	while (NumByteToRead--) /*!< while there is data to be read */
	{
		/*!< Read a byte from the FLASH */
		*pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
		/*!< Point to the next location where the byte read will be saved */
		pBuffer++;
	}

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
}


/**
	* @brief	Initiates a read data byte (READ) sequence from the Flash.
	*	 This is done by driving the /CS line low to select the device, then the READ
	*	 instruction is transmitted followed by 3 bytes address. This function exit
	*	 and keep the /CS line low, so the Flash still being selected. With this
	*	 technique the whole content of the Flash is read with a single READ instruction.
	* @param	ReadAddr: FLASH's internal address to read from.
	* @retval None
	*/
void sFLASH_StartReadSequence(unsigned int ReadAddr)
{
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Read from Memory " instruction */
	sFLASH_SendByte(sFLASH_CMD_READ);

	/*!< Send the 24-bit address of the address to read from -------------------*/
	/*!< Send ReadAddr high nibble address byte */
	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte */
	sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte */
	sFLASH_SendByte(ReadAddr & 0xFF);
}


/**
	* @brief	Reads a byte from the SPI Flash.
	* @note	 This function must be used only if the Start_Read_Sequence function
	*				 has been previously called.
	* @param	None
	* @retval Byte Read from the SPI Flash.
	*/
unsigned char sFLASH_ReadByte(void)
{
	return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

void sFLASH_GlobalUnprotect(void)
{
	sFLASH_WriteEnable();
	
	sFLASH_CS_LOW();
	
	sFLASH_SendByte(sFLASH_CMD_WRSR);
	
	sFLASH_SendByte(0);

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
	
}	

/**
	* @brief	Enables the write access to the FLASH.
	* @param	None
	* @retval None
	*/
void sFLASH_WriteEnable(void)
{
	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Write Enable" instruction */
	sFLASH_SendByte(sFLASH_CMD_WREN);
	
	sFLASH_CS_HIGH();
	


	
}

/**
	* @brief	Polls the status of the Write In Progress (WIP) flag in the FLASH's
	*				 status register and loop until write opertaion has completed.
	* @param	None
	* @retval None
	*/
void sFLASH_WaitForWriteEnd(void)
{
	unsigned char flashstatus = 0;

	/*!< Select the FLASH: Chip Select low */
	sFLASH_CS_LOW();

	/*!< Send "Read Status Register" instruction */
	sFLASH_SendByte(sFLASH_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do
	{
		/*!< Send a dummy byte to generate the clock needed by the FLASH
		and put the value of the status register in FLASH_Status variable */
		flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

	}
	while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

	/*!< Deselect the FLASH: Chip Select high */
	sFLASH_CS_HIGH();
}


