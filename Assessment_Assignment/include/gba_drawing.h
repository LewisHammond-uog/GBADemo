/*
Basic Pixel Plotting Drawing Functionaility
*/
#ifndef __GBA_DRAWING_H__
#define __GBA_DRAWING_H__

#include "gba_types.h"

/*
GBA CONST defines for screen info
*/
#define SCREENBUFFER ((u16*)(VRAM))
#define SCREEN_W 240
#define SCREEN_H 160

///Gets a memory value to create a colour to display on the screen
extern u16 SetColour(u8 a_red, u8 a_green, u8 a_blue);

///Plots a pixel to a given colour on the screen
extern void PlotPixel(s32 a_x, s32 a_y, u16 a_colour);

///Draws a rectangle to the screen
extern void DrawRect(s32 a_left, s32 a_top, s32 a_width, s32 a_height, u16 a_colour, bool a_filled);

///Draws a line to the screen
extern void DrawLine(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u16 a_colour);

#endif //__GBA_DRAWING_H__
