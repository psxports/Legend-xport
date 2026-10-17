#include "psx.h"
#include "game_draft_signatures.h"

static uint32 stage12_sound_init(void)
{
    if ((sint16)r_u16(0x80071734) != 3)
    {
        sub_80044734();
        sub_800447B0(66, 80);
        w_u8(0x800718C4, 66);
        w_u8(0x80071898, 67);
        sub_8004477C(66, 0);
        sub_8004477C(r_u8(0x80071898), 0);
        sub_80044528(175, 66, 2);
        w_u16(0x80071734, 3);
    }
    return 3;
}

/* Native helper for the repeated camera stores */
static void stage12_camera(void)
{
    uint32 x, y, z;
    w_u32(0x800BBFC4, r_u32(0x800BBFC4));
    w_u32(0x800BBFCC, r_u32(0x800BBFCC) - 8000);
    w_u32(0x800BBFC8, r_u32(0x800BBFC8) - 8000);
    x = r_u32(0x800BBFC4);
    y = r_u32(0x800BBFC8);
    z = r_u32(0x800BBFCC);
    w_u32(0x800BC040, x);
    w_u32(0x800BC044, y);
    w_u32(0x800BC048, z);
    w_u32(0x800BC04C, r_u32(0x800BBFD0));
}

/* Native helper for the repeated script stores */
static void stage12_script(uint32 script)
{
    uint32 count = r_u16(0x80071728);
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u32(0x8007165C, script);
    w_u16(0x800717A0, count - 1);
}

uint32 legend_stage12_begin(void)
{
    sub_80014848();
    stage12_sound_init();
    sub_800495B0();
    sub_800498AC();
    sub_80049990();
    sub_8004A02C();
    sub_8002B2A0(762);
    sub_800129E8();
    sub_8002B358(762);
    sub_8004591C(763, 0, 0);
    sub_8002292C(764);
    sub_8004B930(1);
    stage12_camera();
    sub_8002F520();
    stage12_script(0x800CA7E8);
    return sub_80048448(0, 255, 224);
}

uint32 legend_stage13_begin(void)
{
    sub_80014848();
    stage12_sound_init();
    sub_800498AC();
    sub_80049B5C();
    sub_8004A02C();
    sub_8004A0D8();
    sub_8002B2A0(765);
    sub_800129E8();
    sub_8002B358(765);
    sub_8004591C(766, 0, 0);
    sub_8002292C(767);
    sub_8004B930(1);
    stage12_camera();
    sub_80030678();
    stage12_script(0x800CAB34);
    sub_80048448(0, 255, 96);
    sub_80026D8C(69653, (uint32)-4341, (uint32)-11868, 1, 3, 4, 0, 0, 40);
    sub_80026D8C(84003, (uint32)-3841, (uint32)-11868, 1, 3, 4, 0, 0, 40);
    sub_80026D8C(98433, (uint32)-3541, (uint32)-11868, 1, 3, 4, 0, 0, 40);
    sub_80026D8C(112763, (uint32)-3541, (uint32)-11868, 1, 3, 4, 0, 0, 40);
    sub_80026D8C(69555, (uint32)-4610, (uint32)-3321, 0, 3, 4, 0, 0, 40);
    sub_80026D8C(83955, (uint32)-4610, (uint32)-3321, 0, 3, 4, 0, 0, 40);
    sub_80026D8C(98355, (uint32)-4610, (uint32)-3321, 0, 3, 4, 0, 0, 40);
    return sub_80026D8C(112755, (uint32)-4610, (uint32)-3321, 0, 3, 4, 0, 0, 40);
}

uint32 legend_stage14_begin(void)
{
    sub_80014848();
    stage12_sound_init();
    sub_800498AC();
    sub_80049DA0();
    sub_80049E94();
    sub_80049F60();
    sub_8004A02C();
    sub_8004A0D8();
    sub_80019BD4(768, 488, 128, 128, 128, 0);
    sub_80019BD4(769, 489, 400, 400, 400, 0);
    sub_80019648(489, 150, 150, 150);
    sub_8002B2A0(770);
    sub_800129E8();
    sub_8002B358(770);
    sub_8004591C(771, 0, 0);
    sub_8002292C(772);
    sub_8004B930(3);
    stage12_camera();
    sub_80030678();
    stage12_script(0x800CADFC);
    sub_80048448(0, 255, 96);
    sub_80027094(48, 83, r_u8(0x80071898), 700, 13000);
    sub_80028A94(190908, 400, 8996, 248375, 400, 8996, 190908, 400, (uint32)-2704, 248375, 400, (uint32)-2704, 40, r_u16(0x80071728) - 1);
    sub_80026D8C(127195, (uint32)-5632, (uint32)-4417, 0, 3, 4, 0, 0, 50);
    sub_80026D8C(131387, (uint32)-6098, (uint32)-584, 0, 3, 4, 0, 0, 50);
    sub_80026D8C(145632, (uint32)-3381, (uint32)-12292, 0, 3, 4, 0, 0, 50);
    sub_80026D8C(150484, (uint32)-3847, (uint32)-1663, 0, 3, 4, 0, 0, 50);
    sub_80026D8C(168921, (uint32)-5244, (uint32)-3694, 0, 3, 4, 0, 0, 50);
    return sub_80026D8C(188794, (uint32)-4157, (uint32)-2989, 0, 3, 4, 0, 0, 50);
}

uint32 legend_stage15_begin(void)
{
    sub_80014848();
    stage12_sound_init();
    sub_80049DA0();
    sub_80049E94();
    sub_80049F60();
    sub_8004A740();
    sub_8002B2A0(773);
    sub_800129E8();
    sub_8002B358(773);
    sub_8004591C(774, 0, 0);
    sub_8002292C(775);
    sub_8004B930(1);
    stage12_camera();
    sub_80030678();
    stage12_script(0x800CB2B0);
    sub_80048448(0, 255, 96);
    sub_80026D8C((uint32)-22434, (uint32)-3414, (uint32)-351, 1, 3, 5, 0, 0, 100);
    sub_80026D8C((uint32)-11678, (uint32)-2307, 6880, 1, 3, 5, 0, 0, 100);
    sub_80026D8C(755, (uint32)-3268, 9977, 1, 3, 5, 0, 0, 100);
    sub_80026D8C(4899, (uint32)-1066, (uint32)-11602, 1, 3, 5, 0, 0, 100);
    return sub_8002AC34();
}

uint32 sub_8004A02C(void)
{
    sub_800456A8(19, 700);
    w_u16(0x800AECCC, 36);
    w_u16(0x800AECCE, 36);
    w_u16(0x800AECD0, 37);
    w_u16(0x800AECD2, 37);
    w_u16(0x800AECD4, 38);
    w_u16(0x800AECD6, 35);
    w_u16(0x800AECD8, 47);
    sub_8001EE9C();
    return sub_8001EEE8(460, 461, 459, 362, 400, 400, 400, 19, 2);
}

uint32 sub_8004A0D8(void)
{
    sub_800456A8(20, 700);
    w_u16(0x800AECEE, 6);
    w_u16(0x800AECF0, 6);
    w_u16(0x800AECF4, 9);
    w_u16(0x800AECF6, 34);
    w_u16(0x800AECEC, 5);
    w_u16(0x800AECF2, 5);
    w_u16(0x800AECF8, 47);
    sub_8001EE9C();
    return sub_8001EEE8(477, 478, 476, 377, 400, 400, 400, 20, 2);
}

uint32 sub_80049E94(void)
{
    sub_800456A8(17, 700);
    w_u16(0x800AEC8E, 6);
    w_u16(0x800AEC90, 6);
    w_u16(0x800AEC94, 9);
    w_u16(0x800AEC96, 34);
    w_u16(0x800AEC8C, 5);
    w_u16(0x800AEC92, 5);
    w_u16(0x800AEC98, 47);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 800);
    w_u16(0x800AFB18, 800);
    w_u16(0x800AFB1C, 100);
    return sub_8001EEE8(426, 427, 425, 332, 400, 400, 400, 17, 2);
}

uint32 sub_80049F60(void)
{
    sub_800456A8(18, 700);
    w_u16(0x800AECAE, 6);
    w_u16(0x800AECB0, 6);
    w_u16(0x800AECB4, 9);
    w_u16(0x800AECB6, 34);
    w_u16(0x800AECAC, 5);
    w_u16(0x800AECB2, 5);
    w_u16(0x800AECB8, 47);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 800);
    w_u16(0x800AFB18, 800);
    w_u16(0x800AFB1C, 100);
    return sub_8001EEE8(443, 444, 442, 347, 400, 400, 400, 18, 2);
}

uint32 sub_8004A740(void)
{
    sub_800456A8(26, 700);
    w_u16(0x800AEDAC, 63);
    w_u16(0x800AEDB0, 63);
    w_u16(0x800AEDAE, 64);
    w_u16(0x800AEDB2, 64);
    w_u16(0x800AEDB4, 62);
    w_u16(0x800BFC50, 600);
    w_u16(0x800AEDB6, 62);
    w_u16(0x800AEDB8, 62);
    sub_8001EE9C();
    sub_8001EEE8(612, 613, 611, 451, 400, 400, 400, 26, 2);
    return sub_8001EEE8(638, 639, 637, 475, 400, 400, 400, 21, 2);
}

uint32 sub_80028A94(uint32 x0, uint32 y0, uint32 z0, uint32 x1, uint32 y1, uint32 z1, uint32 x2, uint32 y2, uint32 z2, uint32 x3, uint32 y3, uint32 z3, uint32 first, uint32 last)
{
    uint32 node = sub_80032EF0(), i;
    if (!node)
        return 28;
    w_u32(node + 8, 28);
    w_u32(node + 44, (uint32)((sint32)(x0 + x1 + x2 + x3) >> 2));
    w_u32(node + 48, (uint32)((sint32)(y0 + y1 + y2 + y3) >> 2));
    w_u32(node + 52, (uint32)((sint32)(z0 + z1 + z2 + z3) >> 2));
    w_u16(node + 60, first);
    w_u16(node + 62, last);
    w_u16(node + 64, 0);
    w_u16(node + 20, x1 - r_u16(node + 44));
    w_u16(node + 12, x0 - r_u16(node + 44));
    w_u16(node + 28, x2 - r_u16(node + 44));
    w_u16(node + 36, x3 - r_u16(node + 44));
    w_u16(node + 14, y0 - r_u16(node + 48));
    w_u16(node + 22, y1 - r_u16(node + 48));
    w_u16(node + 30, y2 - r_u16(node + 48));
    w_u16(node + 38, y3 - r_u16(node + 48));
    w_u16(node + 16, z0 - r_u16(node + 52));
    w_u16(node + 24, z1 - r_u16(node + 52));
    w_u16(node + 32, z2 - r_u16(node + 52));
    w_u16(node + 40, z3 - r_u16(node + 52));
    for (i = 0; i < 4; ++i)
    {
        w_u16(node + 66 + 2 * i, 0 - (sub_80011B8C() & 255));
        w_u16(node + 74 + 2 * i, 0 - ((sub_80011B8C() & 15) + 2));
    }
    w_u16(node + 82, 128);
    return 128;
}

uint32 sub_8002AC34(void)
{
    uint32 node = sub_80032EF0();
    if (node)
    {
        w_u32(node + 8, 54);
        w_u16(node + 12, 0);
        w_u16(node + 18, 0);
        w_u16(node + 16, 0);
    }
    return 54;
}

uint32 sub_8003D538(uint32 state, uint32 positions)
{
    uint32 position[3], point = positions + 2 * (uint16)(3 * r_u16(state + 4));
    uint32 texture, fade, address, result;
    position[0] = (uint32)(sint32)(sint16)r_u16(point);
    position[1] = (uint32)(sint32)(sint16)r_u16(point + 2);
    position[2] = (uint32)(sint32)(sint16)r_u16(point + 4);
    texture = (r_u16(state + 6) >> 2) + 270;
    fade = (uint16)(16 - r_u16(state + 6));
    address = draft_local_address(position, sizeof(position));
    sub_80016B84(address, 279, 4, 2, (uint16)(4 * fade), (uint16)(2 * fade), fade);
    sub_80016B84(address, texture, 5, 2, (uint16)(10 * fade), (uint16)(8 * fade), (uint16)(2 * fade));
    result = (uint16)(r_u16(state + 6) + 1);
    w_u16(state + 6, result);
    if (result == 16)
    {
        w_u16(state + 6, 0);
        result = sub_80011B8C() & 7;
        w_u16(state + 4, result);
    }
    return result;
}

uint32 sub_8003D660(uint32 node)
{
    return sub_8003D538(node + 12, 0x80068774);
}
