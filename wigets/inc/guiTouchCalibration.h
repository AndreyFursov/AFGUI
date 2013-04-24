/*
 * guiTouchCalibration.h
 *
 *  Created on: 23.04.2013
 *      Author: Andrey Fursov
 */

#ifndef GUITOUCHCALIBRATION_H_
#define GUITOUCHCALIBRATION_H_

extern uint16_t touchCalibration(void);
extern void touchSaveCoef(int16_t _ax, int16_t _bx, int16_t _ay, int16_t _by);
extern void touchLoadCoef(void);

#endif /* GUITOUCHCALIBRATION_H_ */
