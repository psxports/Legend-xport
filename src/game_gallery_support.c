#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_800208F4(void)
{
    w_u16(0x1F800020, 0 - r_u16(0x800BBFD4));
    w_u16(0x1F800024, 0 - r_u16(0x800BBFD8));
    w_u16(0x1F800022, 0 - r_u16(0x800BBFD6));
    return sub_8005D3C8(0x1F800020, 0x800BBFFC);
}

void sub_80022660(void)
{
    uint32 i, count = 0, x = 0, y = 0, a, b;
    sint32 average_x, average_y;
    for (i = 0; i < 2; ++i)
    {
        if (r_u8(0x800AFFB0 + 288 * i))
        {
            ++count;
            x += r_u16(0x800C1CAC + 64 * i) - 192;
            y += r_u16(0x800C1CAE + 64 * i) - 120;
        }
    }
    a = r_u32(0x800BC09C);
    b = r_u32(0x800BC0A0);
    w_u32(0x800BBFD4, a);
    w_u32(0x800BBFD8, b);
    if (count)
    {
        average_x = (sint16)((sint16)x / (sint32)count);
        average_y = (sint16)((sint16)y / (sint32)count);
        w_u16(0x800BBFD6, r_u16(0x800BBFD6) - average_x / 4);
        w_u16(0x800BBFD4, r_u16(0x800BBFD4) + average_y / 4);
    }
    sub_80020DD8();
}

uint32 sub_800293B0(uint32 position, uint32 target, uint32 player)
{
    uint32 node = sub_80032EF0(), mesh, collision, a, b, c, d;
    if (!node)
        return 37;
    w_u32(node + 8, 37);
    mesh = sub_8001A3BC();
    sub_8001A2FC(489, mesh);
    w_u16(mesh + 86, 1);
    a = r_u32(position);
    b = r_u32(position + 4);
    c = r_u32(position + 8);
    d = r_u32(position + 12);
    w_u32(mesh + 8, a);
    w_u32(mesh + 12, b);
    w_u32(mesh + 16, c);
    w_u32(mesh + 20, d);
    w_u32(node + 12, mesh);
    collision = sub_800474F4();
    w_u32(node + 16, collision);
    sub_80047534(collision, mesh, 1);
    w_u16(collision + 138, player);
    w_u16(collision + 142, 0);
    w_u16(node + 24, 0xFFFF);
    w_u32(node + 20, sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 24));
    a = r_u32(target);
    b = r_u32(target + 4);
    c = r_u32(target + 8);
    d = r_u32(target + 12);
    w_u32(node + 44, a);
    w_u32(node + 48, b);
    w_u32(node + 52, c);
    w_u32(node + 56, d);
    w_u16(node + 26, 0);
    return a;
}

uint32 sub_80047CAC(uint32 x, uint32 y, uint32 depth, uint32 position, uint32 radius)
{
    uint32 i, half, xy;
    if ((sint32)depth < (sint32)r_u32(position + 8))
        return 0;
    for (i = 0; i < 3; ++i)
        w_u32(0x1F800028 + 4 * i, r_u32(position + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    for (i = 0; i < 3; ++i)
        draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
    half = (0 - radius) & 0xFFFF;
    draft_gte_data(0, half | (half << 16));
    draft_gte_data(1, 0);
    draft_gte_command(0x180001);
    xy = draft_gte_read(14);
    if ((sint32)x < (sint16)xy || (sint32)y < (sint16)(xy >> 16))
        return 0;
    half = radius & 0xFFFF;
    draft_gte_data(0, half | (half << 16));
    draft_gte_data(1, 0);
    draft_gte_command(0x180001);
    xy = draft_gte_read(14);
    return (sint16)xy >= (sint32)x && (sint16)(xy >> 16) >= (sint32)y;
}

uint32 sub_80047E40(uint32 record, uint32 collision)
{
    uint32 result, i, j, mesh, model, count, radius, box;
    result = (uint16)sub_80047CAC((uint32)(sint32)(sint16)r_u16(record + 48), (uint32)(sint32)(sint16)r_u16(record + 50), r_u32(record + 28), collision, r_u32(collision + 16));
    if (!result)
        return result;
    result = r_u32(collision + 20);
    if ((sint32)result <= 0)
        return result;
    i = 0;
    do
    {
        mesh = r_u32(collision + 24 + 4 * i);
        model = r_u32(mesh + 80);
        count = r_u16(model + 52);
        radius = (uint32)(sint32)(sint16)r_u16(model + 54);
        for (j = 0; j < count; ++j)
        {
            box = mesh + 100 + 16 * j;
            if ((uint16)sub_80047CAC((uint32)(sint32)(sint16)r_u16(record + 48), (uint32)(sint32)(sint16)r_u16(record + 50), r_u32(record + 28), box, radius))
                legend_gallery_unproject((uint32)(sint32)(sint16)r_u16(record + 48), (uint32)(sint32)(sint16)r_u16(record + 50), r_u32(mesh + 108 + 16 * j), record + 20);
        }
        i = (uint16)(i + 1);
    } while ((sint32)i < (sint32)r_u32(collision + 20));
    return i;
}

uint32 sub_80047F74(void)
{
    uint32 player, record, first, z, i, collision;
    sint32 product;
    for (player = 0; player < 2; ++player)
    {
        if (!r_u8(0x800AFFB0 + 288 * player))
            continue;
        first = r_u32(0x80071974);
        record = 0x800C1C7C + 64 * player;
        product = (sint32)(10000 * (r_u32(0x800719A8) - first) * (uint32)(sint32)(sint16)r_u16(record + 48));
        z = (uint32)((product / 384) / 10000) + first;
        legend_gallery_unproject((uint32)(sint32)(sint16)r_u16(record + 48), (uint32)(sint32)(sint16)r_u16(record + 50), z, record + 20);
        for (i = 0; i < r_u16(0x80071668); ++i)
        {
            collision = r_u32(0x800BEFD0 + 4 * i);
            if (!r_u32(collision + 16))
                sub_80047224(collision);
            sub_80047E40(record, collision);
        }
    }
    return 0;
}

uint32 sub_8004F690(uint32 actor, uint32 x)
{
    uint32 i, digit, started = 0;
    sint32 left = (sint16)x;
    sub_80017FB0((uint32)(left + 30), 192, 1, 56);
    sub_80017FB0((uint32)(left + 38), 192, 1, r_u16(actor + 208) + 59);
    for (i = 0; i < 6; ++i)
    {
        digit = (uint16)(r_u8(actor + 250 + i) + 11);
        if (digit >= 60)
            started = 1;
        if (started || i == 5)
            sub_80017FB0((uint32)(left + 62 + 8 * (sint32)i), 192, 1, digit);
    }
    sub_8004EDD8((uint32)left, 224, r_u32(0x80068AF0 + 4 * r_u8(actor + 212)));
    sub_80017FB0((uint32)(left + 12), 224, 1, 4 * r_u8(actor + 212) + r_u8(actor + 213) + 115);
    sub_8004E9E4((uint32)(sint32)(sint16)(x + 30), 208, r_u16(actor + 210), 72, 128);
    sub_80017FB0((uint32)(left + 39), 235, 1, 199);
    sub_80017FB0((uint32)(left + 45), 222, 1, 28);
    return sub_80017FB0((uint32)(left + 53), 224, 1, r_u8(actor + 280) + 59);
}

uint32 sub_8004F9F0(void)
{
    uint32 time, first, second;
    if (r_u16(0x80071828))
    {
        w_u16(0x80071750, r_u16(0x80071750) + 1);
        if (r_u16(0x80071750) == 30)
        {
            if (r_u16(0x80071940))
                w_u16(0x80071940, r_u16(0x80071940) - 1);
            w_u16(0x80071750, 0);
        }
    }
    time = r_u16(0x80071940);
    first = (uint16)(time / 10);
    second = (uint16)(time - 10 * first);
    if (time < 10)
    {
        sub_800180D4(164, 40, 1, first + 245, 128, 0, 0);
        return sub_800180D4(192, 40, 1, second + 245, 128, 0, 0);
    }
    sub_80017FB0(164, 40, 1, first + 245);
    return sub_80017FB0(192, 40, 1, second + 245);
}

uint32 sub_80050FFC(void)
{
    uint8 line[32];
    uint32 source, output, red, green, blue, count, result = r_u16(0x80071764);
    sint32 y, width;
    if (!result)
        return result;
    red = (r_u16(0x800719D0) & 1) << 7;
    green = (r_u16(0x800719D0) & 2) << 6;
    blue = (r_u16(0x800719D0) & 4) << 5;
    source = r_u32(0x80068AFC + 4 * r_u16(0x80071950));
    y = 110 - 8 * (uint16)(r_u8(source++) - 48);
    output = draft_local_address(line, sizeof(line));
    while (r_u8(source))
    {
        count = 0;
        while (r_u8(source) != 124)
            w_u8(output + (uint16)count++, r_u8(source++));
        ++source;
        w_u8(output + (uint16)count, 0);
        width = (sint16)sub_8004ED48(output);
        sub_8004EEFC((uint32)(sint32)(sint16)(192 - width / 2), (uint32)(sint32)(sint16)y, output, red, green, blue, 0);
        y += 16;
    }
    result = r_u16(0x80071764) - 1;
    w_u16(0x80071764, result);
    return result;
}

uint32 sub_80051174(void)
{
    sub_80050414();
    sub_80050FFC();
    if (r_u16(0x80071930))
        sub_80050A08();
    else
    {
        if (r_u8(0x800AFFB0))
            sub_8004F690(0x800AFEC0, 20);
        if (r_u8(0x800B00D0))
            sub_8004F690(0x800AFFE0, 228);
    }
    return sub_8004F9F0();
}
