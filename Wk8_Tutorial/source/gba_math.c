#include "gba_math.h"
#include "gba_mathUtil.h"

//convert and integer to a fixed point representation
fixed	int2fix(s32 a_i)
{
	return a_i << FIX_SHIFT;
}
//Convert a float to a fixed point representation
fixed	float2fix(float a_f)
{
	return (fixed)(a_f*FIX_SCALEF);
}

//convert a fixed point value into an integer value
u32		fix2uint(fixed a_f)
{
	return a_f >> FIX_SHIFT;
}
//Get only the fractional component of a fixed point value as an integer
u32		fix2ufrac(fixed a_f)
{
	return a_f & FIX_MASK;
}
//convert a fixed point number into a signed int
s32		fix2int(fixed a_f)
{
	return a_f / FIX_SCALE;
}

float	fix2float(fixed a_f)
{
	return a_f / FIX_SCALEF;
}

//For these functions to perform correctly fixed point numbers must be in 
//the same format. The format for these functions is 24.8
//Adding two fixed point values together
fixed	fixAdd(fixed a_f1, fixed a_f2)
{
	return a_f1 + a_f2;
}
//subtract two fixed point values
fixed	fixSub(fixed a_f1, fixed a_f2)
{
	return a_f1 - a_f2;
}
//multiply two fixed point values together
//when multiplying the number of fractional bits needs to be adjusted
//a_fa has FIX_SHIFT decimal bits & a_fb has FIX_SHIFT decimal bits
//this effectively shifts the number up an additional FIX_SHIFT number of bits
//the result must be shifted down by FIX_SHIFT bits
fixed	fixMul(fixed a_f1, fixed a_f2)
{
	return (a_f1 * a_f2) / FIX_ONE;
}

fixed	fixDiv(fixed a_f1, fixed a_f2)
{
	return ((a_f1)* FIX_SCALE) / a_f2;
}
//Floor fixed value
fixed fixFloor(fixed a_f)
{
	return a_f & (~FIX_MASK);
}
extern fixed fixCeil(fixed a_f)
{
	s32 s = sign(a_f);
	fixed ceil = (abs(a_f) + (FIX_ONE>>1)) & ~FIX_MASK;
	return (s > 0) ? ceil : -ceil;
}

//convert and integer to a fixed point representation
fixed12	int2fix12(s32 a_i)
{
	return a_i << FIX12_SHIFT;
}
//Convert a float to a fixed point representation
fixed12	float2fix12(float a_f)
{
	return (fixed12)(a_f*FIX12_SCALEF);
}

//convert a fixed point value into an integer value
u32		fix122uint(fixed12 a_f)
{
	return a_f >> FIX12_SHIFT;
}
//Get only the fractional component of a fixed point value as an integer
u32		fix122ufrac(fixed12 a_f)
{
	return a_f & FIX12_MASK;
}
//convert a fixed point number into a signed int
s32		fix122int(fixed12 a_f)
{
	return a_f / FIX12_SCALE;
}

float	fix122float(fixed12 a_f)
{
	return a_f / FIX12_SCALEF;
}

//For these functions to perform correctly fixed point numbers must be in 
//the same format. The format for these functions is 24.8
//Adding two fixed point values together
fixed12	fix12Add(fixed12 a_f1, fixed12 a_f2)
{
	return a_f1 + a_f2;
}
//subtract two fixed point values
fixed12	fix12Sub(fixed12 a_f1, fixed12 a_f2)
{
	return a_f1 - a_f2;
}
//multiply two fixed point values together
//when multiplying the number of fractional bits needs to be adjusted
//a_fa has FIX_SHIFT decimal bits & a_fb has FIX_SHIFT decimal bits
//this effectively shifts the number up an additional FIX_SHIFT number of bits
//the result must be shifted down by FIX_SHIFT bits
fixed12	fix12Mul(fixed12 a_f1, fixed12 a_f2)
{
	fixed12 val = ((s32)a_f1 * (s32)a_f2) / FIX12_ONE;
	if (a_f1 < 0 && a_f2 < 0 && val < 0) val = -val;
	return val;
}

fixed12	fix12Div(fixed12 a_f1, fixed12 a_f2)
{
	return (a_f1* FIX12_SCALE) / a_f2;
}

#include "sinlut.h"

s32 lu_sin(u32 theta)
{
	return sin_lut[(theta >> 7) & 0x1FF];
}

s32 lu_cos(u32 theta)
{
	return sin_lut[((theta >> 7) + 128) & 0x1FF];
}