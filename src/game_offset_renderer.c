#include "psx.h"
#include "game_draft_signatures.h"

static void offset_load_rotation(uint32 source, uint32 control)
{
    uint32 i;
    for (i = 0; i < 5; ++i)
        draft_gte_control(control + i, r_u32(source + 4 * i));
}

static void offset_rotate_columns(uint32 source, uint32 output)
{
    uint32 column, row;
    for (column = 0; column < 3; ++column)
    {
        for (row = 0; row < 3; ++row)
            draft_gte_data(9 + row, r_u16(source + 6 * row + 2 * column));
        draft_gte_command(0x49E012);
        for (row = 0; row < 3; ++row)
            w_u16(output + 6 * row + 2 * column, draft_gte_read(9 + row));
    }
}

static uint32 offset_mesh_transform(uint32 mesh)
{
    uint32 parent, i;
    switch (r_u16(mesh + 86))
    {
        case 0:
            sub_8005D138(mesh + 24, mesh + 32);
            break;
        case 1:
            sub_8005D3C8(mesh + 24, mesh + 32);
            break;
        case 2:
            sub_8005D658(mesh + 24, mesh + 32);
            break;
    }
    parent = r_u32(mesh + 96);
    if (parent)
    {
        offset_load_rotation(parent + 32, 0);
        for (i = 0; i < 3; ++i)
            draft_gte_control(5 + i, r_u32(parent + 8 + 4 * i));
        draft_gte_data(0, r_u32(mesh));
        draft_gte_data(1, r_u32(mesh + 4));
        draft_gte_command(0x480012);
        w_u32(mesh + 8, draft_gte_read(25));
        w_u32(mesh + 12, draft_gte_read(26));
        w_u32(mesh + 16, draft_gte_read(27));
        offset_rotate_columns(mesh + 32, mesh + 32);
    }
    for (i = 0; i < 3; ++i)
        w_u32(0x1F800028 + 4 * i, r_u32(mesh + 8 + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
    return sub_8005CC48(0x800BBFDC, 0x1F800028, mesh + 64);
}

static void offset_vertex(uint32 index, uint32 address)
{
    draft_gte_data(2 * index, r_u32(address));
    draft_gte_data(2 * index + 1, r_u32(address + 4));
}

static void offset_light(uint32 color)
{
    draft_gte_data(6, r_u32(color));
    draft_gte_command(0xE80413);
}

static void offset_link(uint32 packet, uint32 slot, uint32 size)
{
    w_u32(packet, r_u32(slot) | ((size / 4 - 1) << 24));
    w_u32(slot, packet & 0xFFFFFF);
}

static uint32 offset_polygon_groups(uint32 model, uint32 *packet_cursor, uint32 ordering, sint32 limit, uint32 lit)
{
    static const uint32 source_sizes[6] = {12, 16, 20, 28, 24, 28};
    static const uint32 packet_sizes[6] = {20, 24, 28, 36, 32, 40};
    static const uint32 vertex_offsets[6] = {4, 4, 12, 16, 16, 16};
    static const uint32 normal_offsets[6] = {10, 12, 18, 24, 22, 24};
    uint32 primitive = r_u32(model + 12), vertices = r_u32(model), normals = 0;
    uint32 packet = *packet_cursor, kind, count, i, stride, slot, fourth, color_count;
    sint32 depth;
    if (lit)
        normals = r_u32(model + 4);
    for (kind = 0; kind < 6; ++kind)
    {
        if (r_u16(primitive) != kind)
            continue;
        count = r_u16(primitive + 2);
        primitive += 4;
        while (count)
        {
            for (i = 0; i < 3; ++i)
                offset_vertex(i, vertices + 8 * r_u16(primitive + vertex_offsets[kind] + 2 * i));
            draft_gte_command(0x280030);
            if (!lit && kind < 4)
                w_u32(packet + 4, r_u32(primitive));
            if (kind == 4)
                w_u32(packet + 12, r_u32(primitive + 4));
            if (kind == 5)
                w_u16(packet + 36, r_u16(primitive + 14));
            draft_gte_command(0x1400006);
            if ((sint32)draft_gte_read(24) > 0)
            {
                draft_gte_command(0x158002D);
                depth = (sint32)draft_gte_read(7) >> 2;
                if (depth >= 16 && depth < limit)
                {
                    stride = kind < 2 ? 4 : 8;
                    w_u32(packet + 8, draft_gte_read(12));
                    w_u32(packet + 8 + stride, draft_gte_read(13));
                    w_u32(packet + 8 + 2 * stride, draft_gte_read(14));
                    fourth = kind == 1 || kind == 3 || kind == 5;
                    if (fourth)
                    {
                        offset_vertex(0, vertices + 8 * r_u16(primitive + vertex_offsets[kind] + 6));
                        draft_gte_command(0x180001);
                        if (!lit && kind == 3)
                            w_u32(packet + 12, r_u32(primitive + 4));
                        if (kind == 5)
                        {
                            if (!lit)
                                w_u32(packet + 4, r_u32(primitive));
                            w_u32(packet + 12, r_u32(primitive + 4));
                            w_u32(packet + 20, r_u32(primitive + 8));
                            if (!lit)
                                w_u16(packet + 28, r_u16(primitive + 12));
                        }
                        w_u32(packet + 8 + 3 * stride, draft_gte_read(14));
                    }
                    if (lit)
                    {
                        offset_vertex(0, normals + 8 * r_u16(primitive + normal_offsets[kind]));
                        offset_light(primitive);
                        if (kind == 2 || kind == 3)
                        {
                            color_count = kind == 2 ? 3 : 4;
                            for (i = 1; i < color_count; ++i)
                            {
                                w_u32(packet + 4 + 8 * (i - 1), draft_gte_read(22));
                                offset_light(primitive + 4 * i);
                            }
                        }
                        if (kind == 4)
                        {
                            w_u32(packet + 20, r_u32(primitive + 8));
                            w_u32(packet + 28, r_u32(primitive + 12));
                        }
                        if (kind == 5)
                            w_u16(packet + 28, r_u16(primitive + 12));
                    }
                    else
                    {
                        if (kind == 2)
                        {
                            w_u32(packet + 12, r_u32(primitive + 4));
                            w_u32(packet + 20, r_u32(primitive + 8));
                        }
                        if (kind == 3)
                        {
                            w_u32(packet + 20, r_u32(primitive + 8));
                            w_u32(packet + 28, r_u32(primitive + 12));
                        }
                        if (kind == 4)
                        {
                            w_u32(packet + 4, r_u32(primitive));
                            w_u32(packet + 20, r_u32(primitive + 8));
                            w_u32(packet + 28, r_u32(primitive + 12));
                        }
                    }
                    slot = ordering + 4 * (uint32)depth;
                    offset_link(packet, slot, packet_sizes[kind]);
                    if (lit)
                        w_u32(packet + (kind == 2 ? 20 : kind == 3 ? 28 : 4), draft_gte_read(22));
                    packet += packet_sizes[kind];
                }
            }
            primitive += source_sizes[kind];
            --count;
        }
        if (kind == 5)
        {
            *packet_cursor = packet;
            return 0;
        }
    }
    *packet_cursor = packet;
    return 5;
}

static uint32 offset_render_meshes(uint32 mesh, uint32 offset, uint32 lit)
{
    uint32 visible = r_u16(mesh + 90), packet = r_u32(0x80071680), ordering = r_u32(0x8007184C) + 4 * offset;
    uint32 first_light = 1, model, radius, depth, result, clip;
    sint32 limit = (sint32)(2500 - offset);
    do
    {
        model = r_u32(mesh + 80);
        w_u16(mesh + 88, r_u16(mesh + 88) & 1);
        result = offset_mesh_transform(mesh);
        if (model && visible)
        {
            depth = r_u32(mesh + 72);
            radius = r_u32(model + 16);
            result = lit ? depth - radius : (sint32)(depth + radius) < 129;
            if ((sint32)(depth + radius) >= 129)
            {
                result = lit ? (sint32)(depth - radius) < 20000 : (sint32)(depth - radius) > 39999;
                if (lit ? result : !result)
                {
                    result = r_u16(mesh + 88);
                    if (result)
                    {
                        clip = sub_8001A694(mesh, radius);
                        result = lit ? first_light : clip;
                        if (!clip)
                        {
                            if (lit && first_light)
                            {
                                sub_8001B7A0(0);
                                first_light = 0;
                            }
                            w_u16(mesh + 88, r_u16(mesh + 88) | 2);
                            if (lit)
                            {
                                offset_load_rotation(0x800B7184, 0);
                                offset_rotate_columns(mesh + 32, 0x1F800000);
                                offset_load_rotation(0x1F800000, 8);
                            }
                            offset_load_rotation(0x800BBFDC, 0);
                            if (!r_u16(mesh + 84))
                            {
                                offset_rotate_columns(mesh + 32, 0x1F800000);
                                offset_load_rotation(0x1F800000, 0);
                            }
                            result = offset_polygon_groups(model, &packet, ordering, limit, lit);
                        }
                    }
                }
            }
        }
        mesh = r_u32(mesh + 92);
    } while (mesh);
    w_u32(0x80071680, packet);
    return result;
}

uint32 sub_8002D4F4(uint32 mesh, uint32 offset)
{
    return offset_render_meshes(mesh, offset, 1);
}

uint32 sub_8002E410(uint32 mesh, uint32 offset)
{
    return offset_render_meshes(mesh, offset, 0);
}
