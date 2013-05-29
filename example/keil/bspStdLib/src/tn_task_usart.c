#include "globals.h"
#include "uartdrv.h"

#define  TASK_UART_PRIORITY			10
// stack size
#define  TASK_UART_STK_SIZE			32	
// stack
unsigned int task_uart_stack[TASK_UART_STK_SIZE];
TN_TCB  task_uart;
void task_uart_func(void * par);


#ifdef USE_USART1
unsigned char  rxbufUSART1[USART1_RX_BUF_SIZE];
unsigned char  txbufUSART1[USART1_TX_BUF_SIZE];
USARTDRV usart1 = 
{
	USART1_DEF_SPEED,
	txbufUSART1,
	rxbufUSART1,
	USART1_TX_BUF_SIZE,
	USART1_RX_BUF_SIZE,
	0,
	0,
	0,
	0,
	0
};
#endif

#ifdef USE_USART2
unsigned char  rxbufUSART2[USART2_RX_BUF_SIZE];
unsigned char  txbufUSART2[USART2_TX_BUF_SIZE];
USARTDRV usart2 = 
{
	USART2_DEF_SPEED,
	txbufUSART2,
	rxbufUSART2,
	USART2_TX_BUF_SIZE,
	USART2_RX_BUF_SIZE,
	0,
	0,
	0,
	0,
	0
};
#endif

#ifdef USE_USART3
unsigned char  rxbufUSART3[USART3_RX_BUF_SIZE];
unsigned char  txbufUSART3[USART3_TX_BUF_SIZE];
USARTDRV usart3 = 
{
	USART3_DEF_SPEED,
	txbufUSART3,
	rxbufUSART3,
	USART3_TX_BUF_SIZE,
	USART3_RX_BUF_SIZE,
	0,
	0,
	0,
	0,
	0
};
#endif

void uart_task_create(void)
{
   task_uart.id_task = 0;
   tn_task_create(&task_uart,               //-- task TCB
                 task_uart_func,            //-- task function
                 TASK_UART_PRIORITY,        //-- task priority
                 &(task_uart_stack          //-- task stack first addr in memory
                    [TASK_UART_STK_SIZE-1]),
                 TASK_UART_STK_SIZE,        //-- task stack size (in int,not bytes)
                 NULL,                          //-- task function parameter
                 TN_TASK_START_ON_CREATION      //-- Creation option
                 );
	
}


// функция обработки UART IRPS
void task_uart_func(void * par)
{

	for(;;)
	{
		// передача UI
		
		#ifdef USE_USART1
		// обработка приема от UI
		usart1.uRxCountByte = USART1_RX_BUF_SIZE - DMA_GetCurrDataCounter(USART1_RX_DMACH);
		if (usart1.uRxCountByte)
		{
			if (usart1.uRxCountByte == 	usart1.uRxLastCountByte)
			{
				usart1.uRxLastCountByte = 0;
				// обработка запроса
				// обнуление счетчиков
 				//uartClrRx(&usart1, USART1_RX_DMACH);
				// освобождение семафора
				//tn_sem_signal(&semUartUI);
			}
			else
			{
				usart1.uRxLastCountByte = usart1.uRxCountByte;
			}
			
		}
		#endif

		#ifdef USE_USART2
		// обработка приема от UI
		usart2.uRxCountByte = USART2_RX_BUF_SIZE - DMA_GetCurrDataCounter(USART2_RX_DMACH);
		if (usart2.uRxCountByte)
		{
			if (usart2.uRxCountByte == 	usart2.uRxLastCountByte)
			{
				usart2.uRxLastCountByte = 0;
				// обработка запроса
				// обнуление счетчиков
				// освобождение семафора
			}
			else
			{
				usart2.uRxLastCountByte = usart2.uRxCountByte;
			}
			
		}
		#endif

		#ifdef USE_USART3
		// обработка приема от UI
		usart3.uRxCountByte = USART3_RX_BUF_SIZE - DMA_GetCurrDataCounter(USART3_RX_DMACH);
		if (usart3.uRxCountByte)
		{
			if (usart3.uRxCountByte == 	usart3.uRxLastCountByte)
			{
				usart3.uRxLastCountByte = 0;
				// обработка запроса
				// обнуление счетчиков
				// освобождение семафора
			}
			else
			{
				usart3.uRxLastCountByte = usart3.uRxCountByte;
			}
			
		}
		#endif
	tn_task_sleep(3);		
	}
}
