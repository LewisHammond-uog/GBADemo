#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"
#include "gba_input.h"

#include "sp_food_8b.h"

int main()
{
	register_vblank_isr();

	//Set Rendering Mode 0 and enable objects and enable 1D Sprites
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D;

	//Copy Pallet in to memory
	memcpy(PAL_SP_MEM, sp_food_8bPal, sp_food_8bPalLen);

	//There is enough memory to load our sprite in to sprite tile mem
	memcpy(&TILE_MEM[4][0], sp_food_8bTiles, sp_food_8bTilesLen);

	//Set up the first sprite in tiles
	s16 x = (SCREEN_W >> 1) - 8;
	s16 y = (SCREEN_H >> 1) - 8;

	//Set the tile ID
	s16 tileID = 0;

	SpriteObject* sprite = &obj_buffer[0];
	sprite->attr0 = SetSpriteObjectAttribute0(y, A0_MODE_REG, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE);
	sprite->attr1 = SetSpriteObjectAttribute1(x, 0, 1);
	sprite->attr2 = SetSpriteObjectAttribute2(tileID, A2_PRIORITY_0, 0);


	while(1){
		vblank_int_wait(); //Wait for vblank

		PollKeys();
		
		if(KeyReleased(A)){
			tileID += 4 << 1;
			tileID = tileID & 0x1FF;
		}
		
		sprite->attr2 = SetSpriteObjectAttribute2(tileID, A2_PRIORITY_0, 0);
		oam_copy(MEM_OAM, obj_buffer, 1);
	}

	return 0;
}

