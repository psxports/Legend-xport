#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_8002AA44(uint32 region, uint32 offset, uint32 variant)
{
    uint32 node = sub_80032EF0(), mesh, collision, heading, result;
    if (!node)
        return 50;
    w_u32(node + 8, 50);
    mesh = sub_8001A3BC();
    sub_8001A2FC(491, mesh);
    collision = sub_800474F4();
    w_u32(node + 16, collision);
    sub_80047534(collision, mesh, 1);
    w_u16(collision + 138, 0xFFFF);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    heading = (sub_8005129C((uint16)region, (uint32)(sint32)(sint16)offset, mesh + 8) - 1024) & 4095;
    w_u16(mesh + 26, heading);
    if ((uint16)variant)
        w_u16(mesh + 26, heading + 1024);
    w_u32(mesh + 12, r_u32(mesh + 12) - r_u32(0x800B6C98));
    w_u32(node + 12, mesh);
    w_u16(node + 24, 0xFFFF);
    w_u32(node + 20, sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 24));
    w_u32(node + 32, 8192);
    w_u32(node + 28, 0);
    w_u16(node + 36, 1);
    result = sub_80011B8C() & 1;
    if (result)
    {
        result = 0 - r_u32(node + 32);
        w_u16(node + 36, 0);
        w_u32(node + 32, result);
    }
    return result;
}

uint32 sub_8003C7F4(uint32 node)
{
    uint32 mesh = r_u32(node + 12), proximity[8], collision, velocity, phase, cleanup_hint;
    uint32 angle, channel, volume, result;
    sub_80051F74(mesh + 8, draft_local_address(proximity, sizeof(proximity)));
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    angle = sub_80046D0C((uint32)(sint32)(sint16)r_u16(mesh + 28));
    velocity = r_u32(node + 32) + ((sint16)angle < 0 ? 128 : (uint32)-128);
    velocity -= (uint32)((sint32)(sint16)angle >> 2);
    w_u32(node + 32, velocity);
    phase = r_u32(node + 28) + velocity;
    w_u32(node + 28, phase);
    w_u16(mesh + 28, (sint32)phase >> 8);
    collision = r_u32(node + 16);
    w_u32(collision + 132, 0x8002);
    w_u16(collision + 136, (((r_u16(0x800719D0) & 1) << 11) - 1024) & 4095);
    w_u16(collision + 148, 80);
    sub_800475A8(collision);
    sub_80046278(r_u16(node + 24));
    legend_render_mesh_for_region_check(mesh, &cleanup_hint);
    if (((uint16)(angle - 1) < 399 && r_u16(node + 36) && (sint32)r_u32(node + 32) < 0) || ((uint16)(angle + 399) < 399 && !r_u16(node + 36) && (sint32)r_u32(node + 32) > 0))
    {
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(32000);
        sub_8004486C(1, channel, 1, 300, volume, r_u16(0x80071A20));
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(32000);
        sub_8004486C(1, channel, 21, 300, volume, r_u16(0x80071A20));
        w_u16(node + 36, r_u16(node + 36) ^ 1);
        cleanup_hint = 21;
    }
    result = sub_80032D9C(r_u16(node + 24), 15, cleanup_hint);
    if ((uint16)result)
    {
        sub_8003C7B8(node);
        return sub_80032FD0(node);
    }
    return result;
}
