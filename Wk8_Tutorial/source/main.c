#include "gba.h"


#include <string.h>

#include "cotanlut.h"
#include "tanlut.h"
#include "sinlut.h"
#include "coseclut.h"
#include "viewCorrectionlut.h"
#include "rayStepDistlut.h"
#include "Wolf3DWalls.h"

//These two files are generated by our makefile process from
//binary files that have been stored in the img directory 
#include "Wolf3DWallsImg_bin.h"
#include "Wolf3DWallsPal_bin.h"

#include <stdarg.h>
#include <stdio.h>


//\The following code is a useful way to get printf style debugging into mGBA
//#define DEBUG_PRINT 0

#define REG_DEBUG_ENABLE *(v_u16*)0x4FFF780
#define REG_DEBUG_FLAGS *(v_u16*)0x4FFF700
#define REG_DEBUG_STRING *(char*)0x4FFF600

void mgbaLog(int level, const char* str, ...) 
{
  REG_DEBUG_ENABLE = 0xC0DE;
  level &= 0x7;
  va_list args;
  va_start(args, str);
  vsnprintf(&REG_DEBUG_STRING, 0x100, str, args);
  va_end(args);
  REG_DEBUG_FLAGS = level | 0x100;
}

//define a palette for use with the background rendering to render a sky and floor
#define g_paletteLen 36
const u16 g_palette[18] = {
	0x7203, 0x7205, 0x7208, 0x720A, 0x720D, 0x720F, 0x7212, 0x7214,
	0x2945, 0x2946, 0x2948, 0x294A, 0x294C, 0x294E, 0x6B5A, 0x56B5, 
	0x03FF, 0x03E0
};

//\ For the GBA raycaster tiles will be divided up into increments of 64 
//\ this allows us to utilise integer values and rely less on fixed point inaccuracy
#define TILE_SIZE 16384 //(64 << 8 )
#define INV_TILE_SIZE (1/TILE_SIZE)
//\ We will use the FOV value and the SCREEN_W value to determine how many values our
//\ Trig tables need to hold.  
//\ The FOV for our Raycaster
#define FOV 60
#define ANGLE_FOV SCREEN_W
//\ values are integer values as these values will be used within look up tables
#define ANGLE_HALF_FOV (ANGLE_FOV >> 1)
//\ Define quadrant values
#define FOV_PER_CIRCLE (360/FOV)
#define ANGLE_360 ( FOV_PER_CIRCLE * ANGLE_FOV)
#define ANGLE_180 (ANGLE_360 >> 1)
#define ANGLE_90 (ANGLE_180 >> 1)
#define ANGLE_270 (ANGLE_90 + ANGLE_180)

//\--------------------------------------------------------------------
//\ Define our map for this ray caster level
//\ define width and height of the level
//\ use an array of integers to denote wall values
//\ Numerical values correspond to a texture index within a texture sheet
#define mapWidth 24
#define mapHeight 24

int worldMap[mapHeight][mapWidth] =
{
  {1,1,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,13,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,12,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,12,1,1,1,0,0,0,0,0,0,1,1,1,12,1,1,1,1,1},
  {1,1,0,1,0,0,0,0,12,0,0,0,0,0,0,12,0,0,0,0,1,0,1,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,13,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
//\--------------------------------------------------------------------
void drawBackground();
void drawVerticalSegment(s32 a_x, s32 a_y, s32 a_height, s16 a_tileID, s16 a_textureOffset, s16 paletteOffset);

int main()
{
	//define the video mode
	//For this raycasting demo we will use mode 4 bitmap rendering with page swapping
	//MODE 4 is 8bpp with 2 pages
	REG_DISPCNT = VIDEOMODE_4 | BGMODE_2;
	register_vblank_isr();
	//set the palette memory
	memcpy(PAL_BG_BLOCK(0), g_palette, g_paletteLen);
	memcpy(PAL_BG_BLOCK(1), Wolf3DWallsPal_bin, Wolf3DWallsPalLen);
	
	//Players Attributes
	fixed playerX = int2fix(100);
	fixed playerY = int2fix(160);
	s32 playerRot = 20;

	fixed cameraNearPlane = int2fix(208);
	
	fixed gridX = 0, gridY = 0;
	fixed xIntersect = 0, yIntersect = 0;
	
	//loop forever
	while(1)
	{
		//wait until v-sync occurs
		vblank_intr_wait();
		//draw the background every frame (essentially clear the screen each frame)
		drawBackground();
		gridX = 0; gridY = 0;
		xIntersect = 0; yIntersect = 0;
	
		s32 castAngle = playerRot - ANGLE_HALF_FOV;
		if (castAngle < 0)
		{
			castAngle = ANGLE_360 + castAngle;
		}
		

		//find grid and intercept locations
		fixed playerGridY = fixMul(fixFloor(fixDiv(playerY , TILE_SIZE)) , TILE_SIZE);
		fixed playerGridX = fixMul(fixFloor(fixDiv(playerX , TILE_SIZE)) , TILE_SIZE);

		s16 textureOffset = 0;

		fixed yStep = 0;
		fixed xStep = 0;
		//for our raycaster to function we need to iterate through each column of pixels on the screen and test for ray intersections
		for (u32 i = 0; i < SCREEN_W; i+=2)
		{
			//find grid and intercept locations
			gridY = playerGridY;
			gridX = playerGridX;
			yStep = 0;
			xStep = 0;
			
			
			
			//Find the xIntersection
			if (castAngle > 0 && castAngle < ANGLE_180) //Ray is facing down
			{
				gridY += TILE_SIZE;
				yStep = TILE_SIZE;
				
			}
			else
			{
				yStep = -TILE_SIZE;
				gridY -= FIX_ONE;
			}
			
			//Find the Y Intersection
			if (castAngle < ANGLE_90 || castAngle > ANGLE_270) // our ray is facing right
			{
				gridX += TILE_SIZE;
				xStep = TILE_SIZE;
			}
			else
			{
				gridX-= FIX_ONE;
				xStep = -TILE_SIZE;
			}

			fixed coTanVal = cotan_lut[castAngle]>>4;
			fixed tanVal = tan_lut[castAngle]>>4;

			fixed xDiff = gridX - playerX;
			fixed yDiff = gridY - playerY;
			//this if statement tests if the multiplication is outside the bounds of our fixed point storage 
			//we only have 24 bits to store our whole number part if we exceed that range then we will truncate the value and get a smaller number (we get errors)
			if( (((coTanVal>>8) * (yDiff>>8)) << 8) > (1 << 24))
			{
				xIntersect = 0xFFFFFF;
			}
			else
			{
				fixed fxIntersect = fixMul(coTanVal, yDiff);
				xIntersect = fxIntersect + playerX;
			}

			if ((((tanVal >> 8) * (xDiff>>8)) << 8) > (1 << 24))
			{
				yIntersect = 0xFFFFFF;
			}
			else
			{
				fixed fyIntersect = fixMul(tanVal, xDiff);
				yIntersect = fyIntersect + playerY;
			}

			fixed xStepDelta = rayXStepDistance_lut[castAngle]>>4;
			fixed yStepDelta = rayYStepDistance_lut[castAngle]>>4;

			
#ifdef DEBUG_PRINT
			mgbaLog( 1, "xStepDelta: 0x%X", xStepDelta);
			mgbaLog( 1, "yStepDelta: 0x%X", yStepDelta);
#endif
			fixed rayX = playerX;
			fixed rayY = playerY;
			fixed xDistanceToIntersect;
			fixed yDistanceToIntersect;

			s16 bHit = 0;
			while (bHit == 0)
			{

				s32 angle = castAngle + ANGLE_90;
				if (angle >= ANGLE_360)
				{
					angle -= ANGLE_360;
				}
				xDistanceToIntersect = abs(fixMul(abs(xIntersect - rayX), cosec_lut[angle] >> 4));
				yDistanceToIntersect = abs(fixMul(abs(yIntersect - rayY), cosec_lut[castAngle] >> 4));
				
				xDiff = gridX - rayX;
				yDiff = gridY - rayY;

				if (yDistanceToIntersect <= xDistanceToIntersect)
				{
					
								
					rayX += xDiff;// -gridXOffset;
					rayY = yIntersect;
					yIntersect += yStepDelta;
					gridX += xStep;
					textureOffset = rayY>>8; // set the palette so that we have different north/south and east/west wall colours


				}
				else
				{
					rayX = xIntersect;
					rayY += yDiff;// -gridYOffset;
					xIntersect += xStepDelta;
					gridY += yStep;
					textureOffset = rayX>>8;

				}

				//find our texture offset value
				textureOffset = textureOffset & 0x3F;
				
				//test ray grid location for collision
				s32 x = (fix2int(rayX >> 6));
				s32 y = (fix2int(rayY >> 6));
				bHit = worldMap[y][x];
			}
			

			//find nearest intersection
			//collision has occurred find shortest distance
			fixed wallDist = 0;
			fixed xDistanceToWall = abs(rayX - playerX);
			fixed yDistanceToWall = abs(rayY - playerY);
			//use greatest distance value for instances where distance == 0
			if (xDistanceToWall > yDistanceToWall)
			{
				s32 angle = castAngle + ANGLE_90;
				if (angle >= ANGLE_360)
				{
					angle -= ANGLE_360;
				}
				//correct perspective to avoid fish eye distortion on walls multiply by 1/cos(theta) or cosec(theta)
				wallDist = abs(fixMul(xDistanceToWall, cosec_lut[angle]>>4));
				
			}
			else
			{
				wallDist = abs(fixMul(yDistanceToWall, cosec_lut[castAngle]>>4));
			}
			fixed dist = fixDiv(wallDist, viewCorrection_lut[i]>>4);
			s32 projectedHeight = fix2int(fixMul(fixDiv(cameraNearPlane, dist), TILE_SIZE));
			s32 textureYOffset = projectedHeight - SCREEN_H;
			textureYOffset = (textureYOffset < 0) ? 0 : textureYOffset;

			projectedHeight = (projectedHeight > SCREEN_H) ? SCREEN_H : projectedHeight;
			s32 drawStart = (-projectedHeight >> 1) + (SCREEN_H >> 1);
			if (drawStart < 0) drawStart = 0;
			s32 drawEnd = (projectedHeight >> 1) + (SCREEN_H >> 1);
			if (drawEnd >= SCREEN_H) drawEnd = SCREEN_H - 1;

			//find the palette index based off the texture offset
			drawVerticalSegment(i, drawStart, projectedHeight, bHit - 1, textureOffset, 16);
			//drawVerticalTexturedLine_M4(i, drawStart, projectedHeight, bHit-1, textureOffset, 16);

			
			
			castAngle+=2;
			if (castAngle >= ANGLE_360)
				castAngle -= ANGLE_360;

		}
		//Process User Input
		PollKeys();

		//Check for Horizontal movement (rotation)
		s32 horizontal = getAxis(HORIZONTAL);
		if (horizontal != 0)
			playerRot += horizontal * (ANGLE_HALF_FOV>>2);

		//This is a bit lazy of me and could have been handled better (dont use degrees use radians and bitwise & to keep within scope)
		if (playerRot < 0)
		{
			playerRot += ANGLE_360;
		}
		else if (playerRot >= ANGLE_360)
		{
			playerRot -= ANGLE_360;
		}
		
		//Check for vertical input (moving forward or backwards)
		s32 vertical = getAxis(VERTICAL);
		if (vertical != 0)
		{
			s32 angle = playerRot + ANGLE_90;
			if (angle >= ANGLE_360)
			{
				angle -= ANGLE_360;
			}

			playerX += fixMul(vertical<<8, fixMul(int2fix(16) ,sin_lut[angle]>>4));
			playerY += fixMul(vertical<<8, fixMul(int2fix(16), sin_lut[playerRot]>>4));
		}
		//Swap image pages
		page_flip();
		

	}

	return 0;
}

void drawBackground()
{
	//draw the background
	u32* screenBuffer = (u32*)getVideoPage();
	//Here we are going to break the background up into a sky and a floor
	//This will use the colours stored in the colour palette from position 0->13
	//The sky will be broken down into 8 colour shades from the palette with the ground broken
	//into 6 colour shades.

	//Iterate through the 14 colours in the palette
	for (s32 i = 0; i < 14; ++i)
	{
		//Remembering in mode 4 that each pixel is only 8bpp and we cannot write to video memory in bytes we have to write in 16 or 32 bit chunks
		//here we are using a u16 and setting the upper half (pixel 0) and lower half (pixel 1) to the same colour palette index
		//we then cast this to a u32 allowing us to write 4 pixels at a time
		//        1st pixel + 2nd pixel + 3rd pixel + 4th pixel;
		u32 val = (i << 24) + (i << 16) + (i << 8) + i;					
		
		s32 lineVal = (i < 8) ? (SCREEN_W >> 1) * 10 : (SCREEN_W >> 1) * 15; //The top half of the screen is the sky with slightly more colour variation
		u32* screenAddr = screenBuffer + (lineVal>>1);
		//using pointer math iterate through our screen memory and set the buffer value to our four pixels until we reach the address to stop
		while (screenBuffer < screenAddr)
		{
			*screenBuffer = val;
			screenBuffer++;
		}
	}
}

#define TEXTURE_H_TILES 6
#define TEXTURE_V_TILES 19
#define TEXTURE_W 64 //this is the width of the texture in pixels one pixel is 8 bits
#define TEXTURE_STRIDE 384 //(TEXTURE_W * TEXTURE_H_TILES) //this is due to the texture being 6x19 tiles in size 64x64 tiles 6*64 = 384
#define TEXTURE_H_STRIDE 24576 // (TEXTURE_STRIDE * TEXTURE_W) //TEXTURE_STRIDE * 64
#define TEXTURE_VO_NUMERATOR (0x400000)

void drawVerticalSegment(s32 a_x, s32 a_y, s32 a_height, s16 a_tileID, s16 a_textureOffset, s16 paletteOffset)
{
	//accessing in 16bit chunks two pixels becomes 1 read. hence width is not 64 it is 32 as 64 8 bit vals = 32 16bit vals
	s32 tileVerticalOffset = (a_tileID / TEXTURE_H_TILES) * TEXTURE_H_STRIDE;
	s32 tileHorizontalOffset = ((a_tileID % TEXTURE_H_TILES) * TEXTURE_W) + (a_textureOffset);
	s32 tileOrigin = tileVerticalOffset + tileHorizontalOffset;
	s32 vertOffset = TEXTURE_VO_NUMERATOR / (a_height << 8); //fixed 8 notation
	
	s16 po = (paletteOffset << 8) + paletteOffset;
	s16* bitmapu16Val = (s16*)(Wolf3DWallsImg_bin);

	drawVerticalTexturedLine_M4(a_x, a_y, a_height, vertOffset, &bitmapu16Val[tileOrigin>>1], TEXTURE_STRIDE >> 1, po);
}