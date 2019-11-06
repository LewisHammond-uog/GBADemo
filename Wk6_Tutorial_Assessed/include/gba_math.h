//Maths Utilities for GBA (mostly fixed point numbers)
#ifndef __GBA_MATH_H__
#define __GBA_MATH_H__

#include "gba_types.h"

//Number of bits that are reserved for decimal values, GBA uses 8.8
//fixed values for affine sprites and transforms in OAM
#define FIX_SHIFT 8

#define FIX_SCALE       ( 1 << FIX_SHIFT    )
#define FIX_MASK        ( FIX_SCALE - 1     )
#define FIX_SCALEF      ( (float)FIX_SCALE  )
#define FIX_SCALE_INV   ( 1.0f / FIXSCALE_F )
#define FIX_ONE         FIX_SCALE

//Use a 32 bit value for fixed point maths using 24.8, even though GBA
//uses 8.8 so allow for better overflow
typedef s32 fixed;

//Functions to convert from non-fixed to fixed 
extern fixed Int2Fix(s32 a_i);
extern fixed Float2Fix(float a_i); //NEVER USE ON GBA HARDWARE

//Functions to convert from fixed to non-fixed notation
extern u32 Fix2UInt(fixed a_f);
extern u32 Fix2UFract(fixed a_f);
extern s32 Fix2Int(fixed a_f);
extern float Fix2Float(fixed a_f); //NEVER USE ON GBA HARDWARE

//Fixed Point Math Functions
extern fixed FixAdd(fixed a_fa, fixed a_fb);
extern fixed FixSub(fixed a_fa, fixed a_fb);
extern fixed FixMul(fixed a_fa, fixed a_fb);
extern fixed FixDiv(fixed a_fa, fixed a_fb);

//Look up Tables
extern s32 LU_Sin(u32 a_theta);
extern s32 LU_Cos(u32 a_theta);

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

#endif //__GBA_MATH_H__