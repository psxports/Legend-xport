#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80038718(uint32 node)
{
    uint32 motion = r_u32(node + 12);
    uint32 x = r_u32(node + 16), y = r_u32(node + 20), z = r_u32(node + 24), pad = r_u32(node + 28);
    w_u32(motion, x);
    w_u32(motion + 4, y);
    w_u32(motion + 8, z);
    w_u32(motion + 12, pad);
    return sub_800471E8(r_u32(node + 12));
}

static void prop_scratch_vertex(uint32 index)
{
    draft_gte_data(2 * index, r_u32(0x1F800020));
    draft_gte_data(2 * index + 1, r_u32(0x1F800024));
}

uint32 sub_8003823C(void)
{
    uint32 i, source, packet, mode, slot, depth, red = r_u16(0x800719D0) & 1 ? 160 : 80;
    for (i = 0; i < 4; ++i)
    {
        source = 0x8006872C + 10 * i;
        packet = r_u32(0x80071680);
        w_u16(0x1F800020, r_u16(source));
        w_u16(0x1F800022, r_u16(source + 2));
        w_u16(0x1F800024, r_u16(source + 4));
        prop_scratch_vertex(0);
        w_u16(0x1F800022, 416);
        w_u16(0x1F800020, r_u16(source + 6));
        w_u16(0x1F800024, r_u16(source + 8));
        prop_scratch_vertex(1);
        w_u16(0x1F800022, 1184);
        prop_scratch_vertex(2);
        draft_gte_command(0x280030);
        w_u8(packet + 3, 6);
        w_u8(packet + 7, 48);
        w_u8(packet + 4, red);
        w_u8(packet + 5, red + 224);
        w_u8(packet + 6, 0);
        w_u8(packet + 12, 0);
        w_u8(packet + 13, 0);
        w_u8(packet + 14, 0);
        w_u8(packet + 20, 0);
        w_u8(packet + 21, 0);
        w_u8(packet + 22, 0);
        w_u8(packet + 7, 50);
        draft_gte_command(0x158002D);
        depth = (uint32)((sint32)draft_gte_read(7) >> 2);
        if (depth - 16 < 2484)
        {
            w_u32(packet + 8, draft_gte_read(12));
            w_u32(packet + 16, draft_gte_read(13));
            w_u32(packet + 24, draft_gte_read(14));
            slot = r_u32(0x8007184C) + 4 * depth;
            w_u32(packet, r_u32(slot) | 0x6000000);
            mode = packet + 28;
            w_u32(0x80071680, mode + 40);
            w_u32(slot, packet & 0xFFFFFF);
            sub_8005EEB8(mode, 1, 1, r_u16(0x80071782), 0);
            slot = r_u32(0x8007184C) + 4 * depth;
            w_u32(mode, (r_u32(mode) & 0xFF000000) | (r_u32(slot) & 0xFFFFFF));
            w_u32(slot, (r_u32(slot) & 0xFF000000) | (mode & 0xFFFFFF));
        }
    }
    return 0;
}

uint32 sub_800384B8(uint32 node)
{
    uint32 mesh = r_u32(node + 12), region = r_u16(0x800BC0CC), kind, state, x, y, z, pad, phase;
    sint32 sine, product;
    if (region == 0xFFFF)
        return 8 * region;
    kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
    if (kind < r_u16(node + 58) || kind > r_u16(node + 60))
        return 1;
    state = r_u16(node + 56);
    if (state > 1)
        return 1;
    x = r_u32(node + 16);
    y = r_u32(node + 20);
    z = r_u32(node + 24);
    pad = r_u32(node + 28);
    w_u32(mesh + 8, x);
    w_u32(mesh + 12, y);
    w_u32(mesh + 16, z);
    w_u32(mesh + 20, pad);
    w_u32(node + 40, (r_u32(node + 40) + (state ? 68 : 34)) & 4095);
    phase = r_u32(node + 40);
    w_u32(node + 44, (r_u32(node + 44) + (state ? 40 : 20)) & 4095);
    sine = (sint32)sub_8005C958(phase);
    if (!state)
    {
        product = (sint32)((uint32)sine * 700);
        w_u32(mesh + 12, r_u32(mesh + 12) + (uint32)(product / 4096));
        sine = (sint32)sub_8005C958(r_u32(node + 44));
        w_u16(mesh + 28, sine / 32);
        w_u16(0x80071858, 0);
        w_u16(0x8007185A, 0);
        w_u16(0x8007185C, 0);
        w_u16(0x800716E4, 0);
        return sub_8002D4F4(mesh, r_u32(node + 52));
    }
    w_u16(mesh + 26, sine / 16 - 512);
    product = (sint32)(190 * sub_8005C958(r_u32(node + 44)));
    w_u16(mesh + 28, product / 4096);
    sub_8002E410(mesh, r_u32(node + 52));
    if (r_u16(mesh + 88) & 2)
        return sub_8003823C();
    return 0;
}
