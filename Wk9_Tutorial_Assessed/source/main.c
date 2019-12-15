#include "gba.h"
#include <string.h>

#include "rocket-ship.h"

//Define a register for DMA 
typedef struct DMA_REC
{
	const void* src;
	void* dst;
	u32 cnt;
}DMA_REC;

//get a pointer to the DMA memory location 
//access this as an array to get addresses 0 -> 3
#define REG_DMA ((volatile DMA_REC*)0x040000B0)

//define our DMA control register variables
#define DMA_DST_INC		(0x00 << 21)
#define DMA_DST_DEC		(0x01 << 21)
#define DMA_DST_FIXED	(0x02 << 21)
#define DMA_DES_RELOAD	(0x03 << 21)

#define DMA_SRC_INC		(0x00 << 23)
#define DMA_SRC_DEC		(0x01 << 23)
#define DMA_SRC_FIXED	(0x02 << 23)

#define DMA_REPEAT		(0x01 << 25)

#define DMA_16			(0x00 << 26)
#define DMA_32			(0x01 << 26)

#define DMA_AT_NOW		(0x00 << 28)
#define DMA_AT_VBLANK	(0x01 << 28)
#define DMA_AT_HBLANK	(0x02 << 28)
#define DMA_AT_REFRESH	(0x03 << 28)

#define DMA_IRQ			(0x01 << 30)

#define DMA_ENABLE		(0x01 << 31)

#define DMA_NOW			(DMA_ENABLE | DMA_AT_NOW)
#define DMA_16NOW		(DMA_NOW | DMA_16)
#define DMA_32NOW		(DMA_NOW|DMA_32)
//dma cpy flags
#define DMA_CPY16		DMA_16NOW
#define DMA_CPY32		DMA_32NOW
//dma fill flags
#define DMA_FILL16		(DMA_NOW|DMA_SRC_FIXED|DMA_16)
#define DMA_FILL32		(DMA_NOW|DMA_SRC_FIXED|DMA_32)

//DMA TRANSFER COPY & FILL routines
#define DMA_TRANSFER(_dst, _src, _count, _ch, _mode) \
do{													\
	REG_DMA[_ch].cnt = 0;							\
	REG_DMA[_ch].src = (const void*)(_src);			\
	REG_DMA[_ch].dst = (void*)(_dst);				\
	REG_DMA[_ch].cnt = _count | _mode;				\
}while(0)

INLINE void dma_cpy(void* dst, const void* src, u32 count, u32 mode)
{
	REG_DMA[3].cnt = 0;
	REG_DMA[3].src = src;
	REG_DMA[3].dst = dst;
	REG_DMA[3].cnt = count | mode;
}

INLINE void dma_fill(void* dst, volatile u32 src, u32 count, u32 mode)
{
	REG_DMA[3].cnt = 0;
	REG_DMA[3].src = (const void*)&src;
	REG_DMA[3].dst = dst;
	REG_DMA[3].cnt = count | mode | DMA_SRC_FIXED;
}

INLINE void dma_word_cpy(void* dst, const void* src, u32 size)
{
	dma_cpy(dst, src, size>>2, DMA_CPY32);
}

INLINE void dma_word_fill(void* dst, volatile u32 src, u32 size)
{
	dma_fill(dst, src, size>>2, DMA_FILL32);
}

#define DMA_HDMA (DMA_ENABLE|DMA_REPEAT|DMA_AT_HBLANK|DMA_DST_FIXED)

void drawBackground();

u32 g_pal[160];
u32 g_palIndex = 0;

int main( int argc, char* argv[])
{
	REG_DISPCNT = VIDEOMODE_4 | BGMODE_2;
	register_vblank_isr();
	dma_word_cpy(PAL_BG_BLOCK(0), rocket_shipPal, rocket_shipPalLen);
	for (int i = 0; i < 160; ++i)
	{
		g_pal[i] = (i << 24) + (i << 16) + (i << 8) + i;
	}

	page_flip();
	drawBackground();
	page_flip();

	while (true)
	{
		vblank_intr_wait();
		PollKeys();
		
		++g_palIndex;
		g_palIndex = g_palIndex % 160;
		drawBackground();
		page_flip();
	}
	

	return 0;
}

void drawBackground()
{
	dma_word_fill(vid_page, g_pal[g_palIndex], SCREEN_H * SCREEN_W * 2);

	DMA_TRANSFER(PAL_BG_BLOCK(0), &rocket_shipPal[g_palIndex], 1, 3, DMA_HDMA);

}