#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80028894(uint32 position)
{
    uint32 item = sub_80032EF0();
    uint32 x, y, z, pad, random;
    if (!item)
        return 27u;
    w_u32(item + 8u, 27u);
    x = r_u32(position);
    y = r_u32(position + 4u);
    z = r_u32(position + 8u);
    pad = r_u32(position + 12u);
    w_u32(item + 12u, x);
    w_u32(item + 16u, y);
    w_u32(item + 20u, z);
    w_u32(item + 24u, pad);
    random = sub_80011B8C();
    w_u32(item + 44u, 0xFFFFFF00u - (random & 127u));
    w_u32(item + 48u, 128u);
    w_u16(0x1F800020u, 0);
    random = sub_80011B8C();
    w_u16(0x1F800022u, random & 0xFFFu);
    w_u16(0x1F800024u, 0);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    random = sub_80011B8C();
    w_u16(0x1F800020u, (random & 63u) + 32u);
    w_u16(0x1F800022u, 0);
    w_u16(0x1F800024u, 0);
    return sub_8005CDD8(0x1F800000u, 0x1F800020u, item + 28u);
}

uint32 sub_80038B08(uint32 node)
{
    uint32 shade = r_u16(node + 48u), size, result;
    w_u32(node + 16u, r_u32(node + 16u) + r_u32(node + 44u));
    w_u32(node + 12u, r_u32(node + 12u) + r_u32(node + 28u));
    w_u32(node + 20u, r_u32(node + 20u) + r_u32(node + 36u));
    w_u32(node + 44u, r_u32(node + 44u) + 32u);
    sub_80016B84(node + 12u, 242u, 3u, 2u, shade, shade >> 1, shade >> 2);
    size = r_u32(node + 48u);
    result = (uint32)((sint32)size < 4);
    if (result)
        return sub_80032FD0(node);
    result = size - 4u;
    w_u32(node + 48u, result);
    return result;
}
