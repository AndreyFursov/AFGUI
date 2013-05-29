#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "hw_config.h"
#include "tn.h"
#include "gui.h"
#include "appGUI.h"

#include "ee_emul.h"

#define VECTACTIVE  (0x000001FF)
#define rNVIC_ICSR  (*((__IO unsigned int*)0xE000ED04))


typedef unsigned int volatile SYSTEM_TIMER;
extern SYSTEM_TIMER getSystemTimer1ms(void);
extern SYSTEM_TIMER getSystemTimer1s(void);
extern void setSystemTimer1s(SYSTEM_TIMER timer);








#endif
