#include "button.h"

void initButton(TBUTTON * _but, unsigned int _numButton)
{
	int i;
	if (_numButton > NUMKEYMAX) _numButton = 0; 
	for (i = 0; i < _numButton; i++)
	{
		_but[i].bsChanged = 0;
		_but[i].bsHoldCounter = 0;
		_but[i].bsHold = 0;
		_but[i].bsJitter = 0;
		_but[i].bsJustPressed = 0;
		_but[i].bsJustReleased = 0;
		_but[i].bsPressed = 0;
		_but[i].bsShort = 0;
	}		
}	

void buttonControl(TBUTTON * _button, unsigned int _pKeyIn, unsigned int _numButton )
{
	unsigned int i;
	if (_numButton > NUMKEYMAX) _numButton = 0; 
	for(i = 0; i < _numButton; i++)
	{
		
		//------------------------------------------------------------------------------
		//  Кнопка еще не нажата
		//------------------------------------------------------------------------------
		if (!_button[i].bsPressed) 
		{
			_button[i].bsJitter++;
			// активный уровень 0
			if ((_pKeyIn & (1<<i))) _button[i].bsJitter = 0;  // Подавляем дребезг
		
			if (_button[i].bsJitter == 3)				// Перестала дребезжать
			{
				_button[i].bsPressed = 1;			 	// Нажата
				_button[i].bsJustPressed = 1;		 	// Нажата только что (сбрасывается вручную)
				_button[i].bsHold = 0;					// Не удерживается
				_button[i].bsShort = 0;			   		// Не короткое нажатие
				_button[i].bsHoldCounter = 0;
			}   // if jitter
		} 
		else
		{	// if button pressed
		
			//------------------------------------------------------------------------------
			//  Кнопка нажата, проверяем удерживание
			//------------------------------------------------------------------------------
		
			_button[i].bsJitter++;
			// активный уровень 0
			if (!(_pKeyIn & (1<<i))) _button[i].bsJitter = 0; // Подавляем шорох
		
			if (_button[i].bsJitter == 3)			 // Кнопку только что отпустили
			{
				_button[i].bsPressed = 0;
				if (!_button[i].bsHold)			   	// Если не было удерживаниядольше 1 сек,
					_button[i].bsShort = 1;		   	// то установить флаг "короткого нажатия"
		
				_button[i].bsHold = 0;
				_button[i].bsHoldCounter = 0;
		
			}   // if jitter
		
			_button[i].bsHoldCounter++;
		
			if (_button[i].bsHoldCounter >= 50)	   // Проверяем удерживание
				_button[i].bsHold = 1;
		
		}   // if button pressed	
	}
}	

