#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8003F8D0(uint32 actor)
{
    uint32 choice = sub_80011B8C() & 3u;
    return sub_8003F814((uint16)actor, choice);
}

uint32 sub_8003F904(uint32 actor)
{
    return sub_8003F814((uint16)actor, 0u);
}

uint32 sub_8003F928(uint32 actor)
{
    return sub_8003F814((uint16)actor, 4u);
}

uint32 sub_8003F94C(uint32 actor)
{
    return sub_8003F814((uint16)actor, 5u);
}

uint32 sub_8003F970(uint32 actor)
{
    return sub_8003F814((uint16)actor, 6u);
}

uint32 sub_8003F9F0(void)
{
    uint32 sound = (sub_80011B8C() & 127u) >= 65u ? 27u : 28u;
    uint32 channel = (uint16)sub_800448F4();
    uint32 volume = (uint16)sub_80044F58(32000u);
    return sub_8004486C(1u, channel, sound, 1024u, volume, r_u16(0x80071A20u));
}
