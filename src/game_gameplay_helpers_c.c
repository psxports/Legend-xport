#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80022F08(uint32 position, uint32 velocity, uint32 size1, uint32 size2, uint32 type)
{
    uint32 item = sub_80032EF0(), words[4], i;
    if (!item) return 1;
    w_u32(item + 8u, 1);
    for (i = 0; i < 4u; ++i) words[i] = r_u32(position + 4u * i);
    for (i = 0; i < 4u; ++i) w_u32(item + 12u + 4u * i, words[i]);
    for (i = 0; i < 4u; ++i) words[i] = r_u32(velocity + 4u * i);
    for (i = 0; i < 4u; ++i) w_u32(item + 28u + 4u * i, words[i]);
    w_u16(item + 48u, size1);
    w_u16(item + 50u, size2);
    w_u16(item + 46u, type);
    return words[0];
}

uint32 sub_8005915C(uint32 actor, uint32 state)
{
    uint32 descriptor = r_u32(actor + 36u) + 2u * (uint16)(2u * state);
    w_u16(actor + 214u, state);
    w_u16(actor + 216u, r_u16(descriptor));
    return sub_80057A14(actor + 80u, r_u16(descriptor + 2u));
}

uint32 sub_800598CC(uint32 actor)
{
    uint32 table = r_u32(actor + 40u);
    uint32 count = (r_u16(table) & 128u) ? 6u : 4u;
    uint32 choice, result = r_u16(actor + 232u) < 150u;
    if (!result)
        choice = r_u16(table + 8u);
    else
    {
        choice = (uint16)(count * (sub_80011B8C() & 127u)) / 127u;
        if (choice >= count) choice = count - 1u;
        result = choice;
        if (choice == r_u16(actor + 230u))
        {
            result = ++choice;
            if (choice == count) choice = 0;
        }
    }
    w_u16(actor + 230u, choice);
    return result;
}

uint32 sub_800599B4(uint32 actor)
{
    sub_8005915C(actor, 0);
    w_u16(actor + 220u, (sub_80011B8C() & 127u) + 16u);
    return sub_800598CC(actor);
}
