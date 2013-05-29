/*
TNKernel real-time kernel - STMicroelectronics STM32F10X examples

Copyright © 2006, 2008 Yuri Tiomkin
All rights reserved.

Permission to use, copy, modify, and distribute this software in source
and binary forms and its documentation for any purpose and without fee
is hereby granted, provided that the above copyright notice appear
in all copies and that both that copyright notice and this permission
notice appear in supporting documentation.

THIS SOFTWARE IS PROVIDED BY THE YURI TIOMKIN AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL YURI TIOMKIN OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
*/

//#include "stm32f10x.h"
//#include "stm32f2xx_conf.h"

//#include "system_stm32f10x.h"
#include "types.h"
#include "globals.h"
#include "tn.h"

#define TPLL_M      16
#define TPLL_N      240
#define TPLL_P      2
#define TPLL_Q      5

//#include "at26df.h"

//#define USART2_DR_Base  0x40004404
//#define USART3_DR_Base  0x40004804
//#define USART4_DR_Base  0x40004C04

// USART3_TX - DMA1 - Ch4
// USART3_RX - DMA1 - Ch5
// USART2_RX - DMA1 - Ch6


//--- Local functions prototypes ----
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_cfg(void);
void DMA_cfg(void);
void SysTick_cfg(void);
void ADC_cfg(void);
unsigned int RTC_cfg(void);
void iwdg_init(void);
void SPI_TC_Init(void);
//void Beeper_Init(void);

unsigned short resultADC[NUM_ADC_SAMPLE];

unsigned int getAdcResult(void)
{
	unsigned int i, sum;
	sum = 0;
	for (i = 0; i < NUM_ADC_SAMPLE; i++)
	{
		sum += (unsigned int)resultADC[i];
	}
	sum /= (NUM_ADC_SAMPLE*4);
	if (sum > 1023) sum = 1023;
	return sum;
}


//----------------------------------------------------------------------------
unsigned int HardwareInit(void)
{
	unsigned int ret;
	ret = 0;
	RCC_Configuration();
//	DMA_cfg();
//	GPIO_Configuration();
	if (0 != RTC_cfg()) ret |= 1;
//	ADC_cfg();
//	NVIC_cfg();
	SysTick_cfg();
	TP_SPI_Config();
//	Beeper_Init();
// 	lcdInit();

	return ret;
}

//----------------------------------------------------------------------------
void RCC_Configuration(void)
{
 	unsigned int startDelay;

 	RCC_DeInit();  //-- RCC system reset(for debug purpose)
 	RCC_HSICmd(ENABLE);
 	RCC_HSEConfig(RCC_HSE_OFF);
// 		delay_40ms
 	startDelay = 960000;
 	while (startDelay) startDelay--;
 	
 	//-- Enable Prefetch Buffer
 	FLASH_PrefetchBufferCmd(ENABLE);
 	FLASH_SetLatency(FLASH_Latency_3); //-- Flash 3 wait state for 120MHz
 	
 	//-- PLLCLK = 16MHz/16 * 240/2 = 120 MHz
 	RCC_PLLCmd(DISABLE);
	RCC_HCLKConfig  (RCC_SYSCLK_Div1 ) ;
	RCC_PCLK1Config  ( RCC_HCLK_Div4) ;
	RCC_PCLK2Config  ( RCC_HCLK_Div2) ;
 	RCC_PLLConfig(RCC_PLLSource_HSI, TPLL_M, TPLL_N, TPLL_P, TPLL_Q);
	
// 	

// 	//-- Enable PLL &  wait till PLL is ready
 	RCC_PLLCmd(ENABLE);
 	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

// 	startDelay = 240000;
// 	while (startDelay) startDelay--;

// 	//-- Select PLL as system clock source & wait till PLL is used
// 	//-- as system clock source
 	startDelay = 10000;
 	while (startDelay) startDelay--;
 	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
//	while(RCC_GetSYSCLKSource() != 0x08);
//    
//	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	startDelay = RCC_GetSYSCLKSource()  ;
	/* DMA clock enable */
	RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_DMA1	| RCC_AHB1Periph_DMA2 |
							RCC_AHB1Periph_BKPSRAM,
							ENABLE);
   
	/* Enable USART2 clock */
	// uart4 rs-485, uart6 irps
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_USART3 	| RCC_APB1Periph_UART4	|
   							RCC_APB1Periph_PWR 		| RCC_APB1Periph_TIM2,
							ENABLE);

	/* Enable USART1, GPIOA, GPIOx and AFIO clocks */
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_ADC1 	| RCC_APB2Periph_ADC2 	|
   							RCC_APB2Periph_USART1 , 	
							ENABLE);
							
	RCC_AHB3PeriphClockCmd  ( RCC_AHB3Periph_FSMC ,  
							ENABLE);

}



void ADC_cfg(void)
{
	ADC_InitTypeDef 			ADC_InitStructure;
	ADC_CommonInitTypeDef 		ADC_CommonInitStructure;
	GPIO_InitTypeDef 			GPIO_InitStructure;
	RCC_ClocksTypeDef 			RCC_Clocks;
	TIM_TimeBaseInitTypeDef   	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef         	TIM_OCInitStructure;
	DMA_InitTypeDef DMA_InitStructure;


	// RCC - Enable peripheral clocks
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// DMA
	DMA_InitStructure.DMA_Channel = DMA_Channel_0; 
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&resultADC[0];
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Base;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = NUM_ADC_SAMPLE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	/* DMA2_Stream0 enable */
	DMA_Cmd(DMA2_Stream0, ENABLE);
	
	/*
	DMA_DeInit(DMA1_Channel1);
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Base;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&resultADC[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = NUM_ADC_SAMPLE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	// Enable DMA1 Channel1 
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	*/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	/* TIM2 configuration ------------------------------------------------------*/ 
	/* Time Base configuration */
	RCC_GetClocksFreq(&RCC_Clocks);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = RCC_Clocks.SYSCLK_Frequency/10000;          
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM2 channel1 configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
	TIM_OCInitStructure.TIM_Pulse = RCC_Clocks.SYSCLK_Frequency/20000; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	

	//TIM_UpdateDisableConfig(TIM3, ENABLE);

 
//	/* ADC1 configuration ------------------------------------------------------*/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;

	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel13 configuration */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_84Cycles);

	//ADC_ExternalTrigConvCmd(ADC1, ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);


 	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable Vrefint channel17 */
	ADC_TempSensorVrefintCmd(ENABLE);
	
	/* Enable ADC1 reset calibaration register */   
//	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
//	while(ADC_GetResetCalibrationStatus(ADC1));
	 
	   /* Start ADC1 calibaration */
//	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
//	while(ADC_GetCalibrationStatus(ADC1));
	
	
	
}

//----------------------------------------------------------------------------
void GPIO_Configuration(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   
//GPIO_Mode_IN  GPIO Input Mode 
//GPIO_Mode_OUT  GPIO Output Mode 
//GPIO_Mode_AF  GPIO Alternate function Mode 
//GPIO_Mode_AN  GPIO Analog Mode 

//GPIO_PuPd_NOPULL   
//GPIO_PuPd_UP   
//GPIO_PuPd_DOWN   

 

	
	//**********************************************************************
	// PORTA

//	GPIO_Write(GPIOA, (0 | (1<<15)));
	// PORTA
	 RCC_AHB1PeriphClockCmd  (	RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
	 						  | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE ,  
  								ENABLE) ;

	//out pp
	GPIO_Write(GPIOA, 0 | (1<<4));
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2  | GPIO_Pin_3 
									| GPIO_Pin_4 | GPIO_Pin_8 | GPIO_Pin_9
									| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
									
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// in float
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	// PORTB
	GPIO_Write(GPIOB, 0 | (1<<12));
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | 
   									GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

// 	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7 
// 									| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// PORTC
		//out
	GPIO_Write(GPIOC, 0 );
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_1| GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 |
   									GPIO_Pin_7 | GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		// in
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_2  | GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
		//an in
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

 	// PORTD
 		// out
 	GPIO_Write(GPIOD, 0 | (1<<13));
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_13  	;
									//GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
									//GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
									//GPIO_Pin_10 | GPIO_Pin_11 |
									//GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15  	;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
// 		// in
// 	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_8 | GPIO_Pin_9 ;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure);

// 	// PORTE
// 		// out
// 	GPIO_Write(GPIOE, 0 | (1<<8));
// 	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
// 									GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6   	;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);
// 		// in
// 	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
// 									GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
// 									GPIO_Pin_15;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);

   
   //GPIO_PinAFConfig  (GPIO_Remap_SWJ_JTAGDisable, ENABLE );
   //GPIO_PinRemapConfig  (GPIO_Remap_SPI1,  ENABLE);

}

//----------------------------------------------------------------------------
void NVIC_cfg(void)
{

	NVIC_InitTypeDef nvic_InitStruct;

	// UART1 Rx
	nvic_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);

	nvic_InitStruct.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);
 
	nvic_InitStruct.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);

	// UART4 Rx
	nvic_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);

	// UART4 Rx
	nvic_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);

	//-- UART3 Rx
	nvic_InitStruct.NVIC_IRQChannel = DMA1_Stream1_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);
 
	nvic_InitStruct.NVIC_IRQChannel = DMA1_Stream3_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);
 
	//-- UART3 Rx
	nvic_InitStruct.NVIC_IRQChannel = DMA1_Stream5_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);
 
	nvic_InitStruct.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelSubPriority = 6;
	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init  ( &nvic_InitStruct);

 
   	/* Enable the RTC Interrupt */
//	nvic_InitStruct.NVIC_IRQChannel = RTC_IRQn;
//	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//	nvic_InitStruct.NVIC_IRQChannelSubPriority = 0;
//	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&nvic_InitStruct);


}

//----------------------------------------------------------------------------
void DMA_cfg(void)
{
	
//	DMA_InitTypeDef DMA_InitStructure;
//
// 
//	// ADC DMA1 channel1 configuration ----------------------------------------------*/
////	#define ADC1_DR_Base    ((uint32_t)0x4001244C)
//  
//	DMA_DeInit(DMA1_Channel1);
//	DMA_StructInit(&DMA_InitStructure);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Base;
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&resultADC[0];
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = NUM_ADC_SAMPLE;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//	/* Enable DMA1 Channel1 */
//	DMA_Cmd(DMA1_Channel1, ENABLE);
// 

}

//----------------------------------------------------------------------------
void SysTick_cfg(void)
{
	//#define SystemFrequency 24000000
	RCC_ClocksTypeDef RCC_Clocks;
	//NVIC_InitTypeDef nvic_InitStruct;

	
	RCC_GetClocksFreq(&RCC_Clocks);
	//SysTick_CLKSourceConfig  (SysTick_CLKSource_HCLK_Div8);
	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config((RCC_Clocks.HCLK_Frequency )/ 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
//	NVIC_SetPriority(SysTick_IRQn, 0x1);
// 	nvic_InitStruct.NVIC_IRQChannel = SysTick_IRQn;
// 	nvic_InitStruct.NVIC_IRQChannelPreemptionPriority = 5;
// 	nvic_InitStruct.NVIC_IRQChannelSubPriority = 5;
// 	nvic_InitStruct.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init  ( &nvic_InitStruct);
	
}

//----------------------------------------------------------------------------
void UART3_cfg(void)
{
   USART_InitTypeDef USART_InitStructure;

   USART_InitStructure.USART_BaudRate   = 9600;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits   = USART_StopBits_1;
   USART_InitStructure.USART_Parity     = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;

   USART_Init(USART3, &USART_InitStructure);

   USART_DMACmd(USART3, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);
   
   
}

//----------------------------------------------------------------------------

void SPI_TC_Init(void)
{
	
	
}

unsigned int RTC_cfg(void)
{
	unsigned int ret;
	RTC_DateTypeDef   RTC_DateStruct;
	RTC_TimeTypeDef   RTC_TimeStruct;
	
	ret = 0;

	if (RTC_ReadBackupRegister(RTC_BKP_DR1) != 0xA5A5)
	{
	  	ret = 1;
		
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);
	 
		/* Reset Backup Domain */
		RTC_DeInit();
	 
		/* Enable LSE */
		RCC_LSEConfig(RCC_LSE_ON);
		
		/* Wait till LSE is ready */
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
		{}
	 
		/* Select LSE as RTC Clock Source */
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	 
		/* Enable RTC Clock */
		RCC_RTCCLKCmd(ENABLE);
	 
		/* Wait for RTC registers synchronization */
		RTC_WaitForSynchro();
	 
		/* Adjust time */
		RTC_DateStruct.RTC_Year = 13;
		RTC_DateStruct.RTC_Month = 05;
		RTC_DateStruct.RTC_Date = 29;
		RTC_DateStruct.RTC_WeekDay = 3;
		RTC_TimeStruct.RTC_Hours = 11;
		RTC_TimeStruct.RTC_Minutes = 0;	
		RTC_TimeStruct.RTC_Seconds = 0;
		RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);	
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
			
		RTC_WriteBackupRegister(RTC_BKP_DR1, 0xA5A5);
	}
	else
	{
	
		/* Allow access to BKP Domain */
		PWR_BackupAccessCmd(ENABLE);

		/* Wait for RTC registers synchronization */
		RTC_WaitForSynchro();
		while (RTC_GetFlagStatus(RTC_FLAG_RSF) == RESET);
		
	}
	return ret;
}
//----------------------------------------------------------------------------
void iwdg_init(void)
{
	/* IWDG timeout equal to 280 ms (the timeout may varies due to LSI frequency
     dispersion) */
  	/* Enable write access to IWDG_PR and IWDG_RLR registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	/* IWDG counter clock: 40KHz(LSI) / 256 = 156.25 Hz */
	IWDG_SetPrescaler(IWDG_Prescaler_256);

	/* Set counter reload value to 0xFFF */
	IWDG_SetReload(0x0FFF);

	/* Reload IWDG counter */
	IWDG_ReloadCounter();

	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();
}	

// void Beeper_Init(void)
// {
// 	// PC13 ind v2
// 	// PE6	ind v2.1
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
// 	TIM_OCInitTypeDef  TIM_OCInitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
// 	uint16_t PrescalerValue = 0;




// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

// 	// GPIOC Configuration: TIM9 CH2 (PE6)
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
// 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
// 	
// 	GPIO_ResetBits  ( GPIOC, GPIO_Pin_13);
// 	// Connect TIM9 pins to A2 
// 	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9);
// 	
// 	
// 	
// 	/* Enable the TIM9 global Interrupt */
// 	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
// 	NVIC_Init(&NVIC_InitStructure);

// 	/* Time base configuration */
// 	PrescalerValue = (uint16_t) (SystemCoreClock / (2*1000000)) - 1;
// 	TIM_TimeBaseStructure.TIM_Period = 1000;
// 	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
// 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
// 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
// 	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

// 	/* Output Compare Toggle Mode configuration: Channel2 */
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
// 	TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period/2;
// 	
// 	TIM_OC2Init(TIM9, &TIM_OCInitStructure);
// 	
// 	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Disable);

// 	/* TIM enable counter */
// 	TIM_Cmd(TIM9, ENABLE);
// 	
// 	/* TIM IT enable */
// 	
// 	TIM_ITConfig(TIM9, TIM_IT_Update | TIM_IT_CC2, DISABLE);
// 	


// 	


// }
