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

    //Set sprite width and height values
    newPlayer.a_spriteWidth = a_width;
    newPlayer.a_spriteHeight = a_height;

    return newPlayer;
}

//Updates the Player Character with movement, collisions
void UpdatePlayer(SpriteObject* a_sprite){

}