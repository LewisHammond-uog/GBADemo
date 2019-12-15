#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "gba_input.h"
#include "gba_enemies.h"

//How close we can get to the edge of the screnn before we start scolling
#define hScrollLimit 116
#define vScrollLimit 76

//Max Health
#define MaxHealth 3

//Amount that the animation progresses per frame
#define FrameProgression 0x80
//Frames in player Animation
#define PlayerFrames 32

//Key Defines
#define Key_Pickup A
#define Key_Attack B

//Player Update Functions
extern Player InitPlayer(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height);
extern void UpdatePlayer(Player* a_sprite);
extern void PickupItem(Player* a_player, Pickup* a_pickup);
u8 GiveWeapon(u8 a_weapons, WeaponType a_toActivate);
bool CheckWeapon(u8 a_weapons, WeaponType a_toCheck);
extern bool CheckMapScroll(Player* a_player, s8 a_hsp, s8 a_vsp);


#endif //__PLAYER_H__