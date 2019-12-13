#include "gba_entity.h"

//Init Pickup Mem
extern void InitPickupMem(){
    
    //Set memory to zero - removing existing pickups
    for(u16 i = 0; i < MAX_PICKUPS - 1; i++){
        Pickup newPickup;
        createdPickups[i] = &newPickup;
        createdPickups[i]->enabled = false;
    }
    
}

//Functions for removing all current pickups and entites

//Functions to Update all Pickups and Entites
void UpdateAllPickups(){

    //Loop though all pickups, null check them update them
    for(u16 i = 0; i < MAX_PICKUPS; i++){
        Pickup* currentPickup = createdPickups[i];

        //if(currentPickup->enabled){
            UpdatePickup(currentPickup);
        //}
    }

}

//Intialises an pickup within the world
Pickup InitPickup(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height, u16 a_pickupRange){
    
    //Assign Sprite
    Pickup newPickup;
    newPickup.sprite = a_sprite;

    //Hide sprite object as we don't know if it will be on screen
    HideSpriteObject(a_sprite);
    newPickup.visible = false;

    //Set world pos
    newPickup.worldPos = a_worldPos;

    //Set screen pos to 0 as we need to work out if we are visible on screen or not
    Vector2 zero = {0,0};

    //Set pickup range
    newPickup.pickupRange = a_pickupRange;

    newPickup.enabled = true;

    return newPickup;
}


void UpdatePickup(Pickup* a_entity){

    if(a_entity->enabled){
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
}

void DestoryPickup(Pickup* a_pickup){
    HideSpriteObject(a_pickup->sprite);
    a_pickup->visible = false;
    a_pickup->enabled = false;
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