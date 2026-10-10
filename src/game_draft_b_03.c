#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdlib.h>
/* Unverified draft; integration deferred */
/* TODO: Missing SDK boundaries remain declarations for later fail-fast integration */
extern uint32 sub_800122F4(uint32 input, uint32 output, uint32 count);
extern uint32 sub_8005D138(uint32 angles, uint32 matrix);
extern uint32 sub_8005CF68(uint32 matrix);
extern uint32 sub_8005CDA8(uint32 input, uint32 output);
extern void sub_8005CAC8(uint32 far_color, uint32 distance);
extern uint32 sub_8004A9E8(void);
extern uint32 sub_8004B164(void);
extern uint32 sub_80062368(uint32 attributes);
extern uint32 sub_800628B8(uint32 attributes);
extern uint32 sub_800621A8(uint32 enabled, uint32 voices);

uint32 sub_80011DDC(uint32 a1, uint32 a2, uint32 a3)
{
    uint8 occupied[10][24] = {{0}};
    uint32 i, row, column, x = 0u, y = 0u, packed, count;
    PSX_RECT rectangle;
    a1 = (uint16)a1;
    a2 = (uint16)a2;
    a3 = (uint16)a3;
    for (i = 0u; (uint16)i < r_u16(0x800716B4u); ++i)
    {
        sint32 position_x, position_y;
        uint32 mode, length;
        if (r_u16(0x800AF1F4u + 2u * (uint16)i) == a1 && r_u8(0x800BF4ECu + (uint16)i) == a2 && r_u8(0x800BF7F0u + (uint16)i) == a3)
            return (uint16)i;
        sub_80011DC0(r_u16(0x800C0224u + 2u * (uint16)i), draft_local_address(&position_x, sizeof(position_x)), draft_local_address(&position_y, sizeof(position_y)));
        position_y -= 502;
        position_x /= 16;
        mode = r_u8(0x800BF4ECu + (uint16)i);
        length = mode ? 16u : 1u;
        /* TODO: Invalid unpacked positions would overwrite adjacent original locals */
        if ((uint32)position_y >= 10u || position_x < 0 || (uint32)position_x + length > 24u)
            abort();
        for (column = 0; column < length; ++column)
            occupied[position_y][(uint32)position_x + column] = 1u;
    }
    if (r_u16(0x800716B4u) == 240u)
        return 0u;
    for (row = 0; row < 10u; ++row)
    {
        if (a2 == 1u)
        {
            uint32 empty = 0u;
            for (column = 0; column < 16u; ++column)
                if (!occupied[row][column])
                    ++empty;
            if (empty == 16u && !y)
            {
                y = row + 502u;
                x = 0u;
            }
        }
        else
        {
            for (column = 0; column < 24u; ++column)
                if (!occupied[row][column] && !y)
                {
                    y = row + 502u;
                    x = 16u * column;
                }
        }
    }
    if (!y)
        return 0u;
    packed = GetClut((sint32)x, (sint32)y);
    count = r_u16(0x800716B4u);
    w_u8(0x800BF4ECu + count, a2);
    w_u16(0x800AF1F4u + 2u * count, a1);
    count = r_u16(0x800716B4u);
    w_u16(0x800C0224u + 2u * count, packed);
    w_u8(0x800BF7F0u + count, a3);
    rectangle.x = (sint16)x;
    rectangle.y = (sint16)y;
    rectangle.w = a2 ? 256 : 16;
    rectangle.h = 1;
    if (a2)
        sub_80011D78(a1, draft_local_address(&rectangle, sizeof(rectangle)));
    else
        sub_80011D3C(a1, draft_local_address(&rectangle, sizeof(rectangle)));
    count = r_u16(0x800716B4u);
    w_u16(0x800716B4u, count + 1u);
    return count;
}

uint32 sub_80052B94(uint32 a1, uint32 a2, uint32 a3)
{
    static const uint16 offsets[] = {168, 336, 504, 672, 840, 1008, 1176, 1680, 1848, 2016, 2184};
    static const uint16 cleared_halfwords[] = {16, 20, 24, 28, 36, 40, 228, 232, 242, 278, 258, 236, 234, 276, 274};
    uint32 result = r_u8(a1 + 240u), model, capsule, target, i, type;
    w_u32(a1 + 52u, 0u);
    w_u32(a1 + 56u, 0u);
    w_u32(a1 + 64u, 0u);
    w_u32(a1 + 60u, 0u);
    if (!result)
        return result;
    type = r_u8(a1 + 212u);
    model = sub_8001F150(r_u16(0x80069A50u + 2u * type));
    w_u32(a1 + 52u, model);
    if (r_u8(a1 + 212u) == 1u)
        w_u32(r_u32(model) + 332u, 0u - 32u);
    capsule = sub_800471B4();
    w_u32(a1 + 56u, capsule);
    w_u16(capsule + 26u, 0u);
    w_u32(r_u32(a1 + 56u) + 16u, 2000u);
    w_u32(r_u32(a1 + 56u) + 20u, r_u16(0x80069A58u + 2u * r_u8(a1 + 212u)));
    capsule = sub_800474F4();
    w_u32(a1 + 64u, capsule);
    w_u16(capsule + 142u, 0u);
    w_u16(capsule + 138u, r_u8(a1 + 240u) - 1u);
    capsule = sub_800474F4();
    w_u32(a1 + 60u, capsule);
    w_u32(capsule + 124u, r_u32(a1 + 64u));
    w_u16(capsule + 140u, r_u8(a1 + 240u) - 1u);
    for (i = 0; i < sizeof(offsets) / sizeof(offsets[0]); ++i)
        sub_80047534(capsule, r_u32(r_u32(a1 + 52u)) + offsets[i], i < 2u ? 1u : 0u);
    w_u16(a1 + 18u, sub_8005129C((uint16)a2, 64u, a1));
    for (i = 0; i < sizeof(cleared_halfwords) / sizeof(cleared_halfwords[0]); ++i)
        w_u16(a1 + cleared_halfwords[i], 0u);
    w_u32(a1 + 266u, 0xFFFFu);
    w_u16(a1 + 264u, 4u);
    target = r_u32(r_u32(a1 + 52u));
    w_u32(target + 8u, r_u32(a1));
    w_u32(target + 12u, r_u32(a1 + 4u));
    w_u32(target + 16u, r_u32(a1 + 8u));
    w_u32(target + 20u, r_u32(a1 + 12u));
    w_u16(a1 + 204u, 0xFFFFu);
    w_u8(a1 + 230u, 1u);
    w_u32(a1 + 32u, 0u);
    w_u32(a1 + 44u, 0u);
    w_u8(a1 + 245u, 0u);
    w_u32(a1 + 68u, 0u);
    w_u32(a1 + 72u, 160u);
    w_u8(a1 + 244u, 0u);
    w_u32(a1 + 200u, 0u);
    w_u8(a1 + 281u, 0u);
    w_u8(a1 + 218u, 0u);
    sub_800528E8(a1, r_u16(a1 + 246u) | 0x8000u, 24u);
    type = r_u8(a1 + 212u);
    w_u8(a1 + 241u, 64u);
    w_u16(a1 + 284u, 0xFFFFu);
    w_u16(a1 + 76u, r_u16(0x80069A50u + 2u * type));
    w_u16(a1 + 98u, 0xFFFFu);
    w_u32(a1 + 80u, r_u32(r_u32(a1 + 52u) + 4u));
    sub_800513CC(a1, (uint32)(sint32)(sint16)a3);
    return sub_800234BC(r_u8(a1 + 240u) - 1u);
}

uint32 sub_8004B554(void)
{
    uint32 i;
    uint8 loaded[3] = {0};

    sub_80014F0C(17u, 0u, 1000u);
    for (i = 0; i < 28u; ++i)
        sub_80019BD4(i + 18u, i, 400u, 400u, 400u, 2u);
    sub_80019BD4(46u, 28u, 400u, 400u, 400u, 0u);
    sub_80019BD4(47u, 29u, 400u, 400u, 400u, 0u);
    sub_80019BD4(48u, 30u, 400u, 400u, 400u, 0u);
    for (i = 0; i < 4u; ++i)
        sub_80019BD4(49u + i, 31u + i, 400u, 400u, 400u, 1u);
    sub_80019BD4(53u, 35u, 400u, 400u, 400u, 2u);
    sub_80019648(35u, 100u, 100u, 100u);
    sub_80019BD4(54u, 36u, 300u, 300u, 300u, 2u);
    sub_80019648(36u, 100u, 100u, 100u);
    sub_80019BD4(55u, 37u, 300u, 300u, 300u, 0u);
    sub_80019BD4(56u, 38u, 600u, 600u, 600u, 2u);
    sub_80019BD4(57u, 39u, 300u, 300u, 300u, 1u);
    sub_80019648(39u, 800u, 200u, 800u);
    sub_80019BD4(58u, 40u, 600u, 600u, 600u, 1u);
    sub_80019648(40u, 200u, 200u, 200u);
    sub_8004B4F0();
    for (i = 0; i < 2u; ++i)
    {
        uint32 object = 0x800AFEC0u + 288u * i, type;
        if (!r_u8(object + 240u))
            continue;
        type = r_u8(object + 212u);
        /* TODO: Types beyond the local three-entry mask have unresolved effects */
        if (type >= 3u)
            abort();
        if (loaded[type])
            continue;
        if (type == 1u)
            sub_8004AD78();
        else if (type == 2u)
            sub_8004B164();
        else
            sub_8004A9E8();
        loaded[type] = 1u;
    }
    return 2u;
}

uint32 sub_80048BA8(uint32 a1)
{
    sint32 weight, reference = -1, base, factors[3];
    uint32 i, axis, result;
    if (r_u16(a1 + 18u))
    {
        uint32 value = (uint16)(r_u16(a1 + 16u) + r_u16(a1 + 18u));
        w_u16(a1 + 16u, value);
        if (value & 0x8000u)
        {
            w_u16(a1 + 16u, 0u);
            w_u16(a1 + 18u, 0u - r_u16(a1 + 18u));
        }
        if ((sint16)r_u16(a1 + 16u) >= 2040)
        {
            w_u16(a1 + 16u, 2040u);
            w_u16(a1 + 18u, 0u - r_u16(a1 + 18u));
        }
        weight = (sint16)r_u16(a1 + 16u) >> 3;
    }
    else
    {
        if (!(r_u16(0x800719D0u) & 3u))
            w_u16(a1 + 16u, (uint8)sub_80011B8C());
        weight = (sint16)r_u16(a1 + 16u);
    }
    if (r_u8(0x800AFFB0u))
        reference = (sint16)r_u16(0x800AFFCCu);
    if (r_u8(0x800B00D0u) && reference < (sint16)r_u16(0x800B00ECu))
        reference = (sint16)r_u16(0x800B00ECu);
    result = 0xFFFFu;
    if ((sint32)r_u16(a1 + 2u) < reference)
        w_u16(a1, 0xFFFFu);
    else
    {
        result = reference < (sint32)r_u16(a1);
        if (!result)
        {
            base = (sint16)r_u16(a1 + 4u);
            for (axis = 0; axis < 3u; ++axis)
                factors[axis] = (sint16)r_u16(a1 + 4u + 2u * axis) + (sint32)((uint32)((sint16)r_u16(a1 + 10u + 2u * axis) - base) * (uint32)weight) / 256;
            for (i = 0; i < 3u; ++i)
            {
                for (axis = 0; axis < 3u; ++axis)
                {
                    sint32 initial = (sint16)r_u16(0u - 2146673412u + 8u * i + 2u * axis);
                    uint32 destination = 0u - 2146699040u + 8u * i + 2u * axis;
                    w_u16(destination, (uint32)(initial / 4 + (sint32)((uint32)factors[axis] * (uint32)initial) / 128));
                    if ((sint16)r_u16(destination) >= 256)
                        w_u16(destination, 255u);
                }
            }
            result = 0u;
        }
    }
    return result;
}

void sub_80049180(void)
{
    static const uint32 values[7] = {0x80071564u, 0x800716DCu, 0x8007161Cu, 0x80071578u, 0x800716F0u, 0x8007162Cu, 0x800715ECu};
    static const uint32 targets[7] = {0x800719A0u, 0x800715D0u, 0x80071A4Cu, 0x800719ACu, 0x800715DCu, 0x80071A54u, 0x80071A2Cu};
    uint32 i;
    for (i = 0; i < 7u; ++i)
    {
        sint32 value = (sint16)r_u16(values[i]), target = (sint16)r_u16(targets[i]);
        if (i == 6u)
        {
            if (target < value)
            {
                w_u16(values[i], (uint32)(value - 1));
                w_u16(0x800717D0u, 1u);
            }
            value = (sint16)r_u16(values[i]);
            target = (sint16)r_u16(targets[i]);
            if (value < target)
            {
                w_u16(values[i], (uint32)(value + 1));
                w_u16(0x800717D0u, 1u);
            }
            continue;
        }
        if (value < target)
        {
            w_u16(values[i], (uint32)(value + 1));
            if (i >= 3u)
                w_u16(0x800717D0u, 1u);
        }
        value = (sint16)r_u16(values[i]);
        target = (sint16)r_u16(targets[i]);
        if (target < value)
        {
            w_u16(values[i], (uint32)(value - 1));
            if (i >= 3u)
                w_u16(0x800717D0u, 1u);
        }
        if (i == 2u)
        {
            draft_gte_control(21u, 16u * r_u16(values[0]));
            draft_gte_control(22u, 16u * r_u16(values[1]));
            draft_gte_control(23u, 16u * r_u16(values[2]));
        }
    }
    sub_8005CAC8(r_u16(0x80071964u), 512u);
}

uint32 sub_8001F44C(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10)
{
    uint16 count;
    uint32 size, data, positions, source, index;
    sub_8004E0A0((uint16)a1);
    sub_8004DD18(draft_local_address(&count, sizeof(count)), 2u);
    size = (uint16)(8u * count) | 2u;
    data = sub_80011A98(size);
    positions = sub_80011A98(8u * count);
    w_u16(data, count);
    source = r_u32(0x800B0120u + 56u * (uint16)a3);
    w_u32(0x80071570u + 4u * (uint16)a2, data);
    w_u32(0x80071694u + 4u * (uint16)a2, positions);
    if (size >= 3u)
        sub_8004DD18(data + 2u, size - 2u);
    sub_8004E20C();
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x1F800024u, 2048u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    sub_8005CF68(0x1F800000u);
    for (index = 0; index < count; ++index)
    {
        uint32 entry = data + 2u + 8u * index, original = source + 8u * r_u16(entry), x, y, z;
        w_u32(positions + 8u * index, r_u32(original));
        w_u32(positions + 8u * index + 4u, r_u32(original + 4u));
        w_u16(0x1F800020u, r_u16(entry + 2u));
        w_u16(0x1F800022u, r_u16(entry + 4u));
        w_u16(0x1F800024u, r_u16(entry + 6u));
        sub_8005CDA8(0x1F800020u, 0x1F800028u);
        /* TODO: Pseudo labels two effective scale arguments as 9 and 10 */
        x = a4 * r_u32(0x1F800028u);
        y = a9 * r_u32(0x1F80002Cu);
        z = a10 * r_u32(0x1F800030u);
        w_u32(0x1F800028u, x);
        w_u32(0x1F80002Cu, y);
        w_u32(0x1F800030u, z);
        x = (uint32)((sint32)x / 128);
        y = (uint32)((sint32)y / 128);
        z = (uint32)((sint32)z / 128);
        w_u32(0x1F800028u, x);
        w_u32(0x1F80002Cu, y);
        w_u32(0x1F800030u, z);
        w_u16(entry + 2u, 0u - x);
        w_u16(entry + 4u, y);
        w_u16(entry + 6u, z);
    }
    return 0u;
}

uint32 sub_8004E73C(void)
{
    uint32 list = r_u32(0x80071A3Cu), i;
    sint32 old_x, old_y, height = (sint16)r_u16(0x80071798u);
    uint32 count = r_u16(0x800717C0u);
    if (height == 64 && !count)
        return 0u;
    ReadGeomOffset(&old_x, &old_y);
    sub_8005D108(320u, (uint32)height + 220u);
    w_u32(0x1F800028u, 0u);
    w_u32(0x1F80002Cu, 0u);
    w_u32(0x1F800030u, 2720u);
    draft_gte_control(5u, 0u);
    draft_gte_control(6u, 0u);
    draft_gte_control(7u, 2720u);
    w_u16(0x1F800020u, (r_u16(0x800BBFD4u) & 0xFFFu) - 640u);
    if ((sint16)r_u16(0x1F800020u) < -639)
        w_u16(0x1F800020u, (uint32)-640);
    w_u16(0x1F800020u, 0u);
    for (i = 0; (uint16)i < r_u16(0x800717C0u); ++i)
    {
        uint32 entry = list + 16u * i, dx = r_u32(entry) - r_u32(0x800BC0A4u), dz = r_u32(entry + 8u) - r_u32(0x800BC0ACu), angle, j;
        uint32 distance = sub_8001F8A8(dx, dz);
        angle = sub_80046B84(dx, dz, distance);
        w_u16(0x1F800022u, 0u);
        w_u16(0x1F800024u, (angle - 4096u + r_u16(0x800BBFD6u)) & 0xFFFu);
        sub_8005D138(0x1F800020u, 0x1F800000u);
        for (j = 0; j < 5u; ++j)
            draft_gte_control(j, r_u32(0x1F800000u + 4u * j));
        sub_8004E570(r_u16(entry + 4u));
    }
    height = (sint16)r_u16(0x80071798u);
    if (r_u16(0x800717C0u))
    {
        if (height)
            w_u16(0x80071798u, (uint32)(height - 8));
    }
    else if (height < 64)
        w_u16(0x80071798u, (uint32)(height + 8));
    sub_8005D108(old_x, old_y);
    height = (sint16)r_u16(0x80071798u);
    sub_80018214(306u, (uint32)height + 204u, 1u, 163u, (uint32)(sint32)(sint16)(128 - 2 * height), (uint32)(sint32)(sint16)(128 - 2 * height), (uint32)(sint32)(sint16)(128 - 2 * height), 1u);
    return sub_800180D4(320u, (uint32)height + 220u, 3u, 162u, (uint32)(sint32)(sint16)(128 - 2 * height), (uint32)(sint32)(sint16)(128 - 2 * height), (uint32)(sint32)(sint16)(128 - 2 * height));
}

uint32 sub_80044A5C(uint32 a1)
{
    uint32 i;
    a1 = (uint16)a1;
    for (i = 0; i < 24u; ++i)
    {
        uint32 entry = 0u - 2146766808u + 12u * i, kind = r_u16(entry), voice;
        if (kind < 1u || kind > 4u)
            continue;
        voice = 1u << (r_u16(entry + 2u) & 31u);
        if (kind == 1u)
        {
            uint32 index = r_u16(entry + 4u);
            w_u32(0x800C9E04u, 65683u);
            w_u32(0x800C9E00u, voice);
            w_u16(0x800C9E14u, r_u16(entry + 6u));
            w_u32(0x800C9E1Cu, r_u32(0u - 2146767144u + 4u * index));
            w_u32(0x800C9E20u, r_u32(0x800BED30u + 4u * index));
            sub_800449B8(r_u16(entry + 8u), r_u16(entry + 10u));
            sub_80062368(0x800C9E00u);
        }
        else if (kind == 2u)
        {
            w_u32(0x800C9E04u, 3u);
            w_u32(0x800C9E00u, voice);
            sub_800449B8(r_u16(entry + 8u), r_u16(entry + 10u));
            sub_800628B8(0x800C9E00u);
        }
        else if (kind == 3u)
        {
            w_u32(0x800C9E04u, 16u);
            w_u32(0x800C9E00u, voice);
            w_u16(0x800C9E14u, r_u16(entry + 6u));
            sub_800628B8(0x800C9E00u);
        }
        else
            sub_800621A8(0u, voice);
        if (a1)
        {
            uint32 delay;
            for (delay = 0; delay < a1; ++delay)
                sub_80044A40();
        }
        w_u16(entry, 0u);
    }
    return 0u;
}

uint32 sub_80012330(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    uint32 output = sub_80011A98(7680u), i;
    PSX_RECT rectangle;
    for (i = 0; (uint16)i < r_u16(0x800716B4u); ++i)
    {
        uint32 image = r_u16(0x800AF1F4u + 2u * (uint16)i), x, y, base, source, destination, count;
        sub_80011DC0(r_u16(0x800C0224u + 2u * (uint16)i), draft_local_address(&x, sizeof(x)), draft_local_address(&y, sizeof(y)));
        y -= 502u;
        base = r_u32(0x800715ACu);
        if (r_u8(0x800BF4ECu + (uint16)i))
        {
            source = base + (image << 9) + 32u * r_u16(base) + 4u;
            count = 256u;
        }
        else
        {
            source = base + 32u * image + 4u;
            count = 16u;
        }
        destination = output + 2u * (384u * y + x);
        if (r_u8(0x800BF7F0u + (uint16)i))
            sub_800122F4(source, destination, count);
        else
        {
            /* TODO: Preserve real stack color arguments 5, 6 and pixel count 7 despite extra pseudo carriers */
            sub_800121A4(source, destination, a1, (uint32)(sint32)(sint16)a2, (uint32)(sint32)(sint16)a3, (uint32)(sint32)(sint16)a4, count);
        }
    }
    rectangle.x = 0;
    rectangle.y = 502;
    rectangle.w = 384;
    rectangle.h = 10;
    LoadImagePSX(&rectangle, (uint32 *)psx_addr(output, 1u));
    DrawSync(0);
    return sub_80011AF8(output);
}

uint32 sub_800206D8(void)
{
    uint32 column, row;
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x800BBFD4u, r_u16(0x800BBFD4u) & 0xFFFu);
    w_u16(0x800BBFD6u, r_u16(0x800BBFD6u) & 0xFFFu);
    w_u16(0x800BBFD8u, r_u16(0x800BBFD8u) & 0xFFFu);
    w_u16(0x1F800024u, r_u16(0x800BBFD8u));
    sub_8005D138(0x1F800020u, 0x800BBFDCu);
    w_u16(0x1F800024u, 0u);
    w_u16(0x1F800020u, r_u16(0x800BBFD4u));
    w_u16(0x1F800022u, r_u16(0x800BBFD6u));
    sub_8005D138(0x1F800020u, 0x1F800000u);
    for (row = 0; row < 5u; ++row)
        draft_gte_control(row, r_u32(0x800BBFDCu + 4u * row));
    for (column = 0; column < 3u; ++column)
    {
        for (row = 0; row < 3u; ++row)
            draft_gte_data(9u + row, (uint32)(sint32)(sint16)r_u16(0x1F800000u + 6u * row + 2u * column));
        draft_gte_command(0x49E012u);
        for (row = 0; row < 3u; ++row)
            w_u16(0x800BBFDCu + 6u * row + 2u * column, draft_gte_read(9u + row));
    }
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800024u, 0u);
    w_u16(0x800BBFD6u, r_u16(0x800BBFD6u) & 0xFFFu);
    w_u16(0x1F800022u, r_u16(0x800BBFD6u));
    return sub_8005D138(0x1F800020u, 0x800AFE80u);
}

uint32 sub_80014378(void)
{
    uint32 old_position = 0u, offset = 0u, index, count, table;
    uint16 type, length;
    sub_8004E0A0(795u);
    sub_8004DD18(0x800719C0u, 2u);
    count = r_u16(0x800719C0u);
    table = sub_80011A98(4u * count);
    w_u32(0x80071650u, table);
    sub_8004DD18(table, 4u * r_u16(0x800719C0u));
    sub_8004E20C();
    table = sub_80011A98(4u * r_u16(0x800719C0u));
    w_u32(0x80071970u, table);
    sub_8004E0A0(795u);
    for (index = 0; (uint16)index < r_u16(0x800719C0u); ++index)
    {
        uint32 entry = 4u * (uint16)index, position = entry + r_u32(r_u32(0x80071650u) + entry) + 6u;
        sub_8004DE84(position - old_position);
        sub_8004DD18(draft_local_address(&type, sizeof(type)), 2u);
        old_position = position + 2u;
        w_u32(r_u32(0x80071650u) + entry, offset);
        if (type < 2u)
        {
            uint32 allocation;
            sub_8004DD18(draft_local_address(&length, sizeof(length)), 2u);
            allocation = sub_80011A98(2u * length + 4u);
            w_u16(allocation, type);
            w_u16(allocation + 2u, length);
            sub_8004DD18(allocation + 4u, 2u * length);
            old_position += 2u + 2u * length;
            w_u32(r_u32(0x80071970u) + entry, allocation);
            offset += type ? 0x10000u : 0x8000u;
        }
        else if (type < 4u)
        {
            uint32 allocation = sub_80011A98(2u);
            w_u16(allocation, type);
            w_u32(r_u32(0x80071970u) + entry, allocation);
            if (type == 2u)
                offset += 0x20000u;
        }
        sub_8004E20C();
    }
    return 0u;
}

uint32 sub_80057F3C(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6)
{
    uint32 vector = a5, state = a6, result, old_x, old_z, new_x, new_z;
    sint32 difference, product, quotient;
    /* TODO: MIPS uses arguments 5 and 6 where pseudocode labels them 9 and 10 */
    if (!a3)
        return draft_unknown_return("sub_80057F3C BREAK 7");
    difference = (sint16)r_u16(a2 + 2u) - (sint16)r_u16(a1 + 2u);
    product = (sint32)(a4 * (uint32)difference);
    if (a3 == 0xFFFFFFFFu && product == (sint32)0x80000000u)
        return draft_unknown_return("sub_80057F3C BREAK 6");
    quotient = product / (sint32)a3;
    w_u32(0x1F80002Cu, (uint32)quotient);
    w_u16(vector + 2u, 0u - (r_u16(a1 + 2u) + r_u16(0x1F80002Cu)));
    difference = (sint16)r_u16(a2) - (sint16)r_u16(a1);
    product = (sint32)(a4 * (uint32)difference);
    if (a3 == 0xFFFFFFFFu && product == (sint32)0x80000000u)
        return draft_unknown_return("sub_80057F3C BREAK 6");
    w_u32(0x1F800028u, (uint32)(product / (sint32)a3));
    difference = (sint16)r_u16(a2 + 4u) - (sint16)r_u16(a1 + 4u);
    product = (sint32)(a4 * (uint32)difference);
    if (a3 == 0xFFFFFFFFu && product == (sint32)0x80000000u)
        return draft_unknown_return("sub_80057F3C BREAK 6");
    w_u32(0x1F800030u, (uint32)(product / (sint32)a3));
    old_x = r_u16(state + 8u);
    new_x = r_u16(0x1F800028u) + r_u16(a1);
    w_u16(state + 8u, new_x);
    w_u16(state + 12u, new_x);
    old_z = r_u16(state + 10u);
    new_z = r_u16(0x1F800030u) + r_u16(a1 + 4u);
    w_u16(state + 10u, new_z);
    w_u16(state + 14u, new_z);
    w_u16(state + 12u, r_u16(state + 12u) - old_x);
    result = r_u16(state + 14u) - old_z;
    w_u16(state + 14u, result);
    if (r_u8(state + 21u))
    {
        w_u16(vector, 0u);
        w_u16(vector + 4u, 0u);
    }
    else
    {
        w_u16(vector, r_u16(0x1F800028u) + r_u16(a1));
        result = r_u16(0x1F800030u) + r_u16(a1 + 4u);
        w_u16(vector + 4u, result);
        w_u16(state + 12u, 0u);
        w_u16(state + 14u, 0u);
    }
    return result;
}
