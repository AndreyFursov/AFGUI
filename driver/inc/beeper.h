/*
 * beeper.h
 *
 *  Created on: 25.03.2013
 *      Author: Andrey Fursov
 */

#ifndef BEEPER_H_
#define BEEPER_H_

typedef struct
{
	uint32_t ShortDownCounter;
	uint32_t intSoundCounter;
	uint32_t intPauseCounter;

	unsigned intSoundOn		: 1;
	unsigned shortSoundOn	: 1;
	unsigned intSoundEnable	: 1;
} BEEP;

extern void Beeper_Init(void);
extern void Beeper_ShortOn(uint32_t time_ms);
extern void Beeper_Off(void);
extern void Beeper_InterruptOn(void);




#endif /* BEEPER_H_ */
