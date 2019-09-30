#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"
#include "gba_input.h"


int main()
{
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_3 | BGMODE_2;
	register_vblank_isr();

	SeedGBARand(2903);
	
	//Create ball
	Ball ball;
	InitBall(&ball, SCREEN_H >> 0, SCREEN_H >> 1,10,  SetColour(31,31,31));

	//Create paddles
	Paddle p1;
	InitPaddle(&p1, 10, 60, 8,40, UP, DOWN, SetColour(0,0,31));
	Paddle p2;
	InitPaddle(&p2, SCREEN_W - 10, 60, 8,40, B, A, SetColour(31,0,0));

	while(1){
		vblank_int_wait(); //Wait for vblank

		PollKeys();

		ClearBall(&ball);
		ClearPaddle(&p1);
		ClearPaddle(&p2);

		MoveBall(&ball);
		MovePaddle(&p1);
		MovePaddle(&p2);

		DrawBall(&ball);
		DrawPaddle(&p1);
		DrawPaddle(&p2);  
	}

	return 0;
}