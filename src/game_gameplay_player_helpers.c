#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_800525B8(uint32 player, uint32 digit, uint32 amount)
{
    uint32 remaining = amount, address;
    if (!remaining)
        return 0u;
    address = 0x800AFFBAu + 288u * (uint16)player + (uint16)digit;
    do
    {
        w_u8(address, r_u8(address) + 1u);
        if (r_u8(address) == 58u)
        {
            w_u8(address, 48u);
            if ((uint16)digit)
                sub_800525B8((uint16)player, (uint16)(digit - 1u), 1u);
        }
        --remaining;
    } while (remaining);
    return 0u;
}

uint32 sub_8005267C(uint32 player, uint32 amount)
{
    sint32 value = (sint32)amount, divisor = 100000;
    uint32 digit;
    for (digit = 0u; digit < 6u; ++digit)
    {
        sint32 quotient = value / divisor;
        if (quotient)
        {
            sub_800525B8((uint16)player, digit, (uint32)quotient);
            value = (sint32)((uint32)value - (uint32)quotient * (uint32)divisor);
        }
        divisor /= 10;
    }
    return 0u;
}

uint32 sub_80051208(uint32 player)
{
    uint32 mesh = r_u32(r_u32(0x800AFEF4u + 288u * (uint16)player));
    uint32 i, result = 0u;
    for (i = 0u; i < 3u; ++i)
    {
        uint32 sum = r_u32(mesh + 0x548u + 4u * i) + r_u32(mesh + 0x5F0u + 4u * i);
        result = (uint32)((sint32)sum >> 1);
        w_u32(0x1F800028u + 4u * i, result);
    }
    return result;
}

uint32 sub_80051B14(uint32 motion, uint32 position, uint32 floor, uint32 effects)
{
    sint32 acceleration = (sint16)r_u16(motion + 4u);
    uint32 velocity = r_u32(motion) + (uint32)(acceleration / 4);
    uint32 height, result;
    w_u16(motion + 6u, 0u);
    w_u32(motion, velocity);
    height = r_u32(position + 4u) + (uint32)((sint32)velocity >> 3);
    w_u32(position + 4u, height);
    result = (sint32)height < (sint32)floor;
    if ((sint32)r_u32(motion) > 0 && !result)
    {
        w_u32(position + 4u, floor);
        if ((sint32)r_u32(motion) >= 1025 && (uint16)effects)
        {
            uint32 force, channel, volume;
            w_u32(0x1F80002Cu, 5u);
            w_u32(0x1F800028u, 0u);
            w_u32(0x1F800030u, 0u);
            sub_80022F08(position, 0x1F800028u, 5u, 5u, 3u);
            sub_8004EC38(4u);
            force = r_u32(motion) << 2;
            if ((sint32)force >= 16001)
                force = 16000u;
            channel = (uint16)sub_800448F4();
            volume = (uint16)sub_80044F58(force);
            sub_8004486C(1u, channel, 1u, 800u, volume, r_u16(0x80071A20u));
        }
        result = 1u;
        w_u32(motion, 0u);
        w_u16(motion + 6u, 1u);
    }
    return result;
}
