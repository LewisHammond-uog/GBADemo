#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"
#include "gba_input.h"

//Include header files for bitmap images
#include "img_gba_m3.h"
#include "img_gba_m4.h"
#include "img_gba_m5.h"

int main()
{

	u16 vidmode = VIDEOMODE_3;

	/*Copy the data of the m3 bit map (starting at the start and going for the length of the img)
	in to the screen buffer to be drawn*/
	memcpy(SCREENBUFFER, img_gbaM3Bitmap, img_gbaM3BitmapLen);

	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = vidmode | BGMODE_2;
	register_vblank_isr();


	while(1){
		vblank_int_wait(); //Wait for vblank

		PollKeys();

		//Increment video mode if 'a' key is released
		if(KeyReleased(A)){
			++vidmode;
			
			if(vidmode > VIDEOMODE_5){
				vidmode & VIDEOMODE_3;
			}

			switch(vidmode){
				case VIDEOMODE_3:
				{
					memcpy(SCREENBUFFER, img_gbaM3Bitmap, img_gbaM3BitmapLen); //Simply copy img data in to the screen buffer
					break;
				}
				case VIDEOMODE_4:
				{
					memcpy(SCREENBUFFER, img_gba_m4_bitmap, img_gba_m4BitmapLen); //Copy in image
					memcpy(MEM_PALETTE, img_gba_m4_pal, img_gba_m4PalLen); //Copy in pallet
					break;
				}
				case VIDEOMODE_5:
					memcpy(SCREENBUFFER, img_gba_m5Bitmap, img_gba_m5BitmapLen); //Simply copy img data in to the screen buffer

				default:
					break;
			}

			REG_DISPCNT = vidmode | BGMODE_2; //Switch DISPCNT

		}

	}

	return 0;
}