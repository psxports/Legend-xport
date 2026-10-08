#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8005302C(uint32 actor)
{
    static const uint32 tables[9] = {
        0x80068B68, 0x8006902C, 0x80068C5C,
        0x80068E44, 0x80069120, 0x80068D50,
        0x80069214, 0x80068F38, 0x80069308
    };
    uint32 mode = r_u16(actor + 246), character = r_u8(actor + 212);
    uint32 record, count, mask, latch_mask, i;
    if (mode >= 9 || character >= 3) {
        /* TODO: Original invalid selector inherits an undefined saved register */
        record = draft_unknown_argument("sub_8005302C invalid table selector", 0);
    } else record = tables[mode] + 56 * character;
    for (;;) {
        count = r_u16(record);
        if (!count) return (uint32)(sint32)(sint16)count;
        mask = r_u16(record + 2);
        latch_mask = r_u16(record + 4);
        record += 6;
        for (i = 0; i < count; ++i, record += 6) {
            if ((uint32)r_u16(actor + 214) != (uint32)(sint32)(sint16)r_u16(record)) continue;
            sub_80052FF0(actor, mask, latch_mask);
            if ((sint16)r_u16(actor + 92) == (sint16)r_u16(record + 2)
                && r_u16(actor + 238) && !(r_u16(actor + 226) & 0xF000)) {
                uint32 result;
                sub_80052078(actor, 768, 10000);
                sub_800513CC(actor, r_u16(record + 4));
                result = r_u16(actor + 238) - 1;
                w_u16(actor + 238, result);
                return result;
            }
        }
    }
}
