#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 legend_player_reset(uint32 actor)
{
    uint32 fallback = 0u;
    /* TODO: Recover the incoming a2 carrier for callers with an invalid class */
    if (r_u16(actor + 246u) >= 9u)
        fallback = draft_unknown_argument("sub_800527C8", 2u);
    return sub_800527C8(actor, 0u, fallback);
}

uint32 sub_800527C8(uint32 actor, uint32 unused, uint32 fallback)
{
    static const uint16 effects[9] = {0, 12, 11, 13, 14, 15, 16, 17, 18};
    uint32 kind = r_u16(actor + 246u), effect, character, result;

    effect = kind < 9u ? effects[kind] : (uint16)fallback;
    w_u16(actor + 246u, 0u);
    if (effect)
        sub_800233BC(actor, actor, effect, r_u16(actor + 248u));
    character = 2u * r_u8(actor + 212u);
    sub_8001A2FC(r_u16(0x800693FCu + character), r_u32(r_u32(actor + 52u)) + 1512u);
    sub_8001A2FC(r_u16(0x8006946Cu + character), r_u32(r_u32(actor + 52u)) + 1344u);
    result = sub_8001A2FC(r_u16(0x80069434u + character), r_u32(r_u32(actor + 52u)) + 1176u);
    w_u8(actor + 281u, 0u);
    return result;
}
