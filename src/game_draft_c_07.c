#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern uint32 sub_8002372C();
extern uint32 sub_80023D1C();
extern uint32 sub_80014230();
extern uint32 sub_80014194();
extern uint32 sub_8005D138();
extern uint32 sub_8005CC48();
extern uint32 sub_8005CDD8();

void sub_80058678(void)
{
    uint32 script = r_u32(0x8007165Cu), opcode, value, address, index, position, advance, a, b, c, d, e, f;
    for (;;)
    {
        opcode = r_u16(script);
        advance = 0;
        switch (opcode)
        {
            case 0:
                address = r_u32(script + 4u);
                value = r_u16(script + 2u);
                w_u16(address, value);
                advance = 8;
                break;
            case 1:
                address = r_u32(script + 4u);
                value = r_u32(script + 8u);
                w_u32(address, value);
                advance = 12;
                break;
            case 2:
                if (!r_u16(0x80071820u))
                    w_u16(0x80071820u, r_u16(script + 2u) + 1u);
                if (r_u16(0x80071820u) < 2u)
                {
                    w_u16(0x80071820u, 0);
                    advance = 4;
                }
                else
                {
                    w_u16(0x80071820u, r_u16(0x80071820u) - 1u);
                    goto pause;
                }
                break;
            case 3:
                position = r_u8(0x800AFFB0u) ? r_u16(0x800AFFCCu) : 0;
                if (r_u8(0x800B00D0u) && (sint32)position < (sint16)r_u16(0x800B00ECu))
                    position = (uint32)(sint32)(sint16)r_u16(0x800B00ECu);
                if (position < r_u16(script + 2u))
                    goto pause;
                advance = 4;
                break;
            case 4:
            case 38:
            case 47:
                if (r_u16(0x80071774u) != r_u16(script + 4u) || r_u16(0x800717A0u) != r_u16(script + 6u))
                {
                    a = r_u16(script + 4u);
                    b = r_u16(script + 6u);
                    w_u32(0x8007165Cu, script);
                    w_u16(0x80071664u, r_u16(0x80071774u));
                    w_u16(0x8007169Cu, r_u16(0x800717A0u));
                    w_u16(0x80071774u, a);
                    w_u16(0x800717A0u, b);
                    return;
                }
                if (opcode == 47u)
                {
                    if ((sint16)r_u16(0x800717FCu) != 2)
                        goto pause;
                }
                else
                {
                    if (r_u16(0x8007172Cu))
                        goto pause;
                    if (opcode == 4u && r_u16(0x800716BCu))
                        goto pause;
                    w_u16(0x800717A0u, r_u16(0x8007169Cu));
                }
                advance = 8;
                break;
            case 5:
                goto pause;
            case 6:
                a = r_u16(script + 2u);
                b = r_u16(script + 4u);
                c = r_u16(script + 6u);
                d = r_u16(script + 8u);
                e = r_u16(script + 10u);
                f = r_u16(script + 12u);
                value = r_u16(script + 14u);
                w_u16(0x800717D0u, 1);
                w_u16(0x800719ACu, a);
                w_u16(0x800715DCu, b);
                w_u16(0x80071A54u, c);
                w_u16(0x800719A0u, d);
                w_u16(0x800715D0u, e);
                w_u16(0x80071A4Cu, f);
                w_u16(0x80071A2Cu, value);
                advance = 16;
                break;
            case 7:
                w_u16(0x80071774u, r_u16(script + 4u));
                w_u16(0x800717A0u, r_u16(script + 6u));
                if (!r_u16(0x800717A0u))
                    w_u16(0x800717A0u, r_u16(0x80071728u) - 1u);
                advance = 8;
                break;
            case 8:
                if (r_u16(r_u32(script + 4u)) != r_u16(script + 2u))
                    goto pause;
                advance = 8;
                break;
            case 9:
                if (r_u32(r_u32(script + 4u)) != r_u32(script + 8u))
                    goto pause;
                advance = 12;
                break;
            case 10:
            case 11:
                index = 8u * r_u16(script + 2u);
                a = r_u16(script + 4u);
                b = r_u16(script + 6u);
                w_u16((uint32)-2146701382 + index, a);
                if (opcode == 11u)
                    w_u16((uint32)-2146673330 + index, a);
                w_u16((uint32)-2146701384 + index, b);
                if (opcode == 11u)
                    w_u16((uint32)-2146673332 + index, b);
                advance = 8;
                break;
            case 12:
            case 13:
                value = r_u32(script + 4u);
                index = 8u * r_u16(script + 2u);
                w_u16((uint32)-2146701712 + index, (uint8)value);
                if (opcode == 13u)
                    w_u16((uint32)-2146673412 + index, (uint8)value);
                w_u16((uint32)-2146701710 + index, (uint8)(value >> 8));
                if (opcode == 13u)
                    w_u16((uint32)-2146673410 + index, (uint8)(value >> 8));
                w_u16((uint32)-2146701708 + index, (uint8)(value >> 16));
                if (opcode == 13u)
                    w_u16((uint32)-2146673408 + index, (uint8)(value >> 16));
                advance = 8;
                break;
            case 14:
                w_u32(0x800717D8u, r_u16(script + 2u));
                advance = 4;
                break;
            case 15:
                value = r_u16(script + 2u);
                w_u32(0x800718F4u, value);
                w_u32(0x800717D8u, value);
                advance = 4;
                break;
            case 16:
                sub_80023244(r_u8(script + 2u), r_u16(script + 2u) >> 8, r_u32(script + 4u));
                advance = 8;
                break;
            case 17:
            case 18:
                sub_8002372C(r_u8(script + 2u), r_u16(script + 2u) >> 8, opcode == 18u, r_u32(script + 4u));
                advance = 8;
                break;
            case 19:
                w_u16(0x80071744u, 1);
                w_u16(0x800718B0u, r_u16(script + 2u));
                advance = 4;
                break;
            case 20:
                sub_80023D1C(r_u8(script + 2u), r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 21:
                advance = 4;
                break;
            case 22:
                a = r_u8(script + 2u);
                b = r_u16(script + 2u) >> 8;
                c = r_u8(script + 4u);
                d = r_u8(script + 5u);
                e = r_u8(script + 6u);
                f = r_u8(script + 7u);
                sub_80026D18(a, b, c, d, e, f, r_u8(script + 8u), r_u8(script + 9u), r_u8(script + 10u));
                advance = 12;
                break;
            case 23:
                /* TODO: Finalize the mixed-width command's trailing argument signature */
                sub_80026D8C(r_u32(script + 4u), r_u32(script + 8u), r_u32(script + 12u), r_u16(script + 16u), r_u16(script + 18u), r_u16(script + 18u), 0, r_u16(script + 20u), r_u16(script + 22u));
                advance = 24;
                break;
            case 24:
                sub_80024074(r_u8(script + 2u), r_u16(script + 2u) >> 8, r_u16(script + 4u), r_u16(script + 6u), r_u32(script + 8u));
                advance = 12;
                break;
            case 25:
                sub_8002823C(r_u8(script + 2u), r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 26:
                sub_80028480(r_u8(script + 2u), r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 27:
                sub_800287AC(r_u8(script + 2u), r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 28:
                w_u16(0x800AFF8Cu, r_u8(script + 2u));
                w_u16(0x800AFF8Eu, r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 29:
                w_u16(0x800B00ACu, r_u8(script + 2u));
                w_u16(0x800B00AEu, r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 30:
                value = r_u8(0x800AFFB0u) && (sint16)r_u16(0x800AFF8Cu) != -1;
                if (r_u8(0x800B00D0u) && (sint16)r_u16(0x800B00ACu) != -1)
                    value = 1;
                if (value)
                    goto pause;
                advance = 4;
                break;
            case 31:
            case 32:
            case 35:
                if ((sint16)r_u16(0x8007192Cu) < 0)
                    goto pause;
                if (r_u32(0x800715B8u))
                    w_u16(0x8007192Cu, opcode == 31u ? (uint32)-32 : (uint32)-16);
                if (r_u16(0x8007192Cu))
                    goto pause;
                if (opcode == 31u)
                {
                    sub_80013FE8(r_u16(script + 2u) & 127u, 230, 0xFFFFu);
                    w_u16(0x8007192Cu, 32);
                }
                else if (opcode == 32u)
                {
                    sub_80014230();
                    w_u16(0x8007192Cu, 4);
                }
                else
                {
                    sub_80014194();
                    sub_80013FE8(r_u16(script + 2u) & 127u, 230, 0xFFFFu);
                    w_u16(0x8007192Cu, 4);
                }
                advance = 4;
                break;
            case 33:
                w_u16(0x800717F8u, r_u16(script + 2u));
                advance = 4;
                break;
            case 34:
                value = r_u16(script + 2u);
                w_u16(0x800718D4u, 0);
                w_u16(0x80071904u, 0);
                w_u16(0x80071558u, value);
                advance = 4;
                break;
            case 36:
                w_u16(0x80071850u, r_u16(script + 4u));
                w_u16(0x80071852u, r_u16(script + 8u));
                w_u16(0x80071854u, r_u16(script + 12u));
                advance = 16;
                break;
            case 37:
                sub_80026B78(r_u16(script + 2u), r_u16(script + 4u), r_u16(script + 6u), r_u32(script + 8u), r_u32(script + 12u), r_u32(script + 16u));
                advance = 20;
                break;
            case 39:
                value = sub_800294B4(r_u16(script + 2u), r_u16(script + 4u), r_u16(script + 6u), r_u16(script + 8u), r_u16(script + 10u));
                if (!value)
                    goto pause;
                advance = 12;
                break;
            case 40:
                w_u16(0x80071764u, 90);
                w_u16(0x80071950u, r_u16(0x80071940u) == 0);
                advance = 4;
                break;
            case 41:
                sub_8002A908(r_u8(script + 2u), r_u16(script + 2u) >> 8);
                advance = 4;
                break;
            case 42:
            case 43:
                sub_8002AA44(r_u8(script + 2u), r_u16(script + 2u) >> 8, opcode == 43u);
                advance = 4;
                break;
            case 44:
                value = r_u16(script + 2u);
                sub_800451B8(256, 0, 256, 0);
                sub_80013FE8(value & 127u, 230, 1);
                advance = 4;
                break;
            case 45:
                sub_800236DC(0, 80);
                advance = 4;
                break;
            case 46:
                if (r_u8(0x800AFFB0u) && !r_u8(0x80071768u))
                    w_u8(0x80071768u, 1);
                if (r_u8(0x800B00D0u) && !r_u8(0x80071769u))
                    w_u8(0x80071769u, 1);
                advance = 4;
                break;
            default:
                /* TODO: Unknown opcodes repeat at the same script address */
                break;
        }
        script += advance;
    }
pause:
    w_u32(0x8007165Cu, script);
}

uint32 sub_800215EC(void)
{
    uint16 local[4];
    uint32 old_x, old_z, divisor, numerator, values[4], i, zone, terrain, base_angle, dx, dz, abs_x, abs_z;
    uint32 players, distance, target_angle, angle, width, height, base_x, base_z, result;
    local[0] = 0xFFFFu;
    divisor = r_u32(0x80071A08u);
    if (divisor)
    {
        /* TODO: Original BREAK handling for exceptional signed divisions */
        numerator = r_u32(0x800BF7E0u);
        old_x = divisor == 0xFFFFFFFFu && numerator == 0x80000000u ? draft_unknown_argument("sub_800215EC", 0) : (uint32)((sint32)numerator / (sint32)divisor);
        numerator = r_u32(0x800BF7E8u);
        old_z = divisor == 0xFFFFFFFFu && numerator == 0x80000000u ? draft_unknown_argument("sub_800215EC", 1) : (uint32)((sint32)numerator / (sint32)divisor);
        numerator = r_u32(0x800BF7E4u);
        values[0] = divisor == 0xFFFFFFFFu && numerator == 0x80000000u ? draft_unknown_argument("sub_800215EC", 2) : (uint32)((sint32)numerator / (sint32)divisor);
        divisor = r_u32(0x80071738u);
        numerator = r_u32(0x800AF01Cu);
        values[1] = !divisor || (divisor == 0xFFFFFFFFu && numerator == 0x80000000u) ? draft_unknown_argument("sub_800215EC", 3) : (uint32)((sint32)numerator / (sint32)divisor);
        w_u32(0x800BF7E4u, values[0]);
        w_u32(0x800AF01Cu, values[1]);
    }
    else
    {
        /* TODO: Recover position carriers when the optional division path is disabled */
        old_x = draft_unknown_argument("sub_800215EC", 0);
        old_z = draft_unknown_argument("sub_800215EC", 1);
    }
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800024u, 0);
    w_u16(0x1F800022u, 0u - r_u16(0x800BBFD6u));
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u32(0x1F800028u, (uint32)((sint32)(r_u32(0x800AF674u) + r_u32(0x800AF6E0u)) >> 1));
    w_u32(0x1F800030u, r_u32(0x800AF6B8u));
    sub_8005CC48(0x1F800000u, 0x1F800028u, 0x1F800028u);
    w_u32(0x800BF7E0u, r_u32(0x1F800028u) + r_u32(0x800BBFC4u));
    w_u32(0x800BF7E8u, r_u32(0x1F800030u) + r_u32(0x800BBFCCu));
    sub_80046324(old_x, old_z, draft_local_address(local, sizeof(local)));
    zone = local[0] == 0xFFFFu ? 0 : r_u8(r_u32(0x80071704u) + 14u * local[0] + 9u);
    terrain = r_u32(0x8007167Cu) + 28u * zone;
    w_u32(0x800AF6C0u, r_u32(terrain + 4u));
    w_u32(0x800AF6C4u, r_u32(terrain + 8u));
    w_u32(0x800AF6C8u, r_u32(terrain + 12u));
    angle = r_u16(terrain + 16u);
    w_u32(0x800BD1F8u, r_u32(terrain + 20u));
    base_angle = r_u16(r_u32(0x800716D0u) + 2u * zone);
    w_u16(0x80071604u, angle);
    w_u32(0x80071944u, r_u32(terrain + 24u));
    dx = r_u32(0x800AEEA0u) - r_u32(0x800C9E40u);
    dz = r_u32(0x800AEEA8u) - r_u32(0x800C9E48u);
    players = r_u8(0x800AFFB0u) && r_u8(0x800B00D0u) ? 2u : 1u;
    abs_x = (sint32)dx < 0 ? 0u - dx : dx;
    abs_z = (sint32)dz < 0 ? 0u - dz : dz;
    target_angle = base_angle + angle;
    if (((sint32)abs_x >= 32 || (sint32)abs_z >= 32) && (sint32)players < (sint16)r_u16(0x800715A8u))
    {
        distance = sub_8001F8A8(r_u32(0x800AEEA0u) - r_u32(0x800C9E40u), r_u32(0x800AEEA8u) - r_u32(0x800C9E48u));
        angle = sub_80046B84(dx, dz, distance);
        angle = sub_80046D0C((uint32)(sint32)(sint16)(angle + r_u16(0x80071604u) - base_angle));
        if ((sint16)angle < -160)
            angle = (uint32)-160;
        if ((sint16)angle > 160)
            angle = 160;
        target_angle = base_angle + angle;
    }
    if (!r_u8(0x800716ECu))
        w_u16(0x80071654u, sub_800211D8(r_u16(0x80071654u), (uint32)(sint32)(sint16)target_angle));
    else
        w_u16(0x80071654u, target_angle);
    w_u32(0x800AF020u, r_u32(0x800BF7E8u));
    w_u32(0x800AF018u, r_u32(0x800BF7E0u));
    width = r_u32(0x800AF6E0u) - r_u32(0x800AF674u);
    w_u32(0x80071630u, width);
    if (!r_u16(0x80071A30u) && (sint32)width < 3000)
        w_u32(0x80071630u, 3000);
    width = r_u32(0x80071630u);
    height = (uint32)((sint32)(0u - width) >> 1) - width;
    height += (uint32)((sint32)height >> 2);
    if ((sint32)height < -7000)
        height = (uint32)-7000;
    if ((sint32)height < (sint32)r_u32(0x800AF6C4u))
        w_u32(0x800AF6C4u, height);
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800024u, 0);
    w_u32(0x800BC040u, r_u32(0x800BF7E0u));
    w_u32(0x800BC044u, r_u32(0x800BF7E4u) + r_u32(0x800AF6C4u));
    w_u32(0x800BC048u, r_u32(0x800BF7E8u));
    w_u16(0x1F800022u, r_u16(0x80071654u));
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800022u, 0);
    w_u16(0x1F800020u, r_u32(0x800AF6C0u));
    w_u16(0x1F800024u, r_u32(0x800AF6C8u));
    width = r_u32(0x80071630u);
    width += (uint32)((sint32)((uint32)((sint32)width >> 5) + width) >> 5) + (uint32)((sint32)width >> 5);
    if ((sint32)width >= 12001)
        width = 12000;
    w_u32(0x80071630u, width);
    if ((sint16)r_u32(0x800AF6C0u) < (sint32)width)
        w_u16(0x1F800020u, width);
    sub_8005CDD8(0x1F800000u, 0x1F800020u, 0x1F800028u);
    w_u32(0x800BC048u, r_u32(0x800BC048u) + r_u32(0x1F800030u));
    w_u32(0x800BC040u, r_u32(0x800BC040u) + r_u32(0x1F800028u));
    terrain = r_u32(0x80071954u) + 8u * zone;
    base_x = r_u32(terrain);
    base_z = r_u32(terrain + 4u);
    angle = r_u16(r_u32(0x800716D0u) + 2u * zone);
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800024u, 0);
    w_u16(0x1F800022u, angle - 1024u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u32(0x1F800028u, r_u32(0x800BC040u) - base_x);
    w_u32(0x1F800030u, r_u32(0x800BC048u) - base_z);
    sub_8005CC48(0x1F800000u, 0x1F800028u, 0x1F800028u);
    if ((sint32)r_u32(0x80071944u) < (sint32)r_u32(0x1F800030u))
    {
        w_u32(0x1F800030u, r_u32(0x80071944u));
        w_u16(0x1F800020u, 0);
        w_u16(0x1F800024u, 0);
        w_u16(0x1F800022u, 1024u - r_u16(r_u32(0x800716D0u) + 2u * zone));
        sub_8005D138(0x1F800020u, 0x1F800000u);
        sub_8005CC48(0x1F800000u, 0x1F800028u, 0x1F800028u);
        w_u32(0x800BC040u, r_u32(0x1F800028u) + base_x);
        w_u32(0x800BC048u, r_u32(0x1F800030u) + base_z);
    }
    for (i = 0; i < 3u; ++i)
        w_u32(0x1F800028u + 4u * i, r_u32(0x800BC040u + 4u * i) - r_u32(0x800BBFC4u + 4u * i));
    if ((sint32)sub_80047640(r_u32(0x1F800028u), r_u32(0x1F80002Cu), r_u32(0x1F800030u)) < 32)
        for (i = 0; i < 4u; ++i)
            w_u32(0x800BC040u + 4u * i, r_u32(0x800BBFC4u + 4u * i));
    if (r_u8(0x800716ECu))
        for (i = 0; i < 4u; ++i)
            w_u32(0x800BBFC4u + 4u * i, r_u32(0x800BC040u + 4u * i));
    distance = r_u32(0x80071550u) - r_u32(0x800716B0u);
    if ((sint32)distance < 0)
        distance = 0u - distance;
    w_u32(0x800BC0B4u, r_u32(0x800AF018u));
    w_u32(0x800BC0B8u, r_u32(0x800AF01Cu) + r_u32(0x800BD1F8u) - (uint32)((sint32)distance >> 3) - (uint32)((sint32)distance >> 4));
    w_u32(0x800BC0BCu, r_u32(0x800AF020u));
    w_u32(0x1F800028u, r_u32(0x800AF018u) - r_u32(0x800BC0A4u));
    w_u32(0x1F80002Cu, r_u32(0x800BC0B8u) - r_u32(0x800BC0A8u));
    w_u32(0x1F800030u, r_u32(0x800AF020u) - r_u32(0x800BC0ACu));
    if ((sint32)sub_80047640(r_u32(0x1F800028u), r_u32(0x1F80002Cu), r_u32(0x1F800030u)) < 32)
        for (i = 0; i < 4u; ++i)
            w_u32(0x800BC0B4u + 4u * i, r_u32(0x800BC0A4u + 4u * i));
    result = r_u8(0x800716ECu);
    if (result)
    {
        for (i = 0; i < 4u; ++i)
            w_u32(0x800BC0A4u + 4u * i, r_u32(0x800BC0B4u + 4u * i));
        result = r_u32(0x800BC0BCu);
    }
    w_u32(0x80071A08u, 0);
    w_u8(0x800716ECu, 0);
    return result;
}

/* TODO: Overlay and SDK boundaries require fail-fast integration */
extern uint32 draft_guest_call0(uint32 address);
extern void draft_guest_call_void(uint32 address);
extern uint32 sub_8005C154(uint32 command);

extern void sub_8005B278(uint32), sub_8005E4D0(uint32, uint32), sub_800485D0(uint32), sub_8004848C(uint32), sub_8005DFE4(uint32), sub_8005E814(uint32), sub_8005E648(uint32), sub_8005E5D8(uint32), sub_8004C7C4(uint32);

uint32 sub_8004CCA8(void)
{
    uint32 overlay = 0, stage = r_u16(0x80071594u);
    switch (stage)
    {
        case 0:
            overlay = 0x800C9EFCu;
            break;
        case 1:
            overlay = 0x800CA078u;
            break;
        case 2:
            overlay = 0x800CA254u;
            break;
        case 3:
            overlay = 0x800C9EC0u;
            break;
        case 4:
            overlay = 0x800CA180u;
            break;
        case 5:
            overlay = 0x800CA35Cu;
            break;
        case 6:
            overlay = 0x800CA5B8u;
            break;
        case 8:
            overlay = 0x800C9F90u;
            break;
        case 9:
            overlay = 0x800CA220u;
            break;
        case 10:
            overlay = 0x800CA3ACu;
            break;
        case 11:
            overlay = 0x800CA750u;
            break;
        case 12:
            overlay = 0x800C9EDCu;
            break;
        case 13:
            overlay = 0x800CA010u;
            break;
        case 14:
        case 18:
            overlay = 0x800CA2B8u;
            break;
        case 15:
            overlay = 0x800CA5F8u;
            break;
        case 16:
            overlay = 0x800C9F14u;
            break;
        case 17:
            overlay = 0x800CA050u;
            break;
        case 19:
            overlay = 0x800CA614u;
            break;
        case 20:
            overlay = 0x800CA968u;
            break;
        case 21:
            overlay = 0x800CAAF0u;
            break;
    }
    if (stage == 0u || stage == 3u || stage == 8u || stage == 12u || stage == 16u || stage == 19u)
        w_u16(0x80071940u, 99);
    if (overlay)
        draft_guest_call_void(overlay);
    sub_80048154();
    sub_8005B278(0);
    w_u16(0x8007194Cu, 254);
    w_u16(0x800717A4u, (uint32)-8);
    w_u16(0x800716FCu, 2);
    sub_8005B278(0);
    sub_80048180();
    sub_80013B64(1, 0, 0, 0);
    sub_800451B8(0, 1, 0, 2);
    w_u8(0x80071544u, 0);
    while (r_u16(0x8007194Cu) != 255u || r_u16(0x800717A4u))
    {
        w_u32(0x80071700u, sub_8005C008(0x1F8003FCu));
        sub_80011BB8();
        sub_80058678();
        sub_80048EB8();
        sub_80049180();
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        w_u16(0x800717C0u, 0);
        sub_800471D8();
        sub_80047590();
        sub_8002B134();
        if (r_u16(0x8007199Cu))
            sub_800571F0();
        else
            sub_80056C28();
        if (r_u16(0x8007199Cu))
            sub_8003F5E0();
        else
        {
            sub_8003F008();
            sub_80026A88();
        }
        if (!r_u16(0x8007199Cu))
            sub_80030D84();
        sub_800470FC();
        sub_80047B68();
        if (!r_u16(0x8007199Cu))
            sub_8003220C();
        sub_8004EC74();
        if (!r_u16(0x8007199Cu))
            sub_8002B9B4();
        sub_800225C8();
        if (r_u16(0x80071594u) == 4u)
            draft_guest_call_void(0x800CA0B4u);
        sub_800206D8();
        sub_80050E48();
        sub_8002F0F8();
        sub_8002F36C();
        if (!r_u16(0x8007199Cu))
        {
            sub_8003076C();
            sub_8002FC3C();
            sub_80030188();
            sub_8002F98C();
            sub_800485D0(r_u32(0x8007184Cu) + 9996u);
            if (r_u16(0x800719E4u))
                sub_8004848C(2498);
        }
        sub_8005C008(r_u32(0x80071700u));
        sub_8004BD40();
        sub_800140DC();
        sub_80045048(0);
        sub_80044A5C(1);
        sub_8005DFE4(0);
        if (r_u16(0x800717D0u))
        {
            sub_80012330(r_u16(0x800715ECu), r_u16(0x80071578u), r_u16(0x800716F0u), r_u16(0x8007162Cu));
            w_u16(0x800717D0u, 0);
        }
        w_u32(0x800719F0u, r_u32(0x800719D4u));
        if (r_u16(0x800717C4u))
        {
            sub_8005B278(4);
            w_u16(0x800717C4u, r_u16(0x800717C4u) - 1u);
        }
        else if (r_u8(0x80071544u))
            sub_8005B278(2);
        else
            while ((sint32)sub_8005C154(0xF2000001u) < 507)
            {
            }
        sub_80048180();
        sub_8005E814(r_u32(0x800719F0u));
        sub_8005E648(r_u32(0x800719CCu));
        sub_8005E5D8(r_u32(0x8007184Cu) + 9996u);
        w_u16(0x800719D0u, r_u16(0x800719D0u) + 1u);
        w_u16(0x800715E8u, r_u16(0x800715E8u) ^ 1u);
        sub_8004C720();
        if (!r_u16(0x80071A38u))
        {
            if (r_u8(0x800AFFB0u) && ((r_u16(0x80071790u) & 0x800u) || !r_u16(0x80071A24u)))
                sub_8004C7C4(0);
            if (r_u8(0x800B00D0u) && ((r_u16(0x80071792u) & 0x800u) || !r_u16(0x80071A26u)))
                sub_8004C7C4(1);
        }
    }
    sub_80013B64(0, 0, 0, 0);
    sub_8004BC4C();
    sub_80013974();
    sub_800451B8(0x8000, (uint32)-8, 0x8000, (uint32)-4);
    sub_80045048(2);
    sub_80013F80();
    return sub_800455DC();
}

/* TODO: GTE adapters require fail-fast integration */
void sub_8005A7FC(uint32 vertices, uint32 records, uint32 normals, uint32 depth_bias)
{
    static const uint32 record_size[6] = {12, 16, 20, 28, 24, 28};
    uint32 packet = r_u32(0x80071680u), ordering = r_u32(0x8007184Cu);
    uint32 kind = (uint32)(sint32)(sint16)r_u16(records), category;
    sint32 remaining = (sint16)r_u16(records + 2u) - 1;
    records += 4u;
    for (category = 0; category < 6u; ++category)
    {
        if (kind != category)
            continue;
        if (category == 0u)
            draft_gte_data(6, 0x30969696u);
        if (category == 1u)
            draft_gte_data(6, 0x38969696u);
        if (category == 4u)
            draft_gte_data(6, 0x34969696u);
        if (category == 5u)
            draft_gte_data(6, 0x3C969696u);
        do
        {
            uint32 packed = r_u32(records + (category < 2u ? 4u : category == 2u ? 12u : 16u));
            uint32 index[4], normal_words[6], xy[3], colors[3], i, depth, tag, uv4 = 0;
            uint32 triangle = category == 0u || category == 2u || category == 4u;
            index[0] = (packed & 65535u) * 8u;
            index[1] = (packed >> 16) * 8u;
            index[2] = (uint32)(sint32)(sint16)r_u16(records + (category < 2u ? 8u : category == 2u ? 16u : 20u)) * 8u;
            for (i = 0; i < 3u; ++i)
            {
                draft_gte_data(2u * i, r_u32(vertices + index[i]));
                draft_gte_data(2u * i + 1u, r_u32(vertices + index[i] + 4u));
            }
            draft_gte_command(0x280030u);
            if (category < 4u)
            {
                normal_words[0] = r_u32(normals + index[0]);
                normal_words[1] = r_u32(normals + index[0] + 4u);
                if (category < 2u)
                {
                    normal_words[2] = r_u32(normals + index[1]);
                    normal_words[3] = r_u32(normals + index[1] + 4u);
                }
                else
                    colors[0] = r_u32(records);
            }
            else
            {
                w_u32(packet + 12u, r_u32(records + 4u));
                w_u32(packet + 24u, r_u32(records + 8u));
                if (category == 4u)
                    uv4 = r_u16(records + 12u);
            }
            draft_gte_command(0x1400006u);
            if (category == 4u)
                w_u16(packet + 36u, uv4);
            if (category == 5u)
                normal_words[0] = r_u32(normals + index[0]);
            if ((sint32)draft_gte_read(24) <= 0)
                goto next_record;
            draft_gte_command(0x158002Du);
            if (category == 5u)
                normal_words[1] = r_u32(normals + index[0] + 4u);
            /* TODO: Signed depth addition trap handling */
            depth = draft_gte_read(7) + depth_bias;
            if ((sint32)depth < 67 || (sint32)(depth & ~3u) >= 10000)
                goto next_record;
            tag = ordering + (depth & ~3u);
            for (i = 0; i < 3u; ++i)
                xy[i] = draft_gte_read(12u + i);
            if (category < 2u || category >= 4u)
            {
                for (i = 0; i < 3u; ++i)
                    w_u32(packet + (category < 2u ? 8u + 8u * i : 8u + 12u * i), xy[i]);
                if (category == 4u)
                {
                    normal_words[0] = r_u32(normals + index[0]);
                    normal_words[1] = r_u32(normals + index[0] + 4u);
                }
                if (category >= 4u)
                {
                    normal_words[2] = r_u32(normals + index[1]);
                    normal_words[3] = r_u32(normals + index[1] + 4u);
                }
                normal_words[4] = r_u32(normals + index[2]);
                normal_words[5] = r_u32(normals + index[2] + 4u);
                for (i = 0; i < 6u; ++i)
                    draft_gte_data(i, normal_words[i]);
                draft_gte_command(0xF80416u);
                for (i = 0; i < 3u; ++i)
                    colors[i] = draft_gte_read(20u + i);
                if (!triangle)
                {
                    index[3] = (uint32)(sint32)(sint16)r_u16(records + (category == 1u ? 10u : 22u)) * 8u;
                    if (category == 5u)
                    {
                        uv4 = r_u32(records + 12u);
                        w_u16(packet + 36u, uv4);
                        w_u16(packet + 48u, uv4 >> 16);
                    }
                    draft_gte_data(0, r_u32(vertices + index[3]));
                    draft_gte_data(1, r_u32(vertices + index[3] + 4u));
                    draft_gte_command(0x180001u);
                    w_u32(packet + (category == 1u ? 32u : 44u), draft_gte_read(14));
                    draft_gte_data(0, r_u32(normals + index[3]));
                    draft_gte_data(1, r_u32(normals + index[3] + 4u));
                    draft_gte_command(0xE80413u);
                    w_u32(packet + (category == 1u ? 28u : 40u), draft_gte_read(22));
                }
                for (i = 0; i < 3u; ++i)
                    w_u32(packet + (category < 2u ? 4u + 8u * i : 4u + 12u * i), colors[i]);
            }
            else
            {
                draft_gte_data(0, normal_words[0]);
                draft_gte_data(1, normal_words[1]);
                draft_gte_data(6, colors[0]);
                draft_gte_command(0xE80413u);
                for (i = 0; i < 3u; ++i)
                    w_u32(packet + 8u + 8u * i, xy[i]);
                for (i = 1; i < 3u; ++i)
                {
                    uint32 previous = draft_gte_read(22);
                    draft_gte_data(0, r_u32(normals + index[i]));
                    draft_gte_data(1, r_u32(normals + index[i] + 4u));
                    draft_gte_data(6, r_u32(records + 4u * i));
                    draft_gte_command(0xE80413u);
                    w_u32(packet + 4u + 8u * (i - 1u), previous);
                }
                w_u32(packet + 20u, draft_gte_read(22));
                if (!triangle)
                {
                    index[3] = (uint32)(sint32)(sint16)r_u16(records + 22u) * 8u;
                    draft_gte_data(0, r_u32(vertices + index[3]));
                    draft_gte_data(1, r_u32(vertices + index[3] + 4u));
                    draft_gte_command(0x180001u);
                    xy[0] = draft_gte_read(14);
                    draft_gte_data(0, r_u32(normals + index[3]));
                    draft_gte_data(1, r_u32(normals + index[3] + 4u));
                    draft_gte_data(6, r_u32(records + 12u));
                    draft_gte_command(0xE80413u);
                    w_u32(packet + 32u, xy[0]);
                    w_u32(packet + 28u, draft_gte_read(22));
                }
            }
            /* TODO: Preserve packet write timing during later integration */
            w_u32(packet, r_u32(tag) | (category == 4u ? 0x09000000u : category == 5u ? 0x0C000000u : triangle ? 0x06000000u : 0x08000000u));
            w_u32(tag, packet & 0xFFFFFFu);
            packet += category >= 4u ? 52u : triangle ? 28u : 36u;
        next_record:
            records += record_size[category];
        } while (remaining-- > 0);
        if (category < 5u)
        {
            kind = (uint32)(sint32)(sint16)r_u16(records);
            remaining = (sint16)r_u16(records + 2u) - 1;
            records += 4u;
        }
    }
    w_u32(0x80071680u, packet);
}
