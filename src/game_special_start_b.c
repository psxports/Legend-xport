#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8005353C(uint32 player, uint32 action, uint32 fallback)
{
    uint32 result = r_u16(0x8007199C), effect, sound, saved;
    if (result)
        return result;
    result = r_u16(0x8007171C);
    if (result)
        return result;
    if ((uint16)action == 48)
        fallback = 3;
    else if ((uint16)action == 49)
        fallback = 2;
    else if ((uint16)action == 50)
        fallback = 1;
    if (r_u8(player + 280) < (uint16)fallback)
        return 1;
    w_u8(player + 280, r_u8(player + 280) - fallback);
    sub_800527C8(player, action, fallback);
    sub_800513CC(player, (uint16)action);
    w_u8(player + 244, 0);
    w_u16(0x8007199C, 1);
    w_u8(0x80071544, 1);
    w_u16(0x800718F8, 0);
    w_u16(0x800719F4, action - 48);
    w_u16(0x80071928, r_u8(player + 240) - 1);
    effect = 0x800AFDA0 + 288 * r_u8(player + 240);
    sub_80022C40(effect, effect, (uint32)-2610, 1050, 0, 0, (uint32)-2112, 0, ((sint16)r_u16(player + 18) + 512) & 0xFFF);
    w_u16(0x8007168C, sub_8004496C());
    sound = r_u16(0x800719F4);
    sound = (sound == 0 || sound == 2) ? 29 : 30;
    sub_8004486C(1, r_u16(0x8007168C), sound, 800, 32000, 512);
    saved = r_u16(0x8007179C);
    w_u32(0x8007179C, 0);
    w_u16(0x80071830, saved);
    return sub_80044FB0();
}
