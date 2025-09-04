#ifndef _IN_EXT_TEX_H
#define _IN_EXT_TEX_H

#include <PR/ultratypes.h>

s32 extTexInit();
u8 *extTexLoad(u8 type, u16 id, u16 texnum, u32 *width, u32 *height);
u8 extTexExists(u8 type, u16 id, u16 texnum);
u8 extTexFontID(struct font *font);

#endif
