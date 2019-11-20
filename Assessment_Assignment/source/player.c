#include "player.h"

//Initalises a player object struct and returns it for further use
Player InitPlayer(SpriteObject* a_sprite, Position* a_worldPos, u8 a_width, u8 a_height){

    //Create player and assign sprite
    Player newPlayer;
    newPlayer.sprite = a_sprite;

    //Set positions - player always starts in the center of the screen
    newPlayer.worldPos = a_worldPos;
    newPlayer.screenPos->x = (SCREEN_W >> 1) - (a_width >> 1);
    newPlayer.screenPos->y = (SCREEN_H >> 1) - (a_height >> 1);

    //Make sure that the player is at the position that we say it is
    s32 x = newPlayer.worldPos->x + newPlayer.screenPos->x;
    s32 y = newPlayer.worldPos->y + newPlayer.screenPos->y;

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
    Position collsionCheckPos;
    collsionCheckPos.x = a_player->worldPos->x + (a_player->spriteWidth >> 1);
    collsionCheckPos.y = a_player->worldPos->y + (a_player->spriteHeight >> 1);
    
    //Check Collision
    if(CheckCollision(collsionCheckPos.x, collsionCheckPos.y,0,vsp) != 1){
        a_player->worldPos->y += vsp;
    }
    if(CheckCollision(collsionCheckPos.x, collsionCheckPos.y,hsp,0) != 1){
        a_player->worldPos->x += hsp;
    }

    //Set Sprite Screen Position
    SetSpriteScreenPos(a_player->sprite, a_player->worldPos->x, a_player->worldPos->y);
}

//Check a collision at a point infront of the player (addx,)
u8 CheckCollision(int x, int y, int addx, int addy){
	int gridx = (x/8) + addx;
    int gridy = (y/8) + addy;
    return bgCollision[((64*gridy) + gridx)];
}