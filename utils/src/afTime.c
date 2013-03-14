/*
 * afTime.c
 *
 *  Created on: 23.02.2013
 *      Author: Andrey Fursov
 *      основа взята оттуда http://we.easyelectronics.ru/Soft/funkcii-kalendarya-i-vremeni-na-odnom-registre.html
 */
#include "gui.h"

#define JD0 2440588U


void UnixTimeToDateTime(uint32_t utime, DATETIME *DateTime)
{
	uint32_t ace;
	uint8_t b;
	uint8_t d;
	uint8_t m;

	ace=(utime/86400)+32044+JD0;
	b=(4*ace+3)/146097;
	ace=ace-((146097*b)/4);
	d=(4*ace+3)/1461;
	ace=ace-((1461*d)/4);
	m=(5*ace+2)/153;

	DateTime->Day=ace-((153*m+2)/5)+1;
	DateTime->Month=m+3-(12*(m/10));
	DateTime->Year=100*b+d-4800+(m/10);
	DateTime->Hour=(utime/3600)%24;
	DateTime->Minute=(utime/60)%60;
	DateTime->Second=(utime%60);
	SetDayOfWeek(DateTime);

}

uint32_t DateTimeToUnixTime(DATETIME *DateTime)
{
	uint8_t a;
	uint16_t y;
	uint8_t m;
	uint32_t JDN;

	// Вычисление необходимых коэффициентов
	a=(14-DateTime->Month)/12;
	y=DateTime->Year+4800-a;
	m=DateTime->Month+(12*a)-3;
	// Вычисляем значение текущего Юлианского дня
	JDN=DateTime->Day;
	JDN+=(153*m+2)/5;
	JDN+=365*y;
	JDN+=y/4;
	JDN+=-y/100;
	JDN+=y/400;
	JDN+=-32045U;
	JDN+=-JD0; // привязка к 01/01/1970
	JDN*=86400;     // переводим дни в секунды
	JDN+=(DateTime->Hour*3600); // и дополняем его секундами текущего дня
	JDN+=(DateTime->Minute*60);
	JDN+=(DateTime->Second);
	// итого имеем количество секунд с 00-00 01 янв 1970
	return JDN;
}

void SetDayOfWeek(DATETIME *DateTime)
{
	uint32_t a, y, m, w;
	a = (14 - DateTime->Month) / 12;
	y = DateTime->Year - a;
	m = DateTime->Month + 12 * a - 2;
	w = (7000 + (DateTime->Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;
	if (w == 0 ) w = 7;
	DateTime->WeekDay = w;
}

uint16_t DateTimeToString(DATETIME *DateTime, char *str, uint16_t len)
{
	uint16_t i, k;
	i = 0;
	if (i < len) str[i++] = (DateTime->Day/10) + 0x30;
	if (i < len) str[i++] = (DateTime->Day%10) + 0x30;
	if (i < len) str[i++] = '.';
	if (i < len) str[i++] = (DateTime->Month/10) + 0x30;
	if (i < len) str[i++] = (DateTime->Month%10) + 0x30;
	if (i < len) str[i++] = '.';
	if (i < len) str[i++] = (DateTime->Year/1000) + 0x30;
	k = DateTime->Year % 1000;
	if (i < len) str[i++] = k/100 + 0x30;
	k = k % 100;
	if (i < len) str[i++] = (k/10) + 0x30;
	if (i < len) str[i++] = (k%10) + 0x30;
	if (i < len) str[i++] = ' ';
	if (i < len) str[i++] = (DateTime->Hour/10) + 0x30;
	if (i < len) str[i++] = (DateTime->Hour%10) + 0x30;
	if (i < len) str[i++] = ':';
	if (i < len) str[i++] = (DateTime->Minute/10) + 0x30;
	if (i < len) str[i++] = (DateTime->Minute%10) + 0x30;
	if (i < len) str[i++] = ':';
	if (i < len) str[i++] = (DateTime->Second/10) + 0x30;
	if (i < len) str[i++] = (DateTime->Second%10) + 0x30;
	if (i < len) str[i] = 0;
	return i;
}

