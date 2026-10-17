#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80050578(uint32 x, uint32 y, uint32 value)
{
    uint8 text[7];
    uint32 divisor = 100000, started = 0, i, digit;
    for (i = 0; i < 6; ++i)
    {
        digit = value / divisor;
        if (digit)
            started = 1;
        text[i] = (uint8)((started || i == 5) ? digit + 48 : 32);
        value %= divisor;
        divisor /= 10;
    }
    text[6] = 0;
    return sub_8004EEFC((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)y, draft_local_address(text, sizeof(text)), 128, 128, 128, 0);
}

uint32 sub_8005094C(uint32 current, uint32 target, uint32 total, uint32 player)
{
    uint32 previous = r_u32(current), delta = r_u32(target) - previous;
    uint32 divisor = 100000, value, digit, product, text = 0x800AFFBA + 288 * (uint16)player, i;
    if (delta >= 151)
        delta = 150;
    w_u32(current, previous + delta);
    value = delta + r_u32(total);
    w_u32(total, value);
    for (i = 0; i < 6; ++i)
    {
        digit = value / divisor;
        product = digit * divisor;
        w_u8(text + i, digit + 48);
        divisor /= 10;
        value -= product;
    }
    return 0;
}

uint32 sub_80050664(uint32 slide)
{
    uint32 base = 80, player, spacing = 0, offset, x, packet, mode, ordering, result, i;
    if (r_u8(0x800AFFB0) && r_u8(0x800B00D0))
        base = 32;
    for (i = 0; i < 6; ++i)
        sub_8004EDD8((uint32)(sint32)(sint16)(base - slide), 112 + 16 * i, r_u32(0x80068B48 + 4 * i));
    for (player = 0; player < 2; ++player)
    {
        if (!r_u8(0x800AFFB0 + 288 * player))
            continue;
        sub_80017FB0(base + spacing + 144, (uint32)(112 - ((sint16)slide + 8)), 1, 4 * r_u8(0x800AFF94 + 288 * player) + 118);
        x = (uint32)(sint32)(sint16)(base + spacing - slide + 96);
        spacing += 104;
        offset = 4 * player;
        sub_80050578(x, 112, r_u32(0x8007173C + offset));
        sub_80050578(x, 128, r_u32(0x80071708 + offset));
        sub_80050578(x, 144, r_u32(0x800716A8 + offset));
        sub_80050578(x, 176, r_u32(0x800719E8 + offset));
        sub_80050578(x, 192, r_u32(0x80071908 + offset));
    }
    packet = r_u32(0x80071680);
    w_u32(0x80071680, packet + 40);
    w_u8(packet + 3, 3);
    w_u8(packet + 7, 98);
    w_u16(packet + 12, 384);
    w_u16(packet + 14, 251);
    w_u8(packet + 4, 32);
    w_u8(packet + 5, 32);
    w_u8(packet + 6, 0);
    ordering = r_u32(0x8007184C);
    mode = r_u32(0x80071680);
    w_u16(packet + 10, 0);
    w_u16(packet + 8, 0);
    w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ordering + 4) & 0xFFFFFF));
    w_u32(ordering + 4, (r_u32(ordering + 4) & 0xFF000000) | (packet & 0xFFFFFF));
    w_u32(0x80071680, mode + 40);
    sub_8005EEB8(mode, 1, 1, r_u16(0x80071784), 0);
    ordering = r_u32(0x8007184C);
    w_u32(mode, (r_u32(mode) & 0xFF000000) | (r_u32(ordering + 4) & 0xFFFFFF));
    result = (r_u32(ordering + 4) & 0xFF000000) | (mode & 0xFFFFFF);
    w_u32(ordering + 4, result);
    return result;
}

void sub_80050A08(void)
{
    static const uint32 shown[3] = {0x8007173C, 0x80071708, 0x800716A8};
    static const uint32 targets[3] = {0x80071938, 0x800718E8, 0x800718A4};
    uint32 phase = r_u16(0x80071A0C), player, offset, actor, i, total, time, value, saved;
    uint32 complete = 0, changed = 0;
    if (phase == 0)
    {
        time = 25 * r_u16(0x80071940);
        for (player = 0; player < 2; ++player)
        {
            offset = 4 * player;
            actor = 0x800AFEC0 + 288 * player;
            for (i = 0; i < 3; ++i)
                w_u32(shown[i] + offset, 0);
            for (i = 0; i < 3; ++i)
                w_u32(targets[i] + offset, 0);
            if (!r_u8(actor + 240))
                continue;
            w_u32(targets[0] + offset, time);
            w_u32(targets[1] + offset, 10 * r_u16(actor + 210));
            w_u32(targets[2] + offset, player == r_u16(0x80071A34) ? 10000 : 0);
            total = 0x800719E8 + offset;
            w_u32(total, 0);
            for (i = 0; i < 6; ++i)
            {
                value = 10 * r_u32(total);
                w_u32(total, value);
                w_u32(total, value - 48 + r_u8(actor + 250 + i));
            }
            value = r_u32(0x800715F4 + offset);
            saved = r_u32(0x80071788 + offset);
            w_u32(0x80071908 + offset, value);
            w_u32(0x80071958 + offset, saved);
        }
        w_u16(0x80071894, 256);
        w_u16(0x80071A0C, r_u16(0x80071A0C) + 1);
        return;
    }
    if (phase == 1)
    {
        w_u16(0x80071894, r_u16(0x80071894) - 32);
        if (!r_u16(0x80071894))
            w_u16(0x80071A0C, r_u16(0x80071A0C) + 1);
        sub_80050664((uint32)(sint32)(sint16)r_u16(0x80071894));
        return;
    }
    if (phase == 2)
    {
        if (!(r_u16(0x800719D0) & 1))
        {
            complete = 1;
            for (player = 0; player < 2; ++player)
            {
                if (!r_u8(0x800AFFB0 + 288 * player))
                    continue;
                offset = 4 * player;
                for (i = 0; i < 3; ++i)
                {
                    if (r_u32(shown[i] + offset) == r_u32(targets[i] + offset))
                        continue;
                    changed = 1;
                    complete = 0;
                    sub_8005094C(shown[i] + offset, targets[i] + offset, 0x800719E8 + offset, player);
                }
            }
        }
        if (changed)
            sub_8004486C(1, 1, 53, 800, 24000, 512);
        if (complete)
        {
            w_u16(0x80071894, 0);
            w_u16(0x80071A0C, r_u16(0x80071A0C) + 1);
        }
        sub_80050664(0);
        return;
    }
    if (phase == 3)
    {
        w_u16(0x80071894, r_u16(0x80071894) + 1);
        if (r_u16(0x80071894) == 90)
            w_u16(0x80071A0C, 4);
        sub_80050664(0);
    }
}
