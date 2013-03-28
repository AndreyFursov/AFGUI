/*
 * guiRadioGroup.h
 *
 *  Created on: 24.03.2013
 *      Author: Andrey Fursov
 */

#ifndef GUIRADIOGROUP_H_
#define GUIRADIOGROUP_H_

typedef struct
{
	WM_OBJ		wmObj;
	WM_TEXT		wmTxt;
	WM_TOUCH 	wmTouch;
} GUI_RADIO_GROUP_ITEM;


typedef struct
{
	WM_OBJ	wmObj;
	WM_TEXT	wmTxt;
	GUI_RADIO_GROUP_ITEM Item[8];
	uint8_t		NumItem;
	uint8_t		ItemSelected;

} GUI_RADIO_GROUP;


extern void defaultRadioGroupInit(GUI_RADIO_GROUP * radioGroup, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
extern void defaultRadioGroupItemInit(GUI_RADIO_GROUP * radioGroup, uint8_t numItem, uint8_t itemSelected);
extern void RadioGroupTextInit(GUI_RADIO_GROUP * radioGroup, char *text, V_FONT * vFont);

extern void RadioGroupItemInit(GUI_RADIO_GROUP * radioGroup, char *text, V_FONT * vFont, uint8_t index);

extern void RadioGroupDraw(GUI_RADIO_GROUP * radioGroup);
extern void RadioGroupTouchControl(GUI_RADIO_GROUP * radioGroup, int16_t xTouch, int16_t yTouch);
extern void RadioGroupStateRefresh(GUI_RADIO_GROUP * radioGroup);



#endif /* GUIRADIOGROUP_H_ */
