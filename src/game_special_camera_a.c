#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdlib.h>

uint32 sub_8002030C(uint32 target)
{
    uint32 x, y, z, position;
    if (target)
    {
        x = r_u32(0x800BBFC4);
        position = r_u32(target + 8);
        w_u32(0x800BC01C, x - position);
        y = r_u32(0x800BBFC8);
        position = r_u32(target + 12);
        w_u32(0x800BC020, y - position);
        z = r_u32(0x800BBFCC);
        position = r_u32(target + 16);
        w_u32(0x800BC024, z - position);
    }
    else
    {
        x = r_u32(0x800BBFC4);
        y = r_u32(0x800BBFC8);
        z = r_u32(0x800BBFCC);
        w_u32(0x800BC040, x);
        w_u32(0x800BC044, y);
        w_u32(0x800BC048, z);
        w_u32(0x800BC04C, r_u32(0x800BBFD0));
    }
    w_u32(0x800BC02C, target);
    w_u16(0x800BC060, 0);
    w_u16(0x800BC062, 1);
    return 1;
}

void sub_800203EC(uint32 x, uint32 angle, uint32 z, uint32 mode)
{
    w_u32(0x800BC034, x);
    w_u16(0x800BC03C, angle);
    w_u32(0x800BC038, z);
    w_u16(0x800BC062, mode);
}

void sub_80020414(uint32 x, uint32 y, uint32 z, uint32 mode)
{
    w_u16(0x800BC09C, x);
    w_u16(0x800BC09E, y);
    w_u16(0x800BC0A0, z);
    w_u16(0x800BC0C4, mode);
}

uint32 sub_8002095C(uint32 current, uint32 target)
{
    sint32 divisor = r_s32(0x800BC068);
    uint32 difference = target - current, maximum, minimum, step, result;

    /* Preserve the original BREAK boundaries before signed division */
    if (!divisor || (divisor == -1 && difference == 0x80000000))
        abort();
    step = (uint32)((sint32)difference / divisor);
    maximum = r_u32(0x800BC064);
    minimum = 0 - maximum;
    if (!step)
        step = difference;
    if ((sint32)step < (sint32)minimum)
        step = minimum;
    if ((sint32)maximum < (sint32)step)
        step = maximum;
    result = current + step;
    if (result != target)
        w_u16(0x800BC060, 0);
    return result;
}

uint32 sub_80021170(uint32 current, uint32 target)
{
    sint32 delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(target - current));
    sint32 step = delta >> 3;
    if (!step && delta)
        step = delta < 0 ? -1 : 1;
    return (uint32)(sint32)(sint16)(current + (uint32)step);
}

uint32 sub_80021F28(void)
{
    uint16 tile[4];
    uint32 pointer, x, y, z, pad, kind, yaw, result;
    tile[0] = 0xFFFF;
    pointer = r_u32(0x80071994);
    x = r_u32(pointer);
    y = r_u32(pointer + 4);
    z = r_u32(pointer + 8);
    pad = r_u32(pointer + 12);
    w_u32(0x800AFCD8, x);
    w_u32(0x800AFCDC, y);
    w_u32(0x800AFCE0, z);
    w_u32(0x800AFCE4, pad);
    sub_80046324(r_u32(0x800AFCD8), r_u32(0x800AFCE0), draft_local_address(tile, sizeof(tile)));
    kind = tile[0] == 0xFFFF ? 0 : r_u8(r_u32(0x80071704) + 14 * tile[0] + 9);
    yaw = r_u16(r_u32(0x800716D0) + 2 * kind) + r_u16(0x800718AC);
    if (r_u8(0x800719B4))
        w_u16(0x800718E0, yaw);
    else
        w_u16(0x800718E0, sub_80021170((uint32)(sint32)(sint16)r_u16(0x800718E0), (uint32)(sint32)(sint16)yaw));
    w_u16(0x1F800020, 0);
    w_u16(0x1F800024, 0);
    w_u32(0x800BC040, r_u32(0x800AFCD8));
    w_u16(0x1F800022, r_u16(0x800718E0));
    w_u32(0x800BC044, r_u32(0x800AFCDC) + r_u32(0x800BF2B4));
    w_u32(0x800BC048, r_u32(0x800AFCE0));
    sub_8005D138(0x1F800020, 0x1F800000);
    w_u16(0x1F800022, 0);
    w_u16(0x1F800020, r_u16(0x800BF2B0));
    w_u16(0x1F800024, r_u16(0x800BF2B8));
    sub_8005CDD8(0x1F800000, 0x1F800020, 0x1F800028);
    w_u32(0x800BC040, r_u32(0x800BC040) + r_u32(0x1F800028));
    w_u32(0x800BC048, r_u32(0x800BC048) + r_u32(0x1F800030));
    if (r_u8(0x800719B4))
    {
        x = r_u32(0x800BC040);
        y = r_u32(0x800BC044);
        z = r_u32(0x800BC048);
        w_u32(0x800BBFC4, x);
        w_u32(0x800BBFC8, y);
        w_u32(0x800BBFCC, z);
        w_u32(0x800BBFD0, r_u32(0x800BC04C));
    }
    w_u16(0x1F800020, 0);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, r_u16(0x800718E0));
    sub_8005D138(0x1F800020, 0x1F800000);
    w_u16(0x1F800020, r_u16(0x800AEEC8));
    w_u16(0x1F800022, r_u16(0x800AEECC));
    w_u16(0x1F800024, r_u16(0x800AEED0));
    sub_8005CDD8(0x1F800000, 0x1F800020, 0x1F800028);
    pointer = r_u32(0x800719F8);
    w_u32(0x800BC0B4, r_u32(pointer) + r_u32(0x1F800028));
    w_u32(0x800BC0B8, r_u32(pointer + 4) + r_u32(0x1F80002C));
    result = r_u32(pointer + 8) + r_u32(0x1F800030);
    w_u32(0x800BC0BC, result);
    if (r_u8(0x800719B4))
    {
        x = r_u32(0x800BC0B4);
        y = r_u32(0x800BC0B8);
        w_u32(0x800BC0A4, x);
        w_u32(0x800BC0A8, y);
        result = r_u32(0x800BC0BC);
        pad = r_u32(0x800BC0C0);
        w_u32(0x800BC0AC, result);
        w_u32(0x800BC0B0, pad);
    }
    w_u32(0x80071A08, 0);
    w_u8(0x800719B4, 0);
    return result;
}
