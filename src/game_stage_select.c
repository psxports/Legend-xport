#include "psx.h"
#include "game_draft_signatures.h"

extern void sub_8005E4D0(uint32, uint32), sub_8005DFE4(uint32), sub_8005B278(uint32);
extern void sub_8005E814(uint32), sub_8005E648(uint32), sub_8005E5D8(uint32);

static void stage_select_text(uint32 table, uint32 selection, uint32 y)
{
    uint32 text = r_u32(table + 4 * (uint16)selection);
    uint32 width = sub_8004ED48(text);
    uint32 x = (uint32)(sint32)(sint16)(192 - (uint32)((sint32)width >> 1));
    sub_8004EEFC(x, y, text, 128, 128, 128, 2);
}

uint32 sub_8004D35C(void)
{
    static const uint32 tables[4] = {0x800689E8, 0x80068A48, 0x80068A6C, 0x80068A74};
    static const uint32 maximum[4] = {23, 8, 1, 5};
    uint32 values[4] = {0, 0, 0, 0}, row = 0, held = 0, pulse, i;
    sub_80014848();
    sub_80014F0C(17, 0, 1000);
    sub_800129E8();
    sub_80044800();
    w_u16(0x8007194C, 254);
    w_u16(0x800717A4, (uint32)-64);
    w_u16(0x800719D0, 0);
    w_u16(0x800715E8, 0);
    w_u16(0x800716FC, 2);
    sub_80013B64(1, 0, 0, 0);
    sub_800451B8(256, 0, 256, 0);
    while (r_u16(0x8007194C) != 255 || r_u16(0x800717A4))
    {
        sub_80011BB8();
        if (r_u16(0x80071790))
        {
            if (held)
                w_u16(0x80071790, 0);
        }
        else
            held = 0;
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184C), 2500);
        pulse = r_u16(0x800719D0) & 63;
        if (pulse >= 32)
            pulse = 64 - pulse;
        sub_80018A9C(0, (uint32)(sint32)(sint16)(20 * row + 79), 384, 18, (uint16)(pulse + 64), 0, 0, 16);
        for (i = 0; i < 4; ++i)
            stage_select_text(tables[i], values[i], 80 + 20 * i);
        if (r_u16(0x80071790) & 0x1000)
        {
            held = 1;
            if ((uint16)row)
                --row;
        }
        if (r_u16(0x80071790) & 0x4000)
        {
            held = 1;
            if ((uint16)row != 3)
                ++row;
        }
        if (r_u16(0x80071790) & 0x10)
        {
            held = 1;
            if ((uint16)row < 4 && (uint16)values[row])
                --values[row];
        }
        if (r_u16(0x80071790) & 0x40)
        {
            held = 1;
            if ((uint16)row < 4 && (uint16)values[row] < maximum[row])
                ++values[row];
        }
        if (!r_u16(0x800717A4) && (r_u16(0x80071790) & 0x800))
            w_u16(0x800717A4, 8);
        sub_8002F36C();
        sub_8005DFE4(0);
        sub_8005B278(0);
        sub_8005E814(r_u32(0x800719D4));
        sub_8005E648(r_u32(0x800719CC));
        sub_8005E5D8(r_u32(0x8007184C) + 9996);
        w_u16(0x800715E8, r_u16(0x800715E8) ^ 1);
        w_u16(0x800719D0, r_u16(0x800719D0) + 1);
    }
    sub_80013B64(0, 0, 0, 0);
    sub_80013974();
    w_u16(0x80071594, values[0]);
    w_u16(0x80071968, values[1]);
    w_u16(0x800715F0, values[2]);
    w_u16(0x800AFFB6, values[1]);
    w_u16(0x800B00D6, values[1]);
    w_u8(0x800AFFB0, 1);
    w_u8(0x800B00D0, 0);
    switch (values[3])
    {
        case 0:
        case 1:
        case 2:
            w_u8(0x800AFF94, values[3]);
            break;
        case 3:
            w_u8(0x800B00B4, 1);
            w_u8(0x800AFF94, 0);
            w_u8(0x800B00D0, 2);
            break;
        case 4:
            w_u8(0x800AFF94, 0);
            w_u8(0x800B00B4, 2);
            w_u8(0x800B00D0, 2);
            break;
        case 5:
            w_u8(0x800AFF94, 2);
            w_u8(0x800B00B4, 1);
            w_u8(0x800B00D0, 2);
            break;
    }
    sub_800451B8(0x8000, (uint32)-16, 0x8000, (uint32)-16);
    sub_80045048(1);
    return 0;
}
