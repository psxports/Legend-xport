#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_800287AC(uint32 region, uint32 offset)
{
    uint32 node = sub_80032EF0(), x, y, z, pad;
    sint32 selected = (sint16)region;
    if (!node)
        return node;
    w_u32(node + 8, 26);
    if (selected < 0)
        selected = 0;
    if (selected >= (sint32)r_u16(0x80071728))
        selected = (sint16)(r_u16(0x80071728) - 1);
    w_u32(node + 44, 0);
    w_u16(node + 48, 100);
    w_u16(node + 50, 0);
    sub_8005129C((uint32)(sint32)(sint16)selected, (uint32)(sint32)(sint16)offset, node + 12);
    x = r_u32(node + 12);
    y = r_u32(node + 16);
    z = r_u32(node + 20);
    pad = r_u32(node + 24);
    w_u32(node + 28, x);
    w_u32(node + 32, y);
    w_u32(node + 36, z);
    w_u32(node + 40, pad);
    w_u16(node + 120, 0xFFFF);
    w_u16(node + 124, 0);
    w_u16(node + 126, 0);
    w_u16(node + 122, offset);
    return 0xFFFF;
}

uint32 sub_800285B0(void)
{
    uint32 node = sub_80032EF0(), mesh;
    if (!node)
        return 24;
    w_u32(node + 8, 24);
    mesh = sub_8001A3BC();
    sub_8001A2FC(488, mesh);
    w_u32(node + 16, 81778);
    w_u32(node + 20, 17250);
    w_u32(node + 24, 2930);
    w_u32(node + 12, mesh);
    w_u16(node + 58, 0);
    w_u16(node + 60, 38);
    w_u32(node + 40, 0);
    w_u32(node + 52, 0);
    w_u16(node + 56, 0);
    return 38;
}

uint32 sub_80028708(uint32 x, uint32 y, uint32 z, uint32 height)
{
    uint32 node = sub_80032EF0(), motion;
    if (!node)
        return 25;
    w_u32(node + 8, 25);
    motion = sub_800471B4();
    w_u32(node + 12, motion);
    w_u16(motion + 26, 128);
    w_u32(r_u32(node + 12) + 16, 20000);
    w_u32(r_u32(node + 12) + 20, (uint32)(sint32)(sint16)height);
    motion = r_u32(node + 12);
    w_u32(node + 16, x);
    w_u32(node + 20, y);
    w_u32(node + 24, z);
    w_u16(motion + 24, 0);
    return motion;
}

uint32 sub_80028638(uint32 x, uint32 y, uint32 z, uint32 first, uint32 last)
{
    uint32 node = sub_80032EF0(), mesh;
    if (!node)
        return 24;
    w_u32(node + 8, 24);
    mesh = sub_8001A3BC();
    sub_8001A2FC(37, mesh);
    w_u32(node + 12, mesh);
    w_u32(node + 16, x);
    w_u32(node + 20, y);
    w_u32(node + 24, z);
    w_u16(node + 58, first);
    w_u16(node + 60, last);
    w_u32(node + 40, (sub_80011B8C() & 7) << 9);
    w_u32(node + 44, (sub_80011B8C() & 7) << 9);
    w_u32(node + 52, 0);
    w_u16(node + 56, 1);
    return 1;
}

uint32 sub_80026B78(uint32 kind, uint32 strength, uint32 slot, uint32 x, uint32 y, uint32 z)
{
    uint32 index = r_u16(0x80071774) + 1, count = r_u16(0x80071728), selected = index;
    uint32 first, second, dx, dz, position[4], local;
    sint32 best = 10000000, distance;
    if ((uint16)index < count)
    {
        first = r_u32(0x800718E4);
        second = r_u32(0x80071954);
        do
        {
            uint32 offset = 8 * (uint16)index;
            dx = (uint32)((sint32)(r_u32(first + offset) + r_u32(second + offset)) / 2) - x;
            if ((sint32)dx < 0)
                dx = 0 - dx;
            dz = (uint32)((sint32)(r_u32(first + offset + 4) + r_u32(second + offset + 4)) / 2) - z;
            if ((sint32)dz < 0)
                dz = 0 - dz;
            distance = (sint32)(dx + dz) / 2;
            if (distance < best)
            {
                best = distance;
                selected = index;
            }
            ++index;
        } while ((uint16)index < count);
    }
    local = draft_local_address(position, sizeof(position));
    sub_8005129C((uint16)selected, 64, local);
    w_u16(0x80071852, y - r_u16(local + 4));
    w_u16(0x80071850, x - r_u16(local));
    w_u16(0x80071854, z - r_u16(local + 8));
    return sub_80024074((uint32)(sint32)(sint16)selected, 64, (uint16)kind, (uint16)strength, (uint16)slot);
}

uint32 sub_80023244(uint32 region, uint32 offset, uint32 effect)
{
    uint32 node = sub_80032EF0(), mesh, motion, contact, hitbox, result;
    if (!node)
        return 5;
    w_u32(node + 8, 5);
    mesh = sub_8001A3BC();
    sub_8001A2FC(38, mesh);
    sub_8001A320(mesh, 1);
    motion = sub_800471B4();
    w_u32(node + 16, motion);
    w_u32(motion + 16, r_u32(0x800B0980));
    w_u32(r_u32(node + 16) + 20, (uint32)((sint32)r_u32(0x800B0980) >> 2));
    w_u16(r_u32(node + 16) + 26, 128);
    w_u32(node + 20, sub_800474F4());
    hitbox = sub_800474F4();
    w_u32(node + 24, hitbox);
    w_u32(hitbox + 124, r_u32(node + 20));
    sub_80047534(hitbox, mesh, 2);
    contact = r_u32(node + 20);
    sub_80047534(contact, mesh, 2);
    w_u16(contact + 138, 0xFFFF);
    w_u32(node + 28, 0);
    w_u16(node + 32, 200);
    w_u16(node + 34, 0);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    result = sub_8005129C((uint16)region, (uint32)(sint32)(sint16)offset, mesh + 8);
    w_u16(mesh + 26, (result - 1024) & 4095);
    w_u32(mesh + 12, r_u32(mesh + 12) - 8000);
    result = 8 * (sub_80011B8C() & 255);
    w_u32(mesh + 12, r_u32(mesh + 12) - result);
    w_u16(node + 104, 0xFFFF);
    w_u16(node + 106, 0);
    w_u32(node + 12, mesh);
    w_u16(node + 112, 0);
    w_u16(node + 114, effect);
    return result;
}

uint32 sub_8002372C(uint32 region, uint32 offset, uint32 kind, uint32 effect)
{
    uint32 node = sub_80032EF0(), mesh, child, motion, contact, hitbox, model, result;
    if (!node)
        return node;
    w_u32(node + 8, 10);
    mesh = sub_8001A3BC();
    child = sub_8001A3BC();
    sub_8001A320(mesh, 1);
    sub_8001A2FC((uint16)(2 * kind + 31), mesh);
    sub_8001A2FC((2 * kind + 32) & 0xFFFE, child);
    sub_8001A2BC(mesh, child, 0, (uint32)-650, 350);
    motion = sub_800471B4();
    model = 56 * (2 * (uint16)kind + 31);
    w_u32(node + 20, motion);
    w_u32(motion + 16, r_u32(0x800B0130 + model));
    w_u32(r_u32(node + 20) + 20, r_u32(0x800B0130 + model));
    w_u16(r_u32(node + 20) + 26, 129);
    w_u32(node + 24, sub_800474F4());
    hitbox = sub_800474F4();
    w_u32(node + 28, hitbox);
    w_u32(hitbox + 124, r_u32(node + 24));
    sub_80047534(hitbox, mesh, 1);
    sub_80047534(hitbox, child, 1);
    contact = r_u32(node + 24);
    sub_80047534(contact, mesh, 1);
    sub_80047534(contact, child, 1);
    w_u16(contact + 138, 0xFFFF);
    w_u32(node + 32, 0);
    w_u16(node + 36, 200);
    w_u16(node + 38, 0);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    result = sub_8005129C((uint32)(sint32)(sint16)region, (uint32)(sint32)(sint16)offset, mesh + 8);
    w_u16(mesh + 26, (result - 1024) & 4095);
    w_u32(mesh + 12, r_u32(mesh + 12) - 8000);
    result = 8 * (sub_80011B8C() & 255);
    w_u32(mesh + 12, r_u32(mesh + 12) - result);
    w_u16(node + 108, 0xFFFF);
    w_u16(node + 110, 0);
    w_u32(node + 12, mesh);
    w_u32(node + 16, child);
    w_u16(node + 112, kind);
    w_u16(node + 118, 0);
    w_u16(node + 120, effect);
    return result;
}

uint32 sub_80023D1C(uint32 region, uint32 offset)
{
    uint32 node = sub_80032EF0(), x, y, z, pad;
    sint32 selected = (sint16)region;
    if (!node)
        return 12;
    w_u32(node + 8, 12);
    if (selected < 0)
        selected = 0;
    if (selected >= (sint32)r_u16(0x80071728))
        selected = (sint16)(r_u16(0x80071728) - 1);
    w_u32(node + 44, 0);
    w_u16(node + 48, 100);
    w_u16(node + 50, 0);
    sub_8005129C((uint32)(sint32)(sint16)selected, (uint32)(sint32)(sint16)offset, node + 12);
    x = r_u32(node + 12);
    y = r_u32(node + 16);
    z = r_u32(node + 20);
    pad = r_u32(node + 24);
    w_u32(node + 28, x);
    w_u32(node + 32, y);
    w_u32(node + 36, z);
    w_u32(node + 40, pad);
    w_u16(node + 120, 0xFFFF);
    w_u16(node + 122, 0);
    return 0xFFFF;
}
