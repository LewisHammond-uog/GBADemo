#include "gba_bios.h"

void vblank_int_wait(void){
    asm volatile("swi 0x05");
}

ARM void InterruptHandler(void){
    REG_IF = INT_VBLANK;
    REG_IFBIOS |= INT_VBLANK;
}

void register_vblank_isr(void){
    REG_IME = 0x00;
    REG_INTERPUPT = (fnptr)InterruptHandler;
    REG_DISPSTAT |= DSTAT_VBL_IRQ;
    REG_IE |= INT_VBLANK;
    REG_IME = 0x1;
}