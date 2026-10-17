#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdio.h>
#include <stdlib.h>
extern uint32 sub_80045208(void), sub_800452F4(void), sub_8004BFE4(void), sub_80014294(void);
extern uint32 sub_800CB02C(void);
extern uint32 legend_stage0_begin(void);
extern void sub_8005E4D0(uint32, uint32), sub_8005DFE4(uint32), sub_8005B278(uint32), sub_8005E814(uint32), sub_8005E648(uint32), sub_8005E5D8(uint32);

void nullsub_2(void)
{
    sub_8004E20C();
}

extern uint32 sub_800630B8(uint32), sub_800628B8(uint32), sub_80063C94(uint32, uint32, uint32);

uint32 sub_80045208(void)
{
    uint32 i;
    volatile uint32 delay;
    for (i = 0; i < 24u; ++i)
    {
        w_u32(0x800C9E04u, 3);
        w_u32(0x800C9E00u, 1u << i);
        sub_800630B8(0x800C9E00u);
        for (delay = 1; delay <= 500u; ++delay)
        {
        }
        w_u16(0x800BECD0u + 4u * i, r_u16(0x800C9E08u));
        w_u16(0x800BECD2u + 4u * i, r_u16(0x800C9E0Au));
        w_u32(0x800C9E04u, 3);
        w_u32(0x800C9E00u, 1u << i);
        w_u16(0x800C9E08u, 0);
        w_u16(0x800C9E0Au, 0);
        sub_800628B8(0x800C9E00u);
        for (delay = 1; delay <= 500u; ++delay)
        {
        }
    }
    return i < 24u;
}

uint32 sub_800452F4(void)
{
    uint32 i;
    volatile uint32 delay;
    for (i = 0; i < 24u; ++i)
    {
        w_u32(0x800C9E04u, 3);
        w_u32(0x800C9E00u, 1u << i);
        w_u16(0x800C9E08u, r_u16(0x800BECD0u + 4u * i));
        w_u16(0x800C9E0Au, r_u16(0x800BECD2u + 4u * i));
        sub_800628B8(0x800C9E00u);
        for (delay = 1; delay <= 500u; ++delay)
        {
        }
    }
    return i < 24u;
}

uint32 sub_8004BFE4(void)
{
    return sub_8004486C(1, 1, 55, 1700, 20000, 512);
}

uint32 sub_80014294(void)
{
    while (!sub_80063C94(3, 0, 0))
    {
    }
    w_u8(0x80071540u, 1);
    return 1;
}

void sub_8004C7C4(uint32 player)
{
    uint32 held = 0x800u, pad = 0x80071790u + 2u * (uint16)player;
    uint32 keys, first, second, width, half_width, brightness;
    uint16 state = 0, choice = 0, done = 0;
    sub_80013B64(1, 0, 0, 32);
    sub_80045208();
    sub_80013F80();
    sub_8004BFE4();
    do
    {
        sub_80011BB8();
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        keys = r_u16(pad);
        w_u16(pad, keys & ~held);
        held &= keys;
        if (state == 0u)
        {
            first = r_u32(0x800689D0u);
            width = sub_8004ED48(first);
            sub_8004EEFC(192u - (uint32)((sint32)width >> 1), 100, first, 128, 128, 128, 0);
            if (r_u16(pad) & 0x800u)
            {
                done = 1;
                held = 0x800u;
                sub_8004BFE4();
            }
            else if (r_u16(pad) & 0x100u)
            {
                state = 1;
                held = 0x100u;
                choice = 0;
                sub_8004BFE4();
            }
        }
        else if (state == 1u)
        {
            brightness = choice == 0u ? 128u : 48u;
            first = r_u32(0x800689D4u);
            width = sub_8004ED48(first);
            second = r_u32(0x800689D8u);
            width += sub_8004ED48(second) + 32u;
            half_width = (uint32)((sint32)(width << 16) >> 17);
            sub_8004EEFC(192u - half_width, 100, first, brightness, 0, 0, 0);
            brightness = choice == 1u ? 128u : 48u;
            width = sub_8004ED48(r_u32(0x800689D4u));
            sub_8004EEFC(width - half_width + 224u, 100, r_u32(0x800689D8u), brightness, 0, 0, 0);
            if (r_u16(pad) & 0x8000u)
            {
                choice = 0;
                held = 0xFFFFu;
                sub_8004BFE4();
            }
            if (r_u16(pad) & 0x2000u)
            {
                choice = 1;
                held = 0xFFFFu;
                sub_8004BFE4();
            }
            if (r_u16(pad) & 0x40u)
            {
                if (choice)
                {
                    state = 2;
                    held = 0xFFFFu;
                    choice = 1;
                }
                else
                {
                    done = 1;
                    held = 0x840u;
                }
                sub_8004BFE4();
            }
        }
        else if (state == 2u)
        {
            first = r_u32(0x800689DCu);
            width = sub_8004ED48(first);
            sub_8004EEFC(192u - (uint32)((sint32)width >> 1), 100, first, 128, 128, 128, 0);
            first = r_u32(0x800689E0u);
            width = sub_8004ED48(first);
            second = r_u32(0x800689E4u);
            width += sub_8004ED48(second) + 32u;
            half_width = (uint32)((sint32)(width << 16) >> 17);
            brightness = choice == 0u ? 128u : 48u;
            sub_8004EEFC(192u - half_width, 128, first, brightness, 0, 0, 0);
            brightness = choice == 1u ? 128u : 48u;
            width = sub_8004ED48(r_u32(0x800689E0u));
            sub_8004EEFC(width - half_width + 224u, 128, r_u32(0x800689E4u), brightness, 0, 0, 0);
            if (r_u16(pad) & 0x8000u)
            {
                choice = 0;
                held = 0xFFFFu;
                sub_8004BFE4();
            }
            if (r_u16(pad) & 0x2000u)
            {
                choice = 1;
                held = 0xFFFFu;
                sub_8004BFE4();
            }
            if (r_u16(pad) & 0x40u)
            {
                done = 1;
                held = 0xFFFFu;
                sub_8004BFE4();
                if (!choice)
                    w_u16(0x80071888u, 1);
            }
        }
        sub_80044A5C(5);
        sub_8005DFE4(0);
        sub_8005B278(2);
        sub_80048180();
        sub_8005E814(r_u32(0x800719D4u));
        sub_8005E648(r_u32(0x800719CCu));
        sub_8005E5D8(r_u32(0x8007184Cu) + 9996u);
        w_u16(0x800719D0u, r_u16(0x800719D0u) + 1u);
        w_u16(0x800715E8u, r_u16(0x800715E8u) ^ 1u);
    } while (!done || held);
    sub_80014294();
    sub_800452F4();
    sub_80013B64(1, 0, 0, 0);
}

uint32 sub_8004C020(uint32 slot, uint32 output)
{
    uint32 score = 0, i, rank = 0;
    for (i = 0; i < 6u; ++i)
        score = 10u * score - 48u + r_u8(0x800AFFBAu + 288u * (slot & 65535u) + i);
    w_u32(output, score);
    for (i = 0; i < 10u; ++i)
        if ((sint32)r_u32(0x800AF6F8u + 12u * (9u - i)) < (sint32)score)
            rank = 10u - i;
    return rank & 255u;
}

void sub_8004C0DC(uint32 slot, uint32 state, uint32 score)
{
    uint32 rank = (state - 1u) & 255u, held = 0, cursor = 0, done = 0, i, entry = 0x800AF6F0u + 12u * rank;
    uint32 player = 288u * (slot & 65535u), pad = 0x80071790u + 2u * (slot & 65535u);
    if (rank < 9u)
        for (i = 9u; i > rank; --i)
        {
            uint32 source = 0x800AF6E4u + 12u * i, destination = source + 12u;
            uint32 a = r_u32(source), b = r_u32(source + 4u), c = r_u32(source + 8u);
            w_u32(destination, a);
            w_u32(destination + 4u, b);
            w_u32(destination + 8u, c);
        }
    w_u8(entry, r_u8(0x800AFF94u + player));
    w_u32(entry + 8u, score);
    w_u8(entry + 1u, r_u8(0x80071594u));
    sub_80013B64(1, 0, 0, 32);
    sub_80045208();
    sub_80013F80();
    for (i = 0; i < 5u; ++i)
        w_u8(entry + 2u + i, 46);
    do
    {
        uint32 keys, text, width, packet, phase, x, character, ordering;
        sub_80011BB8();
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        keys = r_u16(pad);
        w_u16(pad, keys & ~held);
        held &= keys;
        text = r_u32(0x800689C0u);
        width = sub_8004ED48(text);
        sub_8004EEFC(192u - (uint32)((sint32)width >> 1), 16, text, 128, 128, 128, 0);
        text = r_u32(0x800689C4u + 4u * (slot & 65535u));
        width = sub_8004ED48(text);
        sub_8004EEFC(192u - (uint32)((sint32)width >> 1), 32, text, 128, 128, 128, 0);
        text = r_u32(0x800689CCu);
        width = sub_8004ED48(text);
        sub_8004EEFC(192u - (uint32)((sint32)width >> 1), 64, text, 128, 128, 128, 0);
        sub_8004EEFC(176, 104, 0x800AFFBAu + player, 128, 128, 128, 0);
        sub_80017FB0(128, 180, 1, 4u * r_u8(0x800AFF94u + player) + 118u);
        sub_8004EEFC(176, 160, entry + 2u, 128, 128, 128, 0);
        packet = r_u32(0x80071680u);
        w_u32(0x80071680u, packet + 40u);
        w_u8(packet + 3u, 5);
        w_u8(packet + 7u, 40);
        phase = r_u16(0x800719D0u) & 63u;
        if (phase >= 32u)
            phase = 64u - phase;
        w_u8(packet + 5u, 2u * phase + 128u);
        w_u8(packet + 4u, 0);
        w_u8(packet + 6u, 0);
        x = 16u * cursor + 176u;
        w_u16(packet + 8u, x);
        w_u16(packet + 16u, x);
        w_u16(packet + 10u, 160);
        w_u16(packet + 12u, x + 16u);
        w_u16(packet + 14u, 160);
        w_u16(packet + 18u, 176);
        w_u16(packet + 20u, x + 16u);
        w_u16(packet + 22u, 176);
        ordering = r_u32(0x8007184Cu) + 32u;
        w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(ordering) & 0xFFFFFFu));
        w_u32(ordering, (r_u32(ordering) & 0xFF000000u) | (packet & 0xFFFFFFu));
        if ((r_u16(pad) & 0x8000u) && cursor)
        {
            --cursor;
            sub_8004BFE4();
            held = 0x8000;
        }
        if ((r_u16(pad) & 0x2000u) && cursor < 4u)
        {
            ++cursor;
            sub_8004BFE4();
            held = 0x2000;
        }
        character = r_u8(entry + 2u + cursor);
        if (r_u16(pad) & 0x1000u)
        {
            held = 0x1000;
            sub_8004BFE4();
            character = character == 46u ? 65u : character == 90u ? 46u : (character + 1u) & 255u;
        }
        if (r_u16(pad) & 0x4000u)
        {
            held = 0x4000;
            sub_8004BFE4();
            character = character == 46u ? 90u : character == 65u ? 46u : (character - 1u) & 255u;
        }
        if (r_u16(pad) & 0x800u)
        {
            held = 0x800;
            sub_8004BFE4();
            done = 1;
        }
        w_u8(entry + 2u + cursor, character);
        sub_80044A5C(5);
        sub_8005DFE4(0);
        sub_8005B278(2);
        sub_80048180();
        sub_8005E814(r_u32(0x800719D4u));
        sub_8005E648(r_u32(0x800719CCu));
        sub_8005E5D8(r_u32(0x8007184Cu) + 9996u);
        w_u16(0x800719D0u, r_u16(0x800719D0u) + 1u);
        w_u16(0x800715E8u, r_u16(0x800715E8u) ^ 1u);
    } while (!done || held);
    sub_80014294();
    sub_800452F4();
    sub_80013B64(1, 0, 0, 0);
}

uint32 draft_guest_call0(uint32 target)
{
    if (target == 0x800CB02Cu && r_u32(0x80071588u) == 11u)
        return sub_800CB02C();
    if (target == 0x800C9EFCu && r_u32(0x80071588u) == 154u)
        return legend_stage0_begin();
    switch (target)
    {
        case 0x8004DCDCu:
            return sub_8004DCDC();
        case 0x8004DCACu:
            return sub_8004DCAC();
        case 0x80013BACu:
            return sub_80013BAC();
        case 0x8004E308u:
            return sub_8004E308();
        case 0x8004E2C0u:
            return sub_8004E2C0();
        case 0x80014848u:
            return sub_80014848();
        case 0x800139C0u:
            return sub_800139C0();
        case 0x8002F36Cu:
            return sub_8002F36C();
        case 0x80014E3Cu:
            sub_80014E3C();
            return draft_unknown_return("sub_80014E3C callback");
        case 0x8005BFF8u:
            return sub_8005BFF8();
        case 0x8001199Cu:
            return sub_8001199C();
        case 0x80011B38u:
            return sub_80011B38();
        case 0x80013CE8u:
            return sub_80013CE8();
        case 0x8005BFE8u:
            return sub_8005BFE8();
        case 0x8005C7E8u:
            return sub_8005C7E8();
        case 0x8005BF1Cu:
            return sub_8005BF1C();
        case 0x80013894u:
            return sub_80013894();
        case 0x80045450u:
            return sub_80045450();
        case 0x80060DF8u:
            return sub_80060DF8();
        case 0x80014644u:
            return sub_80014644();
        case 0x80013FB4u:
            return sub_80013FB4();
        case 0x80044FB0u:
            return sub_80044FB0();
        case 0x800CA390u:
            return sub_800CA390();
        case 0x800CA4F8u:
            return sub_800CA4F8();
        case 0x800CA590u:
            sub_800CA590();
            return draft_unknown_return("sub_800CA590");
        case 0x80059B88u:
            return sub_80059B88();
        case 0x80059BD8u:
            return sub_80059BD8();
        case 0x80014B18u:
            return sub_80014B18();
        case 0x80014BA0u:
            return sub_80014BA0();
        case 0x80064008u:
            return sub_80064008();
        case 0x80013ECCu:
            return sub_80013ECC();
        case 0x80018C78u:
            return sub_80018C78();
        case 0x800573B0u:
            return sub_800573B0();
        case 0x8001455Cu:
            return sub_8001455C();
        case 0x8004DBE4u:
            return sub_8004DBE4();
        case 0x800142CCu:
            return sub_800142CC();
        case 0x80014328u:
            return sub_80014328();
        case 0x80014378u:
            return sub_80014378();
        case 0x8004E20Cu:
            sub_8004E20C();
            return draft_unknown_return("sub_8004E20C callback");
        case 0x8005A530u:
            return sub_8005A530();
        case 0x8005A7D8u:
            return sub_8005A7D8();
        case 0x8005A730u:
            return sub_8005A730();
        case 0x80059EE4u:
            return sub_80059EE4();
        case 0x80011BB8u:
            return sub_80011BB8();
        case 0x8005A67Cu:
            return sub_8005A67C();
        case 0x8005A3C8u:
            return sub_8005A3C8();
        case 0x80066998u:
            sub_80066998();
            return draft_unknown_return("sub_80066998 callback");
        case 0x8001EE9Cu:
            return sub_8001EE9C();
        case 0x800129E8u:
            return sub_800129E8();
        case 0x80044800u:
            return sub_80044800();
        case 0x80011B8Cu:
            return sub_80011B8C();
        case 0x8002F0F8u:
            return sub_8002F0F8();
        case 0x80044A40u:
            return sub_80044A40();
        case 0x800140DCu:
            sub_800140DC();
            return draft_unknown_return("sub_800140DC callback");
        case 0x80013974u:
            return sub_80013974();
        case 0x800455DCu:
            return sub_800455DC();
        case 0x80013F80u:
            return sub_80013F80();
        case 0x80020124u:
            return sub_80020124();
        case 0x8004B87Cu:
            return sub_8004B87C();
        case 0x80048EB8u:
            return sub_80048EB8();
        case 0x8001F338u:
            return sub_8001F338();
        case 0x800206D8u:
            return sub_800206D8();
        case 0x8001B570u:
            return sub_8001B570();
        case 0x80018DACu:
            return sub_80018DAC();
        case 0x800574D4u:
            return sub_800574D4();
        case 0x800446ECu:
            return sub_800446EC();
        case 0x800529F4u:
            return sub_800529F4();
        case 0x80045604u:
            return sub_80045604();
        case 0x8004B554u:
            return sub_8004B554();
        case 0x8004B4F0u:
            return sub_8004B4F0();
        case 0x8004AD78u:
            return sub_8004AD78();
        case 0x80014860u:
            return sub_80014860();
        case 0x800149DCu:
            return sub_800149DC();
        case 0x80012DD4u:
            return sub_80012DD4();
        case 0x80018B38u:
            return sub_80018B38();
        case 0x800448F4u:
            return sub_800448F4();
        case 0x80012FBCu:
            return sub_80012FBC();
        case 0x80018BD8u:
            return sub_80018BD8();
        case 0x80014A6Cu:
            return sub_80014A6C();
        case 0x8004CCA8u:
            return sub_8004CCA8();
        case 0x80044734u:
            return sub_80044734();
        case 0x8004944Cu:
            return sub_8004944C();
        case 0x80049504u:
            return sub_80049504();
        case 0x80031154u:
            return sub_80031154();
        case 0x80032DFCu:
            return sub_80032DFC();
        case 0x800471B4u:
            return sub_800471B4();
        case 0x800474F4u:
            return sub_800474F4();
        case 0x80032EF0u:
            return sub_80032EF0();
        case 0x80030678u:
            return sub_80030678();
        case 0x80048154u:
            return sub_80048154();
        case 0x80048180u:
            return sub_80048180();
        case 0x80058678u:
            sub_80058678();
            return draft_unknown_return("sub_80058678 callback");
        case 0x800471D8u:
            sub_800471D8();
            return draft_unknown_return("sub_800471D8 callback");
        case 0x80047590u:
            sub_80047590();
            return draft_unknown_return("sub_80047590 callback");
        case 0x8002B134u:
            return sub_8002B134();
        case 0x80056C28u:
            return sub_80056C28();
        case 0x80026A88u:
            return sub_80026A88();
        case 0x80030D84u:
            return sub_80030D84();
        case 0x800470FCu:
            sub_800470FC();
            return draft_unknown_return("sub_800470FC callback");
        case 0x80047B68u:
            return sub_80047B68();
        case 0x8003220Cu:
            return sub_8003220C();
        case 0x8004EC74u:
            sub_8004EC74();
            return draft_unknown_return("sub_8004EC74 callback");
        case 0x8002B9B4u:
            return sub_8002B9B4();
        case 0x800225C8u:
            return sub_800225C8();
        case 0x80020DD8u:
            sub_80020DD8();
            return draft_unknown_return("sub_80020DD8 callback");
        case 0x800215ECu:
            return sub_800215EC();
        case 0x80020B54u:
            return sub_80020B54();
        case 0x800210E8u:
            return sub_800210E8();
        case 0x80020CFCu:
            return sub_80020CFC();
        case 0x80050E48u:
            sub_80050E48();
            return draft_unknown_return("sub_80050E48 callback");
        case 0x80050414u:
            return sub_80050414();
        case 0x8004E73Cu:
            return sub_8004E73C();
        case 0x8004F8BCu:
            return sub_8004F8BC();
        case 0x8002FC3Cu:
            return sub_8002FC3C();
        case 0x80030188u:
            return sub_80030188();
        case 0x8002F98Cu:
            return sub_8002F98C();
        case 0x8004BD40u:
            return sub_8004BD40();
        case 0x8004C720u:
            return sub_8004C720();
        case 0x8004496Cu:
            return sub_8004496C();
        default:
            fprintf(stderr, "Legend unknown callback target 0x%08X\n", target);
            fflush(stderr);
            abort();
    }
}

void draft_guest_call_void(uint32 target)
{
    if (r_u32(0x80071588) == 182)
    {
        switch (target)
        {
            case 0x800C9F14:
                legend_stage16_begin();
                return;
            case 0x800CA050:
                legend_stage17_begin();
                return;
            case 0x800CA2B8:
                legend_stage18_begin();
                return;
            case 0x800CA614:
                legend_stage19_begin();
                return;
            case 0x800CA968:
                legend_stage20_begin();
                return;
            case 0x800CAAF0:
                legend_stage21_begin();
                return;
        }
    }
    if (r_u32(0x80071588) == 174)
    {
        switch (target)
        {
            case 0x800C9EDC:
                legend_stage12_begin();
                return;
            case 0x800CA010:
                legend_stage13_begin();
                return;
            case 0x800CA2B8:
                legend_stage14_begin();
                return;
            case 0x800CA5F8:
                legend_stage15_begin();
                return;
        }
    }
    if (r_u32(0x80071588) == 168)
    {
        switch (target)
        {
            case 0x800C9F90:
                legend_stage8_begin();
                return;
            case 0x800CA220:
                legend_stage9_begin();
                return;
            case 0x800CA3AC:
                legend_stage10_begin();
                return;
            case 0x800CA750:
                legend_stage11_begin();
                return;
        }
    }
    if (r_u32(0x80071588) == 162 && target == 0x800CB038)
    {
        legend_gallery_run();
        return;
    }
    if (r_u32(0x80071588) == 160 && target == 0x800CA35C)
    {
        legend_stage5_begin();
        return;
    }
    if (r_u32(0x80071588) == 160 && target == 0x800CA5B8)
    {
        legend_stage6_begin();
        return;
    }
    if (r_u32(0x80071588) == 160 && target == 0x800CA180)
    {
        legend_stage4_begin();
        return;
    }
    if (r_u32(0x80071588) == 160 && target == 0x800CA0B4)
    {
        legend_stage4_tick();
        return;
    }
    if (r_u32(0x80071588) == 160 && target == 0x800C9EC0)
    {
        legend_stage3_begin();
        return;
    }
    if (r_u32(0x80071588u) == 154u && target == 0x800CA078u)
    {
        legend_stage1_begin();
        return;
    }
    if (r_u32(0x80071588u) == 154u && target == 0x800CA254u)
    {
        legend_stage2_begin();
        return;
    }
    if (target == 0x800CB02Cu && r_u32(0x80071588u) == 11u)
    {
        sub_800CB02C();
        return;
    }
    if (target == 0x800C9EFCu && r_u32(0x80071588u) == 154u)
    {
        legend_stage0_begin();
        return;
    }
    switch (target)
    {
        case 0x8004DCDCu:
            sub_8004DCDC();
            return;
        case 0x8004DCACu:
            sub_8004DCAC();
            return;
        case 0x80013BACu:
            sub_80013BAC();
            return;
        case 0x8004E308u:
            sub_8004E308();
            return;
        case 0x8004E2C0u:
            sub_8004E2C0();
            return;
        case 0x80014848u:
            sub_80014848();
            return;
        case 0x800139C0u:
            sub_800139C0();
            return;
        case 0x8002F36Cu:
            sub_8002F36C();
            return;
        case 0x80014E3Cu:
            sub_80014E3C();
            return;
        case 0x8005BFF8u:
            sub_8005BFF8();
            return;
        case 0x8001199Cu:
            sub_8001199C();
            return;
        case 0x80011B38u:
            sub_80011B38();
            return;
        case 0x80013CE8u:
            sub_80013CE8();
            return;
        case 0x8005BFE8u:
            sub_8005BFE8();
            return;
        case 0x8005C7E8u:
            sub_8005C7E8();
            return;
        case 0x8005BF1Cu:
            sub_8005BF1C();
            return;
        case 0x80013894u:
            sub_80013894();
            return;
        case 0x80045450u:
            sub_80045450();
            return;
        case 0x80060DF8u:
            sub_80060DF8();
            return;
        case 0x80014644u:
            sub_80014644();
            return;
        case 0x80013FB4u:
            sub_80013FB4();
            return;
        case 0x80044FB0u:
            sub_80044FB0();
            return;
        case 0x800CA390u:
            sub_800CA390();
            return;
        case 0x800CA4F8u:
            sub_800CA4F8();
            return;
        case 0x800CA590u:
            sub_800CA590();
            return;
        case 0x80059B88u:
            sub_80059B88();
            return;
        case 0x80059BD8u:
            sub_80059BD8();
            return;
        case 0x80014B18u:
            sub_80014B18();
            return;
        case 0x80014BA0u:
            sub_80014BA0();
            return;
        case 0x80064008u:
            sub_80064008();
            return;
        case 0x80013ECCu:
            sub_80013ECC();
            return;
        case 0x80018C78u:
            sub_80018C78();
            return;
        case 0x800573B0u:
            sub_800573B0();
            return;
        case 0x8001455Cu:
            sub_8001455C();
            return;
        case 0x8004DBE4u:
            sub_8004DBE4();
            return;
        case 0x800142CCu:
            sub_800142CC();
            return;
        case 0x80014328u:
            sub_80014328();
            return;
        case 0x80014378u:
            sub_80014378();
            return;
        case 0x8004E20Cu:
            sub_8004E20C();
            return;
        case 0x8005A530u:
            sub_8005A530();
            return;
        case 0x8005A7D8u:
            sub_8005A7D8();
            return;
        case 0x8005A730u:
            sub_8005A730();
            return;
        case 0x80059EE4u:
            sub_80059EE4();
            return;
        case 0x80011BB8u:
            sub_80011BB8();
            return;
        case 0x8005A67Cu:
            sub_8005A67C();
            return;
        case 0x8005A3C8u:
            sub_8005A3C8();
            return;
        case 0x80066998u:
            sub_80066998();
            return;
        case 0x8001EE9Cu:
            sub_8001EE9C();
            return;
        case 0x800129E8u:
            sub_800129E8();
            return;
        case 0x80044800u:
            sub_80044800();
            return;
        case 0x80011B8Cu:
            sub_80011B8C();
            return;
        case 0x8002F0F8u:
            sub_8002F0F8();
            return;
        case 0x80044A40u:
            sub_80044A40();
            return;
        case 0x800140DCu:
            sub_800140DC();
            return;
        case 0x80013974u:
            sub_80013974();
            return;
        case 0x800455DCu:
            sub_800455DC();
            return;
        case 0x80013F80u:
            sub_80013F80();
            return;
        case 0x80020124u:
            sub_80020124();
            return;
        case 0x8004B87Cu:
            sub_8004B87C();
            return;
        case 0x80048EB8u:
            sub_80048EB8();
            return;
        case 0x8001F338u:
            sub_8001F338();
            return;
        case 0x80049180u:
            sub_80049180();
            return;
        case 0x800206D8u:
            sub_800206D8();
            return;
        case 0x8001B570u:
            sub_8001B570();
            return;
        case 0x80018DACu:
            sub_80018DAC();
            return;
        case 0x800574D4u:
            sub_800574D4();
            return;
        case 0x800446ECu:
            sub_800446EC();
            return;
        case 0x800529F4u:
            sub_800529F4();
            return;
        case 0x80045604u:
            sub_80045604();
            return;
        case 0x8004B554u:
            sub_8004B554();
            return;
        case 0x8004B4F0u:
            sub_8004B4F0();
            return;
        case 0x8004AD78u:
            sub_8004AD78();
            return;
        case 0x80014860u:
            sub_80014860();
            return;
        case 0x800149DCu:
            sub_800149DC();
            return;
        case 0x80012DD4u:
            sub_80012DD4();
            return;
        case 0x80018B38u:
            sub_80018B38();
            return;
        case 0x800448F4u:
            sub_800448F4();
            return;
        case 0x80012FBCu:
            sub_80012FBC();
            return;
        case 0x80018BD8u:
            sub_80018BD8();
            return;
        case 0x80014A6Cu:
            sub_80014A6C();
            return;
        case 0x8004CCA8u:
            sub_8004CCA8();
            return;
        case 0x80044734u:
            sub_80044734();
            return;
        case 0x8004944Cu:
            sub_8004944C();
            return;
        case 0x80049504u:
            sub_80049504();
            return;
        case 0x80031154u:
            sub_80031154();
            return;
        case 0x80032DFCu:
            sub_80032DFC();
            return;
        case 0x800471B4u:
            sub_800471B4();
            return;
        case 0x800474F4u:
            sub_800474F4();
            return;
        case 0x80032EF0u:
            sub_80032EF0();
            return;
        case 0x80030678u:
            sub_80030678();
            return;
        case 0x80048154u:
            sub_80048154();
            return;
        case 0x80048180u:
            sub_80048180();
            return;
        case 0x80058678u:
            sub_80058678();
            return;
        case 0x800471D8u:
            sub_800471D8();
            return;
        case 0x80047590u:
            sub_80047590();
            return;
        case 0x8002B134u:
            sub_8002B134();
            return;
        case 0x80056C28u:
            sub_80056C28();
            return;
        case 0x80026A88u:
            sub_80026A88();
            return;
        case 0x80030D84u:
            sub_80030D84();
            return;
        case 0x800470FCu:
            sub_800470FC();
            return;
        case 0x80047B68u:
            sub_80047B68();
            return;
        case 0x8003220Cu:
            sub_8003220C();
            return;
        case 0x8004EC74u:
            sub_8004EC74();
            return;
        case 0x8002B9B4u:
            sub_8002B9B4();
            return;
        case 0x800225C8u:
            sub_800225C8();
            return;
        case 0x80020DD8u:
            sub_80020DD8();
            return;
        case 0x800215ECu:
            sub_800215EC();
            return;
        case 0x80020574u:
            sub_80020574();
            return;
        case 0x80020B54u:
            sub_80020B54();
            return;
        case 0x800204C0u:
            sub_800204C0();
            return;
        case 0x800210E8u:
            sub_800210E8();
            return;
        case 0x80020CFCu:
            sub_80020CFC();
            return;
        case 0x80050E48u:
            sub_80050E48();
            return;
        case 0x80050414u:
            sub_80050414();
            return;
        case 0x8004E73Cu:
            sub_8004E73C();
            return;
        case 0x8004F8BCu:
            sub_8004F8BC();
            return;
        case 0x8003076Cu:
            sub_8003076C();
            return;
        case 0x8002FC3Cu:
            sub_8002FC3C();
            return;
        case 0x80030188u:
            sub_80030188();
            return;
        case 0x8002F98Cu:
            sub_8002F98C();
            return;
        case 0x8004BD40u:
            sub_8004BD40();
            return;
        case 0x8004C720u:
            sub_8004C720();
            return;
        case 0x8004496Cu:
            sub_8004496C();
            return;
        default:
            fprintf(stderr, "Legend unknown void callback target 0x%08X\n", target);
            fflush(stderr);
            abort();
    }
}
