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

//Defines for sprite locations
#define PlayerSpriteLocation 0
#define ParticleSpriteLocation 40
#define SwordPickupLocation 80
#define HeartPickupLocation 88
#define CoinPickupLocation 96

int main()
{

	register_vblank_isr();

	//set GBA rendering context to MODE 0 Tile Rendering and enable 1D sprites enable backgrounds 0 & 1
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D | BGMODE_0 | BGMODE_1;

	/*-------BACKGROUNDS-------*/

	//Generate Background Register Controller Info
	u16 bg0RegData = SetBGControlRegister( 1, 0, 0, 0, 16, 0, BG_REG_SIZE_64x32);
	//u16 bg1RegData = SetBGControlRegister( 0, 0, 0, 0, 18, 0, BG_REG_SIZE_64x32);

	//Background Pallet and Tile info
	PalletInfo pallet = {bgPalette, bgPaletteSize};
	TilesInfo tiles = {bgTiles, bgTilesSize};

	//Initalise BG Memory and load backgrounds into memory
	InitBGMem(0, &pallet, &tiles);
	InitBackground(0, 8, 64, 32, bgMap, bg0RegData);
	//InitBackground(1, 8, 64, 32, bgMapLayer1, bg1RegData);

	/*-------END OF BACKGROUNDS-------*/

	/*-------SPRITES-------*/
	//Copy Pallet in to memory
	memcpy(PAL_SP_BLOCK(0), GameSpritesPal, GameSpritesPalLen);
	
	//There is enough memory to load our sprite in to sprite tile mem
	memcpy(sprite_tile_address(0), GameSpritesTiles, GameSpritesTilesLen);

	//Set up the first sprite in tiles
	s16 sx = (SCREEN_W >> 1) - 8;
	s16 sy = (SCREEN_H >> 1) - 8;

	oam_init(obj_buffer, 128);

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
		SetSpriteObjectAttribute2(HeartPickupLocation, A2_PRIORITY_0, 0));

	/*--------END OF SPRITES-------*/
	/*-------TESTING PARTICLES------*/
	
	Emitter emitter;
	emitter.x = Int2Fix(100);
	emitter.y = Int2Fix(100);
	ParticleSystem testSys = InitParticleSystem(&emitter, *particleSprite, &obj_buffer[1]);
	
	/*-------END OF TESTING PARTICLES------*/
	
	Vector2 pos;
	pos.x = SCREEN_W >> 1;
	pos.y = SCREEN_H >> 1;

	Player p = InitPlayer(playerSprite, pos, 16, 16);

	pos.x = SCREEN_W;
	pos.y = SCREEN_H >> 1;

	InitPickupMem();
	Pickup* t = InitPickup(0, coinSprite, pos, 16, 16, 100);
	SetPickupType(t, Weapon, SwordSmall);

	InitEnemyMem();
	Vector2 epos;
	epos.x = SCREEN_W >> 1;
	epos.y = SCREEN_H >> 1;
	Enemy test = InitEnemy(0, heartSprite, epos, 16, 16);
	createdEnemies[0] = &test;

	while (1) { //loop forever
		vblank_int_wait();
		PollKeys();

		UpdatePlayer(&p);
		UpdateAllPickups();
		UpdateEnemy(&test);

		//Update player particles 
		UpdateParticleSystem(&testSys, &emitter);
		emitter.x = Int2Fix(p.screenPos.x);
		emitter.y = Int2Fix(p.screenPos.y);
		
		/*
		if(KeyHit(A)){
			InitBGMem(0, &pallet, &tiles);
			InitBackground(0, 8, 64, 32, bgMap, NULL);
		}

		if(KeyHit(B)){
			InitBGMem(0, &pallet, &tiles);
			InitBackground(0, 8, 64, 32, bgMap, bg0RegData);
		}
		*/


		oam_copy(MEM_OAM, obj_buffer, 128);
	}
	return 0;
}

