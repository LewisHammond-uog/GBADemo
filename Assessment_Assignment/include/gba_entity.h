
#ifndef __GBA_ENTITIY_H__
#define __GBA_ENTITIY_H__

#include "gba_math.h"
#include "gba_backgrounds.h"
#include "gba_drawing.h"
#include "gba_sprites.h"

//Struct for player object
typedef struct Entity{
	SpriteObject* sprite;
	Vector2 screenPos; //Position on the screen
	Vector2 worldPos; //Position in the world
	u8 frame; //Current Animation Frame
	fixed frameCounter; //Counter for current frame time

	//Currently visible
	bool visible;

    //Width and height
    u8 spriteWidth;
    u8 spriteHeight;
}PACKED(4) Entity, Player, Enemy;

extern Entity InitEntity(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height);
extern void UpdateEntity(Entity* a_entity);
extern u8 CheckCollision(Vector2* pos, int addx, int addy);

#endif //__GBA_ENTITIY_H__