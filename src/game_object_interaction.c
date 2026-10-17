#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80031088(uint32 position, uint32 angle, uint32 speed)
{
    uint32 result = angle;
    if ((uint16)speed)
    {
        w_u16(0x1F800020, 0);
        w_u16(0x1F800022, angle);
        w_u16(0x1F800024, 0);
        sub_8005D138(0x1F800020, 0x1F800000);
        w_u16(0x1F800020, 0);
        w_u16(0x1F800022, 0);
        w_u16(0x1F800024, speed);
        sub_8005CDD8(0x1F800000, 0x1F800020, 0x1F800028);
        w_u32(position, r_u32(position) + r_u32(0x1F800028));
        result = r_u32(position + 8) + r_u32(0x1F800030);
        w_u32(position + 8, result);
    }
    return result;
}

uint32 sub_80032360(uint32 position, uint32 proximity, uint32 range)
{
    uint32 i, player, distance, heading, result = 0;
    sint32 difference;
    for (i = 0; i < 2; ++i)
    {
        player = 0x800AFEC0 + 288 * i;
        if (!r_u8(player + 240))
            continue;
        distance = r_u32(proximity + 16 + 4 * i);
        if ((sint32)distance >= (sint32)range)
            continue;
        heading = sub_80046B84(r_u32(position) - r_u32(player), r_u32(position + 8) - r_u32(player + 8), distance);
        difference = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(player + 18) - heading));
        if (difference < 0)
            difference = -difference;
        if (difference < 1024)
        {
            result = 1;
            w_u16(player + 232, r_u16(player + 232) | 4);
        }
    }
    return result;
}

uint32 sub_80033170(uint32 position, uint32 proximity, uint32 range)
{
    uint32 i, player, distance, heading, animation;
    sint32 difference;
    for (i = 0; i < 2; ++i)
    {
        player = 0x800AFEC0 + 288 * i;
        if (!r_u8(player + 240) || r_u16(player + 214) != 41 || !(r_u16(player + 232) & 1))
            continue;
        distance = r_u32(proximity + 16 + 4 * i);
        if ((sint32)distance >= (sint32)range)
            continue;
        heading = sub_80046B84(r_u32(position) - r_u32(player), r_u32(position + 8) - r_u32(player + 8), distance);
        difference = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(player + 18) - heading));
        if (difference < 0)
            difference = -difference;
        if (difference < 1024)
        {
            animation = r_u16(player + 92);
            w_u16(player + 18, heading);
            if (animation == 32)
            {
                w_u16(player + 232, r_u16(player + 232) & 0xFFFE);
                return i + 1;
            }
        }
    }
    return 0;
}

uint32 sub_800327F0(uint32 pitch)
{
    uint32 voice = (uint16)sub_800448F4(), pan = (uint16)sub_80044F58(16000);
    return sub_8004486C(1, voice, 25, (uint16)pitch, pan, r_u16(0x80071A20));
}
