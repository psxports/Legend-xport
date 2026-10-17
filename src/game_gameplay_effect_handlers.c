#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8003B198(uint32 node)
{
    uint32 variant = r_u16(node + 58), texture = 270, frames = 4, value, result, limit, y, step;
    if (variant == 1)
        texture = 274;
    if (variant == 2)
    {
        texture = 265;
        frames = 3;
    }
    if (variant == 3)
    {
        texture = 268;
        frames = 3;
    }
    sub_80018214(r_u32(node + 12), r_u32(node + 16), 1, texture + r_u16(node + 44), (uint32)(sint32)r_s16(node + 52), (uint32)(sint32)r_s16(node + 54), (uint32)(sint32)r_s16(node + 56), 2);
    y = r_u32(node + 16);
    step = r_u32(node + 32);
    value = r_u16(node + 52);
    w_u32(node + 16, y + step);
    if (value < 17)
        w_u16(node + 52, 0);
    else
        w_u16(node + 52, r_u16(node + 52) - 16);
    if (r_u16(node + 54) < 17)
        w_u16(node + 54, 0);
    else
        w_u16(node + 54, r_u16(node + 54) - 16);
    if (r_u16(node + 56) < 17)
        w_u16(node + 56, 0);
    else
        w_u16(node + 56, r_u16(node + 56) - 16);
    value = r_u16(node + 46);
    limit = r_u16(node + 48);
    result = (uint16)(value + 1);
    w_u16(node + 46, result);
    if (limit < result)
    {
        w_u16(node + 44, r_u16(node + 44) + 1);
        result = r_u16(node + 44);
        w_u16(node + 46, 0);
        if (result == frames)
            return sub_80032FD0(node);
    }
    return result;
}

uint32 sub_80038BC4(uint32 node)
{
    uint32 y = r_u32(node + 16), velocity = r_u32(node + 44);
    uint32 x = r_u32(node + 12), xstep = r_u32(node + 28), z, zstep, texture, result;
    y += velocity;
    x += xstep;
    w_u32(node + 16, y);
    z = r_u32(node + 20);
    zstep = r_u32(node + 36);
    w_u32(node + 12, x);
    velocity = r_u32(node + 44);
    z += zstep;
    texture = r_u16(node + 48);
    velocity += 32;
    w_u32(node + 20, z);
    w_u32(node + 44, velocity);
    result = sub_80015B70(node + 12, texture, 5, 0, 128);
    y = r_u32(node + 16);
    if (r_s32(node + 52) < (sint32)y)
        return sub_80032FD0(node);
    return result;
}

uint32 sub_80039E24(uint32 node)
{
    uint32 requested = r_u32(node + 80), mesh, offset, value, result;
    if (requested == 1024)
    {
        sub_80039E00(node);
        return sub_80032FD0(node);
    }
    if (r_u16(node + 18) != requested)
        sub_80057A14(node + 16, requested);
    sub_80058484(node + 16, r_u32(node + 12));
    sub_800585D8(node + 16);
    mesh = r_u32(r_u32(node + 12));
    offset = r_u16(node + 84);
    value = r_u16(mesh + 168);
    w_u16(mesh + 168, value + offset);
    mesh = r_u32(r_u32(node + 12));
    offset = r_u16(node + 88);
    value = r_u16(mesh + 170);
    w_u16(mesh + 170, value + offset);
    mesh = r_u32(r_u32(node + 12));
    offset = r_u16(node + 92);
    value = r_u16(mesh + 172);
    result = value + offset;
    w_u16(mesh + 172, result);
    return result;
}

uint32 sub_8002AFE8(uint32 position, uint32 owner, uint32 target)
{
    uint32 node = sub_80032EF0(), words[4], i;
    if (!node)
        return 58;
    w_u32(node + 8, 58);
    for (i = 0; i < 4; ++i)
        words[i] = r_u32(position + 4 * i);
    for (i = 0; i < 4; ++i)
        w_u32(node + 12 + 4 * i, words[i]);
    w_u16(node + 36, 5);
    w_u16(node + 38, 0);
    w_u32(node + 28, owner);
    w_u32(node + 32, target);
    return 5;
}

uint32 sub_8003E924(uint32 node)
{
    uint32 tick = r_u16(node + 38) + 1, position[4], address, remaining, i;
    sint16 region[4];
    region[0] = -1;
    w_u16(node + 38, tick);
    if (tick & 3)
        return tick & 3;
    for (i = 0; i < 4; ++i)
        position[i] = r_u32(node + 12 + 4 * i);
    position[1] = sub_80046324(position[0], position[2], draft_local_address(region, sizeof(region)));
    position[0] -= 2048;
    position[0] += sub_80011B8C() & 4095;
    position[2] -= 2048;
    position[2] += sub_80011B8C() & 4095;
    sub_8004EC38(8);
    w_u16(0x8007158C, 64);
    w_u16(0x80071A50, 4);
    sub_8003278C(600);
    address = draft_local_address(position, sizeof(position));
    sub_80028EA0(address, 3, 7, 0);
    sub_80029C98(address, 2000, 0xC002, 4, 20, r_u32(node + 28), r_u32(node + 32));
    remaining = (uint16)(r_u16(node + 36) - 1);
    w_u16(node + 36, remaining);
    if (!remaining)
        return sub_80032FD0(node);
    return remaining;
}

uint32 sub_80033308(uint32 node)
{
    uint32 i, packet, depth, ordering, result;
    if (r_u16(node + 60) >= 31 || (r_u16(0x800719D0) & 1))
    {
        for (i = 0; i < 3; ++i)
            w_u32(0x1F800028 + 4 * i, r_u32(node + 12 + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
        sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
        for (i = 0; i < 3; ++i)
            draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
        for (i = 0; i < 5; ++i)
            draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
        for (i = 0; i < 6; ++i)
            draft_gte_data(i, r_u32(node + 28 + 4 * i));
        draft_gte_command(0x280030);
        packet = r_u32(0x80071680);
        w_u8(packet + 3, 9);
        w_u8(packet + 7, 44);
        w_u8(packet + 4, 3);
        w_u8(packet + 5, 3);
        w_u8(packet + 6, 6);
        w_u8(packet + 12, r_u8(0x800C0F08));
        w_u8(packet + 13, r_u8(0x800C0F0A));
        w_u8(packet + 20, r_u8(0x800C0F08) + r_u8(0x800C0F0C) - 1);
        w_u8(packet + 21, r_u8(0x800C0F0A));
        w_u8(packet + 28, r_u8(0x800C0F08));
        w_u8(packet + 29, r_u8(0x800C0F0A) + r_u8(0x800C0F0E) - 1);
        w_u8(packet + 36, r_u8(0x800C0F08) + r_u8(0x800C0F0C) - 1);
        w_u8(packet + 7, r_u8(packet + 7) | 3);
        w_u8(packet + 37, r_u8(0x800C0F0A) + r_u8(0x800C0F0E) - 1);
        w_u16(packet + 14, r_u16(0x800C0F06));
        w_u16(packet + 22, r_u16(0x800C0F04) | r_u16(0x80071784));
        draft_gte_command(0x158002D);
        depth = draft_gte_read(7);
        if (depth - 34 < 0x1186)
        {
            w_u32(packet + 8, draft_gte_read(12));
            w_u32(packet + 16, draft_gte_read(13));
            w_u32(packet + 24, draft_gte_read(14));
            draft_gte_data(0, r_u32(node + 52));
            draft_gte_data(1, r_u32(node + 56));
            draft_gte_command(0x180001);
            ordering = r_u32(0x8007184C) + 4 * ((depth - 32) >> 1);
            result = r_u32(0x80071680) + 40;
            w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ordering) & 0xFFFFFF));
            w_u32(0x80071680, result);
            w_u32(ordering, (r_u32(ordering) & 0xFF000000) | (packet & 0xFFFFFF));
            w_u32(packet + 32, draft_gte_read(14));
        }
    }
    result = (uint16)(r_u16(node + 60) - 1);
    w_u16(node + 60, result);
    return result ? result : sub_80032FD0(node);
}

uint32 sub_800347A4(uint32 node)
{
    uint32 position[4], oscillator, result, counter, i;
    w_u32(node + 16, r_u32(node + 16) + 40);
    for (i = 0; i < 4; ++i)
        position[i] = r_u32(node + 12 + 4 * i);
    position[0] -= (uint32)((sint16)r_u16(node + 32) >> 1);
    oscillator = r_u16(node + 32) + r_u16(node + 44);
    w_u16(node + 32, oscillator);
    if ((uint16)(oscillator + 511) >= 1023)
        w_u16(node + 44, 0 - r_u16(node + 44));
    if ((sint32)r_u32(node + 16) < (sint32)r_u32(node + 36))
    {
        result = (uint16)sub_80016F80(draft_local_address(position, sizeof(position)), 193, 5, node + 28);
        if (result)
            return result;
    }
    counter = r_u32(node + 40);
    w_u16(counter, r_u16(counter) - 1);
    return sub_80032FD0(node);
}

uint32 sub_800236DC(uint32 first_region, uint32 last_region)
{
    uint32 node = sub_80032EF0();
    if (node)
    {
        w_u32(node + 8, 14);
        w_u16(node + 12, first_region);
        w_u16(node + 14, last_region);
        w_u16(node + 16, 0);
    }
    return 14;
}

uint32 sub_80023500(uint32 region, uint32 counter)
{
    uint32 node = sub_80032EF0(), random, result, y;
    sint32 oscillator;
    if (!node)
        return 8;
    w_u32(node + 8, 8);
    random = sub_80011B8C();
    sub_8005129C((uint16)region, (random & 63) + 32, node + 12);
    w_u32(node + 36, r_u32(node + 16));
    random = sub_80011B8C();
    y = r_u32(node + 16);
    w_u16(node + 28, 0);
    w_u16(node + 30, 0);
    w_u32(node + 16, y - 5000 - 16 * (random & 127));
    oscillator = 2 * (sint32)(sub_80011B8C() & 255) - 256;
    w_u16(node + 32, oscillator);
    w_u16(node + 44, oscillator < 0 ? 16 : -16);
    w_u32(node + 40, counter);
    result = r_u16(counter) + 1;
    w_u16(counter, result);
    return result;
}

uint32 sub_80023628(uint32 region, uint32 counter)
{
    uint32 node = sub_80032EF0(), random, result, y;
    if (!node)
        return 55;
    w_u32(node + 8, 55);
    random = sub_80011B8C();
    sub_8005129C((uint16)region, (random & 63) + 32, node + 12);
    w_u32(node + 36, r_u32(node + 16));
    random = sub_80011B8C();
    y = r_u32(node + 16);
    w_u16(node + 28, 0);
    w_u16(node + 30, 0);
    w_u16(node + 32, 0);
    w_u32(node + 40, counter);
    w_u32(node + 16, y - 5000 - 16 * (random & 127));
    w_u16(node + 46, sub_80011B8C() & 3);
    result = r_u16(counter) + 1;
    w_u16(counter, result);
    return result;
}

uint32 sub_80034B4C(uint32 node)
{
    uint32 result = (uint32)(sint32)(sint16)r_u16(0x80071808), coordinate = 8000, low, high, sample;
    sint32 center, lower, upper, sum, step;
    if (!result)
        return result;
    if ((sint16)r_u16(node + 16) >= 10)
        return 0;
    if (r_u8(0x800AFFB0))
    {
        coordinate = r_u16(0x800AFFCC);
        if (r_u8(0x800B00D0))
        {
            sum = (sint16)coordinate + (sint16)r_u16(0x800B00EC);
            coordinate = ((uint32)sum + ((uint32)sum >> 31)) >> 1;
        }
    }
    else if (r_u8(0x800B00D0))
        coordinate = r_u16(0x800B00EC);
    center = (sint16)coordinate;
    if (center == 8000)
        return 8000;
    lower = (sint16)r_u16(node + 12);
    if (center < lower)
        return 1;
    upper = (sint16)r_u16(node + 14);
    if (upper < center)
        return 1;
    low = coordinate - 8;
    if ((sint16)low < lower)
        low = (uint32)lower;
    high = coordinate + 8;
    if (upper < (sint16)high)
        high = (uint32)upper;
    step = (sint32)(sub_80011B8C() & 127) * (sint16)(high - low) / 128;
    sample = low + (uint32)step;
    if ((sint16)high < (sint16)sample)
        sample = high;
    return sub_80023628((uint32)(sint32)(sint16)sample, node + 16);
}
