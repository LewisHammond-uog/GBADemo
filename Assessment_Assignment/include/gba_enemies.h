#ifndef __GBA_ENEMIES_H__
#define __GBA_ENEMIES_H__

#include "gba_entity.h"

//Struct for Enemy
typedef struct Enemy{
	SpriteObject* sprite;

	Vector2 screenPos; //Position on the screen
	Vector2 worldPos; //Position in the world

	Vector2 spd;

	//Currently visible
	bool visible;
    bool enabled;

	s8 health;

    //Width and height
    Vector2 size;
}PACKED(4) Enemy;

//Array to store enimies 
#define MAX_ENEMIES 16
Enemy createdEnemies[MAX_ENEMIES];

extern void InitEnemyMem();
extern Enemy* InitEnemy(u8 a_id, SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height);
extern void UpdateAllEnemies();
extern void UpdateEnemy(Enemy* a_enemy);

#endif //__GBA_ENEMIES_H__