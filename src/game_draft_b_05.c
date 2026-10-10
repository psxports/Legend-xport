#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
/* Unverified draft; integration deferred */
/* TODO: Missing SDK declarations require future fail-fast adapters */
extern uint32 sub_8005CC48(uint32 matrix, uint32 input, uint32 output);

static void b05_vertex(uint32 vertex, uint32 reg)
{
    draft_gte_data(reg, r_u32(vertex));
    draft_gte_data(reg + 1, r_u32(vertex + 4));
}

static uint32 b05_on_screen(uint32 packet, uint32 count, uint32 spacing)
{
    sint32 minx = (sint16)r_u16(packet + 8), maxx = minx;
    sint32 miny = (sint16)r_u16(packet + 10), maxy = miny;
    uint32 i;
    for (i = 1; i != count; ++i)
    {
        sint32 x = (sint16)r_u16(packet + 8 + spacing * i), y = (sint16)r_u16(packet + 10 + spacing * i);
        if (x < minx)
            minx = x;
        if (x > maxx)
            maxx = x;
        if (y < miny)
            miny = y;
        if (y > maxy)
            maxy = y;
    }
    return minx < 384 && maxx >= 0 && miny < 251 && maxy >= 0;
}

uint32 sub_8002BE18(uint32 index)
{
    uint32 object = r_u32(0x80071844u) + (r_u32(r_u32(0x80071548u) + 4 * (uint16)index) & ~3u);
    uint32 result, radius, angle, i, vertices, stream, packet, ordering, lights, type;
    sint32 threshold = (sint32)r_u32(0x80071580u);
    static const uint32 input_sizes[8] = {12, 16, 20, 28, 24, 28, 24, 28};
    static const uint32 output_sizes[8] = {20, 24, 0, 0, 32, 40, 32, 40};
    static const uint32 index_offsets[8] = {4, 4, 0, 0, 16, 16, 16, 16};
    w_u32(0x1F80002Cu, 0);
    w_u32(0x1F800028u, r_u32(object + 12) - r_u32(0x800BBFC4u));
    w_u32(0x1F800030u, r_u32(object + 16) - r_u32(0x800BBFCCu));
    sub_8005CC48(0x800AFE80u, 0x1F800028u, 0x1F800028u);
    radius = r_u32(object + 20);
    result = r_u32(0x1F800030u) + radius;
    if ((sint32)(r_u32(0x1F800030u) - radius) >= 30001 || (sint32)result < 0)
        return result;
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    angle = r_u16(0x800BBFD4u) & 4095u;
    if (angle >= 1024)
        angle = (angle < 2048 ? 1024 : angle < 3072 ? 3072 : 4096) - angle;
    w_u32(0x1F800030u, r_u32(0x1F800030u) + 4 * angle);
    for (i = 0; i != 3; ++i)
        draft_gte_control(5 + i, r_u32(0x1F800028u + 4 * i));
    w_u16(0x1F800020u, 0u - r_u16(object + 20));
    w_u16(0x1F800022u, 0);
    w_u16(0x1F800024u, r_u16(object + 20));
    b05_vertex(0x1F800020u, 0);
    draft_gte_command(0x180001u);
    w_u16(0x1F800020u, r_u16(object + 20));
    result = (sint16)draft_gte_read(14) < 424;
    if (!result)
        return result;
    b05_vertex(0x1F800020u, 0);
    draft_gte_command(0x180001u);
    result = (sint16)draft_gte_read(14) < -40;
    if (result)
        return result;
    for (i = 0; i != 3; ++i)
        w_u32(0x1F800028u + 4 * i, r_u32(object + 4 * i) - r_u32(0x800BBFC4u + 4 * i));
    if (r_u8(0x80071730u))
        for (i = 0; i != 3; ++i)
            w_u32(0x800BEFA8u + 4 * i, r_u32(object + 4 * i));
    sub_8005CC48(0x800BBFDCu, 0x1F800028u, 0x1F800028u);
    for (i = 0; i != 3; ++i)
        draft_gte_control(5 + i, r_u32(0x1F800028u + 4 * i));
    vertices = object + 28;
    stream = vertices + 8 * r_u32(object + 24);
    packet = r_u32(0x80071680u);
    ordering = r_u32(0x8007184Cu);
    lights = r_u32(0x80071948u);
    for (type = 0; type != 8; ++type)
    {
        uint32 count, n;
        result = type;
        if (r_u16(stream) != type)
            continue;
        count = r_u16(stream + 2);
        stream += 4;
        result = count;
        if (type == 2 || type == 3)
        {
            stream += input_sizes[type] * count;
            continue;
        }
        for (n = 0; n != count; ++n, stream += input_sizes[type])
        {
            uint32 triangle[3], j, depth, spacing = type < 2 ? 4 : 8, quad = type & 1;
            uint32 light, destination, page;
            result = (uint16)(count - n - 1u);
            for (j = 0; j != 3; ++j)
            {
                triangle[j] = vertices + 8 * r_u16(stream + index_offsets[type] + 2 * j);
                b05_vertex(triangle[j], 2 * j);
            }
            draft_gte_command(0x280030u);
            if (type >= 4)
            {
                w_u32(packet + 12, r_u32(stream + 4));
                w_u32(packet + 20, r_u32(stream + 8));
            }
            if (type < 6)
            {
                draft_gte_command(0x1400006u);
                if ((sint32)draft_gte_read(24) < 0)
                    continue;
            }
            draft_gte_command(0x158002Du);
            depth = (sint32)draft_gte_read(7) >> 2;
            if (depth - 1u >= 0x943u)
                continue;
            for (j = 0; j != 3; ++j)
                w_u32(packet + 8 + spacing * j, draft_gte_read(12 + j));
            if (quad)
            {
                b05_vertex(vertices + 8 * r_u16(stream + index_offsets[type] + 6), 0);
                draft_gte_command(0x180001u);
                if (type >= 4)
                    w_u16(packet + 28, r_u16(stream + 12));
                w_u32(packet + 8 + 3 * spacing, draft_gte_read(14));
            }
            if (!b05_on_screen(packet, quad ? 4 : 3, spacing))
                continue;
            light = r_u16(stream + (type < 2 ? (quad ? 12 : 10) : (quad ? 24 : 22)));
            if (light == 0xFFFFu)
            {
                w_u32(packet + 4, r_u32(stream));
                if (type >= 4)
                {
                    if (quad)
                        w_u16(packet + 36, r_u16(stream + 14));
                    else
                        w_u32(packet + 28, r_u32(stream + 12));
                }
            }
            else
            {
                draft_gte_data(6, r_u32(stream));
                b05_vertex(lights + 8 * light, 0);
                draft_gte_command(0xE80413u);
                if (type >= 4)
                {
                    if (quad)
                        w_u16(packet + 36, r_u16(stream + 14));
                    else
                        w_u32(packet + 28, r_u32(stream + 12));
                }
                w_u32(packet + 4, draft_gte_read(22));
            }
            if (type >= 4 && (sint32)depth < threshold)
            {
                page = r_u16(packet + 22);
                if (page & 192u)
                {
                    w_u16(packet + 22, page & 0xFF3Fu);
                    w_u16(packet + 22, (page & 0xFF3Fu) | r_u16(0x80071780u));
                    w_u8(packet + 7, r_u8(packet + 7) | 2u);
                }
            }
            if (type >= 4 && quad && r_u8(0x80071730u))
                sub_8002BB88(packet + 4, triangle[0], triangle[1], triangle[2]);
            destination = ordering + 4 * depth + (type >= 6 ? 400 : 0);
            w_u32(packet, r_u32(destination) | ((output_sizes[type] / 4 - 1) << 24));
            w_u32(destination, packet & 0xFFFFFFu);
            packet += output_sizes[type];
        }
    }
    w_u32(0x80071680u, packet);
    return result;
}
