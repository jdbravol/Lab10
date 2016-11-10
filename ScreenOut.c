//Name: Juan David bravo
//Class: EE 445L T-TH 2:00-3:30
//

#include "ScreenOut.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "../EE445L/Lab1/ST7735.h"
#include "../EE445L/inc/tm4c123gh6pm.h"


void ST7735_sDecOut(int32_t n){
	ST7735_OutChar(n/1000 + 0x30);	// outputs the one value
	ST7735_OutChar('.');						// decimal
	n%=1000;
	ST7735_OutChar(n/100 + 0x30);		// tenth
	n%=100;
	ST7735_OutChar(n/10 + 0x30);		//hundredth
	n%=10;
	ST7735_OutChar(n + 0x30);				//thousandth 
}
	
int gHeight;
int gWidth;
void ST7735_LineGraphInit(int height, int width) {
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(0);
	ST7735_DrawFastVLine(12, 10, height, ST7735_GREEN);
	ST7735_DrawFastHLine(12, 10 + height, width, ST7735_GREEN);
	ST7735_DrawChar(0,5,'4',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(5,5,'0',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(0,(10+height/4),'3',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(5,(10+height/4),'0',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(0,(10+height/2),'2',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(5,(10+height/2),'0',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(0,(10+height*.75),'1',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(5,(10+height*.75),'0',ST7735_WHITE,ST7735_BLACK,1);
		ST7735_DrawChar(5,(10+height),'0',ST7735_WHITE,ST7735_BLACK,1);
	for (int i = 0; i < width; i += 4) {
		int x = 12 + i;
		ST7735_DrawFastVLine(x, 5 + height, 10, ST7735_GREEN);
	}
	gHeight = height;
	gWidth = width;
}

int x = 13;
void ST7735_PlotNewPoint(int val) {
	ST7735_DrawFastVLine(x, 10, gHeight-5, ST7735_BLACK);
	ST7735_DrawFastVLine(x + 1, 10, gHeight-5, ST7735_BLACK);
	val = (val*(gHeight/40)) + 10;
	ST7735_DrawPixel(x, val, ST7735_BLUE);
	ST7735_DrawPixel(x + 1, val, ST7735_BLUE);
	ST7735_DrawPixel(x, val + 1, ST7735_BLUE);
	ST7735_DrawPixel(x + 1, val + 1, ST7735_BLUE);
	x = x + 4;
	if (x > gWidth + 12) {
		x = 13;
		ST7735_FillRect(13, 10, gWidth + 5, gHeight -5, ST7735_BLACK); 
	}
}

double vals[26];
int i = 0;
void addPoint(double val) {
	vals[i] = val;
	i += 1;
	i%=26;
}

void ST7735_PlotArray(void) {
	int j = i;
	while (x < gWidth + 13) {
		ST7735_DrawFastVLine(x, 10, gHeight-5, ST7735_BLACK);
		ST7735_DrawFastVLine(x + 1, 10, gHeight-5, ST7735_BLACK);
		int val = ((40 - vals[j])*((gHeight*.75)/30)) + 10;
		ST7735_DrawPixel(x, val, ST7735_BLUE);
		ST7735_DrawPixel(x + 1, val, ST7735_BLUE);
		ST7735_DrawPixel(x, val + 1, ST7735_BLUE);
		ST7735_DrawPixel(x + 1, val + 1, ST7735_BLUE);
		j += 1;
		j%=26;
		x += 4;
	}
	x = 13;
}
