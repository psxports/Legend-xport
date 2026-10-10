#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
extern CdlLOC *CdIntToPos(sint32 sector, CdlLOC *position);
extern uint32 sub_8005CBB8(uint32 value);
/* Unverified draft; integration deferred */
/* TODO: Missing SDK and ABI declarations need fail-fast adapters during integration */
extern uint32 sub_800449A0(uint32 handle);
extern uint32 sub_80047864(uint32 first, uint32 second);
extern uint32 sub_80050250(void);
extern uint32 sub_80061B58(uint32 size);
extern uint32 sub_800623F8(uint32 address);
extern uint32 sub_80062488(uint32 mode);
extern uint32 sub_8005EEB8(uint32 packet, uint32 draw, uint32 dither, uint32 page, uint32 window);
extern uint32 sub_80060DB8(uint32 packet, uint32 primitive);

uint32 sub_80036AC8(uint32 a1)
{
    uint32 owner = r_u16(0x800BC0CCu), local = a1 + 12u, result = 0xFFFFu;
    sint32 strength = 8, lower, current, upper;
    uint32 state;
    if (owner == 0xFFFFu)
        return result;
    lower = (sint16)r_u16(a1 + 12u);
    current = (sint32)r_u8(r_u32(0x80071704u) + 14u * owner + 9u);
    if (current < lower)
    {
        sint32 delta = (sint16)(lower - current);
        if (delta >= 9)
            delta = 8;
        strength = 8 - delta;
    }
    upper = (sint32)r_u8(local + 2u);
    if (upper < current)
    {
        sint32 delta = current - upper;
        if (delta >= 9)
            delta = 8;
        strength = 8 - delta;
    }
    result = 1u;
    state = r_u16(local + 4u);
    if (state == 0u && strength)
    {
        w_u16(local + 6u, sub_8004496C());
        w_u16(local + 16u, 0u);
        w_u16(local + 4u, 1u);
    }
    else if (state == 1u)
    {
        if (!strength)
        {
            result = sub_800449A0(r_u16(local + 6u));
            w_u16(local + 4u, 0u);
        }
        else
        {
            uint32 limit = r_u16(local + 14u), count = (uint16)(r_u16(local + 16u) + 1u);
            w_u16(local + 16u, count);
            result = count < limit;
            if (!result)
            {
                uint32 volume, random;
                w_u16(local + 16u, 0u);
                result = (sub_80011B8C() & 127u) < 65u;
                if (!result)
                {
                    volume = (uint16)((sint32)((uint32)strength * r_u16(local + 12u)) >> 3);
                    random = sub_80011B8C();
                    /* TODO: Arguments after the two explicit outgoing stores are undefined in this call */
                    result = sub_8004486C(1u, r_u16(local + 6u), r_u16(local + 8u), (uint16)(r_u16(local + 10u) + (random & 63u)), volume, 512u);
                }
            }
        }
    }
    return result;
}

uint32 sub_80019498(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5)
{
    sint32 minimum[3] = {100000, 100000, 100000}, maximum[3] = {-100000, -100000, -100000};
    uint32 vertices = r_u32(a1), count = r_u32(a1 + 8u), i, axis;
    uint32 scales[3] = {a3, a4, a5};
    static const uint8 corners[8][3] = {{0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {1, 0, 0}, {0, 1, 0}, {0, 1, 1}, {1, 1, 1}, {1, 1, 0}};
    for (i = 0; i < count; ++i)
    {
        for (axis = 0; axis < 3u; ++axis)
        {
            sint32 coordinate = (sint32)((uint32)(sint32)(sint16)r_u16(vertices + 8u * i + 2u * axis) * scales[axis]) / 100;
            if (coordinate < minimum[axis])
                minimum[axis] = coordinate;
            if (maximum[axis] < coordinate)
                maximum[axis] = coordinate;
        }
    }
    for (i = 0; i < 8u; ++i)
        for (axis = 0; axis < 3u; ++axis)
            w_u32(a2 + 16u * i + 4u * axis, (uint32)(corners[i][axis] ? maximum[axis] : minimum[axis]));
    /* TODO: Zero vertices leave the original return carrier unspecified */
    return count ? 0u : draft_unknown_return("sub_80019498 empty vertices");
}

uint32 sub_8004E9E4(uint32 x, uint32 y, uint32 amount, uint32 maximum, uint32 shade)
{
    uint32 fill, packet, table, right_x, left_x, i;
    static const uint8 zero_offsets[] = {4, 5, 12, 13, 14, 20, 21, 28, 29, 30};
    amount = (uint16)amount;
    maximum = (uint16)maximum;
    /* TODO: Zero maximum raises original BREAK 7 */
    if (!maximum)
        return draft_unknown_return("sub_8004E9E4 division BREAK 7");
    fill = 72u * amount / maximum;
    if ((uint16)fill == 0u && amount)
        fill = 1u;
    if ((uint16)fill >= 73u)
        fill = 72u;
    if ((uint16)fill != 72u)
    {
        packet = r_u32(0x80071680u);
        w_u32(0x80071680u, packet + 40u);
        w_u8(packet + 3u, 8u);
        w_u8(packet + 7u, 0x38u);
        w_u8(packet + 6u, 128u);
        w_u8(packet + 22u, 128u);
        for (i = 0; i < sizeof(zero_offsets); ++i)
            w_u8(packet + zero_offsets[i], 0u);
        left_x = x + fill + 4u;
        right_x = left_x - (fill + 0xFFB8u);
        w_u16(packet + 10u, y + 3u);
        w_u16(packet + 18u, y + 3u);
        table = r_u32(0x8007184Cu);
        w_u16(packet + 8u, left_x);
        w_u16(packet + 24u, left_x);
        w_u16(packet + 26u, y + 8u);
        w_u16(packet + 34u, y + 8u);
        w_u16(packet + 16u, right_x);
        w_u16(packet + 32u, right_x);
        w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(table + 4u) & 0xFFFFFFu));
        w_u32(table + 4u, (r_u32(table + 4u) & 0xFF000000u) | (packet & 0xFFFFFFu));
    }
    /* TODO: Four trailing pseudo arguments are not explicit outgoing arguments */
    return sub_800180D4((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)y, 1u, 155u, (uint32)(sint32)(sint16)shade, (uint32)(sint32)(sint16)shade, (uint32)(sint32)(sint16)shade);
}

uint32 sub_80044DC8(uint32 a1, uint32 a2)
{
    uint32 dx = a1 - r_u32(0x800BBFC4u), dz = a2 - r_u32(0x800BBFCCu);
    uint32 ax = (sint32)dx < 0 ? 0u - dx : dx, az = (sint32)dz < 0 ? 0u - dz : dz;
    sint32 distance = (sint32)r_u32(0x800718A0u), angle, sector;
    uint32 result;
    if (distance == 0 || distance >= 8192)
        result = 512u;
    else
    {
        uint32 magnitude = (sint32)ax < (sint32)az ? ax : az;
        sint32 scaled = (sint32)(magnitude << 10), ratio;
        if (distance == -1 && scaled == (sint32)0x80000000u)
            return draft_unknown_return("sub_80044DC8 division BREAK 6");
        ratio = scaled / distance;
        if (ratio >= 1024)
            ratio = 1023;
        angle = (sint32)r_u16(((sint32)ax < (sint32)az ? 0x800BC9C0u : 0x800BC1B4u) + 2u * (uint32)ratio);
        if ((sint32)dx >= 0)
        {
            if ((sint32)dz >= 0)
                angle = 2048 - angle;
        }
        else
        {
            if ((sint32)dz >= 0)
                angle += 2048;
            else
                angle = 4095 - angle;
        }
        sector = (sint32)((((uint32)angle - r_u16(0x800BBFD6u)) << 20) >> 21);
        if (sector < 512)
            result = (uint32)sector + 512u;
        else if (sector < 1024)
            result = 1535u - (uint32)sector;
        else if (sector < 1536)
            result = 1536u - (uint32)sector;
        else
            result = (uint32)sector - 1536u;
    }
    w_u32(0x80071A20u, result);
    return result;
}

uint32 sub_8001F9D0(uint32 a1)
{
    uint32 x = r_u32(a1 + 64u), z = r_u32(a1 + 72u), ax = (sint32)x < 0 ? 0u - x : x, az = (sint32)z < 0 ? 0u - z : z;
    sint32 length, ratio;
    uint32 result, angle;
    while ((sint32)ax >= 2049 || (sint32)az >= 2049)
    {
        ax = (uint32)((sint32)ax >> 1);
        az = (uint32)((sint32)az >> 1);
    }
    length = (sint32)sub_8005CBB8(ax * ax + az * az);
    result = (sint32)ax < (sint32)az;
    if (!length)
        return result;
    ratio = (sint32)((result ? ax : az) << 10) / length;
    if (ratio >= 1024)
        ratio = 1023;
    angle = r_u16((result ? 0x800BC9C0u : 0x800BC1B4u) + 2u * (uint32)ratio);
    if ((sint32)x <= 0)
    {
        result = 2048u;
        if ((sint32)z <= 0)
            angle = result - angle;
    }
    else
    {
        result = 4095u;
        if ((sint32)z <= 0)
            angle += 2048u;
        else
            angle = result - angle;
    }
    w_u16(0x800BBFD6u, angle);
    return result;
}

uint32 sub_80011BB8(void)
{
    uint32 i, result, second, type0, type1;
    for (i = 0; i < 8u; ++i)
    {
        uint32 first = r_u8(0x80071634u + i), last = r_u8(0x8007163Cu + i);
        w_u8(0x80071834u + i, first);
        w_u8(0x8007183Cu + i, last);
    }
    w_u16(0x80071792u, 0u);
    w_u16(0x80071790u, 0u);
    for (i = 0; i < 2u; ++i)
    {
        w_u16(0x800BD1C8u + 8u * i, 0u);
        w_u16(0x800BD1CAu + 8u * i, 0u);
        w_u16(0x800BD1CCu + 8u * i, 0u);
        w_u16(0x800BD1CEu + 8u * i, 0u);
    }
    result = r_u8(0x80071834u);
    w_u16(0x80071A26u, 0u);
    w_u16(0x80071A24u, 0u);
    if (!result && r_u8(0x80071835u) == 65u)
    {
        uint32 high = r_u8(0x80071836u);
        w_u16(0x80071A24u, 65u);
        w_u16(0x80071790u, ~(r_u8(0x80071837u) | (high << 8)));
    }
    if (!r_u8(0x8007183Cu) && r_u8(0x8007183Du) == 65u)
    {
        uint32 high = r_u8(0x8007183Eu);
        w_u16(0x80071A26u, 65u);
        w_u16(0x80071792u, ~(r_u8(0x8007183Fu) | (high << 8)));
    }
    result = r_u16(0x80071790u);
    second = r_u16(0x80071792u);
    type0 = r_u16(0x80071A24u);
    type1 = r_u16(0x80071A26u);
    w_u16(0x80071660u, result);
    w_u16(0x800718D8u, result);
    w_u16(0x80071662u, second);
    w_u16(0x800718DAu, second);
    w_u16(0x8007160Cu, type0);
    w_u16(0x8007160Eu, type1);
    return result;
}

uint32 sub_80044528(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 result = sub_8004E214((uint16)a1), data, offset = 0u, remaining = a3 - 1u;
    if ((sint32)result < 0)
        return result;
    data = sub_8004E308();
    if ((uint16)a3)
    {
        do
        {
            uint32 size = r_u32(data + offset + 12u), source = data + offset + 48u, allocation, table = 0x800BED30u + 4u * (uint16)a2;
            offset += 48u + size;
            allocation = sub_80061B58(size);
            if (r_u32(table) != 0xFFFFFFFFu)
            {
                uint32 i;
                for (i = 0; i < (size >> 4); ++i)
                    w_u8(source + 16u * i + 1u, r_u8(source + 16u * i + 1u) | 2u);
                w_u32(table, r_u32(table) + allocation);
            }
            if (allocation)
            {
                w_u32(0u - 2146767144u + 4u * (uint16)a2, allocation);
                sub_800623F8(allocation);
                SpuWrite(psx_addr(source, size), size);
                while (!sub_80062488(0u))
                {
                }
            }
            ++a2;
        } while ((uint16)remaining-- != 0u);
    }
    return sub_8004E2C0();
}

uint32 sub_8004DD18(uint32 a1, uint32 a2)
{
    uint32 buffer = r_u32(0x8007166Cu), requested = a2, file_remaining = r_u32(0x8007157Cu), result;
    result = (sint32)file_remaining < (sint32)requested;
    if (result)
        requested = file_remaining;
    while (requested)
    {
        uint32 valid = r_u32(0x8007159Cu), cursor = r_u32(0x80071814u), chunk;
        if (cursor == valid)
        {
            uint32 capacity = r_u32(0x80071824u);
            uint32 position_words[2];
            CdlLOC *position = (CdlLOC *)position_words;
            w_u32(0x80071814u, 0u);
            do
            {
                CdIntToPos((sint32)r_u32(0x800718FCu), position);
            } while (!sub_8004DA84((uint8 *)position, buffer, (uint32)((sint32)capacity / 2048)));
            w_u32(0x8007159Cu, capacity);
            w_u32(0x800718FCu, r_u32(0x800718FCu) + (uint32)((sint32)capacity / 2048));
            valid = capacity;
        }
        chunk = requested;
        cursor = r_u32(0x80071814u);
        if ((sint32)(valid - cursor) < (sint32)requested)
            chunk = valid - cursor;
        sub_8004DA38(buffer + cursor, a1, chunk);
        requested -= chunk;
        a1 += chunk;
        w_u32(0x80071814u, r_u32(0x80071814u) + chunk);
        w_u32(0x8007157Cu, r_u32(0x8007157Cu) - chunk);
        result = chunk + r_u32(0x800717E8u);
        w_u32(0x800717E8u, result);
    }
    return result;
}

uint32 sub_80050414(void)
{
    uint32 i = 0u, result;
    while ((uint16)i < r_u16(0x800717ACu))
    {
        uint32 text = r_u32(0x80068A8Cu + 4u * r_u8(0x800715D4u + (uint16)i));
        sint32 width = (sint16)sub_8004ED48(text);
        uint32 coordinate = 0x800AFEA0u + 2u * (uint16)i, color = r_u8(0x80071A14u + (uint16)i);

        sub_8004EEFC(192u - (uint32)(width >> 1), (uint32)(sint32)(sint16)r_u16(coordinate), text, color, color, color, 2u);
        color = r_u8(0x80071A14u + (uint16)i);
        if (color)
        {
            w_u8(0x80071A14u + (uint16)i, color - 1u);
            if (r_u16(0x800719D0u) & 1u)
                w_u16(coordinate, r_u16(coordinate) - 1u);
        }
        ++i;
    }
    result = r_u8(0x80071A14u);
    if (!result)
    {
        result = r_u16(0x800717ACu);
        if (result)
            return sub_80050250();
    }
    return result;
}

uint32 sub_80020F8C(uint32 a1, uint32 a2, uint32 a3)
{
    sint32 maximum = (sint32)r_u32(0x800BC07Cu), increment = maximum / 24;
    sint32 difference = (sint32)(a2 - a1), divisor = (sint32)r_u32(0x800BC080u), velocity, current;
    if (!increment)
        increment = 1;
    if (!divisor || (divisor == -1 && difference == (sint32)0x80000000u))
        return draft_unknown_return("sub_80020F8C division BREAK");
    velocity = difference / divisor;
    if (velocity < -maximum)
        velocity = -maximum;
    if (velocity > maximum)
        velocity = maximum;
    if (!velocity)
        velocity = difference;
    current = (sint32)r_u32(a3);
    if (velocity < 0)
    {
        sint32 magnitude = -velocity;
        if (current >= magnitude)
            w_u32(a3, (uint32)magnitude);
        else
        {
            current = (sint32)((uint32)current + (uint32)increment);
            if (current > maximum)
                current = maximum;
            if (current > magnitude)
                current = magnitude;
            w_u32(a3, (uint32)current);
            velocity = -current;
        }
    }
    if (velocity >= 0)
    {
        current = (sint32)r_u32(a3);
        if (current >= velocity)
            w_u32(a3, (uint32)velocity);
        else
        {
            current = (sint32)((uint32)current + (uint32)increment);
            if (current > maximum)
                current = maximum;
            if (current > velocity)
                current = velocity;
            w_u32(a3, (uint32)current);
            velocity = current;
        }
    }
    return a1 + (uint32)velocity;
}

uint32 sub_800121A4(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10, uint32 a11)
{
    uint32 remaining = a11 - 1u, result = a10 << 16;
    if ((uint16)a11)
    {
        do
        {
            uint32 pixel = r_u16(a1), flag = pixel & 0x8000u;
            sint32 red = pixel & 31u, green = (pixel >> 5) & 31u, blue = (pixel >> 10) & 31u;
            a1 += 2u;
            if (flag)
            {
                sint32 average = (red + green + blue) / 3;
                blue = (sint32)((uint32)(blue - average) * a3) / 128 + average;
                green = (sint32)((uint32)(green - average) * a3) / 128 + average;
                red = (sint32)((uint32)(red - average) * a3) / 128 + average;
                if (blue < (sint16)a10)
                    blue = (sint16)a10;
                if (red < (sint16)a4)
                    red = (sint16)a4;
                if (green < (sint16)a9)
                    green = (sint16)a9;
                if (blue >= 32)
                    blue = 31;
                if (green >= 32)
                    green = 31;
                if (red >= 32)
                    red = 31;
            }
            w_u16(a2, flag | ((uint32)blue << 10) | ((uint32)green << 5) | (uint32)red);
            a2 += 2u;
            result = (uint16)remaining;
        } while ((uint16)remaining-- != 0u);
    }
    return result;
}

uint32 sub_80047B68(void)
{
    uint32 i = 0u, result = r_u16(0x80071688u);
    while ((uint16)i < r_u16(0x80071688u))
    {
        uint32 first = r_u32(0u - 2146700608u + 4u * (uint16)i), j = 0u;
        sub_80047224(first);
        while ((uint16)j < r_u16(0x80071668u))
        {
            uint32 second = r_u32(0x800BEFD0u + 4u * (uint16)j);
            if (r_u32(second + 124u) != first && r_u32(first + 124u) != second && (r_u16(second + 140u) == 0xFFFFu || r_u16(first + 142u)))
            {
                if (!r_u32(second + 16u))
                    sub_80047224(second);
                sub_80047864(first, second);
            }
            ++j;
        }
        result = (uint16)++i;
    }
    return result;
}

uint32 sub_800180D4(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7)
{
    uint32 packet = r_u32(0x80071680u), texture = 0x800C0564u + 16u * a4, table, result;
    w_u32(0x80071680u, packet + 40u);
    w_u8(packet + 15u, 4u);
    w_u8(packet + 19u, 100u);
    /* TODO: MIPS reads stack arguments 5 through 7; pseudo mislabeled them 9 through 11 */
    w_u8(packet + 16u, a5);
    w_u8(packet + 17u, a6);
    w_u8(packet + 18u, a7);
    w_u16(packet + 20u, a1 - r_u16(texture + 12u));
    w_u16(packet + 22u, a2 - r_u16(texture + 14u));
    w_u8(packet + 24u, r_u8(texture + 4u));
    w_u8(packet + 25u, r_u8(texture + 6u));
    w_u16(packet + 28u, r_u16(texture + 8u) - 1u);
    w_u16(packet + 30u, r_u16(texture + 10u) - 1u);
    w_u16(packet + 26u, r_u16(texture + 2u));
    sub_8005EEB8(packet, 1u, 1u, r_u16(texture), 0u);
    sub_80060DB8(packet, packet + 12u);
    table = r_u32(0x8007184Cu) + 4u * a3;
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(table) & 0xFFFFFFu));
    result = (r_u32(table) & 0xFF000000u) | (packet & 0xFFFFFFu);
    w_u32(table, result);
    return result;
}

uint32 sub_80057514(uint32 a1)
{
    uint32 item = 0x800BFD08u + 40u * (uint16)a1, result = 40u * (uint16)a1;
    if (!r_u32(item))
    {
        uint32 count, size, data, table, i;
        uint16 kind;
        sub_8004DD18(draft_local_address(&count, sizeof(count)), 4u);
        sub_8004DD18(draft_local_address(&size, sizeof(size)), 4u);
        sub_8004DD18(draft_local_address(&kind, sizeof(kind)), 2u);
        data = sub_80011A98(size);
        table = sub_80011A98(4u * count);
        sub_8004DD18(data, size);
        w_u32(item + 4u, table);
        w_u16(item + 20u, kind);
        w_u32(item, count);
        for (i = 0; (uint16)i < count; ++i)
        {
            sint32 first = (sint16)r_u16(data + 4u), second = (sint16)r_u16(data + 6u);
            w_u32(r_u32(item + 4u) + 4u * (uint16)i, data);
            data += 2u * (uint32)(first / 2 + second / 2 + 7);
        }
        result = 0u;
    }
    return result;
}

uint32 sub_80030E5C(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    sint32 dx = (sint32)(r_u32(a2) - r_u32(a1)), dz = (sint32)(r_u32(a2 + 8u) - r_u32(a1 + 8u));
    uint32 distance = 0u;
    sint32 step = (sint32)a3;
    if (a4)
        distance = sub_8001F8A8((uint32)dx, (uint32)dz);
    if (dx)
    {
        if (dz)
            step = (sint32)((uint32)step - (uint32)(step >> 4));
        if (dx > 0 && step < dx)
            dx = step;
        if (dx < 0 && (uint32)step < 0u - (uint32)dx)
            dx = (sint32)(0u - (uint32)step);
    }
    if (dz > 0 && step < dz)
        dz = step;
    if (dz < 0 && (uint32)step < 0u - (uint32)dz)
        dz = (sint32)(0u - (uint32)step);
    w_u32(a1, r_u32(a1) + (uint32)dx);
    w_u32(a1 + 8u, r_u32(a1 + 8u) + (uint32)dz);
    return a4 ? (sint32)a4 < (sint32)distance : 1u;
}

uint32 sub_80012CB0(uint32 a1)
{
    uint32 buffer = sub_80011A98(0x8000u), allocation = r_u8(0x800C04F4u + (uint16)a1), index = r_u8(0x8007154Cu);
    uint32 x, y;
    PSX_RECT rectangle;
    a1 = (uint16)a1;
    w_u8(0x800BD21Cu + index, r_u8(0x800C04F4u + a1));
    w_u32(0x800BD234u + 4u * index, buffer);
    index = r_u8(0x8007154Cu);
    w_u8(0x800BD204u + index, r_u8(0x800C020Cu + a1));
    w_u16(0x800C9DCCu + 2u * index, r_u16(0x800AF684u + 2u * a1));
    w_u16(0x800BF4C0u + 2u * r_u8(0x8007154Cu), r_u16(0x800AEE74u + 2u * a1));
    sub_80012780(allocation, &x, &y);
    rectangle.x = (sint16)x;
    rectangle.y = (sint16)y;
    rectangle.w = 64;
    rectangle.h = 256;
    sub_8005E2F0(draft_local_address(&rectangle, sizeof(rectangle)), r_u32(0x800BD234u + 4u * r_u8(0x8007154Cu)));
    DrawSync(0);
    index = r_u8(0x8007154Cu) + 1u;
    w_u8(0x8007154Cu, index);
    return index;
}

extern uint32 sub_8005CA28(uint32 angle);
extern uint32 sub_8005C958(uint32 angle);

uint32 sub_8001F338(void)
{
    uint32 i;
    for (i = 0; i < 3u; ++i)
    {
        uint32 angle0 = (uint32)(sint32)(sint16)r_u16(0x800C5D4Eu + 8u * i);
        uint32 cosine0 = sub_8005CA28(angle0), sine0 = sub_8005C958(angle0);
        uint32 angle1 = (uint32)(sint32)(sint16)r_u16(0x800C5D4Cu + 8u * i);
        uint32 cosine1 = sub_8005CA28(angle1), sine1 = sub_8005C958(angle1);
        w_u16(0x800B7184u + 6u * i, (uint32)((sint32)((0u - sine0) * cosine1) / 4096));
        w_u16(0x800B7186u + 6u * i, 0u - sine1);
        w_u16(0x800B7188u + 6u * i, (uint32)((sint32)(cosine0 * cosine1) / 4096));
    }
    return 0u;
}

uint32 sub_80046B84(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 ax = (sint32)a1 < 0 ? 0u - a1 : a1, az = (sint32)a2 < 0 ? 0u - a2 : a2;
    sint32 ratio, numerator;
    uint32 angle;
    if (!a3)
        return 0u;
    numerator = (sint32)(((sint32)ax < (sint32)az ? ax : az) << 10);
    if (a3 == 0xFFFFFFFFu && numerator == (sint32)0x80000000u)
        return draft_unknown_return("sub_80046B84 division BREAK 6");
    ratio = numerator / (sint32)a3;
    if (ratio >= 1024)
        ratio = 1023;
    angle = r_u16(((sint32)ax < (sint32)az ? 0x800BC9C0u : 0x800BC1B4u) + 2u * (uint32)ratio);
    if ((sint32)a1 < 0)
    {
        if ((sint32)a2 <= 0)
            angle += 2048u;
        else
            angle = 4095u - angle;
    }
    else if ((sint32)a2 <= 0)
        angle = 2048u - angle;
    return (uint32)(sint32)(sint16)angle;
}
