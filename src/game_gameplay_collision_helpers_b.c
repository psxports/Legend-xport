#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_800475A8(uint32 collision)
{
    uint32 active = r_u32(collision + 20u), count;
    w_u32(collision + 16u, 0u);
    w_u32(collision + 128u, 0u);
    w_u16(collision + 144u, 0u);
    if (!active) return 0u;
    count = r_u16(0x80071688u);
    if (count >= 128u) return count + 1u;
    w_u16(0x80071688u, count + 1u);
    w_u32(0x800BF2C0u + 4u * count, collision);
    return 4u * count;
}
