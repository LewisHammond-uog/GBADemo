#include "gba_enemies.h"


extern Enemy* InitEnemy(u8 a_id, SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){
    
    //Check that ID is less than max pickups
    if(a_id > MAX_PICKUPS){
        return;
    }

    //Assign Sprite
    Enemy newEnemy;
    newEnemy.sprite = a_sprite;

    //Hide sprite object as we don't know if it will be on screen
    HideSpriteObject(a_sprite);
    newEnemy.visible = false;

    //Set world pos
    newEnemy.worldPos = a_worldPos;
    //Set screen pos to 0 as we need to work out if we are visible on screen or not
    Vector2 zero = {0,0};

    //Enable Enemy
    newEnemy.enabled = true;

    //Add Enemy to array
    createdEnemies[a_id] = newEnemy;
    return &createdEnemies[a_id];

}


void UpdateEnemy(Enemy* a_enemy){

    //Random Walk
    s8 vsp = GBARandRange(-1 , 1);
    s8 hsp = GBARandRange(-1 , 1);

    if(CheckCollision(&(a_enemy->worldPos), hsp, 0) != 1){
        a_enemy->worldPos.x += hsp;
    }

    if(CheckCollision(&(a_enemy->worldPos), 0, vsp) != 1){
        a_enemy->worldPos.y += vsp;
    }

    //Check if Enemy should be visible
    if(a_enemy->enabled){
        //Get current screen offset
        Vector2 currentOffset = GetBackgroundOffset(0);

        //Calculate the screen position of this entity
        Vector2 screenPos = {
            a_enemy->worldPos.x - currentOffset.x,
            a_enemy->worldPos.y - currentOffset.y
        };


        //Check if our screen pos is within the bounds of the screen
        if(screenPos.x < SCREEN_W && screenPos.y < SCREEN_H){

            //Set visible and position
            if(!a_enemy->visible){
                UnHideSpriteObject(a_enemy->sprite, A0_MODE_REG);
                a_enemy->visible = true;
            }

            a_enemy->screenPos = screenPos;

            //Update screen pos
            SetSpriteScreenPos(a_enemy->sprite, screenPos.x, screenPos.y);

        }else{
            //Make sure sprite is hidden
            if(a_enemy->visible){
                HideSpriteObject(a_enemy->sprite);
                a_enemy->visible = false;
            }
        }
    }

}