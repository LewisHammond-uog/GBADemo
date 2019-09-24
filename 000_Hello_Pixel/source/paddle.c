#include "paddle.h"
#include "gba_drawing.h"

//Initalise the paddle
void InitPaddle(Paddle* a_paddle, s32 a_x, s32 a_y, s32 a_width, s32 a_height, u16 a_colour){
	a_paddle->x = a_x;
	a_paddle->y = a_y;
	a_paddle->width = a_width;
	a_paddle->height = a_height;
	a_paddle->colour = a_colour;
}

//Draw the paddle
void DrawPaddle(Paddle* a_paddle){
	DrawRect(a_paddle->x, a_paddle->y, a_paddle->width, a_paddle->height, a_paddle->colour, true);
}

//Draw the paddle
void ClearPaddle(Paddle* a_paddle){
	DrawRect(a_paddle->x, a_paddle->y, a_paddle->width, a_paddle->height, a_paddle->colour, SetColour(0,0,0));
}