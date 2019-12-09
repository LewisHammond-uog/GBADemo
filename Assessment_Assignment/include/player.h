#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gba_sprites.h"
#include "gba_drawing.h"
#include "gba_input.h"
#include "BG_Externs.h"
#include "gba_math.h"
#include "gba_backgrounds.h"

//Struct for player object
typedef struct Player{
	SpriteObject* sprite;
	Vector2 screenPos; //Position on the screen
	Vector2 worldPos; //Position in the world
	u8 frame; //Current Animation Frame
	fixed frameCounter; //Counter for current frame time

    //Width and height
    u8 spriteWidth;
    u8 spriteHeight;
}PACKED(4) Player;

//How close we can get to the edge of the screnn before we start scolling
#define hScrollLimit 116
#define vScrollLimit 76

//Player Update Functions
extern Player InitPlayer(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height);
extern void UpdatePlayer(Player* a_sprite);
extern u8 CheckCollision(Vector2* pos, int addx, int addy);


#endif //__PLAYER_H__