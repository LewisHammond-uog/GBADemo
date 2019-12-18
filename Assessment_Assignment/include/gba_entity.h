
#ifndef __GBA_ENTITIY_H__
#define __GBA_ENTITIY_H__

#include <stdio.h>
#include <string.h>

#include "gba_math.h"
#include "gba_backgrounds.h"
#include "gba_drawing.h"
#include "gba_sprites.h"
#include "gba_input.h"
#include "gba_particles.h"

typedef enum Pickups{
	Health,
	Weapon,
	Coin
} PickupType;

//Enum for weapons
typedef enum Weapons{
	None = 0x00,
	SwordSmall = 0x01,
} WeaponType;

#define WeaponCount 0x4

//Weapon Damages
#define WeaponDamange_SwordSmall 1
#define WeaponDamange_SwordLarge 3
#define WeaponDamange_SwordBow 0

#define WeaponRange_SwordSmall 20
#define WeaponRange_SwordLarge 100
#define WeaponRange_Bow 0

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
	enum Pickups pickupType; //Type of pickup - bow, sword, health etc.
	u8 pickupSub; //Sub Type of pickup - for health and coins this is the
				  //number of coin/health. For weapons this is the weapon type

	void (*actionFP)(u8); //Function Pointer to pickup action 
}PACKED(4) Pickup;

//Struct for Player - Almost just an entity but has lots
//of operational differences
typedef struct Player{
	SpriteObject* sprite;
	SpriteObject* weaponSprite;
	Vector2 screenPos; //Position on the screen
	Vector2 worldPos; //Position in the world
	
	u16 frame; //Current Animation Frame
	fixed frameCounter; //Counter for current frame time

	//Currently visible/pickup able
	bool visible;

	u8 health;
	u8 coins;
	u8 heldWeapons;
	WeaponType selectedWeapon;
	u8 weaponHoldDirection; //Side of the player to hold the weapon on (-1,1) - updated by hsp

    //Width and height
    Vector2 size;
}PACKED(4) Player;

//Array to store all of the created Pickups
#define MAX_PICKUPS 16
Pickup createdPickups[MAX_PICKUPS];

extern void InitPickupMem();
extern void UpdateAllPickups();
extern void UpdatePickup(Pickup* a_entity);

extern Pickup* InitPickup(u8 a_id, SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height, u16 a_pickupRange);
extern void SetPickupType(Pickup* a_pickup, PickupType a_type, u8 a_subType);
extern void DisablePickup(Pickup* a_pickup);

extern u8 AABBWallCollision(Vector2 a_pos, Vector2 a_size, s8 a_hsp, s8 a_vsp);
extern u8 CheckCollision(Vector2* pos, int addx, int addy);

#endif //__GBA_ENTITIY_H__