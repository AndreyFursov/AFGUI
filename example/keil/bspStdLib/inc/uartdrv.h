#ifndef USARTDRV_H
#define USARTDRV_H

typedef  struct
{
	unsigned int 	uSpeed;
	unsigned char *	uTxBuf;
	unsigned char *	uRxBuf;
	unsigned int 	uTxBufLen;
	unsigned int 	uRxBufLen;

	unsigned short	uTxNumByte;
	unsigned short	uTxCountByte;

	unsigned short	uRxCountByte;
	unsigned short	uRxLastCountByte;
	
	unsigned short	uParity;	// 0 - no parity, 1 - нечет, 2 - четный
	
} USARTDRV;

extern void uart_drvInit(USART_TypeDef * _uart, USARTDRV * _uDrv);

extern void uart485_SendDma(USART_TypeDef * _uart,  DMA_Stream_TypeDef * _dmach, unsigned int _len, unsigned int _maxlen);
extern void uart_SendDma(USART_TypeDef * _uart,  DMA_Stream_TypeDef * _dmach, unsigned int _len, unsigned int _maxlen);
extern void uartDrv_Init(USART_TypeDef * _uart,  
							unsigned int _uart_dr_base, 
							DMA_Stream_TypeDef * _dmachTx, 
							DMA_Stream_TypeDef * _dmachRx, 
							USARTDRV * _uDrv
							);
extern void uartClrRx(USARTDRV * _uDrv, DMA_Stream_TypeDef * _dmach);							

#endif
