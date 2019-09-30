#ifndef __GBA_MATHUTIL_H__
#define __GBA_MATHUTIL_H__

#include "gba_types.h"

//Random Number Generation Seed
extern s32 __gba_rand_seed;

/*
Functions for generating and using random number generation
*/
extern s32 SeedGBARand(s32 a_value);
extern s32 GBARand();
extern s32 GBARandRange(s32 a_min, s32 a_max);

/*
Function to get the absolute value of a number
*/
extern s32 abs(s32 a_val);


#endif //__GBA_MATHUTIL_H__