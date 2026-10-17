#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80029DD4(uint32 position, uint32 vertical_velocity, uint32 period, uint32 scale, uint32 kind, uint32 red, uint32 green, uint32 blue)
{
    uint32 node = sub_80032EF0(), x, y, z, pad, i, offset, random;
    if (!node)
        return 0;
    w_u32(node + 8, 44);
    x = r_u32(position);
    y = r_u32(position + 4);
    z = r_u32(position + 8);
    pad = r_u32(position + 12);
    w_u32(node + 12, x);
    w_u32(node + 16, y);
    w_u32(node + 20, z);
    w_u32(node + 24, pad);
    w_u32(node + 32, (uint32)(sint32)(sint16)vertical_velocity);
    w_u32(node + 28, 0);
    w_u32(node + 36, 0);
    w_u16(node + 48, period);
    w_u16(node + 50, scale - 1);
    w_u16(node + 52, red);
    w_u16(node + 54, green);
    w_u16(node + 56, blue);
    w_u16(node + 58, kind);
    w_u16(node + 46, 0);
    w_u16(node + 44, 0);
    for (i = 0; i < 8; ++i)
    {
        offset = node + 60 + 8 * i;
        w_u16(offset, (uint32)-256);
        random = sub_80011B8C();
        w_u16(offset + 2, (uint32)-256);
        w_u16(offset, r_u16(offset) + (random & 511));
        random = sub_80011B8C();
        w_u16(offset + 4, (uint32)-256);
        w_u16(offset + 2, r_u16(offset + 2) + (random & 511));
        random = sub_80011B8C();
        w_u16(offset + 4, r_u16(offset + 4) + (random & 511));
    }
    return 0;
}

uint32 sub_8003AF78(uint32 node)
{
    uint32 kind = r_u16(node + 58), first = 270, count = 4, i, j, address, value, result;
    uint32 position[4];
    if (kind == 1)
        first = 274;
    if (kind == 2 || kind == 3)
    {
        first = kind == 2 ? 265 : 268;
        count = 3;
    }
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 4; ++j)
            position[j] = r_u32(node + 12 + 4 * j);
        for (j = 0; j < 3; ++j)
            position[j] += (uint32)(sint32)(sint16)r_u16(node + 60 + 8 * i + 2 * j);
        sub_80016B84(draft_local_address(position, sizeof(position)), (uint16)(first + r_u16(node + 44)), r_u16(node + 50), 2, r_u16(node + 52), r_u16(node + 54), r_u16(node + 56));
    }
    for (i = 0; i < 3; ++i)
        w_u32(node + 12 + 4 * i, r_u32(node + 12 + 4 * i) + r_u32(node + 28 + 4 * i));
    for (i = 0; i < 3; ++i)
    {
        address = node + 52 + 2 * i;
        value = r_u16(address);
        w_u16(address, value < 5 ? 0 : value - 4);
    }
    value = r_u16(node + 48);
    result = (uint16)(r_u16(node + 46) + 1);
    w_u16(node + 46, result);
    if (value < result)
    {
        w_u16(node + 44, r_u16(node + 44) + 1);
        result = r_u16(node + 44);
        w_u16(node + 46, 0);
        if (result == count)
            return sub_80032FD0(node);
    }
    return result;
}
