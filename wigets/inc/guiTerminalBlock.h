/*
 * guiTerminalBlock.h
 *
 *  Created on: 15.06.2013
 *      Author: Andrey Fursov
 */

#ifndef GUITERMINALBLOCK_H_
#define GUITERMINALBLOCK_H_

typedef struct
{
	WM_OBJ wmObj;
	uint16_t qSymb;
	uint16_t qString;
	uint16_t countString;
	uint16_t startString;
	V_FONT	* vFont;
	uint16_t TextColor;
	char ** strings;
} GUI_TERMINAL_BLOCK;

extern void defaultTerminalBlockInit(GUI_TERMINAL_BLOCK * tBlock, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void TerminalBlockOnPait(GUI_TERMINAL_BLOCK * tBlock);
extern void TerminalBlockStringDraw(GUI_TERMINAL_BLOCK * tBlock);
extern void TerminalBlockClear(GUI_TERMINAL_BLOCK * tBlock);
extern void TerminalBlockAddStrings(GUI_TERMINAL_BLOCK * tBlock, char * str, uint16_t len);


#endif /* GUITERMINALBLOCK_H_ */
