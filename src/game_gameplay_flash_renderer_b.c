#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static void flash_vertex(uint32 vertices, uint32 index, uint32 slot)
{
    uint32 source = vertices + 8u * index;
    draft_gte_data(2u * slot, r_u32(source));
    draft_gte_data(2u * slot + 1u, r_u32(source + 4u));
}

uint32 sub_8001A7A8(uint32 mesh, uint32 red, uint32 green, uint32 blue)
{
    static const uint8 strides[8] = {12, 16, 20, 28, 24, 28, 24, 28};
    static const uint8 indices[8] = {4, 4, 12, 16, 16, 16, 16, 16};
    uint32 packet = r_u32(0x80071680u), ot = r_u32(0x8007184Cu);
    uint32 model, result, depth, radius, axis, column, stream, vertices, kind, count, i, quad, bucket;
    do
    {
        model = r_u32(mesh + 80u);
        w_u16(mesh + 88u, r_u16(mesh + 88u) & 1u);
        sub_8001A518(mesh);
        sub_8001A414(mesh);
        sub_8001A494(mesh);
        result = sub_8001A59C(mesh);
        if (model)
        {
            depth = r_u32(mesh + 72u);
            radius = r_u32(model + 16u);
            result = depth - radius;
            if ((sint32)(depth + radius) >= 64)
            {
                result = (sint32)result < 20000;
                if (result)
                {
                    result = r_u16(mesh + 88u);
                    if (result)
                    {
                        result = (uint16)sub_8001A694(mesh, radius);
                        if (!result)
                        {
                            w_u16(mesh + 88u, r_u16(mesh + 88u) | 2u);
                            for (axis = 0u; axis < 5u; ++axis)
                                draft_gte_control(axis, r_u32(0x800BBFDCu + 4u * axis));
                            if (!r_u16(mesh + 84u))
                            {
                                for (column = 0u; column < 3u; ++column)
                                {
                                    for (axis = 0u; axis < 3u; ++axis)
                                        draft_gte_data(9u + axis, r_u16(mesh + 32u + 2u * column + 6u * axis));
                                    draft_gte_command(0x49E012u);
                                    for (axis = 0u; axis < 3u; ++axis)
                                        w_u16(0x1F800000u + 2u * column + 6u * axis, draft_gte_read(9u + axis));
                                }
                                for (axis = 0u; axis < 5u; ++axis)
                                    draft_gte_control(axis, r_u32(0x1F800000u + 4u * axis));
                            }
                            for (axis = 0u; axis < 3u; ++axis)
                                draft_gte_control(5u + axis, r_u32(mesh + 64u + 4u * axis));
                            stream = r_u32(model + 12u);
                            vertices = r_u32(model);
                            for (kind = 0u; kind < 8u; ++kind)
                            {
                                result = kind;
                                if (r_u16(stream) != kind)
                                    continue;
                                count = r_u16(stream + 2u);
                                stream += 4u;
                                for (i = 0u; i < count; ++i)
                                {
                                    quad = kind & 1u;
                                    for (axis = 0u; axis < 3u; ++axis)
                                        flash_vertex(vertices, r_u16(stream + indices[kind] + 2u * axis), axis);
                                    draft_gte_command(0x280030u);
                                    w_u8(packet + 3u, quad ? 5u : 4u);
                                    w_u8(packet + 7u, quad ? 40u : 32u);
                                    w_u8(packet + 4u, red);
                                    w_u8(packet + 5u, green);
                                    w_u8(packet + 6u, blue);
                                    draft_gte_command(0x1400006u);
                                    if ((sint32)draft_gte_read(24u) > 0)
                                    {
                                        draft_gte_command(0x158002Du);
                                        depth = (uint32)((sint32)draft_gte_read(7u) >> 2);
                                        if (depth - 16u < 0x9B4u)
                                        {
                                            for (axis = 0u; axis < 3u; ++axis)
                                                w_u32(packet + 8u + 4u * axis, draft_gte_read(12u + axis));
                                            if (quad)
                                            {
                                                flash_vertex(vertices, r_u16(stream + indices[kind] + 6u), 0u);
                                                draft_gte_command(0x180001u);
                                            }
                                            bucket = ot + 4u * depth;
                                            w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(bucket) & 0xFFFFFFu));
                                            w_u32(bucket, (r_u32(bucket) & 0xFF000000u) | (packet & 0xFFFFFFu));
                                            if (quad)
                                                w_u32(packet + 20u, draft_gte_read(14u));
                                            packet += quad ? 24u : 20u;
                                        }
                                    }
                                    stream += strides[kind];
                                }
                                if (kind == 7u)
                                    result = 0u;
                            }
                        }
                    }
                }
            }
        }
        mesh = r_u32(mesh + 92u);
    } while (mesh);
    w_u32(0x80071680u, packet);
    return result;
}
