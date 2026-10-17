#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
extern uint32 sub_8005D3C8(uint32 rotation, uint32 matrix);

static void render_a_controls(uint32 matrix, uint32 first, uint32 count)
{
    uint32 i;
    for (i = 0; i < count; ++i)
        draft_gte_control(first + i, r_u32(matrix + 4u * i));
}

static void render_a_vector(uint32 address, uint32 first)
{
    draft_gte_data(first, r_u32(address));
    draft_gte_data(first + 1, r_u32(address + 4));
}

static void render_a_compose(uint32 source, uint32 destination)
{
    uint32 column, row;
    for (column = 0; column < 3; ++column)
    {
        for (row = 0; row < 3; ++row)
            draft_gte_data(9 + row, r_u16(source + column * 2 + row * 6));
        draft_gte_command(0x49E012u);
        for (row = 0; row < 3; ++row)
            w_u16(destination + column * 2 + row * 6, draft_gte_read(9 + row));
    }
}

static uint32 render_a_mesh(uint32 mesh, uint32 *cleanup_hint)
{
    static const uint8 record_sizes[8] = {12, 16, 20, 28, 24, 28, 24, 28};
    static const uint8 packet_sizes[8] = {20, 24, 28, 36, 32, 40, 32, 40};
    uint32 packet = r_u32(0x80071680u), ordering = r_u32(0x8007184Cu), visible = r_u16(mesh + 90), first = 1, result;
    do
    {
        uint32 geometry = r_u32(mesh + 80), rotation = r_u16(mesh + 86), parent = r_u32(mesh + 96), i;
        w_u16(mesh + 88, r_u16(mesh + 88) & 1u);
        if (rotation == 0)
            sub_8005D138(mesh + 24, mesh + 32);
        else if (rotation == 1)
            sub_8005D3C8(mesh + 24, mesh + 32);
        else if (rotation == 2)
            sub_8005D658(mesh + 24, mesh + 32);
        if (parent)
        {
            render_a_controls(parent + 32, 0, 5);
            render_a_controls(parent + 8, 5, 3);
            render_a_vector(mesh, 0);
            draft_gte_command(0x480012u);
            for (i = 0; i < 3; ++i)
                w_u32(mesh + 8 + 4 * i, draft_gte_read(25 + i));
            render_a_compose(mesh + 32, mesh + 32);
        }
        w_u32(0x1F800028u, r_u32(mesh + 8) - r_u32(0x800BBFC4u));
        w_u32(0x1F80002Cu, r_u32(mesh + 12) - r_u32(0x800BBFC8u));
        w_u32(0x1F800030u, r_u32(mesh + 16) - r_u32(0x800BBFCCu));
        result = sub_8005CC48(0x800BBFDCu, 0x1F800028u, mesh + 64);
        if (cleanup_hint)
            *cleanup_hint = mesh + 64;
        if (geometry && visible)
        {
            uint32 depth = r_u32(mesh + 72), radius = r_u32(geometry + 16);
            result = depth - radius;
            if ((sint32)(depth + radius) >= 129)
            {
                result = (sint32)result < 20000;
                if (result)
                {
                    result = r_u16(mesh + 88);
                    if (result)
                    {
                        uint32 culled = (uint16)sub_8001A694(mesh, radius);
                        result = first;
                        if (!culled)
                        {
                            uint32 vertices = r_u32(geometry), normals = r_u32(geometry + 4), records = r_u32(geometry + 12), format;
                            if (first)
                            {
                                sub_8001B7A0(0);
                                first = 0;
                            }
                            w_u16(mesh + 88, r_u16(mesh + 88) | 2u);
                            render_a_controls(0x800B7184u, 0, 5);
                            render_a_compose(mesh + 32, 0x1F800000u);
                            render_a_controls(0x1F800000u, 8, 5);
                            render_a_controls(0x800BBFDCu, 0, 5);
                            if (!r_u16(mesh + 84))
                            {
                                render_a_compose(mesh + 32, 0x1F800000u);
                                render_a_controls(0x1F800000u, 0, 5);
                            }
                            for (format = 0; format < 8; ++format)
                            {
                                uint32 count, n;
                                result = format;
                                if (r_u16(records) != format)
                                    continue;
                                count = r_u16(records + 2);
                                records += 4;
                                result = count;
                                for (n = 0; n < count; ++n)
                                {
                                    uint32 vertex_offset = format < 2 ? 4u : (format == 2 ? 12u : 16u);
                                    uint32 normal_offset = format == 0 ? 10u : (format == 1 ? 12u : (format == 2 ? 18u : ((format == 4 || format == 6) ? 22u : 24u)));
                                    sint32 bucket;
                                    uint32 accepted = 1, ot, j;
                                    for (j = 0; j < 3; ++j)
                                        render_a_vector(vertices + 8u * r_u16(records + vertex_offset + 2u * j), 2u * j);
                                    draft_gte_command(0x280030u);
                                    if (format == 4 || format == 6)
                                        w_u32(packet + 12, r_u32(records + 4));
                                    if (format == 5 || format == 7)
                                        w_u16(packet + 36, r_u16(records + 14));
                                    if (format < 6)
                                    {
                                        draft_gte_command(0x1400006u);
                                        accepted = (sint32)draft_gte_read(24) > 0;
                                    }
                                    if (accepted)
                                    {
                                        draft_gte_command(0x158002Du);
                                        bucket = (sint32)draft_gte_read(7) >> 2;
                                        if (((uint32)bucket - 16u) < 0x9B4u)
                                        {
                                            w_u32(packet + 8, draft_gte_read(12));
                                            w_u32(packet + (format < 2 ? 12 : 16), draft_gte_read(13));
                                            w_u32(packet + (format < 2 ? 16 : 24), draft_gte_read(14));
                                            if (format == 1 || format == 3 || format == 5 || format == 7)
                                            {
                                                render_a_vector(vertices + 8u * r_u16(records + vertex_offset + 6), 0);
                                                draft_gte_command(0x180001u);
                                                w_u32(packet + (format == 1 ? 20 : 32), draft_gte_read(14));
                                            }
                                            render_a_vector(normals + 8u * r_u16(records + normal_offset), 0);
                                            draft_gte_data(6, r_u32(records));
                                            draft_gte_command(0xE80413u);
                                            if (format == 2 || format == 3)
                                            {
                                                w_u32(packet + 4, draft_gte_read(22));
                                                draft_gte_data(6, r_u32(records + 4));
                                                draft_gte_command(0xE80413u);
                                                w_u32(packet + 12, draft_gte_read(22));
                                                if (format == 3)
                                                {
                                                    draft_gte_data(6, r_u32(records + 8));
                                                    draft_gte_command(0xE80413u);
                                                    w_u32(packet + 20, draft_gte_read(22));
                                                }
                                                draft_gte_data(6, r_u32(records + (format == 2 ? 8 : 12)));
                                                draft_gte_command(0xE80413u);
                                            }
                                            if (format == 4 || format == 6)
                                            {
                                                w_u32(packet + 20, r_u32(records + 8));
                                                w_u32(packet + 28, r_u32(records + 12));
                                            }
                                            if (format == 5 || format == 7)
                                            {
                                                w_u32(packet + 12, r_u32(records + 4));
                                                w_u32(packet + 20, r_u32(records + 8));
                                                w_u16(packet + 28, r_u16(records + 12));
                                            }
                                            ot = ordering + 4u * (uint32)bucket;
                                            w_u32(packet, r_u32(ot) | ((uint32)(packet_sizes[format] / 4u - 1u) << 24));
                                            w_u32(ot, packet & 0xFFFFFFu);
                                            w_u32(packet + (format == 2 ? 20 : (format == 3 ? 28 : 4)), draft_gte_read(22));
                                            packet += packet_sizes[format];
                                        }
                                    }
                                    records += record_sizes[format];
                                    result = (uint16)(count - n - 1u);
                                }
                            }
                            if (cleanup_hint)
                                *cleanup_hint = records;
                        }
                    }
                }
            }
        }
        mesh = r_u32(mesh + 92);
    } while (mesh);
    w_u32(0x80071680u, packet);
    return result;
}

uint32 sub_8001C4B8(uint32 mesh)
{
    return render_a_mesh(mesh, 0);
}

uint32 legend_render_mesh_for_region_check(uint32 mesh, uint32 *cleanup_hint)
{
    /* The original caller uses the outgoing model cursor when no player is active */
    return render_a_mesh(mesh, cleanup_hint);
}
