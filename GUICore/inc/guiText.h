/*
 * guiText.h
 *
 *  Created on: 27.12.2012
 *      Author: Andrey
 */

#ifndef GUITEXT_H_
#define GUITEXT_H_

extern void guiDrawString(uint8_t * text, V_FONT *font, uint16_t len, uint16_t Xpos, uint16_t Ypos);
extern void int16toString(uint8_t *str, int16_t value, uint16_t len, uint8_t format);

#endif /* GUITEXT_H_ */
