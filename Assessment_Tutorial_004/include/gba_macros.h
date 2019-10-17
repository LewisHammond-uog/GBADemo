#pragma once

#ifndef __GBA_MACROS_H__
#define __GBA_MACROS_H__

#if __INTELLISENSE__
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#ifndef NULL
#define NULL (void*)0
#endif

#define INLINE static inline

#define ARM __attribute__((__target__("arm"))) //Target ARM 32 bit Arcitecture
#define THUMB __attribute__((__target__("thumb"))) //Target thumb 16 bit Arcitecture

#define PACKED(n) __attribute__((packed, aligned(n)))

#endif //__GBA_MACROS_H__
