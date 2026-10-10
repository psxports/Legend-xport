#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80018A9C(uint32 x, uint32 y, uint32 width, uint32 height, uint32 red, uint32 green, uint32 blue, uint32 depth)
{
    uint32 packet = r_u32(0x80071680), ot, link;
    w_u32(0x80071680, packet + 40);
    w_u8(packet + 3, 3);
    w_u8(packet + 7, 0x60);
    w_u8(packet + 4, (uint16)red);
    w_u8(packet + 5, (uint16)green);
    w_u8(packet + 6, (uint16)blue);
    ot = r_u32(0x8007184C);
    link = r_u32(packet);
    ot += 4 * (uint16)depth;
    w_u16(packet + 8, x);
    w_u16(packet + 10, y);
    w_u16(packet + 12, width);
    w_u16(packet + 14, height);
    w_u32(packet, (link & 0xFF000000) | (r_u32(ot) & 0xFFFFFF));
    link = (r_u32(ot) & 0xFF000000) | (packet & 0xFFFFFF);
    w_u32(ot, link);
    return link;
}

void sub_80050134(void)
{
    uint32 active = 0;
    sint32 frame;
    if (r_u8(0x800AFFB0))
        active = (r_u16(0x800AFFAA) & 3) != 0;
    if (r_u8(0x800B00D0) && (r_u16(0x800B00CA) & 3))
        active = 1;
    if (!active)
    {
        w_u16(0x800718D4, 0);
        return;
    }
    frame = (sint16)r_u16(0x800718D4);
    if (frame >= 31)
        return;
    if (frame == 0 || frame == 15)
        sub_8004486C(1, 1, 2, 950, 24000, 512);
    if ((uint32)r_u16(0x800718D4) - 11 >= 4)
        sub_80017FB0(290, 80, 1, 161);
    w_u16(0x800718D4, r_u16(0x800718D4) + 1);
}
