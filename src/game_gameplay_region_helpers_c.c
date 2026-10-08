#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80046658(uint32 position)
{
    uint32 vector[4], vector_address = draft_local_address(vector, sizeof(vector));
    uint32 region, direction, i, result, x, z;
    do {
        region = r_u16(position + 10);
        w_u16(0x1F800020, 0);
        direction = r_u8(r_u32(0x80071704) + 14 * region + 9);
        w_u16(0x1F800024, 0);
        w_u16(0x1F800022, r_u16(r_u32(0x800716D0) + 2 * direction));
        sub_8005D138(0x1F800020, 0x1F800000);
        for (i = 0; i < 5; ++i) draft_gte_control(i, r_u32(0x1F800000 + 4 * i));
        w_u16(0x1F800020, 0);
        w_u16(0x1F800022, 0);
        w_u16(0x1F800024, 32);
        sub_8005CDA8(0x1F800020, vector_address);
        x = r_u32(position) + vector[0];
        z = r_u32(position + 4) + vector[2];
        w_u32(position, x);
        w_u32(position + 4, z);
        sub_80046324(x, z, position + 10);
        direction = r_u8(r_u32(0x80071704) + 14 * r_u16(position + 10) + 9);
        result = (sint32)(sint16)r_u16(0x80071774) < (sint32)direction;
    } while (!result);
    return result;
}
