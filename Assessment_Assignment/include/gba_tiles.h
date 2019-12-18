#ifndef __GBA_TILES_H__
#define __GBA_TILES_H__

#include "gba_macros.h"
#include "gba_types.h"
#include "gba_reg.h"

//Palette Mem
#define MEM_PALETTE	0x05000000
//The GBA has 2 areas of pallet memeory - background and forground (Sprite)
//Background Pallet Memory has 256 colours - Pallet colour entries are 16 bit (2 bytes)
#define PAL_BG_MEM  (u16*)(MEM_PALETTE)
//Sprite Memory also 256 colours
#define PAL_SP_MEM  (u16*)(MEM_PALETTE + 0x200) // + 512 (256colours * 2bytes)


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
#define TILEBLOCK_SIZE      0x4000 //Size of a page of tiles in memory
#define TILEMAP_BLOCK_SIZE  0x0800 //Size of background tile maps in memory

//The following define allows us to access title memory pages the way we would access an array
#define TILE_MEM ((TILEBLOCK*)VRAM)
#define TILE8_MEM ((TILEBLOCK8*)VRAM)

//Struct for Tile Info, stores tiles and tile size info
//Can also be used for pallet info
typedef struct TilesInfo{
    const u16* data;
    const u16 size; //Size of data not tiles themselves
} TilesInfo, PalletInfo;

#endif //__GBA_TILES_H__