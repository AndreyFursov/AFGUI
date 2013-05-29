#ifndef CRCM_H
#define CRCM_H


// аппаратный CRC
/*
#define CRC16_POLYLEN	0x000F	// Length of polynomial-1
#define CRC16_POLY	0x8005	// Generator Polynomial X^12 + X^5
#define CRC16_INIT	0xFFFF	// Generator Polynomial X^12 + X^5
						 
extern void CRC_Init(void);

extern UINT16 CRC_Calc_ChecksumByte(UINT8* data, UINT16 Number_of_bytes, UINT16 prev_CRC) __attribute__ ((section (".libperi")));// <<-- аппаратный CRC
*/




// CRC16 for ModBus
extern unsigned short Crc16ModBus(unsigned char * , unsigned int );
extern unsigned short Crc16ModBusNext(unsigned char * , unsigned int , unsigned short);
//extern unsigned int Crc16Mercury(unsigned char * , unsigned short );
// CRC16 for PPP
unsigned short Crc16ppp( unsigned char *, unsigned short);


extern unsigned short Crc16(unsigned char * , unsigned short );




#endif
