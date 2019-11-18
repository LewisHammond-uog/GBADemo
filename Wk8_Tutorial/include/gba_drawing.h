
#ifndef __GBA_DRAWING_H__
#define __GBA_DRAWING_H__

#include "gba_types.h"
#include "gba_mathUtil.h"
#include "gba_gfx.h"

#define SCREENBUFFER ((v_u16*)(VRAM))

#define SCREEN_W 240
#define SCREEN_H 160

INLINE u16 setColor(u8 a_red, u8 a_green, u8 a_blue)
{
	return (a_red & 0x1F) | (a_green & 0x1F) << 5 | (a_blue & 0x1f) << 10;
}

void drawRect(u32 a_left, u32 a_top, u32 a_width, u32 a_height, u16 a_color);
void drawLine(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u16 a_color);

INLINE void m4_plot(int x, int y, u8 clrid)
{
	u16* vid_page = getVideoPage();
	u16 dataWrite = (clrid << 8) + clrid;

	u16 *dst = &vid_page[(y*SCREEN_W + x) / 2];  // Division by 2 due to u8/u16 pointer mismatch!
	*dst = dataWrite; //we can only write to vid memory in 16bit chunks in mode 4 this is two pixels at a time, comment this out and uncomment below to repair
	//if (x & 1)
	//	*dst = (*dst & 0xFF) | (clrid << 8);    // odd pixel
	//else
	//	*dst = (*dst&~0xFF) | clrid;        // even pixel
}

INLINE void m4_plot16(int x, int y, u16 a_pix)
{
	u16* vid_page = getVideoPage();
	u16 *dst = &vid_page[(y*SCREEN_W + x) / 2];  // Division by 2 due to u8/u16 pointer mismatch!
	*dst = a_pix; 
}

void drawLine_M4(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u8 a_paletteID);
//void  drawVerticalTexturedLine_M4(s32 a_x, s32 a_y, s32 a_height, s16 a_tileID, s16 a_textureOffset, s16 paletteOffset);
void  drawVerticalTexturedLine_M4(s32 a_x, s32 a_y, s32 a_height, s32 a_yVertInc, s16* a_bitmapLoc, s16 a_stride, s16 paletteOffset);

#endif //__GBA_DRAWING_H__
