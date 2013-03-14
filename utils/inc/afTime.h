/*
 * afTime.h
 *
 *  Created on: 23.02.2013
 *      Author: Andrey Fursov
 */

#ifndef AFTIME_H_
#define AFTIME_H_

typedef struct
{
	uint8_t  Day ;
	uint8_t  Month ;
	uint16_t  Year ;

	uint8_t  WeekDay ;

	uint8_t  Hour ;
	uint8_t  Minute ;
	uint8_t  Second ;

} DATETIME;

extern void UnixTimeToDateTime(uint32_t utime, DATETIME *DateTime);
extern uint32_t DateTimeToUnixTime(DATETIME *DateTime);
extern void SetDayOfWeek(DATETIME *DateTime);
extern uint16_t DateTimeToString(DATETIME *DateTime, char *str, uint16_t len);
#endif /* AFTIME_H_ */
