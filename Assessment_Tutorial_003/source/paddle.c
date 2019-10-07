#include "paddle.h"
#include "gba_drawing.h"
#include "gba_input.h"

/*
Initalises the data elements of the paddle
*/
void InitPaddle(Paddle* a_paddle, s32 a_x, s32 a_y, s32 a_width, s32 a_height, u16 a_up, u16 a_down, u16 a_colour){
	a_paddle->x = a_x;
	a_paddle->y = a_y;
	a_paddle->width = a_width;
	a_paddle->height = a_height;
	a_paddle-> upButton = a_up;
	a_paddle-> downButton = a_down;
	a_paddle->colour = a_colour;
}

/*
Draws the paddle on the screen
*/
void DrawPaddle(Paddle* a_paddle){
	DrawRect(a_paddle->x, a_paddle->y, a_paddle->width, a_paddle->height, a_paddle->colour, true);
}

void MovePaddle(Paddle* a_paddle){

	s16 dir = 0;
	if(KeyDown(a_paddle->upButton)){
		dir = -1;
	}else if(KeyDown(a_paddle->downButton)){
		dir = 1;
	}

	a_paddle->y += dir;
}

/*
Clears a rectangle behind the paddle on the screen
*/
void ClearPaddle(Paddle* a_paddle){
	DrawRect(a_paddle->x, a_paddle->y, a_paddle->width, a_paddle->height, SetColour(0,0,0), true);
}