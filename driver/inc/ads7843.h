/*
 * ads7843.h
 *
 *  Created on: 11.01.2013
 *      Author: Andrey Fursov
 */

#ifndef ADS7843_H_
#define ADS7843_H_

// SPI for TouchPanel (ADS7843)
#define GPIO_Pin_TP_SCK		GPIO_Pin_13
#define GPIO_Pin_TP_MISO	GPIO_Pin_14
#define GPIO_Pin_TP_MOSI	GPIO_Pin_15
#define GPIO_Pin_TP_CS		GPIO_Pin_12
#define PORT_TP_SPI			GPIOB
#define PORT_TP_CS			GPIOB
#define TP_Select()			GPIO_ResetBits(PORT_TP_CS, GPIO_Pin_TP_CS)
#define TP_Deselect()		GPIO_SetBits(PORT_TP_CS, GPIO_Pin_TP_CS)


extern void TP_SPI_Config(void);
extern void touchGetSense(int16_t * x, int16_t * y);

#endif /* ADS7843_H_ */
