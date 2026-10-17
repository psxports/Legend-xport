#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_8003BA20(uint32 node)
{
    uint32 tick = r_u16(node + 20), growth, next_growth, scale, yscale, phase, position[4], root, radius, width, random, product, i, address;
    sint32 shade;
    w_u16(node + 20, tick + 1);
    if (tick >= 31)
    {
        sub_8003B9E4(node);
        return sub_80032FD0(node);
    }
    growth = r_u32(node + 24);
    next_growth = growth + 128;
    shade = (sint32)(256 - (uint32)((sint32)next_growth >> 4));
    scale = (uint32)(sint32)(sint16)((growth << 2) + 4096);
    yscale = (uint32)(sint32)(sint16)((growth << 1) + 4096);
    w_u32(node + 24, next_growth);
    if (shade < 0)
        shade = 0;
    sub_8001D684(r_u32(node + 12), 1, scale, yscale, scale, (uint32)shade, 0, 0);
    sub_8001D684(r_u32(node + 16), 1, scale, yscale, scale, (uint32)shade, 0, 0);
    phase = r_u16(0x800719D0) & 3;
    if (phase)
        return phase;
    product = r_u32(0x800B0788) * scale;
    root = r_u32(node + 12);
    for (i = 0; i < 4; ++i)
        position[i] = r_u32(root + 8 + 4 * i);
    radius = (uint32)((sint32)product / 4096);
    address = draft_local_address(position, sizeof(position));
    sub_80029C98(address, radius, r_u16(node + 28), 4, 2, r_u32(node + 32), r_u32(node + 36));
    position[0] -= radius;
    position[2] -= radius;
    width = radius << 1;
    random = sub_80011B8C();
    product = width * (random & 255);
    position[0] += (uint32)((sint32)product / 256);
    random = sub_80011B8C();
    product = width * (random & 255);
    position[2] += (uint32)((sint32)product / 256);
    sub_8004EC38(8);
    w_u16(0x8007158C, 64);
    w_u16(0x80071A50, 4);
    sub_8003278C(700);
    return sub_80028EA0(address, 2, 7, 0);
}

uint32 sub_8003CFF0(uint32 node)
{
    uint32 position[4], address, i, remaining;
    uint16 region = 0xFFFF;
    if (!(r_u16(node + 38) & 7))
    {
        for (i = 0; i < 4; ++i)
            position[i] = r_u32(node + 12 + 4 * i);
        position[1] = sub_80046324(position[0], position[2], draft_local_address(&region, sizeof(region)));
        address = draft_local_address(position, sizeof(position));
        sub_8004EC38(8);
        w_u16(0x8007158C, 64);
        w_u16(0x80071A50, 4);
        sub_8003278C(700);
        sub_80028EA0(address, 3, 7, 0);
        for (i = 0; i < 3; ++i)
            sub_8002837C(address, 36, sub_80011B8C() & 4095, 1, 0, 50);
        sub_80029C98(address, 1000, r_u8(node + 42) | 0xC000, 4, 20, r_u32(node + 28), r_u32(node + 32));
        remaining = (uint16)(r_u16(node + 40) - 1);
        w_u16(node + 40, remaining);
        if (!remaining)
            return sub_80032FD0(node);
    }
    w_u16(node + 38, r_u16(node + 38) + 1);
    return sub_80031088(node + 12, (uint32)(sint32)(sint16)r_u16(node + 36), 160);
}
