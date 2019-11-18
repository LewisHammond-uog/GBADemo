#include "gba_drawing.h"


void drawRect(u32 a_left, u32 a_top, u32 a_width, u32 a_height, u16 a_color)
{
	for (u32 y = 0; y < a_height; ++y)
	{
		for (u32 x = 0; x < a_width; ++x)
		{
			SCREENBUFFER[(a_top + y) * SCREEN_W + a_left + x] = a_color;
		}
	}
}

void drawLine(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u16 a_color)
{
	s32 w = a_x2 - a_x;
	s32 h = a_y2 - a_y;
	s32 dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w<0) dx1 = -1; else if (w>0) dx1 = 1;
	if (h<0) dy1 = -1; else if (h>0) dy1 = 1;
	if (w<0) dx2 = -1; else if (w>0) dx2 = 1;
	s32 longest = abs(w);
	s32 shortest = abs(h);
	if (!(longest>shortest)) {
		longest = abs(h);
		shortest = abs(w);
		if (h<0) dy2 = -1; else if (h>0) dy2 = 1;
		dx2 = 0;
	}
	s32 numerator = longest >> 1;
	for (s32 i = 0; i <= longest; i++) {
		SCREENBUFFER[a_y * SCREEN_W + a_x] = a_color;
		numerator += shortest;
		if (!(numerator<longest)) {
			numerator -= longest;
			a_x += dx1;
			a_y += dy1;
		}
		else {
			a_x += dx2;
			a_y += dy2;
		}
	}
}

void drawLine_M4(s32 a_x, s32 a_y, s32 a_x2, s32 a_y2, u8 a_paletteID)
{
	s32 w = a_x2 - a_x;
	s32 h = a_y2 - a_y;
	s32 dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w < 0) dx1 = -1; else if (w > 0) dx1 = 1;
	if (h < 0) dy1 = -1; else if (h > 0) dy1 = 1;
	if (w < 0) dx2 = -1; else if (w > 0) dx2 = 1;
	s32 longest = abs(w);
	s32 shortest = abs(h);
	if (!(longest > shortest)) {
		longest = abs(h);
		shortest = abs(w);
		if (h < 0) dy2 = -1; else if (h > 0) dy2 = 1;
		dx2 = 0;
	}
	s32 numerator = longest >> 1;
	for (s32 i = 0; i <= longest; i++) {
		m4_plot( a_x, a_y, a_paletteID);
		numerator += shortest;
		if (!(numerator < longest)) {
			numerator -= longest;
			a_x += dx1;
			a_y += dy1;
		}
		else {
			a_x += dx2;
			a_y += dy2;
		}
	}
}

//#include "Wolf3DWalls.h"
//#include "Wolf3DWallsImg_bin.h"
//
//
//
//void drawVerticalTexturedLine_M4(s32 a_x, s32 a_y, s32 a_height, s16 a_tileID, s16 a_textureOffset, s16 paletteOffset)
//{
//	//accessing in 16bit chunks two pixels becomes 1 read. hence width is not 64 it is 32 as 64 8 bit vals = 32 16bit vals
//	s32 tileVerticalOffset = (a_tileID / 6) * ((64 * 6) * 64) ;
//	s32 tileHorizontalOffset = ((a_tileID % 6) * 64) + (a_textureOffset);
//	s32 tileOrigin = (tileVerticalOffset>>1) + (tileHorizontalOffset>>1);
//	//fixed division = ((a_f1)* FIX_SCALE) / a_f2;
//	s32 vertOffset = ((64 << 8) * (1 << 8)) / (a_height << 8);
//	//vertOffset = vertOffset << 1;
//	s32 yIndexLookup = 0;
//	s16 po = (paletteOffset << 8) + paletteOffset;
//	s16* bitmapu16Val = (u16*)Wolf3DWallsImg_bin;
//	for( s32 i = 0; i < a_height; ++i )
//	{
//		s32 pixelIndex = tileOrigin + ((yIndexLookup>>8) * (32 * 6));
//		if (pixelIndex < Wolf3DWallsBitmapLen)
//		{
//			s16 pix = bitmapu16Val[pixelIndex] + po;
//
//			m4_plot16(a_x, a_y, pix);
//			a_y++;
//			yIndexLookup += vertOffset;
//		}
//	}
//}

void  drawVerticalTexturedLine_M4(s32 a_x, s32 a_y, s32 a_height, s32 a_yVertInc, s16* a_bitmapLoc, s16 a_stride, s16 paletteOffset)
{
	s32 yIndexLookup = 0;
	for (s32 i = 0; i < a_height; ++i)
	{
		s32 pixelIndex = ((yIndexLookup >> 8) * a_stride);
		s16 pix = a_bitmapLoc[pixelIndex] + paletteOffset;
		m4_plot16(a_x, a_y, pix);
		a_y++;
		yIndexLookup += a_yVertInc;
		
	}
}