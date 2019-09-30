#ifndef __GBA_BIOS_H__
#define __GBA_BIOS_H__

#include "gba_reg.h"
#include "gba_types.h"
#include "gba_macros.h"

typedef void (*fnptr)(void);

#define REG_IME (*(v_u16*)(0x4000208)) //Interupt master controller

#define REG_IE (*(v_u16*)(0x4000200))
#define REG_IF (*(v_u16*)(0x4000202))

#define REG_INTERPUPT *(fnptr*)(0x3007FFC)

#define REG_DISPSTAT (*(v_u16*)(0x4000004))
#define REG_IFBIOS (*(v_u16*)(0x3007FF8))

#define INT_VBLANK 0x001
#define INT_HBLANK 0x002
#define INT_COUNT 0x004

#define DSTAT_VBL_IRQ 0x0008
#define DSTAT_HBL_IRQ 0x0010
#define DSTAT_VCT_IRQ 0x0020

void vblank_int_wait(void);
ARM void InterruptHandler(void);
void register_vblank_isr(); //Register vblank interput subroutine


#endif //__GBA_BIOS_H__