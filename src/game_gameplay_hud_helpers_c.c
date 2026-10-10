#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8004E570(uint32 kind)
{
    uint32 packet = r_u32(0x80071680), ot, i;
    kind = (uint16)kind;
    w_u32(0x80071680, packet + 40);
    w_u8(packet + 3, 8);
    w_u8(packet + 7, 0x38);
    if (kind <= 2)
    {
        for (i = 0; i < 3; ++i)
        {
            w_u8(packet + 4 + 8 * i, kind == 1 ? 255 : 0);
            w_u8(packet + 5 + 8 * i, kind == 0 ? 255 : 0);
            w_u8(packet + 6 + 8 * i, kind == 2 ? 255 : 0);
        }
        w_u8(packet + 28, 255);
        w_u8(packet + 29, 255);
        w_u8(packet + 30, 255);
    }
    /* GTE vector registers consume the low halfword of each Z carrier */
    draft_gte_data(0, 0xFFF3FFF3);
    draft_gte_data(1, 0);
    draft_gte_data(2, 0xFF9C0000);
    draft_gte_data(3, 0);
    draft_gte_data(4, 0x00060000);
    draft_gte_data(5, 0);
    draft_gte_command(0x280030);
    ot = r_u32(0x8007184C) + 8;
    w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ot) & 0xFFFFFF));
    w_u32(ot, (r_u32(ot) & 0xFF000000) | (packet & 0xFFFFFF));
    w_u32(packet + 8, draft_gte_read(12));
    w_u32(packet + 16, draft_gte_read(13));
    w_u32(packet + 24, draft_gte_read(14));
    draft_gte_data(0, 0xFFF3000D);
    draft_gte_data(1, 0);
    draft_gte_command(0x180001);
    w_u32(packet + 32, draft_gte_read(14));
    return packet + 32;
}
