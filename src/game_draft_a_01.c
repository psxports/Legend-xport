#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdlib.h>

/* Unverified draft; integration deferred */

/* TODO: Missing boundaries and stack-switch adapters require fail-fast during integration */
extern uint32 xport_draft_switch_stack(uint32 stack);
extern uint32 draft_sdk_sqrt(uint32 value);
extern uint32 draft_sdk_cd_mix(uint8 *buffer);
extern uint32 draft_sdk_open_event(uint32 descriptor);
extern uint32 draft_sdk_enable_event(uint32 descriptor);
extern uint32 draft_sdk_spu_write(uint32 address, uint32 size, uint32 mode);
extern void nullsub_2(void);

uint32 sub_8005C008(uint32 a1)
{
    FUNCTION_MARKER(0x8005C008u, "SLES_007.30");
    /* Retain the guest stack carrier while native C owns call frames */
    return xport_draft_switch_stack(a1);
}

void sub_800471D8(void)
{
    FUNCTION_MARKER(0x800471D8u, "SLES_007.30");
    w_u16(0x80071758u, 0u);
}

uint32 sub_80044A40(void)
{
    FUNCTION_MARKER(0x80044A40u, "SLES_007.30");
    uint32 count = 1u;
    while (count < 50u) ++count;
    return 0u;
}

uint32 sub_8004DA68(uint32 a1)
{
    FUNCTION_MARKER(0x8004DA68u, "SLES_007.30");
    return r_u32(0x800C1CFCu + 4u * (a1 & 0xFFFFu));
}

uint32 sub_80063DE0(uint8 *buffer)
{
    FUNCTION_MARKER(0x80063DE0u, "SLES_007.30");
    draft_sdk_cd_mix(buffer);
    return 1u;
}

uint32 sub_8002F0D4(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x8002F0D4u, "SLES_007.30");
    uint32 count;
    for (count = a2; count != 0u; --count) w_u8(a1++, 0u);
    return count;
}

uint32 sub_80011A70(uint32 a1)
{
    FUNCTION_MARKER(0x80011A70u, "SLES_007.30");
    uint32 result;
    if (a1 & 3u) a1 += 4u - (a1 & 3u);
    result = r_u32(0x800718BCu) - a1;
    w_u32(0x800718BCu, result);
    return result;
}

uint32 sub_80059BD8(void)
{
    FUNCTION_MARKER(0x80059BD8u, "SLES_007.30");
    return sub_80059C50(0x8006A040u);
}

uint32 sub_80048180(void)
{
    FUNCTION_MARKER(0x80048180u, "SLES_007.30");
    draft_sdk_open_event(0xF2000001u);
    return draft_sdk_enable_event(0xF2000001u);
}

uint32 sub_8004DA38(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x8004DA38u, "SLES_007.30");
    uint32 result = a3, remaining = a3;
    if (remaining != 0u)
    {
        do { result = r_u8(a1++); w_u8(a2++, (uint8)result); } while (--remaining != 0u);
    }
    return result;
}

uint32 sub_80013F80(void)
{
    FUNCTION_MARKER(0x80013F80u, "SLES_007.30");
    uint32 result;
    do { result = CdControlB(9u, NULL, NULL); } while (result == 0u);
    w_u8(0x80071540u, 0u);
    return result;
}

uint32 sub_80018F6C(uint32 a1)
{
    FUNCTION_MARKER(0x80018F6Cu, "SLES_007.30");
    uint16 first = r_u16(a1 + 20u), second = r_u16(a1 + 18u);
    uint8 c0 = r_u8(a1 + 8u), c1 = r_u8(a1 + 9u);
    uint32 result = r_u8(a1 + 12u);
    uint8 d1 = r_u8(a1 + 13u);
    w_u16(a1 + 18u, first);
    w_u8(a1 + 8u, result); w_u8(a1 + 9u, d1);
    w_u16(a1 + 20u, second);
    w_u8(a1 + 12u, c0); w_u8(a1 + 13u, c1);
    return result;
}

uint32 sub_80013FB4(void)
{
    FUNCTION_MARKER(0x80013FB4u, "SLES_007.30");
    uint8 volume[8];
    volume[0] = 0xE6u; volume[1] = 0u; volume[2] = 0xE6u; volume[3] = 0u;
    return sub_80063DE0(volume);
}

uint32 sub_8001F8A8(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x8001F8A8u, "SLES_007.30");
    return draft_sdk_sqrt(a1 * a1 + a2 * a2);
}

uint32 sub_800474F4(void)
{
    FUNCTION_MARKER(0x800474F4u, "SLES_007.30");
    uint32 result = sub_80011A98(152u);
    w_u16(result + 140u, 0xFFFFu);
    w_u32(result + 128u, 0u); w_u32(result + 20u, 0u); w_u32(result + 124u, 0u);
    w_u16(result + 142u, 1u); w_u16(result + 144u, 0u);
    return result;
}

uint32 sub_8001A2BC(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5)
{
    FUNCTION_MARKER(0x8001A2BCu, "SLES_007.30");
    uint32 result;
    w_u32(a2 + 96u, a1);
    while ((result = r_u32(a1 + 92u)) != 0u) a1 = r_u32(a1 + 92u);
    w_u16(a2, a3); w_u16(a2 + 2u, a4);
    w_u16(a2 + 4u, a5);
    w_u32(a1 + 92u, a2);
    return result;
}

uint32 sub_80018EF4(uint32 a1)
{
    FUNCTION_MARKER(0x80018EF4u, "SLES_007.30");
    uint16 next = r_u16(a1 + 20u), previous = r_u16(a1 + 18u);
    uint8 c0 = r_u8(a1 + 4u), c1 = r_u8(a1 + 5u), c2 = r_u8(a1 + 6u);
    uint32 result = r_u8(a1 + 8u);
    uint8 d1 = r_u8(a1 + 9u), d2 = r_u8(a1 + 10u);
    w_u16(a1 + 18u, next);
    w_u8(a1 + 4u, result); w_u8(a1 + 5u, d1); w_u8(a1 + 6u, d2);
    w_u16(a1 + 20u, previous);
    w_u8(a1 + 8u, c0); w_u8(a1 + 9u, c1); w_u8(a1 + 10u, c2);
    return result;
}

uint32 sub_8001EE58(uint32 a1)
{
    FUNCTION_MARKER(0x8001EE58u, "SLES_007.30");
    sub_80011AF8(r_u32(a1));
    sub_80011AF8(r_u32(a1 + 4u));
    return sub_80011AF8(a1);
}

uint32 sub_80011D78(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x80011D78u, "SLES_007.30");
    uint32 data = r_u32(0x800715ACu);
    uint32 pixels = data + 32u * r_u16(data) + ((a1 & 0xFFFFu) << 9) + 4u;
    LoadImagePSX((PSX_RECT *)psx_addr(a2, 8u), (uint32 *)psx_addr(pixels, 1u));
    return DrawSync(0);
}

uint32 sub_80057B74(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x80057B74u, "SLES_007.30");
    uint32 count = r_u16(a1 + 2u), cursor = a1 + 4u;
    sint16 target = (sint16)a2;
    while (count != 0u)
    {
        if ((sint16)r_u16(cursor) >= target) break;
        --count; cursor += 2u * a3;
        if ((uint16)count == 0u) break;
    }
    return cursor;
}

uint32 sub_8001EE9C(void)
{
    FUNCTION_MARKER(0x8001EE9Cu, "SLES_007.30");
    uint32 index = 0u;
    do
    {
        uint32 address = 0x800AFAD8u + 8u * (uint16)index++;
        w_u16(address + 4u, 100u); w_u16(address + 2u, 100u); w_u16(address, 100u);
    } while ((uint16)index < 64u);
    return 0u;
}

uint32 sub_800447B0(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x800447B0u, "SLES_007.30");
    uint32 remaining = a2 - 1u;
    /* TODO: A zero count leaves the original return carrier unspecified */
    uint32 result = 0u;
    if ((uint16)a2 != 0u)
    {
        do
        {
            w_u32(0x800BED30u + 4u * (uint16)a1++, 0xFFFFFFFFu);
            result = (uint16)remaining; remaining += 0xFFFFu;
        } while (result != 0u);
    }
    return result;
}

uint32 sub_8004E4C8(uint32 index)
{
    FUNCTION_MARKER(0x8004E4C8u, "SLES_007.30");
    uint32 result = r_u32(0x80071588u);
    if (index != result)
    {
        sub_8004E0A0(index & 0xFFFFu);
        result = sub_8004DD18(r_u32(0x8005B0F4u), r_u32(0x8007157Cu));
        w_u32(0x80071588u, index);
    }
    return result;
}

uint32 sub_80062398(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x80062398u, "SLES_007.30");
    uint32 size = a2 > 0x7EFF0u ? 0x7EFF0u : a2;
    draft_sdk_spu_write(a1, size, a3);
    if (r_u32(0x8006FE7Cu) == 0u) w_u32(0x8006FE78u, 0u);
    return size;
}

uint32 sub_800142CC(void)
{
    FUNCTION_MARKER(0x800142CCu, "SLES_007.30");
    uint32 size = sub_8004DA68(2u);
    uint32 data = sub_80011A98(size);
    uint32 result;
    w_u32(0x800715ACu, data);
    result = sub_8004E0A0(2u);
    if ((sint32)result >= 0)
    {
        result = sub_8004DD18(r_u32(0x800715ACu), size);
        nullsub_2();
        return result;
    }
    return result;
}

uint32 sub_8001F8E0(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x8001F8E0u, "SLES_007.30");
    sint16 delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(a2 - a1));
    sint32 step = delta >> (a3 & 31u);
    if (step == 0 && delta != 0) step = delta < 0 ? -1 : 1;
    return (a1 + (uint16)step) & 0xFFFu;
}

uint32 sub_800211D8(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x800211D8u, "SLES_007.30");
    sint16 delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(a2 - a1));
    sint32 step = delta >> 4;
    if (step == 0 && delta != 0) step = delta < 0 ? -1 : 1;
    return (uint32)(sint32)(sint16)(a1 + (uint32)step);
}

uint32 sub_8004ED48(uint32 a1)
{
    FUNCTION_MARKER(0x8004ED48u, "SLES_007.30");
    sint16 width = 0;
    uint32 cursor = a1 + 1u;
    if (r_u8(a1) != 0u)
    {
        do { width = (sint16)(width + 16); } while (r_u8(cursor++) != 0u);
    }
    return (uint32)(sint32)width;
}

uint32 sub_80027094(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5)
{
    FUNCTION_MARKER(0x80027094u, "SLES_007.30");
    uint32 object = sub_80032EF0();
    if (object != 0u)
    {
        w_u32(object + 8u, 18u); w_u16(object + 12u, a1); w_u16(object + 14u, a2);
        w_u16(object + 16u, 0u); w_u16(object + 20u, a3); w_u16(object + 22u, a4);
        /* TODO: Pseudocode a5 is the first stack argument in MIPS */
        w_u16(object + 24u, a5);
    }
    return 18u;
}

uint32 sub_800210E8(void)
{
    FUNCTION_MARKER(0x800210E8u, "SLES_007.30");
    uint32 result;
    result = sub_80020F8C(r_u32(0x800BC0A4u), r_u32(0x800BC0B4u), 0x800BC084u); w_u32(0x800BC0A4u, result);
    result = sub_80020F8C(r_u32(0x800BC0A8u), r_u32(0x800BC0B8u), 0x800BC088u); w_u32(0x800BC0A8u, result);
    result = sub_80020F8C(r_u32(0x800BC0ACu), r_u32(0x800BC0BCu), 0x800BC08Cu); w_u32(0x800BC0ACu, result);
    return result;
}

uint32 sub_800139C0(void)
{
    FUNCTION_MARKER(0x800139C0u, "SLES_007.30");
    uint32 buffer = r_u16(0x800715E8u);
    w_u32(0x800719CCu, 92u * (1u - buffer) + 0x800BF1D0u);
    w_u32(0x800719D4u, 20u * buffer + 0x800BF288u);
    w_u32(0x8007184Cu, 10000u * buffer + 0x800B71A4u);
    w_u32(0x80071680u, 120000u * buffer + 0x800740DCu);
    return 0x800740DCu;
}

uint32 sub_80012F20(uint32 a1)
{
    FUNCTION_MARKER(0x80012F20u, "SLES_007.30");
    uint16 index = 0u;
    sint16 remaining = (sint16)a1;
    uint32 result;
    while (index < r_u16(0x80071600u))
    {
        uint32 slot = index++;
        if (r_u8(0x800C020Cu + slot) == 0u && remaining != 0)
        { --remaining; sub_80012CB0(slot); }
    }
    do { result = (uint16)sub_80012DD4(); } while (result != 0u);
    return result;
}

uint32 sub_8004E0A0(uint32 a1)
{
    FUNCTION_MARKER(0x8004E0A0u, "SLES_007.30");
    uint32 index = a1 & 0xFFFFu;
    sint32 offset = (sint32)r_u32(0x800C5D68u + 4u * index);
    sint32 previous = (sint32)r_u32(0x800717E8u);
    if (offset >= previous) offset = (sint32)((uint32)offset - (uint32)previous);
    else sub_8004DCAC();
    w_u32(0x8007157Cu, r_u32(0x800C1CFCu + 4u * index));
    sub_8004DF80((uint32)offset);
    return 1u;
}

uint32 sub_8001A348(uint32 a1)
{
    FUNCTION_MARKER(0x8001A348u, "SLES_007.30");
    sub_8002F0D4(a1, 168u);
    w_u32(a1 + 80u, 0u); w_u32(a1 + 92u, 0u); w_u32(a1 + 96u, 0u);
    w_u16(a1, 0u); w_u16(a1 + 2u, 0u); w_u16(a1 + 4u, 0u);
    w_u32(a1 + 16u, 0u); w_u32(a1 + 12u, 0u); w_u32(a1 + 8u, 0u);
    w_u16(a1 + 28u, 0u); w_u16(a1 + 26u, 0u); w_u16(a1 + 24u, 0u);
    w_u16(a1 + 86u, 0u); w_u16(a1 + 84u, 0u); w_u16(a1 + 88u, 1u); w_u16(a1 + 90u, 1u);
    w_u32(a1 + 164u, 0u);
    return 1u;
}

uint32 sub_8001ED84(uint32 a1)
{
    FUNCTION_MARKER(0x8001ED84u, "SLES_007.30");
    uint16 count = (uint16)(a1 + 1u), index = 0u;
    uint32 header = sub_80011A98(12u);
    uint32 objects = sub_80011A98(168u * count);
    while (index < count)
    {
        uint32 object = objects + 168u * index++;
        sub_8001A348(object); w_u16(object + 86u, 1u);
    }
    w_u32(header, objects); w_u16(header + 8u, count);
    return header;
}

/* TODO: External game and SDK dependencies await fail-fast adapters */
extern uint32 draft_boundary_8004C020(uint32 slot, uint32 *argument);
extern uint32 draft_boundary_8004C0DC(uint32 slot, uint32 state, uint32 argument);
extern uint32 draft_boundary_80066C88(uint32 *data, uint32 *header);

uint32 sub_80044800(void)
{
    FUNCTION_MARKER(0x80044800u, "SLES_007.30");
    uint32 index = 0u;
    do
    {
        uint32 slot = (uint16)index++;
        w_u8(0x800AEEB0u + slot, 0u);
        w_u16(0x800AF028u + 12u * slot, 0u);
    } while ((uint16)index < 24u);
    w_u8(0x800AEEB0u, 1u); w_u8(0x800AEEB1u, 1u);
    w_u16(0x80071628u, 0u); w_u16(0x800719A4u, 0u);
    return 1u;
}

uint32 sub_80014A6C(void)
{
    FUNCTION_MARKER(0x80014A6Cu, "SLES_007.30");
    uint32 level = r_u16(0x80071594u), image;
    switch (level)
    {
    case 0u: case 1u: case 2u: image = 154u; break;
    case 3u: case 4u: case 5u: case 6u: image = 160u; break;
    case 7u: case 22u: case 23u: image = 162u; break;
    case 8u: case 9u: case 10u: case 11u: image = 168u; break;
    case 12u: case 13u: case 14u: case 15u: image = 174u; break;
    case 16u: case 17u: case 18u: case 19u: case 20u: case 21u: image = 182u; break;
    default:
        /* TODO: Default retains an incoming return carrier */
        return draft_unknown_return("sub_80014A6C");
    }
    return sub_8004E4C8(image);
}

uint32 sub_8004C720(void)
{
    FUNCTION_MARKER(0x8004C720u, "SLES_007.30");
    uint32 index = 0u, argument;
    do
    {
        uint32 slot = (uint16)index;
        if (r_u8(0x80071768u + slot) == 1u)
        {
            /* TODO: Resolve the local output argument ABI during integration */
            uint32 result = draft_boundary_8004C020(slot, &argument) & 0xFFu;
            if (result != 0u) draft_boundary_8004C0DC(slot, result, argument);
            w_u8(0x80071768u + slot, 2u);
        }
        ++index;
    } while ((uint16)index < 2u);
    return 0u;
}

uint32 sub_80046278(uint32 a1)
{
    FUNCTION_MARKER(0x80046278u, "SLES_007.30");
    uint32 red = 16u, green = 16u, blue = 16u;
    a1 &= 0xFFFFu;
    if (a1 != 0xFFFFu)
    {
        uint32 color = r_u16(r_u32(0x80071704u) + 14u * a1 + 10u);
        w_u16(0x800716E4u, (color & 0x8000u) != 0u);
        red = (color & 0x7FFFu) >> 10;
        green = (color >> 5) & 31u;
        blue = color & 31u;
    }
    w_u16(0x80071858u, 8u * red - 128u);
    w_u16(0x8007185Au, 8u * green - 128u);
    w_u16(0x8007185Cu, 8u * blue - 128u);
    return 8u * blue - 128u;
}

uint32 sub_80047640(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x80047640u, "SLES_007.30");
    uint32 absolute;
    absolute = (sint32)a1 < 0 ? 0u - a1 : a1;
    if ((sint32)absolute >= 12001) a1 = 12000u;
    absolute = (sint32)a2 < 0 ? 0u - a2 : a2;
    if ((sint32)absolute >= 12001) a2 = 12000u;
    absolute = (sint32)a3 < 0 ? 0u - a3 : a3;
    if ((sint32)absolute >= 12001) a3 = 12000u;
    if ((sint32)a1 < 12000 || (sint32)a3 < 12000 || (sint32)a2 < 12000)
        return draft_sdk_sqrt(a1 * a1 + a3 * a3 + a2 * a2);
    return 24000u;
}

uint32 sub_8005A67C(void)
{
    FUNCTION_MARKER(0x8005A67Cu, "SLES_007.30");
    uint32 remaining = 0x7FFFFFu, offset, result;
    if (r_u16(0x80071A8Au) == 0u)
    {
        while (remaining != 0u && r_u16(0x80071A8Au) == 0u) --remaining;
    }
    w_u16(0x80071A8Au, 0u);
    w_u16(0x80071A8Cu, r_u16(0x80071A8Cu) ^ 1u);
    offset = (uint32)((sint32)((uint32)r_u16(0x80071A8Cu) << 16) >> 13);
    w_u16(0x80071A80u, r_u16(0x80071A70u + offset));
    offset = (uint32)((sint32)((uint32)r_u16(0x80071A8Cu) << 16) >> 13);
    result = r_u16(0x80071A72u + offset);
    w_u16(0x80071A82u, result);
    return result;
}

uint32 sub_800513CC(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x800513CCu, "SLES_007.30");
    uint32 kind = r_u16(a1 + 246u), offset;
    w_u16(a1 + 214u, a2);
    switch (kind)
    {
    case 1u: a2 += 207u; break;
    case 2u: a2 += 51u; break;
    case 3u: a2 += 129u; break;
    case 4u: a2 += 246u; break;
    case 5u: a2 += 90u; break;
    case 6u: a2 += 285u; break;
    case 7u: a2 += 168u; break;
    case 8u: a2 += 324u; break;
    default: break;
    }
    offset = 2u * (uint16)(2u * a2);
    w_u16(a1 + 216u, r_u16(0x800694A4u + offset));
    return sub_80057A14(a1 + 76u, r_u16(0x800694A6u + offset));
}

void sub_800140DC(void)
{
    FUNCTION_MARKER(0x800140DCu, "SLES_007.30");
    uint8 position[8], result[8];
    uint32 sector, remaining;
    if (r_u8(0x80071540u) == 0u || (r_u16(0x800719D0u) & 31u) != 31u) return;
    CdControlB(17u, NULL, result);
    position[0] = result[5]; position[1] = result[6]; position[2] = result[7];
    sector = sub_80063F88(position);
    if ((sint32)sector < (sint32)r_u32(0x800715C4u)) return;
    remaining = r_u16(0x800717E0u);
    if (remaining != 0xFFFFu) w_u16(0x800717E0u, (uint16)(remaining - 1u));
    remaining = r_u16(0x800717E0u);
    if (remaining != 0u)
        sub_80013FE8((uint32)(sint32)(sint16)r_u16(0x80071770u), r_u16(0x800715FCu), remaining);
    else sub_80013F80();
}

uint32 sub_80030678(void)
{
    FUNCTION_MARKER(0x80030678u, "SLES_007.30");
    uint32 object = sub_80011A98(3000u), tail = object + 36u;
    uint16 index = 0u;
    w_u32(0x80071530u, object);
    do
    {
        uint32 size;
        ++index;
        w_u32(object, (uint32)randPSX() & 511u);
        w_u32(tail - 32u, (uint32)randPSX() & 511u);
        w_u32(tail - 28u, (uint32)randPSX() & 511u);
        w_u16(tail - 20u, 0xFFFEu); w_u16(tail - 18u, 0xFFB0u);
        object += 40u;
        w_u16(tail - 16u, ((uint32)randPSX() & 7u) + 3u);
        w_u16(tail - 12u, 2u);
        size = r_u16(tail - 16u);
        w_u16(tail - 10u, 0xFFB0u); w_u16(tail - 4u, 0u); w_u16(tail - 2u, 0u);
        w_u16(tail - 8u, size); w_u16(tail, size);
        tail += 40u;
    } while (index < 75u);
    return 0u;
}

uint32 sub_8005A530(void)
{
    FUNCTION_MARKER(0x8005A530u, "SLES_007.30");
    uint32 remaining = 0x800000u, data, header, frame;
    while (1)
    {
        /* StGetNext writes the stream and header guest addresses */
        uint32 ready = draft_boundary_80066C88(&data, &header);
        --remaining;
        if (ready == 0u) break;
        if (remaining == 0u) return 0u;
    }
    w_u32(0x80071A6Cu, r_u32(0x80071A6Cu) + 1u);
    frame = r_u32(header + 8u);
    if (r_u32(0x80071A64u) >= frame && frame >= r_u32(0x80071A6Cu)
        && r_u16(header + 16u) == r_u16(0x80071A60u)
        && r_u16(header + 18u) == r_u16(0x80071A62u)) return data;
    w_u16(0x80071A88u, 1u);
    return data;
}

