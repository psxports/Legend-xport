#include "psx.h"
#include "game_draft_signatures.h"

extern uint32 sub_8005B278(uint32 mode);
extern uint32 sub_8005E4D0(uint32 ordering_table, uint32 count);
extern uint32 sub_8005DFE4(uint32 mode);
extern uint32 sub_8005C154(uint32 counter);
extern uint32 sub_8005E814(uint32 environment);
extern uint32 sub_8005E648(uint32 environment);
extern void sub_8005E5D8(uint32 ordering_table);

static uint32 gallery_extra_resources(void)
{
    return sub_8001EEE8(729, 730, 728, 451, 400, 400, 400, 26, 2);
}

static void gallery_camera_init(uint32 region, uint32 height, uint32 offset)
{
    uint32 angle = sub_8005129C((uint16)region, 64, 0x800BBFC4), y = r_u32(0x800BBFC8), a, b;
    w_u16(0x800BBFD6, (5119 - angle) & 4095);
    w_u16(0x800BBFD4, 0);
    w_u16(0x800BBFD8, 0);
    sub_8005129C((uint16)region, offset, 0x800BBFC4);
    w_u32(0x800BBFC8, y + height);
    a = r_u32(0x800BBFD4);
    b = r_u32(0x800BBFD8);
    w_u32(0x800BC09C, a);
    w_u32(0x800BC0A0, b);
}

static uint32 gallery_player_init(uint32 region, uint32 player, uint32 lateral, uint32 height, uint32 offset)
{
    uint32 index = (uint16)player, record = 0x800C1C7C + 64 * index, mesh, weapon, muzzle, y, a, b, angle;
    w_u32(record + 4, 0);
    w_u32(record, 0);
    if (!r_u8(0x800AFFB0 + 288 * index))
        return 0;
    w_u16(record + 40, player);
    mesh = sub_8001A3BC();
    w_u32(record, mesh);
    weapon = sub_8001A3BC();
    sub_8001A2FC(488, weapon);
    w_u32(record + 4, weapon);
    sub_8001A2BC(mesh, weapon, 0, 0, 0);
    muzzle = sub_8001A3BC();
    sub_8001A2FC(489, muzzle);
    w_u32(record + 8, muzzle);
    sub_8001A2BC(weapon, muzzle, 0, (uint32)-170, 300);
    w_u16(record + 42, region);
    sub_8005129C((uint32)(sint32)(sint16)region, 64, mesh + 8);
    y = r_u32(mesh + 12);
    angle = r_u16(r_u32(0x800716D0) + 2 * (uint32)(sint32)(sint16)region);
    w_u16(record + 46, 0xFFFF);
    w_u16(record + 44, angle);
    sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), record + 46);
    sub_8005129C((uint32)(sint32)(sint16)region, offset, mesh + 8);
    w_u32(mesh + 12, y);
    w_u16(0x1F800020, 0);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, (r_u16(record + 44) - 1024) & 4095);
    sub_8005D138(0x1F800020, 0x1F800000);
    w_u16(0x1F800020, lateral);
    w_u16(0x1F800022, 0);
    w_u16(0x1F800024, 0);
    sub_8005CDD8(0x1F800000, 0x1F800020, 0x1F800028);
    w_u32(mesh + 8, r_u32(mesh + 8) + r_u32(0x1F800028));
    w_u32(mesh + 16, r_u32(mesh + 16) + r_u32(0x1F800030));
    w_u16(mesh + 24, 0);
    w_u16(mesh + 26, (r_u16(record + 44) - 1024) & 4095);
    w_u16(mesh + 26, 0);
    a = r_u32(mesh + 24);
    b = r_u32(mesh + 28);
    w_u32(record + 12, a);
    w_u32(record + 16, b);
    w_u32(record + 36, r_u32(mesh + 12));
    w_u32(mesh + 12, r_u32(mesh + 12) + height);
    w_u16(record + 48, 64 * index + 160);
    w_u16(record + 52, 0);
    w_u16(record + 50, 120);
    w_u16(record + 56, 0);
    w_u16(record + 54, 0);
    w_u16(record + 58, 0);
    w_u16(record + 60, 0);
    return 120;
}

static uint32 gallery_setup(uint32 region, uint32 offset)
{
    static const uint32 initial_zero[] = {0x800719D0, 0x800715E8, 0x8007156C, 0x8007155C, 0x8007158C};
    static const uint32 reset[] = {0x80071820, 0x8007172C, 0x800717F4, 0x80071808, 0x800717AC, 0x80071744, 0x800715CC, 0x8007188C, 0x800716E8, 0x80071804, 0x80071678, 0x800715BC, 0x80071930, 0x800717C4};
    uint32 i, first, last, result;
    sub_80031154();
    sub_80032DFC();
    sub_80044800();
    w_u32(0x80071A1C, sub_80011A98(256));
    for (i = 0; i < sizeof(initial_zero) / sizeof(initial_zero[0]); ++i)
        w_u16(initial_zero[i], 0);
    w_u16(0x80071A50, 8);
    w_u16(0x8007198C, 0);
    w_u16(0x800719FC, 0);
    w_u16(0x80071750, 0);
    w_u16(0x80071828, 0);
    sub_8004B87C();
    if (r_u8(0x800AFFB0) && r_u8(0x800B00D0))
    {
        gallery_player_init(region, 0, (uint32)-500, (uint32)-1500, offset);
        gallery_player_init(region, 1, 500, (uint32)-1500, offset);
    }
    else
    {
        gallery_player_init(region, 0, 0, (uint32)-1500, offset);
        gallery_player_init(region, 1, 0, (uint32)-1500, offset);
    }
    sub_80020124();
    gallery_camera_init((uint16)region, (uint32)-2000, offset + 15);
    sub_8002043C(768, 5, 0);
    sub_8002046C(768, 5, 0);
    w_u16(0x80071810, 1);
    for (i = 0; i < sizeof(reset) / sizeof(reset[0]); ++i)
        w_u16(reset[i], 0);
    w_u16(0x80071A34, 0xFFFF);
    w_u16(0x80071764, 0);
    for (i = 0; i < 16; ++i)
    {
        w_u8(0x800C9D68 + i, 0);
        w_u16(0x800BEE88 + 18 * i, 0xFFFF);
    }
    sub_8005D0D8(0x80071818, 0x8007181C);
    result = ReadGeomScreen();
    first = r_u32(r_u32(0x800718E4) + 8 * (uint16)region - 20);
    last = r_u32(r_u32(0x800718E4) + 8 * (uint16)region + 28);
    w_u32(0x800715A4, result);
    w_u16(0x80071A38, 0);
    w_u32(0x80071974, first);
    w_u32(0x800719A8, last);
    return result;
}

static uint32 gallery_player_cleanup(void)
{
    uint32 i, record;
    for (i = 0; i < 2; ++i)
    {
        record = 0x800C1C7C + 64 * i;
        if (r_u32(record + 4))
        {
            sub_80011AF8(r_u32(record));
            sub_80011AF8(r_u32(record + 4));
            sub_80011AF8(r_u32(record + 8));
        }
    }
    return 2;
}

uint32 legend_gallery_unproject(uint32 x, uint32 y, uint32 z, uint32 output)
{
    uint32 depth = z - r_u32(0x800BBFCC), i;
    sint32 denominator = (sint32)r_u32(0x800715A4), product_x, product_y, projected_x, projected_y;
    if (!depth)
        depth = 1;
    product_x = (sint32)((x - r_u32(0x80071818)) * depth);
    if (!denominator || (denominator == -1 && product_x == (sint32)0x80000000))
        return draft_unknown_return("overlay162 CA554 DIV BREAK");
    projected_x = product_x / denominator;
    product_y = (sint32)((y - r_u32(0x8007181C)) * depth);
    if (!denominator || (denominator == -1 && product_y == (sint32)0x80000000))
        return draft_unknown_return("overlay162 CA554 DIV BREAK");
    projected_y = product_y / denominator;
    w_u32(0x1F800030, depth);
    w_u32(0x1F800028, (uint32)projected_x);
    w_u32(0x1F80002C, (uint32)projected_y);
    sub_8005CC48(0x800BBFFC, 0x1F800028, output);
    for (i = 0; i < 3; ++i)
        w_u32(output + 4 * i, r_u32(output + 4 * i) + r_u32(0x800BBFC4 + 4 * i));
    return r_u32(output + 8);
}

static void gallery_player_update(uint32 player)
{
    static const uint32 directions[] = {0x8000, 0x2000, 0x1000, 0x4000};
    uint32 index = (uint16)player, record = 0x800C1C7C + 64 * index, weapon, mesh, pad, state, i, coordinate, step, pulse, a, b;
    sint32 delta;
    if (!r_u8(0x800AFFB0 + 288 * index))
        return;
    mesh = r_u32(record);
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    mesh = r_u32(record);
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    pad = 0x80071790 + 2 * index;
    w_u16(record + 54, r_u16(pad));
    if (!r_u16(0x80071810))
        w_u16(record + 54, 0);
    w_u16(record + 54, r_u16(record + 54) & ~r_u16(record + 56));
    w_u16(record + 56, r_u16(record + 56) & r_u16(pad));
    weapon = r_u32(record + 4);
    if ((sint16)r_u16(weapon + 4))
        w_u16(weapon + 4, r_u16(weapon + 4) + 32);
    state = r_u16(record + 58);
    if (!state && (r_u16(record + 54) & 0x80))
    {
        w_u16(record + 58, 1);
        weapon = r_u32(record + 4);
        w_u16(record + 56, r_u16(record + 56) | 0x80);
        w_u16(weapon + 4, (uint32)-256);
        sub_8003FA6C();
        w_u16(r_u32(record + 8) + 88, 0);
        sub_800293B0(r_u32(record + 8) + 8, record + 20, index);
    }
    else if (state == 1 && !(sint16)r_u16(r_u32(record + 4) + 4))
    {
        w_u16(record + 58, 0);
        w_u16(r_u32(record + 8) + 88, 1);
    }
    if (!(r_u16(record + 54) & 0xF000))
        w_u16(record + 52, 0);
    for (i = 0; i < 4; ++i)
    {
        if (!(r_u16(record + 54) & directions[i]))
            continue;
        step = r_u16(record + 52) + 2;
        coordinate = record + (i < 2 ? 48 : 50);
        w_u16(record + 52, step);
        w_u16(coordinate, r_u16(coordinate) + ((i & 1) ? step : 0 - step));
    }
    if ((sint16)r_u16(record + 52) >= 8)
        w_u16(record + 52, 7);
    if ((sint16)r_u16(record + 48) < 10)
        w_u16(record + 48, 10);
    if ((sint16)r_u16(record + 48) >= 361)
        w_u16(record + 48, 360);
    if ((sint16)r_u16(record + 50) < 0)
        w_u16(record + 50, 0);
    if ((sint16)r_u16(record + 50) >= 241)
        w_u16(record + 50, 240);
    pulse = r_u16(0x800719D0) & 31;
    if (pulse >= 16)
        pulse = 31 - pulse;
    pulse = 4 * (pulse + 16);
    sub_800180D4((uint32)(sint32)(sint16)r_u16(record + 48), (uint32)(sint32)(sint16)r_u16(record + 50), 160, index + 280, pulse, pulse, pulse);
    mesh = r_u32(record);
    a = r_u32(record + 12);
    b = r_u32(record + 16);
    w_u32(mesh + 24, a);
    w_u32(mesh + 28, b);
    delta = (sint32)r_u16(record + 48) - 192;
    mesh = r_u32(record);
    w_u16(mesh + 26, r_u16(mesh + 26) + delta + ((sint16)delta >> 1));
    delta = (sint32)r_u16(record + 50) - 120;
    mesh = r_u32(record);
    w_u16(mesh + 24, r_u16(mesh + 24) - delta - ((sint16)delta >> 2));
    sub_80046278(r_u16(record + 46));
    sub_8001DEB0(r_u32(record));
}

static uint32 gallery_sound_init(void)
{
    if ((sint16)r_u16(0x80071734) != 5)
    {
        sub_80044734();
        sub_800447B0(66, 80);
        w_u8(0x80071998, 66);
        w_u8(0x800719D8, 67);
        w_u8(0x800719DC, 68);
        sub_8004477C(66, 0);
        sub_8004477C(r_u8(0x800719DC), 0);
        sub_80044528(163, 66, 3);
        w_u16(0x80071734, 5);
    }
    return 5;
}

static uint32 gallery_stage_begin(uint32 stage)
{
    uint32 i, map = stage == 7 ? 742 : stage == 22 ? 744 : 746;
    uint32 script = stage == 7 ? 0x800CB494 : stage == 22 ? 0x800CB5CC : 0x800CB6D4;
    sub_8005D128(256);
    sub_80014848();
    gallery_sound_init();
    for (i = 0; i < 4; ++i)
        sub_80019648(i + 31, 200, 200, 200);
    sub_80019648(38, 150, 150, 150);
    sub_80014F0C(725, 280, 1000);
    sub_80019BD4(726, 488, 400, 400, 400, 2);
    sub_80019BD4(727, 489, 400, 400, 400, 2);
    sub_80019648(489, 100, 100, 100);
    if (stage != 7)
        gallery_extra_resources();
    sub_8002B2A0(map);
    sub_800129E8();
    sub_8002B358(map);
    sub_8004591C(map + 1, 0, 0);
    gallery_setup(20, stage == 7 ? 160 : 140);
    sub_80030678();
    w_u16(0x80071774, 0);
    w_u16(0x80071778, 0);
    w_u32(0x8007165C, script);
    w_u16(0x800717A0, r_u16(0x80071728) - 1);
    sub_80048448(0, 255, 128);
    w_u16(0x80071940, 35);
    if (stage == 23)
    {
        sub_80027094(0, 72, r_u8(0x800719DC), 800, 15000);
        return sub_80027114(0, 72, r_u8(0x800719D8), 800, 26000, 160);
    }
    return 35;
}

static uint32 gallery_cleanup(void)
{
    uint32 i;
    sub_8005D128(400);
    sub_8002B238();
    sub_80045700();
    for (i = 119; i < 512; ++i)
        sub_80018CFC(i);
    for (i = 3; i < 32; ++i)
        sub_800573EC(i);
    sub_8003F638();
    sub_800311E4();
    gallery_player_cleanup();
    sub_80011AF8(r_u32(0x80071A1C));
    sub_80030748();
    return sub_8004B4F0();
}

uint32 legend_gallery_run(void)
{
    uint32 stage = r_u16(0x80071594);
    if (stage == 7 || stage == 22 || stage == 23)
        gallery_stage_begin(stage);
    sub_80048154();
    sub_8005B278(0);
    w_u16(0x8007194C, 254);
    w_u16(0x800717A4, (uint32)-8);
    w_u16(0x800716FC, 2);
    sub_8005B278(0);
    sub_80048180();
    sub_80013B64(1, 0, 0, 0);
    sub_800451B8(0, 1, 0, 2);
    while ((sint16)r_u16(0x8007194C) != 255 || (sint16)r_u16(0x800717A4))
    {
        w_u32(0x80071700, sub_8005C008(0x1F8003FC));
        sub_80011BB8();
        sub_80058678();
        sub_80048EB8();
        sub_80049180();
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184C), 2500);
        sub_800471D8();
        sub_80047590();
        sub_8002B134();
        sub_8003F008();
        sub_800208F4();
        sub_80047F74();
        gallery_player_update(0);
        gallery_player_update(1);
        w_u16(0x800BC0CC, r_u16(0x800C1CAA));
        sub_800470FC();
        sub_80047B68();
        sub_8003220C();
        sub_8004EC74();
        sub_8002B9B4();
        sub_80022660();
        sub_800206D8();
        sub_80051174();
        sub_8002F0F8();
        sub_8002F36C();
        sub_8003076C();
        sub_8002FC3C();
        sub_800485D0(r_u32(0x8007184C) + 9996);
        sub_8005C008(r_u32(0x80071700));
        sub_8004BD40();
        sub_800140DC();
        sub_80045048(0);
        sub_80044A5C(1);
        sub_8005DFE4(0);
        if (r_u16(0x800717D0))
        {
            sub_80012330((uint32)(sint32)(sint16)r_u16(0x800715EC), (uint32)(sint32)(sint16)r_u16(0x80071578), (uint32)(sint32)(sint16)r_u16(0x800716F0), (uint32)(sint32)(sint16)r_u16(0x8007162C));
            w_u16(0x800717D0, 0);
        }
        w_u32(0x800719F0, r_u32(0x800719D4));
        if (r_u16(0x800717C4))
        {
            sub_8005B278(4);
            w_u16(0x800717C4, r_u16(0x800717C4) - 1);
        }
        else
        {
            while ((sint32)sub_8005C154(0xF2000001) < 507)
            {
            }
        }
        sub_80048180();
        sub_8005E814(r_u32(0x800719F0));
        sub_8005E648(r_u32(0x800719CC));
        sub_8005E5D8(r_u32(0x8007184C) + 9996);
        w_u16(0x800719D0, r_u16(0x800719D0) + 1);
        w_u16(0x800715E8, r_u16(0x800715E8) ^ 1);
        sub_8004C720();
        if (!r_u16(0x80071A38))
        {
            if (r_u8(0x800AFFB0) && ((r_u16(0x80071790) & 0x800) || !r_u16(0x80071A24)))
                sub_8004C7C4(0);
            if (r_u8(0x800B00D0) && ((r_u16(0x80071792) & 0x800) || !r_u16(0x80071A26)))
                sub_8004C7C4(1);
        }
    }
    sub_80013B64(0, 0, 0, 0);
    gallery_cleanup();
    sub_80013974();
    sub_800451B8(0x8000, (uint32)-8, 0x8000, (uint32)-4);
    sub_80045048(2);
    sub_80013F80();
    return sub_800455DC();
}
