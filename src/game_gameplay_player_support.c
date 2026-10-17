#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_800516E8(uint32 player, uint32 region)
{
    uint16 angles[2];
    uint32 kind;
    sint32 speed;
    region = (uint16)region;
    if (region == 0xFFFF)
        return 0xFFFF;
    kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
    angles[1] = (r_u16(r_u32(0x800716D0) + 2 * kind) + 2048) & 4095;
    speed = (sint16)r_u16(0x80071804) / 5;
    return sub_80051550(player, (uint32)speed, draft_local_address(angles, sizeof(angles)));
}

static uint32 player_face_target(uint32 player, uint32 targets, uint32 positions)
{
    uint32 result = r_u8(player + 240) - 1, index, offset;
    if (!r_u16(0x800716E0))
        return result;
    index = (uint16)result;
    result = 8 * index;
    if (!r_u32(targets + 4 * index))
        return result;
    offset = 28 * index;
    result = sub_80046B84(r_u32(positions + offset) - r_u32(player), r_u32(positions + offset + 8) - r_u32(player + 8), r_u32(positions + 16 + 32 * index));
    w_u16(player + 18, result);
    return result;
}

uint32 sub_80052228(uint32 player)
{
    return player_face_target(player, 0x80071648, 0x800C5D14);
}

uint32 sub_800522D0(uint32 player)
{
    return player_face_target(player, 0x80071620, 0x800C1B44);
}

uint32 sub_800540C0(uint32 player)
{
    uint32 index = 0, result = 40 * r_u16(player + 76);
    uint32 mesh = r_u32(r_u32(player + 52)), count = r_u16(0x800BFD10 + result);
    uint32 bone = mesh + 168, phase;
    if (!count)
        return result;
    do
    {
        phase = (uint16)index;
        index += 2;
        sub_80016358(bone + 8, ((r_u16(0x800719D0) + phase) & 3) + 234, 4, 4, 1, 128);
        bone += 336;
        result = (uint16)index < count;
    } while (result);
    return result;
}

uint32 sub_80054414(uint32 position, uint32 target)
{
    return sub_80022C40(position, target, (uint32)-3522, (uint32)-3500, 0, 0, (uint32)-1048, 0, 2288);
}
