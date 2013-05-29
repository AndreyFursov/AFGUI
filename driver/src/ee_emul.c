/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_conf.h"
#include "ee_emul.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t const eepromdata[PAGE_SIZE] __attribute__((at(EEPROM_START_ADDRESS)));

uint16_t EE_ReadBuf(uint16_t EEAddress, uint16_t* _data, uint16_t len)
{
	volatile uint16_t * fData, i;
	
	fData = (volatile uint16_t *)(EEAddress + EEPROM_START_ADDRESS);
	
	for (i = 0; i < len; i++)
	{
		_data[i] = fData[i];
	}
	
	return i;
}

uint16_t EE_WriteBuf(uint16_t EEAddress, uint16_t* _data, uint16_t len)
{
	uint16_t * rData, * fData;
	uint32_t adr;
	uint32_t ret;
	uint32_t i;
	volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

	ret = 0;
	// check data
	rData = (uint16_t *)_data;
	fData = (uint16_t *)(EEAddress + EEPROM_START_ADDRESS);
	adr = EEAddress + EEPROM_START_ADDRESS;
	for (i = 0; i < len; i++)
	{
		if (rData[i] != fData[i] )
		{
			ret = 1;
			if (fData[i] != 0xFFFF) 
			{
				ret = 2;
				i = len;
			}
		}
	}
	
	if (ret)
	{
		FLASH_Unlock();
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
			FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
		// Clear Page
		if (ret == 2)
			FLASHStatus = FLASH_EraseSector(PAGE0_ID, VOLTAGE_RANGE);
		ret = 0;
		if (FLASHStatus == FLASH_COMPLETE)
		{
			for (i = 0; i < len; i++)
			{
				FLASHStatus = FLASH_ProgramHalfWord(adr, rData[i]);
				adr += 2;
			}
			// check flash write
			rData = (uint16_t *)_data;
			fData = (uint16_t *)(EEAddress + EEPROM_START_ADDRESS);
			for (i = 0; i < len; i++)
			{
				if (rData[i] != fData[i] ) ret = 1;
			}
		}
		else
		{
			ret = 2;
		}
		FLASH_Lock();
	}
	return ret;
}

