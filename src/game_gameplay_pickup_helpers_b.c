#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

void sub_80033CD8(uint32 actor, uint32 player, uint32 kind, uint32 count)
{
    static const uint16 score[4] = {400, 200, 600, 300};
    static const uint8 weapon[8] = {2, 1, 3, 4, 5, 6, 7, 8};
    uint32 address, value;
    player &= 65535u;
    kind &= 65535u;
    if (kind <= 3u)
        sub_80052558(player, kind ? 4u : 8u);
    else if (kind <= 6u)
        sub_8005267C(player, kind == 4u ? 150u : kind == 5u ? 250u : 500u);
    else if (kind <= 10u)
    {
        address = 0x800715F4u + 4u * player;
        w_u32(address, r_u32(address) + score[kind - 7u]);
    }
    else if (kind <= 18u)
        sub_800528E8(actor, weapon[kind - 11u], (uint16)count);
    else if (kind == 19u)
    {
        value = (r_u8(actor + 280u) + 1u) & 255u;
        w_u8(actor + 280u, value >= 10u ? 9u : value);
    }
    else if (kind == 20u)
    {
        address = 0x80071788u + 4u * player;
        w_u32(address, r_u32(address) + 1u);
    }
}

uint32 sub_80033E98(uint32 actor, uint32 distances, uint32 limit)
{
    uint32 i, player, distance, angle, mesh;
    for (i = 0u; i < 2u; ++i)
    {
        player = 0x800AFEC0u + 288u * i;
        if (!r_u8(player + 240u) || r_u16(player + 214u) != 3u || !(r_u16(player + 232u) & 1u))
            continue;
        distance = r_u32(distances + 16u + 4u * i);
        if ((sint32)distance >= (sint32)limit)
            continue;
        mesh = r_u32(actor);
        angle = sub_80046B84(r_u32(mesh + 8u) - r_u32(player), r_u32(mesh + 16u) - r_u32(player + 8u), distance);
        sub_80046D0C((uint32)(sint32)(sint16)(r_u16(player + 18u) - angle));
        w_u16(player + 18u, angle);
        if (r_u16(player + 92u) != 8u)
            continue;
        sub_80033CD8(player, i, r_u16(actor + 102u), r_u16(actor + 104u));
        w_u16(player + 232u, r_u16(player + 232u) & 65534u);
        sub_800502F4(r_u8(player + 212u));
        sub_800502F4(r_u16(actor + 102u) + 3u);
        return i + 1u;
    }
    return 0u;
}

uint32 sub_80032D0C(uint32 region, uint32 unused, uint32 fallback)
{
    uint32 i, difference = fallback, best = 32000u;

    for (i = 0u; i < 2u; ++i)
    {
        if (!r_u8(0x800AFFB0u + 288u * i))
            continue;
        difference = (uint32)((sint32)(sint16)r_u16(0x800AFFCCu + 288u * i) - (sint32)(sint16)region);
        if ((sint32)difference < 0)
            difference = 0u - difference;
        if ((sint16)difference < (sint16)best)
            best = difference;
    }
    /* The original returns the last active difference rather than the minimum */
    return (uint32)(sint32)(sint16)difference;
}

uint32 sub_80032D9C(uint32 region, uint32 threshold, uint32 fallback)
{
    uint32 kind = r_u8(r_u32(0x80071704u) + 14u * (uint16)region + 9u);
    return (sint16)sub_80032D0C(kind, threshold, fallback) >= (sint16)threshold;
}

uint32 legend_pickup_region_check(uint32 region, uint32 threshold)
{
    uint32 fallback = 0u;
    /* TODO: Recover the incoming a2 carrier when both players are inactive */
    if (!r_u8(0x800AFFB0u) && !r_u8(0x800B00D0u))
        fallback = draft_unknown_argument("sub_80032D9C", 2u);
    return sub_80032D9C(region, threshold, fallback);
}
