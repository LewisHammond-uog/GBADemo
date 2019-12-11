#include "gba_entity.h"

//Intialises an entity within the world
extern Entity InitEntity(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){
    
    //Assign Sprite
    Entity newEntity;
    newEntity.sprite = a_sprite;

    //Hide sprite object as we don't know if it will be on screen
    //HideSpriteObject(a_sprite);

    //Set world pos
    newEntity.worldPos = a_worldPos;

    //Set screen pos to 0 as we need to work out if we are visible on screen or not
    Vector2 zero = {0,0};
    newEntity.screenPos = zero;

}

//Check a collision at a point infront of the player 
//a_pos - Current Player Position
//a_addX - Position difference from player (X Direction)
//a_addY - Position difference from player (Y Direction)
u8 CheckCollision(Vector2* a_pos, int a_addX, int a_addY){
	int gridx = (a_pos->x/8) + a_addX;
    int gridy = (a_pos->y/8) + a_addY;
    return bgCollision[((64*gridy) + gridx)];
}