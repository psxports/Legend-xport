#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static void projectile_copy_vector(uint32 dst, uint32 src)
{
    uint32 x = r_u32(src), y = r_u32(src + 4), z = r_u32(src + 8), pad = r_u32(src + 12);
    w_u32(dst, x);
    w_u32(dst + 4, y);
    w_u32(dst + 8, z);
    w_u32(dst + 12, pad);
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
