#include "gba_drawing.h"
#include "gba_gfx.h"


//Creates the block of memory that can be used to create a colour at a given pixel
//a_red - Red Value
//a_green - Green Value
//a_blue - Blue Value
u16 SetColour(u8 a_red, u8 a_green, u8 a_blue){
	return (a_red &0x1F) | (a_green & 0x1F) << 5 | (a_blue & 0x1F) << 10; 
}


//Plots a pixel on the screen of a given colour
//a_x - X
//a_y - Y
//a_colour - Colour
void PlotPixel(s32 a_x, s32 a_y, u16 a_colour){
	SCREENBUFFER[a_y * SCREEN_W + a_x] = a_colour; //Find the pixel and plot the colour to that pixels memory address
}


//Draws a rectangle (filled or unfilled) to the screen
//a_left - Left (X) Coordinate
//a_top - Top (Y) Coordinate
//a_width - Width of Rect
//a_height - Height of Rect
//a_colour - Colour of Rect
//a_filled - Filled or Outline Rect?
void DrawRect(s32 a_left, s32 a_top, s32 a_width, s32 a_height, u16 a_colour, bool a_filled){
	
	//Check if we want a filled or "empty" rect
	if(a_filled){	
		//Loop through all x/y values and fill with colour
		for(s32 y = 0; y < a_height; ++y){
			for(s32 x = 0; x < a_width; ++x){
				PlotPixel(a_left + x, a_top +y, a_colour);
			}
		}
	}else{
		//Draw an empty rect by drawing out 4 lines
		DrawLine(a_left, a_top, a_left + a_width, a_top, a_colour); //Top line
		DrawLine(a_left, a_top, a_left, a_top + a_height, a_colour); //Left line
		DrawLine(a_left, a_top + a_height, a_left + a_width, a_top + a_height, a_colour); //Bottom line
		DrawLine(a_left + a_width, a_top , a_left + a_width, a_top + a_height, a_colour); //Right line
	}
}


//Draws a line to the screen of a given colour
//a_x - Starting X
//a_y - Starting Y
//a_x2 - Ending X
//a_y2 - Ending Y
//a_colour - Colour
void DrawLine(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u16 a_colour){

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
		PlotPixel(a_x, a_y, a_colour);
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