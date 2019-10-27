#ifndef __GBA_SPRITES_H__
#define __GBA_SPRITES_H__

#include "gba_tiles.h"

//To enable sprites we need to set a bit in our REG_DISPC
#define ENABLE_OBJECTS 0x1000
//There are two modes of mapping for Sprites 1D & 2D
//1d mode makes more programmatical sense
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
//there are 128 sprites available in OAM we may want to create a buffer for these,
//as we cannot mobify sprites when they are being draw to the screen
extern SpriteObject obj_buffer[128];
//Sprite memory in GBA terms is called Object Attribute Memory (OAM)
#define MEM_OAM ((SpriteObject*)0x07000000)

//We now need to define each attribute of the sprite (0-2) and what the bits in each attribute do

#pragma region Sprite Attribute Defines

/*-------Attribute 0--------*/
/*
BIT     DESCRIPTION
0-7     Y-Coordiate (0-255)
*/
#define A0_YPOS_MASK            0xFF
#define A0_YPOS_SHIFT           0
#define A0_YPOS(n)              ((n << A0_YPOS_SHIFT) & A0_YPOS_MASK)
/*
8       Rotation/Scaling Flag (0=off, 1=on)
9       ROTATION & SCALING ENABLED - Double-Size Flag
9       ROTATION & SCALING ENABLED - Object Disable Flag
*/
#define A0_MODE_MASK            0x0300 //Mask to not overflow/underflow
#define A0_MODE_REG             0x0 //Regular Mode
#define A0_MODE_AFFINE          0x1 //Affine Mode
#define A0_MODE_DISABLE         0x2 //Disabled
#define A0_MODE_AFF_DBL         0x3 //Affine Double
#define A0_MODE_SHIFT           8//Number of bits to shift to set mode, in set mode macro
#define A0_MODE(n)              ((n << A0_MODE_SHIFT) & A0_MODE_MASK)
/*
10-11   Object Mode (0=normal, 1=semi-transparent, 2=obj window, 3=forbidden)
*/
#define A0_GFX_MODE_MASK        0x0C00 //Mask to not overflow/underflow
#define A0_GFX_MODE_REG         0 //Regular Mode
#define A0_GFX_MODE_BLEND       1 //Semi Transparent
#define A0_GFX_MODE_WINDOW      2 //Window
#define A0_GFX_MODE_SHIFT       10 //Number of bits to shift to set mode, in set mode macro
#define A0_GFX_MODE(n)          ((n << A0_GFX_MODE_SHIFT) & A0_GFX_MODE_MASK)
/*
12      Object Mosaic (0=off, 1=on)
*/
#define A0_MOSAIC_MASK          0x1000
#define A0_MOSAIC_SHIFT         12
#define A0_MOSAIC(n)            ((n << A0_MOSAIC_SHIFT) & A0_MOSAIC_MASK)
/*
13      Colours/Pallets (0=16/16, 1=256/1)
*/
#define A0_COLOUR_MODE_MASK     0x2000
#define A0_COLOUR_MODE_4BPP     0x0
#define A0_COLOUR_MODE_8BPP     1
#define A0_COLOUR_MODE_SHIFT    13
#define A0_COLOUR_MODE(n)      ((n << A0_COLOUR_MODE_SHIFT) & A0_COLOUR_MODE_MASK)
/*
14-15   Object Shape (0=Square, 1=Horizontal, 2=Vertical, 3=Prohibited)
*/
#define A0_SHAPE_MASK           0xC000
#define A0_SHAPE_SQUARE         0    
#define A0_SHAPE_WIDE           1
#define A0_SHAPE_TALL           2
#define A0_SHAPE_SHIFT          14
#define A0_SHAPE(n)             ((n << A0_SHAPE_SHIFT) & A0_SHAPE_MASK)
/*-------End of Attribute 0--------*/


/*-------Attribute 1--------*/
/*
BIT     DESCRIPTION
0-8     X-Coordinate (0 - 511)
*/
#define A1_XPOS_MASK            0x1FF
#define A1_XPOS_SHIFT           0
#define A1_XPOS(n)              ((n << A1_XPOS_SHIFT) & A1_XPOS_MASK)
/*
9-13    ROTATION & SCALING ENABLED - Rotation and Scaling Parameter Selection (0-31)
9-11    ROTATION & SCALING DISABLED - Not Used
12      ROTATION & SCALING DISABLED - Horizonal Flip (0=Normal, 1=Flipped)
13      ROTATION & SCALING DISABLED - Vertical Flip (0=Normal, 1=Flipped)
*/
#define A1_AFFINE_INDEX_MASK    0x3E00
#define A1_FLIP_MASK            0x3000
#define A1_H_FLIP               1
#define A1_V_FLIP               2
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
#define A1_SIZE_0               0
#define A1_SIZE_1               1
#define A1_SIZE_2               2
#define A1_SIZE_3               3
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
#define A2_PRIORITY_0           0
#define A2_PRIORITY_1           1
#define A2_PRIORITY_2           2
#define A2_PRIORITY_3           3
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
extern void SetupSprite(SpriteObject* a_sprite, u16 a_attribute0, u16 a_attribute1, u16 a_attribute2);
extern void SetSpriteScreenPos(SpriteObject* a_sprite, s32 a_x, s32 a_y);
extern Position* GetSpriteScreenPos(SpriteObject* a_sprite);
extern u16 SetSpriteObjectAttribute0(u8 a_y, u8 a_objectMode, u8 a_gfxMode, u8 a_mosaic, u8 a_colourMode, u8 a_shape);
extern u16 SetSpriteObjectAttribute1(u16 a_x, u8 a_flip, u8 a_size);
extern u16 SetSpriteObjectAttribute2(u16 a_tileIndex, u8 a_priority, u8 a_paletteBank);
extern void oam_copy(SpriteObject* a_destination, SpriteObject* a_source, u8 a_count);


#endif //__GBA_SPRITES_H__