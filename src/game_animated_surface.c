#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80038C60(uint32 corners, uint32 column, uint32 row, uint32 output)
{
    sint32 first[3], second[3], a, b, product, result = 0;
    uint32 i;
    for (i = 0; i < 3; ++i)
    {
        a = (sint16)r_u16(corners + 2 * i);
        b = (sint16)r_u16(corners + 16 + 2 * i);
        product = (sint32)((uint32)(b - a) * row);
        first[i] = (sint16)((uint32)a + (uint32)(product / 4));
    }
    for (i = 0; i < 3; ++i)
    {
        a = (sint16)r_u16(corners + 8 + 2 * i);
        b = (sint16)r_u16(corners + 24 + 2 * i);
        product = (sint32)((uint32)(b - a) * row);
        second[i] = (sint16)((uint32)a + (uint32)(product / 4));
    }
    for (i = 0; i < 3; ++i)
    {
        product = (sint32)((uint32)(second[i] - first[i]) * column);
        result = (sint32)((uint32)first[i] + (uint32)(product / 8));
        w_u16(output + 2 * i, result);
    }
    return (uint32)result;
}

uint32 sub_80031224(uint32 kind, uint32 mode)
{
    uint32 i, allocation;
    for (i = 0; i < 8; ++i)
    {
        if (!r_u32(0x800BD408 + 4 * i))
        {
            allocation = sub_80011A98(1152);
            if (!allocation)
                return 0xFFFF;
            w_u32(0x800BD408 + 4 * i, allocation);
            w_u16(0x800C04E4 + 2 * i, kind);
            w_u16(0x800BD398 + 2 * i, 0);
            w_u16(0x800AEA5C + 2 * i, 0);
            w_u32(0x800C9DA0 + 4 * i, mode);
            return i;
        }
    }
    return 0xFFFF;
}

uint32 sub_80031308(uint32 trail)
{
    uint32 value;
    trail = (uint16)trail;
    if (trail == 0xFFFF)
        return 0xFFFF;
    value = r_u16(0x800C04E4 + 2 * trail) | 128;
    w_u16(0x800C04E4 + 2 * trail, value);
    return value;
}

uint32 sub_8003133C(uint32 trail, uint32 position, uint32 shape, uint32 rotation)
{
    uint32 head, record, i, j, table, values[2][3], address[2];
    trail = (uint16)trail;
    if (trail == 0xFFFF)
        return 0xFFFF;
    record = r_u32(0x800BD408 + 4 * trail);
    head = (r_u16(0x800BD398 + 2 * trail) + 1) & 31;
    w_u16(0x800BD398 + 2 * trail, head);
    if (head == r_u16(0x800AEA5C + 2 * trail))
        w_u16(0x800AEA5C + 2 * trail, (r_u16(0x800AEA5C + 2 * trail) + 1) & 31);
    record += 36 * head;
    for (i = 0; i < 5; ++i)
        draft_gte_control(i, r_u32(rotation + 4 * i));
    table = 0x800685E8 + 2 * (uint16)(6 * (uint16)shape);
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 3; ++j)
            w_u16(0x1F800020 + 2 * j, r_u16(table + 6 * i + 2 * j));
        address[i] = draft_local_address(values[i], sizeof(values[i]));
        sub_8005CDA8(0x1F800020, address[i]);
        for (j = 0; j < 3; ++j)
            values[i][j] += r_u32(position + 4 * j);
    }
    for (i = 0; i < 3; ++i)
        w_u32(record + 4 * i, (uint32)((sint32)(values[0][i] + values[1][i]) >> 1));
    for (i = 0; i < 2; ++i)
        for (j = 0; j < 3; ++j)
            w_u16(record + 16 + 8 * i + 2 * j, values[i][j] - r_u16(record + 4 * j));
    w_u32(record + 32, 127);
    return 127;
}

uint32 sub_80028EA0(uint32 position, uint32 period, uint32 scale, uint32 kind)
{
    uint32 node = sub_80032EF0(), x, y, z, pad, texture;
    if (!node)
        return 30;
    w_u32(node + 8, 30);
    x = r_u32(position);
    y = r_u32(position + 4);
    z = r_u32(position + 8);
    pad = r_u32(position + 12);
    w_u32(node + 12, x);
    w_u32(node + 16, y);
    w_u32(node + 20, z);
    w_u32(node + 24, pad);
    w_u16(node + 34, scale - 1);
    w_u16(node + 32, period);
    w_u16(node + 30, 0);
    w_u16(node + 28, 0);
    texture = (uint16)kind ? 180 : 174;
    w_u16(node + 36, texture);
    return texture;
}

uint32 sub_800398F0(uint32 node)
{
    uint32 counter, result;
    sub_80015B70(node + 12, (uint16)(r_u16(node + 36) + r_u16(node + 28)), r_u16(node + 34), 0, 128);
    counter = (uint16)(r_u16(node + 30) + 1);
    w_u16(node + 30, counter);
    result = counter;
    if (r_u16(node + 32) < counter)
    {
        w_u16(node + 30, 0);
        w_u16(node + 28, r_u16(node + 28) + 1);
        result = 6;
        if (r_u16(node + 28) == 6)
            return sub_80032FD0(node);
    }
    return result;
}

uint32 sub_800395B8(uint32 node)
{
    uint32 mesh = r_u32(node + 16), root = r_u32(node + 12), collision, floor, i, record[8], distances, phase;
    w_u16(mesh + 24, (r_u16(mesh + 24) - 128) & 4095);
    collision = r_u32(node + 20);
    if (r_u32(collision + 128))
        w_u32(collision + 128, 0);
    distances = draft_local_address(record, sizeof(record));
    sub_80051F74(root + 8, distances);
    floor = sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108);
    w_u32(node + 104, floor);
    sub_800325CC(node + 24, root + 8, floor, 1);
    w_u16(node + 96, 0);
    w_u16(node + 100, 0);
    w_u16(node + 98, r_u16(root + 26));
    sub_80051550(root + 8, 120, node + 96);
    if (!(r_u16(0x800719D0) & 3))
    {
        w_u32(0x1F800028, 0);
        w_u32(0x1F80002C, (uint32)-20);
        w_u32(0x1F800030, 0);
        sub_80022CC0(root + 8, 0x1F800028, 3, 6);
    }
    if (r_u16(node + 30))
    {
        sub_8004EC38(8);
        w_u16(0x8007158C, 128);
        w_u16(0x8007156C, 64);
        w_u16(0x80071A50, 8);
        sub_8003278C(700);
        sub_80028EA0(root + 8, 3, 7, 0);
        for (i = 0; i < 3; ++i)
            sub_8002837C(root + 8, 36, sub_80011B8C() & 4095, 1, 0, 50);
        sub_80031308(r_u16(node + 114));
        sub_80037DC4(node);
        return sub_80032FD0(node);
    }
    sub_8005178C(root + 8, 1500, root + 24, r_u16(node + 108), node + 32);
    collision = r_u32(node + 20);
    w_u32(collision + 132, 49160);
    w_u16(collision + 136, (r_u16(root + 26) + ((r_u16(0x800719D0) & 1) << 10) - 512) & 4095);
    w_u16(collision + 148, 80);
    sub_800475A8(collision);
    sub_80032A20(node + 32);
    if ((sint32)r_u32(distances + 16 + 4 * r_u16(distances + 24)) < 8000)
        sub_8004E520(root + 8, 1);
    phase = r_u16(0x800719D0) & 3;
    if (phase == 0 || phase == 2)
        sub_8001A7A8(root, 255, 64, 0);
    else
        sub_8001B824(root);
    sub_8003133C(r_u16(node + 114), mesh + 8, 1, mesh + 32);
    if (r_u16(0x80071594) != 19)
        return sub_8002B178(root + 8, 255, 128, 0);
    return 19;
}

uint32 sub_80028C94(uint32 position, uint32 heading)
{
    uint32 node = sub_80032EF0(), root, mesh, collision, x, y, z, pad, channel, volume;
    if (!node)
        return 29;
    w_u32(node + 8, 29);
    root = sub_8001A3BC();
    mesh = sub_8001A3BC();
    sub_8001A2FC(489, mesh);
    sub_8001A320(root, 1);
    sub_8001A2BC(root, mesh, 0, (uint32)-825, 0);
    collision = sub_800474F4();
    w_u32(node + 20, collision);
    sub_80047534(collision, mesh, 0);
    w_u16(collision + 138, 0xFFFF);
    w_u32(node + 24, (uint32)-4000 - (sub_80011B8C() & 1023));
    w_u16(node + 28, 150);
    w_u16(node + 30, 0);
    w_u16(root + 24, 0);
    w_u16(root + 28, 0);
    w_u16(root + 26, heading);
    x = r_u32(position);
    y = r_u32(position + 4);
    z = r_u32(position + 8);
    pad = r_u32(position + 12);
    w_u32(root + 8, x);
    w_u32(root + 12, y);
    w_u32(root + 16, z);
    w_u32(root + 20, pad);
    w_u16(node + 108, 0xFFFF);
    sub_80046324(r_u32(root + 8), r_u32(root + 16), node + 108);
    w_u32(node + 12, root);
    w_u32(node + 16, mesh);
    w_u16(node + 114, sub_80031224(0, 10));
    sub_80044CC0(r_u32(root + 8), r_u32(root + 16));
    sub_80044DC8(r_u32(root + 8), r_u32(root + 16));
    channel = (uint16)sub_800448F4();
    volume = (uint16)sub_80044F58(12000);
    return sub_8004486C(1, channel, 61, 1200, volume, r_u16(0x80071A20));
}

uint32 sub_80028E38(uint32 region)
{
    uint32 position[4] = {0, 0, 0, 0};
    uint32 address = draft_local_address(position, sizeof(position));
    uint32 heading = (sub_8005129C((uint16)region, 0, address) + 1024) & 4095;
    uint32 random = sub_80011B8C();
    position[2] += 2048 + (random & 2047);
    position[1] += 2048;
    return sub_80028C94(address, heading);
}

/* Native helper for the four projected bounds */
static sint32 surface_overlaps(uint32 packet, uint32 component, sint32 limit)
{
    uint32 i;
    sint32 minimum = (sint16)r_u16(packet + 8 + component);
    sint32 maximum = minimum, value;
    for (i = 1; i < 4; ++i)
    {
        value = (sint16)r_u16(packet + 8 + 12 * i + component);
        if (value < minimum)
            minimum = value;
        if (value > maximum)
            maximum = value;
    }
    return minimum < limit && maximum > 0;
}

/* Native helper for the original packed vertex loads */
static void surface_mesh_vertex(uint32 vertices, uint32 index, uint32 slot)
{
    uint32 source = vertices + 8 * index;
    draft_gte_data(2 * slot, r_u32(source));
    draft_gte_data(2 * slot + 1, r_u32(source + 4));
}

uint32 sub_8001B824(uint32 mesh)
{
    static const uint8 strides[6] = {12, 16, 20, 28, 24, 28};
    static const uint8 indices[6] = {4, 4, 12, 16, 16, 16};
    static const uint8 packet_sizes[6] = {20, 24, 28, 36, 32, 40};
    uint32 visible = r_u16(mesh + 90), packet = r_u32(0x80071680), ordering = r_u32(0x8007184C);
    uint32 kind, model, parent, column, i, result, radius, depth, stream, vertices, count, primitive, tag;
    do
    {
        kind = r_u16(mesh + 86);
        model = r_u32(mesh + 80);
        w_u16(mesh + 88, r_u16(mesh + 88) & 1);
        if (kind == 0)
            sub_8005D138(mesh + 24, mesh + 32);
        else if (kind == 1)
            sub_8005D3C8(mesh + 24, mesh + 32);
        else if (kind == 2)
            sub_8005D658(mesh + 24, mesh + 32);
        parent = r_u32(mesh + 96);
        if (parent)
        {
            for (i = 0; i < 5; ++i)
                draft_gte_control(i, r_u32(parent + 32 + 4 * i));
            for (i = 0; i < 3; ++i)
                draft_gte_control(5 + i, r_u32(parent + 8 + 4 * i));
            draft_gte_data(0, r_u32(mesh));
            draft_gte_data(1, r_u32(mesh + 4));
            draft_gte_command(0x480012);
            for (i = 0; i < 3; ++i)
                w_u32(mesh + 8 + 4 * i, draft_gte_read(25 + i));
            for (column = 0; column < 3; ++column)
            {
                for (i = 0; i < 3; ++i)
                    draft_gte_data(9 + i, r_u16(mesh + 32 + 2 * column + 6 * i));
                draft_gte_command(0x49E012);
                for (i = 0; i < 3; ++i)
                    w_u16(mesh + 32 + 2 * column + 6 * i, draft_gte_read(9 + i));
            }
        }
        w_u32(0x1F800028, r_u32(mesh + 8) - r_u32(0x800BBFC4));
        w_u32(0x1F80002C, r_u32(mesh + 12) - r_u32(0x800BBFC8));
        w_u32(0x1F800030, r_u32(mesh + 16) - r_u32(0x800BBFCC));
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
                            for (i = 0; i < 5; ++i)
                                draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
                            if (!r_u16(mesh + 84))
                            {
                                for (column = 0; column < 3; ++column)
                                {
                                    for (i = 0; i < 3; ++i)
                                        draft_gte_data(9 + i, r_u16(mesh + 32 + 2 * column + 6 * i));
                                    draft_gte_command(0x49E012);
                                    for (i = 0; i < 3; ++i)
                                        w_u16(0x1F800000 + 2 * column + 6 * i, draft_gte_read(9 + i));
                                }
                                for (i = 0; i < 5; ++i)
                                    draft_gte_control(i, r_u32(0x1F800000 + 4 * i));
                            }
                            /* 1A694 has already set the translation controls */
                            stream = r_u32(model + 12);
                            vertices = r_u32(model);
                            for (kind = 0; kind < 6; ++kind)
                            {
                                result = kind;
                                if (r_u16(stream) != kind)
                                    continue;
                                count = r_u16(stream + 2);
                                stream += 4;
                                for (primitive = 0; primitive < count; ++primitive)
                                {
                                    for (i = 0; i < 3; ++i)
                                        surface_mesh_vertex(vertices, r_u16(stream + indices[kind] + 2 * i), i);
                                    draft_gte_command(0x280030);
                                    if (kind < 4)
                                        w_u32(packet + 4, r_u32(stream));
                                    else if (kind == 4)
                                        w_u32(packet + 12, r_u32(stream + 4));
                                    else
                                        w_u16(packet + 36, r_u16(stream + 14));
                                    draft_gte_command(0x1400006);
                                    if ((sint32)draft_gte_read(24) > 0)
                                    {
                                        draft_gte_command(0x158002D);
                                        depth = (uint32)((sint32)draft_gte_read(7) >> 2);
                                        if (depth - 16 < 2484)
                                        {
                                            for (i = 0; i < 3; ++i)
                                                w_u32(packet + 8 + (kind < 2 ? 4 : 8) * i, draft_gte_read(12 + i));
                                            if (kind & 1)
                                            {
                                                surface_mesh_vertex(vertices, r_u16(stream + indices[kind] + 6), 0);
                                                draft_gte_command(0x180001);
                                                if (kind != 5)
                                                    w_u32(packet + (kind == 1 ? 20 : 32), draft_gte_read(14));
                                            }
                                            if (kind == 2)
                                            {
                                                w_u32(packet + 12, r_u32(stream + 4));
                                                w_u32(packet + 20, r_u32(stream + 8));
                                            }
                                            else if (kind == 3)
                                            {
                                                for (i = 0; i < 3; ++i)
                                                    w_u32(packet + 12 + 8 * i, r_u32(stream + 4 + 4 * i));
                                            }
                                            else if (kind == 4)
                                            {
                                                w_u32(packet + 4, r_u32(stream));
                                                w_u32(packet + 20, r_u32(stream + 8));
                                                w_u32(packet + 28, r_u32(stream + 12));
                                            }
                                            else if (kind == 5)
                                            {
                                                w_u32(packet + 4, r_u32(stream));
                                                w_u32(packet + 12, r_u32(stream + 4));
                                                w_u32(packet + 20, r_u32(stream + 8));
                                                w_u32(packet + 32, draft_gte_read(14));
                                                w_u16(packet + 28, r_u16(stream + 12));
                                            }
                                            tag = ordering + 4 * depth;
                                            w_u32(packet, r_u32(tag) | ((uint32)(packet_sizes[kind] / 4 - 1) << 24));
                                            w_u32(tag, packet & 0xFFFFFF);
                                            packet += packet_sizes[kind];
                                        }
                                    }
                                    stream += strides[kind];
                                }
                                result = 0;
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

uint32 sub_80038E20(uint32 node)
{
    uint32 corners = node + 12, region, kind, i, row, column, wave, phase, packet, ordering, texture, clut, page, tag, countdown, selected = 8000;
    uint32 points[3][2] = {{0, 0}, {0, 0}, {0, 0}}, local[3];
    sint32 height, color, depth, average, target;
    w_u16(node + 64, (r_u16(node + 64) + 1) & 63);
    region = r_u16(0x800BC0CC);
    if (region == 0xFFFF)
        return 0xFFFF;
    kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
    if ((sint32)kind < (sint16)r_u16(node + 60))
        return 1;
    if ((sint16)r_u16(node + 62) < (sint32)kind)
        return 1;
    w_u32(0x1F800030, r_u32(node + 52) - r_u32(0x800BBFCC));
    w_u32(0x1F800028, r_u32(node + 44) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(node + 48) - r_u32(0x800BBFC8));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    for (i = 0; i < 5; ++i)
        draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
    for (i = 0; i < 3; ++i)
        draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
    packet = r_u32(0x80071680);
    ordering = r_u32(0x8007184C);
    texture = r_u32(0x800B6BEC);
    clut = r_u16(texture + 10);
    page = r_u16(texture + 14);
    for (i = 0; i < 4; ++i)
    {
        w_u16(node + 66 + 2 * i, r_u16(node + 66 + 2 * i) + r_u16(node + 74 + 2 * i));
        height = (sint16)r_u16(node + 66 + 2 * i);
        if (height < -1280)
        {
            w_u16(node + 66 + 2 * i, (uint32)-1280);
            w_u16(node + 74 + 2 * i, 0 - r_u16(node + 74 + 2 * i));
        }
        if ((sint16)r_u16(node + 66 + 2 * i) >= 0)
        {
            w_u16(node + 66 + 2 * i, 0);
            w_u16(node + 74 + 2 * i, 0 - r_u16(node + 74 + 2 * i));
        }
    }
    phase = r_u8(node + 64) & 63;
    for (i = 0; i < 3; ++i)
        local[i] = draft_local_address(points[i], sizeof(points[i]));
    for (row = 0; row < 4; ++row)
    {
        for (column = 0; column < 8; ++column)
        {
            sub_80038C60(corners, column, row, local[0]);
            sub_80038C60(corners, column + 1, row, local[1]);
            sub_80038C60(corners, column, row + 1, local[2]);
            wave = column + 2 * row;
            for (i = 0; i < 3; ++i)
            {
                w_u16(local[i] + 2, r_u16(local[i] + 2) + r_u16(node + 66 + 2 * ((wave + i) & 3)));
                draft_gte_data(2 * i, r_u32(local[i]));
                draft_gte_data(2 * i + 1, r_u32(local[i] + 4));
            }
            draft_gte_command(0x280030);
            sub_80038C60(corners, column + 1, row + 1, local[0]);
            draft_gte_command(0x158002D);
            depth = (sint32)draft_gte_read(7) >> 2;
            if ((uint32)(depth + 199) >= 2499)
                continue;
            w_u32(packet + 8, draft_gte_read(12));
            w_u32(packet + 20, draft_gte_read(13));
            w_u32(packet + 32, draft_gte_read(14));
            w_u16(local[0] + 2, r_u16(local[0] + 2) + r_u16(node + 66 + 2 * ((wave + 3) & 3)));
            draft_gte_data(0, r_u32(local[0]));
            draft_gte_data(1, r_u32(local[0] + 4));
            draft_gte_command(0x180001);
            w_u32(packet + 44, draft_gte_read(14));
            if (!surface_overlaps(packet, 0, 384) || !surface_overlaps(packet, 2, 256))
                continue;
            w_u8(packet + 3, 12);
            w_u8(packet + 7, 60);
            for (i = 0; i < 4; ++i)
            {
                color = (-(sint32)(sint16)r_u16(node + 66 + 2 * ((wave + i) & 3)) >> 3) + 64;
                w_u8(packet + 4 + 12 * i, color);
                w_u8(packet + 5 + 12 * i, color);
                w_u8(packet + 6 + 12 * i, (uint32)((sint16)color + ((uint32)(uint16)color >> 15)) >> 1);
            }
            w_u16(packet + 14, clut);
            w_u8(packet + 13, 64);
            w_u8(packet + 25, 64);
            w_u8(packet + 37, 127);
            w_u8(packet + 49, 127);
            w_u8(packet + 12, phase);
            w_u8(packet + 24, phase + 63);
            w_u8(packet + 36, phase);
            w_u8(packet + 48, phase + 63);
            w_u16(packet + 26, page);
            tag = ordering + 4 * (uint32)(depth + 200);
            w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(tag) & 0xFFFFFF));
            w_u32(tag, (r_u32(tag) & 0xFF000000) | (packet & 0xFFFFFF));
            packet += 52;
        }
    }
    countdown = r_u16(node + 82);
    w_u32(0x80071680, packet);
    w_u16(node + 82, countdown - 1);
    if (countdown)
        return countdown - 1;
    w_u16(node + 82, 2 * ((sub_80011B8C() & 127) + 30));
    if (r_u8(0x800AFFB0))
    {
        selected = r_u16(0x800AFFCC);
        if (r_u8(0x800B00D0))
        {
            average = (sint16)selected + (sint16)r_u16(0x800B00EC);
            selected = ((uint32)average + ((uint32)average >> 31)) >> 1;
        }
    }
    else if (r_u8(0x800B00D0))
        selected = r_u16(0x800B00EC);
    if ((sint16)selected == 8000)
        return 8000;
    target = (sint16)(selected - 3 + (sub_80011B8C() & 7));
    if (target < (sint16)r_u16(node + 60) + 5)
        return 1;
    if ((sint16)r_u16(node + 62) - 5 < target)
        return 1;
    return sub_80028E38((uint32)target);
}
