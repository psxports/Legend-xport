#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern uint32 sub_800203EC(uint32 x, uint32 angle, uint32 z, uint32 other);
extern uint32 sub_80020414(uint32 a, uint32 b, uint32 c, uint32 d);
extern uint32 sub_8002030C(uint32 target);
extern uint32 sub_8002095C(uint32 value, uint32 target);
extern uint32 sub_8005CBB8(uint32 squared);
extern uint32 sub_8005D138(uint32 vector, uint32 matrix);
extern uint32 sub_8005CDD8(uint32 matrix, uint32 vector, uint32 result);
extern uint32 sub_8005B278(uint32 count);
extern uint32 sub_80066D68(void);
extern uint32 sub_8005E290(uint32 rectangle, uint32 source);
extern uint32 sub_80067AE8(uint32 buffer, uint32 sectors);

void sub_80020DD8(void)
{
    uint32 script = r_u32(0x800BC094u), a, b, c, d;
    if (!script)
        return;
    for (;;)
    {
        switch (r_u32(script))
        {
            case 0:
                a = r_u32(script + 4u);
                b = r_u16(script + 8u);
                c = r_u32(script + 12u);
                d = r_u16(script + 16u);
                script += 20u;
                sub_800203EC(a, b, c, d);
                w_u16(0x800BC060u, 0);
                break;
            case 1:
                a = r_u16(script + 4u);
                b = r_u16(script + 8u);
                c = r_u16(script + 12u);
                d = r_u16(script + 16u);
                script += 20u;
                sub_80020414(a, b, c, d);
                w_u16(0x800BC060u, 0);
                break;
            case 2:
                if (!r_u16(0x800BC060u))
                    return;
                script += 4u;
                break;
            case 3:
                w_u32(0x800BC094u, 0);
                return;
            case 4:
                a = r_u32(script + 4u);
                b = r_u32(script + 8u);
                c = r_u32(script + 12u);
                script += 16u;
                sub_8002043C(a, b, c);
                break;
            case 5:
                a = r_u32(script + 4u);
                b = r_u32(script + 8u);
                c = r_u32(script + 12u);
                script += 16u;
                sub_8002046C(a, b, c);
                break;
            case 6:
                a = r_u32(script + 4u);
                b = r_u16(script + 8u);
                script += 12u;
                w_u16(a, b);
                break;
            case 7:
                if (r_u32(script + 4u) == 1u)
                {
                    if (!r_u16(0x800BC03Eu))
                    {
                        w_u32(0x800BC030u, r_u32(0x800BC02Cu));
                        sub_8002030C(0);
                    }
                    w_u16(0x800BC03Eu, 1);
                }
                else
                {
                    if (r_u16(0x800BC03Eu))
                        sub_8002030C(r_u32(0x800BC030u));
                    w_u16(0x800BC03Eu, 0);
                }
                script += 8u;
                break;
            case 8:
                w_u32(0x800BC094u, script + 4u);
                return;
            default:
                /* TODO: Unknown command repeats without advancing the script */
                break;
        }
        w_u32(0x800BC094u, script);
    }
}

uint32 sub_80020B54(void)
{
    uint32 old_x = r_u32(0x800BBFC4u), old_y = r_u32(0x800BBFC8u), old_z = r_u32(0x800BBFCCu);
    uint32 target = r_u32(0x800BC02Cu), result;
    w_u16(0x800BC060u, 1);
    if (target)
    {
        w_u32(0x800BC01Cu, sub_8002095C(r_u32(0x800BC01Cu), r_u32(0x800BC040u)));
        w_u32(0x800BC020u, sub_8002095C(r_u32(0x800BC020u), r_u32(0x800BC044u)));
        w_u32(0x800BC024u, sub_8002095C(r_u32(0x800BC024u), r_u32(0x800BC048u)));
        w_u32(0x800BBFC4u, r_u32(target + 8u) + r_u32(0x800BC01Cu));
        w_u32(0x800BBFC8u, r_u32(target + 12u) + r_u32(0x800BC020u));
        w_u32(0x800BBFCCu, r_u32(target + 16u) + r_u32(0x800BC024u));
    }
    else
    {
        w_u32(0x800BBFC4u, sub_800209E4(r_u32(0x800BBFC4u), r_u32(0x800BC040u), 0x800BC06Cu));
        w_u32(0x800BBFC8u, sub_800209E4(r_u32(0x800BBFC8u), r_u32(0x800BC044u), 0x800BC070u));
        w_u32(0x800BBFCCu, sub_800209E4(r_u32(0x800BBFCCu), r_u32(0x800BC048u), 0x800BC074u));
    }
    w_u32(0x800BC050u, r_u32(0x800BBFC4u) - old_x);
    result = r_u32(0x800BBFC8u) - old_y;
    w_u32(0x800BC054u, result);
    w_u32(0x800BC058u, r_u32(0x800BBFCCu) - old_z);
    return result;
}

uint32 sub_800529F4(void)
{
    uint32 i, j, object, active, kind, saved, result = 1;
    for (i = 0; i < 2u; ++i)
    {
        object = 0x800AFEC0u + 288u * i;
        active = r_u8(object + 240u);
        kind = r_u8(object + 212u);
        saved = r_u16(object + 246u);
        sub_8002F0D4(object, 288u);
        w_u8(object + 240u, active);
        w_u8(object + 212u, kind);
        w_u16(object + 246u, saved);
        w_u32(0x80071788u + 4u * i, 0);
        w_u8(0x80071768u + i, 0);
        w_u32(0x800715F4u + 4u * i, 0);
        w_u16(0x80071A44u + 2u * i, 0);
        w_u16(object + 208u, 5);
        w_u16(object + 210u, 72);
        for (j = 0; j < 6u; ++j)
            w_u8(object + 250u + j, 48);
        w_u8(object + 280u, 3);
        w_u16(object + 248u, 0);
        w_u8(object + 231u, 0);
    }
    w_u16(0x80071918u, 1);
    if (r_u8(0x800AFFB0u))
    {
        result = 2;
        if (r_u8(0x800B00D0u))
            w_u16(0x80071918u, 2);
    }
    return result;
}

uint32 sub_8001FB5C(uint32 a1)
{
    uint32 y = r_u32(a1 + 68u), z = r_u32(a1 + 72u), ay = y, az = z, root, quotient, angle, result;
    if ((sint32)ay < 0)
        ay = 0u - ay;
    if ((sint32)az < 0)
        az = 0u - az;
    while ((sint32)ay >= 2049 || (sint32)az >= 2049)
    {
        ay = (uint32)((sint32)ay >> 1);
        az = (uint32)((sint32)az >> 1);
    }
    root = sub_8005CBB8(ay * ay + az * az);
    result = (sint32)ay < (sint32)az;
    if (!root)
        return result;
    quotient = (result ? ay : az) << 10;
    /* TODO: Preserve original BREAK handling for signed division overflow */
    if (root == 0xFFFFFFFFu && quotient == 0x80000000u)
        quotient = draft_unknown_argument("sub_8001FB5C", 0);
    else
        quotient = (uint32)((sint32)quotient / (sint32)root);
    angle = r_u16((result ? 0x800BC9C0u : 0x800BC1B4u) + ((sint32)quotient >= 1024 ? 2046u : 2u * quotient));
    if ((sint32)y >= 0)
    {
        result = 2048;
        if ((sint32)z <= 0)
            angle = result - angle;
    }
    else
    {
        result = 4095;
        if ((sint32)z <= 0)
            angle += 2048u;
        else
            angle = result - angle;
    }
    w_u16(0x800BBFD4u, angle);
    return result;
}

uint32 sub_80051D38(uint32 a1, uint32 a2)
{
    uint32 other = 0x800AFEC0u + 288u * ((uint16)a2 ^ 1u), result = r_u8(other + 240u);
    uint32 x, z, dx, dz, distance, angle;
    if (!result)
        return result;
    x = r_u32(a1) + r_u32(other);
    z = r_u32(a1 + 8u) + r_u32(other + 8u);
    x = (uint32)((sint32)x / 2);
    z = (uint32)((sint32)z / 2);
    dx = r_u32(a1) - x;
    dz = r_u32(a1 + 8u) - z;
    distance = sub_8001F8A8(dx, dz);
    result = (sint32)distance < 3501;
    if (!result)
    {
        angle = sub_80046B84(r_u32(a1) - x, r_u32(a1 + 8u) - z, distance);
        w_u16(0x1F800020u, 0);
        w_u16(0x1F800022u, angle & 4095u);
        w_u16(0x1F800024u, 0);
        sub_8005D138(0x1F800020u, 0x1F800000u);
        w_u16(0x1F800020u, 0);
        w_u16(0x1F800022u, 0);
        w_u16(0x1F800024u, 3500);
        sub_8005CDD8(0x1F800000u, 0x1F800020u, 0x1F800028u);
        w_u32(a1, x + r_u32(0x1F800028u));
        result = z + r_u32(0x1F800030u);
        w_u32(a1 + 8u, result);
    }
    return result;
}

uint32 sub_80045048(uint32 a1)
{
    uint32 value, changed, result;
    sint16 delta;
    a1 = (uint16)a1;
    do
    {
        changed = 0;
        delta = (sint16)r_u16(0x800716D8u);
        if (delta)
        {
            value = r_u32(0x800718C8u) + (uint32)(sint32)delta;
            w_u32(0x800718C8u, value);
            changed = 1;
            if ((sint32)value <= 0)
            {
                w_u32(0x800718C8u, 0);
                w_u16(0x800716D8u, 0);
            }
            if ((sint32)r_u32(0x800718C8u) >= 256)
            {
                w_u32(0x800718C8u, 256);
                w_u16(0x800716D8u, 0);
            }
        }
        delta = (sint16)r_u16(0x8007192Cu);
        if (delta)
        {
            value = r_u32(0x800715B8u) + (uint32)(sint32)delta;
            w_u32(0x800715B8u, value);
            changed = 1;
            if ((sint32)value <= 0)
            {
                w_u32(0x800715B8u, 0);
                w_u16(0x8007192Cu, 0);
            }
            if ((sint32)r_u32(0x800715B8u) >= 256)
            {
                w_u32(0x800715B8u, 256);
                w_u16(0x8007192Cu, 0);
            }
        }
        result = changed;
        if (changed)
            result = sub_80044FB0();
        if (!a1)
            break;
        sub_800140DC();
        sub_8005B278(a1);
        result = a1;
        if (!r_u16(0x8007192Cu) && !r_u16(0x800716D8u))
            result = a1 = 0;
    } while (result);
    return result;
}

uint32 sub_800209E4(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 maximum = r_u32(0x800BC064u), divisor = r_u32(0x800BC068u), difference = a2 - a1;
    uint32 acceleration = (uint32)((sint32)maximum / 24), step, speed, result, magnitude;
    if (!acceleration)
        acceleration = 1;
    /* TODO: Original BREAK on division by zero or signed overflow */
    if (!divisor || (divisor == 0xFFFFFFFFu && difference == 0x80000000u))
        step = draft_unknown_argument("sub_800209E4", 0);
    else
        step = (uint32)((sint32)difference / (sint32)divisor);
    if (!step)
        step = difference;
    if ((sint32)step < (sint32)(0u - maximum))
        step = 0u - maximum;
    if ((sint32)step > (sint32)maximum)
        step = maximum;
    magnitude = (sint32)step < 0 ? 0u - step : step;
    speed = r_u32(a3);
    if ((sint32)speed >= (sint32)magnitude)
        w_u32(a3, magnitude);
    else
    {
        speed += acceleration;
        w_u32(a3, speed);
        if ((sint32)maximum < (sint32)speed)
            w_u32(a3, maximum);
        if ((sint32)magnitude < (sint32)r_u32(a3))
            w_u32(a3, magnitude);
        step = (sint32)step < 0 ? 0u - r_u32(a3) : r_u32(a3);
    }
    result = a1 + step;
    if (result != a2)
        w_u16(0x800BC060u, 0);
    return result;
}

uint32 sub_80059EE4(void)
{
    uint32 index, frame, limit, sectors;
    if (r_u16(0x80071A58u) && r_u32(0x800BF5DCu))
    {
        sub_80066D68();
        w_u32(0x800BF5DCu, 0);
    }
    index = (uint32)((sint32)(r_u16(0x80071A90u) << 16) >> 14);
    sub_8005E290(0x80071A80u, r_u32(0x80071A9Cu + index));
    w_u16(0x80071A90u, r_u16(0x80071A90u) ^ 1u);
    w_u16(0x80071A80u, r_u16(0x80071A80u) + r_u16(0x80071A84u));
    frame = r_u16(0x80071A80u);
    index = (uint32)((sint32)(r_u16(0x80071A8Cu) << 16) >> 13);
    limit = (uint32)((sint16)r_u16(0x80071A70u + index) + (sint16)r_u16(0x80071A74u + index));
    if ((sint16)frame >= (sint32)limit)
    {
        w_u16(0x80071A8Au, 1);
        return 1;
    }
    sectors = sub_8005A730();
    index = (uint32)((sint32)(r_u16(0x80071A90u) << 16) >> 14);
    return sub_80067AE8(r_u32(0x80071A9Cu + index), sectors);
}

uint32 sub_80020124(void)
{
    static const uint32 full[] = {0x800BC064u, 0x800BC074u, 0x800BC070u, 0x800BC06Cu, 0x800BC07Cu, 0x800BC08Cu, 0x800BC088u, 0x800BC084u};
    static const uint32 zero[] = {0x800BBFC8u, 0x800BBFCCu, 0x800BC02Cu, 0x800BC098u, 0x800BC0B4u, 0x800BC0B8u, 0x800BC0BCu, 0x800BC0A4u, 0x800BC0A8u, 0x800BC0ACu, 0x800BC040u, 0x800BC044u, 0x800BC048u, 0x800BC050u, 0x800BC054u, 0x800BC058u, 0x800BC094u};
    uint32 i;
    sub_8002F0D4(0x800BBFC4u, 268u);
    w_u32(0x800BBFC4u, 0);
    w_u16(0x800BC062u, 1);
    for (i = 0; i < sizeof(full) / sizeof(full[0]); ++i)
        w_u32(full[i], 256);
    for (i = 0; i < sizeof(zero) / sizeof(zero[0]); ++i)
        w_u32(zero[i], 0);
    w_u16(0x800BBFD4u, 0);
    w_u16(0x800BBFD6u, 0);
    w_u16(0x800BBFD8u, 0);
    w_u16(0x800BC0C6u, 0);
    w_u16(0x800BC060u, 0);
    w_u32(0x800BC068u, 3);
    w_u32(0x800BC080u, 3);
    w_u16(0x800BC03Eu, 0);
    w_u16(0x800BC0CCu, 0xFFFFu);
    return 0xFFFFu;
}

uint32 sub_80012DD4(void)
{
    uint32 candidate, index, count, j;
    if (!r_u8(0x8007154Cu))
        return 0;
    for (candidate = 0; candidate < r_u8(0x8007154Cu); ++candidate)
    {
        count = r_u16(0x80071600u);
        for (index = 0; index < count; ++index)
        {
            if (r_u8(0x800C04F4u + index) != r_u8(0x800BD21Cu + candidate))
            {
                count = r_u16(0x80071600u);
                continue;
            }
            for (j = index; j < r_u16(0x80071600u) - 1u; ++j)
            {
                w_u8(0x800C04F4u + j, r_u8(0x800C04F5u + j));
                w_u16(0x800AF684u + 2u * j, r_u16(0x800AF686u + 2u * j));
                w_u8(0x800C020Cu + j, r_u8(0x800C020Du + j));
                w_u16(0x800AEE74u + 2u * j, r_u16(0x800AEE76u + 2u * j));
            }
            w_u16(0x80071600u, r_u16(0x80071600u) - 1u);
            return 1;
        }
    }
    return 0;
}

uint32 sub_80030C38(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 position[4], difference_x, difference_z, i, product;
    sint16 local[4];
    local[0] = -1;
    position[0] = (uint32)((sint32)(r_u32(a1) + r_u32(a2)) >> 1);
    position[2] = (uint32)((sint32)(r_u32(a1 + 4u) + r_u32(a2 + 4u)) >> 1);
    position[1] = sub_80046324(position[0], position[2], draft_local_address(local, sizeof(local)));
    difference_x = r_u32(a2) - r_u32(a1);
    difference_z = r_u32(a2 + 4u) - r_u32(a1 + 4u);
    for (i = 1; i <= 4u; ++i)
    {
        product = i * difference_x;
        position[0] = (uint32)((sint32)product / 5) + r_u32(a1);
        product = i * difference_z;
        position[2] = (uint32)((sint32)product / 5) + r_u32(a1 + 4u);
        sub_80016738(draft_local_address(position, sizeof(position)), (r_u16(0x800719D0u) & 7u) + 234u, 0x4000, a3 << 5, 0, 128);
    }
    return 0;
}

uint32 sub_800542D4(uint32 a1)
{
    uint32 ticks = r_u16(0x800719D0u), value, root;
    if (!(ticks & 7u) && r_u16(0x8007176Cu))
        w_u16(0x8007176Cu, r_u16(0x8007176Cu) - 1u);
    if (!(r_u16(0x800719D0u) & 1u) && r_u16(0x8007182Cu))
        w_u16(0x8007182Cu, r_u16(0x8007182Cu) - 1u);
    root = r_u32(r_u32(a1 + 52u));
    value = r_u16(0x8007176Cu) + (uint32)((sint32)(r_u32(root + 180u) - r_u32(0x8007180Cu)) >> 2);
    w_u16(0x8007176Cu, value);
    if (value & 0x8000u)
        w_u16(0x8007176Cu, 0);
    if ((sint16)r_u16(0x8007176Cu) >= 129)
        w_u16(0x8007176Cu, 128);
    root = r_u32(r_u32(a1 + 52u));
    value = r_u16(0x8007182Cu) + (uint32)((sint32)(r_u32(root + 180u) - r_u32(0x800718B4u)) >> 2);
    w_u16(0x8007182Cu, value);
    if (value & 0x8000u)
        w_u16(0x8007182Cu, 0);
    if ((sint16)r_u16(0x8007182Cu) >= 129)
        w_u16(0x8007182Cu, 128);
    sub_8001F700(0, 67, (uint32)(sint32)(sint16)r_u16(0x8007176Cu));
    return sub_8001F700(1, 69, (uint32)(sint32)(sint16)r_u16(0x8007182Cu));
}
