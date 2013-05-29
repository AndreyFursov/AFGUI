#ifndef __AT26DF_H
#define __AT26DF_H

// prototypes
//high  Layer
void sFLASH_DeInit(void);
void sFLASH_Init(void);
void sFLASH_EraseSector(unsigned int SectorAddr);
void sFLASH_EraseBlock4k(unsigned int SectorAddr);
void sFLASH_EraseBlock32k(unsigned int SectorAddr);
void sFLASH_EraseBulk(void);
void sFLASH_WritePage(unsigned char * pBuffer, unsigned int WriteAddr, unsigned int NumByteToWrite);
void sFLASH_WriteBuffer(unsigned char * pBuffer, unsigned int WriteAddr, unsigned int NumByteToWrite);
void sFLASH_ReadBuffer(unsigned char * pBuffer, unsigned int ReadAddr, unsigned int NumByteToRead);
unsigned int sFLASH_ReadID(void);
unsigned int sFLASH_ReadStatus(void);
void sFLASH_StartReadSequence(unsigned int ReadAddr);
// low Layer
unsigned char sFLASH_ReadByte(void);
unsigned char sFLASH_SendByte(unsigned char byte);
unsigned short sFLASH_SendHalfWord(unsigned short HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);
void sFLASH_GlobalUnprotect(void);


#define sFLASH_CS_LOW()       GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
#define sFLASH_CS_HIGH()      GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)   


#define sFLASH_CMD_WRITE          0x02  /*!< Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /*!< Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /*!< Write enable instruction */
#define sFLASH_CMD_READ           0x03  /*!< Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /*!< Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /*!< Read identification */
#define sFLASH_CMD_SE             0xD8  /*!< Sector Erase instruction */
#define sFLASH_CMD_BE             0xC7  /*!< Bulk Erase instruction */
#define sFLASH_CMD_4K_ERASE       0x20  /*!< Bulk Erase instruction */
#define sFLASH_CMD_32K_ERASE      0x52  /*!< Bulk Erase instruction */

#define sFLASH_WIP_FLAG           0x01  /*!< Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100

#define sFLASH_M25P128_ID         0x202018
#define sFLASH_M25P64_ID          0x202017




#endif
