#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static uint32 particle_project(void)
{
    draft_gte_data(0, r_u32(0x1F800020));
    draft_gte_data(1, r_u32(0x1F800024));
    draft_gte_command(0x180001);
    return draft_gte_read(14);
}

uint32 sub_80016B84(uint32 position, uint32 texture, uint32 scale, uint32 semitransparency, uint32 red, uint32 green, uint32 blue)
{
    uint32 descriptor, packet, xy, depth, ot, shift = scale & 31;
    w_u32(0x1F800030, r_u32(position + 8) - r_u32(0x800BBFCC));
    w_u32(0x1F800028, r_u32(position) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(position + 4) - r_u32(0x800BBFC8));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    if (r_u32(0x1F800030) > 39999 || r_u32(0x1F800028) + 20000 > 40000 || r_u32(0x1F80002C) + 20000 > 40000)
        return 0;
    if ((sint32)r_u32(0x1F800030) < 32)
        w_u32(0x1F800030, 32);
    descriptor = 0x800C0564 + 16 * (uint16)texture;
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    draft_gte_control(5, r_u32(0x1F800028));
    draft_gte_control(6, r_u32(0x1F80002C));
    draft_gte_control(7, r_u32(0x1F800030));
    packet = r_u32(0x80071680);
    w_u16(0x1F800020, (0u - (uint32)(sint32)(sint16)r_u16(descriptor + 12)) << shift);
    w_u32(0x80071680, packet + 40);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, (0u - (uint32)(sint32)(sint16)r_u16(descriptor + 14)) << shift);
    xy = particle_project();
    w_u8(packet + 3, 9);
    w_u8(packet + 7, (uint16)semitransparency ? 46 : 44);
    w_u8(packet + 4, red);
    w_u8(packet + 5, green);
    w_u8(packet + 6, blue);
    w_u32(packet + 8, xy);
    w_u16(0x1F800020, r_u16(0x1F800020) + ((uint32)(sint32)(sint16)r_u16(descriptor + 8) << shift));
    xy = particle_project();
    w_u16(packet + 22, r_u16(descriptor));
    if ((uint16)semitransparency)
        w_u16(packet + 22, r_u16(packet + 22) | r_u16(0x8007177E + 2 * (uint16)semitransparency));
    w_u32(packet + 16, xy);
    w_u16(0x1F800022, r_u16(0x1F800022) + ((uint32)(sint32)(sint16)r_u16(descriptor + 10) << shift));
    xy = particle_project();
    w_u16(packet + 14, r_u16(descriptor + 2));
    w_u32(packet + 32, xy);
    w_u16(0x1F800020, r_u16(0x1F800020) - ((uint32)(sint32)(sint16)r_u16(descriptor + 8) << shift));
    xy = particle_project();
    w_u8(packet + 12, r_u8(descriptor + 4));
    w_u8(packet + 13, r_u8(descriptor + 6));
    w_u8(packet + 20, r_u8(descriptor + 4) + r_u8(descriptor + 8) - 1);
    w_u8(packet + 21, r_u8(descriptor + 6));
    w_u8(packet + 28, r_u8(descriptor + 4));
    w_u8(packet + 29, r_u8(descriptor + 6) + r_u8(descriptor + 10) - 1);
    w_u8(packet + 36, r_u8(descriptor + 4) + r_u8(descriptor + 8) - 1);
    w_u8(packet + 37, r_u8(descriptor + 6) + r_u8(descriptor + 10) - 1);
    w_u32(packet + 24, xy);
    depth = (uint32)((sint32)r_u32(0x1F800030) >> 4);
    if (depth - 1 < 2499)
    {
        ot = r_u32(0x8007184C) + 4 * depth;
        w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ot) & 0xFFFFFF));
        w_u32(ot, (r_u32(ot) & 0xFF000000) | (packet & 0xFFFFFF));
    }
    return 1;
}

uint32 sub_8003302C(uint32 node)
{
    uint32 result = (uint16)sub_80016B84(node + 12, (uint16)(r_u16(node + 44) + 167), r_u16(node + 50), 4, r_u16(node + 52), r_u16(node + 54), r_u16(node + 56));
    uint32 tick, vx, vy, vz;
    if (!result)
        return sub_80032FD0(node);
    tick = (uint16)(r_u16(node + 46) + 1);
    vx = r_u32(node + 28);
    vy = r_u32(node + 32);
    vz = r_u32(node + 36);
    w_u16(node + 46, tick);
    w_u32(node + 12, r_u32(node + 12) + vx);
    w_u32(node + 16, r_u32(node + 16) + vy);
    result = r_u16(node + 48) < tick;
    w_u32(node + 20, r_u32(node + 20) + vz);
    if (result)
    {
        w_u16(node + 46, 0);
        w_u16(node + 44, r_u16(node + 44) + 1);
        result = 7;
        if (r_u16(node + 44) == 7)
            return sub_80032FD0(node);
    }
    return result;
}
