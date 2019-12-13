
#ifndef __GBA_ENTITIY_H__
#define __GBA_ENTITIY_H__

#include <stdio.h>
#include <string.h>

#include "gba_math.h"
#include "gba_backgrounds.h"
#include "gba_drawing.h"
#include "gba_sprites.h"
#include "gba_input.h"

//Struct for a pickup-able object. Has base entity that 
//has drawing animation frame and position
typedef struct Pickup{
	SpriteObject* sprite;
	Vector2 screenPos; //Position on the screen
	Vector2 worldPos; //Position in the world

	//Currently visible/pickup able
	bool visible;
	bool enabled;

    //Width and height
    u8 spriteWidth;
    u8 spriteHeight;

	u16 pickupRange; //Range we can pickup from
	u16 pickupType; //Type of pickup - bow, sword, health etc.

	void (*actionFP)(u8); //Function Pointer to pickup action 
}PACKED(4) Pickup;

//Struct for Player - Almost just an entity but has lots
//of operational differences
typedef struct Player{
	SpriteObject* sprite;
	Vector2 screenPos; //Position on the screen
	Vector2 worldPos; //Position in the world
	u8 frame; //Current Animation Frame
	fixed frameCounter; //Counter for current frame time

	//Currently visible/pickup able
	bool visible;

    //Width and height
    u8 spriteWidth;
    u8 spriteHeight;
}PACKED(4) Player, Enemy;

//Array to store all of the created Pickups
#define MAX_PICKUPS 32
Pickup* createdPickups[MAX_PICKUPS];

extern void InitPickupMem();
extern void UpdateAllPickups();
extern void UpdatePickup(Pickup* a_entity);

extern Pickup InitPickup(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height, u16 a_pickupRange);
extern void DestoryPickup(Pickup* a_pickup);
extern u8 CheckCollision(Vector2* pos, int addx, int addy);

#endif //__GBA_ENTITIY_H__