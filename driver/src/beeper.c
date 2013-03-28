/*
 * beeper.c
 *
 *  Created on: 25.03.2013
 *      Author: Andrey Fursov
 */
#include "stm32f2xx_conf.h"
#include "beeper.h"
#ifdef TNKERNEL_PORT_CORTEXM3
#include "tn.h"
#endif


BEEP beep =
{
	100,	// uint32_t ShortDownCounter;
	2000,	// uint32_t intSoundCounter;
	2000,	// uint32_t intPauseCounter;

	0,		// unsigned intSoundOn		: 1;
	1,		// unsigned shortSoundOn	: 1;
	0		// unsigned intSoundEnable	: 1;

};

void Beeper_Init(void)
{
	// PC13 ind v2
	// PE6	ind v2.1
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint16_t PrescalerValue = 0;




	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

//	// GPIOC Configuration: TIM9 CH2 (PE6)
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9);

	GPIO_ResetBits  ( GPIOC, GPIO_Pin_13);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits  ( GPIOC, GPIO_Pin_13);
	// Connect TIM9 pins to A2



	/* Enable the TIM9 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Time base configuration */
	PrescalerValue = (uint16_t) (SystemCoreClock / (2*1000000)) - 1;
	TIM_TimeBaseStructure.TIM_Period = 500;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	/* Output Compare Toggle Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_TimeBaseStructure.TIM_Period/2;

	TIM_OC2Init(TIM9, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Disable);

	/* TIM enable counter */
	TIM_Cmd(TIM9, ENABLE);

	/* TIM IT enable */

	//TIM_ITConfig(TIM9, TIM_IT_Update | TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
}

void TIM1_BRK_TIM9_IRQHandler(void)  //-- UART2 Tx
{
	//	tn_event_iset(&event_all_uart, EVENT_UART3_TX_END);
	//-- Clear int flag
	/* TIM9_CH2 toggling with frequency = 366.2 Hz */
	if (TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
	}

	if (beep.intSoundOn || beep.shortSoundOn)
	{
		GPIO_ToggleBits  ( GPIOC, GPIO_Pin_13);
	}
	else
	{
		GPIO_ResetBits  ( GPIOC, GPIO_Pin_13);
	}

	if (beep.shortSoundOn)
	{
		if (beep.ShortDownCounter--)
		{

		}
		else
		{
			beep.shortSoundOn = 0;
		}
	}

	if (beep.intSoundEnable)
	{
		if (beep.intSoundCounter)
		{
			beep.intSoundCounter--;
			beep.intSoundOn = 1;
			beep.intPauseCounter = 2000;
		}
		else
		{
			if (beep.intPauseCounter)
			{
				beep.intPauseCounter--;
				beep.intSoundOn = 0;
			}
			else
			{
				beep.intSoundCounter = 2000;
			}
		}

	}
	else
	{
		beep.intSoundOn = 0;
	}




#ifdef TNKERNEL_PORT_CORTEXM3
	tn_int_exit();
#endif
}



void Beeper_ShortOn(uint32_t time_ms)
{
	beep.ShortDownCounter = time_ms*4;
	beep.shortSoundOn = 1;
}

void Beeper_Off(void)
{
	beep.intSoundCounter = 2000;
	beep.intPauseCounter = 2000;
	beep.intSoundEnable = 0;
}

void Beeper_InterruptOn(void)
{
	if (beep.intSoundEnable == 0)
	{
		beep.intSoundCounter = 2000;
		beep.intPauseCounter = 2000;
	}
	beep.intSoundEnable = 1;
}
