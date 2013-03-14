/*
 * colors.h
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#ifndef COLORS_H_
#define COLORS_H_


typedef struct
{
	unsigned BLUE	: 4;
	unsigned GREEN	: 6;
	unsigned RED	: 6;
} GUI_COLOR;


extern uint16_t guiChangeColorLight(uint16_t color, uint16_t percent);

#endif /* COLORS_H_ */
