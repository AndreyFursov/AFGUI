#ifndef _BUTTON_H
#define _BUTTON_H


#define NUMKEYMAX 	32

typedef struct 
{	
	unsigned char   bsHoldCounter	: 8;	// Для проверки удерживания
	unsigned char   bsJitter		: 2;		// Для подавления дребезга
	
										// Состояния
	unsigned bsPressed 				:1;		// Состояния кнопок
	unsigned bsHold					:1;		// Состояние длительного удерживания
	unsigned bsShort				:1;		// Короткое нажатие и отпускание
	unsigned bsJustPressed			:1;		// Кнопки только что нажаты
	unsigned bsJustReleased			:1;		// Кнопки только что отпущены
	unsigned bsChanged				:1;		// Состояние кнопок изменилось
		
									// События:

} TBUTTON;

extern void buttonControl(TBUTTON *, unsigned int _pKeyIn, unsigned int _numKey );
extern void initButton(TBUTTON * _but, unsigned int _numButton);

// пример от tester
// http://www.microchip.su/showpost.php?p=76612&postcount=12




#endif
