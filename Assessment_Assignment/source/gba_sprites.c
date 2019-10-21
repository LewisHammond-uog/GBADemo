#include "gba_sprites.h"

//Initalise The Buffer of sprites that we will keep in Working RAM
//This is because we cannot access OAM while the screen is drawing
SpriteObject obj_buffer[128] = { 0 };

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