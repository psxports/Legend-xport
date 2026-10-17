#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80059C00(void)
{
    return sub_80059C50(0x8006A060);
}

uint32 sub_80059C28(void)
{
    return sub_80059C50(0x8006A080);
}

uint32 sub_80014194(void)
{
    uint8 location[8];
    uint32 selector, mode, position, state, offset;
    sub_80063C94(17, 0, draft_local_address(location, sizeof(location)));
    selector = r_u16(0x80071770);
    mode = r_u16(0x800715FC);
    position = r_u32(0x800715C4);
    state = r_u16(0x800717E0);
    offset = 4 * (uint32)(sint32)(sint16)selector;
    w_u32(0x80071984, r_u32(0x800AFCF0 + offset));
    w_u8(0x80071984, location[5]);
    w_u8(0x80071985, location[6]);
    w_u8(0x80071986, location[7]);
    w_u16(0x800716F4, selector);
    w_u16(0x800715A0, mode);
    w_u32(0x80071560, position);
    w_u16(0x8007177C, state);
    return offset;
}

uint32 sub_80014230(void)
{
    uint32 selector = r_u16(0x800716F4), mode = r_u16(0x800715A0);
    uint32 position = r_u32(0x80071560), state = r_u16(0x8007177C), result;
    w_u16(0x80071770, selector);
    w_u16(0x800715FC, mode);
    w_u32(0x800715C4, position);
    w_u16(0x800717E0, state);
    sub_80063C94(2, 0x80071984, 0);
    do
    {
        result = sub_80063C94(3, 0, 0);
    } while (!result);
    return result;
}

uint32 sub_80014B44(void)
{
    uint32 stage = r_u16(0x80071594), result;
    uint16 offset = 0;
    while (r_u8(0x800685B0 + offset) != stage)
        offset = (uint16)(offset + 2);
    result = r_u8(0x800685B1 + offset);
    w_u16(0x80071594, result);
    return result;
}
