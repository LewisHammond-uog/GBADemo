#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"
#include "gba_input.h"

#include <string.h>

int main()
{
	register_vblank_isr();

	//Set Rendering Mode 0 and enable objects and enable 1D Sprites
	REG_DISPCNT = VIDEOMODE_0 | ENABLE_OBJECTS | MAPPING_MODE_1D;

	while(1){
		vblank_int_wait(); //Wait for vblank

		PollKeys();
	}

	return 0;
}

