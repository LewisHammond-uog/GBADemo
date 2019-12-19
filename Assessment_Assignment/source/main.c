#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_math.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_input.h"
#include "gba_tiles.h"
#include "gba_sprites.h"
#include "gba_backgrounds.h"

#include "player.h"

#include <string.h>

#include "LVL1BG_Externs.h"
#include "GameSprites.h"

int main()
{
	//Register that we want to catch a v-blank
	register_vblank_isr();

	//set GBA rendering context to MODE 0 Tile Rendering and enable 1D sprites enable backgrounds 0 & 1
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D | BGMODE_0;

	#pragma region Backgronds

	/*-------BACKGROUNDS-------*/
	//Generate Background Register Controller Info
	u16 bg0RegData = SetBGControlRegister( 1, 0, 0, 0, 16, 0, BG_REG_SIZE_64x32);

	//Background Pallet and Tile info
	PalletInfo bgPallet = {bgPalette, bgPaletteSize};
	TilesInfo tiles = {bgTiles, bgTilesSize};

	//Initalise BG Memory and load backgrounds into memory
	InitBGMem(0, &bgPallet, &tiles);
	InitBackground(0, 8, 64, 32, bgMap, bg0RegData);

	/*-------END OF BACKGROUNDS-------*/

	#pragma endregion

	#pragma region Sprites
	/*-------SPRITES-------*/

	//Copy sprite pallet in to memory
	memcpy(PAL_SP_BLOCK(0), GameSpritesPal, GameSpritesPalLen);
	//Copy all of the sprites in to memory
	memcpy(sprite_tile_address(0), GameSpritesTiles, GameSpritesTilesLen);

	//Initalise the Object Buffer
	oam_init(obj_buffer, 128);

	/*------
	OAM MEMORY LAYOUT

	These are the locations in OAM that are used for different types of object.
	When followed sprite memory is never overwritten and each type of sprite object
	we have is within its own OAM section.

	LOCATION  SPRITE
	0 		= Player
	1 		= Player Held Weapon
	2 - 18 	= Particles
	19 - 35	= Pickups
	36 - 52	= Enimies
	------*/
	const s8 playerSpriteOAM = 0;
	const s8 playerHeldOAM = 1;
	const s8 particleStartOAM = 2;
	const s8 pickupStartOAM = 19;
	const s8 enemyStartOAM = 36;

	/*
	Load all of the sprites that we want to use in to memory
	for sprites that are used mutiple times in the world we create
	an inital sprite and then use a for loop to duplicate them 
	in to adjacent memory slots for however many we need.
	This enables the same image to apear in mutiple locations in the map
	*/

	//Player Sprite
	SpriteObject* playerSprite = &obj_buffer[playerSpriteOAM];
	SetupSprite(playerSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, A1_SIZE_1), 
		SetSpriteObjectAttribute2(PlayerSpriteLocation, A2_PRIORITY_0, 0));

	//Player Held Weapon Sprite
	//Initalised to disabled as it won't be visible at the start
	SpriteObject* playerHeldSprite = &obj_buffer[playerHeldOAM];
	SetupSprite(playerHeldSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_DISABLE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, A1_SIZE_1), 
		SetSpriteObjectAttribute2(SwordPickupLocation, A2_PRIORITY_0, 0));

	//Sprite for particles
	//is duplicated by InitParticleSystem Function
	SpriteObject* particleSprite = &obj_buffer[particleStartOAM];
	SetupSprite(particleSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, A1_SIZE_1), 
		SetSpriteObjectAttribute2(ParticleSpriteLocation, A2_PRIORITY_0, 0));

	//Coin, Heart and Weapon Pickup Sprites
	SpriteObject* coinSprite = &obj_buffer[pickupStartOAM];
	SetupSprite(coinSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_DISABLE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, A1_SIZE_1), 
		SetSpriteObjectAttribute2(CoinPickupLocation, A2_PRIORITY_0, 0));
	SpriteObject* heartSprite = &obj_buffer[pickupStartOAM + COIN_PICKUP_COUNT];
	SetupSprite(heartSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_DISABLE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, A1_SIZE_1), 
		SetSpriteObjectAttribute2(HeartPickupLocation, A2_PRIORITY_0, 0));
	SpriteObject* weaponSprite = &obj_buffer[pickupStartOAM + COIN_PICKUP_COUNT + HEART_PICKUP_COUNT];
	SetupSprite(weaponSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_DISABLE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, A1_SIZE_1), 
		SetSpriteObjectAttribute2(SwordPickupLocation, A2_PRIORITY_0, 0));

	//Duplicate the sprites for each pickup in to OAM so that we have a seperate sprite
	//for each pickup
	s8 currentOAMPos = pickupStartOAM; //Current position in OAM starting at pickup start
	for(s8 i = 0; i < COIN_PICKUP_COUNT; ++i){
		obj_buffer[currentOAMPos++] = *coinSprite;
	}
	for(s8 i = 0; i < HEART_PICKUP_COUNT; ++i){
		obj_buffer[currentOAMPos++] = *heartSprite;
	}
	for(s8 i = 0; i < SWORD_PICKUP_COUNT; ++i){
		obj_buffer[currentOAMPos++] = *weaponSprite;
	}

	//Enemy Sprite
	SpriteObject* enemySprite = &obj_buffer[enemyStartOAM];
	SetupSprite(enemySprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_DISABLE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, 1), 
		SetSpriteObjectAttribute2(EnemySpriteLocation, A2_PRIORITY_0, 0));

	//Duplicate the sprite in OAM so that we have a seperate object for each enemy
	for(s8 i = 1; i < ENEMY_COUNT; ++i){
		obj_buffer[enemyStartOAM + i] = *enemySprite;
	}

	/*--------END OF SPRITES-------*/

	#pragma endregion
	
	#pragma region Particles
	/*-------PARTICLES------*/
	
	//Create an emitter and initalise particles. This particle
	//system will follow the player around the map
	Emitter emitter;
	emitter.x = Int2Fix(100);
	emitter.y = Int2Fix(100);
	ParticleSystem playerParticles = InitParticleSystem(&emitter, *particleSprite);
	
	/*-------END OF PARTICLES------*/
	#pragma endregion
	
	#pragma region Object Intitalisation

	//Initalise Player to a custom position within the map
	Vector2 playerStartPos;
	playerStartPos.x = 87;
	playerStartPos.y = 46;
	Player playerObject = InitPlayer(playerSprite, playerStartPos, 16, 16);
	playerObject.weaponSprite = playerHeldSprite;

	//Initalise Pickup Memory and create pickups
	InitPickupMem();
	Vector2 coinPositions[COIN_PICKUP_COUNT] = {{65, 23}, {74, 169}, {394, 178}, {464, 28}};
	Vector2 heartPositions[HEART_PICKUP_COUNT] = {{65, 72} , {220, 196}}; 
	Vector2 swordPositions[SWORD_PICKUP_COUNT] = {{130, 50}};

	//Var to increment the ID of the pickup so that it can be assigned
	//to the Pickup Array within the gba_entity file
	s8 pickupID = 0;
	Pickup* currentPickup;

	//Loop through all of the types of pickups and initalise them
	for(s8 i = 0; i < COIN_PICKUP_COUNT; ++i){
		currentPickup = InitPickup(pickupID, &obj_buffer[pickupStartOAM + pickupID], coinPositions[i], 16, 16, DEFAULT_PICKUP_RANGE);
		SetPickupType(currentPickup, Coin, 1);
		pickupID++;
	}
	for(s8 i = 0; i < HEART_PICKUP_COUNT; ++i){
		currentPickup = InitPickup(pickupID, &obj_buffer[pickupStartOAM + pickupID], heartPositions[i], 16, 16, DEFAULT_PICKUP_RANGE);
		SetPickupType(currentPickup, Health, 1);
		pickupID++;
	}
	for(s8 i = 0; i < SWORD_PICKUP_COUNT; ++i){
		currentPickup = InitPickup(pickupID, &obj_buffer[pickupStartOAM + pickupID], swordPositions[i], 16, 16, DEFAULT_PICKUP_RANGE);
		SetPickupType(currentPickup, Weapon, SwordSmall);
		pickupID++;
	}

	//Loop and create enemies at correct positions
	InitEnemyMem();
	Vector2 enemyPositions[ENEMY_COUNT] = {{57,165}, {99, 165}, {355,151}, {442,151}, {355,200}, {442,200}};
	for(s8 i = 0; i < ENEMY_COUNT; ++i){
		InitEnemy(i, &(obj_buffer[enemyStartOAM + i]), enemyPositions[i], 16, 16);
	}


	#pragma endregion

	//Game Forever Loop
	while (1) { //loop forever
		//Wait for VBlank before we do any updates
		vblank_int_wait();

		//Get the keys that have been pressed these are used within
		//player update function
		PollKeys();

		//Update Player, Pickups and Enimies
		UpdatePlayer(&playerObject);
		UpdateAllPickups();
		UpdateAllEnemies();
		
		//Update player particle emitter to player location
		UpdateParticleSystem(&playerParticles, &emitter);
		emitter.x = Int2Fix(playerObject.screenPos.x);
		emitter.y = Int2Fix(playerObject.screenPos.y);

		//Copy sprites from the buffer in to OAM
		oam_copy(MEM_OAM, obj_buffer, 128);
	}
	return 0;
}

