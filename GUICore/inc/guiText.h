/*
 * guiText.h
 *
 *  Created on: 27.12.2012
 *      Author: Andrey
 */

#ifndef GUITEXT_H_
#define GUITEXT_H_

extern void guiDrawString(char * text, V_FONT *font, uint16_t len, uint16_t Xpos, uint16_t Ypos);
extern uint32_t int16toString(char * str, int16_t value, uint16_t len, uint8_t format);
extern uint32_t uint32toTime(char * str, uint32_t value, uint16_t len, uint8_t format);
extern uint32_t int32toString(char * str, int32_t value, uint16_t len, uint8_t format);

#endif /* GUITEXT_H_ */
