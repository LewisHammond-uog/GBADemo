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
            a_player->worldPos.y += vsp;

        }
        //Check if we are on the edge of the screen
        if(SCREEN_H - (a_player->screenPos.y + vsp) < vScrollLimit || a_player->screenPos.y + vsp < vScrollLimit){
            //Scroll the background
            MoveBackground(0, 0, vsp);
            MoveBackground(1, 0, vsp);

        }else{
            //Move the player on the screen
            a_player->screenPos.y += vsp;
        }

    }


    if(hsp != 0){
        if(CheckCollision(&collsionCheckPos,hsp,0) != 1){
            a_player->worldPos.x += hsp;

            //Check if we are on the edge of the screen
            if(SCREEN_W - (a_player->screenPos.x + hsp) < hScrollLimit || (a_player->screenPos.x + hsp) < hScrollLimit){
                //Scroll the background
                MoveBackground(0, hsp, 0);
                MoveBackground(1, hsp, 0);

            }else{
                //Move the player on the screen
                a_player->screenPos.x += hsp;
            }
        }
    }
    

    //Set Sprite Screen Position
    SetSpriteScreenPos(a_player->sprite, a_player->screenPos.x, a_player->screenPos.y);
}

//Check a collision at a point infront of the player (addx,)
u8 CheckCollision(Vector2* pos, int addx, int addy){
	int gridx = (pos->x/8) + addx;
    int gridy = (pos->y/8) + addy;
    return bgCollision[((64*gridy) + gridx)];
}