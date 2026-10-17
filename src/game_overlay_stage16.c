#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_8004A184(void)
{
    sub_800456A8(22, 700);
    w_u16(0x800AED2C, 31);
    w_u16(0x800AED2E, 31);
    w_u16(0x800AED30, 32);
    w_u16(0x800AED32, 32);
    w_u16(0x800AED34, 33);
    w_u16(0x800AED36, 35);
    w_u16(0x800AED38, 47);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 400);
    w_u16(0x800AFB18, 400);
    w_u16(0x800AFB22, 400);
    w_u16(0x800AFB20, 400);
    w_u16(0x800AFB1C, 120);
    w_u16(0x800AFB24, 120);
    return sub_8001EEE8(494, 495, 493, 392, 350, 350, 350, 22, 2);
}

uint32 sub_8004A268(void)
{
    sub_800456A8(23, 450);
    w_u16(0x800AED54, 38);
    w_u16(0x800AED4C, 36);
    w_u16(0x800AED4E, 36);
    w_u16(0x800AED50, 37);
    w_u16(0x800AED52, 37);
    w_u16(0x800BFBF0, 350);
    w_u16(0x800AED56, 36);
    w_u16(0x800BFBF2, 350);
    w_u16(0x800AED58, 37);
    w_u16(0x800BFBF4, 350);
    sub_8001EE9C();
    return sub_8001EEE8(509, 510, 508, 405, 300, 300, 300, 23, 2);
}

uint32 sub_8004A328(void)
{
    sub_800456A8(25, 500);
    w_u16(0x800AED8C, 36);
    w_u16(0x800AED8E, 36);
    w_u16(0x800AED90, 37);
    w_u16(0x800AED92, 37);
    w_u16(0x800AED94, 38);
    w_u16(0x800AED96, 36);
    w_u16(0x800AED98, 37);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 200);
    w_u16(0x800AFB18, 200);
    w_u16(0x800AFB1C, 200);
    w_u16(0x800AFB22, 200);
    w_u16(0x800AFB20, 200);
    w_u16(0x800AFB24, 200);
    return sub_8001EEE8(544, 545, 543, 436, 200, 200, 200, 25, 2);
}

uint32 sub_8004A400(void)
{
    sub_800456A8(24, 500);
    w_u16(0x800AED6E, 6);
    w_u16(0x800AED70, 6);
    w_u16(0x800AED74, 9);
    w_u16(0x800AED76, 34);
    w_u16(0x800AED78, 47);
    w_u16(0x800AED6C, 5);
    w_u16(0x800AED72, 5);
    w_u16(0x800AED7A, 5);
    w_u16(0x800BFC16, 350);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 200);
    w_u16(0x800AFB18, 200);
    w_u16(0x800AFB1C, 200);
    w_u16(0x800AFB22, 200);
    w_u16(0x800AFB20, 200);
    w_u16(0x800AFB24, 200);
    return sub_8001EEE8(527, 528, 526, 421, 400, 400, 400, 24, 2);
}

uint32 sub_8004A828(void)
{
    sub_800456A8(26, 700);
    w_u16(0x800AEDAE, 6);
    w_u16(0x800AEDB0, 6);
    w_u16(0x800AEDB4, 44);
    w_u16(0x800AEDB6, 34);
    w_u16(0x800AEDB8, 34);
    w_u16(0x800AEDAC, 5);
    w_u16(0x800AEDB2, 5);
    w_u16(0x800AEDBA, 5);
    w_u16(0x800BFC56, 500);
    sub_8001EE9C();
    return sub_8001EEE8(645, 646, 644, 451, 400, 400, 400, 26, 2);
}

uint32 sub_8004A8E4(void)
{
    sub_800456A8(27, 600);
    w_u16(0x800AEDCE, 6);
    w_u16(0x800AEDD0, 6);
    w_u16(0x800AEDD4, 44);
    w_u16(0x800AEDCC, 5);
    w_u16(0x800AEDD2, 5);
    w_u16(0x800AEDD6, 34);
    sub_8001EE9C();
    w_u16(0x800AFB1C, 300);
    w_u16(0x800AFB1A, 300);
    w_u16(0x800AFB18, 300);
    w_u16(0x800AFB24, 300);
    w_u16(0x800AFB22, 300);
    w_u16(0x800AFB20, 300);
    w_u16(0x800AFB4C, 300);
    w_u16(0x800AFB4A, 300);
    w_u16(0x800AFB48, 300);
    w_u16(0x800AFB54, 300);
    w_u16(0x800AFB52, 300);
    w_u16(0x800AFB50, 300);
    return sub_8001EEE8(662, 663, 661, 466, 400, 400, 400, 27, 2);
}

static uint32 stage16_sound_init(void)
{
    if ((sint16)r_u16(0x80071734) != 4)
    {
        sub_80044734();
        sub_800447B0(66, 80);
        w_u8(0x80071998, 66);
        w_u8(0x800718C4, 67);
        w_u8(0x80071990, 68);
        w_u8(0x80071898, 69);
        sub_8004477C(66, 0);
        sub_8004477C(r_u8(0x800718C4), 0);
        sub_8004477C(r_u8(0x80071990), 0);
        sub_8004477C(r_u8(0x80071898), 0);
        sub_80044528(183, 66, 4);
        w_u16(0x80071734, 4);
    }
    return 4;
}

static void stage16_camera(void)
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

static void stage16_script(uint32 script)
{
    uint32 count = r_u16(0x80071728);
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u32(0x8007165C, script);
    w_u16(0x800717A0, count - 1);
}

uint32 legend_stage16_begin(void)
{
    sub_80014848();
    stage16_sound_init();
    sub_800495B0();
    sub_800498AC();
    sub_80049B5C();
    sub_8004A184();
    sub_8004A268();
    sub_8002B2A0(776);
    sub_800129E8();
    sub_8002B358(776);
    sub_8004591C(777, 0, 0);
    sub_8002292C(778);
    sub_8004B930(1);
    stage16_camera();
    sub_80030678();
    stage16_script(0x800CAD2C);
    return sub_80048448(0, 255, 160);
}

uint32 legend_stage17_begin(void)
{
    sub_80014848();
    stage16_sound_init();
    sub_80049504();
    sub_80049740();
    sub_80049990();
    sub_8004A184();
    sub_8004A268();
    sub_8002B2A0(779);
    sub_800129E8();
    sub_8002B358(779);
    sub_8004591C(780, 0, 0);
    sub_8002292C(781);
    sub_8004B930(1);
    stage16_camera();
    sub_80030678();
    stage16_script(0x800CB1C4);
    sub_80048448(0, 255, 160);
    sub_80026D8C((uint32)-4618, (uint32)-3529, 3247, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(3970, (uint32)-2211, 5097, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(8698, (uint32)-2211, 5097, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(17323, (uint32)-4292, 3276, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(26710, (uint32)-5206, 1911, 1, 2, 4, 0, 0, r_u16(0x80071728));
    return sub_80026D8C(24782, (uint32)-2211, (uint32)-5668, 1, 2, 4, 0, 0, r_u16(0x80071728));
}

uint32 legend_stage18_begin(void)
{
    sub_80014848();
    stage16_sound_init();
    sub_80049740();
    sub_800498AC();
    sub_8004A0D8();
    sub_8004A184();
    sub_8004A400();
    sub_8002B2A0(782);
    sub_800129E8();
    sub_8002B358(782);
    sub_8004591C(783, 0, 0);
    sub_8002292C(784);
    sub_8004B930(1);
    stage16_camera();
    sub_80030678();
    stage16_script(0x800CB49C);
    sub_80048448(0, 255, 160);
    sub_80026D8C((uint32)-39951, (uint32)-1573, 1112, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-25455, (uint32)-836, 1112, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-19431, 42, 3969, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-14210, 185, 4031, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-6383, (uint32)-766, 1112, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-11183, (uint32)-466, 1112, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(3252, (uint32)-1366, 1002, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(12816, (uint32)-1966, 1112, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(22416, (uint32)-2566, 1112, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(28678, (uint32)-2357, 3934, 1, 2, 4, 0, 0, r_u16(0x80071728));
    return sub_80026D8C(33789, (uint32)-2214, 4031, 1, 2, 4, 0, 0, r_u16(0x80071728));
}

uint32 legend_stage19_begin(void)
{
    sub_80014848();
    stage16_sound_init();
    sub_8004A0D8();
    sub_8004A328();
    sub_8004A400();
    sub_80019BD4(785, 489, 400, 400, 400, 0);
    sub_80019648(489, 150, 150, 150);
    sub_8002B2A0(786);
    sub_800129E8();
    sub_8002B358(786);
    sub_8004591C(787, 0, 0);
    sub_8002292C(788);
    sub_8004B930(2);
    stage16_camera();
    sub_8002F520();
    stage16_script(0x800CB880);
    sub_80048448(0, 255, 160);
    sub_80027094(12, 21, r_u8(0x80071898), 500, 13000);
    sub_8002B0D0(12, 21);
    sub_8002AC70();
    sub_80026D8C((uint32)-33217, (uint32)-2744, 6728, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-25194, (uint32)-1210, (uint32)-3497, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-25213, (uint32)-2744, 6838, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-25194, (uint32)-1210, (uint32)-3497, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-17326, (uint32)-710, 7584, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-18793, (uint32)-710, (uint32)-915, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-4307, (uint32)-2744, 11638, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C((uint32)-20412, (uint32)-2744, 11528, 1, 2, 4, 0, 0, r_u16(0x80071728));
    return sub_80026D8C((uint32)-27652, (uint32)-2744, 11638, 1, 2, 4, 0, 0, r_u16(0x80071728));
}

uint32 legend_stage20_begin(void)
{
    sub_80014848();
    stage16_sound_init();
    sub_80049E94();
    sub_8004A0D8();
    sub_8004A184();
    sub_8004A268();
    sub_8004A400();
    sub_8002B2A0(789);
    sub_800129E8();
    sub_8002B358(789);
    sub_8004591C(790, 0, 0);
    sub_8002292C(791);
    sub_8004B930(4);
    stage16_camera();
    sub_8003008C();
    stage16_script(0x800CBC54);
    sub_80048448(0, 255, 200);
    sub_80027094(24, 58, r_u8(0x80071990), 1400, 30000);
    sub_80027094(24, 58, r_u8(0x80071898), 500, 13000);
    return sub_8002B06C(24, 58);
}

uint32 legend_stage21_begin(void)
{
    sub_80014848();
    stage16_sound_init();
    sub_8004A184();
    sub_8004A268();
    sub_8004A400();
    sub_8004A828();
    sub_8004A8E4();
    sub_8002B2A0(792);
    sub_800129E8();
    sub_8002B358(792);
    sub_8004591C(793, 0, 0);
    sub_8002292C(794);
    sub_8004B930(6);
    stage16_camera();
    sub_80030678();
    stage16_script(0x800CBFE4);
    sub_80048448(0, 255, 160);
    sub_80027094(0, r_u16(0x80071728), r_u8(0x80071990), 1400, 30000);
    sub_80027094(0, r_u16(0x80071728), r_u8(0x80071898), 500, 13000);
    sub_8002B06C(0, r_u16(0x80071728));
    sub_80026D8C(237517, (uint32)-1110, (uint32)-3736, 1, 2, 4, 0, 0, r_u16(0x80071728));
    sub_80026D8C(250407, (uint32)-1110, (uint32)-3736, 1, 2, 4, 0, 0, r_u16(0x80071728));
    return sub_80026D8C(256758, (uint32)-1110, (uint32)-3736, 1, 2, 4, 0, 0, r_u16(0x80071728));
}

uint32 sub_8002AC70(void)
{
    uint32 node = sub_80032EF0();
    if (node)
    {
        w_u32(node + 8, 61);
        w_u16(node + 12, 0);
        w_u16(node + 18, 0);
        w_u16(node + 16, 0);
    }
    return 61;
}

uint32 sub_8002B06C(uint32 first, uint32 last)
{
    uint32 node = sub_80032EF0(), result = 60;
    if (node)
    {
        w_u32(node + 8, 60);
        w_u16(node + 12, first);
        w_u16(node + 14, last);
        result = (sub_80011B8C() & 255) + 30;
        w_u16(node + 16, result);
    }
    return result;
}

uint32 sub_8002B0D0(uint32 first, uint32 last)
{
    uint32 node = sub_80032EF0(), result = 62;
    if (node)
    {
        w_u32(node + 8, 62);
        w_u16(node + 12, first);
        w_u16(node + 14, last);
        result = (sub_80011B8C() & 255) + 30;
        w_u16(node + 16, result);
    }
    return result;
}

uint32 sub_8003008C(void)
{
    uint32 buffer = sub_80011A98(2560), node, i;
    w_u32(0x80071530, buffer);
    for (i = 0; i < 64; ++i)
    {
        node = buffer + 40 * i;
        w_u32(node, (uint32)randPSX() & 511);
        w_u32(node + 4, (uint32)randPSX() & 511);
        w_u32(node + 8, (uint32)randPSX() & 511);
        w_u16(node + 16, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 24, 5 + ((uint32)randPSX() & 7));
        w_u16(node + 32, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 18, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 26, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 34, 5 + ((uint32)randPSX() & 7));
        w_u16(node + 20, 0);
        w_u16(node + 28, 0);
        w_u16(node + 36, 0);
    }
    return 0;
}

void sub_800369DC(uint32 node)
{
    uint32 region = r_u16(0x800BC0CC), kind, timer, channel;
    if (region == 0xFFFF)
        return;
    kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
    if ((sint32)kind < (sint16)r_u16(node + 12) || kind > r_u8(node + 14))
        return;
    timer = r_u16(node + 16);
    w_u16(node + 16, timer - 1);
    if (timer)
        return;
    w_u16(node + 16, (sub_80011B8C() & 255) + 30);
    sub_8004EC38(8);
    w_u16(0x8007158C, 64);
    w_u16(0x80071A50, 8);
    channel = (uint16)sub_800448F4();
    sub_8004486C(1, channel, 24, 500, 16000, 512);
}

uint32 sub_8003D688(uint32 node)
{
    return sub_8003D538(node + 12, 0x800687A4);
}

void sub_8003EA78(uint32 node)
{
    uint32 region = r_u16(0x800BC0CC), kind, timer, table, player, heading;
    uint32 position[4], distances[8], address, proximity;
    if (region == 0xFFFF)
        return;
    kind = r_u8(r_u32(0x80071704) + 14 * region + 9);
    if ((sint32)kind < (sint16)r_u16(node + 12) || kind > r_u8(node + 14))
        return;
    timer = r_u16(node + 16);
    w_u16(node + 16, timer - 1);
    if (timer)
        return;
    w_u16(node + 16, (sub_80011B8C() & 255) + 60);
    table = 0x800687D4 + 12 * (sub_80011B8C() & 3);
    position[0] = r_u32(table) + 512;
    position[1] = r_u32(table + 4);
    position[2] = r_u32(table + 8);
    /* The constructor copies a fourth position word that is not a coordinate */
    position[3] = 0;
    address = draft_local_address(position, sizeof(position));
    proximity = draft_local_address(distances, sizeof(distances));
    sub_80051F74(address, proximity);
    player = r_u16(proximity + 24);
    heading = sub_80046B84(r_u32(0x800AFEC0 + 288 * player) - position[0], r_u32(0x800AFEC8 + 288 * player) - position[2], r_u32(proximity + 16 + 4 * player));
    position[1] += 2048;
    sub_80028C94(address, (uint32)(sint32)(sint16)heading);
}
