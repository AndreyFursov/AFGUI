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

//#include <string.h>
//#include "stm32f10x_lib_cfg.h"
#include "stm32f10x.h"
#include "tn.h"
#include "tn_utils.h"
#include "types.h"
#include "globals.h"
#include "utils.h"

//----------------------------------------------------------------------------
void send_uart2(unsigned char * _buf, int _len)
{
//	unsigned int elem;
//	int rc;
//	elem = (_len << 20) | (((unsigned int)_buf) & 0x000FFFFF);
//	rc = tn_queue_send_polling(&queueTxUART2, (void *)elem);
//	if (rc == TERR_NO_ERR)
//		tn_event_set(&event_all_uart, EVENT_UART2_TX_QUEUE);
	
}

void  pw3_rx_ready(void)
{
	// обработка сообщения
	DMA_Cmd(DMA1_Channel6, DISABLE);
	DMA_SetCurrDataCounter (DMA1_Channel6,  UART2_RX_BUF_SIZE); 
	DMA_Cmd(DMA1_Channel6, ENABLE);
};

void send_pw3(unsigned char * _buf, int _len)
{
	//pw3_rx_ready();
//	rDMA1_CCR7 &= ~1;
//	rDMA1_CMAR7  = (unsigned int)_buf;
//	rDMA1_CNDTR7 = _len;
//	rDMA1_CCR7 |= 1;

	DMA_Cmd(DMA1_Channel6, DISABLE);
	DMA_SetCurrDataCounter (DMA1_Channel6,  _len); 
	DMA_Cmd(DMA1_Channel6, ENABLE);
	
	
	
	
}

void send_uart3(unsigned char * _buf, int _len)
{
	//USART3->CR1 &= ~USART_Mode_Rx;
//	rDMA1_CCR2 &= ~1;
//	rDMA1_CMAR2  = (unsigned int)_buf;
//	rDMA1_CNDTR2 = _len;
//	rDMA1_CCR2 |= 1;

	DMA_Cmd(DMA1_Channel2, DISABLE);
	DMA_SetCurrDataCounter (DMA1_Channel6,  _len); 
	DMA_Cmd(DMA1_Channel2, ENABLE);
}

//
//void send_data_uart3(unsigned char * buf, int size)
//{
//   int rc;
//   unsigned int elem;
//   unsigned char * tx_buf;
//   int tx_bytes;
//   int nbytes = size;
//   unsigned char * ptr = buf;
//
//   if(ptr == NULL)
//      return;
//
//   tn_sem_acquire(&semTxUART3, TN_WAIT_INFINITE);
//
//   while(nbytes)
//   {
//      if(nbytes > UART3_TX_PACKET_SIZE)
//         tx_bytes = UART3_TX_PACKET_SIZE;
//      else
//         tx_bytes = nbytes;
//
//      rc = tn_fmem_get(&TxUART3MemPool, (void **) &tx_buf, TN_WAIT_INFINITE);
//      if(rc == TERR_NO_ERR)
//      {
//         memcpy(tx_buf, ptr, tx_bytes);
//
//         //--- Pack len & addr
//         elem = (tx_bytes << 24) | (((unsigned int)tx_buf) & 0x00FFFFFF);
//
//         tn_queue_send(&queueTxUART3, (void *)elem, TN_WAIT_INFINITE);
//      }
//
//      ptr    += tx_bytes;
//      nbytes -= tx_bytes;
//   }
//
//   tn_sem_signal(&semTxUART3);
//}
//
//
//
//void send_data_uart2(unsigned char * buf, int size)
//{
//   int rc;
//   unsigned int elem;
//   unsigned char * tx_buf;
//   int tx_bytes;
//   int nbytes = size;
//   unsigned char * ptr = buf;
//
//   if(ptr == NULL)
//      return;
//
//   tn_sem_acquire(&semTxUART2, TN_WAIT_INFINITE);
//
//   while(nbytes)
//   {
//      if(nbytes > UART2_TX_PACKET_SIZE)
//         tx_bytes = UART2_TX_PACKET_SIZE;
//      else
//         tx_bytes = nbytes;
//
//      rc = tn_fmem_get(&TxUART2MemPool, (void **) &tx_buf, TN_WAIT_INFINITE);
//      if(rc == TERR_NO_ERR)
//      {
//         memcpy(tx_buf, ptr, tx_bytes);
//
//         //--- Pack len & addr
//         elem = (tx_bytes << 24) | (((unsigned int)tx_buf) & 0x00FFFFFF);
//
//         tn_queue_send(&queueTxUART2, (void *)elem, TN_WAIT_INFINITE);
//      }
//
//      ptr    += tx_bytes;
//      nbytes -= tx_bytes;
//   }
//
//   tn_sem_signal(&semTxUART2);
//}
////----------------------------------------------------------------------------
//void send_data_uart3_str(unsigned char * buf)
//{
//   if(buf == NULL || buf[0] == 0)
//      return;
//   send_data_uart3(buf, strlen((char*)buf));
//}
//
//void send_data_uart2_str(unsigned char * buf)
//{
//   if(buf == NULL || buf[0] == 0)
//      return;
//   send_data_uart2(buf, strlen((char*)buf));
//}
//
//
////----------------------------------------------------------------------------
//int uart_rx_drv(unsigned char * buf, unsigned char in_byte, int max_buf_size)
//{
//   static int pos = 0;
//   int tmp;
//
//   if(in_byte == '\r' || in_byte == '\n') //-- We ignore empty str here
//   {
//      tmp = pos;
//      pos = 0;
//      return tmp;
//   }
//   else
//   {
//      buf[pos] = in_byte;
//      pos++;
//      if(pos >= max_buf_size) //-- Too much symbols
//      {
//         tmp = pos;
//         pos = 0;
//         return tmp;
//      }
//   }
//   return 0;
//}
//
////----------------------------------------------------------------------------
//int uart_rx_drv_ex(UARTDRV * ud, unsigned char in_byte)
//{
//   int tmp;
//
//   if(in_byte == '\r' || in_byte == '\n') //-- We ignore empty str here
//   {
//      tmp = ud->pos;
//      ud->pos = 0;
//      return tmp;
//   }
//   else
//   {
//      ud->buf[ud->pos] = in_byte;
//      ud->pos++;
//      if(ud->pos >= ud->max_buf_size) //-- Too much symbols
//      {
//         tmp = ud->pos;
//         ud->pos = 0;
//         return tmp;
//      }
//   }
//   return 0;
//}
//
////----------------------------------------------------------------------------
//void read_dma_uart(DMAINFO * di)
//{
//   register int nbytes;
//   register int count;
//
//   count =  *(di->dma_cnt);
//
//   nbytes = di->prev - count;
//
//   if(nbytes && count) //-- counts == 0 -> read it inside DMA int
//   {
//
//      tn_queue_isend_polling(di->rx_queue,
//         (void*) (((di->buf_size - di->prev) << 16) | //-- chunk start in buf(offset)
//                                           nbytes));
//      di->prev = count;
//   }
//}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
