#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80053A28(uint32 position, uint32 effect)
{
    uint32 channel, volume;
    w_u32(0x1F800028u, 0u);
    w_u32(0x1F80002Cu, 5u);
    w_u32(0x1F800030u, 0u);
    sub_80022CC0(position, 0x1F800028u, 3u, 5u);
    sub_8004EC38((uint16)effect >> 4);
    channel = (uint16)sub_800448F4();
    volume = (uint16)sub_80044F58(10000u);
    return sub_8004486C(1u, channel, (effect & 15u) ? 43u : 1u, 800u, volume, r_u16(0x80071A20u));
}

uint32 sub_800539C0(uint32 actor, uint32 bone)
{
    uint32 mode = r_u16(actor + 246u);
    if (mode == 7u)
        return (uint32)((uint16)(bone - 8u) < 2u);
    if ((mode >= 1u && mode <= 6u) || mode == 8u)
        return (uint32)((uint16)bone == 9u);
    return 0u;
}
