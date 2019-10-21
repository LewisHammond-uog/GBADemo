#include "gba_backgrounds.h"

//Function to setup/configure BG Control Register
u16 SetBGControlRegister(u8 a_priority, u8 a_tileblock, u8 a_mosaic, u8 a_colourMode,
  u8 a_mapblock, u8 a_affineWrap, u8 a_bgSize ){
    u16 controlReg = BGCNT_PRIORITY(a_priority) | BGCNT_TILEBLOCK(a_tileblock) | BGCNT_MOSAIC(a_mosaic) |
    BGCNT_COLOUR_MODE(a_colourMode) | BGCNT_TILEMAP_LOC(a_mapblock) | BGCNT_AFFINE_WRAP(a_affineWrap) |
    BGCNT_SIZE(a_bgSize);
    return controlReg;
}

//Get the address to the tile map in memory by providing a number (0-32)
u16* GetBGMapBlock(u8 a_mapBlockIndex){
    return (u16*)(VRAM + (a_mapBlockIndex & BG_MAPBLOCK_MASK) * TILEMAP_BLOCK_SIZE);
}

//Gets the address of a tile block memory by providing a number (0-3)
u16* GetBGTileBlock(u8 a_tileBlockIndex)
{
    return  (u16*)(TILE_MEM[(a_tileBlockIndex & BG_TILEBLOCK_MASK)]);
}