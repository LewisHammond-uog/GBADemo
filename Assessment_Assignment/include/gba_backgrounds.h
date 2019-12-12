#ifndef __GBA_BACKGROUNDS_H__
#define __GBA_BACKGROUNDS_H__

#include "gba_tiles.h"
#include "gba_drawing.h"

//Backgrounds
#include "LVL1BG_Externs.h"

//Define a base registry for the background controller
//Accessing this as an array will provide us with the 4 BG Controllers
//EG REG_BGCNT[0] = 1st Background page
#define REG_BGCNT ((u16*)(REG_BASE+0x0008))

/*------DEFINES----*/
/*
BIT     DESCRIPTION
0-1     Background Priority (0 - 3, 0=highest)
*/
#define BGCNT_PRIORITY_MASK       0x3
#define BGCNT_PRIORITY_SHIFT      0
#define BGCNT_PRIORITY(n)         (( n << BGCNT_PRIORITY_SHIFT) & BGCNT_PRIORITY_MASK)
/*
2-3     Character Base Block - Which Block do these tiles live in (0-3)
*/
#define BGCNT_TILEBLOCK_MASK      0xC
#define BGCNT_TILEBLOCK_SHIFT     2
#define BGCNT_TILEBLOCK(n)        ((n << BGCNT_TILEBLOCK_SHIFT) & BGCNT_TILEBLOCK_MASK)
/*
4-5     Not Used, has to be 0
*/

/*
6       Mosaic (0=disable, 1=enable)
*/
#define BGCNT_MOSAIC_MASK         0x40
#define BGCNT_MOSAIC_SHIFT        6
#define BGCNT_MOSAIC(n)           ((n << BGCNT_MOSAIC_SHIFT) & BGCNT_MOSAIC_MASK)
/*
7       Colours/Palettes (0=16/16 - 4bpp, 1=256/1 - 8bpp)
*/
#define BGCNT_COLOUR_MODE_MASK    0x80
#define BGCNT_COLOUR_MODE_SHIFT   7
#define BGCNT_COLOUR_MODE(n)      ((n << BGCNT_COLOUR_MODE_SHIFT) & BGCNT_COLOUR_MODE_MASK)
/*
8 - 12  Screen base Block (0-32, in units of 2 KBytes, Background Map Data)
*/
#define BGCNT_TILEMAP_LOC_MASK    0x1F00
#define BGCNT_TILEMAP_LOC_SHIFT   8
#define BGCNT_TILEMAP_LOC(n)      ((n << BGCNT_TILEMAP_LOC_SHIFT) & BGCNT_TILEMAP_LOC_MASK)
/*
13      BG0/BG1: Not Used (except in  NDS mode; Ect palette slot for BG0/1)
13      BG2/BG3: Display Area Overflow (0=Transparent, 1=Wraparound)
*/
#define BGCNT_AFFINE_WRAP_MASK    0x2000
#define BGCNT_AFFINE_WRAP_SHIFT   13
#define BGCNT_AFFINE_WRAP(n)      ((n << BGCNT_AFFINE_WRAP_SHIFT) & BGCNT_AFFINE_WRAP_MASK)
/*
14 - 15 Screen Size (0-3)
        Internal Screen Size
        Size    Texture Mode    Resolution/Scaling Mode
        0       256x256         128x128     (256 bytes)
        1       512x512         256x256     (1kb)
        2       256x512         512x512     (4kb)
        3       512x512         1024x1024   (16kb)
*/
 #define BGCNT_SIZE_MASK        0xC000
 #define BGCNT_SIZE_SHIFT       14
 #define BGCNT_SIZE(n)          ((n << BGCNT_SIZE_SHIFT) & BGCNT_SIZE_MASK)
 //Regular Background sizes
 #define BG_REG_SIZE_32x32      0x0
 #define BG_REG_SIZE_64x32      0x1
 #define BG_REG_SIZE_32x64      0x2
 #define BG_REG_SIZE_64x64      0x3
 //Affine Background sizes
 #define BG_AFF_SIZE_16x16      0x0
 #define BG_AFF_SIZE_32x32      0x1
 #define BG_AFF_SIZE_64x64      0x2
 #define BG_AFF_SIZE_128x128    0x3

//Struct to allow us to control the pos of the render window
typedef struct BackgroundOffset
{
  s16 x;
  s16 y;
}PACKED(4) BGOffset;

//Struct for backgrounds
typedef struct Background{
  Vector2 offset;
  Vector2 maxOffset; //Max Offset allowed on this BG before it loops around
  Vector2 size;
  u8 tileSize;
}Background;

//Define for background offsets - register can only be writen to
#define REG_BG_OFFSET ((BGOffset*)(REG_BASE+0x0010))

#define BG_TILEBLOCK_MASK     0x3 //There are only 4 tileblocks for BG Tiles
#define BG_MAPBLOCK_MASK      0x1F //There are only 32 mapblocks

//Array for all of the BGs we have created
Background createdBackgrounds[4];

extern u16* GetBGTileBlock(u8 a_tileblock);
extern u16* GetBGMapBlock(u8 a_mapBlock);
extern u16 SetBGControlRegister(u8 a_priority, u8 a_tileblock, u8 a_mosaic, u8 a_colourMode,
  u8 a_mapblock, u8 a_affineWrap, u8 a_bgSize);

extern void InitBGMem(u8 a_tileBlockID, PalletInfo* a_pallet, TilesInfo* a_tiles);
extern Background* InitBackground(u8 a_id, u8 a_tileSize, u16 a_tiledWidth, u16 a_tiledHeight, const u16* a_mapData, u16 a_regData);

extern void MoveBackground(u8 a_bgID, s16 a_x, s16 a_y);
extern bool MapScrollInBounds(u8 a_bgID, s16 a_x, s16 a_y);
extern Vector2 GetBackgroundOffset(u8 a_bgID);

//We are creating a struct to hold the data for a row of screen tiles
//it holds 16 tiles (or half a screen row)
//Map blocks are 16 bits per tile - 10 bits for index, 1 for hflip, 1 for vflip and 4 for the pallete index
typedef struct {u32 data[8]; } HALF_ROW;
void copy64x32MapIntoMemory( const u16* a_mapData, u16 a_mapBlockAddress);

#endif //__GBA_BACKGROUNDS_H__