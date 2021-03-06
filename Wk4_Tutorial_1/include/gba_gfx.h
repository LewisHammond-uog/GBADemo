#ifndef __GBA_GFX_H__
#define __GBA_GFX_H__

#include "gba_macros.h"
#include "gba_types.h"
#include "gba_reg.h"

//Display controller address
#define REG_DISPCNT *((v_u32*)(REG_BASE))

//Defines for settng up different video modes
#define VIDEOMODE_0 0x0000  //Sprite Mode 0
#define VIDEOMODE_1 0x0001  //Sprite Mode 1
#define VIDEOMODE_2 0x0002  //Sprite Mode 2
#define VIDEOMODE_3 0x0003	// < Mode 3; 240x160 @16bpp
#define VIDEOMODE_4	0x0004	// < Mode 4; 240x160 @8 bpp
#define VIDEOMODE_5 0x0005  // < Mode 5; 

//Defines for enabling different backgrounds
#define BGMODE_0	0x0100
#define BGMODE_1	0x0200
#define BGMODE_2	0x0400
#define BGMODE_3	0x0800

//vcount - checks current scan line being rendered
#define REG_VCOUNT (*(v_u16*)(REG_BASE + 0x06))

//Palette Mem
#define MEM_PALETTE	0x05000000
//The GBA has 2 areas of pallet memeory - background and forground (Sprite)
//Background Pallet Memory has 256 colours - Pallet colour entries are 16 bit (2 bytes)
#define PAL_BG_MEM  (u16*)(MEM_PALETTE)
//Sprite Memory also 256 colours
#define PAL_SP_MEM  (u16*)(MEM_PALETTE + 0x200) // + 512 (256colours * 2bytes)

#define VIDEO_PAGE			0x0010	//!< Page indicator

#define VRAM_PAGE_SIZE		0x0A000
#define VRAM_BACK	(VRAM + VRAM_PAGE_SIZE)

#define vid_mem			((u16*)VRAM)
#define vid_page_front	((u16*)VRAM)
#define vid_page_back	((u16*)VRAM_BACK)
extern void vsync();

//GBA Uses tiled rendering in Modes 0-2
//A tile consists of 8x8 pixels
//There are two variations on bitdepth 4bpp or 8bpp
//So we have two tile types 8x8@4bpp or 8x8@8bpp
typedef struct TILE { u32 data[8]; } PACKED(4) TILE, TILE4;
typedef struct TILE8 { u32 data[16]; } PACKED(4) TILE8;

//GBA Tile memory is split up into different pages
//There are six pages in total, four for background tiles and two for sprite tiles
//Each page can hold a total of 512 4bpp tiles or 256 8bpp tiles
//Defines for TILE blocks for standard tiles and double size tiles
typedef TILE TILEBLOCK[512];
typedef TILE8 TILEBLOCK8[256];
//The following define allows us to access title memory pages the way we would access an array
#define TILE_MEM ((TILEBLOCK*)0x06000000)
#define TILE8_MEM ((TILEBLOCK8*)0x06000000)
//To enable sprites we need to set a bit in our REG_DISPC
#define ENABLE_OBJECTS 0x1000
//There are two modes of mapping for Sprites 1D & 2D
//I prefer to use 1D as this makes more logical sense as a programmer
#define MAPPING_MODE_1D 0x0040

//Define Sprite Structure
//GBATek shows sprites are a collection of 4 16bit attributes
//attribute 0-2 are utilised attribute 3 is padding for affine sprites
typedef struct SpriteObject {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	s16 padding;
} PACKED(4) SpriteObject;
//there are 128 sprites available in OAM we may want to create a buffer for these
extern SpriteObject obj_buffer[128];
//Sprite memory in GBA terms is called OBject Attribute Memory (OAM)
#define MEM_OAM ((SpriteObject*)0x07000000)

//We now need to define each attribute of the sprite (0-2) and what the bits in each attribute do

#pragma region Sprite Attribute Defines

/*-------Attribute 0--------*/
/*
BIT     DESCRIPTION
0-7     Y-Coordiate (0-255)
*/
#define A0_YPOS_MASK            0xFF
/*
8       Rotation/Scaling Flag (0=off, 1=on)
9       ROTATION & SCALING ENABLED - Double-Size Flag
9       ROTATION & SCALING ENABLED - Object Disable Flag
*/
#define A0_MODE_MASK            0x0300 //Mask to not overflow/underflow
#define A0_MODE_REG             0x0 //Regular Mode
#define A0_MODE_AFFINE          0x100 //Affine Mode
#define A0_MODE_DISABLE         0x200 //Disabled
#define A0_MODE_AFF_DBL         0x300 //Affine Double
#define A0_MODE_SHIFT           8//Number of bits to shift to set mode, in set mode macro
#define A0_MODE(n)              ((n << A0_MODE_SHIFT) & A0_MODE_MASK)
/*
10-11   Object Mode (0=normal, 1=semi-transparent, 2=obj window, 3=forbidden)
*/
#define A0_GFX_MODE_MASK        0x0C00 //Mask to not overflow/underflow
#define A0_GFX_MODE_REG         0x0 //Regular Mode
#define A0_GFX_MODE_BLEND       0x400 //Semi Transparent
#define A0_GFX_MODE_WINDOW      0x800 //Window
#define A0_GFX_MODE_SHIFT       10 //Number of bits to shift to set mode, in set mode macro
#define A0_GFX_MODE(n)          ((n << A0_GFX_MODE_SHIFT) & A0_GFX_MODE_MASK)
/*
12      Object Mosaic (0=off, 1=on)
*/
#define A0_MOSAIC_MASK          0x1000
#define A0_MOSAIC_SHIFT         12
#define A0_MOSAIC(n)          ((n << A0_MOSAIC_SHIFT) & A0_MOSAIC_MASK)
/*
13      Colours/Pallets (0=16/16, 1=256/1)
*/
#define A0_COLOUR_MODE_MASK     0x2000
#define A0_COLOUR_MODE_4BPP     0x0
#define A0_COLOUR_MODE_8BPP     0x2000
#define A0_COLOUR_MODE_SHIFT    13
#define A0_COLOUR_MODE(n)      ((n << A0_COLOUR_MODE_SHIFT) & A0_COLOUR_MODE_MASK)
/*
14-15   Object Shape (0=Square, 1=Horizontal, 2=Vertical, 3=Prohibited)
*/
#define A0_SHAPE_MASK           0xC000
#define A0_SHAPE_SQUARE         0x0       
#define A0_SHAPE_WIDE           0x4000
#define A0_SHAPE_TALL           0x8000
#define A0_SHAPE_SHIFT          14
#define A0_SHAPE(n)             ((n << A0_SHAPE_SHIFT) & A0_SHAPE_MASK)
/*-------End of Attribute 0--------*/


/*-------Attribute 1--------*/
/*
BIT     DESCRIPTION
0-8     X-Coordinate (0 - 511)
*/
#define A1_XPOS_MASK            0x1FF
/*
9-13    ROTATION & SCALING ENABLED - Rotation and Scaling Parameter Selection (0-31)
9-11    ROTATION & SCALING DISABLED - Not Used
12      ROTATION & SCALING DISABLED - Horizonal Flip (0=Normal, 1=Flipped)
13      ROTATION & SCALING DISABLED - Vertical Flip (0=Normal, 1=Flipped)
*/
#define A1_AFFINE_INDEX_MASK    0x3E00
#define A1_FLIP_MASK            0x3000
#define A1_H_FLIP               0x1000
#define A1_V_FLIP               0x2000
#define A1_FLIP_SHIFT           12
#define A1_FLIP(n)              ((n << A1_FLIP_SHIFT) & A1_FLIP_MASK)
/*
14      Object Size (0-3 Depends on OBJ Shape being set in ATTR0)
        Size    Square  Horizontal  Veritcal
        0       8x8     16x8        8x16
        1       16x16   32x8        8x32
        2       32x32   32x16       16x32   
        3       64x64   64x32       32x64
*/
#define A1_SIZE_MASK            0xC000
#define A1_SIZE_0               0x0
#define A1_SIZE_1               0x4000
#define A1_SIZE_2               0x8000
#define A1_SIZE_3                0xC000
#define A1_SIZE_SHIFT           14
#define A1_SIZE(n)              ((n << A1_SIZE_SHIFT) & A1_SIZE_MASK)
/*-------End of Attribute 1--------*/

/*-------Attribute 2--------*/
/*
BIT     DESCRIPTION
0-9     Character Name/Tile Number (0 - 1023)
*/
#define A2_TILE_MASK            0x3FFF
#define A2_TILE_SHIFT           0
#define A2_TILE(n)              ((n << A2_TILE_SHIFT) & A2_TILE_MASK)
/*
10-11   Priority Relative to Background (0-3; 0 = highest)
*/
#define A2_PRIORITY_MASK        0xC00
#define A2_PRIORITY_0           0x0
#define A2_PRIORITY_1           0x400
#define A2_PRIORITY_2           0x800
#define A2_PRIORITY_3           0xC00
#define A2_PRIORITY_SHIFT       10
#define A2_PRIORITY(n)          ((n << A2_PRIORITY_SHIFT) & A2_PRIORITY_MASK)
/*
12-15   Pallet Number (0-15) - Not used in 256/1 pallet mode - see atrr1, bit 13
*/
#define A2_PALETTE_MASK          0xF000
#define A2_PALETTE_SHIFT         12
#define A2_PALETTE(n)          ((n << A2_PALETTE_SHIFT) & A2_PALETTE_MASK)
/*-------End of Attribute 2--------*/

#pragma endregion

//Functions to actaully do things to sprites
extern u16 SetSpriteObjectAttribute0(u8 a_y, u8 a_objectMode, u8 a_gfxMode, u8 a_mosaic, u8 a_colourMode, u8 a_shape);
extern u16 SetSpriteObjectAttribute1(u16 a_x, u8 a_flip, u8 a_size);
extern u16 SetSpriteObjectAttribute2(u16 a_tileIndex, u8 a_priority, u8 a_paletteBank);

#endif //__GBA_GFX_H__