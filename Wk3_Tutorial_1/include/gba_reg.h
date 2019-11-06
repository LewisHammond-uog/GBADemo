/*
Header to contain all of the GBA Memory address defines that we use
*/
#ifndef __GBA_REG_H__
#define __GBA_REG_H__

//Base adress for external working ram
//256k in size
#define	EWRAM	0x02000000
#define	EWRAM_END	0x02040000 // From This address up to 0x02FFFFFF is not utilised

//Start for Internal Working Ram
//32k in size
#define IWRAM 0x03000000

//Start Adress of I/O Hardware registers
#define REG_BASE 0x04000000

//Start of the Video Ram
//96k in size
#define VRAM 0x06000000

//Start of the save cart ram
//64k in size
#define	SRAM 0x0E000000

#endif //__GBA_REG_H__