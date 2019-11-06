#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_math.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "sp_food_8b.h"

#include <string.h>

int main()
{

	register_vblank_isr();
	//set GBA rendering context to MODE 0 Tile Rendering and enable 1D sprites enable backgrounds 0 & 1
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D | BGMODE_0 | BGMODE_1;

	//Copy Pallet in to memory
	memcpy(PAL_SP_MEM, sp_food_8bPal, sp_food_8bPalLen);

	//There is enough memory to load our sprite in to sprite tile mem
	memcpy(&TILE_MEM[4][0], sp_food_8bTiles, sp_food_8bTilesLen);

	//Set up the first sprite in tiles
	s16 x = (SCREEN_W >> 1) - 8;
	s16 y = (SCREEN_H >> 1) - 8;

	//Angle 
	u16 alpha = 0;
	u16 alpha_ofs = 1 << 8;

	//Scale, init to 1x
	fixed scale = 1 << 8;
	int scale_ofs = 4;

	SpriteObject* sprite = &obj_buffer[0];
	sprite->attr0 = SetSpriteObjectAttribute0(y, A0_MODE_AFFINE, A0_GFX_MODE_REG, 0, 1, A0_SHAPE_SQUARE);
	sprite->attr1 = SetSpriteObjectAttribute1(x, 0, 1);
	sprite->attr2 = SetSpriteObjectAttribute2(0, 0, 0);
	//SetAttribute1AffineIndex(sprite,0);

	oam_copy(MEM_OAM, obj_buffer, 1);
	

	while (1) { //loop forever
		vblank_int_wait();
		//PollKeys();
	}
	return 0;
}

