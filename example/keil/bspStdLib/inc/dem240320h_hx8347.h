#ifndef DEM240320H_HX8347_H
#define DEM240320H_HX8347_H

#define RED_16	 	0xFC00
#define GREEN_16 	0x03F0
#define BLUE_16 	0x000F
#define BLACK_16 	0x0000
#define WHITE_16 	0xFFFF
#define GRAY_16 	0x8208
#define YELLOW_16 	0xFFF0
#define ORANGE_16 	0xFD10
#define LIME_16 	0x7FF0


typedef struct 
{
	unsigned clRed		: 6;
	unsigned clGreen	: 6;
	unsigned clBlue		: 4;
} RGB16;

typedef struct 
{
	unsigned clRed		: 6;
	unsigned clGreen	: 6;
	unsigned clBlue		: 6;
} RGB32;


extern void lcdInit(void);



#endif


