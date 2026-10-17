#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_800294B4(uint32 kind, uint32 count, uint32 interval, uint32 first, uint32 last)
{
    uint32 node = sub_80032EF0(), active;
    if (!node)
        return 0;
    active = r_u16(0x8007172C);
    w_u32(node + 8, 38);
    w_u16(node + 12, kind);
    w_u16(node + 14, count);
    w_u16(node + 16, interval);
    w_u16(node + 18, 0);
    w_u16(node + 20, first);
    w_u16(node + 22, last);
    w_u16(0x8007172C, active + 1);
    return 1;
}

uint32 sub_8003A160(void)
{
    return r_u16(0x80068754 + 2 * (sub_80011B8C() & 15));
}

uint32 sub_8003A194(uint32 node)
{
    uint32 coordinate, span, kind, side, first_height, last_height, reward, result;
    w_u16(node + 18, r_u16(node + 18) + 1);
    if (r_u16(node + 18) < r_u16(node + 16))
    {
        result = r_u16(0x80071940);
        if (result)
            return result;
    }
    result = r_u16(node + 14);
    w_u16(node + 18, 0);
    if (!result || !r_u16(0x80071940))
    {
        sub_80032FD0(node);
        result = r_u16(0x8007172C) - 1;
        w_u16(0x8007172C, result);
        return result;
    }
    span = (uint16)(r_u16(node + 22) - r_u16(node + 20));
    w_u16(node + 14, r_u16(node + 14) - 1);
    coordinate = r_u16(node + 20) + ((uint16)(span * (sub_80011B8C() & 31)) >> 5);
    kind = r_u16(node + 12);
    if (!kind)
    {
        first_height = (sub_80011B8C() & 63) + 24;
        side = sub_80011B8C() & 1;
        reward = sub_8003A160();
        return sub_80023948((uint16)coordinate, first_height, side, (uint16)reward);
    }
    if (kind == 1 || kind == 3)
    {
        side = (sub_80011B8C() & 127) < 65;
        first_height = (sub_80011B8C() & 63) + 24;
        last_height = (sub_80011B8C() & 63) + 24;
        reward = (uint16)sub_8003A160();
        if (kind == 1)
        {
            if (side)
                return sub_80029688(r_u16(node + 22) + 2, first_height, r_u16(node + 20), last_height, reward);
            return sub_80029688(r_u16(node + 20) - 2, first_height, r_u16(node + 22), last_height, reward);
        }
        if (side)
            return sub_80029844(r_u16(node + 22) + 2, first_height, r_u16(node + 20), last_height, reward);
        return sub_80029844(r_u16(node + 20) - 2, first_height, r_u16(node + 22), last_height, reward);
    }
    if (kind == 2)
    {
        side = (sub_80011B8C() & 127) < 65;
        reward = (uint16)sub_8003A160();
        return sub_80029688(r_u16(node + (side ? 22 : 20)), 128, (uint16)coordinate, 8, reward);
    }
    return 3;
}

uint32 sub_80023948(uint32 region, uint32 offset, uint32 kind, uint32 reward)
{
    uint32 node = sub_80032EF0(), mesh, child, motion, contact, hitbox, model, result;
    if (!node)
        return node;
    w_u32(node + 8, 36);
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
    w_u16(node + 36, 10);
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
    w_u16(node + 120, reward);
    w_u16(0x8007172C, r_u16(0x8007172C) + 1);
    return result;
}

uint32 sub_80029688(uint32 first, uint32 first_offset, uint32 last, uint32 last_offset, uint32 reward)
{
    uint32 node = sub_80032EF0(), mesh, child, motion, collision, result;
    if (!node)
        return 40;
    w_u32(node + 8, 40);
    mesh = sub_8001A3BC();
    sub_8001A320(mesh, 1);
    child = sub_8001A3BC();
    sub_8001A320(child, 2);
    sub_8001A2FC(38, child);
    sub_8001A2BC(mesh, child, 0, 0, 0);
    w_u16(child + 28, 1024);
    motion = sub_800471B4();
    w_u32(node + 20, motion);
    w_u32(motion + 16, r_u32(0x800B0980));
    w_u32(r_u32(node + 20) + 20, (uint32)((sint32)r_u32(0x800B0980) >> 2));
    w_u16(r_u32(node + 20) + 26, 128);
    collision = sub_800474F4();
    w_u32(node + 24, collision);
    sub_80047534(collision, child, 2);
    w_u32(node + 44, 0);
    w_u16(node + 48, 170);
    w_u16(node + 50, 0);
    sub_8005129C((uint16)first, (uint32)(sint32)(sint16)first_offset, mesh + 8);
    sub_8005129C((uint16)last, (uint32)(sint32)(sint16)last_offset, node + 28);
    w_u32(mesh + 12, r_u32(mesh + 12) - 3000);
    w_u16(mesh + 26, sub_80046C98(mesh + 8, node + 28));
    w_u16(node + 120, 0xFFFF);
    w_u32(node + 12, mesh);
    w_u32(node + 16, child);
    w_u16(node + 122, reward);
    result = (sub_80011B8C() & 63) + 64;
    w_u16(node + 124, result);
    w_u16(0x8007172C, r_u16(0x8007172C) + 1);
    return result;
}

uint32 sub_80029844(uint32 first, uint32 first_offset, uint32 last, uint32 last_offset, uint32 reward)
{
    uint32 node = sub_80032EF0(), actor, motion, collision, mesh, i, result;
    if (!node)
        return node;
    w_u32(node + 8, 64);
    actor = sub_8001F150(26);
    w_u32(node + 12, actor);
    motion = sub_800471B4();
    w_u32(node + 76, motion);
    w_u32(motion + 16, 2000);
    w_u32(r_u32(node + 76) + 20, 600);
    w_u16(r_u32(node + 76) + 26, 0);
    collision = sub_800474F4();
    w_u32(node + 80, collision);
    for (i = 0; i < 12; ++i)
        sub_80047534(collision, r_u32(r_u32(node + 12)) + 168 * (i + 1), 0);
    w_u16(node + 16, 26);
    w_u32(node + 20, r_u32(r_u32(node + 12) + 4));
    w_u16(node + 38, 0xFFFF);
    mesh = r_u32(r_u32(node + 12));
    w_u32(node + 100, 0);
    w_u16(node + 106, 0);
    w_u16(node + 104, 320);
    sub_8005129C((uint16)first, (uint32)(sint32)(sint16)first_offset, mesh + 8);
    sub_8005129C((uint16)last, (uint32)(sint32)(sint16)last_offset, node + 84);
    w_u16(mesh + 26, sub_80046C98(mesh + 8, node + 84));
    w_u16(node + 176, 0xFFFF);
    w_u16(node + 178, reward);
    result = 2 * ((sub_80011B8C() & 63) + 64);
    w_u16(node + 184, result);
    w_u16(node + 180, result);
    w_u16(node + 186, 0);
    w_u16(node + 182, 0);
    sub_80057A14(node + 16, 1);
    result = r_u16(0x8007172C) + 1;
    w_u16(0x8007172C, result);
    return result;
}

uint32 sub_80046C98(uint32 first, uint32 last)
{
    uint32 x = r_u32(last) - r_u32(first), z = r_u32(last + 8) - r_u32(first + 8);
    uint32 distance = sub_8005CBB8(x * x + z * z);
    return (uint16)sub_80046B84(x, z, distance);
}

static uint32 gallery_axis_angle(uint32 first, uint32 last, sint32 distance)
{
    uint32 a = (sint32)first < 0 ? 0 - first : first;
    uint32 b = (sint32)last < 0 ? 0 - last : last;
    uint32 table = (sint32)a < (sint32)b ? 0x800BC9C0 : 0x800BC1B4;
    sint32 numerator = (sint32)(((sint32)a < (sint32)b ? a : b) << 10), ratio;
    if (!distance || (distance == -1 && numerator == (sint32)0x80000000))
        return draft_unknown_return("8001FDE0 DIV BREAK");
    ratio = numerator / distance;
    if (ratio >= 1024)
        ratio = 1023;
    return r_u16(table + 2 * (uint32)ratio);
}

uint32 sub_8001FDE0(uint32 position, uint32 target, uint32 angles, uint32 speed)
{
    uint32 x = r_u32(target) - r_u32(position), y = r_u32(target + 4) - r_u32(position + 4), z = r_u32(target + 8) - r_u32(position + 8);
    uint32 vector[3], address, angle;
    sint32 distance = (sint32)sub_8005CBB8(x * x + y * y + z * z);
    if ((sint32)speed >= distance)
        return 0;
    angle = gallery_axis_angle(x, z, distance);
    if ((sint32)x < 0)
        angle = (sint32)z > 0 ? 4095 - angle : angle + 2048;
    else if ((sint32)z <= 0)
        angle = 2048 - angle;
    w_u16(angles + 2, angle);
    w_u16(0x1F800020, 0);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, 0 - r_u16(angles + 2));
    sub_8005D138(0x1F800020, 0x1F800000);
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    address = draft_local_address(vector, sizeof(vector));
    sub_8005CC48(0x1F800000, address, address);
    vector[0] += r_u32(position);
    vector[1] += r_u32(position + 4);
    vector[2] += r_u32(position + 8);
    z = vector[2] - r_u32(position + 8);
    y = vector[1] - r_u32(position + 4);
    angle = gallery_axis_angle(y, z, distance);
    if ((sint32)y < 0)
    {
        if ((sint32)z <= 0)
            angle = 2048 - angle;
    }
    else
        angle = (sint32)z > 0 ? 4095 - angle : angle + 2048;
    w_u16(angles, angle);
    return 1;
}

static void gallery_move_mesh(uint32 mesh, uint32 velocity, uint32 speed)
{
    uint32 i;
    w_u16(0x1F800020, r_u16(mesh + 24));
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, r_u16(mesh + 26));
    sub_8005D3C8(0x1F800020, 0x1F800000);
    w_u16(0x1F800020, 0);
    w_u16(0x1F800022, 0);
    w_u16(0x1F800024, speed);
    sub_8005CDD8(0x1F800000, 0x1F800020, velocity);
    for (i = 0; i < 3; ++i)
        w_u32(mesh + 8 + 4 * i, r_u32(mesh + 8 + 4 * i) + r_u32(velocity + 4 * i));
}

void sub_80039F40(uint32 node)
{
    uint32 mesh = r_u32(node + 12), x, y, z, pad, collision;
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    if (r_u32(r_u32(node + 16) + 128) || r_u16(node + 26) || (sint32)r_u32(node + 20) < (sint32)r_u32(mesh + 12))
    {
        w_u32(0x1F800028, 0);
        w_u32(0x1F80002C, 5);
        w_u32(0x1F800030, 0);
        sub_80022CC0(mesh + 8, 0x1F800028, 2, 4);
        sub_80039F04(node);
        sub_80032FD0(node);
        return;
    }
    if (sub_8001FDE0(mesh + 8, node + 44, mesh + 24, 600))
        gallery_move_mesh(mesh, node + 28, 600);
    else
    {
        x = r_u32(node + 44);
        y = r_u32(node + 48);
        z = r_u32(node + 52);
        pad = r_u32(node + 56);
        w_u32(mesh + 8, x);
        w_u32(mesh + 12, y);
        w_u32(mesh + 16, z);
        w_u32(mesh + 20, pad);
        w_u16(node + 26, 1);
    }
    w_u32(node + 20, sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 24));
    collision = r_u32(node + 16);
    w_u32(collision + 132, 8);
    w_u16(r_u32(node + 16) + 136, r_u16(mesh + 26));
    w_u16(r_u32(node + 16) + 148, 160);
    sub_800475A8(r_u32(node + 16));
    sub_80046278(r_u16(node + 24));
    sub_8001DEB0(mesh);
}

uint32 sub_80029554(uint32 position, uint32 reward, uint32 player)
{
    uint32 node = sub_80032EF0(), mesh, x, y, z, pad, result;
    if (!node)
        return 39;
    w_u32(node + 8, 39);
    mesh = sub_8001A3BC();
    sub_8001A2FC(r_u16(0x80068660 + 4 * (uint16)reward), mesh);
    w_u16(mesh + 86, 1);
    x = r_u32(position);
    y = r_u32(position + 4);
    z = r_u32(position + 8);
    pad = r_u32(position + 12);
    w_u32(mesh + 8, x);
    w_u32(mesh + 12, y);
    w_u32(mesh + 16, z);
    w_u32(mesh + 20, pad);
    w_u32(node + 12, mesh);
    w_u16(node + 48, reward);
    w_u16(node + 50, player);
    x = r_u32(0x800BBFC4);
    y = r_u32(0x800BBFC8);
    z = r_u32(0x800BBFCC);
    w_u32(node + 32, x);
    w_u32(node + 36, y);
    w_u32(node + 40, z);
    w_u32(node + 44, r_u32(0x800BBFD0));
    w_u32(node + 36, r_u32(node + 36) + 500);
    w_u32(node + 32, r_u32(node + 32) + ((uint16)player ? 1000 : (uint32)-1000));
    result = r_u16(0x8007172C) + 1;
    w_u16(0x8007172C, result);
    return result;
}

void sub_8003A4D8(uint32 node)
{
    uint32 mesh = r_u32(node + 12), player;
    if (sub_8001FDE0(mesh + 8, node + 32, mesh + 24, 500))
    {
        gallery_move_mesh(mesh, node + 16, 500);
        sub_80046278(0xFFFF);
        sub_8001DEB0(mesh);
    }
    else
    {
        player = r_u16(node + 50);
        sub_80033CD8(0x800AFEC0 + 288 * player, player, r_u16(node + 48), 24);
        w_u16(0x8007172C, r_u16(0x8007172C) - 1);
        sub_8003A4B4(node);
        sub_80032FD0(node);
    }
}

static void gallery_target_burst(uint32 position, uint32 child)
{
    w_u32(0x1F80002C, 5);
    w_u32(0x1F800028, 0);
    w_u32(0x1F800030, 0);
    sub_80022F08(position, 0x1F800028, 5, 6, 3);
    sub_8003278C(1100);
    sub_8004EC38(4);
    sub_80027F08(child, 4);
}

void sub_8003A684(uint32 node)
{
    uint32 motion = r_u32(node + 20), mesh = r_u32(node + 12), child = r_u32(node + 16);
    uint32 x, y, z, pad, channel, volume, floor_height;
    if ((sint16)r_u16(motion + 28))
    {
        x = r_u32(motion);
        y = r_u32(motion + 4);
        z = r_u32(motion + 8);
        pad = r_u32(motion + 12);
        w_u32(mesh + 8, x);
        w_u32(mesh + 12, y);
        w_u32(mesh + 16, z);
        w_u32(mesh + 20, pad);
    }
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    if (r_u32(r_u32(node + 24) + 128))
    {
        gallery_target_burst(mesh + 8, child);
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, channel, 22, 3000, volume, r_u16(0x80071A20));
        sub_80029554(mesh + 8, r_u16(node + 122), r_u16(r_u32(node + 24) + 138));
        sub_8003A630(node);
        sub_80032FD0(node);
        w_u16(0x8007172C, r_u16(0x8007172C) - 1);
        w_u16(0x80071940, r_u16(0x80071940) + 2);
        sub_800502F4(24);
        return;
    }
    w_u16(child + 26, r_u16(child + 26) + 128);
    floor_height = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 120);
    w_u32(node + 116, floor_height);
    sub_800325CC(node + 44, mesh + 8, floor_height, 1);
    if ((sint16)r_u16(node + 50))
        w_u32(node + 44, (uint32)-2024 - 4 * (sub_80011B8C() & 511));
    if (r_u16(0x80071940) && sub_80030E5C(mesh + 8, node + 28, r_u16(node + 124), r_u16(node + 124)))
    {
        sub_8005178C(mesh + 8, 1000, mesh + 24, r_u16(node + 120), node + 52);
        motion = r_u32(node + 20);
        x = r_u32(mesh + 8);
        y = r_u32(mesh + 12);
        z = r_u32(mesh + 16);
        pad = r_u32(mesh + 20);
        w_u32(motion, x);
        w_u32(motion + 4, y);
        w_u32(motion + 8, z);
        w_u32(motion + 12, pad);
        w_u16(r_u32(node + 20) + 24, r_u16(mesh + 26));
        sub_800471E8(r_u32(node + 20));
        sub_800475F4(r_u32(node + 24));
        sub_80032A20(node + 52);
        sub_80046278(r_u16(node + 120));
        sub_8001DEB0(mesh);
    }
    else
    {
        gallery_target_burst(mesh + 8, child);
        sub_8003A630(node);
        sub_80032FD0(node);
        w_u16(0x8007172C, r_u16(0x8007172C) - 1);
    }
}

static void gallery_falling_target_burst(uint32 mesh, uint32 child)
{
    sub_8003278C(1000);
    sub_800327F0(1000);
    w_u32(0x1F80002C, 5);
    w_u32(0x1F800028, 0);
    w_u32(0x1F800030, 0);
    sub_80022F08(mesh + 8, 0x1F800028, 5, 6, 3);
    sub_8004EC38(4);
    sub_80027F08(mesh, 4);
    sub_80027F08(child, 4);
}

void sub_800353C8(uint32 node)
{
    uint32 motion = r_u32(node + 20), mesh = r_u32(node + 12), child = r_u32(node + 16);
    uint32 x, y, z, pad, channel, volume, floor_height, region;
    if ((sint16)r_u16(motion + 28))
    {
        x = r_u32(motion);
        y = r_u32(motion + 4);
        z = r_u32(motion + 8);
        pad = r_u32(motion + 12);
        w_u32(mesh + 8, x);
        w_u32(mesh + 12, y);
        w_u32(mesh + 16, z);
        w_u32(mesh + 20, pad);
    }
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    if (r_u32(r_u32(node + 28) + 128))
    {
        gallery_falling_target_burst(mesh, child);
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, channel, 22, 3000, volume, r_u16(0x80071A20));
        sub_80029554(mesh + 8, r_u16(node + 120), r_u16(r_u32(node + 28) + 138));
        sub_80034CE8(node);
        sub_80032FD0(node);
        w_u16(0x8007172C, r_u16(0x8007172C) - 1);
        w_u16(0x80071940, r_u16(0x80071940) + 2);
        sub_800502F4(24);
        return;
    }
    w_u16(mesh + 26, r_u16(mesh + 26) + 64);
    floor_height = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 108);
    region = r_u16(node + 108);
    w_u32(node + 104, floor_height);
    if (region != 0xFFFF)
        sub_80046A28(r_u32(0x80071704) + 14 * region, region, mesh + 8);
    sub_800325CC(node + 32, mesh + 8, r_u32(node + 104), 1);
    if (!(sint16)r_u16(node + 38) && r_u16(0x80071940))
    {
        sub_8005178C(mesh + 8, 1300, mesh + 24, r_u16(node + 108), node + 40);
        motion = r_u32(node + 20);
        x = r_u32(mesh + 8);
        y = r_u32(mesh + 12);
        z = r_u32(mesh + 16);
        pad = r_u32(mesh + 20);
        w_u32(motion, x);
        w_u32(motion + 4, y);
        w_u32(motion + 8, z);
        w_u32(motion + 12, pad);
        w_u16(r_u32(node + 20) + 24, r_u16(mesh + 26));
        sub_800471E8(r_u32(node + 20));
        sub_800475F4(r_u32(node + 28));
        sub_80032A20(node + 40);
        sub_80046278(r_u16(node + 108));
        sub_8001C4B8(mesh);
    }
    else
    {
        gallery_falling_target_burst(mesh, child);
        sub_80034CE8(node);
        sub_80032FD0(node);
        w_u16(0x8007172C, r_u16(0x8007172C) + 0xFFFF);
    }
}

void sub_8003EC18(uint32 node)
{
    uint32 actor_record = node + 12, motion, mesh, state, x, y, z, pad, channel, volume, floor_height;
    if (r_u16(node + 186) != 2047)
        w_u16(node + 186, r_u16(node + 186) + 1);
    motion = r_u32(node + 76);
    mesh = r_u32(r_u32(node + 12));
    if ((sint16)r_u16(motion + 28))
    {
        x = r_u32(motion);
        y = r_u32(motion + 4);
        z = r_u32(motion + 8);
        pad = r_u32(motion + 12);
        w_u32(mesh + 8, x);
        w_u32(mesh + 12, y);
        w_u32(mesh + 16, z);
        w_u32(mesh + 20, pad);
    }
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    if (r_u16(node + 182) != 1 && r_u32(r_u32(node + 80) + 128))
    {
        w_u32(0x1F80002C, 5);
        w_u32(0x1F800028, 0);
        w_u32(0x1F800030, 0);
        sub_80022F08(mesh + 8, 0x1F800028, 5, 6, 3);
        sub_8004EC38(4);
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, channel, 22, 3000, volume, r_u16(0x80071A20));
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, channel, 9, 800, volume, r_u16(0x80071A20));
        sub_80029554(mesh + 8, r_u16(node + 178), r_u16(r_u32(node + 80) + 138));
        w_u32(node + 100, (uint32)-3000);
        w_u16(0x80071940, r_u16(0x80071940) + 2);
        sub_800502F4(24);
        w_u16(node + 182, 1);
        sub_80057A14(node + 16, 5);
    }
    state = r_u16(actor_record + 170);
    if (state == 1)
    {
        w_u16(actor_record + 168, 0);
        if (r_u8(actor_record + 24))
            goto cleanup;
    }
    else if (state == 2)
    {
        w_u16(actor_record + 168, 0);
        if (r_u8(actor_record + 24))
        {
            w_u16(actor_record + 170, 0);
            w_u16(actor_record + 174, 2047);
            sub_80057A14(actor_record + 4, 1);
        }
    }
    else if (state == 3)
    {
        w_u16(actor_record + 168, r_u16(actor_record + 172) >> 1);
        if ((sint16)r_u16(actor_record + 94))
        {
            w_u16(actor_record + 170, 0);
            w_u16(actor_record + 174, 2047);
            sub_80057A14(actor_record + 4, 1);
        }
    }
    else if (!state)
    {
        w_u16(actor_record + 168, r_u16(actor_record + 172));
        if (!(r_u16(actor_record + 174) & 31) && (uint8)sub_80011B8C() >= 201)
        {
            if ((uint8)sub_80011B8C() >= 129)
            {
                w_u16(actor_record + 170, 2);
                sub_80057A14(actor_record + 4, 3);
            }
            else
            {
                w_u16(actor_record + 170, 3);
                sub_80057A14(actor_record + 4, 4);
                w_u32(actor_record + 88, (uint32)-3000);
            }
        }
    }
    floor_height = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), actor_record + 164);
    w_u32(actor_record + 160, floor_height);
    sub_800325CC(actor_record + 88, mesh + 8, floor_height, 1);
    if (!r_u16(0x80071940) || !sub_80030E5C(mesh + 8, actor_record + 72, r_u16(actor_record + 168), r_u16(actor_record + 168)))
        goto cleanup;
    sub_8005178C(mesh + 8, 1000, mesh + 24, r_u16(actor_record + 164), actor_record + 96);
    sub_800475F4(r_u32(actor_record + 68));
    sub_80032A20(actor_record + 96);
    sub_80058484(actor_record + 4, r_u32(actor_record));
    sub_80051614(mesh + 8, actor_record + 4, (uint32)(sint32)(sint16)r_u16(mesh + 26));
    sub_800585D8(actor_record + 4);
    sub_80046278(r_u16(actor_record + 164));
    sub_8001DEB0(mesh);
    return;
cleanup:
    sub_8003EBD0(node);
    sub_80032FD0(node);
    w_u16(0x8007172C, r_u16(0x8007172C) - 1);
}

uint32 sub_80023B78(void)
{
    uint32 region = 8000, sum, node, first, last, result;
    sint32 span, product;
    if (r_u8(0x800AFFB0))
    {
        region = r_u16(0x800AFFCC);
        if (r_u8(0x800B00D0))
        {
            sum = (uint32)(sint32)(sint16)region + (uint32)(sint32)(sint16)r_u16(0x800B00EC);
            region = (sum + (sum >> 31)) >> 1;
        }
    }
    else if (r_u8(0x800B00D0))
        region = r_u16(0x800B00EC);
    result = (uint32)(sint32)(sint16)region;
    if (result == 8000)
        return result;
    node = sub_80032EF0();
    if (!node)
        return 11;
    w_u32(node + 8, 11);
    first = region - 6;
    if ((sint16)first < 0)
        first = 0;
    last = region + 6;
    if ((sint16)last >= (sint32)r_u16(0x80071728))
        last = r_u16(0x80071728) - 1;
    span = (sint16)(last - first);
    product = (sint32)(sub_80011B8C() & 127) * span;
    region = first + (uint32)(product / 128);
    if ((sint16)region >= (sint32)r_u16(0x80071728))
        region = r_u16(0x80071728) - 1;
    result = sub_80011B8C();
    sub_8005129C((uint32)(sint32)(sint16)region, (result & 63) + 32, node + 12);
    w_u16(node + 28, 0);
    result = r_u32(node + 16) - 100;
    w_u32(node + 16, result);
    w_u16(0x800715CC, r_u16(0x800715CC) + 1);
    return result;
}

uint32 sub_80035724(uint32 node)
{
    uint32 result = (uint16)sub_80015B70(node + 12, (uint16)(r_u16(node + 28) + 194), 4, 0, 128);
    if (result)
    {
        result = r_u16(node + 28) + 1;
        w_u16(node + 28, result);
        result = (uint32)(sint32)(sint16)result;
        if (result != 4)
            return result;
    }
    sub_80032FD0(node);
    result = r_u16(0x800715CC) - 1;
    w_u16(0x800715CC, result);
    return result;
}
