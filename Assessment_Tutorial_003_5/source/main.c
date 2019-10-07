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
#include "img_mario_walk_1.h"
#include "img_mario_walk_2.h"
#include "img_mario_walk_3.h"

u16* vidPage = vid_page_back;

//Decleration for function to copy bitmap in memory
void CopyBitmapToPage(u16* a_vidPage, const u16* a_bitmap, s16 a_width, s16 a_height, s16 a_x, s16 a_y);
void PageFlip(void);

/*
This program loads images in to memory pages for display on the screen
Pressing A (Z) changes which pages are displayed
Pages are only swaped out when they are not visible
*/

int main()
{
	register_vblank_isr();
	//Mario bitmap image sizes
	s8 marioH = 90;
	s8 marioW = 70;

	//copy colour palette into memory
	memcpy(MEM_PALETTE, img_mario_walk_1Pal, img_mario_walk_1PalLen);
	
	//Set Memory Address of the pages to the colour of the first pixel in the bitmap image. So that the
	//Background is all white
	memset(vid_page_front, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	memset(vid_page_back, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);

	REG_DISPCNT = VIDEOMODE_4 | BGMODE_2;

	//Copy Images in to pages
	CopyBitmapToPage(vid_page_front, img_mario_walk_1Bitmap, marioW, marioH , 10, 10);
	CopyBitmapToPage(vid_page_back, img_mario_walk_2Bitmap, marioW, marioH , 10, 10);

	s8 keyFrame = 0;
	while(1){
		vblank_int_wait(); //Wait for vblank

		PollKeys();

		//Increment video mode if 'a' key is released
		
		if(KeyReleased(A)){
			++keyFrame;
			keyFrame = keyFrame & 0x3;

			switch (keyFrame)
			{
				
			/*
				On key frame 0 we are display the orignal image
				Just before we switch page on key frame 1 we load the second image in to memory
				then in key frame 2 we revert back to the original image
				then just before switching page on key frame 3 we load image 3 in
				then go back to key frame 0
			*/
			case 1:{
				//Copy Frame 2 to back buffer
				CopyBitmapToPage(vid_page_back, img_mario_walk_2Bitmap, marioW, marioH , 10, 10);
				break;
			}
			case 3:{
				//Copy Frame 3 to back buffer
				CopyBitmapToPage(vid_page_back, img_mario_walk_3Bitmap, marioW, marioH , 10, 10);
				break;
			}
			
			default:
				break;
			}

			//Function to flip between the pages
			PageFlip();
		}
		

	}

	return 0;
}

//Swap between image images
void PageFlip(void){
	vidPage = (u16*)((u32)vidPage ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= VIDEO_PAGE;
	return vidPage;
}

void CopyBitmapToPage(u16* a_vidPage, const u16* a_bitmap, s16 a_width, s16 a_height, s16 a_x, s16 a_y){

	u16 screenLocation = 0;
	u16 bitmapLocation = 0;
	for( s16 i = 0; i < a_height; ++i )
	{
		screenLocation =  (a_y + i) * 120 + a_x; 
		bitmapLocation = (i * a_width>>1)+i;

		memcpy( &a_vidPage[screenLocation], &a_bitmap[bitmapLocation], a_width);
	}

}