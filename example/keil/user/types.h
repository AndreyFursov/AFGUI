#ifndef _TYPES_H_
#define _TYPES_H_

#include "HAL_Calender.h"
#include <string.h>

#define UART1_RX_BUF_SIZE 	512	
#define UART1_TX_BUF_SIZE 	512

#define UART2_RX_BUF_SIZE 	512	
#define UART2_TX_BUF_SIZE 	512

#define UART3_RX_BUF_SIZE 	512
#define UART3_TX_BUF_SIZE 	512

//#define UART4_RX_BUF_SIZE 	512
//#define UART4_TX_BUF_SIZE 	512


#define NUM_ADC_SAMPLE		200
#define NUM_DI				18
#define NUM_DO				10
#define NUM_AI				8


#define USART1_DR_Base	((unsigned int)0x40011004)
#define USART2_DR_Base	((unsigned int)0x40004404)
#define USART3_DR_Base	((unsigned int)0x40004804)
//#define USART4_DR_Base	((unsigned int)0x40004C04)

#define UART_UI 			USART1
#define UART_485 			USART2

#define UART_UI_DMA_TX 		DMA2_Stream7
#define UART_UI_DMA_RX 		DMA2_Stream5

#define UART_485_DMA_TX		DMA1_Stream6
#define UART_485_DMA_RX		DMA1_Stream5

#define UART_UI_TX_LEN 		UART1_TX_BUF_SIZE
#define UART_UI_RX_LEN		UART1_RX_BUF_SIZE
#define UART_485_TX_LEN 	UART2_TX_BUF_SIZE
#define UART_485_RX_LEN		UART2_RX_BUF_SIZE


#define USART3_TX_DMACH		DMA1_Stream3
#define USART3_RX_DMACH		DMA1_Stream1
#define USART2_TX_DMACH		DMA1_Stream6
#define USART2_RX_DMACH		DMA1_Stream5

#define USART1_TX_DMACH		DMA2_Stream7
#define USART1_RX_DMACH		DMA2_Stream5

#define ADC1_DR_Base    ((unsigned int)0x4001204C)

//-----------------------------

typedef unsigned int volatile SYSTEM_TIMER;
extern SYSTEM_TIMER getSystemTimer1ms(void);
extern SYSTEM_TIMER getSystemTimer1s(void);
extern void setSystemTimer1s(SYSTEM_TIMER timer);
extern unsigned int getAdcResult(void);
extern unsigned int HardwareInit(void);
extern void  delay_ms(SYSTEM_TIMER _time);
   //--- NVIC

//#define ISRPENDING  (1u<<22)
#define VECTACTIVE  (0x000001FF)
#define rNVIC_ICSR  (*((__IO unsigned int*)0xE000ED04))


typedef struct
{
	SYSTEM_TIMER lastResp;
	SYSTEM_TIMER lastRespTnu;

	unsigned 	resWriteDateTime	: 1;
	unsigned 	resReadDateTime		: 1;
	unsigned 	resReadTnu			: 1;
	unsigned 	resReadCfg			: 1;
	unsigned 	resReadCfgUser		: 1;
	unsigned 	resWriteCfg			: 1;
	unsigned 	resWriteCfgUser		: 1;
	unsigned 	resWriteAck			: 1;
	
	unsigned 	resWriteStart		: 1;
	unsigned 	resWriteStop		: 1;
	
	
	
	
	
	
} RESPONSE_STATE;

extern RESPONSE_STATE* getPtrRespState(void);


#endif
