/*
 * guiFonts.c
 *
 *	Created on: 18.12.2012
 *			Author: Andrey
 */

#include "gui.h"
//#include "..\inc\font_tables\ArialBold_64.h"
//#include "..\inc\font_tables\ArialBold_24.h"
//#include "..\inc\font_tables\ArialBold_16.h"
#include "..\inc\font_tables\ArialNarrow_15.h"
//#include "..\inc\font_tables\ArialNarrow_21.h"
//#include "..\inc\font_tables\Arial_11.h"
#include "..\inc\font_tables\Arial_12.h"
//#include "..\inc\font_tables\Calibri_10.h"
//#include "..\inc\font_tables\LucidaConsolas_8.h"
#include "..\inc\font_tables\fwLucida_12.h"


V_FONT GS_Lucida_12 =
	{
		fwLucida_12_SymbolTable,
		8, 			// Width
		9, 			// Height
		0, // *tableSymbWidth;
		fwLucida_12_OffsetTable, // *tableSymbOffset;
		32, 		// Offset;
		224,			// NumSymb;
		0				// Symbol Space
	};

//S_FONT GS_Lucida_12 =
//{
//	fwLucida_12_SymbolTable,
//	10,
//	12
//};

//V_FONT GL_ArialBold_64 =
//	{
//		ArialBold_64_SymbolTable,
//		0, 			// Width
//		64, 			// Height
//		ArialBold_64_WidthTable, // *tableSymbWidth;
//		ArialBold_64_OffsetTable, // *tableSymbOffset;
//		32, 			// Offset;
//		224,			// NumSymb;
//		4				// Symbol Space
//	};

//V_FONT GL_ArialBold_24 =
//	{
//		ArialBold_24_SymbolTable,
//		0, 			// Width
//		24, 			// Height
//		ArialBold_24_WidthTable, // *tableSymbWidth;
//		ArialBold_24_OffsetTable, // *tableSymbOffset;
//		32, 		// Offset;
//		224,			// NumSymb;
//		2				// Symbol Space
//	};


//V_FONT GL_ArialBold_16 =
//	{
//		ArialBold_16_SymbolTable,
//		0, 			// Width
//		16, 			// Height
//		ArialBold_16_WidthTable, // *tableSymbWidth;
//		ArialBold_16_OffsetTable, // *tableSymbOffset;
//		32, 		// Offset;
//		224,			// NumSymb;
//		1				// Symbol Space
//	};

V_FONT GL_ArialNarrow_15 =
	{
		ArialNarrow_15_SymbolTable,
		0, 			// Width
		15, 			// Height
		ArialNarrow_15_WidthTable, // *tableSymbWidth;
		ArialNarrow_15_OffsetTable, // *tableSymbOffset;
		32, 		// Offset;
		224,			// NumSymb;
		1				// Symbol Space
	};

//V_FONT GL_ArialNarrow_21 =
//	{
//		ArialNarrow_21_SymbolTable,
//		0, 			// Width
//		21, 			// Height
//		ArialNarrow_21_WidthTable, // *tableSymbWidth;
//		ArialNarrow_21_OffsetTable, // *tableSymbOffset;
//		32, 		// Offset;
//		224,			// NumSymb;
//		1				// Symbol Space
//	};
//
//
V_FONT GL_Arial_12 =
	{
		Arial_12_SymbolTable,
		0, 			// Width
		12, 			// Height
		Arial_12_WidthTable, // *tableSymbWidth;
		Arial_12_OffsetTable, // *tableSymbOffset;
		32, 		// Offset;
		224,			// NumSymb;
		1				// Symbol Space
	};
//
//V_FONT GL_Arial_11 =
//	{
//		Arial_11_SymbolTable,
//		0, 			// Width
//		11, 			// Height
//		Arial_11_WidthTable, // *tableSymbWidth;
//		Arial_11_OffsetTable, // *tableSymbOffset;
//		32, 		// Offset;
//		224,			// NumSymb;
//		1				// Symbol Space
//	};
//
//V_FONT GL_Calibri_10 =
//	{
//		Calibri_10_SymbolTable,
//		0, 			// Width
//		10, 			// Height
//		Calibri_10_WidthTable, // *tableSymbWidth;
//		Calibri_10_OffsetTable, // *tableSymbOffset;
//		32, 		// Offset;
//		224,			// NumSymb;
//		1				// Symbol Space
//	};
//
//V_FONT GL_Lucida_8 =
//	{
//		LucidaConsolas_8_SymbolTable,
//		0, 			// Width
//		8, 			// Height
//		LucidaConsolas_8_WidthTable, // *tableSymbWidth;
//		LucidaConsolas_8_OffsetTable, // *tableSymbOffset;
//		32, 		// Offset;
//		224,			// NumSymb;
//		1				// Symbol Space
//	};
