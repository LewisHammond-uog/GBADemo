#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"
#include "gba_input.h"



int main()
{
	register_vblank_isr();


	REG_DISPCNT = VIDEOMODE_0;

	while(1){
		vblank_int_wait(); //Wait for vblank

		PollKeys();
		
		if(KeyReleased(A)){
			
		}
	}

	return 0;
}

