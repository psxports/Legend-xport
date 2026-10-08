#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80032854(uint32 mesh, uint32 flags)
{
    uint32 channel, volume;
    flags &= 65535u;
    w_u32(0x1F800028u, 0u);
    w_u32(0x1F80002Cu, 5u);
    w_u32(0x1F800030u, 0u);
    sub_80022CC0(mesh + 8u, 0x1F800028u, 3u, 5u);
    sub_8004EC38(flags >> 4);
    channel = (uint16)sub_800448F4();
    volume = (uint16)sub_80044F58(10000u);
    return sub_8004486C(1u, channel, (flags & 15u) ? 43u : 1u,
                         (flags & 15u) ? 800u : 700u, volume, r_u16(0x80071A20u));
}
