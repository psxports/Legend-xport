#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8004B164(void)
{
    static const uint16 model_slots[] = {108, 110, 109, 111, 112, 113, 114, 115, 116, 117, 118};
    uint32 index;

    sub_800456A8(2, 700);
    w_u16(0x800AEAAE, 6);
    w_u16(0x800AEAB0, 6);
    w_u16(0x800AEAB4, 10);
    w_u16(0x800AEABA, 20);
    w_u16(0x800AEAAC, 5);
    w_u16(0x800AEAB2, 5);
    w_u16(0x800AEABC, 3);
    w_u16(0x800BF918, 700);
    w_u16(0x800AEABE, 21);
    w_u16(0x800BF91A, 700);
    w_u16(0x800AEAC0, 4);
    w_u16(0x800BF91C, 700);
    w_u16(0x800AEAC2, 21);
    w_u16(0x800BF91E, 700);

    sub_8001EE9C();
    w_u16(0x800AFB1C, 300);
    w_u16(0x800AFB1A, 300);
    w_u16(0x800AFB18, 300);
    w_u16(0x800AFB24, 300);
    w_u16(0x800AFB22, 300);
    w_u16(0x800AFB20, 300);
    w_u16(0x800AFB4C, 200);
    w_u16(0x800AFB4A, 200);
    w_u16(0x800AFB48, 200);
    w_u16(0x800AFB3C, 200);
    w_u16(0x800AFB3A, 200);
    w_u16(0x800AFB38, 200);
    w_u16(0x800AFB44, 200);
    w_u16(0x800AFB42, 200);
    w_u16(0x800AFB40, 200);
    w_u16(0x800AFB54, 200);
    w_u16(0x800AFB52, 200);
    w_u16(0x800AFB50, 200);

    sub_8001EEE8(122, 125, 121, 93, 400, 400, 400, 2, 2);
    for (index = 0; index < 11; ++index)
        sub_80019BD4(140 + index, model_slots[index], 400, 400, 400, 2);

    sub_80019648(108, 300, 300, 300);
    sub_80019648(110, 120, 120, 120);
    sub_80019648(109, 120, 120, 120);
    sub_80019648(111, 120, 120, 120);
    sub_80019648(113, 300, 300, 100);
    sub_80019648(114, 100, 100, 100);
    sub_80019648(115, 200, 200, 200);
    sub_80019648(116, 200, 200, 200);
    sub_80019648(117, 100, 100, 100);
    return sub_80019648(112, 100, 100, 100);
}

uint32 sub_8002B238(void)
{
    sub_80011AF8(r_u32(0x80071924));
    sub_80011AF8(r_u32(0x800716A4));
    sub_80011AF8(r_u32(0x800719B8));
    sub_80011AF8(r_u32(0x800717CC));
    return sub_80011AF8(r_u32(0x800717B8));
}

uint32 sub_80045700(void)
{
    sub_80011AF8(r_u32(0x800718D0));
    sub_80011AF8(r_u32(0x80071704));
    sub_80011AF8(r_u32(0x80071714));
    sub_80011AF8(r_u32(0x80071934));
    sub_80011AF8(r_u32(0x800718E4));
    sub_80011AF8(r_u32(0x80071954));
    return sub_80011AF8(r_u32(0x800716D0));
}

uint32 sub_80051484(void)
{
    uint32 index, pointer;
    for (index = 0; index < 2; ++index)
    {
        uint32 player = 0x800AFEC0 + 288 * index;
        pointer = r_u32(player + 52);
        if (pointer)
            sub_8001EE58(pointer);
        pointer = r_u32(player + 56);
        if (pointer)
            sub_80011AF8(pointer);
        pointer = r_u32(player + 64);
        if (pointer)
            sub_80011AF8(pointer);
        pointer = r_u32(player + 60);
        if (pointer)
            sub_80011AF8(pointer);
    }
    return 0;
}

uint32 sub_8003118C(uint32 index)
{
    uint32 result, slot, pointer;
    index = (uint16)index;
    if (index == 0xFFFF)
        return 0xFFFF;
    result = 4 * index;
    slot = 0x800BD408 + result;
    pointer = r_u32(slot);
    if (pointer)
        result = sub_80011AF8(pointer);
    w_u32(slot, 0);
    return result;
}

uint32 sub_800311E4(void)
{
    uint32 index;
    for (index = 0; index < 8; ++index)
        sub_8003118C(index);
    return 0;
}

uint32 sub_80030748(void)
{
    /* Runtime GP 80071474 plus original offset BC */
    return sub_80011AF8(r_u32(0x80071530));
}
