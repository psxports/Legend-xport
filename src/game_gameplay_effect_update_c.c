#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80036C7C(uint32 node)
{
    uint32 tick, result, shade, red, green, blue;
    sub_800173DC(node + 12, r_u16(node + 28), r_u16(node + 36), r_u16(node + 40),
        r_u16(node + 38), r_u16(node + 42));
    shade = r_u16(node + 38);
    w_u16(node + 38, shade < 8 ? 0 : shade - 8);
    tick = r_u16(node + 32);
    w_u16(node + 32, tick + 1);
    if (tick >= r_u16(node + 34)) {
        w_u16(node + 32, 0);
        w_u16(node + 30, r_u16(node + 30) - 1);
        w_u16(node + 28, r_u16(node + 28) + 1);
        if (!r_u16(node + 30)) sub_80032FD0(node);
    }
    result = r_u16(node + 44);
    if (!result) return result;
    shade = r_u16(node + 38);
    red = (uint32)((sint32)(r_u16(node + 46) * shade) / 128);
    green = (uint32)((sint32)(r_u16(node + 48) * shade) / 128);
    blue = (uint32)((sint32)(r_u16(node + 50) * shade) / 128);
    return sub_8002B178(node + 12, red, green, blue);
}

