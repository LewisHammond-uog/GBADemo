#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_math.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "rocket4bpp.h"

#include <string.h>

int main()
{

	register_vblank_isr();
	//set GBA rendering context to MODE 0 Tile Rendering and enable 1D sprites enable backgrounds 0 & 1
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D;

	//Copy Pallet in to memory
	memcpy(PAL_SP_MEM, rocket4bppPal, rocket4bppPalLen);

	//There is enough memory to load our sprite in to sprite tile mem
	memcpy(&TILE8_MEM[4][0], rocket4bppTiles, rocket4bppTilesLen);
	oam_init(obj_buffer, 128);
	

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
	sprite->attr0 = SetSpriteObjectAttribute0(y, A0_MODE_AFF_DBL, A0_GFX_MODE_REG, 0, A0_COLOUR_MODE_4BPP, A0_SHAPE_TALL);
	sprite->attr1 = SetSpriteObjectAttribute1(x, 0, A1_SIZE_3);
	sprite->attr2 = SetSpriteObjectAttribute2(0, 0, 0);
	SetAttribute1AffineIndex(sprite,0);
	sprite->attr2 = 0;

	//Set Affine for this sprite
	SpriteAffine * spriteAff = &obj_affine_buffer[0];
	ObjAffineIdentity(spriteAff);
	

	while (1) { //loop forever
		vblank_int_wait();
		//PollKeys();

		--y;
		SetSpriteScreenPos(sprite, x, y);

		alpha += alpha_ofs;

		if(alpha > 256 << 8){
			alpha = 0;
		}

		scale += scale_ofs;

		if(scale > 2 << 9 || scale < 1 << 6){
			scale_ofs = -scale_ofs;
		}

		ObjAffineRotScale(spriteAff, scale, scale, alpha);

		oam_copy(MEM_OAM, obj_buffer, 128);
	}
	return 0;
}

