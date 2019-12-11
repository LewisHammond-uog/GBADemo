#include "player.h"

//Initalises a player object struct and returns it for further use
Player InitPlayer(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){

    //Create player and assign sprite
    Player newPlayer;
    newPlayer.sprite = a_sprite;

    //Set positions - player always starts in the center of the screen
    newPlayer.worldPos = a_worldPos;
    newPlayer.screenPos = a_worldPos;

    //Make sure that the player is at the position that we say it is
    s32 x = newPlayer.worldPos.x + newPlayer.screenPos.x;
    s32 y = newPlayer.worldPos.y + newPlayer.screenPos.y;

    //Set sprite width and height values
    newPlayer.spriteWidth = a_width;
    newPlayer.spriteHeight = a_height;

    return newPlayer;
}

//Updates the Player Character with movement, collisions
void UpdatePlayer(Player* a_player){

    //Check Player input
    s8 vsp = -getAxis(VERTICAL); //Vertical Speed
    s8 hsp = getAxis(HORIZONTAL); //Horizontal Speed

    //Calculate Position to check collision at
    Vector2 collsionCheckPos;
    collsionCheckPos.x = a_player->worldPos.x + (a_player->spriteWidth >> 1);
    collsionCheckPos.y = a_player->worldPos.y + (a_player->spriteHeight >> 1);
    
    
    if(vsp != 0){
        //Check Collision
        if(CheckCollision(&collsionCheckPos,0,vsp) != 1){
            //Check if we are on the edge of the screen
            if(CheckMapScroll(a_player, 0, vsp) && MapScrollInBounds(0, 0, vsp)){
                //Scroll the background
                MoveBackground(0, 0, vsp);
                MoveBackground(1, 0, vsp);
                a_player->worldPos.y += vsp;
            }else{
                //Move the player on the screen
                a_player->worldPos.y += vsp;
                a_player->screenPos.y += vsp;
            }
        }
    }

    if(hsp != 0){
        //Check Collision
        if(CheckCollision(&collsionCheckPos,hsp,0) != 1){
            //Check if we are on the edge of the screen
            if(CheckMapScroll(a_player, hsp, 0) && MapScrollInBounds(0, hsp, 0)){
                //Scroll the background
                MoveBackground(0, hsp, 0);
                MoveBackground(1, hsp, 0);
                a_player->worldPos.x += hsp;
            }else{
                //Move the player on the screen
                a_player->worldPos.x += hsp;
                a_player->screenPos.x += hsp;
            }
        }
    }

    //Set Sprite Screen Position
    SetSpriteScreenPos(a_player->sprite, a_player->screenPos.x, a_player->screenPos.y);
}


//Checks if we should scroll the map
bool CheckMapScroll(Player* a_player, s8 a_hsp, s8 a_vsp){

    //Check each direction and if we are heading in that direction and
    //are at the limits of the screen we are allow to go to then
    //return that the bg should scroll

    if(a_vsp > 0 && a_player->screenPos.y > SCREEN_H - vScrollLimit){
        return true;
    }
    
    if(a_vsp < 0 && a_player->screenPos.y < vScrollLimit){
        return true;
    }

    if(a_hsp > 0 && a_player->screenPos.x > SCREEN_W - hScrollLimit){
        return true;
    }
    
    if(a_hsp < 0 && a_player->screenPos.x < hScrollLimit){
        return true;
    }
    return false;
}

//Check a collision at a point infront of the player (addx,)
u8 CheckCollision(Vector2* pos, int addx, int addy){
	int gridx = (pos->x/8) + addx;
    int gridy = (pos->y/8) + addy;
    return bgCollision[((64*gridy) + gridx)];
}