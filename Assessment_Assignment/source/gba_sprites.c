#include "gba_sprites.h"

//Initalise The Buffer of sprites that we will keep in Working RAM
//This is because we cannot access OAM while the screen is drawing
SpriteObject obj_buffer[128] = { 0 };

//Setup sprite with attribute
void SetupSprite(SpriteObject* a_sprite, u16 a_attribute0, u16 a_attribute1, u16 a_attribute2){
    a_sprite->attr0 = a_attribute0;
    a_sprite->attr1 = a_attribute1;
    a_sprite->attr2 = a_attribute2;
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

//Get Sprite Position
Vector2* GetSpriteScreenPos(SpriteObject* a_sprite){

    Vector2 newPos;
    newPos.x = a_sprite->attr1 & A1_XPOS_MASK;
    newPos.y = a_sprite->attr0 & A0_YPOS_MASK;
    return &newPos;  

}

//Hide a Sprite Object
void HideSpriteObject(SpriteObject* a_obj){
    a_obj->attr0 = (a_obj->attr0 & A0_MODE_MASK) | A0_MODE(A0_MODE_DISABLE);
}

//Unhide a Sprite Object
void UnHideSpriteObject(SpriteObject* a_obj, u8 a_mode){
    a_obj->attr0 = (a_obj->attr0 & ~A0_MODE_MASK) | A0_MODE(a_mode);
}

//Sets attribute 0 up with the correct values
u16 SetSpriteObjectAttribute0(u8 a_y, u8 a_objectMode, u8 a_gfxMode, u8 a_mosaic, u8 a_colourMode, u8 a_shape){
    u16 attrib0 = A0_YPOS(a_y) | A0_MODE(a_objectMode) | A0_GFX_MODE(a_gfxMode) | A0_MOSAIC(a_mosaic)
    |  A0_COLOUR_MODE(a_colourMode) | A0_SHAPE(a_shape);
    return attrib0;
}

//Sets attribute 1 up with the correct values
u16 SetSpriteObjectAttribute1(u16 a_x, u8 a_flip, u8 a_size){
    u16 attrib1 = A1_XPOS(a_x) | A1_FLIP(a_flip) | A1_SIZE(a_size);
    return attrib1;
}

//Sets attribute 2 up with the correct values
u16 SetSpriteObjectAttribute2(u16 a_tileIndex, u8 a_priority, u8 a_paletteBank){
    u16 attrib2 = A2_TILE(a_tileIndex) | A2_PRIORITY(a_priority) | A2_PALETTE(a_paletteBank);
    return attrib2;
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

//Initalise Object Attribute Memory
void oam_init(SpriteObject* a_obj, u8 a_count){

    u32 currentSpriteID = a_count;
    SpriteObject* currentSprite = a_obj;

    //Hide Each Object
    while (currentSpriteID--)
    {
        currentSprite->attr0 = 0;
        currentSprite->attr1 = 0;
        currentSprite->attr2 = 0;
        currentSprite->padding = 0;
        HideSpriteObject(currentSprite);
        ++currentSprite;
    }

    //Initalise OAM
    oam_copy(MEM_OAM, a_obj, a_count);
    
}