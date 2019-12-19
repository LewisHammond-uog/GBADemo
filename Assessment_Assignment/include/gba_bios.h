/*
BIOS defines and interupt handiling
*/

#ifndef __GBA_BIOS_H__
#define __GBA_BIOS_H__

#include "gba_reg.h"
#include "gba_types.h"
#include "gba_macros.h"

typedef void (*fnptr)(void); //Create a function pointer type

#define REG_IME (*(v_u16*)(0x4000208)) //Interupt master controller

#define REG_IE (*(v_u16*)(0x4000200)) //Register that is used to store what interupts we want to be notified about
#define REG_IF (*(v_u16*)(0x4000202)) //Register that is set to when we get an interupt. Need to 'notify' this that we have proccessed an interupt

#define REG_INTERPUPT *(fnptr*)(0x3007FFC) //Register that stores the function that we want to run when an interupt is triggered

#define REG_DISPSTAT (*(v_u16*)(0x4000004)) //Register for display interupts
#define REG_IFBIOS (*(v_u16*)(0x3007FF8))//BIOS Register that is set to when we get an interupt. Need to 'notify' this that we have proccessed an interupt

#define INT_VBLANK 0x001 //Mem value for vblank interupt
#define INT_HBLANK 0x002 //Mem value for hblank interupt
#define INT_COUNT 0x004 //Mem value for count interupt

#define DSTAT_VBL_IRQ 0x0008 //Display mem value for vblank interupt
#define DSTAT_HBL_IRQ 0x0010 //Display mem value for hblank interupt
#define DSTAT_VCT_IRQ 0x0020 //Display mem value for vcount interupt

void vblank_int_wait(void); //Function for waiting for vblank
ARM void InterruptHandler(void);
void register_vblank_isr(); //Register vblank interput subroutine


#endif //__GBA_BIOS_H__