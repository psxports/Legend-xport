#include "psx.h"
#include "game_draft_signatures.h"

void sub_80037B80(uint32 node)
{
    uint32 mesh = r_u32(node + 12), visible = 1, floor_height, region, lifetime;
    sint16 angles[4] = {0, (sint16)r_u16(node + 30), 0, 0};
    uint32 edge_position[3];
    if (!r_u16(node + 22))
    {
        sub_80051550(mesh + 8, r_u16(node + 36), draft_local_address(angles, sizeof(angles)));
        w_u16(mesh + 24, (r_u16(mesh + 24) + 128) & 4095);
        w_u16(mesh + 26, (r_u16(mesh + 26) + 76) & 4095);
        if (!(r_u16(0x800719D0) & 7))
        {
            w_u32(0x1F800028, 0);
            w_u32(0x1F80002C, 5);
            w_u32(0x1F800030, 0);
            sub_80022CC0(mesh + 8, 0x1F800028, 2, 4);
        }
    }
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    floor_height = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 28);
    w_u32(node + 24, floor_height);
    sub_800325CC(node + 16, mesh + 8, floor_height, 1);
    if (r_u16(node + 22))
    {
        lifetime = r_u16(node + 34);
        if (!lifetime)
        {
            sub_80037B5C(node);
            sub_80032FD0(node);
            return;
        }
        lifetime = (uint16)(lifetime - 1);
        w_u16(node + 34, lifetime);
        if (lifetime < 30)
            visible = lifetime & 1;
    }
    region = r_u16(node + 28);
    if (region != 0xFFFF && (uint32)(r_u8(r_u32(0x80071704) + 14 * region + 8) - 1) < 2)
    {
        edge_position[0] = r_u32(mesh + 8);
        edge_position[1] = r_u32(mesh + 16);
        /* The callee writes the low angle halfword before reading it */
        edge_position[2] = r_u16(node + 28) << 16;
        sub_800468F0(draft_local_address(edge_position, sizeof(edge_position)));
        w_u32(mesh + 8, edge_position[0]);
        w_u32(mesh + 16, edge_position[1]);
    }
    sub_80046278(r_u16(node + 28));
    if (!visible)
        return;
    if (r_u16(node + 32))
        sub_8001DEB0(mesh);
    else
        sub_8001C4B8(mesh);
}

static void debris_copy_position(uint32 output, uint32 input)
{
    uint32 x = r_u32(input), y = r_u32(input + 4), z = r_u32(input + 8), pad = r_u32(input + 12);
    w_u32(output, x);
    w_u32(output + 4, y);
    w_u32(output + 8, z);
    w_u32(output + 12, pad);
}

static uint32 debris_center_polygon(uint32 position, uint32 vertices, uint32 normals, const uint32 *source_vertices, const uint32 *source_normals, uint32 count)
{
    uint32 axis, i, first = 0, second;
    sint32 sum;
    for (axis = 0; axis < 3; ++axis)
    {
        sum = 0;
        for (i = 0; i < count; ++i)
            sum += (sint16)r_u16(source_vertices[i] + 2 * axis);
        w_u32(0x1F800028 + 4 * axis, (uint32)(sum / (sint32)count) + r_u32(position + 4 * axis));
    }
    for (i = 0; i < count; ++i)
        for (axis = 0; axis < 3; ++axis)
            w_u16(vertices + 8 * i + 2 * axis, r_u16(position + 4 * axis) + r_u16(source_vertices[i] + 2 * axis) - r_u16(0x1F800028 + 4 * axis));
    debris_copy_position(position, 0x1F800028);
    for (i = 0; i < count; ++i)
    {
        first = r_u32(source_normals[i]);
        second = r_u32(source_normals[i] + 4);
        w_u32(normals + 8 * i, first);
        w_u32(normals + 8 * i + 4, second);
    }
    return first;
}

uint32 sub_8002738C(uint32 position, uint32 vertices, uint32 normals, uint32 v0, uint32 v1, uint32 v2, uint32 n0, uint32 n1, uint32 n2)
{
    uint32 points[3] = {v0, v1, v2}, lights[3] = {n0, n1, n2};
    return debris_center_polygon(position, vertices, normals, points, lights, 3);
}

uint32 sub_800275C0(uint32 position, uint32 vertices, uint32 normals, uint32 v0, uint32 v1, uint32 v2, uint32 v3, uint32 n0, uint32 n1, uint32 n2, uint32 n3)
{
    uint32 points[4] = {v0, v1, v2, v3}, lights[4] = {n0, n1, n2, n3};
    return debris_center_polygon(position, vertices, normals, points, lights, 4);
}

uint32 sub_80027884(uint32 position, uint32 type, uint32 primitive, uint32 vertices, uint32 normals)
{
    uint32 node = sub_80032EF0(), kind = type & 7, start, count, i, index, points[4], lights[4];
    if (!node)
        return 20;
    w_u32(node + 8, 20);
    debris_copy_position(node + 28, position);
    w_u32(node + 28, r_u32(node + 28) - 2048);
    index = sub_80011B8C() & 4095;
    w_u32(node + 28, r_u32(node + 28) + index);
    w_u32(node + 36, r_u32(node + 36) - 2048);
    index = sub_80011B8C() & 4095;
    w_u32(node + 36, r_u32(node + 36) + index);
    debris_copy_position(node + 12, position);
    index = sub_80011B8C() & 1023;
    w_u16(node + 56, 100);
    w_u32(node + 52, (uint32)-1000 - index);
    w_u16(node + 58, 0);
    w_u16(node + 44, 0);
    w_u16(node + 48, 0);
    w_u16(node + 46, 0);
    w_u32(node + 60, type);
    w_u32(node + 68, primitive);
    w_u16(node + 136, 0xFFFF);
    if (kind > 5)
        return 0;
    start = kind == 0 || kind == 3 ? 2 : kind == 1 ? 6 : 8;
    count = kind < 3 ? 3 : 4;
    for (i = 0; i < count; ++i)
    {
        index = r_u16(primitive + 2 * (start + i));
        points[i] = vertices + 8 * index;
        lights[i] = normals + 8 * r_u16(primitive + 2 * (start + ((type & 128) ? i : count)));
    }
    if (count == 3)
        return sub_8002738C(node + 12, node + 72, node + 104, points[0], points[1], points[2], lights[0], lights[1], lights[2]);
    return sub_800275C0(node + 12, node + 72, node + 104, points[0], points[1], points[2], points[3], lights[0], lights[1], lights[2], lights[3]);
}

void sub_80027F08(uint32 mesh, uint32 step)
{
    static const uint32 kinds[6] = {0, 3, 1, 4, 2, 5};
    static const uint32 sizes[6] = {12, 16, 20, 28, 24, 28};
    uint32 model = r_u32(mesh + 80), primitive, vertices, normals, kind, remaining, consumed;
    if (!model)
        return;
    primitive = r_u32(model + 12);
    vertices = r_u32(model);
    normals = r_u32(model + 4);
    for (kind = 0; kind < 6; ++kind)
    {
        if (r_u16(primitive) != kind)
            continue;
        remaining = r_u16(primitive + 2);
        primitive += 4;
        if (!remaining)
            continue;
        do
        {
            sub_80027884(mesh + 8, kinds[kind], primitive, vertices, normals);
            consumed = (uint16)remaining < (uint16)step ? remaining : step;
            remaining -= consumed;
            primitive += sizes[kind] * (uint16)consumed;
        } while ((uint16)remaining);
    }
}

void sub_8003368C(uint32 mesh)
{
    w_u32(0x1F80002C, 5);
    w_u32(0x1F800028, 0);
    w_u32(0x1F800030, 0);
    sub_80022F08(mesh + 8, 0x1F800028, 5, 6, 3);
    sub_8004EC38(4);
    sub_80027F08(mesh, 2);
}
