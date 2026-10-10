#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_800325CC(uint32 state, uint32 position, uint32 floor_height, uint32 effects)
{
    uint32 velocity = r_u32(state) + (uint32)(sint32)(sint16)r_u16(state + 4u);
    uint32 height, result, volume, channel;
    w_u16(state + 6u, 0);
    w_u32(state, velocity);
    height = r_u32(position + 4u) + (uint32)((sint32)velocity >> 3);
    w_u32(position + 4u, height);
    result = (uint32)((sint32)height < (sint32)floor_height);
    if ((sint32)r_u32(state) <= 0 || result)
        return result;
    w_u32(position + 4u, floor_height);
    if ((sint32)r_u32(state) >= 2049 && (uint16)effects)
    {
        w_u32(0x1F80002Cu, 5);
        w_u32(0x1F800028u, 0);
        w_u32(0x1F800030u, 0);
        sub_80022F08(position, 0x1F800028u, 5u, 5u, 3u);
        sub_8004EC38(4u);
        volume = r_u32(state) << 2;
        if ((sint32)volume >= 16001)
            volume = 16000u;
        channel = (uint16)sub_800448F4();
        volume = (uint16)sub_80044F58(volume);
        sub_8004486C(1u, channel, 1u, 800u, volume, r_u16(0x80071A20u));
    }
    w_u32(state, 0);
    w_u16(state + 6u, 1);
    return 1u;
}

uint32 sub_800324A0(uint32 position, uint32 distances, uint32 threshold, uint32 flags)
{
    uint32 index, result = 0;
    for (index = 0; index < 2u; ++index)
    {
        uint32 player = 0x800AFEC0u + 288u * index;
        uint32 distance, heading, angle;
        if (!r_u8(player + 240u))
            continue;
        distance = r_u32(distances + 16u + 4u * index);
        if ((sint32)distance >= (sint32)threshold)
            continue;
        heading = sub_80046B84(r_u32(position) - r_u32(player), r_u32(position + 8u) - r_u32(player + 8u), distance);
        angle = (uint32)(sint32)(sint16)(r_u16(player + 18u) - heading);
        sub_80046D0C(angle);
        result |= 1u;
        w_u16(player + 232u, r_u16(player + 232u) | flags);
    }
    return result;
}

uint32 sub_80052558(uint32 player_index, uint32 amount)
{
    uint32 address = 0x800AFF92u + 288u * (uint16)player_index;
    w_u16(address, r_u16(address) + amount);
    if (r_u16(address) >= 73u)
        w_u16(address, 72u);
    return 72u;
}
