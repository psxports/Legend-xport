#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80014878(void)
{
    /* Runtime GP 80071474 plus original offsets 140 and 18C */
    w_u16(0x800715B4u, 0);
    w_u16(0x80071600u, 0);
    return 0;
}

uint32 sub_80018DEC(void)
{
    uint32 i, slot, pointer;
    for (i = 0; i < 2u; ++i)
    {
        slot = 0x80071570u + 4u * i;
        pointer = r_u32(slot);
        if (pointer)
        {
            sub_80011AF8(pointer);
            sub_80011AF8(r_u32(0x80071694u + 4u * i));
            w_u32(slot, 0);
        }
    }
    return 2u;
}

uint32 sub_8004BC4C(void)
{
    uint32 i;
    sub_8002B238();
    sub_80045700();
    for (i = 119u; i < 512u; ++i)
        sub_80018CFC(i);
    for (i = 3u; i < 32u; ++i)
        sub_800573EC(i);
    sub_8003F638();
    sub_80051484();
    sub_80011AF8(r_u32(0x80071A3Cu));
    sub_80011AF8(r_u32(0x8007167Cu));
    sub_800311E4();
    sub_80011AF8(r_u32(0x80071A1Cu));
    sub_80030748();
    for (i = 0; i < 2u; ++i)
    {
        w_u8(0x800AFF95u + 288u * i, 0);
        w_u16(0x800AFFC2u + 288u * i, 0);
    }
    return 0;
}
