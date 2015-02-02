/*
 * widget.h
 *
 *  Created on: 21.12.2012
 *      Author: Andrey
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include "gui.h"

//! Typical widget structure
typedef struct
{
	uint16_t xPos;						//!< X position for object
	uint16_t yPos;						//!< Y position for object
	uint16_t Width;						//!< Width of object
	uint16_t Height;					//!< Height of object

	uint16_t Color;						//!< Back color of object
	uint16_t BorderWidth;				//!< Border width
	uint16_t BorderColor;				//!< Border color

	unsigned 	Visible			: 1;	//!< Enable draw object
	unsigned 	Enable			: 1;	//!< Enable control object
	unsigned	Transparent		: 1;	//!< Transparent object
	unsigned	Selected		: 1;	//!< Object selected (for button etc.)
	unsigned	Visual3D		: 1;	//!<


} WM_OBJ;

typedef struct
{
	char * 	Text;
	V_FONT	* vFont;

	uint16_t TextColor;
	uint16_t TextPosX;
	uint16_t TextPosY;
	uint16_t TextWidth;
	uint16_t TextLen;

	unsigned	TextAlignH		: 2;
	unsigned	TextAlignV		: 2;
	unsigned	TextRotate		: 2;
	unsigned	TextDirection	: 1;
	unsigned	TextFlip		: 1;

	unsigned 	TextUnderlined	: 1;
	unsigned 	TextCrossed		: 1;

//	unsigned	TextTransparent	: 1;

} WM_TEXT;

typedef struct
{

	unsigned   HoldCounter			: 8;	// ��� �������� �����������
	unsigned   Jitter				: 2;	// ��� ���������� ��������

										// ���������
	unsigned Pressed 				: 1;	// ��������� ������
	unsigned Hold					: 1;	// ��������� ����������� �����������
	unsigned Short					: 1;	// �������� ������� � ����������
	unsigned JustPressed			: 1;	// ������ ������ ��� ������
	unsigned JustReleased			: 1;	// ������ ������ ��� ��������
	unsigned Changed				: 1;	// ��������� ������ ����������
	unsigned 						: 16;	// ������������ �� 32 ����

} WM_TOUCH;

typedef struct
{
	void * pObjInFocus;

} WM_GUI;

extern void wmObjInit(WM_OBJ * wm, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void wmTextInit(WM_TEXT * wmText, char *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v);
extern void wmTextPositionInit(WM_TEXT *wmText, uint16_t xPos, uint16_t yPos, uint16_t width, uint16_t height);
extern void wmTouchControl(WM_OBJ *wmObj, WM_TOUCH *wmTouch, uint16_t x, uint16_t y);
extern void wmObjTextInit(WM_OBJ *wmObj,  WM_TEXT * wmText);
extern void wmTouchInit( WM_TOUCH *wmTouch);
extern void wmObjOnPaint(WM_OBJ * wmObj);
//extern void defaultWmTextInit(WM_OBJ * wm, uint8_t *text, V_FONT * vFont, uint8_t rot, uint8_t flip, uint8_t align_h, uint8_t align_v)

#endif /* WIDGET_H_ */
