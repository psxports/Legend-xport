#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80049990(void)
{
    sub_800456A8(11, 700);
    w_u16(0x800AEBCC, 36);
    w_u16(0x800AEBCE, 36);
    w_u16(0x800AEBD0, 37);
    w_u16(0x800AEBD2, 37);
    w_u16(0x800AEBD4, 38);
    w_u16(0x800AEBDA, 54);
    sub_8001EE9C();
    return sub_8001EEE8(311, 312, 310, 229, 350, 350, 350, 11, 2);
}

uint32 sub_800495B0(void)
{
    static const uint16 values[7] = {36, 36, 37, 37, 38, 35, 47};
    uint32 i;
    sub_800456A8(5, 700);
    for (i = 0; i < 7; ++i)
        w_u16(0x800AEB0C + 2 * i, values[i]);
    sub_8001EE9C();
    sub_8001EEE8(219, 220, 218, 149, 400, 400, 400, 5, 2);
    return sub_8001EEE8(236, 237, 235, 164, 400, 400, 400, 6, 2);
}

uint32 sub_80049B5C(void)
{
    sub_800456A8(13, 700);
    w_u16(0x800AEC0C, 45);
    w_u16(0x800AEC0E, 46);
    w_u16(0x800AEC10, 46);
    w_u16(0x800AEC12, 46);
    w_u16(0x800AEC14, 46);
    sub_8001EE9C();
    w_u16(0x800AFAE2, 200);
    w_u16(0x800AFAE0, 200);
    w_u16(0x800AFAE4, 200);
    return sub_8001EEE8(349, 350, 348, 263, 400, 400, 400, 13, 2);
}

uint32 sub_80049694(void)
{
    static const uint16 values[7] = {31, 31, 32, 32, 33, 35, 47};
    uint32 i;
    sub_800456A8(7, 700);
    for (i = 0; i < 7; ++i)
        w_u16(0x800AEB4C + 2 * i, values[i]);
    sub_8001EE9C();
    return sub_8001EEE8(243, 244, 242, 169, 400, 400, 400, 7, 2);
}

static void forest_resource_fields(uint32 base, uint32 fourth)
{
    w_u16(base + 2, 6);
    w_u16(base + 4, 6);
    w_u16(base + 8, fourth);
    w_u16(base + 10, 34);
    w_u16(base, 5);
    w_u16(base + 6, 5);
    w_u16(base + 12, 47);
}

uint32 sub_80049740(void)
{
    sub_800456A8(8, 700);
    forest_resource_fields(0x800AEB6C, 9);
    sub_8001EE9C();
    return sub_8001EEE8(260, 261, 259, 184, 400, 400, 400, 8, 2);
}

uint32 sub_800497EC(void)
{
    sub_800456A8(9, 700);
    forest_resource_fields(0x800AEB8C, 9);
    sub_8001EE9C();
    w_u16(0x800AFB22, 300);
    w_u16(0x800AFB20, 300);
    return sub_8001EEE8(277, 278, 276, 199, 400, 400, 400, 9, 2);
}

uint32 sub_8004A4F4(void)
{
    sub_800456A8(26, 700);
    forest_resource_fields(0x800AEDAC, 44);
    sub_8001EE9C();
    w_u16(0x800AFB22, 300);
    w_u16(0x800AFB20, 400);
    return sub_8001EEE8(561, 562, 560, 451, 400, 400, 400, 26, 2);
}

uint32 sub_8004A5B8(void)
{
    sub_800456A8(26, 700);
    forest_resource_fields(0x800AEDAC, 44);
    sub_8001EE9C();
    return sub_8001EEE8(578, 579, 577, 451, 400, 400, 400, 26, 2);
}
