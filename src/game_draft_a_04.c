#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdint.h>
#include <stdlib.h>

/* Unverified draft; integration deferred */
/* TODO: Missing SDK and external adapters require fail-fast during integration */
extern uint32 sub_80022B24();
extern uint32 sub_80022CC0();
extern uint32 sub_80023500();
extern uint32 sub_80029DD4();
extern uint32 sub_8002AFE8();
extern uint32 sub_80031224();
extern uint32 sub_80031308();
extern uint32 sub_8003133C();
extern uint32 sub_80032FD0();

extern uint32 sub_80040D64();
extern uint32 sub_800410B8();
extern uint32 sub_800449A0();
extern uint32 sub_80044F58();
extern uint32 sub_8004EB88();
extern uint32 sub_80050A08();
extern uint32 sub_80051550();
extern uint32 sub_800516E8();
extern uint32 sub_80052078();
extern uint32 sub_80052228();
extern uint32 sub_800522D0();
extern uint32 sub_800524AC();
extern uint32 sub_80053774();
extern uint32 sub_80053A28();
extern uint32 sub_800540C0();
extern uint32 sub_80054184();
extern uint32 sub_80054414();
extern uint32 sub_8005B278();
extern uint32 sub_8005CC48();
extern uint32 sub_8005CDA8();
extern uint32 sub_8005CDD8();
extern void sub_8005CF98();
extern uint32 sub_8005D138();
extern uint32 sub_8005D3C8();
extern uint32 sub_8005D658(uint32 rotation, uint32 matrix);
extern uint32 sub_8005DFE4();
extern uint32 sub_8005E290();
extern uint32 sub_8005E814();
extern uint32 sub_8005EEB8();
extern uint32 sub_80060DB8();
extern uint32 sub_80063C94();
extern uint32 sub_80065768();
extern uint32 sub_80067A6C();
extern uint32 sub_80067AE8();

uint32 sub_80034890(uint32 a1)
{
    FUNCTION_MARKER(0x80034890u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 result;
    uint32 v2;
    uint32 v3;
    sint32 v4;
    sint32 v5;
    sint32 v6;
    sint32 v7;
    uint32 v8;
    uint32 v9;
    uint32 v10;
    sint32 v11;
    uint32 v12;

    result = r_u16((uint32)(0x80071808u));
    v2 = (uint32)(a1 + 12);
    if (!r_u16((uint32)(0x80071808u)))
        return result;
    result = (sint16)r_u16((uint32)((a1 + 16))) < 10;
    if ((sint16)r_u16((uint32)((a1 + 16))) >= 10)
        return result;
    v3 = 8000;
    if (r_u8((uint32)(0x800AFFB0u)))
    {
        v3 = r_u16((uint32)(0x800AFFCCu));
        if (r_u8((uint32)(0x800B00D0u)))
            v3 = (r_u16((uint32)(0x800AFFCCu)) + r_u16((uint32)(0x800B00ECu)) + ((uint32)(r_u16((uint32)(0x800AFFCCu)) + r_u16((uint32)(0x800B00ECu))) >> 31)) >> 1;
        goto LABEL_8;
    }
    v4 = 524288000;
    if (r_u8((uint32)(0x800B00D0u)))
    {
        v3 = r_u16((uint32)(0x800B00ECu));
    LABEL_8:
        v4 = v3 << 16;
    }
    v5 = v4 >> 16;
    result = 8000;
    if (v5 != 8000)
    {
        v6 = r_u16((uint32)(v2));
        result = v5 < v6;
        if (v5 >= v6)
        {
            v7 = r_u16((uint32)(v2 + 2u * (1)));
            result = v7 < v5;
            if (v7 >= v5)
            {
                v8 = v3 - 8;
                if ((sint16)(v3 - 8) < v6)
                    v8 = r_u16((uint32)(v2));
                v9 = v3 + 8;
                if (v7 < (sint16)(v3 + 8))
                    v9 = r_u16((uint32)(v2 + 2u * (1)));
                v10 = v8 + (sub_80011B8C() & 0x7F) * (sint16)(v9 - v8) / 128;
                v11 = (sint16)v9 < (sint16)v10;
                v12 = v10 << 16;
                if (v11)
                    v12 = v9 << 16;
                return sub_80023500((uint16)((uint32)(v12) >> 16), v2 + 2);
            }
        }
    }
    return result;
}

uint32 sub_8004F06C(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x8004F06Cu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    uint32 v3;
    sint32 v5;
    sint32 v6;
    sint8 v7;
    sint16 v8;
    sint32 v9;
    sint32 v10;

    v3 = a1;
    sub_80017FB0(a2, 232 - a1, 1, 159);
    v5 = a2 << 16;
    if (v3)
    {
        v6 = r_u32((uint32)(0x80071680u));
        w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (40));
        w_u8((uint32)((v6 + 3)), 5);
        w_u8((uint32)((v6 + 7)), 40);
        if (v3 >= 0x10)
        {
            w_u16((uint32)((v6 + 4)), 255);
        }
        else
        {
            w_u8((uint32)((v6 + 4)), 0);
            w_u8((uint32)((v6 + 5)), -1);
        }
        w_u8((uint32)((v6 + 6)), 0);
        if (a1 == 64)
        {
            v7 = -1;
            if ((r_u16((uint32)(0x800719D0u)) & 7u) < 4)
            {
                w_u8((uint32)((v6 + 4)), -1);
            }
            else
            {
                w_u8((uint32)((v6 + 4)), -1);
                v7 = 0x80;
            }
            w_u8((uint32)((v6 + 5)), v7);
            w_u8((uint32)((v6 + 6)), 0);
        }
        v8 = 234 - (a1 + 1);
        w_u16((uint32)((v6 + 8)), a2 - 1);
        w_u16((uint32)((v6 + 16)), a2 - 1);
        v9 = r_u32((uint32)(0x8007184Cu));
        w_u16((uint32)((v6 + 10)), v8);
        w_u16((uint32)((v6 + 14)), v8);
        w_u16((uint32)((v6 + 12)), a2 + 2);
        w_u16((uint32)((v6 + 20)), a2 + 2);
        v10 = r_u32((uint32)(v6));
        w_u16((uint32)((v6 + 18)), 233);
        w_u16((uint32)((v6 + 22)), 233);
        w_u32((uint32)(v6), v10 & 0xFF000000 | r_u32((uint32)((v9 + 4))) & 0xFFFFFF);
        w_u32((uint32)((v9 + 4)), r_u32((uint32)((v9 + 4))) & 0xFF000000 | v6 & 0xFFFFFF);
        v5 = a2 << 16;
    }
    return sub_80017FB0((sint16)((uint32)(v5) >> 16), 234, 1, 156);
}

uint32 sub_8004BD40(void)
{
    FUNCTION_MARKER(0x8004BD40u, "SLES_007.30");
    uint32 result;
    if (r_u16(0x80071888u) == 1u)
    {
        if (r_u16(0x8007194Cu) != 0u)
            return 16u;
        w_u16(0x800717A4u, 16u);
        w_u16(0x800716FCu, 2u);
        result = r_u16(0x80071A38u) | 1u;
        w_u16(0x80071A38u, result);
        return result;
    }
    if (r_u16(0x800715BCu) != 0u)
    {
        sub_80017FB0(192u, 140u, 1u, 257u);
        sub_80017FB0(169u, 86u, 1u, 255u);
        sub_80017FB0(119u, 98u, 1u, 256u);
        w_u16(0x800715BCu, r_u16(0x800715BCu) + 1u);
        result = 16u;
        if (r_u16(0x800715BCu) == 90u)
        {
            w_u16(0x800717A4u, 16u);
            w_u16(0x800716FCu, 2u);
            result = 2u;
        }
        return result;
    }
    result = 1u;
    if (!((r_u8(0x800AFFB0u) != 0u && r_u8(0x800AFFA7u) == 0u) || (r_u8(0x800B00D0u) != 0u && r_u8(0x800B00C7u) == 0u)))
    {
        w_u16(0x800715BCu, 1u);
        w_u16(0x80071888u, 2u);
        result = r_u16(0x80071A38u) | 1u;
        w_u16(0x80071A38u, result);
    }
    return result;
}

uint32 sub_8004EEFC(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10, uint32 a11)
{
    FUNCTION_MARKER(0x8004EEFCu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 v12;
    uint32 v13;
    sint32 v15;
    uint16 v16;
    uint32 result;

    v12 = (uint8)r_u8((uint32)(a3));
    v13 = a3 + 1;
    if (r_u8((uint32)(a3)))
    {
        v15 = a4;
        do
        {
            v16 = -1;
            if ((uint32)(v12 - 65) < 0x1A)
                v16 = v12 + 4;
            if ((uint16)v12 == 35)
                v16 = 95;
            if ((uint16)v12 == 46)
                v16 = 96;
            if ((uint16)v12 == 58)
                v16 = 97;
            if ((uint16)v12 == 44)
                v16 = 96;
            if ((uint16)v12 == 33)
                v16 = 112;
            if ((uint16)v12 == 63)
                v16 = 113;
            if ((uint16)v12 == 45)
                v16 = 111;
            if ((uint32)(v12 - 48) < 0xA)
                v16 = v12 + 51;
            result = a9 << 16;
            if (v16 != 0xFFFF)
                result = sub_80018214(a1, a2, 1, v16, v15, (sint16)a9, a10, a11);
            a1 += 16;
            v12 = r_u8((uint32)((v13 += 1u, v13 - 1u)));
        } while (v12);
    }
    return result;
}

uint32 sub_800577EC(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x800577ECu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    uint32 v2;
    uint32 v3;
    sint32 v4;
    uint32 v5;
    uint32 v6;
    uint32 v7;
    sint32 result;
    uint32 v9;
    uint8 v10;
    uint32 v11;
    sint8 v12;
    sint8 v13;
    sint8 v14;
    sint8 v15;
    sint8 v16;

    v2 = 16;
    w_u16((uint32)(a2), r_u16((uint32)(a1)));
    v3 = a2 + 2u;
    w_u16((uint32)(v3), r_u16((uint32)((a1 + 2))));
    v4 = r_u16((uint32)((a1 + 8)));
    v5 = v3 + 2u;
    v13 = r_u8((uint32)((a1 + 10)));
    v6 = (uint32)(a1 + 14 + r_u16((uint32)((a1 + 4))));
    v14 = r_u8((uint32)((a1 + 11)));
    v7 = (uint32)(a1 + 16);
    v15 = r_u8((uint32)((a1 + 12)));
    result = (uint16)v4;
    v16 = r_u8((uint32)((a1 + 13)));
    v9 = r_u16((uint32)((a1 + 14)));
    v10 = (uint16)v4 == 0;
    v11 = v4 - 1;
    if (!v10)
    {
        while ((v9 & 1) == 0)
        {
            v2 += 0xFFFF;
            v9 >>= 1;
            if (!(uint16)v2)
            {
                v2 = 16;
                v9 = r_u16((uint32)((v7 += 2u, v7 - 2u)));
            }
            if ((v9 & 1) != 0)
            {
                v2 += 0xFFFF;
                v9 >>= 1;
                if (!(uint16)v2)
                {
                    v2 = 16;
                    v9 = r_u16((uint32)((v7 += 2u, v7 - 2u)));
                }
                if ((v9 & 1) != 0)
                {
                    v2 += 0xFFFF;
                    v9 >>= 1;
                    if (!(uint16)v2)
                    {
                        v2 = 16;
                        v9 = r_u16((uint32)((v7 += 2u, v7 - 2u)));
                    }
                    if ((v9 & 1) != 0)
                    {
                        v12 = v16;
                        goto LABEL_17;
                    }
                    w_u8((uint32)(v5), v15);
                }
                else
                {
                    w_u8((uint32)(v5), v14);
                }
            }
            else
            {
                w_u8((uint32)(v5), v13);
            }
        LABEL_18:
            (v5 += 1u);
            v2 += 0xFFFF;
            v9 >>= 1;
            if (!(uint16)v2)
            {
                v2 = 16;
                v9 = r_u16((uint32)((v7 += 2u, v7 - 2u)));
            }
            result = (uint16)v11;
            v10 = (uint16)v11 != 0;
            v11 += 0xFFFF;
            if (!v10)
                return result;
        }
        v12 = r_u8((uint32)((v6 += 1u, v6 - 1u)));
    LABEL_17:
        w_u8((uint32)(v5), v12);
        goto LABEL_18;
    }
    return result;
}

void sub_80020574(void)
{
    FUNCTION_MARKER(0x80020574u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint16 v0;
    sint32 v1;

    if (r_u32((uint32)(0x800BC02Cu)))
    {
        w_u32((uint32)(0x1F80002Cu), r_u32((uint32)(0x800BC038u)));
        w_u32((uint32)(0x1F800028u), 0);
        w_u32((uint32)(0x1F800030u), 0u - r_u32((uint32)(0x800BC034u)));
        if (r_u16((uint32)(0x800BC062u)))
        {
            w_u16((uint32)(0x1F800020u), r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 24))));
            w_u16((uint32)(0x1F800022u), (r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 26))) + r_u16((uint32)(0x800BC03Cu))) & 0xFFF);
            w_u16((uint32)(0x1F800024u), r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 28))));
        }
        else
        {
            w_u16((uint32)(0x1F800020u), 0);
            v0 = r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 26)));
            w_u16((uint32)(0x1F800024u), 0);
            w_u16((uint32)(0x1F800022u), (v0 + r_u16((uint32)(0x800BC03Cu))) & 0xFFF);
        }
        v1 = r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 86)));
        if (v1 == 1)
        {
            sub_8005D3C8(528482336, 528482304);
        }
        else if (r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 86))) >= 2u)
        {
            if (v1 == 2)
                sub_8005D658(528482336, 528482304);
        }
        else if (!r_u16((uint32)((r_u32((uint32)(0x800BC02Cu)) + 86))))
        {
            sub_8005D138(528482336, 528482304);
        }
        sub_8005CC48(528482304, 528482344, -2146713536);
        return;
    }
    return;
}

uint32 sub_80046A28(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x80046A28u, "SLES_007.30");

    struct
    {
        uint32 x, z;
        uint16 angle, index;
    } position;

    uint32 descriptor = a1, changed = 0u, carrier;
    if ((uint32)r_u8(a1 + 8u) - 1u < 2u)
    {
        position.x = r_u32(a3);
        position.z = r_u32(a3 + 8u);
        position.index = (uint16)a2;
        /* TODO: Bind the ordinary local aggregate to the guest-carrier helper ABI */
        carrier = draft_local_address(&position, sizeof(position));
        sub_800468F0(carrier);
        w_u32(a3, position.x);
        w_u32(a3 + 8u, position.z);
        changed = 1u;
        descriptor = r_u32(0x80071704u) + 14u * position.index;
    }
    if ((sint16)r_u16(0x80071774u) >= (sint32)r_u8(descriptor + 9u))
    {
        position.x = r_u32(a3);
        position.z = r_u32(a3 + 8u);
        position.index = (uint16)a2;
        sub_80046658(draft_local_address(&position, sizeof(position)));
        w_u32(a3, position.x);
        w_u32(a3 + 8u, position.z);
        changed = 1u;
    }
    if ((sint32)r_u8(descriptor + 9u) >= (sint16)r_u16(0x800717A0u))
    {
        position.x = r_u32(a3);
        position.z = r_u32(a3 + 8u);
        position.index = (uint16)a2;
        sub_800467A0(draft_local_address(&position, sizeof(position)));
        w_u32(a3, position.x);
        w_u32(a3 + 8u, position.z);
    }
    return changed;
}

uint32 sub_80058484(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x80058484u, "SLES_007.30");
    uint32 animation, target, count, before, after, stride, result;
    sint32 frame, low, high, divisor, fraction;
    sub_80058100(a1);
    animation = r_u32(a1 + 4u);
    frame = (sint16)r_u16(a1 + 16u);
    target = r_u32(a2) + 168u;
    count = (uint16)(r_u16(a2 + 8u) - 1u);
    stride = 3u * (count + 1u) + 1u;
    before = sub_80057B0C(animation, (uint32)frame, stride);
    after = sub_80057B74(animation, (uint32)frame, stride);
    high = (sint16)r_u16(after);
    if (frame >= high)
        before = after;
    low = (sint16)r_u16(before);
    divisor = high - low;
    if (divisor == 0)
        divisor = 1;
    fraction = frame - low;
    result = sub_80057F3C(before + 2u, after + 2u, (uint32)divisor, (uint32)fraction, target, a1);
    before += 8u;
    after += 8u;
    for (uint32 index = 0u; (uint16)index < count; ++index)
    {
        sub_80057BC0(before, after, (uint32)divisor, (uint32)fraction, target);
        before += 6u;
        after += 6u;
        target += 168u;
        result = (uint16)(index + 1u) < count;
    }
    return result;
}

uint32 sub_80035D90(uint32 a1)
{
    FUNCTION_MARKER(0x80035D90u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    uint16 v1;
    sint32 v2;
    sint32 v3;
    sint32 v4;
    uint16 v5;
    sint32 result;
    sint16 v7;

    v1 = 128;
    v2 = 234;
    if (r_u16((uint32)((a1 + 34))))
        v2 = 238;
    v3 = v2 + ((r_u16((uint32)((a1 + 36))) >> 3) & 3);
    v4 = r_u16((uint32)((a1 + 28)));
    w_u16((uint32)((a1 + 36)), r_u16((uint32)((a1 + 36))) + (3));
    if (v4)
    {
        v5 = r_u16((uint32)((a1 + 28))) - 1;
        w_u16((uint32)((a1 + 28)), v5);
        if (r_u16((uint32)((a1 + 28))) < 0x80u)
            v1 = v5;
        if (!r_u16((uint32)((a1 + 28))))
            return sub_80032FD0((uint32)a1);
        return sub_80016358((uint32)(a1 + 12), v3, r_u16((uint32)((a1 + 38))), r_u16((uint32)((a1 + 40))), 1, v1 + (r_u16((uint32)((a1 + 36))) & 0x1F));
    }
    v7 = -1;
    if (r_u8((uint32)(0x800AFFB0u)))
        v7 = r_u16((uint32)(0x800AFFCCu));
    if (r_u8((uint32)(0x800B00D0u)) && v7 < r_u16((uint32)(0x800B00ECu)))
        v7 = r_u16((uint32)(0x800B00ECu));
    if ((sint16)r_u16((uint32)((a1 + 32))) < v7)
        return sub_80032FD0((uint32)a1);
    result = v7 < (sint16)r_u16((uint32)((a1 + 30)));
    if (v7 >= (sint16)r_u16((uint32)((a1 + 30))))
        return sub_80016358((uint32)(a1 + 12), v3, r_u16((uint32)((a1 + 38))), r_u16((uint32)((a1 + 40))), 1, v1 + (r_u16((uint32)((a1 + 36))) & 0x1F));
    return result;
}

uint32 sub_80012FBC(void)
{
    FUNCTION_MARKER(0x80012FBCu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    /* GP resolves to 0x80071474 */
    sint32 result;
    uint16 v2;
    sint32 v3;
    uint32 v4;
    sint32 v5;
    sint8 v6;
    sint32 v7;
    uint32 v8;
    sint16 v9[4];
    sint32 v10;
    sint32 v11;

    result = r_u8((uint32)((0x80071474u + 216)));
    v2 = 0;
    if (r_u8((uint32)((0x80071474u + 216))))
    {
        do
        {
            v3 = v2;
            sub_80012780(r_u8((uint32)((v2 - 2146708964))), (uint32 *)&v10, (uint32 *)&v11);
            v9[2] = 64;
            v9[3] = 256;
            v4 = (uint32)(4 * v2 - 2146708940);
            v9[0] = v10;
            v9[1] = v11;
            sub_8005E290(draft_local_address(v9, sizeof(v9)), r_u32((uint32)(v4)));
            sub_8005DFE4(0);
            ++v2;
            sub_80011AF8(r_u32((uint32)(v4)));
            w_u8((uint32)((r_u16((uint32)((0x80071474u + 396))) - 2146695948)), r_u8((uint32)((v3 - 2146708964))));
            v5 = r_u16((uint32)((0x80071474u + 396)));
            v6 = r_u8((uint32)((v3 - 2146708988)));
            v3 *= 2;
            w_u8((uint32)((v5 - 2146696692)), v6);
            v7 = r_u16((uint32)((0x80071474u + 396)));
            w_u16((uint32)((2 * v5 - 2146765180)), r_u16((uint32)((v3 - 2146656820))));
            w_u16((uint32)((0x80071474u + 396)), v7 + 1);
            w_u16((uint32)((2 * v7 - 2146767244)), r_u16((uint32)((v3 - 2146700096))));
            v8 = r_u8((uint32)((0x80071474u + 216)));
            result = v2 < v8;
        } while (v2 < v8);
    }
    w_u8((uint32)((0x80071474u + 216)), 0);
    return result;
}

uint32 sub_800468F0(uint32 a1)
{
    FUNCTION_MARKER(0x800468F0u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */
    uint32 gte_t4, gte_t5, gte_t6;

    sint32 v2;
    sint16 v3;
    sint32 v9;
    sint32 v10;
    sint32 v11;
    sint32 result;
    sint32 v13[4];

    do
    {
        v2 = r_u16((uint32)((a1 + 10)));
        w_u32((uint32)(0x1F800020u), 0);
        v3 = r_u16((uint32)((14 * v2 + r_u32((uint32)(0x80071704u)) + 12)));
        w_u16((uint32)((a1 + 8)), v3);
        w_u16((uint32)(0x1F800022u), v3);
        w_u16((uint32)(0x1F800024u), 0);
        sub_8005D138(528482336, 528482304);
        gte_t4 = r_u32((uint32)(0x1F800000u));
        gte_t5 = r_u32((uint32)(0x1F800004u));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
        draft_gte_control(0u, gte_t4);
        draft_gte_control(1u, gte_t5);
        gte_t4 = r_u32((uint32)(0x1F800008u));
        gte_t5 = r_u32((uint32)(0x1F80000Cu));
        gte_t6 = r_u32((uint32)(0x1F800010u));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
        draft_gte_control(2u, gte_t4);
        draft_gte_control(3u, gte_t5);
        draft_gte_control(4u, gte_t6);
        w_u32((uint32)(0x1F800020u), 0);
        w_u16((uint32)(0x1F800022u), 0);
        w_u16((uint32)(0x1F800024u), 32);
        sub_8005CDA8(528482336, draft_local_address(v13, sizeof(v13)));
        v9 = r_u32((uint32)((a1 + 4)));
        w_u32((uint32)(a1), r_u32((uint32)(a1)) + (v13[0]));
        v10 = r_u32((uint32)(a1));
        v11 = v9 + v13[2];
        w_u32((uint32)((a1 + 4)), v11);
        sub_80046324(v10, v11, (uint32)(a1 + 10));
        result = (uint32)r_u8((uint32)((14 * r_u16((uint32)((a1 + 10))) + r_u32((uint32)(0x80071704u)) + 8))) - 1 < 2;
    } while ((uint32)r_u8((uint32)((14 * r_u16((uint32)((a1 + 10))) + r_u32((uint32)(0x80071704u)) + 8))) - 1 < 2);
    return result;
}

uint32 sub_8001B570(void)
{
    FUNCTION_MARKER(0x8001B570u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    uint16 v0;
    sint32 v1;
    sint16 v2;
    sint16 v3;
    sint16 v4;

    v0 = 0;
    v1 = 0;
    do
    {
        v2 = r_u16((uint32)((8 * v1 - 2146699040))) + r_u16((uint32)(0x80071858u));
        v3 = r_u16((uint32)((8 * v1 - 2146699038))) + r_u16((uint32)(0x8007185Au));
        v4 = r_u16((uint32)((8 * v1 - 2146699036))) + r_u16((uint32)(0x8007185Cu));
        if ((v2 & 0x8000) != 0)
            v2 = 0;
        if (((r_u16((uint32)((8 * v1 - 2146699038))) + r_u16((uint32)(0x8007185Au))) & 0x8000) != 0)
            v3 = 0;
        if (((r_u16((uint32)((8 * v1 - 2146699036))) + r_u16((uint32)(0x8007185Cu))) & 0x8000) != 0)
            v4 = 0;
        if (v2 >= 256)
            v2 = 255;
        if (v3 >= 256)
            v3 = 255;
        ++v0;
        if (v4 >= 256)
            v4 = 255;
        w_u16((uint32)((2 * v1 - 2146733724)), 4 * v2);
        w_u16((uint32)((2 * v1 - 2146733718)), 4 * v3);
        w_u16((uint32)((2 * v1 - 2146733712)), 4 * v4);
        v1 = v0;
    } while (v0 < 3u);
    sub_8005CF98(-2146733724);
    /* SetColorMatrix preserves the false loop-condition value in MIPS v0 */
    return (uint16)v0 < 3u;
}

uint32 sub_80017FB0(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    FUNCTION_MARKER(0x80017FB0u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 v4;
    uint32 v5;
    uint32 v7;
    uint32 result;

    v4 = r_u32((uint32)(0x80071680u));
    w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (40));
    w_u8((uint32)((v4 + 15)), 4);
    w_u8((uint32)((v4 + 19)), 101);
    v5 = (uint32)(16 * a4 - 2146695836);
    w_u16((uint32)((v4 + 20)), a1 - r_u16((uint32)(v5 + 2u * (6))));
    w_u16((uint32)((v4 + 22)), a2 - r_u16((uint32)(v5 + 2u * (7))));
    w_u8((uint32)((v4 + 24)), r_u8((uint32)((v5 + 1u * (4)))));
    w_u8((uint32)((v4 + 25)), r_u8((uint32)((v5 + 1u * (6)))));
    w_u16((uint32)((v4 + 28)), r_u16((uint32)(v5 + 2u * (4))) - 1);
    w_u16((uint32)((v4 + 30)), r_u16((uint32)(v5 + 2u * (5))) - 1);
    w_u16((uint32)((v4 + 26)), r_u16((uint32)(v5 + 2u * (1))));
    sub_8005EEB8(v4, 1, 1, r_u16((uint32)(v5)), 0u);
    sub_80060DB8(v4, v4 + 12);
    v7 = (uint32)(4 * a3 + r_u32((uint32)(0x8007184Cu)));
    w_u32((uint32)(v4), r_u32((uint32)(v4)) & 0xFF000000 | r_u32((uint32)(v7)) & 0xFFFFFF);
    result = r_u32((uint32)(v7)) & 0xFF000000 | v4 & 0xFFFFFF;
    w_u32((uint32)(v7), result);
    return result;
}

void sub_8004DF80(uint32 a1)
{
    FUNCTION_MARKER(0x8004DF80u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 v2;
    sint32 v3;
    sint32 v4;
    sint32 v5;
    sint32 v6;
    uint32 v7;

    if (a1)
    {
        v2 = r_u32((uint32)(0x8007159Cu)) - r_u32((uint32)(0x80071814u));
        if (r_u32((uint32)(0x8007159Cu)) - r_u32((uint32)(0x80071814u)) < a1)
        {
            w_u32((uint32)(0x80071814u), r_u32((uint32)(0x8007159Cu)));
            v3 = a1 - v2;
            v4 = ((a1 - v2) / 2048) << 11;
            v5 = (a1 - v2) % 2048;
            w_u32((uint32)(0x800717E8u), r_u32((uint32)(0x800717E8u)) + (v4 + v2));
            w_u32((uint32)(0x800718FCu), r_u32((uint32)(0x800718FCu)) + (v3 / 2048));
            if (v5)
            {
                v6 = r_u32((uint32)(0x8007157Cu));
                w_u32((uint32)(0x8007157Cu), 100000);
                v7 = sub_80011A98(v5);
                sub_8004DD18(v7, v5);
                sub_80011AF8((sint32)v7);
                w_u32((uint32)(0x8007157Cu), v6);
            }
        }
        else
        {
            w_u32((uint32)(0x80071814u), r_u32((uint32)(0x80071814u)) + (a1));
            w_u32((uint32)(0x800717E8u), r_u32((uint32)(0x800717E8u)) + (a1));
        }
    }
}

uint32 sub_80052EE8(uint32 a1)
{
    FUNCTION_MARKER(0x80052EE8u, "SLES_007.30");
    uint32 offset[3], result;
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800024u, 0u);
    w_u16(0x1F800022u, r_u16(a1 + 18u));
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x1F800024u, r_u16(a1 + 276u));
    /* TODO: Resolve SDK local vector output adapter without guest stack reproduction */
    sub_8005CDD8(0x1F800000u, 0x1F800020u, draft_local_address(offset, sizeof(offset)));
    offset[0] += r_u32(a1);
    offset[2] += r_u32(a1 + 8u);
    sub_80021288(offset[0], offset[2], r_u32(a1 + 48u), r_u32(a1 + 4u), 1u);
    sub_80021288(offset[0], offset[2], r_u32(a1 + 48u), r_u32(a1 + 4u), 1u);
    result = sub_80021288(offset[0], offset[2], r_u32(a1 + 48u), r_u32(a1 + 4u), 1u);
    return result;
}

uint32 sub_80057A14(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x80057A14u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 v4;
    sint32 v5;
    sint32 v6;
    uint32 v7;
    uint32 v8;
    uint16 v9;

    v4 = r_u16((uint32)(a1));
    v5 = r_u16((uint32)(a1 + 2u * (11)));
    v6 = 40 * v4 - 2146697976;
    v7 = r_u32((uint32)((4 * (uint16)a2 + r_u32((uint32)((v6 + 4))))));
    if (v5 != 0xFFFF)
    {
        sub_80031308(v5);
        w_u16((uint32)(a1 + 2u * (11)), -1);
    }
    v8 = (uint32)r_u32((uint32)((a1 + 4u * (1))));
    w_u16((uint32)(a1 + 2u * (1)), a2);
    w_u16((uint32)(a1 + 2u * (8)), 0);
    v9 = r_u16((uint32)(v7));
    w_u16((uint32)(a1 + 2u * (11)), -1);
    w_u8((uint32)((a1 + 1u * (20))), 0);
    w_u16((uint32)(a1 + 2u * (13)), 0);
    w_u16((uint32)(a1 + 2u * (12)), 0);
    w_u8((uint32)((a1 + 1u * (21))), 0);
    w_u16((uint32)(a1 + 2u * (14)), 4096);
    w_u16((uint32)(a1 + 2u * (17)), 0);
    w_u16((uint32)(a1 + 2u * (20)), 0);
    w_u16((uint32)(a1 + 2u * (21)), 0);
    w_u16((uint32)(a1 + 2u * (4)), 0);
    w_u16((uint32)(a1 + 2u * (5)), 0);
    w_u16((uint32)(a1 + 2u * (28)), 0);
    w_u16((uint32)(a1 + 2u * (29)), 0);
    w_u16((uint32)(a1 + 2u * (9)), v9);
    sub_800577EC((sint32)v7, v8);
    return sub_80057954(r_u32((uint32)((a1 + 4u * (1)))), r_u16((uint32)((v6 + 8))));
}

void sub_80013FE8(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x80013FE8u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    /* GP resolves to 0x80071474 */
    sint32 v6;
    sint32 v7;
    /* GP resolves to 0x80071474 */
    sint32 v9;
    /* GP resolves to 0x80071474 */
    /* GP resolves to 0x80071474 */
    sint8 v12[8];
    sint8 v13[8];

    v6 = a1;
    if (a1 > 0 && (sint16)r_u16((uint32)((0x80071474u + 412))) >= (sint32)a1)
    {
        v13[0] = 1;
        sub_80063C94(14, draft_local_address(v13, sizeof(v13)), 0);
        v12[0] = -26;
        v12[1] = 0;
        v12[2] = -26;
        v12[3] = 0;
        sub_80063DE0((uint8 *)v12);
        v7 = 4 * v6;
        w_u16((uint32)((0x80071474u + 764)), a1);
        w_u16((uint32)((0x80071474u + 392)), 230);
        v9 = sub_80063F88((const uint8 *)psx_addr((uint32)(v7 - 2146763532), 3u));
        w_u32((uint32)((0x80071474u + 336)), v9 - 256);
        sub_80063C94(2, v7 - 2146763536, 0);
        while (!sub_80063C94(3, 0, 0))
            ;
        w_u8((uint32)((0x80071474u + 204)), 1);
        w_u16((uint32)((0x80071474u + 876)), a3);
    }
}

uint32 sub_80032DFC(void)
{
    FUNCTION_MARKER(0x80032DFCu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    uint16 v0;
    sint32 v1;
    sint32 v2;
    sint32 v3;
    sint32 result;

    v0 = 0;
    w_u32((uint32)(0x80071718u), (sint32)sub_80011A98(26560));
    v1 = 0;
    do
    {
        ++v0;
        sub_8002F0D4((uint32)(332 * v1 + r_u32((uint32)(0x80071718u))), 332);
        v1 = v0;
    } while (v0 < 0x50u);
    v2 = 0;
    w_u32((uint32)(0x80071868u), 0);
    v3 = r_u32((uint32)(0x80071718u));
    w_u32((uint32)(0x80071670u), r_u32((uint32)(0x80071718u)));
    do
    {
        w_u32((uint32)((332 * (unsigned __int16)v2 + v3 + 4)), 332 * (uint16)v2 + 332 + v3);
        ++v2;
    } while ((uint16)v2 < 0x4Fu);
    result = r_u32((uint32)(0x80071718u));
    w_u16((uint32)(0x800718F0u), 0);
    w_u32((uint32)((r_u32((uint32)(0x80071718u)) + 26232)), 0);
    return result;
}
