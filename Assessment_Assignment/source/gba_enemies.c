#include "gba_enemies.h"

//Initalise the Enemy Array with all enimies disabled
void InitEnemyMem(){

    //Fill Memory with disabled enimies
    for(u16 i = 0; i < ENEMY_COUNT; i++){
        Enemy newEnemy;
        newEnemy.enabled = false;
        createdEnemies[i] = newEnemy;
    }

}

//Initalise an individual enemy
//a_id - ID of the enemy within the array
//a_sprite - Enemy Sprite Object
//a_worldpos - Postion to start the enemy at
//a_width - Width of the enemy sprite
//a_height - Height of the enemy sprite
extern Enemy* InitEnemy(u8 a_id, SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){
    
    //Check that ID is less than max pickups
    if(a_id > ENEMY_COUNT){
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
    //and where we should be on the screen
    Vector2 zero = {0,0};
    newEnemy.spd.x = GBARandRange(-1 , 2);
    newEnemy.spd.y = GBARandRange(-1 , 2);
    newEnemy.screenPos = zero;

    //Set Health
    newEnemy.health = StartHealth;

    //Enable Enemy
    newEnemy.enabled = true;

    //Add Enemy to array
    createdEnemies[a_id] = newEnemy;
    return &createdEnemies[a_id];

}

//Update all enimies that have been created
void UpdateAllEnemies(){

    //Loop through all enimies in the enemy array and update them
    for(u16 i = 0; i < ENEMY_COUNT; i++){
        UpdateEnemy(&createdEnemies[i]);
    }

}

//Update an individual enemy
//a_enemy - Enemy to Update
void UpdateEnemy(Enemy* a_enemy){

    //Check that enemy is enabled
    if(a_enemy->enabled){

        //If we are not going to collide with a wall keep moving in our current direction
        //else choose a new random direction for us to go in
        if(!AABBWallCollision(a_enemy->worldPos, a_enemy->size, a_enemy->spd.x, a_enemy->spd.y)){
            a_enemy->worldPos.x += a_enemy->spd.x;
            a_enemy->worldPos.y += a_enemy->spd.y;
        }else{
            a_enemy->spd.x = GBARandRange(-1 , 2);
            a_enemy->spd.y = GBARandRange(-1 , 2);
        }

        //---Check if Enemy should be visible----
    
        //Get current screen offset
        Vector2 currentOffset = GetBackgroundOffset(0);

        //Calculate the screen position of this entity
        Vector2 screenPos = {
            a_enemy->worldPos.x - currentOffset.x,
            a_enemy->worldPos.y - currentOffset.y
        };

        //Check if our screen pos is within the bounds of the screen
        if(screenPos.x < SCREEN_W && screenPos.y < SCREEN_H){

            //Set visible
            if(!a_enemy->visible){
                UnHideSpriteObject(a_enemy->sprite, A0_MODE_REG);
                a_enemy->visible = true;
            }

            //Update screen pos
            a_enemy->screenPos = screenPos;
            SetSpriteScreenPos(a_enemy->sprite, screenPos.x, screenPos.y);

            //---------Animate--------
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

            //Make sure sprite is hidden as we are disabled
            if(a_enemy->visible){
                HideSpriteObject(a_enemy->sprite);
                a_enemy->visible = false;
            }
        }
    }

    //Check that we have health, if we don't
    //then visabled
    if(a_enemy->health <= 0){
        a_enemy->enabled = false;
        HideSpriteObject(a_enemy->sprite);
    }
}