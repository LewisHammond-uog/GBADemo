#include "Intellisense.h"

#include <stdint.h>
#include <stdbool.h>

//Basic Types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
//Define volitile types (i.e don't optimise (const) these types as hardware might change them)
typedef volatile uint8_t vu8;
typedef volatile uint16_t vu16;
typedef volatile uint32_t vu32;
typedef volatile int8_t vs8;
typedef volatile int16_t vs16;
typedef volatile int32_t vs32;

#define REG_DISPCNT *((vu32*)(0x04000000)) //Address of the display controller
#define VIDEOMODE_3 0x0003
#define BG_ENABLE2 0x0400

#define SCREENBUFFER ((vu16*)(0x06000000)) //Screenbuffer - where you can write directly to the screen
#define SCREEN_W 240
#define SCREEN_H 160

///Gets a memory value to create a colour to display on the screen
///setColour(red, green, blue)
u16 setColour(u8 a_red, u8 a_green, u8 a_blue){
	return (a_red &0x1F) | (a_green & 0x1F) << 5 | (a_blue & 0x1F) << 10; 
}

///Plots a pixel to a given colour on the screen
///plotPixel(x, y, colour)
void plotPixel(s32 a_x, s32 a_y, u16 a_colour){
	SCREENBUFFER[a_y * SCREEN_W + a_x] = a_colour; //Find the pixel and plot the colour to that pixels memory address
}

///Draws a rectangle to the screen
///drawRect(startLeft, startTop, width, height, colour, filled)
void drawRect(s32 a_left, s32 a_top, s32 a_width, s32 a_height, u16 a_colour, bool a_filled){
	
	//Check if we want a filled or "empty" rect
	if(a_filled){	
		//Loop through all x/y values
		for(s32 y = 0; y < a_height; ++y){
			for(s32 x = 0; x < a_width; ++x){
				plotPixel(a_left + x, a_top +y, a_colour);
			}
		}
	}else{
		//Draw an empty rect by drawing out 4 lines
		drawLine(a_left, a_top, a_left + a_width, a_top, a_colour); //Top line
		drawLine(a_left, a_top, a_left, a_top + a_height, a_colour); //Left line
		drawLine(a_left, a_top + a_height, a_left + a_width, a_top + a_height, a_colour); //Bottom line
		drawLine(a_left + a_width, a_top , a_left + a_width, a_top + a_height, a_colour); //Right line
	}
}

//Calculate the absolute value of a int
//abs(value)
s32 abs(s32 a_val){
	s32 mask = a_val >> 31;
	return (a_val ^ mask) - mask;
}

///Draws a line to the screen
///drawLine(startX, startY, endX, endY, colour)
void drawLine(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u16 a_colour){

	//Get the horizontal and vertical displacement of the line
	s32 w = a_x2 - a_x;
	s32 h = a_y2 - a_y;
	//Work out the change in x and y with these delta values
	s32 dx1 = 0, dx2 = 0, dy1 = 0, dy2 = 0;

	if(w < 0) dx1 = dx2 = -1; else if(w > 0) dx1 = dx2 = 1;
	if(h < 0) dy1 = -1; else if(h > 0) dy1 = 1;
	
	//Work out the longest side, start by assuming that width is the longest
	s32 longest = abs(w);
	s32 shortest = abs(h);

	//test if we assumed correctly
	if(shortest > longest){
		//We assumed wrong
		//use xor to swap the values of longest and shortest
		longest ^= shortest; shortest ^= longest; longest ^= shortest;
		if(h < 0) dy2 = -1; else if(h > 0) dy2 = 1;
		dx2 = 0;
	}

	//Get half of the longest displacement
	s32 num = longest >> 1;
	for(s32 i = 0; i <= longest; ++i){
		plotPixel(a_x, a_y, a_colour);
		num += shortest;
		if(num > longest){
			num -= longest;
			a_x += dx1;
			a_y += dx1;
		}else{
			a_x += dx2;
			a_y += dy2;
		}
	}
	

}

int main()
{
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_3 | BG_ENABLE2;

	s32 t = 0;
	while(1){
		drawRect(20, 20, SCREEN_W - 40, SCREEN_H - 40, setColour(31,5,12), false);
		drawLine(10,5, 230, 70, setColour(20,10,1));
	}
	return 0;
}