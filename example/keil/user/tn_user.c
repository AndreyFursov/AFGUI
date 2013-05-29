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

//#include "stm32f2xx.h"
//#include "stm32f2xx_conf.h"
//#include "types.h"
#include "globals.h"
#include "tn.h"
#include "hw_config.h"
//#include "utils.h"

//---- Local functions prototypes
SYSTEM_TIMER curTime, startTime;



static void tn_calc_performance(void);
//static volatile int time1ms = 0;
SYSTEM_TIMER timer1ms, timer1s;
uint16_t counter1000ms;

SYSTEM_TIMER getSystemTimer1ms(void)
{
	return(timer1ms);
}	
SYSTEM_TIMER getSystemTimer1s(void)
{
	return(timer1s);
}	

void setSystemTimer1s(SYSTEM_TIMER timer)
{
	timer1s = timer;
}	


void  delay_ms(SYSTEM_TIMER _time)
{
	
// 	startTime = getSystemTimer1ms();
// 	while(curTime - startTime < _time)
// 	{
// 		curTime = getSystemTimer1ms();
// 	};
	
	_time *= 50000;
	while (_time--);
		
}



//----------------------------------------------------------------------------
// прерывание от 1ms - системный тик
void SysTick_Handler(void)
{
	tn_tick_int_processing();
	tn_calc_performance();
	timer1ms++;
	if (counter1000ms++ >= 999)
	{
		counter1000ms = 0;
		timer1s++;
	}
	tn_int_exit();
}

//----------------------------------------------------------------------------
void DMA1_Stream1_IRQHandler(void)  //-- UART3 Rx
{
  //--- Reload DMA - urgent
 	DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1); 
	#ifdef USE_USART3
	DMA_Cmd(DMA1_Stream1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Stream1, USART3_RX_BUF_SIZE);
	DMA_Cmd(DMA1_Stream1, ENABLE);
	#endif
	tn_int_exit();
}
//----------------------------------------------------------------------------
void DMA1_Stream3_IRQHandler (void)  //-- UART3 Tx
{
	//-- Clear int flag
	DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3); 	

	tn_int_exit();
}


//----------------------------------------------------------------------------
void DMA1_Stream5_IRQHandler(void)  //-- UART2 Rx
{
  //--- Reload DMA - urgent
 	DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5); 
	#ifdef USE_USART2
	DMA_Cmd(DMA1_Stream5, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Stream5, USART2_RX_BUF_SIZE);
	DMA_Cmd(DMA1_Stream5, ENABLE);
	#endif
	tn_int_exit();
}
//----------------------------------------------------------------------------
void DMA1_Stream6_IRQHandler(void)  //-- UART2 Tx
{
	//	tn_event_iset(&event_all_uart, EVENT_UART3_TX_END);
	//-- Clear int flag
	DMA_ClearFlag(DMA1_Stream6, DMA_FLAG_TCIF6); 	
	
	
	tn_int_exit();
}

//----------------------------------------------------------------------------
void DMA2_Stream5_IRQHandler(void)  //-- UART1 Rx
{
  //--- Reload DMA - urgent
 	DMA_ClearFlag(DMA2_Stream5, DMA_FLAG_TCIF5); 
	#ifdef USE_USART1
	DMA_Cmd(DMA2_Stream5, DISABLE);
	DMA_SetCurrDataCounter(DMA2_Stream5, USART1_RX_BUF_SIZE);
	DMA_Cmd(DMA2_Stream5, ENABLE);
	#endif
	tn_int_exit();
}
//----------------------------------------------------------------------------
void DMA2_Stream7_IRQHandler(void)  //-- UART1 Tx
{
	//	tn_event_iset(&event_all_uart, EVENT_UART3_TX_END);
	//-- Clear int flag
	DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF6); 	
	
	
	tn_int_exit();
}

void USART3_IRQHandler(void)  //-- UART3 Tx Complite
{
	if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_TC);
		#ifdef USE_USART1_RS485
		USART1_DE_485_OFF();
		USART1->CR1 |= USART_Mode_Rx;
		#endif
	}

	tn_int_exit();
}

void USART2_IRQHandler(void)  //-- UART2 Tx Complite
{
	if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_TC);
		#ifdef USE_USART2_RS485
		USART2_DE_485_OFF();
		USART2->CR1 |= USART_Mode_Rx;
		#endif
	}
	tn_int_exit();
}

void USART1_IRQHandler(void)  //-- UART3 Tx Complite
{
	if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_TC);
		#ifdef USE_USART3_RS485
		USART3_DE_485_OFF();
		USART3->CR1 |= USART_Mode_Rx;
		#endif
	}

	tn_int_exit();
}




//void RTC_IRQHandler(void)
//{
//	volatile unsigned int counter;
//	static volatile SYSTEM_TIMER lastTime, deltaTime;
//	
//	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
//	{
//		/* Clear the RTC Second interrupt */
//		RTC_ClearITPendingBit(RTC_IT_SEC);
//		deltaTime = getSystemTimer1ms() - lastTime;
//		lastTime = getSystemTimer1ms();
//		counter = RTC_GetCounter();
//		/* Toggle LED1 */
//		//STM_EVAL_LEDToggle(LED1);
//	
//		/* Enable time update */
//		//TimeDisplay = 1;
//	
//		/* Wait until last write operation on RTC registers has finished */
//		//RTC_WaitForLastTask();
//     
//	}
//	tn_int_exit();
//}


//----------------------------------------------------------------------------
static void tn_calc_performance(void)
{
   static int cnt = 0;

   cnt++;
   if(cnt == 1000)  //-- 1 s
   {
      cnt = 0;

      tn_curr_performance = tn_idle_count;
      tn_idle_count = 0;

      //tn_sem_isignal(&semMeasPrf);  //-- To send result to the host
   }
   tn_int_exit();
}

//----------------------------------------------------------------------------
//  Processor specific routines for Cortex-M3
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void tn_cpu_int_enable()
{
   tn_arm_enable_interrupts();
}

//----------------------------------------------------------------------------
int tn_inside_int(void)
{
   if(rNVIC_ICSR & VECTACTIVE)
      return 1;
   return 0;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------





