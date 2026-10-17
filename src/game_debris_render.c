#include "psx.h"
#include "game_draft_signatures.h"

static void debris_light(uint32 color)
{
    draft_gte_data(6, r_u32(color));
    draft_gte_command(0xE80413);
}

uint32 sub_80036DB4(uint32 node)
{
    static const uint32 sizes[6] = {20, 28, 32, 24, 36, 40};
    static const uint32 opcodes[6] = {32, 48, 36, 40, 56, 44};
    uint32 floor_height, packet, primitive, kind, depth, link, i, stride, length;
    sub_80030E5C(node + 12, node + 28, 25, 0);
    floor_height = sub_80046324(r_u32(node + 12), r_u32(node + 20), node + 136);
    w_u32(node + 64, floor_height);
    sub_800325CC(node + 52, node + 12, floor_height, 0);
    if ((sint16)r_u16(node + 58))
        return sub_80032FD0(node);
    if (!(r_u16(0x800719D0) & 7))
    {
        w_u32(0x1F800028, 0);
        w_u32(0x1F80002C, 5);
        w_u32(0x1F800030, 0);
        sub_80022CC0(node + 12, 0x1F800028, 2, 4);
    }
    w_u32(0x1F800028, r_u32(node + 12) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(node + 16) - r_u32(0x800BBFC8));
    w_u32(0x1F800030, r_u32(node + 20) - r_u32(0x800BBFCC));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    for (i = 0; i < 3; ++i)
        draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
    for (i = 0; i < 5; ++i)
        draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
    packet = r_u32(0x80071680);
    primitive = r_u32(node + 68);
    sub_80046278(r_u16(node + 136));
    sub_8001B7A0(0);
    kind = r_u32(node + 60) & 7;
    if (kind > 5)
    {
        w_u32(0x80071680, packet);
        return 0;
    }
    for (i = 0; i < 6; ++i)
        draft_gte_data(i, r_u32(node + 72 + 4 * i));
    draft_gte_command(0x280030);
    if (kind == 2)
        w_u32(packet + 12, r_u32(primitive + 4));
    if (kind == 5)
        w_u32(packet + 36, r_u32(primitive + 16));
    draft_gte_command(0x158002D);
    depth = (uint32)((sint32)draft_gte_read(7) >> 2);
    if (depth - 16 >= 2484)
    {
        w_u32(0x80071680, packet);
        return 0;
    }
    stride = kind == 0 || kind == 3 ? 4 : 8;
    w_u32(packet + 8, draft_gte_read(12));
    w_u32(packet + 8 + stride, draft_gte_read(13));
    w_u32(packet + 8 + 2 * stride, draft_gte_read(14));
    if (kind >= 3)
    {
        draft_gte_data(0, r_u32(node + 96));
        draft_gte_data(1, r_u32(node + 100));
        draft_gte_command(0x180001);
        if (kind == 5)
        {
            w_u32(packet + 12, r_u32(primitive + 4));
            w_u32(packet + 20, r_u32(primitive + 8));
        }
        w_u32(packet + 8 + 3 * stride, draft_gte_read(14));
    }
    draft_gte_data(0, r_u32(node + 104));
    draft_gte_data(1, r_u32(node + 108));
    debris_light(primitive);
    if (kind == 1 || kind == 4)
    {
        w_u32(packet + 4, draft_gte_read(22));
        debris_light(primitive + 4);
        w_u32(packet + 12, draft_gte_read(22));
        debris_light(primitive + 8);
        if (kind == 4)
        {
            w_u32(packet + 20, draft_gte_read(22));
            debris_light(primitive + 12);
        }
    }
    else if (kind == 2)
    {
        w_u32(packet + 20, r_u32(primitive + 8));
        w_u32(packet + 28, r_u32(primitive + 12));
    }
    else if (kind == 5)
        w_u32(packet + 28, r_u32(primitive + 12));
    length = sizes[kind] / 4 - 1;
    link = r_u32(0x8007184C) + 4 * depth;
    w_u32(packet, r_u32(link) | (length << 24));
    w_u32(link, packet & 0xFFFFFF);
    w_u32(packet + (kind == 1 ? 20 : kind == 4 ? 28 : 4), draft_gte_read(22));
    w_u8(packet + 3, length);
    w_u8(packet + 7, opcodes[kind]);
    w_u32(0x80071680, packet + sizes[kind]);
    return opcodes[kind];
}
