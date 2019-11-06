#include "gba_gfx.h"

//Initalise The Buffer of sprites that we will keep in Working RAM
//This is because we cannot access OAM while the screen is drawing
SpriteObject obj_buffer[128] = { 0 };

//Use a cast to get the affine buffer to use the same memory as the regular object buffer
SpriteAffine *const obj_affine_buffer = (SpriteAffine*)obj_buffer;

//Sets attribute 0 up with the correct values
u16 SetSpriteObjectAttribute0(u8 a_y, u8 a_objectMode, u8 a_gfxMode, u8 a_mosaic, u8 a_colourMode, u8 a_shape){
    u16 attrib0 = (a_y & A0_YPOS_MASK) | A0_MODE(a_objectMode) | A0_GFX_MODE(a_gfxMode) | A0_MOSAIC(a_mosaic)
    |  A0_COLOUR_MODE(a_colourMode) | A0_SHAPE(a_shape);
    return attrib0;
}

//Sets attribute 1 up with the correct values
u16 SetSpriteObjectAttribute1(u16 a_x, u8 a_flip, u8 a_size){
    u16 attrib1 = (a_x & A1_XPOS_MASK) | A1_FLIP(a_flip) | A1_SIZE(a_size);
    return attrib1;
}

//Sets attribute 2 up with the correct values
u16 SetSpriteObjectAttribute2(u16 a_tileIndex, u8 a_priority, u8 a_paletteBank){
    u16 attrib2 = A2_TILE(a_tileIndex) | A2_PRIORITY(a_priority) | A2_PALETTE(a_paletteBank);
    return attrib2;
}

//Set affube sprite attribute index
void SetAttribute1AffineIndex(SpriteObject* a_object, u8 a_index){
    a_object->attr1 = (a_object->attr1 & ~A1_AFFINE_INDEX_MASK) | A1_AFFINE_INDEX(a_index);
}

//Set Sprite Position
void SetSpriteScreenPos(SpriteObject* a_sprite, s32 a_x, s32 a_y){

    //Clear XPos then set a new one
    a_sprite->attr1 &= 0xfe00;
    a_sprite->attr1 |= A1_XPOS(a_x);

    //Clear Y Pos then set a new one
    a_sprite->attr0 &= 0xff00;
    a_sprite->attr0 |= A0_YPOS(a_y);

}

//Sets an Affine Sprite to an Identity Matrix
void ObjAffineIdentity(SpriteAffine* a_object){
    a_object->pa = 0x01001;
    a_object->pb = 0;
    a_object->pc = 0;
    a_object->pd = 0x0100;
}

//Sets the rotation and scale of an affine sprite
void ObjAffineRotScale(SpriteAffine* a_object, fixed a_sx, fixed a_sy, u16 a_alpha){

    int sin = LU_Sin(a_alpha);
    int cos = LU_Cos(a_alpha);

    //Shift down by 2 to account for fixed point mutiply for .8 fixed
    a_object->pa = cos*a_sx >> 12; 
    a_object->pb = -sin*a_sx >> 12; 
    a_object->pc = sin*a_sy >> 12; 
    a_object->pd = cos*a_sy >> 12;
}

//Copies sprites from obj_buffer to OAM Memory
void oam_copy(SpriteObject* a_destination, SpriteObject* a_source, u8 a_count){

    //Cast source and destination to a u32 so we deal in 32 bit cunks instead of 64
    //(sprites are 4 * u16)
    u32* dstw = (u32*)a_destination;
    u32* srcw = (u32*)a_source;

    //While we have not coppied all of the sprites 
    //we have been told to
    while (a_count--)
    {
        *dstw++ = *srcw++; //Copy memory to these locations then move both of them along 1 * 32 bits
        *dstw++ = *srcw++; //Do the second 32 bits of our sprite
    }
}

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