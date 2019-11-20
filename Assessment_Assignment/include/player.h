#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gba_sprites.h"
#include "gba_drawing.h"
#include "gba_input.h"
#include "BG_Externs.h"

//Struct for player object
typedef struct Player{
	SpriteObject* sprite;
	Position* screenPos; //Position on the screen
	Position* worldPos; //Position in the world
	u8 frame; //Current Animation Frame
	fixed frameCounter; //Counter for current frame time

    //Width and height
    u8 spriteWidth;
    u8 spriteHeight;
}PACKED(4) Player;

//Player Update Functions
extern Player InitPlayer(SpriteObject* a_sprite, Position* a_worldPos, u8 a_width, u8 a_height);
extern void UpdatePlayer(Player* a_sprite);
extern u8 CheckCollision(int x, int y, int addx, int addy);


#endif //__PLAYER_H__