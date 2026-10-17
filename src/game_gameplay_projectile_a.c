#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_800399C0(uint32 node)
{
    uint32 mesh = r_u32(node + 12), collision, timer, velocity, floor, region, i;
    uint32 distances[8], z;
    sub_80051F74(mesh + 8, draft_local_address(distances, sizeof(distances)));
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    collision = r_u32(node + 16);
    if (r_u32(collision + 128))
    {
        if (!r_u16(collision + 144))
        {
            if (r_u16(node + 100) & 0x4000)
            {
                sub_8003278C(700);
                sub_80028EA0(mesh + 8, 3, 6, 1);
            }
            goto destroy;
        }
        velocity = r_u32(node + 108);
        w_u16(node + 24, 100);
        w_u16(node + 98, 1);
        z = r_u32(node + 116);
        w_u32(node + 108, (uint32)((sint32)(0 - velocity) / 2));
        w_u32(node + 116, (uint32)((sint32)(0 - z) / 2));
    }
    timer = r_u16(node + 124);
    if (timer != 0xFFFF)
    {
        w_u16(node + 124, timer - 1);
        if (!timer)
        {
            if (r_u16(node + 100) & 0x4000)
            {
                sub_8003278C(700);
                sub_80028EA0(mesh + 8, 3, 6, 1);
            }
            goto destroy;
        }
    }
    w_u32(mesh + 8, r_u32(mesh + 8) + r_u32(node + 108));
    z = r_u32(mesh + 16);
    w_u32(mesh + 12, r_u32(mesh + 12) + r_u32(node + 112));
    z += r_u32(node + 116);
    w_u32(mesh + 16, z);
    floor = sub_80046324(r_u32(mesh + 8), z, node + 96);
    w_u32(node + 92, floor);
    sub_800325CC(node + 20, mesh + 8, floor, 1);
    if (r_u16(node + 26))
    {
        if (r_u16(node + 126) & 4)
        {
            sub_8004EC38(8);
            w_u16(0x8007158C, 64);
            w_u16(0x80071A50, 4);
            sub_8003278C(700);
            sub_80028EA0(mesh + 8, 3, 7, 0);
            for (i = 0; i < 3; ++i)
                sub_8002837C(mesh + 8, 36, sub_80011B8C() & 4095, 1, 0, 50);
            sub_80029C98(mesh + 8, 2000, r_u8(node + 100) | 0xC000, 4, 20, 0, 0);
        }
        else
        {
            w_u32(0x1F800028, 0);
            w_u32(0x1F80002C, 5);
            w_u32(0x1F800030, 0);
            sub_80022CC0(mesh + 8, 0x1F800028, 2, 4);
        }
        goto destroy;
    }
    region = r_u16(node + 96);
    if (region != 0xFFFF && sub_80046A28(r_u32(0x80071704) + 14 * region, region, mesh + 8))
    {
        if (r_u16(node + 124) == 0xFFFF)
            w_u16(node + 124, 4);
    }
    sub_8005178C(mesh + 8, 500, mesh + 24, r_u16(node + 96), node + 28);
    if (r_u16(node + 98))
        w_u32(r_u32(node + 16) + 128, 0);
    else
    {
        w_u32(r_u32(node + 16) + 132, r_u16(node + 100));
        w_u16(r_u32(node + 16) + 136, r_u16(node + 104));
        w_u16(r_u32(node + 16) + 148, r_u16(node + 102));
        sub_800475A8(r_u32(node + 16));
    }
    sub_80032A20(node + 28);
    sub_80046278(r_u16(node + 96));
    if (!(r_u16(node + 100) & 0x4000))
        return sub_8001C4B8(mesh);
    sub_8001A7A8(mesh, 255, (r_u16(0x800719D0) & 1) ? 0 : 128, 0);
    sub_8002B178(mesh + 8, 256, 128, 0);
    w_u32(0x1F800028, 0);
    w_u32(0x1F80002C, 0);
    w_u32(0x1F800030, 0);
    return sub_80022CC0(mesh + 8, 0x1F800028, 2, 4);

destroy:
    sub_80039984(node);
    return sub_80032FD0(node);
}

static void projectile_copy_vector(uint32 dst, uint32 src)
{
    uint32 x = r_u32(src), y = r_u32(src + 4), z = r_u32(src + 8), pad = r_u32(src + 12);
    w_u32(dst, x);
    w_u32(dst + 4, y);
    w_u32(dst + 8, z);
    w_u32(dst + 12, pad);
}

void sub_8003A9BC(uint32 node)
{
    uint32 root = r_u32(node + 12), mesh = r_u32(node + 16), floor_height, pitch, yaw, volume, collision, i, random, heading, shadow_height;
    sub_80044CC0(r_u32(root + 8), r_u32(root + 16));
    sub_80044DC8(r_u32(root + 8), r_u32(root + 16));
    if (r_s16(node + 30))
    {
        sub_800449A0(r_u16(node + 114));
        sub_8003278C(700);
        for (i = 0; i < 3; ++i)
        {
            random = sub_80011B8C();
            heading = (uint32)(sint32)r_s16(root + 26) + (random & 1023) - 2560;
            sub_8002837C(root + 8, 36, heading, 1, 0, 50);
        }
        sub_800376A8(node);
        sub_80032FD0(node);
        return;
    }
    floor_height = sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108);
    w_u32(node + 104, floor_height);
    sub_800325CC(node + 24, root + 8, floor_height, 1);
    pitch = r_u16(mesh + 24);
    yaw = r_u16(mesh + 26);
    w_u16(mesh + 24, (pitch - 128) & 4095);
    w_u16(mesh + 26, (yaw + 32) & 4095);
    if (!(r_u16(0x800719D0) & 7))
    {
        w_u32(0x1F800028, 0);
        w_u32(0x1F80002C, (uint32)-20);
        w_u32(0x1F800030, 0);
        sub_80022CC0(root + 8, 0x1F800028, 3, 7);
        sub_8004EC38(4);
        volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, r_u16(node + 114), 23, 500, volume, r_u16(0x80071A20));
    }
    sub_8005178C(root + 8, 1500, root + 24, r_u16(node + 108), node + 32);
    collision = r_u32(node + 20);
    w_u32(collision + 132, 0x8008);
    heading = r_u16(root + 26) + ((r_u16(0x800719D0) & 1) << 10) - 512;
    collision = r_u32(node + 20);
    w_u16(collision + 136, heading & 4095);
    collision = r_u32(node + 20);
    w_u16(collision + 148, 80);
    sub_800475A8(r_u32(node + 20));
    sub_80032A20(node + 32);
    floor_height = r_u32(node + 104);
    shadow_height = (uint32)((sint32)(r_u32(root + 12) - floor_height) >> 1) + floor_height;
    sub_80021288(r_u32(root + 8), r_u32(root + 16), floor_height, shadow_height, 0);
    sub_8004E520(root + 8, 1);
    sub_80046278(r_u16(node + 108));
    sub_8001DEB0(root);
}

uint32 sub_8003E6BC(uint32 node)
{
    uint32 root = r_u32(node + 12), mesh = r_u32(node + 16), floor_height, pitch, yaw, volume, collision, i, random, heading, shadow_height;
    sub_80044CC0(r_u32(root + 8), r_u32(root + 16));
    sub_80044DC8(r_u32(root + 8), r_u32(root + 16));
    if (r_s16(node + 34))
    {
        sub_800449A0(r_u16(node + 118));
        sub_8003278C(700);
        for (i = 0; i < 3; ++i)
        {
            random = sub_80011B8C();
            heading = (uint32)(sint32)r_s16(root + 26) + (random & 1023) - 2560;
            sub_8002837C(root + 8, 36, heading, 1, 0, 50);
        }
        sub_8003E668(node);
        return sub_80032FD0(node);
    }
    floor_height = sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 112);
    w_u32(node + 108, floor_height);
    sub_800325CC(node + 28, root + 8, floor_height, 1);
    pitch = r_u16(mesh + 24);
    yaw = r_u16(mesh + 26);
    w_u16(mesh + 24, (pitch - 128) & 4095);
    w_u16(mesh + 26, (yaw + 32) & 4095);
    if (!(r_u16(0x800719D0) & 7))
    {
        w_u32(0x1F800028, 0);
        w_u32(0x1F80002C, (uint32)-20);
        w_u32(0x1F800030, 0);
        sub_80022CC0(root + 8, 0x1F800028, 3, 7);
        sub_8004EC38(4);
        volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, r_u16(node + 118), 23, 500, volume, r_u16(0x80071A20));
    }
    sub_8005178C(root + 8, 1500, root + 24, r_u16(node + 112), node + 36);
    collision = r_u32(node + 24);
    w_u32(collision + 132, 0x8008);
    heading = r_u16(root + 26) + ((r_u16(0x800719D0) & 1) << 10) - 512;
    collision = r_u32(node + 24);
    w_u16(collision + 136, heading & 4095);
    collision = r_u32(node + 24);
    w_u16(collision + 148, 80);
    sub_800475A8(r_u32(node + 24));
    sub_80032A20(node + 36);
    floor_height = r_u32(node + 108);
    shadow_height = (uint32)((sint32)(r_u32(root + 12) - floor_height) >> 1) + floor_height;
    sub_80021288(r_u32(root + 8), r_u32(root + 16), floor_height, shadow_height, 0);
    sub_8004E520(root + 8, 1);
    sub_80046278(r_u16(node + 112));
    return sub_8001C4B8(root);
}

uint32 sub_80029A18(uint32 model, uint32 owner)
{
    uint32 vector[4], position, tile, item, parent, child, collider, result;
    uint16 tile_data[4];
    tile_data[0] = 0xFFFFu;
    position = draft_local_address(vector, sizeof(vector));
    tile = draft_local_address(tile_data, sizeof(tile_data));
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800024u, 0);
    result = sub_80011B8C();
    w_u16(0x1F800022u, r_u16(model + 26) + (result & 2047u) - 1024u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800022u, 0);
    result = sub_80011B8C();
    w_u16(0x1F800024u, (result & 1023u) + 3000u);
    sub_8005CDD8(0x1F800000u, 0x1F800020u, position);
    vector[0] += r_u32(model + 8);
    vector[1] += r_u32(model + 12);
    vector[2] += r_u32(model + 16);
    result = sub_80011B8C();
    vector[1] -= 7000u + ((result & 63u) << 6);
    sub_80046324(vector[0], vector[2], tile);
    if (tile_data[0] == 0xFFFFu)
        return 0xFFFFu;
    item = sub_80032EF0();
    if (!item)
        return 41;
    w_u32(item + 8, 41);
    parent = sub_8001A3BC();
    child = sub_8001A3BC();
    sub_8001A2FC(35, child);
    sub_8001A320(parent, 1);
    sub_8001A2BC(parent, child, 0, (uint32)-825, 0);
    collider = sub_800474F4();
    w_u32(item + 20, collider);
    sub_80047534(collider, child, 0);
    w_u16(collider + 138, 0xFFFFu);
    w_u32(collider + 124, owner);
    w_u32(item + 24, 0);
    w_u16(item + 28, 150);
    w_u16(item + 30, 0);
    w_u16(parent + 24, 0);
    w_u16(parent + 28, 0);
    w_u16(parent + 26, sub_80011B8C() & 0xFFFu);
    w_u32(parent + 8, vector[0]);
    w_u32(parent + 12, vector[1]);
    w_u32(parent + 16, vector[2]);
    /* TODO Original fourth VECTOR word is an unwritten local stack pad */
    w_u32(item + 12, parent);
    w_u32(item + 16, child);
    w_u16(item + 108, tile_data[0]);
    result = sub_8004496C();
    w_u16(item + 114, result);
    return result;
}

uint32 sub_8002A270(uint32 position, uint32 yaw, uint32 mode, uint32 variant, uint32 source_collider, uint32 owner, uint32 value, uint32 attach_mode)
{
    uint16 tile_data[4];
    uint32 item, node, tile, collider, body, result;
    tile_data[0] = 0xFFFFu;
    item = sub_80032EF0();
    if (!item)
        return 51;
    w_u32(item + 8, 51);
    node = sub_8001A3BC();
    projectile_copy_vector(node + 8, position);
    tile = draft_local_address(tile_data, sizeof(tile_data));
    result = sub_80046324(r_u32(position), r_u32(position + 8), tile);
    w_u32(item + 100, result);
    w_u16(item + 70, 500);
    w_u32(item + 32, 500);
    w_u16(item + 68, 1);
    w_u16(item + 36, 0);
    w_u16(item + 38, 0);
    w_u16(item + 40, 0);
    w_u32(node + 80, item + 16);
    sub_8001A494(node);
    collider = sub_800474F4();
    w_u32(item + 72, collider);
    body = item + 12;
    sub_80047534(collider, node, (uint8)attach_mode);
    if (source_collider)
    {
        w_u16(collider + 138, r_u16(source_collider + 138));
        w_u16(collider + 142, r_u16(source_collider + 142));
    }
    else
        w_u16(collider + 138, 0xFFFFu);
    w_u32(collider + 124, owner);
    w_u32(body, node);
    projectile_copy_vector(body + 64, position);
    w_u16(body + 82, yaw);
    w_u16(body + 84, 0);
    w_u16(body + 80, 0);
    w_u16(body + 108, 0xFFFFu);
    mode = (uint16)mode;
    if (!mode)
    {
        w_u16(body + 92, 200);
        w_u16(body + 98, 30);
        w_u16(body + 94, 0);
        w_u16(body + 106, 1);
        result = sub_8004496C();
        w_u16(body + 108, result);
        result = sub_8004486C(1, r_u16(body + 108), 29, 500, 16000, 512);
    }
    else
    {
        result = 400;
        if (mode == 1)
        {
            w_u16(body + 92, 400);
            result = 30;
            w_u16(body + 94, 0);
            w_u16(body + 98, 30);
            w_u16(body + 106, 0);
        }
    }
    w_u16(body + 100, mode);
    w_u16(body + 102, variant);
    w_u16(body + 96, value);
    w_u16(body + 104, 0);
    return result;
}

uint32 sub_8002AB88(uint32 position, uint32 yaw, uint32 kind, uint32 angle, uint32 a5, uint32 a6)
{
    uint32 item = sub_80032EF0(), result;
    if (!item)
        return 53;
    w_u32(item + 8, 53);
    result = r_u32(position);
    projectile_copy_vector(item + 12, position);
    w_u16(item + 36, yaw);
    w_u16(item + 38, 0);
    w_u16(item + 40, angle);
    w_u32(item + 28, a5);
    w_u32(item + 32, a6);
    w_u16(item + 42, kind);
    return result;
}
