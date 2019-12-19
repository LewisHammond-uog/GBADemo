#include "gba_math.h"

/*----Fixed Point Functions----*/

//Convert from an int to a fixed
fixed Int2Fix(s32 a_i){
    return a_i << FIX_SHIFT;
}

//Convert from a float to a fixed
//DO NOT USE ON GBA HARDWARE
fixed Float2Fix(float a_f){
    return (fixed)(a_f * FIX_SCALEF);
}

//Convert from a fixed to an unsigned int
u32 Fix2UInt(fixed a_f){
    return a_f >> FIX_SHIFT;
}

//Convert from a fixed to a signed int
s32 Fix2Int(fixed a_f){
    return a_f / FIX_SCALE;
}

//Convert from a fixed to a float
//DO NOT USE ON GBA HARDWARE
float Fix2Float(fixed a_f){
    return a_f / FIX_SCALEF;
}

//Adds 2 fixed's together
fixed fixAdd(fixed a_fa, fixed a_fb){
    return a_fa + a_fb;
}

//Subtracts 2 fixeds from eachother
fixed fixSub(fixed a_fa, fixed a_fb){
    return a_fa - a_fb;
}

//Mutilplies 2 fixed's together
fixed fixMul(fixed a_fa, fixed a_fb){
    return (a_fa * a_fb) >> FIX_SHIFT;
}

//Divides 2 fixed's
fixed fixDiv(fixed a_fa, fixed a_fb){
    return ((a_fa) * FIX_SCALE) / a_fb;
}

/*----Look Up Tables----*/
//Lookup Sin of an angle
s32 LU_Sin(u32 a_theta){
    return sin_lut[(a_theta >> 7) & 0x1FF];
}

//Lookup Cos of an angle
s32 LU_Cos(u32 a_theta){
    return sin_lut[((a_theta >> 7) + 128) & 0x1FF]; 
}

/*----General Math Utility Functions----*/

//Random Number Generation Seed
s32 __gba_rand_seed = 22;

//Get the distance between 2 vectors squrared
//a - 1st Vector
//b - 2nd Vector
s32 Vector2DistSqrd(Vector2 a, Vector2 b){
    return ((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y));
}


//Seed the random number generator
//a_value - Value to seed with
s32 SeedGBARand(s32 a_value){
	s32 old_seed = __gba_rand_seed;
	__gba_rand_seed = a_value;
	return old_seed;
}


//Generate a random number based on LCG
s32 GBARand(){
	__gba_rand_seed = 1664525 + __gba_rand_seed + 1013904221;
	return(__gba_rand_seed >> 16) & 0x7FFF;
}


//Generate a random number within a given range
//a_min - Minimum Value
//a_max - Maximum Value
s32 GBARandRange(s32 a_min, s32 a_max){
	return (GBARand() * (a_max - a_min) >> 15) + a_min;
}


//Calculates the absoulte value of an interger (s32)
//a_val - Value
s32 abs(s32 a_val){
	s32 mask = a_val >> 31;
	return (a_val ^ mask) - mask;
}