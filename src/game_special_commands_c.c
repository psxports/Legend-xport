#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_8005353C(uint32 player, uint32 action, uint32 fallback);

uint32 sub_80053714(uint32 character)
{
    uint32 sound = (uint16)character == 1 ? 52 : 51;
    uint32 channel = (uint16)sub_800448F4();
    return sub_8004486C(1, channel, sound, 1000, 16000, 512);
}

uint32 sub_80053774(uint32 player, uint32 unused)
{
    static const uint32 tables[9] = {0x80068C10, 0x800690D4, 0x80068D04, 0x80068EEC, 0x800691C8, 0x80068DF8, 0x800692BC, 0x80068FE0, 0x800693B0};
    uint32 selector = r_u16(player + 246), table, length, count, index, mismatch, action, energy, allowed;
    if (selector < 9)
        table = tables[selector];
    else
    {
        /* TODO: Invalid selectors retain an unspecified incoming a2 table */
        table = draft_unknown_argument("sub_80053774 invalid selector", 2);
    }
    for (;;)
    {
        if (!r_s16(table))
            return 0;
        length = r_u16(table);
        mismatch = 0;
        count = r_u8(player + 218);
        if ((sint32)count == (sint16)length)
        {
            for (index = 0; (sint16)index < (sint32)count; ++index)
                if ((sint32)r_u8(player + 219 + (sint16)index) != r_s16(table + 2 + 2 * (sint16)index))
                    mismatch = 1;
            if (!mismatch)
            {
                w_u8(player + 218, 0);
                action = r_u16(table + 2 + (uint32)(2 * (sint32)(sint16)length));
                if (action - 48 < 2 || (sint16)action == 50)
                    return sub_8005353C(player, action, (uint16)table);
                allowed = 0;
                energy = r_u8(player + 241);
                if ((sint16)action == 35)
                {
                    if (energy == 64)
                    {
                        w_u8(player + 241, r_u8(player + 241) + 192);
                        allowed = 1;
                    }
                }
                else if (energy >= 16)
                {
                    w_u8(player + 241, r_u8(player + 241) + 240);
                    allowed = 1;
                }
                if (allowed)
                {
                    sub_80053714(r_u8(player + 212));
                    w_u8(player + 244, 0);
                    sub_80052078(player, 768, 10000);
                    return sub_800513CC(player, (uint16)action);
                }
            }
        }
        table += (uint32)(2 * (sint32)(sint16)length) + 4;
    }
}
