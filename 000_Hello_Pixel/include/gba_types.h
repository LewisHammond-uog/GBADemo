/*
Header to contain all of the custom types for GBA
*/

#ifndef __GBA_TYPES_H__
#define __GBA_TYPES_H__

#include <stdint.h>
#include <stdbool.h>

//Basic Types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
//Define volitile types (i.e don't optimise (const) these types as hardware might change them)
typedef volatile uint8_t v_u8;
typedef volatile uint16_t v_u16;
typedef volatile uint32_t v_u32;
typedef volatile int8_t v_s8;
typedef volatile int16_t v_s16;
typedef volatile int32_t v_s32;

#endif //__GBA_TYPES_H__