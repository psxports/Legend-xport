#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80040D64(uint32 actor)
{
    uint32 index = (uint16)(r_u8(actor + 240) - 1), slot = 0x80071648 + 4 * index;
    uint32 target = r_u32(slot), result = 0x80071648;
    if (target)
    {
        result = 9 * index;
        if ((sint32)r_u32(0x800C5D24 + 32 * index) < 2500)
        {
            w_u32(slot, 0);
            w_u32(actor + 200, target);
            w_u32(target + 44, 0x800AFEC0 + 288 * index);
            result = sub_8005915C(target, 6);
            w_u16(target + 242, 0);
        }
    }
    return result;
}

uint32 sub_800410B8(uint32 actor)
{
    uint32 index = (uint16)(r_u8(actor + 240) - 1), slot = 0x80071620 + 4 * index;
    uint32 target = r_u32(slot), result = 0x80071620;
    if (target)
    {
        result = 9 * index;
        if ((sint32)r_u32(0x800C1B54 + 32 * index) < 2500)
        {
            w_u32(slot, 0);
            w_u32(actor + 200, target);
            w_u32(target + 44, 0x800AFEC0 + 288 * index);
            result = sub_8005915C(target, 7);
            w_u16(target + 242, 0);
        }
    }
    return result;
}
