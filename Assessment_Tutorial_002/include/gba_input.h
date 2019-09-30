#ifndef __GBA_INPUT_H__
#define __GBA_INPUT_H__

#include "gba_reg.h"
#include "gba_types.h"
#include "gba_macros.h"

//Key Input Memory Address
#define REG_KEYINPUT *(v_u16*)(REG_BASE + 0x130)
#define REG_KEYCNT *(v_u16*)(REG_BASE + 0x132)

typedef enum KEYS {
    A       =   (1 << 0),
    B       =   (1 << 1),
    SELECT  =   (1 << 2),
    START   =   (1 << 3),
    RIGHT      =   (1 << 4),
    LEFT    =   (1 << 5),
    UP   =   ( 1 << 6),
    DOWN    =   (1 << 7),
    R       =   (1 << 9),
    L       =   (1 << 9),

    //Interput Controller
    KEYIRQ_ENABLE   =   (1 << 14),
    KEYIRQ_OR       =   (1 << 15),
    KEYIRQ_AND      =   (1 << 15),

    KEYS_MAX

}KEYS;

#define KEY_MASK 0x3FF //We only care about the 10 lower bits

extern u16 __currentKeys, __prevKeys;

//Poll the active keys
INLINE void PollKeys(void)
{
    __prevKeys = __currentKeys;
    __currentKeys = ~REG_KEYINPUT & KEY_MASK;
}

//Get Key States
INLINE u16 currentKeyState(void) { return __currentKeys;}
INLINE u16 previousKeyState(void) { return __prevKeys;}
INLINE u16 KeyDown( u16 a_key) { return __currentKeys & a_key;}
INLINE u16 KeyUp( u16 a_key) { return ~__currentKeys & a_key;}
INLINE u16 KeyHeld( u16 a_key) { return (__prevKeys & __currentKeys) & a_key;}
INLINE u16 KeyReleased( u16 a_key) { return (__prevKeys & ~__currentKeys) & a_key;}
INLINE u16 KeyHit (u16 a_key) { return (~__prevKeys & __currentKeys) & a_key;}
INLINE u16 KeyStateChange (u16 a_key) { return (__prevKeys ^ __currentKeys) & a_key;}

typedef enum AXIS{
    HORIZONTAL = 0,
    VERTICAL,
}AXIS;

INLINE s16 getAxis(AXIS a_val){
    switch(a_val){
        case HORIZONTAL:
            return ((__currentKeys >> 4) & 1) - ((__currentKeys >> 5) & 1);
        case VERTICAL:
            return ((__currentKeys >> 6) & 1) - ((__currentKeys >> 7) & 1);
        default:
            return 0;
    }
}


#endif // __GBA_INPUT_H__