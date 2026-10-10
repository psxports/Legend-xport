#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_80022CC0(uint32, uint32, uint32, uint32);
extern uint32 sub_80022C40(uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_8002837C(uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_800326FC(void);
extern uint32 sub_80015F54(uint32, uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_800233BC(uint32, uint32, uint32, uint32);

uint32 sub_8003FC28(uint32 node)
{
    uint32 index, child;
    sub_80011AF8(r_u32(node + 20));
    sub_80011AF8(r_u32(node + 28));
    sub_80011AF8(r_u32(node + 24));
    sub_8001EE58(r_u32(node + 12));
    w_u16(0x8007172C, r_u16(0x8007172C) - 1);
    index = r_u16(node + 252);
    if (index != 1024)
        w_u8(0x800C9D68 + index, 0);
    child = r_u32(node + 16);
    if (child)
        w_u32(child + 68, 1024);
    return index;
}

uint32 sub_80040314(uint32 actor)
{
    uint32 descriptor = 0x800BFD10 + 40 * r_u16(actor + 80);
    uint32 count = r_u16(descriptor), first = r_u16(descriptor + 2);
    uint32 bone = r_u32(r_u32(actor)) + 168, index = 0, angle;
    w_u32(0x1F800028, 0);
    w_u32(0x1F80002C, 5);
    w_u32(0x1F800030, 0);
    sub_80022CC0(bone + 8, 0x1F800028, 4, 6);
    while (index < count)
    {
        angle = sub_80011B8C() & 4095;
        sub_8002837C(bone + 8, (uint16)(first + index), angle, r_u16(descriptor + 28) - 1, 100, 25);
        bone += 168;
        index = (uint16)(index + 1);
    }
    return sub_800326FC();
}

uint32 sub_80040428(uint32 actor)
{
    uint32 offset = 40 * r_u16(actor + 80);
    uint32 bone = r_u32(r_u32(actor)) + 168, count = r_u16(0x800BFD10 + offset), index = 0;
    if (!count)
        return offset;
    do
    {
        sub_80016358(bone + 8, ((r_u16(0x800719D0) + index) & 3) + 234, 4, 4, 1, 128);
        bone += 336;
        index = (uint16)(index + 2);
    } while (index < count);
    return index < count;
}

uint32 sub_800404EC(uint32 actor)
{
    sint32 min_x = 1000000, max_x = -1000000, min_z = 1000000, max_z = -1000000, min_y = 1000000;
    uint32 count = r_u16(0x800BFD10 + 40 * r_u16(actor + 80));
    uint32 mesh = r_u32(r_u32(actor)), bone = mesh + 176, index = 0, xspan, zspan, height, position[4];
    while (index < count)
    {
        sint32 x = (sint32)r_u32(bone), y = (sint32)r_u32(bone + 4), z = (sint32)r_u32(bone + 8);
        if (x < min_x)
            min_x = x;
        if (max_x < x)
            max_x = x;
        if (y < min_y)
            min_y = y;
        if (z < min_z)
            min_z = z;
        if (max_z < z)
            max_z = z;
        bone += 168;
        index = (uint16)(index + 1);
    }
    mesh = r_u32(r_u32(actor));
    xspan = (uint32)max_x - (uint32)min_x;
    if ((sint32)xspan < 0)
        xspan = 0u - xspan;
    zspan = (uint32)max_z - (uint32)min_z;
    if ((sint32)zspan < 0)
        zspan = 0u - zspan;
    height = (uint32)min_y - r_u32(mesh + 12);
    if ((sint32)height < 0)
        height = 0u - height;
    if ((sint32)xspan < (sint32)zspan)
        xspan = zspan;
    position[0] = r_u32(mesh + 8);
    position[1] = r_u32(mesh + 12);
    position[2] = r_u32(mesh + 16);
    position[3] = r_u32(mesh + 20);
    return sub_80015F54(draft_local_address(position, sizeof(position)), 186, xspan, height, 1, 128, 2000);
}

uint32 sub_800409E8(void)
{
    if (r_u16(0x800715C8) < 901)
        return r_u16(0x80068804 + 2 * (sub_80011B8C() & 15));
    return r_u16(0x80068824 + 2 * (sub_80011B8C() & 3));
}

uint32 sub_80040A50(uint32 mesh)
{
    if ((sub_80011B8C() & 63) < 33 && r_u16(0x800715C8) < 901)
        return 1;
    return sub_800233BC(mesh + 8, mesh + 8, (uint16)sub_800409E8(), 24);
}

uint32 sub_800411A0(uint32 actor, uint32 selected)
{
    uint16 first = (uint16)(selected - 1), used = 1, index, entry;
    uint32 descriptor = 0x800BFD10 + 40 * r_u16(actor + 80);
    uint32 count = r_u16(descriptor), storage = sub_80011A98(256), bone, removed, current, parent;
    w_u16(storage, first);
    w_u8(actor + 244, first + 1);
    w_u8(actor + 248, r_u8(r_u32(descriptor + 8) + 2 * first) + 1);
    for (index = 0; index < count; ++index)
    {
        uint16 found = 0, length = used;
        for (entry = 0; entry < length; ++entry)
            if (r_u16(r_u32(descriptor + 8) + 2 * index) == r_u16(storage + 2 * entry))
                found = 1;
        if (found)
        {
            w_u16(storage + 2 * used, index);
            ++used;
        }
    }
    bone = r_u32(r_u32(actor)) + 168;
    do
    {
        uint16 found = 0;
        current = r_u32(bone + 92);
        for (entry = 0; entry < used; ++entry)
        {
            parent = r_u32(r_u32(actor)) + 168 + 168 * r_u16(storage + 2 * entry);
            if (current == parent && !found)
            {
                found = 1;
                removed = current;
            }
        }
        if (found)
            w_u32(bone + 92, r_u32(removed + 92));
        else
            bone = r_u32(bone + 92);
    } while (bone);
    for (entry = 1; entry < used; ++entry)
    {
        parent = r_u32(r_u32(actor));
        w_u32(parent + 260 + 168 * r_u16(storage + 2 * entry - 2), parent + 168 + 168 * r_u16(storage + 2 * entry));
    }
    w_u32(r_u32(r_u32(actor)) + 260 + 168 * r_u16(storage + 2 * used - 2), 0);
    w_u32(r_u32(r_u32(actor)) + 264 + 168 * first, 0);
    w_u16(actor + 246, -128);
    return sub_80011AF8(storage);
}

void sub_8004148C(uint32 actor)
{
    uint32 kind = r_u16(actor + 222), mesh = r_u32(r_u32(actor));
    if (kind == 20)
        sub_80022C40(mesh + 344, mesh + 8, -6000, -6000, 0, 0, -848, 0, 2288);
    else if (kind == 10 || kind == 11 || kind == 12 || kind == 25 || kind == 26)
        sub_80022C40(mesh + 344, mesh + 8, -3522, -5142, 0, 0, -848, 0, 2288);
}
