#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_8004EB88(uint32 icon, uint32 amount, uint32 maximum, uint32 x)
{
    if ((uint16)amount || (r_u16(0x800719D0) & 1))
        sub_80017FB0((uint32)((sint16)x + 16), 234, 1, r_u16(0x80068B08 + 2 * (uint16)icon));
    return sub_8004E9E4((uint32)(sint32)(sint16)(x + 30), 224, (uint16)amount, (uint16)maximum, 128);
}

uint32 sub_800156A4(uint32 x, uint32 y, uint32 depth, uint32 extra_width, uint32 extra_height, uint32 flip, uint32 texture, uint32 shade)
{
    uint32 packet = r_u32(0x80071680), descriptor, width, height;
    uint32 left, right, top, bottom, u, v, right_u, bottom_v, ordering, result;
    w_u32(0x80071680, packet + 40);
    descriptor = 0x800C0564 + 16 * texture;
    width = (uint32)((sint16)r_u16(descriptor + 8) - 1);
    height = (uint32)((sint16)r_u16(descriptor + 10) - 1);
    left = flip ? x + (uint32)(sint32)(sint16)r_u16(descriptor + 12) - width : x - (uint32)(sint32)(sint16)r_u16(descriptor + 12);
    left -= (uint32)((sint32)extra_width >> 1);
    right = left + width + extra_width;
    w_u16(packet + 16, right);
    w_u16(packet + 32, right);
    w_u16(packet + 8, left);
    w_u16(packet + 24, left);
    top = y - (uint32)(sint32)(sint16)r_u16(descriptor + 14) - (uint32)((sint32)extra_height >> 1);
    bottom = top + height + extra_height;
    w_u16(packet + 10, top);
    w_u16(packet + 18, top);
    w_u16(packet + 26, bottom);
    w_u16(packet + 34, bottom);
    u = r_u16(descriptor + 4);
    v = r_u16(descriptor + 6);
    right_u = u + width;
    bottom_v = v + height;
    w_u8(packet + 12, flip ? right_u : u);
    w_u8(packet + 13, v);
    w_u8(packet + 20, flip ? u : right_u);
    w_u8(packet + 21, v);
    w_u8(packet + 28, flip ? right_u : u);
    w_u8(packet + 29, bottom_v);
    w_u8(packet + 36, flip ? u : right_u);
    w_u8(packet + 37, bottom_v);
    w_u8(packet + 3, 9);
    w_u8(packet + 7, 44);
    w_u16(packet + 22, r_u16(descriptor));
    result = r_u8(packet + 7);
    u = r_u16(descriptor + 2);
    w_u8(packet + 4, shade);
    w_u8(packet + 5, shade);
    w_u8(packet + 6, shade);
    w_u8(packet + 7, result & 0xFC);
    w_u16(packet + 14, u);
    if ((sint32)depth >= 2500)
        depth = 2499;
    ordering = r_u32(0x8007184C) + 4 * depth;
    w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ordering) & 0xFFFFFF));
    result = (r_u32(ordering) & 0xFF000000) | (packet & 0xFFFFFF);
    w_u32(ordering, result);
    return result;
}

void sub_8004848C(uint32 depth)
{
    uint32 angle = r_u16(0x800BBFD4) & 4095, phase;
    sint32 half, bend, x, y;
    if (angle >= 2049)
        angle |= 0xF000;
    half = (sint16)angle >> 1;
    bend = half - (half >> 1);
    if (bend < -96)
        bend = -96;
    if (bend >= 129)
        bend = 128;
    y = (sint16)(r_u16(0x800717DC) - bend);
    x = -(sint32)((r_u16(0x800BBFD6) & 4095) >> 5);
    phase = r_u16(0x800719D0) & 7;
    while (x < 384)
    {
        sub_80011B8C();
        sub_800156A4((uint32)x, (uint32)y, depth, 32, 80, 0, phase + 234, r_u32(0x800718F4));
        phase = (phase + 1) & 7;
        x = (sint16)(x + 64);
    }
}
