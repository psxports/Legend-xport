#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8004EC38(uint32 effect)
{
    sint32 current = (sint16)r_u16(0x80071808);
    uint32 result;
    if (current < 0)
        current = -current;
    result = current < (sint16)effect;
    if (result)
        w_u16(0x80071808, effect);
    return result;
}
