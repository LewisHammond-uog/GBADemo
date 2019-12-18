#include "gba_enemies.h"


void InitEnemyMem(){

    //Set memory to zero - removing existing pickups
    for(u16 i = 0; i < MAX_ENEMIES; i++){
        Enemy newEnemy;
        newEnemy.enabled = false;
        createdEnemies[i] = newEnemy;
    }

}

extern Enemy* InitEnemy(u8 a_id, SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){
    
    //Check that ID is less than max pickups
    if(a_id > MAX_ENEMIES){
        return NULL;
    }

    //Assign Sprite
    Enemy newEnemy;
    newEnemy.sprite = a_sprite;

    //Hide sprite object as we don't know if it will be on screen
    HideSpriteObject(a_sprite);
    newEnemy.visible = false;

    //Set sprite width and height values
    Vector2 enemySize = {a_width, a_height};
    newEnemy.size = enemySize;

    //Set world pos
    newEnemy.worldPos = a_worldPos;
    //Set screen pos to 0 as we need to work out if we are visible on screen or not
    Vector2 zero = {0,0};
    newEnemy.spd.x = GBARandRange(-1 , 2);
    newEnemy.spd.y = GBARandRange(-1 , 2);
    newEnemy.screenPos = zero;

    newEnemy.health = 3;

    //Set Size
    

    //Enable Enemy
    newEnemy.enabled = true;

    //Add Enemy to array
    createdEnemies[a_id] = newEnemy;
    return &createdEnemies[a_id];

}

void UpdateAllEnemies(){

    //Set memory to zero - removing existing pickups
    for(u16 i = 0; i < MAX_ENEMIES; i++){
        UpdateEnemy(&createdEnemies[i]);
    }

}

void UpdateEnemy(Enemy* a_enemy){

    if(a_enemy->enabled){
        if(!AABBWallCollision(a_enemy->worldPos, a_enemy->size, a_enemy->spd.x, a_enemy->spd.y)){
            a_enemy->worldPos.x += a_enemy->spd.x;
            a_enemy->worldPos.y += a_enemy->spd.y;
        }else{
            a_enemy->spd.x = GBARandRange(-1 , 2);
            a_enemy->spd.y = GBARandRange(-1 , 2);
        }

    //Check if Enemy should be visible
   
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

            //Update screen pos
            a_enemy->screenPos = screenPos;
            SetSpriteScreenPos(a_enemy->sprite, screenPos.x, screenPos.y);

            //Animate
            //Advance frame counter
            a_enemy->frameCounter += FrameProgression;
            
            //Check if frame counter is > 1
            if(Fix2Int(a_enemy->frameCounter) > 1){
                //Advance Frame by 8
                a_enemy->frame += 4 << 1;

                //Check if frame is over our frame count and reset
                if(a_enemy->frame > EnemyFrames){
                    a_enemy->frame = 0;
                }

                //Reset Frame Counter
                a_enemy->frameCounter = Int2Fix(0);
            }

            //Set Sprite Frame in Mem
            a_enemy->sprite->attr2 = SetSpriteObjectAttribute2(EnemySpriteLocation + a_enemy->frame, A2_PRIORITY_0, 0);

        }else{
            //Make sure sprite is hidden
            if(a_enemy->visible){
                HideSpriteObject(a_enemy->sprite);
                a_enemy->visible = false;
            }
        }
    }

    //If we have no health then disable this object
    if(a_enemy->health <= 0){
        a_enemy->enabled = false;
        HideSpriteObject(a_enemy->sprite);
    }
}