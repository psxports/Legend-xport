#include "psx.h"
#include "game_draft_signatures.h"

static uint32 stage8_resources(void)
{
    sub_80019BD4(748, 490, 300, 300, 300, 1);
    sub_80019BD4(749, 491, 370, 370, 370, 1);
    sub_80019648(490, 100, 100, 100);
    return sub_80019648(491, 80, 80, 80);
}

static uint32 stage8_sound_init(void)
{
    if ((sint16)r_u16(0x80071734) != 2)
    {
        sub_80044734();
        sub_800447B0(66, 80);
        w_u8(0x800717D4, 66);
        w_u8(0x800718C4, 67);
        w_u8(0x800719D8, 68);
        w_u8(0x800719DC, 69);
        sub_8004477C(66, 0);
        sub_8004477C(r_u8(0x800718C4), 0);
        sub_8004477C(r_u8(0x800719DC), 0);
        sub_80044528(169, 66, 4);
        w_u16(0x80071734, 2);
    }
    return 2;
}

/* Native helper for the repeated camera stores */
static void stage8_camera(uint32 height)
{
    uint32 x, y, z;
    w_u32(0x800BBFC4, r_u32(0x800BBFC4));
    w_u32(0x800BBFCC, r_u32(0x800BBFCC) - 8000);
    w_u32(0x800BBFC8, r_u32(0x800BBFC8) - height);
    x = r_u32(0x800BBFC4);
    y = r_u32(0x800BBFC8);
    z = r_u32(0x800BBFCC);
    w_u32(0x800BC040, x);
    w_u32(0x800BC044, y);
    w_u32(0x800BC048, z);
    w_u32(0x800BC04C, r_u32(0x800BBFD0));
}

/* Native helper for the repeated script stores */
static void stage8_script(uint32 script)
{
    uint32 count = r_u16(0x80071728);
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u32(0x8007165C, script);
    w_u16(0x800717A0, count - 1);
}

uint32 legend_stage8_begin(void)
{
    sub_80014848();
    stage8_sound_init();
    sub_80049504();
    sub_80049694();
    sub_80049990();
    sub_80049C08();
    sub_80049CD4();
    stage8_resources();
    sub_8002B2A0(750);
    sub_800129E8();
    sub_8002B358(750);
    sub_8004591C(751, 0, 0);
    sub_8002292C(752);
    sub_8004B930(1);
    stage8_camera(8000);
    sub_80030678();
    stage8_script(0x800CA88C);
    sub_80048448(0, 255, 96);
    sub_80026D8C((uint32)-90048, (uint32)-3236, 803, 1, 3, 5, 0, 0, 31);
    sub_80026D8C((uint32)-84104, (uint32)-4571, (uint32)-1257, 1, 3, 5, 0, 0, 31);
    sub_80026D8C((uint32)-76087, (uint32)-4574, (uint32)-1257, 1, 3, 5, 0, 0, 31);
    sub_80026D8C((uint32)-68124, (uint32)-4574, (uint32)-1257, 1, 3, 5, 0, 0, 31);
    sub_80027094(0, 20, r_u8(0x800717D4), 1400, 23000);
    sub_80027114(0, 20, 55, 850, 15000, 60);
    sub_80027094(30, 72, r_u8(0x800719DC), 800, 15000);
    return sub_80027114(30, 72, r_u8(0x800719D8), 800, 26000, 160);
}

uint32 legend_stage9_begin(void)
{
    sub_80014848();
    stage8_sound_init();
    sub_800495B0();
    sub_800498AC();
    sub_80049A30();
    sub_80049C08();
    sub_80049CD4();
    stage8_resources();
    sub_8002B2A0(753);
    sub_800129E8();
    sub_8002B358(753);
    sub_8004591C(754, 0, 0);
    sub_8002292C(755);
    sub_8004B930(2);
    stage8_camera(4000);
    sub_80030678();
    stage8_script(0x800CAC90);
    sub_80048448(0, 255, 96);
    sub_80027094(8, 57, r_u8(0x800719DC), 800, 15000);
    return sub_80027114(8, 57, r_u8(0x800719D8), 800, 26000, 160);
}

uint32 legend_stage10_begin(void)
{
    sub_80014848();
    stage8_sound_init();
    sub_800497EC();
    sub_800498AC();
    sub_80049990();
    sub_80049A30();
    sub_80049C08();
    sub_80049CD4();
    sub_80049DA0();
    stage8_resources();
    sub_8002B2A0(756);
    sub_800129E8();
    sub_8002B358(756);
    sub_8004591C(757, 0, 0);
    sub_8002292C(758);
    sub_8004B930(1);
    stage8_camera(8000);
    sub_80030678();
    stage8_script(0x800CAFA8);
    sub_80048448(0, 255, 128);
    sub_80026D8C((uint32)-35775, (uint32)-3507, 5566, 1, 3, 5, 0, 0, 22);
    sub_80026D8C((uint32)-16929, (uint32)-4505, 5815, 1, 3, 5, 0, 0, 22);
    sub_80026D8C((uint32)-28015, (uint32)-4743, 7415, 1, 3, 5, 0, 0, 22);
    sub_80026D8C((uint32)-14628, (uint32)-2154, (uint32)-2184, 1, 3, 5, 0, 0, 22);
    sub_80026D8C(2210, (uint32)-5495, 5548, 1, 3, 5, 0, 0, r_u16(0x80071728));
    sub_80026D8C(15023, (uint32)-4335, 7239, 1, 3, 5, 0, 0, r_u16(0x80071728));
    sub_80026D8C(21224, (uint32)-4000, 5741, 1, 3, 5, 0, 0, r_u16(0x80071728));
    sub_80026D8C(29008, (uint32)-5294, 7214, 1, 3, 5, 0, 36, r_u16(0x80071728));
    sub_80026D8C(31897, (uint32)-5294, 8476, 1, 3, 5, 0, 36, r_u16(0x80071728));
    sub_80026D8C(39009, (uint32)-5294, 8476, 1, 3, 5, 0, 36, r_u16(0x80071728));
    sub_80026D8C(41897, (uint32)-5294, 7214, 1, 3, 5, 0, 36, r_u16(0x80071728));
    sub_80027094(0, 50, r_u8(0x800717D4), 1400, 23000);
    return sub_80027114(0, 50, 55, 850, 15000, 60);
}

uint32 legend_stage11_begin(void)
{
    sub_80014848();
    stage8_sound_init();
    sub_800495B0();
    sub_800498AC();
    sub_8004A664();
    sub_8002B2A0(759);
    sub_800129E8();
    sub_8002B358(759);
    sub_8004591C(760, 0, 0);
    sub_8002292C(761);
    sub_8004B930(2);
    stage8_camera(8000);
    sub_8002F520();
    stage8_script(0x800CB380);
    sub_80048448(0, 255, 128);
    return sub_80029C3C(25, 90, 210);
}
