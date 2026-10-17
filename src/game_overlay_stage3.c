#include "psx.h"
#include "game_draft_signatures.h"

static uint32 stage3_sound_init(void)
{
    if ((sint16)r_u16(0x80071734) != 1)
    {
        sub_80044734();
        sub_800447B0(66, 80);
        w_u8(0x80071A10, 66);
        w_u8(0x800717E4, 67);
        sub_80044528(161, 66, 2);
        w_u16(0x80071734, 1);
    }
    return 1;
}

uint32 legend_stage3_begin(void)
{
    uint32 x, y, z;
    sub_80014848();
    stage3_sound_init();
    sub_8004944C();
    sub_800495B0();
    sub_80049740();
    sub_80049B5C();
    sub_8002B2A0(712);
    sub_800129E8();
    sub_8002B358(712);
    sub_8004591C(713, 0, 0);
    sub_8002292C(714);
    sub_8004B930(1);
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
    sub_80030678();
    w_u32(0x8007165C, 0x800CA834);
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u16(0x800717A0, r_u16(0x80071728) - 1);
    sub_80028638((uint32)-13227, (uint32)-5342, 928, 0, 58);
    sub_80028638((uint32)-2893, (uint32)-1154, (uint32)-5116, 0, 58);
    sub_80028638(6000, (uint32)-3896, 1079, 0, 58);
    sub_80028638(13209, (uint32)-3874, 1122, 0, 58);
    sub_80028638(27241, 680, (uint32)-4857, 38, 78);
    sub_80028638(45848, 4198, (uint32)-10720, 38, 78);
    sub_80048448(0, 255, 128);
    return sub_80027114(7, 64, r_u8(0x800717E4), 950, 13000, 200);
}

uint32 legend_stage4_tick(void)
{
    uint32 region = r_u16(0x800BC0CC), kind, amplitude = 0, result = 0xFFFF;
    sint32 product;
    if (region != 0xFFFF)
    {
        kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
        result = kind < 44;
        if (kind - 35 < 31)
        {
            amplitude = kind < 44 ? 8 * (kind - 35) : 64;
            result = 65;
            if (kind >= 57)
            {
                result = 65 - kind;
                amplitude = 8 * result;
            }
        }
    }
    if (amplitude)
    {
        product = (sint32)(amplitude * sub_8005C958(16 * r_u16(0x800719D0)));
        result = (uint32)(product / 4096);
        w_u16(0x800BC0C6, result);
    }
    else
        w_u16(0x800BC0C6, 0);
    return result;
}

uint32 legend_stage4_begin(void)
{
    uint32 x, y, z;
    sub_80014848();
    stage3_sound_init();
    sub_8004944C();
    sub_80049694();
    sub_800497EC();
    sub_80049990();
    sub_80019BD4(715, 488, 128, 128, 128, 1);
    sub_8002B2A0(716);
    sub_800129E8();
    sub_8002B358(716);
    sub_8004591C(717, 0, 0);
    sub_8002292C(718);
    sub_8004B930(5);
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
    sub_80030678();
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u32(0x8007165C, 0x800CAC80);
    w_u16(0x800717A0, r_u16(0x80071728) - 1);
    sub_800285B0();
    sub_80028708(113490, 14294, (uint32)-13983, 1100);
    sub_80028708(142393, 14294, (uint32)-13993, 1100);
    sub_80027114(9, 26, r_u8(0x80071A10), 850, 10000, 120);
    sub_80027114(37, 65, r_u8(0x80071A10), 850, 20000, 120);
    return sub_80048448(0, 255, 128);
}

uint32 legend_stage5_begin(void)
{
    uint32 x, y, z;
    sub_80014848();
    stage3_sound_init();
    sub_800495B0();
    sub_80049694();
    sub_800497EC();
    sub_80049990();
    sub_8002B2A0(719);
    sub_800129E8();
    sub_8002B358(719);
    sub_8004591C(720, 0, 0);
    sub_8002292C(721);
    sub_8004B930(1);
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
    sub_80030678();
    w_u32(0x8007165C, 0x800CB084);
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u16(0x800717A0, r_u16(0x80071728) - 1);
    sub_80028638(176199, 10031, (uint32)-5596, 0, r_u16(0x80071728));
    sub_80028638(185599, 10337, (uint32)-15651, 0, r_u16(0x80071728));
    sub_80026D8C(189184, 9594, (uint32)-4940, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(193800, 9637, (uint32)-4984, 0, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80028638(198408, 10337, (uint32)-15695, 0, r_u16(0x80071728));
    sub_80028638(214954, 10337, (uint32)-14514, 0, r_u16(0x80071728));
    sub_80028638(230630, 10687, (uint32)-5639, 0, r_u16(0x80071728));
    return sub_80048448(0, 255, 128);
}

uint32 legend_stage6_begin(void)
{
    uint32 x, y, z;
    sub_80014848();
    stage3_sound_init();
    sub_8004944C();
    sub_80049504();
    sub_80049694();
    sub_8004A5B8();
    sub_8002B2A0(722);
    sub_800129E8();
    sub_8002B358(722);
    sub_8004591C(723, 0, 0);
    sub_8002292C(724);
    sub_8004B930(1);
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
    sub_80030678();
    w_u32(0x8007165C, 0x800CB448);
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u16(0x800717A0, r_u16(0x80071728) - 1);
    sub_80026D8C(240497, 11225, (uint32)-1058, 1, 3, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(251634, 11225, (uint32)-1058, 0, 3, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(262834, 11225, (uint32)-1058, 1, 3, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(274097, 11225, (uint32)-1058, 0, 3, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(285297, 11225, (uint32)-1058, 1, 3, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(256398, 14781, (uint32)-749, 1, 5, 5, 0, 0, r_u16(0x80071728));
    return sub_80048448(0, 255, 128);
}
