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

//#include "BG_Externs.h"
#include "LVL1BG_Externs.h"
#include "sp_food_8b.h"
//#include "sp_testcharacter.h"

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

	//Copy Pallet in to memory
	memcpy(PAL_SP_MEM, sp_food_8bPal, sp_food_8bPalLen);

	//There is enough memory to load our sprite in to sprite tile mem
	memcpy(&TILE_MEM[4][0], sp_food_8bTiles, sp_food_8bTilesLen);

	//Set up the first sprite in tiles
	s16 sx = (SCREEN_W >> 1) - 8;
	s16 sy = (SCREEN_H >> 1) - 8;

	oam_init(obj_buffer, 128);

	//Set the tile ID
	s16 tileID = 0;

	SpriteObject* sprite = &obj_buffer[0];
	SetupSprite(sprite,  
		SetSpriteObjectAttribute0(sy, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(sx, 0, 1), 
		SetSpriteObjectAttribute2(tileID, A2_PRIORITY_0, 0));
	
	Vector2 pos;
	pos.x = SCREEN_W >> 1;
	pos.y = SCREEN_H >> 1;

	Player p = InitPlayer(sprite, pos, 16, 16);

	SpriteObject* sprite2 = &obj_buffer[1];
	SetupSprite(sprite2,  
		SetSpriteObjectAttribute0(sy+10, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE), 
		SetSpriteObjectAttribute1(sx-5, 0, 1), 
		SetSpriteObjectAttribute2(16, A2_PRIORITY_0, 0));

	pos.x = SCREEN_W;
	pos.y = SCREEN_H >> 1;
	
	Entity e = InitEntity(sprite2, pos, 16,16);

	
	while (1) { //loop forever
		vblank_int_wait();
		PollKeys();

		UpdatePlayer(&p);
		UpdateEntity(&e);
		
		if(KeyHit(A)){
			InitBGMem(0, &pallet, &tiles);
			InitBackground(0, 8, 64, 32, bgMap, NULL);
		}

		if(KeyHit(B)){
			InitBGMem(0, &pallet, &tiles);
			InitBackground(0, 8, 64, 32, bgMap, bg0RegData);
		}


		/*
		if(getAxis(HORIZONTAL) != 0 || getAxis(VERTICAL)){
			tileID += 4 << 1;
			tileID = tileID & 0x38;
		}else{
			tileID = 0;
		}
		sprite->attr2 = SetSpriteObjectAttribute2(tileID, A2_PRIORITY_0, 0);
		*/

		oam_copy(MEM_OAM, obj_buffer, 128);
	}
	return 0;
}

