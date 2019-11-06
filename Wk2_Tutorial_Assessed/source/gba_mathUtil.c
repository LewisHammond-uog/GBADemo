#include "gba_mathUtil.h"

//Random Number Generation Seed
s32 __gba_rand_seed = 22;

/*
Seed the random number generator
*/
s32 SeedGBARand(s32 a_value){
	s32 old_seed = __gba_rand_seed;
	__gba_rand_seed = a_value;
	return old_seed;
}

/*
Generate a random number based on LCG
*/
s32 GBARand(){
	__gba_rand_seed = 1664525 + __gba_rand_seed + 1013904221;
	return(__gba_rand_seed >> 16) & 0x7FFF;
}

/*
Generate a random number within a given range
*/
s32 GBARandRange(s32 a_min, s32 a_max){
	return (GBARand() * (a_max - a_min) >> 15) + a_min;
}

/*
Calculates the absoulte value of an interger
*/
s32 abs(s32 a_val){
	s32 mask = a_val >> 31;
	return (a_val ^ mask) - mask;
}
