/*
 * appGUI.c
 *
 *  Created on: 07.05.2013
 *      Author: Andrey Fursov
 */

#include "globals.h"
#include "HMI_Control.h"

#define  TASK_APPGUI_PRIORITY		12
// stack size
#define  TASK_APPGUI_STK_SIZE		128	
// stack
unsigned int task_appGUI_stack[TASK_APPGUI_STK_SIZE];
TN_TCB  task_appGUI;

void task_appGUI_func(void * par);

void appGUI_task_create(void)
{
   task_appGUI.id_task = 0;
   tn_task_create(&task_appGUI,               //-- task TCB
                 task_appGUI_func,            //-- task function
                 TASK_APPGUI_PRIORITY,        //-- task priority
                 &(task_appGUI_stack          //-- task stack first addr in memory
                    [TASK_APPGUI_STK_SIZE-1]),
                 TASK_APPGUI_STK_SIZE,        //-- task stack size (in int,not bytes)
                 NULL,                          //-- task function parameter
                 TN_TASK_START_ON_CREATION      //-- Creation option
                 );
	
}



// функция обработки GUI
void task_appGUI_func(void * par)
{
	uint16_t temp;
	// GUI app init
	LCD_Init();
	LCD_Clear(LCD_COLOR_BLUED);
	touchLoadCoef();
	if (getTouchState() || touchVerifyCoef())
	{
//		touchSetCoef(11, -17, -15, 256);
		while (9 != temp) 
		{
			temp = touchCalibration();
			tn_task_sleep(40);
		}
	}
	LCD_Clear(LCD_COLOR_GREYL);

	
	for(;;)
	{
		HMI_Control();
		tn_task_sleep(30);
	}
}
