#ifndef __PONG_BALL_H__
#define __PONG_BALL_H__

#include "gba_types.h"

/*
Struct for data elements of the ball 
*/
typedef struct Ball{
	s32 x,y,xDir, yDir, size;
	u16 colour;
}Ball;

/*
Functions to intalise and use the ball
*/
extern void StartBall(Ball* a_ball);
extern void InitBall(Ball* a_ball, s32 a_x, s32 a_y, s32 a_size, u16 a_colour);
extern void MoveBall(Ball* a_ball);
extern void DrawBall(Ball* a_ball);
extern void ClearBall(Ball* a_ball);

#endif //__PONG_BALL_H__