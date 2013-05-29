
#include "hw_config.h"
#include "uartdrv.h"

#ifdef STM32F10X_CL
#include "stm32f10x_conf.h"
#endif
#ifdef STM32F2XX
#include "stm32f2xx_conf.h"


#endif



void uart_SendDma(USART_TypeDef * _uart,  DMA_Stream_TypeDef * _dmach, unsigned int _len, unsigned int _maxlen)
{
	unsigned int cnt = 0;
	// включаем DE, отключаем прием
	if (_uart == USART1)
	{
		#ifdef USART1_USE_RS485
		USART1_DE_485_ON();
		_uart->CR1 &= ~USART_Mode_Rx;
		cnt = 100;
		#endif
	}
	if (_uart == USART2)
	{
		#ifdef USART2_USE_RS485
		USART2_DE_485_ON();
		_uart->CR1 &= ~USART_Mode_Rx;
		cnt = 100;
		#endif
	}
	if (_uart == USART3)
	{
		#ifdef USART3_USE_RS485
		USART3_DE_485_ON();
		_uart->CR1 &= ~USART_Mode_Rx;
		cnt = 100;
		#endif
	}
	while (cnt--);
	if (_len > _maxlen) _len = _maxlen;
	
	// запускаем передачу данных	
	if (_len > _maxlen) _len = _maxlen;
	DMA_Cmd(_dmach, DISABLE);
	DMA_SetCurrDataCounter (_dmach,  _len); 
	if (_uart == USART3)
	{
		DMA_ClearFlag  ( _dmach, DMA_FLAG_TCIF3);  
		DMA_ClearFlag  ( _dmach, DMA_FLAG_HTIF3);  
		DMA_ClearFlag  ( _dmach, DMA_FLAG_FEIF3);  
	}
	if (_uart == USART2)
	{
		DMA_ClearFlag  ( _dmach, DMA_FLAG_TCIF6);  
		DMA_ClearFlag  ( _dmach, DMA_FLAG_HTIF6);  
		DMA_ClearFlag  ( _dmach, DMA_FLAG_FEIF6);  
	}
	if (_uart == USART1)
	{
		DMA_ClearFlag  ( _dmach, DMA_FLAG_TCIF7);  
		DMA_ClearFlag  ( _dmach, DMA_FLAG_HTIF7);  
		DMA_ClearFlag  ( _dmach, DMA_FLAG_FEIF7);  
	}
  

	DMA_Cmd(_dmach, ENABLE);
}




void uartClrRx(USARTDRV * _uDrv, DMA_Stream_TypeDef * _dmach)
{
	int i;
	for (i = 0; i < _uDrv->uRxCountByte; i++) _uDrv->uRxBuf[i] = 0;
	_uDrv->uRxCountByte = 0;
	DMA_Cmd(_dmach, DISABLE);
	DMA_SetCurrDataCounter (_dmach,  _uDrv->uRxBufLen); 
	DMA_Cmd(_dmach, ENABLE);
}


//*******************************************************************
// UART
void uart_drvInit(USART_TypeDef * _uart, USARTDRV * _uDrv)
{
	uint32_t
		dma_channel_tx = 0, 
		dma_channel_rx = 0, 
		uart_base = USART1_DR_Base		;	
	 DMA_Stream_TypeDef 
		* dma_stream_tx = 0, 
		* dma_stream_rx = 0;

	DMA_InitTypeDef DMA_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	GPIO_TypeDef * GPIOx = GPIOB;
	GPIO_InitTypeDef GPIO_InitStructure;

	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	// RCC
	#ifdef USE_USART1
	if (_uart == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		RCC_AHB1PeriphClockCmd(USART1_AHB_GPIO, ENABLE);
		GPIO_PinAFConfig(PORT_USART1_TX, AF_USART1_TX, GPIO_AF_USART1);	//TX
		GPIO_PinAFConfig(PORT_USART1_RX, AF_USART1_RX, GPIO_AF_USART1);	//RX
		GPIO_InitStructure.GPIO_Pin = GPIO_USART1_TX | GPIO_USART1_RX;
		GPIOx = PORT_USART1_TX;
		dma_channel_tx = USART1_TX_DMA_CHANNEL;
		dma_channel_rx = USART1_RX_DMA_CHANNEL;
		uart_base = USART1_DR_Base;
		dma_stream_tx = USART1_TX_DMACH;
		dma_stream_rx = USART1_RX_DMACH;
	}
	#endif
	#ifdef USE_USART2
	if (_uart == USART2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
		RCC_AHB1PeriphClockCmd(USART2_AHB_GPIO, ENABLE);
		GPIO_PinAFConfig(PORT_USART2_TX, AF_USART2_TX, GPIO_AF_USART2);	//TX
		GPIO_PinAFConfig(PORT_USART2_RX, AF_USART2_RX, GPIO_AF_USART2);	//RX
		GPIO_InitStructure.GPIO_Pin = GPIO_USART2_TX | GPIO_USART2_RX;
		GPIOx = PORT_USART2_TX;
		dma_channel_tx = USART2_TX_DMA_CHANNEL;
		dma_channel_rx = USART2_RX_DMA_CHANNEL;
		uart_base = USART2_DR_Base;
		dma_stream_tx = USART2_TX_DMACH;
		dma_stream_rx = USART2_RX_DMACH;
	}
	#endif
	#ifdef USE_USART3
	if (_uart == USART3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
		RCC_AHB1PeriphClockCmd(USART3_AHB_GPIO, ENABLE);
		GPIO_PinAFConfig(PORT_USART3_TX, AF_USART3_TX, GPIO_AF_USART3);	//TX
		GPIO_PinAFConfig(PORT_USART3_RX, AF_USART3_RX, GPIO_AF_USART3);	//RX
		GPIO_InitStructure.GPIO_Pin = GPIO_USART3_TX | GPIO_USART3_RX;
		GPIOx = PORT_USART3_TX;
		dma_channel_tx = USART3_TX_DMA_CHANNEL;
		dma_channel_rx = USART3_RX_DMA_CHANNEL;
		uart_base = USART3_DR_Base;
		dma_stream_tx = USART3_TX_DMACH;
		dma_stream_rx = USART3_RX_DMACH;
		
	}
	#endif
	
	// GPIO
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	// USART
	USART_OverSampling8Cmd(_uart, ENABLE);
	USART_InitStructure.USART_BaudRate   			= _uDrv->uSpeed;
	USART_InitStructure.USART_WordLength 			= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   			= USART_StopBits_1;
	USART_InitStructure.USART_Parity     			= _uDrv->uParity;
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode       			= USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(_uart, &USART_InitStructure);

	//DMA Ch UART RX
	DMA_InitStructure.DMA_Channel = dma_channel_rx;
	DMA_InitStructure.DMA_PeripheralBaseAddr = uart_base;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)_uDrv->uRxBuf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = _uDrv->uRxBufLen;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(dma_stream_rx, &DMA_InitStructure);	// usart1 rx

	//DMA Ch UART TX
	DMA_InitStructure.DMA_Channel = dma_channel_tx;
	DMA_InitStructure.DMA_PeripheralBaseAddr = uart_base;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)_uDrv->uTxBuf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(dma_stream_tx, &DMA_InitStructure);		// usart1 tx

	DMA_ITConfig(dma_stream_rx, DMA_IT_TC, ENABLE);	// usart1 rx
   
	USART_ITConfig(_uart, USART_IT_TC, ENABLE);

	USART_Cmd(_uart, ENABLE);

	USART_DMACmd(_uart, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
	
	DMA_Cmd(dma_stream_rx, ENABLE);
}

