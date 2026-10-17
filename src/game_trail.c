#include "psx.h"
#include "game_draft_signatures.h"

static void trail_link_packet(uint32 packet, uint32 bucket)
{
    uint32 entry = r_u32(0x8007184C) + 4 * bucket;
    w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(entry) & 0xFFFFFF));
    w_u32(entry, (r_u32(entry) & 0xFF000000) | (packet & 0xFFFFFF));
}

uint32 sub_8003160C(uint32 trail)
{
    uint32 buffer, head, index, record, count = 0, parity, i, endpoint;
    uint32 xy[2][2], depth[2], kind, packet, descriptor, stride, result;
    uint32 decay_step, decay_value, decay_remaining = 30, color, u, v;
    sint32 product, bucket, green, decrement;
    trail = (uint16)trail;
    buffer = r_u32(0x800BD408 + 4 * trail);
    index = r_u16(0x800AEA5C + 2 * trail);
    head = r_u16(0x800BD398 + 2 * trail);
    if ((r_u16(0x800C04E4 + 2 * trail) & 128) && index == head)
        return sub_8003118C(trail);
    if (index == head)
        return head;
    decay_step = r_u32(0x800C9DA0 + 4 * trail);
    decay_value = 30 * decay_step;
    do
    {
        index = (index + 1) & 31;
        record = buffer + 36 * index;
        for (i = 0; i < 3; ++i)
            w_u32(0x1F800028 + 4 * i, r_u32(record + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
        sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
        for (i = 0; i < 3; ++i)
            draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
        parity = count & 1;
        depth[parity] = r_u32(0x1F800030);
        for (endpoint = 0; endpoint < 2; ++endpoint)
        {
            for (i = 0; i < 3; ++i)
            {
                product = (sint32)((uint32)(sint16)r_u16(record + 16 + 8 * endpoint + 2 * i) * r_u32(record + 32));
                w_u16(0x1F800020 + 2 * i, product >> 7);
            }
            if (endpoint)
                xy[0][parity] = draft_gte_read(14);
            draft_gte_data(0, r_u32(0x1F800020));
            draft_gte_data(1, r_u32(0x1F800024));
            draft_gte_command(0x180001);
        }
        xy[1][parity] = draft_gte_read(14);
        if (count)
        {
            bucket = (sint32)(depth[0] + depth[1]) >> 5;
            if ((uint32)(bucket - 16) < 0x9B4)
            {
                kind = r_u16(0x800C04E4 + 2 * trail) & 127;
                if (kind < 6)
                {
                    packet = r_u32(0x80071680);
                    w_u32(0x80071680, packet + 40);
                    if (kind < 3)
                    {
                        w_u8(packet + 3, 5);
                        w_u8(packet + 7, 40);
                        if (kind == 0)
                        {
                            color = 2 * r_u32(record + 32);
                            green = (sint32)(color - 2 * (255 - color));
                            w_u8(packet + 4, color);
                            w_u8(packet + 5, green < 0 ? 0 : green);
                            w_u8(packet + 6, 0);
                        }
                        else
                        {
                            w_u8(packet + 4, 0);
                            w_u8(packet + 5, kind == 1 ? 2 * r_u8(record + 32) : 0);
                            w_u8(packet + 6, kind == 2 ? 2 * r_u8(record + 32) : 0);
                        }
                        stride = 4;
                    }
                    else
                    {
                        w_u8(packet + 3, 9);
                        w_u8(packet + 7, 44);
                        w_u8(packet + 4, r_u8(record + 32));
                        w_u8(packet + 5, r_u8(record + 32));
                        w_u8(packet + 6, r_u8(record + 32));
                        descriptor = 0x800C0FA4 + 16 * (kind - 3);
                        u = r_u8(descriptor + 4);
                        v = r_u8(descriptor + 6);
                        w_u8(packet + 12, u + 1);
                        w_u8(packet + 13, v + 1);
                        w_u8(packet + 20, u + r_u8(descriptor + 8) - 2);
                        w_u8(packet + 21, v + 1);
                        w_u8(packet + 28, u + 1);
                        w_u8(packet + 29, v + r_u8(descriptor + 10) - 1);
                        w_u8(packet + 36, u + r_u8(descriptor + 8) - 2);
                        w_u8(packet + 37, v + r_u8(descriptor + 10) - 1);
                        stride = 8;
                    }
                    w_u8(packet + 7, r_u8(packet + 7) | 2);
                    w_u32(packet + 8, xy[0][parity ^ 1]);
                    w_u32(packet + 8 + stride, xy[0][parity]);
                    w_u32(packet + 8 + 2 * stride, xy[1][parity ^ 1]);
                    w_u32(packet + 8 + 3 * stride, xy[1][parity]);
                    if (kind >= 3)
                    {
                        w_u16(packet + 14, r_u16(descriptor + 2));
                        w_u16(packet + 22, r_u16(descriptor) | r_u16(0x80071782));
                    }
                    trail_link_packet(packet, (uint32)bucket);
                    if (kind < 3)
                    {
                        packet = r_u32(0x80071680);
                        w_u32(0x80071680, packet + 40);
                        sub_8005EEB8(packet, 1, 1, r_u16(0x80071782), 0);
                        trail_link_packet(packet, (uint32)bucket);
                    }
                }
            }
        }
        ++count;
        decrement = (sint32)decay_value / 32;
        if (!decrement)
            decrement = 1;
        if (decay_remaining)
        {
            decay_value -= decay_step;
            --decay_remaining;
        }
        result = r_u32(record + 32) - (uint32)decrement;
        w_u32(record + 32, result);
        if ((sint32)result <= 0)
            w_u32(record + 32, 0);
    } while (index != head);
    index = (r_u16(0x800AEA5C + 2 * trail) + 1) & 31;
    result = r_u32(buffer + 36 * index + 32);
    if (!result)
        w_u16(0x800AEA5C + 2 * trail, index);
    return result;
}
