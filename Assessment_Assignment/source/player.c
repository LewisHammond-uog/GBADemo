#include "player.h"

//Initalises a player object struct and returns it for further use
//a_sprite - player sprite
//a_worldPos - world position
//a_width - sprite width
//a_height - sprite height
Player InitPlayer(SpriteObject* a_sprite, Vector2 a_worldPos, u8 a_width, u8 a_height){

    //Create player and assign sprite
    Player newPlayer;
    newPlayer.sprite = a_sprite;

    //Set positions - player always starts in the center of the screen
    newPlayer.worldPos = a_worldPos;
    newPlayer.screenPos = a_worldPos;

    //Set sprite width and height values
    Vector2 playerSize = {a_width, a_height};
    newPlayer.size = playerSize;

    //Set visible
    UnHideSpriteObject(a_sprite, A0_MODE_REG);
    newPlayer.visible = true;
    newPlayer.frame = 0;
    newPlayer.frameCounter = Int2Fix(0);

    //Setup Health, Coins and Weapons
    newPlayer.health = 0;
    newPlayer.coins = 0;
    newPlayer.heldWeapons = 0;
    newPlayer.selectedWeapon = None;
    newPlayer.weaponHoldDirection = 1;

    return newPlayer;
}

//Updates the Player Character with movement, collisions
//a_player - Player to Update
void UpdatePlayer(Player* a_player){

    //Check Player input
    s8 vsp = -getAxis(VERTICAL); //Vertical Speed
    s8 hsp = getAxis(HORIZONTAL); //Horizontal Speed
    
    //----Movement----//
    if(vsp != 0){
        //Check Collision
        if(!AABBWallCollision(a_player->worldPos, a_player->size, 0, vsp)){
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
        if(!AABBWallCollision(a_player->worldPos, a_player->size, hsp, 0)){
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

        //Set Horizontal of the sprite
        SetSpriteHorizontalFlip(a_player->sprite, hsp);   
        
        //Update Direction of the held weapon
        a_player->weaponHoldDirection = hsp;
    }

    //----Animation----//
    if(vsp !=0 || hsp!=0){
        //Advance frame counter
        a_player->frameCounter += FrameProgression;
        
        //Check if frame counter is > 1
        if(Fix2Int(a_player->frameCounter) > 1){
            //Advance Frame by 8
            a_player->frame += 4 << 1;

            //Check if frame is over our frame count and reset
            if(a_player->frame > PlayerFrames){
                a_player->frame = 0;
            }

            //Reset Frame Counter
            a_player->frameCounter = Int2Fix(0);
        }

    }else{
        a_player->frame = 0;
    }

    //Set Sprite Frame in Mem
    a_player->sprite->attr2 = SetSpriteObjectAttribute2(PlayerSpriteLocation + a_player->frame, A2_PRIORITY_0, 0);

    //Set Sprite Screen Position
    SetSpriteScreenPos(a_player->sprite, a_player->screenPos.x, a_player->screenPos.y);
    
    //Update Held Weapon Position
    SetSpriteScreenPos(a_player->weaponSprite, a_player->screenPos.x + (PlayerWeaponHoldDist * a_player->weaponHoldDirection), a_player->screenPos.y);

    //Check if we are want to change weapon
    if(KeyHit(L) || KeyHit(R)){
        if(a_player->selectedWeapon == SwordSmall){
            a_player->selectedWeapon = None;
            HideSpriteObject(a_player->weaponSprite);
        }else if(a_player->selectedWeapon == None && CheckWeapon(a_player->heldWeapons, SwordSmall)){
            a_player->selectedWeapon = SwordSmall;
            UnHideSpriteObject(a_player->weaponSprite, A0_MODE_REG);
        }
    }

    //Do Pickup Check
    if(KeyHit(Key_Pickup)){
        CheckForPickup(a_player);
    }

    //Do Attack Check
    if(KeyHit(Key_Attack)){
        CheckForAttack(a_player);
    }
}

//Checks if there are any items that can be picked up and picks them up
void CheckForPickup(Player* a_player){

    //Loop through all pickups and check if we are close enough to that pickup, pick it up
    for(u8 i = 0; i < MAX_PICKUPS; i++){
        Pickup* currentPickup = &createdPickups[i];
        //Check that we are both in range and the pickup is enabled
        if(Vector2DistSqrd(currentPickup->worldPos, a_player->worldPos) < (currentPickup->pickupRange * currentPickup->pickupRange) && currentPickup->enabled){
            //Pick up item
            PickupItem(a_player,currentPickup);
        }
    }

}

//Checks if there are any enimies that can be attacked and attacks them
void CheckForAttack(Player* a_player){

    //Check that the player has a weapon
    if(a_player->heldWeapons == 0){
        return;
    }

    //Setup Damage, set by whichever weapon we have
    s8 damage = 0;
    s16 range = 0;

    if(a_player->selectedWeapon == SwordSmall){
        damage = WeaponDamange_SwordSmall;
        range = WeaponRange_SwordSmall;
    }

    //Apply Attack on Nearby Enimies
    //Loop through all enemy and check if we are close enough to that enemy, attack it
    for(u8 i = 0; i < MAX_ENEMIES; i++){
        Enemy* currentEnemy = &createdEnemies[i];
        if(Vector2DistSqrd(currentEnemy->worldPos, a_player->worldPos) < (range*range) && currentEnemy->enabled){
            //Reduce Enemy Health
            currentEnemy->health -= damage;
        }
    }
    
}

//Pick up an item
void PickupItem(Player* a_player, Pickup* a_pickup){

    //Determine Pickup Type and apply action based on that
    switch (a_pickup->pickupType)
    {
    case Health:
        a_player->health += a_pickup->pickupSub;
        break;
    case Coin:
        a_player->coins += a_pickup->pickupSub;
    case Weapon:
        //Activate Weapon for player
        a_player->heldWeapons =  GiveWeapon(a_player->heldWeapons, a_pickup->pickupSub);
        break;
    default:
        break;
    }

    //Disable Pickup
    DisablePickup(a_pickup);

}

//Give the player a given weapon
u8 GiveWeapon(u8 a_weapons, WeaponType a_toActivate){
    return a_weapons | a_toActivate;
}

//Check if the player has a given weapon
bool CheckWeapon(u8 a_weapons, WeaponType a_toCheck){
    return (a_weapons & a_toCheck);
}



//Checks if we should scroll the map
//a_player - player to check
//a_hsp - Intended Horizontal Speed
//a_vsp - Intended Vertical Speed
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
