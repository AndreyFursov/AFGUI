/*
 * ads7843.h
 *
 *  Created on: 11.01.2013
 *      Author: Andrey Fursov
 */

#ifndef ADS7843_H_
#define ADS7843_H_



#define EE_ADR_COEF	0x10

extern void TP_SPI_Config(void);
extern void touchGetSense(int16_t * x, int16_t * y);
extern void touchSetCoef(int16_t ax, int16_t bx, int16_t ay, int16_t by);
extern uint16_t touchVerifyCoef(void);

extern int16_t touchGetX(void);
extern int16_t touchGetY(void);
extern uint16_t getTouchState(void);

#endif /* ADS7843_H_ */
