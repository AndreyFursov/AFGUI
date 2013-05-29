/*----------------------------------------------------------------------------
 * Name:    HAL_Calender.h
 * Purpose: Date/Time support.
 *                          
 * Version: V1.00
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/
//                  
#include <stdint.h>		
#include <time.h>		// RV31

#ifndef	_DATETIME_
#define	_DATETIME_

#ifdef	LOCALE_US
	#define	GetWeekDay()		GetWeekDayU()
	#define	GetWeekDayString(a)	GetWeekDayString_US(a)
#else	// EU
	#define	GetWeekDay()		GetWeekDayE()
	#define	GetWeekDayString(a)	GetWeekDayString_DE(a)
#endif

typedef	struct tm TTimeRec;

#endif

//------------------------------------------------------------------------------
//
//	Built around time.h from RTL (\RV31 or other subdir with Real View Library)
//
//  The time is a 32-bit counter of seconds: 0 is 01-01-1970 00:00:00.
//	As the counter the RTC counter or a software driven counter can be
//	used. To access the counter two functions:
//
extern uint32_t GetElapsed(void);
extern uint32_t SetElapsed(uint32_t e);
extern uint32_t RTC_GetCounter(void);
extern uint32_t RTC_SetCounter(uint32_t e);

//
//	...should be implemented elsewhere IN THE USER CODE.
//
//  The simplest implementation looks like:
/*

volatile uint32_t	TimeCounter;

uint32_t GetElapsed(void)
{
	return	TimeCounter;
}

uint32_t SetElapsed(uint32_t e)
{
	return	TimeCounter = e;
}

void	SomeTimeoutEverySecond(void)
{
	IncElapsed();	
}
*/
//
extern uint32_t IncElapsed(void);
extern uint8_t	IsLeapYear(uint16_t y);

extern uint32_t	Count2Time(uint32_t c,
				  	   	   uint8_t *h, 
				 	       uint8_t *m, 
					       uint8_t *s);

extern uint32_t	Count2Date(uint32_t  c,
						   uint16_t *y,	
					       uint8_t  *m, 	// 1..12
						   uint8_t  *d); 	// 1..31

extern uint32_t	Time2Count(uint8_t  h,	
				       	   uint8_t  m, 
					       uint8_t  s);

extern uint32_t	Date2Count(uint16_t y,	// like 2010
				       	   uint8_t  m, 	// 1..12
					       uint8_t  d);	// 1..31

extern uint32_t	GetTime(uint8_t *h, 
						uint8_t *m, 
						uint8_t *s);

extern uint32_t	GetDate(uint16_t *y,	
						uint8_t  *m, 	// 1..12
						uint8_t  *d); 	// 1..31

extern uint8_t	GetWeekDayU(void);	// US: 0=Sun, 6=Sat
extern uint8_t	GetWeekDayE(void);	// EU: 0=Mo,  6=So

extern const char*	GetWeekDayString_US(uint8_t wd);	// string like "Su"...
extern const char*	GetWeekDayString_DE(uint8_t wd);	// string like "Mo"...
/* see also macros
#define	GetWeekDay()		
#define	GetWeekDayString(a)	
*/
extern void 	SetTime(uint8_t h, 	// 0..23
						uint8_t m, 	// 0..59
						uint8_t s);	// 0..59
extern void 	SetDate(uint16_t y,	// like 2010
						uint8_t  m, 	// 1..12
						uint8_t  d); 	// 1..31
//------------------------------------------------------------------------------
