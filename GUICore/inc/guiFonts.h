/*
 * guiFonts.h
 *
 *  Created on: 17.12.2012
 *      Author: Andrey
 */

#ifndef GUIFONTS_H_
#define GUIFONTS_H_

typedef struct
{
	const uint8_t * table;
	uint16_t Width;
	uint16_t Height;
} S_FONT;


typedef struct
{
	const uint8_t * table;
	uint16_t Width;
	uint16_t Height;
	const uint8_t * tableSymbWidth;
	const uint16_t * tableSymbIndex;
	uint16_t Offset;
	uint16_t NumSymb;
	uint16_t SymbolSpace;
} V_FONT;



extern V_FONT GL_ArialBold_16;
extern V_FONT GL_ArialNarrow_15;
extern V_FONT GL_ArialNarrow_21;
extern V_FONT GL_ArialBold_24;
extern V_FONT GL_ArialBold_64;
extern V_FONT GL_Arial_12;
extern V_FONT GL_Arial_11;
extern V_FONT GL_Lucida_8;
extern V_FONT GL_Calibri_10;

extern V_FONT GS_Lucida_12;

#endif /* GUIFONTS_H_ */
