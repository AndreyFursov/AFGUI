#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#include "stm32f2xx_conf.h"
//************************************************************
// USE SECTION

//#define USE_USART1
//#define USE_USART2
#define USE_USART3
#define USE_FLASH_SPI2




//************************************************************
// USART SECTION
//************************************************************
#define USART1_DR_Base	((unsigned int)0x40011004)
#define USART2_DR_Base	((unsigned int)0x40004404)
#define USART3_DR_Base	((unsigned int)0x40004804)

#define USART1_TX_DMACH		DMA2_Stream7
#define USART1_RX_DMACH		DMA2_Stream5
#define USART2_TX_DMACH		DMA1_Stream6
#define USART2_RX_DMACH		DMA1_Stream5
#define USART3_TX_DMACH		DMA1_Stream3
#define USART3_RX_DMACH		DMA1_Stream1


#ifdef USE_USART1
	#define USART1_RX_BUF_SIZE 		264	
	#define USART1_TX_BUF_SIZE 		264

	#define PORT_USART1_TX 			GPIOB
	#define GPIO_USART1_TX 			GPIO_Pin_6
	#define AF_USART1_TX 			GPIO_PinSource6
	
	#define PORT_USART1_RX 			GPIOB
	#define GPIO_USART1_RX 			GPIO_Pin_7
	#define AF_USART1_RX 			GPIO_PinSource7

	#define USART1_DEF_SPEED 9600
	#define USART1_USE_RS485
	
	#ifdef USART1_USE_RS485
		#define USART1_485DE_PORT	GPIOG
		#define USART1_485DE_PIN	GPIO_Pin_14
		#define USART1_DE_485_ON()	GPIO_SetBits	(USART1_485DE_PORT, USART1_485DE_PIN)
		#define USART1_DE_485_OFF()	GPIO_ResetBits	(USART1_485DE_PORT, USART1_485DE_PIN)
		#define USART1_AHB_GPIO		RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOG
	#else
		#define USART1_AHB_GPIO		RCC_AHB1Periph_GPIOB
	#endif
	
	#define USART1_TX_DMA_CHANNEL 		DMA_Channel_4
	#define USART1_RX_DMA_CHANNEL 		DMA_Channel_4
#endif

#ifdef USE_USART2
	#define USART2_RX_BUF_SIZE 	264	
	#define USART2_TX_BUF_SIZE 	264

	#define PORT_USART2_TX 	GPIOA
	#define GPIO_USART2_TX 	GPIO_Pin_2
	#define AF_USART2_TX 	GPIO_PinSource2

	#define PORT_USART2_RX 	GPIOA
	#define GPIO_USART2_RX 	GPIO_Pin_3
	#define AF_USART2_RX 	GPIO_PinSource3

	#define USART2_DEF_SPEED 9600
	
	#define USART2_USE_RS485
	#ifdef USART2_USE_RS485
		#define 	USART2_485DE_PORT	GPIOC
		#define 	USART2_485DE_PIN	GPIO_Pin_3
		#define 	USART2_DE_485_ON()	GPIO_SetBits	(USART2_485DE_PORT, USART2_485DE_PIN)
		#define 	USART2_DE_485_OFF()	GPIO_ResetBits	(USART2_485DE_PORT, USART2_485DE_PIN)
		#define 	USART2_AHB_GPIO		RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC
	#else
		#define USART2_AHB_GPIO			RCC_AHB1Periph_GPIOA
	#endif
	
	#define USART2_TX_DMA_CHANNEL 		DMA_Channel_4
	#define USART2_RX_DMA_CHANNEL 		DMA_Channel_4
	
#endif

#ifdef USE_USART3
	#define USART3_RX_BUF_SIZE 	264	
	#define USART3_TX_BUF_SIZE 	264

	#define PORT_USART3_TX 	GPIOB
	#define GPIO_USART3_TX 	GPIO_Pin_10
	#define AF_USART3_TX 	GPIO_PinSource10

	#define PORT_USART3_RX 	GPIOB
	#define GPIO_USART3_RX 	GPIO_Pin_11
	#define AF_USART3_RX 	GPIO_PinSource11

	#define USART3_DEF_SPEED 115200
	
	//#define USART3_USE_RS485
	#ifdef USART3_USE_RS485
		#define USART3_485DE_PORT	GPIOG
		#define USART3_485DE_PIN	GPIO_Pin_14
		#define USART3_DE_485_ON()	GPIO_SetBits	(USART3_485DE_PORT, USART3_485DE_PIN)
		#define USART3_DE_485_OFF()	GPIO_ResetBits	(USART3_485DE_PORT, USART3_485DE_PIN)
		#define USART3_AHB_GPIO		RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOG
	#else
		#define USART3_AHB_GPIO		RCC_AHB1Periph_GPIOB
	#endif
	
	#define USART3_TX_DMA_CHANNEL 		DMA_Channel_4
	#define USART3_RX_DMA_CHANNEL 		DMA_Channel_4
	
#endif

// <-- ***************************************************************





//********************************************************************
// SPI FLASH
//********************************************************************
#ifdef USE_FLASH_SPI2
	#define sFLASH_SPI                       SPI2
	#define sFLASH_SPI_CLK                   RCC_APB1Periph_SPI2
	#define sFLASH_SPI_SCK_PIN               GPIO_Pin_13                 
	#define sFLASH_SPI_SCK_GPIO_PORT         GPIOB                      
	#define sFLASH_SPI_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOB
	#define sFLASH_SPI_MISO_PIN              GPIO_Pin_14                 
	#define sFLASH_SPI_MISO_GPIO_PORT        GPIOB                      
	#define sFLASH_SPI_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOB
	#define sFLASH_SPI_MOSI_PIN              GPIO_Pin_15                 
	#define sFLASH_SPI_MOSI_GPIO_PORT        GPIOB                      
	#define sFLASH_SPI_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOB
	#define sFLASH_CS_PIN                    GPIO_Pin_7                
	#define sFLASH_CS_GPIO_PORT              GPIOG                      
	#define sFLASH_CS_GPIO_CLK               RCC_AHB1Periph_GPIOG

	#define sFLASH_BLOCK_SIZE		0x1000
#endif


//********************************************************************
// SPI for TouchPanel (ADS7843)
//********************************************************************
#define SPI_TP				SPI3
#define GPIO_Pin_TP_SCK		GPIO_Pin_3
#define GPIO_Pin_TP_MISO	GPIO_Pin_4
#define GPIO_Pin_TP_MOSI	GPIO_Pin_5
#define GPIO_Pin_TP_CS		GPIO_Pin_15
#define GPIO_Pin_TP_IRQ		GPIO_Pin_13
#define PORT_TP_SPI			GPIOB
#define PORT_TP_CS			GPIOG
#define PORT_TP_IRQ			GPIOG

#define AHB1_TP_GPIO_SPI	RCC_AHB1Periph_GPIOB
#define AHB1_TP_GPIO_CS		RCC_AHB1Periph_GPIOG
#define AHB1_TP_GPIO_IRQ	RCC_AHB1Periph_GPIOG
#define APB1_TP_SPI			RCC_APB1Periph_SPI3

#define GPIO_TP_AF_SCK 		GPIO_PinSource3
#define GPIO_TP_AF_MISO		GPIO_PinSource4
#define GPIO_TP_AF_MOSI		GPIO_PinSource5
#define GPIO_TP_AF_SPI		GPIO_AF_SPI3

#define TP_Select()			GPIO_ResetBits(PORT_TP_CS, GPIO_Pin_TP_CS)
#define TP_Deselect()		GPIO_SetBits(PORT_TP_CS, GPIO_Pin_TP_CS)



//********************************************************************
// ADC
//********************************************************************
#define ADC1_DR_Base    ((unsigned int)0x4001204C)


//********************************************************************
// Prototypes
//********************************************************************
extern unsigned int HardwareInit(void);


#endif
