#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static void special_rotation(uint32 matrix)
{
    uint32 i;
    for (i = 0; i < 5; ++i)
        draft_gte_control(i, r_u32(matrix + 4 * i));
}

static void special_columns(uint32 source, uint32 destination)
{
    uint32 column, row;
    for (column = 0; column < 3; ++column)
    {
        for (row = 0; row < 3; ++row)
            draft_gte_data(9 + row, r_u16(source + 6 * row + 2 * column));
        draft_gte_command(0x49E012);
        for (row = 0; row < 3; ++row)
            w_u16(destination + 6 * row + 2 * column, draft_gte_read(9 + row));
    }
}

static void special_triangle(uint32 vertices, uint32 record)
{
    uint32 i, vertex;
    for (i = 0; i < 3; ++i)
    {
        vertex = vertices + 8 * r_u16(record + 16 + 2 * i);
        draft_gte_data(2 * i, r_u32(vertex));
        draft_gte_data(2 * i + 1, r_u32(vertex + 4));
    }
    draft_gte_command(0x280030);
}

uint32 sub_8001D684(uint32 mesh, uint32 blend, uint32 xscale, uint32 yscale, uint32 zscale, uint32 red, uint32 green, uint32 blue)
{
    uint32 packet = r_u32(0x80071680), ordering = r_u32(0x8007184C);
    uint32 page = r_u16(0x80071780 + 2 * (uint16)blend), visible = r_u16(mesh + 90);
    uint32 model, parent, rotation, i, result, depth, radius, record, vertices, count, slot, link, vertex;
    do
    {
        rotation = r_u16(mesh + 86);
        model = r_u32(mesh + 80);
        w_u16(mesh + 88, r_u16(mesh + 88) & 1);
        if (rotation == 0)
            sub_8005D138(mesh + 24, mesh + 32);
        else if (rotation == 1)
            sub_8005D3C8(mesh + 24, mesh + 32);
        else if (rotation == 2)
            sub_8005D658(mesh + 24, mesh + 32);
        parent = r_u32(mesh + 96);
        if (parent)
        {
            special_rotation(parent + 32);
            for (i = 0; i < 3; ++i)
                draft_gte_control(5 + i, r_u32(parent + 8 + 4 * i));
            draft_gte_data(0, r_u32(mesh));
            draft_gte_data(1, r_u32(mesh + 4));
            draft_gte_command(0x480012);
            for (i = 0; i < 3; ++i)
                w_u32(mesh + 8 + 4 * i, draft_gte_read(25 + i));
            special_columns(mesh + 32, mesh + 32);
        }
        for (i = 0; i < 3; ++i)
            w_u32(0x1F800028 + 4 * i, r_u32(mesh + 8 + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
        result = sub_8005CC48(0x800BBFDC, 0x1F800028, mesh + 64);
        if (model && visible)
        {
            depth = r_u32(mesh + 72);
            radius = r_u32(model + 16);
            result = depth - radius;
            if ((sint32)(depth + radius) >= 129)
            {
                result = (sint32)result < 20000;
                if (result)
                {
                    result = r_u16(mesh + 88);
                    if (result)
                    {
                        result = (uint16)sub_8001A694(mesh, radius);
                        if (!result)
                        {
                            w_u16(mesh + 88, r_u16(mesh + 88) | 2);
                            special_rotation(0x800BBFDC);
                            if (!r_u16(mesh + 84))
                            {
                                special_columns(mesh + 32, 0x1F800000);
                                w_u32(0x1F800028, xscale);
                                w_u32(0x1F80002C, yscale);
                                w_u32(0x1F800030, zscale);
                                sub_8005CE28(0x1F800000, 0x1F800028);
                                special_rotation(0x1F800000);
                            }
                            record = r_u32(model + 12);
                            vertices = r_u32(model);
                            if (r_u16(record) == 4)
                            {
                                count = r_u16(record + 2);
                                record += 4;
                                while (count)
                                {
                                    special_triangle(vertices, record);
                                    w_u32(packet + 12, r_u32(record + 4));
                                    draft_gte_command(0x1400006);
                                    if ((sint32)draft_gte_read(24) > 0)
                                    {
                                        draft_gte_command(0x158002D);
                                        slot = (uint32)((sint32)draft_gte_read(7) >> 2);
                                        if (slot - 16 < 0x9B4)
                                        {
                                            for (i = 0; i < 3; ++i)
                                                w_u32(packet + 8 + 8 * i, draft_gte_read(12 + i));
                                            w_u32(packet + 4, r_u32(record));
                                            w_u32(packet + 20, r_u32(record + 8));
                                            link = r_u32(record + 12);
                                            w_u8(packet + 4, red);
                                            w_u8(packet + 5, green);
                                            w_u8(packet + 6, blue);
                                            w_u8(packet + 7, r_u8(packet + 7) | 2);
                                            w_u32(packet + 28, link);
                                            w_u16(packet + 22, page | r_u16(packet + 22));
                                            link = packet & 0xFFFFFF;
                                            w_u32(packet, r_u32(ordering + 4 * slot) | 0x07000000);
                                            packet += 32;
                                            w_u32(ordering + 4 * slot, link);
                                        }
                                    }
                                    record += 24;
                                    --count;
                                }
                            }
                            result = 5;
                            if (r_u16(record) == 5)
                            {
                                count = r_u16(record + 2);
                                result = count;
                                record += 4;
                                while (count)
                                {
                                    special_triangle(vertices, record);
                                    w_u16(packet + 36, r_u16(record + 14));
                                    draft_gte_command(0x1400006);
                                    if ((sint32)draft_gte_read(24) > 0)
                                    {
                                        draft_gte_command(0x158002D);
                                        slot = (uint32)((sint32)draft_gte_read(7) >> 2);
                                        if (slot - 16 < 0x9B4)
                                        {
                                            for (i = 0; i < 3; ++i)
                                                w_u32(packet + 8 + 8 * i, draft_gte_read(12 + i));
                                            vertex = vertices + 8 * r_u16(record + 22);
                                            draft_gte_data(0, r_u32(vertex));
                                            draft_gte_data(1, r_u32(vertex + 4));
                                            draft_gte_command(0x180001);
                                            w_u32(packet + 4, r_u32(record));
                                            w_u32(packet + 12, r_u32(record + 4));
                                            w_u32(packet + 20, r_u32(record + 8));
                                            w_u32(packet + 32, draft_gte_read(14));
                                            w_u8(packet + 4, red);
                                            w_u8(packet + 5, green);
                                            w_u8(packet + 6, blue);
                                            w_u16(packet + 28, r_u16(record + 12));
                                            w_u16(packet + 22, page | r_u16(packet + 22));
                                            w_u8(packet + 7, r_u8(packet + 7) | 2);
                                            link = packet & 0xFFFFFF;
                                            w_u32(packet, r_u32(ordering + 4 * slot) | 0x09000000);
                                            packet += 40;
                                            w_u32(ordering + 4 * slot, link);
                                        }
                                    }
                                    record += 28;
                                    result = (uint16)(count - 1);
                                    --count;
                                }
                            }
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
