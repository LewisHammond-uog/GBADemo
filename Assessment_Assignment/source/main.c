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
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D | BGMODE_0 | BGMODE_1;

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

	//Get a position in the direct center of the screen
	s16 sx = (SCREEN_W >> 1) - 8;
	s16 sy = (SCREEN_H >> 1) - 8;

	//Initalise the Object Buffer
	oam_init(obj_buffer, 128);

	//Create Sprites for different items on the screen
	SpriteObject* playerSprite = &obj_buffer[0];
	SetupSprite(playerSprite,  
		SetSpriteObjectAttribute0(sy, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(sx, 0, 1), 
		SetSpriteObjectAttribute2(PlayerSpriteLocation, A2_PRIORITY_0, 0));

		
	SpriteObject* particleSprite = &obj_buffer[1];
	SetupSprite(particleSprite,  
		SetSpriteObjectAttribute0(-1, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(-1, 0, 1), 
		SetSpriteObjectAttribute2(ParticleSpriteLocation, A2_PRIORITY_0, 0));

	SpriteObject* coinSprite = &obj_buffer[2];
	SetupSprite(coinSprite,  
		SetSpriteObjectAttribute0(sy+10, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(sx-5, 0, 1), 
		SetSpriteObjectAttribute2(CoinPickupLocation, A2_PRIORITY_0, 0));

	SpriteObject* heartSprite = &obj_buffer[3];
	SetupSprite(heartSprite,  
		SetSpriteObjectAttribute0(sy, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(sx, 0, 1), 
		SetSpriteObjectAttribute2(EnemySpriteLocation, A2_PRIORITY_0, 0));

	//Sprite to store the currently held player weapon
	//start is as hidden until we know the player has a weapon
	SpriteObject* playerHeldSprite = &obj_buffer[4];
	SetupSprite(playerHeldSprite,  
		SetSpriteObjectAttribute0(0, A0_MODE_DISABLE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(0, 0, 1), 
		SetSpriteObjectAttribute2(SwordPickupLocation, A2_PRIORITY_0, 0));

	/*--------END OF SPRITES-------*/

	#pragma endregion
	
	#pragma region Particles
	/*-------PARTICLES------*/
	
	Emitter emitter;
	emitter.x = Int2Fix(100);
	emitter.y = Int2Fix(100);
	ParticleSystem playerParticles = InitParticleSystem(&emitter, *particleSprite, &obj_buffer[1]);
	
	/*-------END OF PARTICLES------*/
	#pragma endregion
	
	#pragma region Object Intitalisation

	//Initalise Player to the center of the screen
	Vector2 pos;
	pos.x = SCREEN_W >> 1;
	pos.y = (SCREEN_H >> 1) - 20;
	Player p = InitPlayer(playerSprite, pos, 16, 16);
	p.weaponSprite = playerHeldSprite;

	//Initalise Pickup Memory and create a test pickup
	InitPickupMem();
	pos.x = SCREEN_W;
	pos.y = SCREEN_H >> 1;
	Pickup* t = InitPickup(0, coinSprite, pos, 16, 16, 100);
	SetPickupType(t, Weapon, SwordSmall);

	//Initalise Enemy Memory and create a test enemy
	InitEnemyMem();
	Vector2 epos;
	epos.x = SCREEN_W >> 1;
	epos.y = (SCREEN_H >> 1) - 20;
	Enemy* testEnemy = InitEnemy(0, heartSprite, epos, 16, 16);

	#pragma endregion

	while (1) { //loop forever
		vblank_int_wait();

		//Get the keys that have been pressed
		PollKeys();

		//Update Player, Pickups and Enimies
		UpdatePlayer(&p);
		UpdateAllPickups();
		UpdateAllEnemies();
		
		//Update player particles and set emitter to player's
		//position
		UpdateParticleSystem(&playerParticles, &emitter);
		emitter.x = Int2Fix(p.screenPos.x);
		emitter.y = Int2Fix(p.screenPos.y);

		//Copy sprites from the buffer in to OAM
		oam_copy(MEM_OAM, obj_buffer, 128);
	}
	return 0;
}

