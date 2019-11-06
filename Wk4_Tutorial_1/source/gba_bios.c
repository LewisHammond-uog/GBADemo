#include "gba_bios.h"

/*
Function puts the CPU to sleep until we get a vblank interupt
*/
void vblank_int_wait(void){
    asm volatile("swi 0x05"); //Put the CPU to sleep until we get an interupt
}

/*
Function called whenever we get an interupt
*/
ARM void InterruptHandler(void){
    REG_IF = INT_VBLANK; //Let the register know that we have handled the interupt
    REG_IFBIOS |= INT_VBLANK; //Let the bios know that we have handled ther interupt
}

/*
Function sets up getting vblank interupts
*/
void register_vblank_isr(void){
    REG_IME = 0x00; //Temporarly disable getting interupts
    REG_INTERPUPT = (fnptr)InterruptHandler; //Point to the function to call when we get an interupt
    REG_DISPSTAT |= DSTAT_VBL_IRQ; //Tell the display taht we want to get vblank interupts
    REG_IE |= INT_VBLANK; //Tell the IME what that we want ot get vblank interupts
    REG_IME = 0x1; //Re-enabled getting interupts
}