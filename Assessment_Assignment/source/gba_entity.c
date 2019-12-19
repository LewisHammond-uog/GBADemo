#include "gba_entity.h"

//Init Pickup Mem
extern void InitPickupMem(){
    
    //Set memory to zero - removing existing pickups
    for(u16 i = 0; i < PICKUP_COUNT - 1; i++){
        Pickup newPickup;
        newPickup.enabled = false;
        createdPickups[i] = newPickup;
    }
    
}

//Functions for removing all current pickups and entites

//Functions to Update all Pickups and Entites
void UpdateAllPickups(){

    //Loop though all pickups, null check them update them
    for(u16 i = 0; i < PICKUP_COUNT; i++){
        Pickup* currentPickup = &createdPickups[i];

        if(currentPickup->enabled){
            UpdatePickup(currentPickup);
        }
    }

}

//Intialises an pickup within the world
Pickup* InitPickup(u8 a_id, SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height, u16 a_pickupRange){
    
    //Check that ID is less than max pickups
    if(a_id > PICKUP_COUNT){
        return NULL;
    }

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
    newPickup.screenPos = zero;

    //Set pickup range
    newPickup.pickupRange = a_pickupRange;
    //Enable Pickup
    newPickup.enabled = true;

    //Add Pickup to array
    createdPickups[a_id] = newPickup;
    return &createdPickups[a_id];
}

//Set the type and sub type of the pickup
void SetPickupType(Pickup* a_pickup, PickupType a_type, u8 a_subType){
    a_pickup->pickupType = a_type;
    a_pickup->pickupSub = a_subType;
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

//Disables a given pickup
//a_pickup - Pickup to disable
void DisablePickup(Pickup* a_pickup){
    HideSpriteObject(a_pickup->sprite);
    a_pickup->visible = false;
    a_pickup->enabled = false;
}

//Check AABB Collsion against a wall
//a_pos - Position to Check
//a_spd - Speed that the object is moving at
//a_size - Size of the object to check
u8 AABBWallCollision(Vector2 a_pos, Vector2 a_size, s8 a_hsp, s8 a_vsp){

    //Get Sprite Cordinates (i.e top left, top right, bottom left, bottom right)
    Vector2 topLeft = a_pos;
    Vector2 topRight = {a_pos.x + a_size.x, a_pos.y};
    Vector2 bottomLeft = {a_pos.x, a_pos.y + a_size.y};
    Vector2 bottomRight = {a_pos.x + a_size.x, a_pos.y + a_size.y};

    //Form Speed Vector
    Vector2 spd = {a_hsp, a_vsp};

    if(CheckCollision(&topLeft, spd.x, spd.y) ||
    CheckCollision(&topRight, spd.x, spd.y)   ||
    CheckCollision(&bottomLeft, spd.x, spd.y) ||
    CheckCollision(&bottomRight, spd.x, spd.y)){
        return 1;
    }

    return 0;
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