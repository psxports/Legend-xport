#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_8002823C(uint32 region, uint32 offset)
{
    uint32 node = sub_80032EF0(), root, mesh, collision, heading, floor_height;
    if (!node)
        return 0;
    w_u32(node + 8, 21);
    root = sub_8001A3BC();
    mesh = sub_8001A3BC();
    sub_8001A2FC(35, mesh);
    sub_8001A320(root, 1);
    sub_8001A2BC(root, mesh, 0, (uint32)-825, 0);
    collision = sub_800474F4();
    w_u32(node + 20, collision);
    sub_80047534(collision, mesh, 0);
    w_u16(collision + 138, 0xFFFF);
    w_u32(node + 24, 0);
    w_u16(node + 28, 200);
    w_u16(node + 30, 0);
    w_u16(root + 24, 0);
    w_u16(root + 28, 0);
    heading = sub_8005129C((uint16)region, (uint32)(sint32)(sint16)offset, root + 8);
    w_u16(root + 26, (heading - 1024) & 4095);
    w_u32(root + 12, r_u32(root + 12) - 8000);
    w_u16(node + 108, 0xFFFF);
    floor_height = sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108);
    w_u16(node + 110, 0);
    w_u32(node + 12, root);
    w_u32(node + 16, mesh);
    w_u16(node + 112, offset);
    return floor_height;
}

uint32 sub_80028480(uint32 region, uint32 offset)
{
    uint32 node = sub_80032EF0(), root, mesh, collision, heading, floor_height;
    if (!node)
        return 23;
    w_u32(node + 8, 23);
    root = sub_8001A3BC();
    mesh = sub_8001A3BC();
    sub_8001A2FC(35, mesh);
    sub_8001A320(root, 1);
    sub_8001A2BC(root, mesh, 0, (uint32)-825, 0);
    collision = sub_800474F4();
    w_u32(node + 20, collision);
    sub_80047534(collision, mesh, 0);
    w_u16(collision + 138, 0xFFFF);
    w_u32(node + 24, 0);
    w_u16(node + 28, 150);
    w_u16(node + 30, 0);
    w_u16(root + 24, 0);
    w_u16(root + 28, 0);
    heading = sub_8005129C((uint16)region, (uint32)(sint32)(sint16)offset, root + 8);
    w_u16(root + 26, (heading - 1024) & 4095);
    w_u32(root + 12, r_u32(root + 12) - 12000);
    w_u16(node + 108, 0xFFFF);
    floor_height = sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108);
    w_u16(node + 110, 0);
    w_u32(node + 12, root);
    w_u32(node + 16, mesh);
    return floor_height;
}

static void dropping_object_dust(uint32 position)
{
    w_u32(0x1F800028, 0);
    w_u32(0x1F80002C, (uint32)-20);
    w_u32(0x1F800030, 0);
    sub_80022CC0(position, 0x1F800028, 3, 7);
}

static uint32 dropping_object_heading(uint32 region)
{
    uint32 kind = r_u8(r_u32(0x80071704) + 14 * (uint16)region + 9);
    return r_u16(r_u32(0x800716D0) + 2 * kind);
}

static void dropping_object_collision(uint32 collision, uint32 mesh, uint32 flags)
{
    uint32 angle = r_u16(mesh + 26) + ((r_u16(0x800719D0) & 1) << 10) - 512;
    w_u32(collision + 132, flags);
    w_u16(collision + 136, angle & 4095);
    w_u16(collision + 148, 80);
    sub_800475A8(collision);
}

void sub_800376F0(uint32 node)
{
    uint32 root = r_u32(node + 12), mesh = r_u32(node + 16), collision = r_u32(node + 20);
    uint32 proximity[8], region, heading, i, volume;
    if (r_u32(collision + 128))
        w_u32(collision + 128, 0);
    sub_80051F74(root + 8, draft_local_address(proximity, sizeof(proximity)));
    if (!r_u16(node + 110))
    {
        /* TODO: Recover incoming activation carrier when both players are inactive */
        if (!legend_pickup_region_check(r_u16(node + 108), 3))
        {
            w_u16(node + 110, 1);
            w_u16(node + 114, sub_8004496C());
        }
        return;
    }
    if (r_u16(node + 110) != 1)
        return;
    sub_80044CC0(r_u32(root + 8), r_u32(root + 16));
    sub_80044DC8(r_u32(root + 8), r_u32(root + 16));
    w_u32(node + 104, sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108));
    region = r_u16(node + 108);
    if (region != 0xFFFF && sub_80046A28(r_u32(0x80071704) + 14 * region, region, root + 8))
    {
        sub_800449A0(r_u16(node + 114));
        sub_8003278C(700);
        for (i = 0; i < 5; ++i)
        {
            uint32 random = sub_80011B8C();
            heading = (uint32)(sint32)(sint16)r_u16(root + 26) + (random & 1023) - 2560;
            sub_8002837C(root + 8, 36, heading, 1, 0, 50);
        }
        sub_800376A8(node);
        sub_80032FD0(node);
        return;
    }
    sub_800325CC(node + 24, root + 8, r_u32(node + 104), 1);
    heading = (dropping_object_heading(r_u16(node + 108)) + 1024) & 4095;
    w_u16(root + 26, heading);
    if ((sint16)r_u16(node + 112) >= 64)
        w_u16(root + 26, (heading + 2048) & 4095);
    if (r_u16(node + 30))
    {
        w_u16(mesh + 24, (r_u16(mesh + 24) - 128) & 4095);
        w_u16(node + 96, 0);
        w_u16(node + 100, 0);
        w_u16(node + 98, r_u16(root + 26));
        sub_80051550(root + 8, 150, node + 96);
        if (!(r_u16(0x800719D0) & 3))
        {
            dropping_object_dust(root + 8);
            sub_8004EC38(4);
        }
        if (!(r_u16(0x800719D0) & 7))
        {
            volume = (uint16)sub_80044F58(16000);
            sub_8004486C(1, r_u16(node + 114), 23, 500, volume, r_u16(0x80071A20));
        }
    }
    sub_8005178C(root + 8, 1500, root + 24, r_u16(node + 108), node + 32);
    dropping_object_collision(r_u32(node + 20), root, 0x8008);
    sub_80032A20(node + 32);
    sub_80021288(r_u32(root + 8), r_u32(root + 16), r_u32(node + 104), r_u32(root + 12), 0);
    sub_8004E520(root + 8, 1);
    sub_80046278(r_u16(node + 108));
    sub_8001DEB0(root);
}

void sub_80037E0C(uint32 node)
{
    uint32 root = r_u32(node + 12), mesh = r_u32(node + 16), collision = r_u32(node + 20);
    uint32 proximity[8], region, heading, channel, i, floor_height, shadow_height;
    if (r_u32(collision + 128))
        w_u32(collision + 128, 0);
    sub_80051F74(root + 8, draft_local_address(proximity, sizeof(proximity)));
    if (!r_u16(node + 110))
    {
        /* TODO: Recover incoming activation carrier when both players are inactive */
        if (!legend_pickup_region_check(r_u16(node + 108), 10))
        {
            w_u16(node + 110, 1);
            w_u16(node + 114, sub_80031224(5, 8));
            channel = (uint16)sub_800448F4();
            sub_8004486C(1, channel, 26, 1800, 16000, 512);
        }
        return;
    }
    if (r_u16(node + 110) != 1)
        return;
    sub_80044CC0(r_u32(root + 8), r_u32(root + 16));
    sub_80044DC8(r_u32(root + 8), r_u32(root + 16));
    w_u32(node + 104, sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108));
    region = r_u16(node + 108);
    if (region != 0xFFFF)
        sub_80046A28(r_u32(0x80071704) + 14 * region, region, root + 8);
    sub_800325CC(node + 24, root + 8, r_u32(node + 104), 1);
    heading = (dropping_object_heading(r_u16(node + 108)) + 2048) & 4095;
    w_u16(root + 26, heading);
    w_u16(node + 96, 0);
    w_u16(node + 100, 0);
    w_u16(node + 98, r_u16(root + 26));
    sub_80051550(root + 8, 300, node + 96);
    if (!(r_u16(0x800719D0) & 3))
        dropping_object_dust(root + 8);
    if (r_u16(node + 30))
    {
        sub_8004EC38(8);
        w_u16(0x8007158C, 128);
        w_u16(0x80071A50, 8);
        sub_8003278C(700);
        sub_80028EA0(root + 8, 3, 7, 0);
        for (i = 0; i < 5; ++i)
            sub_8002837C(root + 8, 36, sub_80011B8C() & 4095, 1, 0, 50);
        sub_80031308(r_u16(node + 114));
        sub_80037DC4(node);
        sub_80032FD0(node);
        return;
    }
    sub_8005178C(root + 8, 1500, root + 24, r_u16(node + 108), node + 32);
    dropping_object_collision(r_u32(node + 20), root, 0xC008);
    sub_80032A20(node + 32);
    floor_height = r_u32(node + 104);
    shadow_height = (uint32)((sint32)(r_u32(root + 12) - floor_height) >> 2) + floor_height;
    sub_80021288(r_u32(root + 8), r_u32(root + 16), floor_height, shadow_height, 0);
    sub_8004E520(root + 8, 1);
    sub_80046278(r_u16(node + 108));
    if (r_u16(0x800719D0) & 3)
        sub_8001DEB0(root);
    else
        sub_8001A7A8(root, 255, 0, 0);
    sub_8003133C(r_u16(node + 114), mesh + 8, 0, mesh + 32);
    sub_8002B178(root + 8, 255, 128, 0);
}
