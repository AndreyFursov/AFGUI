#ifndef _I2C_EEPROM_H_
#define _I2C_EEPROM_H_


#define sEE_WRITE_ADDRESS1        0x50
#define sEE_READ_ADDRESS1         0x50

#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1
#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                   
#define sEE_I2C_SCL_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sEE_I2C_SDA_PIN                  GPIO_Pin_7               
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                   
#define sEE_I2C_SDA_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sEE_AT24C02
 
//#define sEE_I2C_DMA                      DMA1   
//#define sEE_I2C_DMA_CHANNEL_TX           DMA1_Channel4
//#define sEE_I2C_DMA_CHANNEL_RX           DMA1_Channel5 
//#define sEE_I2C_DMA_FLAG_TX_TC           DMA1_IT_TC4   
//#define sEE_I2C_DMA_FLAG_TX_GL           DMA1_IT_GL4 
//#define sEE_I2C_DMA_FLAG_RX_TC           DMA1_IT_TC5 
//#define sEE_I2C_DMA_FLAG_RX_GL           DMA1_IT_GL5    
//#define sEE_I2C_DMA_CLK                  RCC_AHBPeriph_DMA1
//#define sEE_I2C_DR_Address               ((uint32_t)0x40005810)
//#define sEE_USE_DMA
    
#define sEE_I2C_DMA_TX_IRQn              DMA1_Channel4_IRQn
#define sEE_I2C_DMA_RX_IRQn              DMA1_Channel5_IRQn
#define sEE_I2C_DMA_TX_IRQHandler        DMA1_Channel4_IRQHandler
#define sEE_I2C_DMA_RX_IRQHandler        DMA1_Channel5_IRQHandler  
#define sEE_I2C_DMA_PREPRIO		0
#define sEE_I2C_DMA_SUBPRIO		0
 
#define I2C_SLAVE_ADDRESS7		0xA0
#define sEE_DIRECTION_TX		0
#define sEE_DIRECTION_RX		1 
 
 /* Time constant for the delay caclulation allowing to have a millisecond 
    incrementing counter. This value should be equal to (System Clock / 1000).
    ie. if system clock = 24MHz then sEE_TIME_CONST should be 24. */
#define sEE_TIME_CONST          24 
 


//	sEE_Init();
//	sEE_WriteBuffer(Tx1_Buffer, sEE_WRITE_ADDRESS1, BUFFER_SIZE1);
//	sEE_ReadBuffer(Rx1_Buffer, sEE_READ_ADDRESS1, (uint16_t *)(&NumDataRead)); 


#endif
