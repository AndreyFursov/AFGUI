/*----------------------------------------------------------------------------
 * Name:    HAL_Calender.c
 * Purpose: Date/Time support.
 *                          
 * Version: V1.00
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/
//  
#include "stm32f2xx_conf.h"
#include "HAL_Calender.h"





static const char*	wdays_us[] = {"??", "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
static const char*	wdays_de[] = {"??", "Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};
static const uint8_t   mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

//------------------------------------------------------------------------------
//
//	Built around time.h from RTL (\RV31 or other subdir with Real View Library)
//
//  The time is a 32-bit counter of seconds: 0 is 01-01-1970 00:00:00.
//	As the counter the RTC counter or a software driven counter can be
//	used. To access the counter two functions:
//
// 		uint32_t GetElapsed(void);
//		uint32_t SetElapsed(uint32_t e);
//
//	should be implemented elsewhere IN THE USER CODE.
//
//------------------------------------------------------------------------------

uint32_t IncElapsed(void)
{
	return SetElapsed(GetElapsed() + 1);
}
//------------------------------------------------------------------------------
uint8_t	IsLeapYear(uint16_t y)
{
	return (y%4 == 0 && y%100 != 0) || (y%400 == 0);
}

//------------------------------------------------------------------------------

uint32_t	Time2Count(uint8_t  h,	
			       	   uint8_t  m, 
				       uint8_t  s)
{
/*
	TTimeRec  t;
	uint8_t	  dr = sizeof(TTimeRec)/sizeof(uint8_t),
			  *b = (uint8_t*)&t;

	while (dr--) *b++ = 0;
	t.tm_hour = (h < 24 ? h:0); 
	t.tm_min  = (m < 60 ? m:0); 
	t.tm_sec  = (s < 60 ? s:0);	

	return mktime(&t);
*/
	h = (h < 24 ? h:0); 
	m = (m < 60 ? m:0); 
	s = (s < 60 ? s:0);	
	return (uint32_t)60*(60*h + m) + s;
}
//------------------------------------------------------------------------------

uint32_t	Count2Time(uint32_t c,
				  	   uint8_t *h, 
				 	   uint8_t *m, 
					   uint8_t *s)
{
	TTimeRec *t = localtime((const time_t*)&c);		// time.h from RTL V4.12

	*h = (*t).tm_hour;
	*m = (*t).tm_min;
	*s = (*t).tm_sec;	

	return c;
}
//------------------------------------------------------------------------------

uint32_t	GetTime(uint8_t *h, 
					uint8_t *m, 
					uint8_t *s)
{
	return Count2Time(GetElapsed(), h, m, s);
}

//------------------------------------------------------------------------------

uint8_t	GetWeekDayU(void)	// US: 0=Sun, 6=Sat
{
	uint32_t  e = GetElapsed();
	TTimeRec *t = localtime((const time_t*)&e);	
	return	(*t).tm_wday;
}
//------------------------------------------------------------------------------

uint8_t	GetWeekDayE(void)	// EU: 0=Mo, 6=So 
{
	uint8_t	  w = GetWeekDayU();
	return	 (w == 0 ? 6: w-1);
}



//------------------------------------------------------------------------------

static __inline uint8_t _AdjustWeekDay(uint8_t wd)
{
	if (wd > 6) wd = 0; else wd++;
	return wd;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

const char*	GetWeekDayString_US(uint8_t wd)	
{
	return	wdays_us[_AdjustWeekDay(wd)];
}

//------------------------------------------------------------------------------

const char*	GetWeekDayString_DE(uint8_t wd)	
{
	return	wdays_de[_AdjustWeekDay(wd)];
}
//------------------------------------------------------------------------------

uint32_t	Date2Count(uint16_t y,	// like 2010
				       uint8_t  m, 	// 1..12
					   uint8_t  d) 	// 1..31
{
	TTimeRec  t;
	uint8_t	  dr = sizeof(TTimeRec)/sizeof(uint8_t),
			  *b = (uint8_t*)&t;

	while (dr--) *b++ = 0;
	t.tm_year = y = (y < 1900 ? 0 : y -1900); 
	t.tm_mon  = m = (m < 1 ? 0 : (m > 12 ? 11 : m-1));	// [0..11]

	// validate the day range

	dr = mdays[m]; 	// days in the month=[0..11] 
	if (m == 1 /*Feb*/ && IsLeapYear(y +1900)) dr++; // leap year

	// set the day

	t.tm_mday = (d < 1 ? 1 : (d > dr ? dr : d));	

	return mktime(&t);
}
//------------------------------------------------------------------------------

uint32_t	Count2Date(uint32_t  c,
					   uint16_t *y,	// like 2010
				       uint8_t  *m, // 1..12
					   uint8_t  *d) // 1..31
{
	TTimeRec *t = localtime((const time_t*)&c);	

	*y = (*t).tm_year + 1900; 
	*m = (*t).tm_mon  + 1;
	*d = (*t).tm_mday;

	return c;
}
//------------------------------------------------------------------------------

uint32_t	GetDate(uint16_t *y,// like 2010
					uint8_t  *m,// 1..12
					uint8_t  *d)// 1..31
{
	return Count2Date(GetElapsed(), y, m, d);
}

//------------------------------------------------------------------------------

void 	SetTime(uint8_t h, 
				uint8_t m, 
				uint8_t s)
{
	uint32_t  e = GetElapsed();
	TTimeRec *t = localtime((const time_t*)&e);	

	(*t).tm_hour = (h < 24 ? h:0); 
	(*t).tm_min	 = (m < 60 ? m:0); 
	(*t).tm_sec	 = (s < 60 ? s:0);	

	SetElapsed(mktime(t));
}

//------------------------------------------------------------------------------

void 	SetDate(uint16_t y,	// like 2010
				uint8_t  m, // 1..12
				uint8_t  d) // 1..31
{
	uint8_t	  dr;
	uint32_t  e = GetElapsed();
	TTimeRec *t = localtime((const time_t*)&e);	

	(*t).tm_year = y = (y < 1900 ? 0 : y -1900); 
	(*t).tm_mon  = m = (m < 1 ? 0 : (m > 12 ? 11 : m-1));	// [0..11]

	// validate the day range

	dr = mdays[m]; 	// days in the month=[0..11] 
	if (m == 1 /*Feb*/ && IsLeapYear(y +1900)) dr++; // leap year

	// set the day

	(*t).tm_mday = (d < 1 ? 1 : (d > dr ? dr : d));	

	SetElapsed(mktime(t));
}
//------------------------------------------------------------------------------
uint8_t	GetWeekDayR(uint32_t _e)	// EU: 0=Mo, 6=So 
{
	uint32_t e;
	TTimeRec * t;
	uint8_t	  w;
	
	e = _e;
	
	t = localtime((const time_t*)&e);
	w = t->tm_wday;
	return	 (w == 0 ? 6: w-1);
}

uint32_t RTC_GetCounter(void)
{
	RTC_DateTypeDef   RTC_DateStruct;
	RTC_TimeTypeDef   RTC_TimeStruct;
	uint32_t DateTime;
	
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
	DateTime = Date2Count((uint16_t)RTC_DateStruct.RTC_Year+2000, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date);
	DateTime += Time2Count(RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds);
	
	
	return DateTime;
};
uint32_t RTC_SetCounter(uint32_t e)
{
	uint16_t yy;
	uint32_t c;
	 
	RTC_DateTypeDef   RTC_DateStruct;
	RTC_TimeTypeDef   RTC_TimeStruct;
	 
					
	c = Count2Date(e,
					   &yy,	// like 2010
				       &RTC_DateStruct.RTC_Month, // 1..12
					   &RTC_DateStruct.RTC_Date); // 1..31			
	
	if (yy >= 2000) RTC_DateStruct.RTC_Year = (uint8_t)(yy - 2000);			   
		else 		RTC_DateStruct.RTC_Year = (uint8_t)yy;
	Count2Time(c,	&RTC_TimeStruct.RTC_Hours, 
				 	&RTC_TimeStruct.RTC_Minutes, 
					&RTC_TimeStruct.RTC_Seconds);
	RTC_DateStruct.RTC_WeekDay = GetWeekDayR(e);
	
	RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
	
					   
	 
	
	
	return 0;
};
