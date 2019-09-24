#include "Intellisense.h"

#include <stdint.h>
#include <stdbool.h>

#pragma region Tutorial_000_Code

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
///SetColour(red, green, blue)
u16 SetColour(u8 a_red, u8 a_green, u8 a_blue){
	return (a_red &0x1F) | (a_green & 0x1F) << 5 | (a_blue & 0x1F) << 10; 
}

///Plots a pixel to a given colour on the screen
///PlotPixel(x, y, colour)
void PlotPixel(s32 a_x, s32 a_y, u16 a_colour){
	SCREENBUFFER[a_y * SCREEN_W + a_x] = a_colour; //Find the pixel and plot the colour to that pixels memory address
}

///Draws a rectangle to the screen
///DrawRect(startLeft, startTop, width, height, colour, filled)
void DrawRect(s32 a_left, s32 a_top, s32 a_width, s32 a_height, u16 a_colour, bool a_filled){
	
	//Check if we want a filled or "empty" rect
	if(a_filled){	
		//Loop through all x/y values
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

//Calculate the absolute value of a int
//abs(value)
s32 abs(s32 a_val){
	s32 mask = a_val >> 31;
	return (a_val ^ mask) - mask;
}

///Draws a line to the screen
///DrawLine(startX, startY, endX, endY, colour)
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

#pragma endregion

#pragma region Random_Number_Generation
//Random Number Generation
s32 __gba_rand_seed = 22;

//Seed the RNG
//seedGBARand(a_seed)
s32 SeedGBARand(s32 a_value){
	s32 old_seed = __gba_rand_seed;
	__gba_rand_seed = a_value;
	return old_seed;
}

///Generate a rando number using LCG
s32 GBARand(){
	__gba_rand_seed = 1664525 + __gba_rand_seed + 1013904223;
	return(__gba_rand_seed >> 16) & 0x7FFF;
}

///Generate a random number within a range
s32 GBARandRange(s32 a_min, s32 a_max){
	return (GBARand() * (a_max - a_min) >> 15) + a_min;
}

#pragma endregion

#pragma region VSync

#define REG_VCOUNT (*(vu16*)(0x04000006)) //Keeps count of what scan line we are drawing

//Vsync the screen
void VSync(){
	while(REG_VCOUNT >= SCREEN_H);
	while(REG_VCOUNT < SCREEN_H);
}

#pragma endregion

#pragma region Pong_Ball

typedef struct Ball{
	s32 x,y,xDir, yDir, size;
	u16 colour;
}Ball;

//Start the ball moving in a random direcition
void StartBall(Ball* a_ball){

	//Generate Random x dir, we don't want it to be 0
	while(a_ball->xDir == 0){
		a_ball->xDir = GBARandRange(-1,2);
	}
	a_ball->yDir = GBARandRange(-1,2);
}

//Initlalise the ball
void InitBall(Ball* a_ball, s32 a_x, s32 a_y, s32 a_size, u16 a_colour){

	a_ball->x = a_x;
	a_ball->y = a_y;
	a_ball->size = a_size;
	a_ball->colour = a_colour;
	a_ball->xDir = a_ball->yDir = 0;
	StartBall(a_ball);
}

//Move the ball with its current direction
void MoveBall(Ball* a_ball){

	//Move ball in y direction
	a_ball->y += a_ball->yDir;

	//Bounds check for top/bottom of screen
	if(a_ball->y < 0){
		a_ball->y = 0;
		a_ball->yDir *= -1;
	}else if(a_ball->y > SCREEN_H - a_ball->size){
		a_ball->y = SCREEN_H - a_ball->size;
		a_ball->yDir *= -1;
	}

	//Move ball in y direction
	a_ball->x += a_ball->xDir;

	//Bounds check for left/right (reset ball)
	if(a_ball->x < 0 || a_ball-> x > SCREEN_W - a_ball->size){
		a_ball->x = (SCREEN_W >> 1)  - (a_ball->size >> 1); //bitshift >> 1 is the same as *0.5
		a_ball->y = (SCREEN_H >> 1)  - (a_ball->size >> 1); //bitshift >> 1 is the same as *0.5
		a_ball->xDir = a_ball->yDir = 0;
		StartBall(a_ball);
	}

}

///Draws the ball on the screen
void DrawBall(Ball* a_ball){
	DrawRect(a_ball->x, a_ball->y, a_ball->size, a_ball->size, a_ball->colour, true);
}

///Clears the ball draw
void ClearBall(Ball* a_ball){
	DrawRect(a_ball->x, a_ball->y, a_ball->size, a_ball->size, SetColour(0,0,0), true);
}

#pragma endregion

#pragma region Pong_Paddle

typedef struct Paddle{
	s32 x,y,width,height;
	s16 colour;
}Paddle;

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


#pragma endregion

int main()
{
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_3 | BG_ENABLE2;

	SeedGBARand(2903);
	
		
	Ball ball;
	InitBall(&ball, SCREEN_H >> 0, SCREEN_H >> 1,10,  SetColour(31,31,31));

	Paddle p1;
	InitPaddle(&p1, 10, 60, 8,40, SetColour(0,0,31));

	Paddle p2;
	InitPaddle(&p2, SCREEN_W - 10, 60, 8,40, SetColour(31,0,0));

	while(1){
		VSync();
		ClearBall(&ball);
		ClearPaddle(&p1);
		ClearPaddle(&p2);

		MoveBall(&ball);
		DrawBall(&ball);
		DrawPaddle(&p1);
		DrawPaddle(&p2);
	}

	return 0;
}