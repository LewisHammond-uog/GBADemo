#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"
#include "gba_input.h"
#include "gba_tiles.h"
#include "gba_sprites.h"
#include "gba_backgrounds.h"

#include <string.h>

#include "BG_Externs.h"
#include "sp_food_8b.h"

//The map we have is in the wrong format for the gba

//We are going to convert the map in to the GBA format
//with a function

//We are creating a struct to hold the data for a row of screen tiles
//it holds 16 tiles (or half a screen row)
//Map blocks are 16 bits per tile - 10 bits for index, 1 for hflip, 1 for vflip and 4 for the pallete index
typedef struct {u32 data[8]; } HALF_ROW;

//Function to convert 64x32 MapED Maps to GBA format
void copy64x32MapIntoMemory( const u16* a_mapData, u16 a_mapBlockAddress )
{
	//get a pointer to the map ed data we want
	HALF_ROW* src = (HALF_ROW*)a_mapData;

	//a 32x32 map occupies one address space (32x16 bits no$gba demo's this well)
	//a 64x32 map occupies two address spaces, 64x64 occupies four address spaces
	HALF_ROW* dst0 = (HALF_ROW*)GetBGMapBlock(a_mapBlockAddress);
	HALF_ROW* dst1 = (HALF_ROW*)GetBGMapBlock(a_mapBlockAddress+1);

	//as there are 32 tiles per page row the following loop can be used.
	//Using post increment - so assignment happens before the increment
	for( u32 i = 0; i < 32; ++i)
	{
		//copy row i of the left page
		*dst0++ = *src++;   *dst0++ = *src++;
		//copy row i of the right page
		*dst1++ = *src++;   *dst1++ = *src++;
	}
}

int main()
{

	register_vblank_isr();
	//set GBA rendering context to MODE 0 Tile Rendering and enable 1D sprites enable backgrounds 0 & 1
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D | BGMODE_0 | BGMODE_1;
	//copy sprite palette into sprite palette memory
	memcpy( PAL_BG_MEM, bgPalette, bgPaletteSize);
	//There is enough memory to copy all tiles into memory
	u16* tileblock = GetBGTileBlock(0);
	//copy the BG tiles into tile memory
	memcpy( tileblock, bgTiles, bgTilesSize);
	//copy maps
	copy64x32MapIntoMemory( bgMapLayer0, 16);
	copy64x32MapIntoMemory( bgMapLayer1, 18);

	//set up Background controllers for each layer
	REG_BGCNT[0] = SetBGControlRegister( 1, 0, 0, 0, 16, 0, BG_REG_SIZE_64x32);
	REG_BGCNT[1] = SetBGControlRegister( 0, 0, 0, 0, 18, 0, BG_REG_SIZE_64x32);

		//Copy Pallet in to memory
	memcpy(PAL_SP_MEM, sp_food_8bPal, sp_food_8bPalLen);

	//There is enough memory to load our sprite in to sprite tile mem
	memcpy(&TILE_MEM[4][0], sp_food_8bTiles, sp_food_8bTilesLen);

	//Set up the first sprite in tiles
	s16 sx = (SCREEN_W >> 1) - 8;
	s16 sy = (SCREEN_H >> 1) - 8;

	//Set the tile ID
	s16 tileID = 0;

	SpriteObject* sprite = &obj_buffer[0];
	sprite->attr0 = SetSpriteObjectAttribute0(sy, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE);
	sprite->attr1 = SetSpriteObjectAttribute1(sx, 0, 1);
	sprite->attr2 = SetSpriteObjectAttribute2(tileID, A2_PRIORITY_0, 0);

	s32 x = 0;
	s32 y = 0;

	while (1) { //loop forever
		vblank_int_wait();
		PollKeys();

		x += getAxis(HORIZONTAL);
		y -= getAxis(VERTICAL);
		REG_BG_OFFSET[0].x = x;
		REG_BG_OFFSET[0].y = y;
		REG_BG_OFFSET[1].x = x;
		REG_BG_OFFSET[1].y = y;

		oam_copy(MEM_OAM, obj_buffer, 1);
	}
	return 0;
}

