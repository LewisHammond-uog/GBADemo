#include "gba_gfx.h"

//Vsync the screen
void vsync(){
	while(REG_VCOUNT >= 160);
	while(REG_VCOUNT < 160);
}