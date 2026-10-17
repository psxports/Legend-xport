#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_8002A908(uint32 region, uint32 offset)
{
    uint32 node = sub_80032EF0(), mesh, contact, collision, heading;
    if (!node)
        return 49;
    w_u32(node + 8, 49);
    mesh = sub_8001A3BC();
    sub_8001A2FC(490, mesh);
    contact = sub_800471B4();
    w_u32(node + 20, contact);
    w_u32(contact + 16, r_u32(0x800B6C60));
    w_u32(contact + 20, (sint32)r_u32(0x800B6C60) >> 2);
    w_u16(contact + 26, 128);
    collision = sub_800474F4();
    w_u32(node + 16, collision);
    sub_80047534(collision, mesh, 1);
    w_u16(collision + 138, 0xFFFF);
    w_u32(node + 24, 0);
    w_u16(node + 28, 200);
    w_u16(node + 30, 0);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    heading = sub_8005129C((uint16)region, (uint32)(sint32)(sint16)offset, mesh + 8);
    w_u16(mesh + 26, (heading - 3072) & 4095);
    w_u32(mesh + 12, r_u32(mesh + 12) - 8000);
    w_u32(node + 12, mesh);
    w_u16(node + 102, 0xFFFF);
    w_u32(node + 32, sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 102));
    w_u16(node + 100, 100);
    w_u16(node + 104, 0);
    return 100;
}

uint32 sub_8003C434(uint32 node)
{
    uint32 mesh = r_u32(node + 12), proximity[8], address, state, mode, timer, i;
    uint32 contact, collision, cleanup_hint, result;
    address = draft_local_address(proximity, sizeof(proximity));
    sub_80051F74(mesh + 8, address);
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    state = r_u16(node + 104);
    if (!state)
    {
        timer = (uint16)(r_u16(node + 100) - 1);
        w_u16(node + 100, timer);
        if (timer)
            return timer;
        w_u16(node + 104, 1);
        w_u32(node + 24, 0);
        w_u16(node + 30, 0);
        return 1;
    }
    if (state == 1)
    {
        sub_800325CC(node + 24, mesh + 8, r_u32(node + 32), 0);
        if (r_u16(node + 30))
        {
            w_u16(node + 104, 2);
            sub_80032854(mesh, 193);
            w_u16(node + 100, 0);
            sub_8003278C(700);
            w_u32(0x1F800028, 0);
            w_u32(0x1F80002C, (uint32)-20);
            w_u32(0x1F800030, 0);
            sub_80022CC0(mesh + 8, 0x1F800028, 3, 7);
            for (i = 0; i < 3; ++i)
                sub_8002837C(mesh + 8, 36, sub_80011B8C() & 4095, 1, 0, 50);
        }
        mode = 1;
    }
    else if (state == 2)
    {
        timer = r_u16(node + 100);
        w_u16(node + 100, timer + 1);
        if (timer >= 61)
        {
            w_u16(node + 100, 0);
            w_u16(node + 104, 3);
        }
        mode = 2;
    }
    else if (state == 3)
    {
        w_u32(mesh + 12, r_u32(mesh + 12) - 100);
        timer = (uint16)(r_u16(node + 100) + 1);
        w_u16(node + 100, timer);
        if (timer == 80)
        {
            w_u16(node + 104, 0);
            w_u16(node + 100, (uint8)sub_80011B8C() + 127);
        }
        mode = 2;
    }
    else
    {
        /* TODO: Invalid states inherit an unspecified saved register in the original */
        return draft_unknown_return("8003C434 state outside constructor cycle 0..3");
    }
    sub_8005178C(mesh + 8, 2000, mesh + 24, r_u16(node + 102), node + 36);
    w_u16(mesh + 28, 0);
    w_u16(mesh + 24, 0);
    if (mode == 2)
    {
        contact = r_u32(node + 20);
        for (i = 0; i < 4; ++i)
            w_u32(contact + 4 * i, r_u32(mesh + 8 + 4 * i));
        w_u16(contact + 24, r_u16(mesh + 26));
        sub_800471E8(contact);
    }
    if (mode == 1)
    {
        collision = r_u32(node + 16);
        w_u32(collision + 132, 0x8002);
        w_u16(collision + 136, (((r_u16(0x800719D0) & 1) << 11) - 1024) & 4095);
        w_u16(collision + 148, 80);
        sub_800475A8(collision);
    }
    sub_80032A20(node + 36);
    if ((sint32)r_u32(address + 16 + 4 * r_u16(address + 24)) < 6000 && mode == 1)
    {
        uint32 floor_height = r_u32(node + 32);
        uint32 shadow_height = (uint32)((sint32)(r_u32(mesh + 12) - floor_height) >> 1) + floor_height;
        sub_80021288(r_u32(mesh + 8), r_u32(mesh + 16), floor_height, shadow_height, 2);
    }
    sub_80046278(r_u16(node + 102));
    legend_render_mesh_for_region_check(mesh, &cleanup_hint);
    result = sub_80032D9C(r_u16(node + 102), 15, cleanup_hint);
    if ((uint16)result)
    {
        sub_8003C3EC(node);
        return sub_80032FD0(node);
    }
    return result;
}
