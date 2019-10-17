#include "ball.h"
#include "gba_drawing.h"

/*
Starts the ball moving in a random direction. Direction chosen will head towards 
the paddles on the side of the screen
*/
void StartBall(Ball* a_ball){

	//Generate Random x dir, we don't want it to be 0
	while(a_ball->xDir == 0){
		a_ball->xDir = GBARandRange(-1,2);
	}
	a_ball->yDir = GBARandRange(-1,2);
}

/*
Initalises data properties and calls to start the ball moving in a random direction
*/
void InitBall(Ball* a_ball, s32 a_x, s32 a_y, s32 a_size, u16 a_colour){

	a_ball->x = a_x;
	a_ball->y = a_y;
	a_ball->size = a_size;
	a_ball->colour = a_colour;
	a_ball->xDir = a_ball->yDir = 0;
	StartBall(a_ball);
}

/*
Moves the ball in its current direction. Protecting the ball from going off the screen.
Resets the ball if it goes behind the paddles
*/
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

/*
Draws the ball to the screen
*/
void DrawBall(Ball* a_ball){
	DrawRect(a_ball->x, a_ball->y, a_ball->size, a_ball->size, a_ball->colour, true);
}

/*
Clears the rect behind the ball on the screen
*/
void ClearBall(Ball* a_ball){
	DrawRect(a_ball->x, a_ball->y, a_ball->size, a_ball->size, SetColour(0,0,0), true);
}

#pragma endregion