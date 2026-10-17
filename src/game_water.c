#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80026E60(uint32 x0, uint32 y0, uint32 z0, uint32 x1, uint32 y1, uint32 z1, uint32 x2, uint32 y2, uint32 z2, uint32 x3, uint32 y3, uint32 z3, uint32 first, uint32 last)
{
    uint32 node = sub_80032EF0(), result;
    if (!node)
        return 16;
    w_u32(node + 8, 16);
    w_u32(node + 44, (uint32)((sint32)(x0 + x1 + x2 + x3) >> 2));
    w_u32(node + 48, (uint32)((sint32)(y0 + y1 + y2 + y3) >> 2));
    w_u16(node + 20, x1 - r_u16(node + 44));
    w_u16(node + 60, first);
    w_u16(node + 62, last);
    w_u16(node + 64, 0);
    w_u16(node + 66, 0);
    w_u32(node + 52, (uint32)((sint32)(z0 + z1 + z2 + z3) >> 2));
    w_u16(node + 36, x3 - r_u16(node + 44));
    w_u16(node + 12, x0 - r_u16(node + 44));
    w_u16(node + 28, x2 - r_u16(node + 44));
    w_u16(node + 22, y1 - r_u16(node + 48));
    w_u16(node + 14, y0 - r_u16(node + 48));
    w_u16(node + 30, y2 - r_u16(node + 48));
    w_u16(node + 38, y3 - r_u16(node + 48));
    w_u16(node + 16, z0 - r_u16(node + 52));
    w_u16(node + 24, z1 - r_u16(node + 52));
    result = z2 - r_u16(node + 52);
    w_u16(node + 32, result);
    w_u16(node + 40, z3 - r_u16(node + 52));
    return result;
}

static sint32 water_divide(sint32 value, sint32 divisor)
{
    if (!divisor || (value == (sint32)0x80000000 && divisor == -1))
        return (sint32)draft_unknown_return("sub_80035ED4 division BREAK");
    return value / divisor;
}

uint32 sub_80035ED4(uint32 corners, uint32 column, uint32 row, uint32 output)
{
    sint16 edge[2][3];
    uint32 side, axis, from, to, product, result = 0;
    sint32 divisor;
    for (side = 0; side < 2; ++side)
    {
        for (axis = 0; axis < 3; ++axis)
        {
            from = (uint32)(sint32)(sint16)r_u16(corners + 8 * side + 2 * axis);
            to = (uint32)(sint32)(sint16)r_u16(corners + 16 + 8 * side + 2 * axis);
            product = (to - from) * row;
            divisor = axis == 1 ? (sint32)(9 - row) : 4;
            edge[side][axis] = (sint16)(from + (uint32)water_divide((sint32)product, divisor));
        }
    }
    for (axis = 0; axis < 3; ++axis)
    {
        product = (uint32)(edge[1][axis] - edge[0][axis]) * column;
        result = (uint32)edge[0][axis] + (uint32)water_divide((sint32)product, 8);
        w_u16(output + 2 * axis, result);
    }
    return result;
}

uint32 sub_80027008(uint32 position, uint32 velocity, uint32 counter)
{
    uint32 node = sub_80032EF0(), x, y, z, pad, result;
    if (!node)
        return 17;
    w_u32(node + 8, 17);
    x = r_u32(position);
    y = r_u32(position + 4);
    z = r_u32(position + 8);
    pad = r_u32(position + 12);
    w_u32(node + 12, x);
    w_u32(node + 16, y);
    w_u32(node + 20, z);
    w_u32(node + 24, pad);
    w_u32(node + 28, velocity);
    w_u16(node + 32, 0);
    result = r_u16(counter) + 1;
    w_u16(counter, result);
    w_u32(node + 36, counter);
    return result;
}

uint32 sub_8003675C(uint32 node)
{
    uint32 velocity = r_u32(node + 28), result, counter;
    w_u32(node + 16, r_u32(node + 16) + (uint32)((sint32)velocity >> 3));
    w_u32(node + 28, velocity + 50);
    sub_80016358(node + 12, (uint32)((sint16)r_u16(node + 32) + 167), 6, 5, 2, 40);
    result = r_u16(0x800719D0) & 1;
    if (result)
        return result;
    result = r_u16(node + 32) + 1;
    w_u16(node + 32, result);
    result = (uint32)(sint32)(sint16)result;
    if (result != 7)
        return result;
    counter = r_u32(node + 36);
    w_u16(counter, r_u16(counter) - 1);
    return sub_80032FD0(node);
}

static uint32 water_screen_visible(uint32 packet, uint32 component, sint32 limit)
{
    sint32 value = (sint16)r_u16(packet + 8 + component), minimum = value, maximum = value;
    uint32 i;
    for (i = 1; i < 4; ++i)
    {
        value = (sint16)r_u16(packet + 8 + 12 * i + component);
        if (value < minimum)
            minimum = value;
        if (maximum < value)
            maximum = value;
    }
    return minimum < limit && maximum > 0;
}

uint32 sub_800360E8(uint32 node)
{
    uint16 vertices[3][4] = {{0}};
    uint32 buffer, region, kind, corners = node + 12, packet, ordering, texture, clut, page;
    uint32 row, column, i, depth, phase, first_u, second_u, color, address, result;
    sint32 first, last, span, offset;
    w_u16(node + 64, (r_u16(node + 64) - 7) & 63);
    region = r_u16(0x800BC0CC);
    if (region == 0xFFFF)
        return 0xFFFF;
    kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
    first = (sint16)r_u16(node + 60);
    last = (sint16)r_u16(node + 62);
    result = last < (sint32)kind;
    if (first < last)
    {
        if ((sint32)kind < first || result)
            return result;
    }
    else if ((sint32)kind < first && result)
        return result;
    w_u32(0x1F800030, r_u32(node + 52) - r_u32(0x800BBFCC));
    w_u32(0x1F800028, r_u32(node + 44) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(node + 48) - r_u32(0x800BBFC8));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    for (i = 0; i < 5; ++i)
        draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
    for (i = 0; i < 3; ++i)
        draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
    packet = r_u32(0x80071680);
    texture = r_u32(0x800B6BB4);
    clut = r_u16(texture + 10);
    page = r_u16(texture + 14);
    ordering = r_u32(0x8007184C);
    first_u = (r_u16(0x800719D0) & 1) ? 192 : 255;
    second_u = (r_u16(0x800719D0) & 1) ? 255 : 192;
    buffer = draft_local_address(vertices, sizeof(vertices));
    for (row = 0; row < 4; ++row)
    {
        for (column = 0; column < 8; ++column)
        {
            phase = r_u8(node + 64) & 63;
            sub_80035ED4(corners, column, row, buffer);
            sub_80035ED4(corners, column + 1, row, buffer + 8);
            sub_80035ED4(corners, column, row + 1, buffer + 16);
            for (i = 0; i < 6; ++i)
                draft_gte_data(i, r_u32(buffer + 4 * i));
            draft_gte_command(0x280030);
            sub_80035ED4(corners, column + 1, row + 1, buffer);
            draft_gte_command(0x158002D);
            depth = (uint32)((sint32)draft_gte_read(7) >> 2);
            if (depth - 1 >= 2499)
                continue;
            w_u32(packet + 8, draft_gte_read(12));
            w_u32(packet + 20, draft_gte_read(13));
            w_u32(packet + 32, draft_gte_read(14));
            draft_gte_data(0, r_u32(buffer));
            draft_gte_data(1, r_u32(buffer + 4));
            draft_gte_command(0x180001);
            w_u32(packet + 44, draft_gte_read(14));
            if (!water_screen_visible(packet, 0, 384) || !water_screen_visible(packet, 2, 256))
                continue;
            w_u8(packet + 3, 12);
            w_u8(packet + 7, 60);
            for (i = 0; i < 4; ++i)
            {
                color = 180 - 32 * (row + (i >= 2));
                w_u8(packet + 4 + 12 * i, color);
                w_u8(packet + 5 + 12 * i, color);
                w_u8(packet + 6 + 12 * i, color);
            }
            w_u16(packet + 14, clut);
            w_u16(packet + 26, page);
            for (i = 0; i < 4; ++i)
            {
                w_u8(packet + 12 + 12 * i, (i & 1) ? second_u : first_u);
                w_u8(packet + 13 + 12 * i, phase + (i >= 2 ? 63 : 0));
            }
            address = ordering + 4 * depth;
            w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(address) & 0xFFFFFF));
            w_u32(address, (r_u32(address) & 0xFF000000) | (packet & 0xFFFFFF));
            packet += 52;
        }
    }
    w_u32(0x80071680, packet);
    result = r_u16(0x800719D0) & 1;
    if (!result)
        return result;
    if ((sint16)r_u16(node + 66) >= 32)
        return 0;
    span = (sint16)r_u16(corners + 8) - (sint16)r_u16(corners);
    offset = ((sint32)(sub_80011B8C() & 63) * span / 80) >> 1;
    if (sub_80011B8C() & 1)
        offset = -offset;
    w_u32(0x1F800028, r_u32(node + 44) + (uint32)offset);
    w_u32(0x1F80002C, r_u32(node + 48) - 14000);
    w_u32(0x1F800030, r_u32(node + 52) - 6000);
    if ((sub_80011B8C() & 15) >= 11)
        w_u32(0x1F800030, r_u32(0x1F800030) - 7000);
    result = sub_80011B8C() & 255;
    return sub_80027008(0x1F800028, 0 - (result + 1000), node + 66);
}
