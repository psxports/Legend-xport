#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80022CC0(uint32 position, uint32 velocity, uint32 texture, uint32 frame_count)
{
    uint32 node = sub_80032EF0(), words[4], i, result, x, z;
    if (!node) return node;
    w_u32(node + 8, 0);
    for (i = 0; i < 4; ++i) words[i] = r_u32(position + 4 * i);
    for (i = 0; i < 4; ++i) w_u32(node + 12 + 4 * i, words[i]);
    w_u32(node + 12, r_u32(node + 12) + (uint32)((sint32)r_u32(velocity) >> 1));
    w_u32(node + 20, r_u32(node + 20) + (uint32)((sint32)r_u32(velocity + 8) >> 1));
    for (i = 0; i < 4; ++i) words[i] = r_u32(velocity + 4 * i);
    for (i = 0; i < 4; ++i) w_u32(node + 28 + 4 * i, words[i]);
    x = r_u32(node + 28);
    z = r_u32(node + 36);
    w_u16(node + 50, frame_count - 1);
    w_u16(node + 48, texture);
    w_u16(node + 56, 128);
    w_u16(node + 54, 128);
    w_u16(node + 52, 128);
    w_u16(node + 46, 0);
    w_u16(node + 44, 0);
    w_u32(node + 28, x - (uint32)((sint32)x >> 3));
    result = r_u32(node + 32);
    w_u32(node + 36, z - (uint32)((sint32)z >> 3));
    result -= 20;
    w_u32(node + 32, result);
    return result;
}

uint32 sub_80033104(uint32 node)
{
    uint32 result = r_u16(0x800719D0) & 1;
    if (result) {
        sub_80022CC0(node + 12, node + 28, r_u16(node + 48), r_u16(node + 50));
        result = (uint16)(r_u16(node + 46) - 1);
        w_u16(node + 46, result);
        if (!result) return sub_80032FD0(node);
    }
    return result;
}
