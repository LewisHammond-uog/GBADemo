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

//Initalises Background Memory - Pallets and Tiles
void InitBGMem(u8 a_tileBlockID, PalletInfo* a_pallet, TilesInfo* a_tiles){

    //Copy Pallet Data in to memory
    memcpy(PAL_BG_MEM, a_pallet->data, a_pallet->size);

    //Get tile block and store tiles in memory
    u16* tileblock = GetBGTileBlock(a_tileBlockID);
    memcpy(tileblock, a_tiles->data, a_tiles->size);

}

Background* InitBackground(u8 a_id, u16 a_width, u16 a_height, const u16* a_mapData, u16 a_regData){
    
    //Copy map in to memory
    copy64x32MapIntoMemory(a_mapData, 16 + (a_id*2));

    //Setup background controller
    REG_BGCNT[a_id] = a_regData;

    //Create Struct and init data
    Vector2 offset = {0, 0};
    Vector2 size = {a_width, a_height};
    Background bg = {
        offset,
        size
    };

    //Add BG to array
    createdBackgrounds[a_id] = bg;

    return &createdBackgrounds[a_id];
}

//Moves a background by a given pixel value
void MoveBackground(u8 a_bgID, s16 a_x, s16 a_y){

    //Increase Offset
    createdBackgrounds[a_bgID].offset.x += a_x;
    createdBackgrounds[a_bgID].offset.y += a_y;

    REG_BG_OFFSET[a_bgID].x = createdBackgrounds[a_bgID].offset.x;
    REG_BG_OFFSET[a_bgID].y = createdBackgrounds[a_bgID].offset.y;
}

//Function to convert 64x32 MapED Maps to GBA format
void copy64x32MapIntoMemory( const u16* a_mapData, u16 a_mapBlockAddress )
{
	//get a pointer to the map ed data we want
	HALF_ROW* src = (HALF_ROW*)a_mapData;

	//a 32x32 map occupies one address space
	//a 64x32 map occupies two address spaces, 64x64 occupies four address spaces
	HALF_ROW* dst0 = (HALF_ROW*)GetBGMapBlock(a_mapBlockAddress);
	HALF_ROW* dst1 = (HALF_ROW*)GetBGMapBlock(a_mapBlockAddress + 1);

	//as there are 32 tiles per page row the following loop can be used.
	//Using post increment - so assignment happens before the increment
	for( u32 i = 0; i < 32; ++i)
	{
		//copy row i of the left page
		*dst0++ = *src++;   *dst0++ = *src++;
		//copy row i of the right page
		*dst1++ = *src++;   *dst1++ = *src++;
	}
}