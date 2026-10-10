#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Native translations of FILE.DAT entry 7 and entry 11 */
extern uint32 _bu_init(void);
extern uint32 sub_80068468(uint32 channel);
extern uint32 sub_80068478(uint32 channel);
extern uint32 sub_800684A8(uint32 channel);
extern uint32 sub_8005C018(uint32 path, uint32 mode);
extern uint32 sub_8005C028(uint32 handle, uint32 destination, uint32 size);
extern uint32 sub_8005C048(uint32 handle);
extern uint32 sub_800CF6E0(void);
extern uint32 sub_800CF730(void);
extern uint32 sub_800CF784(void);
extern uint32 sub_800CD944(void);
extern uint32 sub_800CD1BC(void);
extern void sub_800CE39C(void);
extern uint32 sub_800CF860(uint32 mode);
extern uint32 sub_800CF440(void);
extern uint32 sub_8005EEB8(uint32 packet, uint32 draw, uint32 dither, uint32 page, uint32 window);
extern uint32 sub_8005E4D0(uint32 ordering, uint32 count);
extern uint32 sub_8005DFE4(uint32 mode);
extern uint32 sub_8005B278(uint32 mode);
extern uint32 sub_8005E648(uint32 environment);
extern uint32 sub_8005E814(uint32 environment);
extern uint32 sub_8005E5D8(uint32 ordering);

static const uint32 card_events[8] = {0x80071748u, 0x8007174Cu, 0x80071754u, 0x8007175Cu, 0x800717B0u, 0x800717B4u, 0x800717BCu, 0x800717C8u};

static void overlay7_card_path(uint32 channel)
{
    channel = (uint16)channel;
    w_u8(0x800D0B24u, 'b');
    w_u32(0x800D0B44u, channel);
    w_u8(0x800D0B25u, 'u');
    w_u8(0x800D0B26u, (channel >> 4) + '0');
    w_u8(0x800D0B27u, (channel & 15u) + '0');
    w_u8(0x800D0B28u, ':');
}

uint32 sub_800CA390(void)
{
    static const uint32 specifications[4] = {4u, 0x8000u, 256u, 0x2000u};
    uint32 i, result;
    overlay7_card_path(0);
    for (i = 0; i < 8u; ++i)
    {
        result = (uint32)OpenEventPSX(i < 4u ? 0xF4000001u : 0xF0000011u, specifications[i & 3u], 0x2000u, 0);
        w_u32(card_events[i], result);
        if (result == 0xFFFFFFFFu)
            return result;
    }
    xport_bios_init_card(1);
    xport_bios_start_card();
    return _bu_init();
}

uint32 sub_800CA4F8(void)
{
    uint32 i, result = 0;
    for (i = 0; i < 8u; ++i)
        result = (uint32)EnableEventPSX(r_u32(card_events[i]));
    return result;
}

void sub_800CA590(void)
{
    uint32 i;
    xport_bios_enter_critical();
    for (i = 0; i < 8u; ++i)
        CloseEventPSX(r_u32(card_events[i]));
    xport_bios_exit_critical();
}

static uint32 overlay7_poll_events(uint32 first)
{
    uint32 i;
    for (;;)
        for (i = 0; i < 4u; ++i)
            if (TestEvent(r_u32(card_events[first + i])) == 1)
                return i;
}

static void overlay7_clear_events(uint32 first)
{
    uint32 i;
    for (i = 0; i < 4u; ++i)
        TestEvent(r_u32(card_events[first + i]));
}

static sint32 overlay7_card_ready(void)
{
    sint32 status;
    for (;;)
    {
        overlay7_clear_events(0);
        sub_80068468(r_u32(0x800D0B44u));
        status = (sint32)overlay7_poll_events(0);
        if (status == 2)
            return -1;
        if (status == 0)
        {
            overlay7_clear_events(0);
            sub_80068478(r_u32(0x800D0B44u));
            status = (sint32)overlay7_poll_events(0);
            if (status == 0)
                return 1;
            if (status == 3)
                return -2;
        }
        else if (status != 3)
        {
            sub_8005B278(0);
            continue;
        }
        overlay7_clear_events(4);
        sub_800684A8(r_u32(0x800D0B44u));
        if (overlay7_poll_events(4) == 0)
        {
            overlay7_clear_events(0);
            sub_80068478(r_u32(0x800D0B44u));
            status = (sint32)overlay7_poll_events(0);
            if (status == 0)
                return 1;
            if (status == 3)
                return -2;
        }
        sub_8005B278(0);
    }
}

uint32 sub_800CA338(uint32 channel)
{
    overlay7_card_path(channel);
    return 58;
}

uint32 sub_800CA778(void)
{
    return overlay7_poll_events(0);
}

uint32 sub_800CA880(void)
{
    uint32 i, result = 0;
    for (i = 0; i < 4u; ++i)
        result = (uint32)TestEvent(r_u32(card_events[i]));
    return result;
}

uint32 sub_800CA930(void)
{
    return (uint32)overlay7_card_ready();
}

static void overlay7_load_bytes(uint32 source, uint32 destination, uint32 count)
{
    uint32 i;
    for (i = 0; i < count; ++i)
    {
        uint32 offset = r_u16(0x800D0B50u);
        w_u16(0x800D0B50u, offset + 1u);
        w_u8(destination + i, r_u8(source + offset));
    }
}

uint32 sub_800CB8F8(uint32 channel)
{
    uint32 buffer, source, i, attempt, handle, sum;
    static const uint32 destinations[8] = {0x800719C8u, 0x80071A30u, 0x800716E0u, 0x800719BCu, 0x800717ECu, 0x8007179Cu, 0x80071590u, 0x800AF6F0u};
    static const uint32 counts[8] = {2, 2, 2, 2, 4, 4, 4, 120};
    overlay7_card_path(channel);
    if (overlay7_card_ready() != 1)
        return 0;
    buffer = sub_80011A98(8192);
    overlay7_card_path(r_u16(0x800D0B44u));
    source = r_u32(0x800D06C0u);
    i = 0;
    while (r_u8(source + (uint16)i))
    {
        w_u8(0x800D0B29u + (uint16)i, r_u8(source + (uint16)i));
        ++i;
        source = r_u32(0x800D06C0u);
    }
    w_u8(0x800D0B29u + (uint16)i, 0);
    for (attempt = 0; attempt < 7u; ++attempt)
    {
        handle = sub_8005C018(0x800D0B24u, 1);
        if (handle == 0xFFFFFFFFu)
        {
            sub_8005C048(handle);
            continue;
        }
        if (sub_8005C028(handle, buffer, 8192) != 8192u)
        {
            sub_8005C048(handle);
            continue;
        }
        if (sub_8005C048(handle) == 0xFFFFFFFFu || r_u8(buffer) != 'S' || r_u8(buffer + 1) != 'C')
            continue;
        sum = 0;
        for (i = 0; i < 2048u; ++i)
            sum += r_u8(buffer + 516u + i);
        if (r_u32(buffer + 512u) != sum)
            continue;
        w_u16(0x800D0B50u, 516);
        for (i = 0; i < 8u; ++i)
            overlay7_load_bytes(buffer, destinations[i], counts[i]);
        sub_80011AF8(buffer);
        return 1;
    }
    sub_80011AF8(buffer);
    return 0;
}

uint32 sub_800D04E8(void)
{
    uint32 choice, next;
    sub_80014888(5);
    sub_800447B0(0, 80);
    sub_8004477C(2, 0);
    sub_80044528(8, 0, 13);
    sub_80014848();
    sub_80014F0C(9, 0, 1000);
    sub_80014F0C(10, 68, 1000);
    sub_800CF6E0();
    sub_800CF730();
    sub_800CF784();
    sub_800129E8();
    w_u16(0x800D08A4u, r_u16(0x800BF296u));
    w_u16(0x800BF2AAu, 240);
    w_u16(0x800BF296u, 240);
    w_u16(0x800D08B0u, 0);
    do
    {
        next = (uint16)(sub_800CD944() + 1u);
        if (next == 3u)
        {
            while ((uint16)sub_800CD1BC() == 7u)
                sub_800CE39C();
            next = 0;
        }
        choice = next;
        if ((uint16)(next - 1u) < 2u)
            choice = (uint16)sub_800CF860(next);
    } while (!choice);
    if (choice == 256u)
        sub_800CF440();
    w_u16(0x800BF2AAu, r_u16(0x800D08A4u));
    w_u16(0x800BF296u, r_u16(0x800D08A4u));
    sub_80018DAC();
    sub_800574D4();
    sub_800446EC();
    return choice == 256u ? 0 : choice;
}

static uint32 overlay11_packet(void)
{
    uint32 packet = r_u32(0x80071680u);
    w_u32(0x80071680u, packet + 40u);
    return packet;
}

static void overlay11_link(uint32 packet, uint32 depth)
{
    uint32 slot = r_u32(0x8007184Cu) + 4u * depth;
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(slot) & 0xFFFFFFu));
    w_u32(slot, (r_u32(slot) & 0xFF000000u) | (packet & 0xFFFFFFu));
}

static void overlay11_quad(sint32 x0, sint32 y0, sint32 x1, sint32 y1, uint32 colors)
{
    uint32 packet = overlay11_packet(), i;
    w_u8(packet + 3, 8);
    w_u8(packet + 7, 58);
    for (i = 0; i < 4u; ++i)
    {
        w_u8(packet + 4 + 8 * i, (colors & (1u << i)) ? 255u : 0);
        w_u8(packet + 5 + 8 * i, (colors & (1u << i)) ? 255u : 0);
        w_u8(packet + 6 + 8 * i, (colors & (1u << i)) ? 128u : 0);
        w_u16(packet + 8 + 8 * i, (i & 1u) ? x1 : x0);
        w_u16(packet + 10 + 8 * i, (i & 2u) ? y1 : y0);
    }
    overlay11_link(packet, 2498);
}

static void overlay11_tile(sint32 x, sint32 y, uint32 width, uint32 height, uint32 shade, uint32 command, uint32 depth)
{
    uint32 packet = overlay11_packet();
    w_u8(packet + 3, 3);
    w_u8(packet + 7, command);
    w_u8(packet + 4, shade);
    w_u8(packet + 5, shade);
    w_u8(packet + 6, shade);
    w_u16(packet + 8, x);
    w_u16(packet + 10, y);
    w_u16(packet + 12, width);
    w_u16(packet + 14, height);
    overlay11_link(packet, depth);
}

static void overlay11_draw_mode(uint32 depth)
{
    uint32 packet = overlay11_packet();
    sub_8005EEB8(packet, 1, 1, r_u16(0x80071784u), 0);
    overlay11_link(packet, depth);
}

static sint16 overlay11_approach(sint16 current, sint16 target)
{
    sint32 difference = (sint16)((uint32)target - (uint32)current), step = difference >> 5;
    if (!step && difference)
        step = difference < 0 ? -1 : 1;
    return (sint16)(current + step);
}

static void overlay11_marker(sint32 x, sint32 y)
{
    sub_80017FB0((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)y, 17, 132);
}

static void overlay11_character(sint32 x, sint32 y, uint32 pose)
{
    sint32 left = (sint16)(x - 55), top = (sint16)(y - 212);
    sub_80017FB0((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)y, 16, pose ? 131 : 130);
    sub_80017FB0(left, top, 16, 127);
    sub_80017FB0(left + 150, top + 83, 16, 128);
    sub_80017FB0(left + 1, top + 1, 16, 129);
}

void sub_800CA294(uint32 destination, uint32 bonus)
{
    sint32 bounce = 0, scroll_x = 0, scroll_y = -256, target_x, target_y, x, y;
    sint16 state = 0, hold = 0;
    uint16 fade = 0, offset = 288, velocity = 0;
    uint32 finished = 0, i, text, slot;
    destination = (uint16)destination;
    bonus = (uint16)bonus;
    w_u16(0x800719D0u, 0);
    sub_80014848();
    w_u16(0x800715E8u, 0);
    sub_800134E0(12, 0, 0);
    sub_800134E0(13, 1, 0);
    sub_800134E0(14, 2, 0);
    sub_80014F0C(15, 0, 1000);
    sub_800129E8();
    w_u16(0x8007194Cu, 254);
    w_u16(0x800717A4u, (uint16)-16);
    w_u16(0x800716FCu, 2);
    sub_80013B64(1, 140, 136, 129);
    w_u8(r_u32(0x800CB508u) + 7, bonus + 49);
    sub_800451B8(256, 0, 256, 0);
    sub_80044800();
    slot = 0x800CB4ECu + 4 * destination;
    do
    {
        sub_80011BB8();
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        if (velocity)
        {
            sint16 position = (sint16)(bounce + velocity);
            bounce += (sint16)velocity;
            if ((sint16)velocity > 0)
            {
                if (position >= (sint16)velocity)
                    velocity = (uint16)(1 - velocity);
            }
            else if ((sint16)velocity >= position)
                velocity = (uint16)~velocity;
            if (!velocity)
                bounce = 0;
        }
        if (fade)
        {
            uint32 depth = fade == 255 ? 0 : 2;
            sint32 center;
            text = r_u32(slot);
            center = (sint16)(192 - ((sint32)sub_8004ED48(text) >> 1));
            sub_8004EEFC(center, 68, text, fade >> 1, fade >> 1, fade >> 1, depth);
            sub_8004EEFC(center + 4, 64, text, 0, 0, fade >> 2, 2);
            text = r_u32(0x800CB508u);
            center = (sint16)(192 - ((sint32)sub_8004ED48(text) >> 1));
            sub_8004EEFC(center, 88, text, fade >> 1, 0, 0, depth);
            sub_8004EEFC(center + 4, 84, text, 0, 0, fade >> 2, 2);
            overlay11_tile(0, 0, 384, 256, fade, 98, 1);
            overlay11_draw_mode(1);
        }
        if (fade != 255)
        {
            if (destination < 5u)
            {
                sub_800184C0((sint16)scroll_x + 320, (sint16)(scroll_y + (sint16)bounce), 2499, 0);
                y = scroll_y + (sint16)bounce + 256;
                sub_800184C0((sint16)scroll_x, y, 2499, 1);
                sub_800184C0((sint16)scroll_x + 320, y, 2499, 2);
                overlay11_quad(0, 0, 384, 32, 3);
                overlay11_quad(0, 224, 384, 256, 12);
                overlay11_quad((sint16)scroll_x + 608, 0, (sint16)scroll_x + 640, 256, 10);
                overlay11_tile((sint16)scroll_x + 640, 0, 128, 256, 0, 96, 2498);
                overlay11_quad((sint16)scroll_x, 0, (sint16)scroll_x + 32, 256, 5);
                overlay11_tile((sint16)scroll_x - 128, 0, 128, 256, 0, 96, 2498);
                overlay11_draw_mode(2498);
                text = r_u32(0x800CB4E8u);
                x = (sint16)(192 - ((sint32)sub_8004ED48(text) >> 1));
                sub_8004EEFC(x, 12, text, 128, 128, 128, 0);
                for (i = 0; (sint16)i < (sint16)(destination + (bonus ? 1 : 0)); ++i)
                    overlay11_marker((sint16)r_u16(0x800CB4D0u + 4 * i) + (sint16)scroll_x, (sint16)r_u16(0x800CB4D2u + 4 * i) + scroll_y + (sint16)bounce);
            }
            for (i = 0; i < 2u; ++i)
            {
                uint32 actor = 0x800AFEC0u + 288 * i;
                if (r_u8(actor + 240))
                {
                    uint32 texture = 4 * r_u8(actor + 212) + 118;
                    x = (sint16)(224 * i + 72);
                    sub_80017FB0(x, 248, 0, texture);
                    sub_80018214(x | 4, 244, 0, texture, 32, 32, 32, 1);
                }
            }
        }
        target_x = (sint16)(192 - r_u16(0x800CB4D0u + 4 * destination));
        target_y = (sint16)(200 - r_u16(0x800CB4D2u + 4 * destination));
        scroll_x = overlay11_approach((sint16)scroll_x, (sint16)target_x);
        scroll_y = overlay11_approach((sint16)scroll_y, (sint16)target_y);
        x = offset + r_u16(0x800CB4D0u + 4 * destination) + scroll_x;
        y = r_u16(0x800CB4D2u + 4 * destination) + (uint16)scroll_y - offset;
        switch (state)
        {
            case 0:
                if ((sint16)scroll_x == target_x && (sint16)scroll_y == target_y)
                {
                    state = 1;
                    sub_8004486C(1, (uint16)sub_800448F4(), 21, 800, 32000, 512);
                }
                break;
            case 1:
                overlay11_character(x, y, 0);
                offset = (uint16)(offset - 32);
                if (!offset)
                {
                    state = 2;
                    velocity = 8;
                    hold = 0;
                    sub_8004486C(1, (uint16)sub_800448F4(), 1, 1000, 32000, 512);
                }
                break;
            case 2:
                overlay11_character(x, y + bounce, 1);
                overlay11_marker(r_u16(0x800CB4D0u + 4 * destination) + scroll_x, r_u16(0x800CB4D2u + 4 * destination) + scroll_y + bounce);
                if (!velocity && !(sint16)bounce && ++hold >= 50)
                    state = 3;
                break;
            case 3:
                overlay11_character(x, y + bounce, 1);
                fade = (uint16)(fade + 4);
                overlay11_marker(r_u16(0x800CB4D0u + 4 * destination) + scroll_x, r_u16(0x800CB4D2u + 4 * destination) + scroll_y + bounce);
                if (fade >= 255)
                {
                    fade = 255;
                    state = 4;
                }
                break;
            case 4:
                finished = 1;
                break;
        }
        sub_80045048(0);
        sub_80044A5C(1);
        sub_8002F36C();
        sub_8005DFE4(0);
        sub_8005B278(0);
        sub_8005E648(r_u32(0x800719CCu));
        sub_8005E814(r_u32(0x800719D4u));
        sub_8005E5D8(r_u32(0x8007184Cu) + 9996);
        w_u16(0x800719D0u, r_u16(0x800719D0u) + 1);
        w_u16(0x800715E8u, r_u16(0x800715E8u) ^ 1u);
    } while (!finished);
    sub_8005B278(0);
    sub_80013B64(1, 0, 0, 0);
}
