/*
 * guiColor.c
 *
 *  Created on: 26.12.2012
 *      Author: Andrey
 */
#include "gui.h"

uint16_t guiChangeColorLight(uint16_t color, uint16_t percent)
{
	uint32_t temp, outColor;
	outColor = 0;
	temp = 0;
	if (percent > 99)
	{
		if ((color & COLOR_RED_MASK) == COLOR_RED_MASK)
			temp |= 0x00F3;
		if ((color & COLOR_GREEN_MASK) == COLOR_GREEN_MASK)
			temp |= 0x3C03;
		if ((color & COLOR_BLUE_MASK) == COLOR_BLUE_MASK)
			temp |= 0x3CF0;
		if (color == 0) color = 0x5145;

	}
	color |= (uint16_t)temp;
	// red channel
	temp = (color & COLOR_RED_MASK)>>COLOR_RED_OFFSET;
	temp *= percent;
	temp /= 100;
	if (temp > 0x3F) temp = 0x3F;
	temp <<= COLOR_RED_OFFSET;
	temp &= COLOR_RED_MASK;
	outColor |= temp;
	// green channel
	temp = (color & COLOR_GREEN_MASK)>>COLOR_GREEN_OFFSET;
	temp *= percent;
	temp /= 100;
	if (temp > 0x3F) temp = 0x3F;
	temp <<= COLOR_GREEN_OFFSET;
	temp &= COLOR_GREEN_MASK;
	outColor |= temp;
	// blue channel
	temp = (color & COLOR_BLUE_MASK)>>COLOR_BLUE_OFFSET;
	temp *= percent;
	temp /= 100;
	if (temp > 0x0F) temp = 0x0F;
	temp <<= COLOR_BLUE_OFFSET;
	temp &= COLOR_BLUE_MASK;
	outColor |= temp;


	return (uint16_t)outColor;
}


