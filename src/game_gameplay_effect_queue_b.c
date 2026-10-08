#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8002B178(uint32 position, uint32 first, uint32 second, uint32 third)
{
    uint32 slot, entry, words[4], i;
    for (slot = 0u; slot < 4u; ++slot)
    {
        entry = 0x800BD3A8u + 24u * slot;
        if (r_u16(entry + 22u)) continue;
        w_u16(entry + 22u, 1u);
        for (i = 0u; i < 4u; ++i) words[i] = r_u32(position + 4u * i);
        for (i = 0u; i < 4u; ++i) w_u32(entry + 4u * i, words[i]);
        w_u16(entry + 16u, first);
        w_u16(entry + 18u, second);
        w_u16(entry + 20u, third);
        w_u8(0x80071730u, 1u);
        return entry;
    }
    return 4u;
}
