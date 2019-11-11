#include "gba.h"
#include <string.h>

#include "rocket4bpp.h"
#include "particles.h"

int main()
{

	register_vblank_isr();
	//set GBA rendering context to MODE 0 Tile Rendering and enable 1D sprites
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D;
	//copy sprite palette into sprite palette memory
	memcpy( PAL_SP_BLOCK(0), rocket4bppPal, rocket4bppPalLen);
	//copy sprite tiles into memory
	memcpy( sprite_tile_address(0), rocket4bppTiles, rocket4bppTilesLen);

	oam_init(obj_buffer, 128);

	// Set position to center of screen
	int x = (SCREEN_W >> 1) - 16, y = (SCREEN_H >> 1) - 32;
	//set up our rocket sprite
	SpriteObject* rocketSprite = &obj_buffer[0];
	rocketSprite->attr0 = SetSpriteObjectAttrib0( y, A0_MODE_REG, A0_GFX_MODE_REG, 0, A0_COLOUR_MODE_4BPP, A0_SHAPE_TALL);
	rocketSprite->attr1 = SetSpriteObjectAttrib1( x, 0, A1_SIZE_3);
	rocketSprite->attr2 = SetSpriteObjectAttrib2( 0, 0, 0);
	

	while (1) //loop forever
	{ 
		vblank_intr_wait();
		PollKeys();
		
		oam_copy(MEM_OAM, obj_buffer, 128);
	}
	return 0;
}
