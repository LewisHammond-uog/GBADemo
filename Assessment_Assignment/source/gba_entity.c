#include "gba_entity.h"

//Init Entity Mem

//Init Pickup Mem

//Functions for removing all current pickups and entites

//Functions to Update all Pickups and Entites

//Intialises an entity within the world
Entity InitEntity(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){
    
    //Assign Sprite
    Entity newEntity;
    newEntity.sprite = a_sprite;

    //Hide sprite object as we don't know if it will be on screen
    HideSpriteObject(a_sprite);
    newEntity.visible = false;

    //Set world pos
    newEntity.worldPos = a_worldPos;

    //Set screen pos to 0 as we need to work out if we are visible on screen or not
    Vector2 zero = {0,0};

    return newEntity;
}

Pickup InitPickup(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height, u16 a_pickupRange){

    //Create new Pickup and base entity
    Pickup newPickup;
    newPickup.baseEntity = InitEntity(a_sprite, a_worldPos, a_width, a_height);

    //Set pickup range
    newPickup.pickupRange = a_pickupRange;

    //Return new pickup
    return newPickup;

}

void UpdateEntity(Entity* a_entity){

    //Get current screen offset
    Vector2 currentOffset = GetBackgroundOffset(0);

    //Calculate the screen position of this entity
    Vector2 screenPos = {
        a_entity->worldPos.x - currentOffset.x,
        a_entity->worldPos.y - currentOffset.y
    };

    //Check if our screen pos is within the bounds of the screen
    if(screenPos.x < SCREEN_W && screenPos.y < SCREEN_H){

        //Set visible and position
        if(!a_entity->visible){
            UnHideSpriteObject(a_entity->sprite, A0_MODE_REG);
            a_entity->visible = true;
        }

        a_entity->screenPos = screenPos;

        //Update screen pos
        SetSpriteScreenPos(a_entity->sprite, screenPos.x, screenPos.y);

    }else{
        //Make sure sprite is hidden
        if(a_entity->visible){
            HideSpriteObject(a_entity->sprite);
            a_entity->visible = false;
        }
    }
}

//Updates pickup, seeing if it can be picked up (in range)
void UpdatePickup(Pickup* a_pickup){

    //Update entity
    Entity* entity = &(a_pickup->baseEntity);

    //Update base entity
    UpdateEntity(entity);

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