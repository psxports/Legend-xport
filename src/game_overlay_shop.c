#include "psx.h"
#include "game_draft_signatures.h"

extern uint32 sub_8005B278(uint32 mode);
extern uint32 sub_8005E4D0(uint32 table, uint32 count);
extern uint32 sub_8005DFE4(uint32 mode);
extern uint32 sub_8005C154(uint32 counter);
extern uint32 sub_8005E814(uint32 environment);
extern uint32 sub_8005E648(uint32 environment);
extern void sub_8005E5D8(uint32 table);

static void shop_select_sound(void)
{
    sub_8004486C(1, 0, 66, 1024, 16000, 512);
}

static void shop_confirm_sound(void)
{
    sub_8004486C(1, 1, 67, 1024, 16000, 512);
}

static void shop_purchase_sound(void)
{
    sub_8004486C(1, 2, 72, 2048, 20000, 512);
}

static void shop_voice(uint32 sound)
{
    sub_8004486C(1, 3, (uint16)sound, 1024, 30000, 512);
}

static void shop_price(uint32 x, uint32 y, uint32 amount)
{
    uint32 divisor = 100000, i, count = 0, started = 0, digit;
    char text[8];
    sint32 left;
    for (i = 0; i < 6; ++i)
    {
        digit = amount / divisor;
        if (digit)
            started = 1;
        if (started || i == 5)
            text[count++] = (char)(digit + 48);
        amount -= digit * divisor;
        divisor /= 10;
    }
    text[count] = 0;
    left = (sint16)(x - 16 - 4 * count);
    sub_8004EDD8((uint32)left, (uint32)(sint32)(sint16)y, draft_local_address(text, sizeof(text)));
    sub_80017FB0((uint32)(left + 8 * (sint32)count), (uint32)((sint16)y + 9), 7, 298);
}

static void shop_wallet(uint32 actor, uint32 x)
{
    shop_price((uint32)(sint32)(sint16)(x + 56), 56, r_u32(0x800715F0 + 4 * r_u8(actor + 240)));
}

static void shop_hud(void)
{
    if (r_u8(0x800AFFB0))
    {
        sub_8004F220(0x800AFEC0, 20);
        shop_wallet(0x800AFEC0, 20);
    }
    if (r_u8(0x800B00D0))
    {
        sub_8004F220(0x800AFFE0, 228);
        shop_wallet(0x800AFFE0, 228);
    }
}

static void shop_add_item(uint32 item, uint32 quantity, uint32 price)
{
    uint32 count = r_u16(0x800CBF04), entry = r_u32(0x800CBF00) + 12 * count;
    w_u32(entry, item);
    w_u32(entry + 4, quantity);
    w_u16(0x800CBF04, count + 1);
    w_u32(entry + 8, price);
}

static void shop_inventory(uint32 index)
{
    uint32 source = r_u32(0x800CBE48 + 4 * (uint16)index), count = r_u32(source), i;
    w_u32(0x800CBF00, sub_80011A98(12 * count));
    w_u16(0x800CBF04, 0);
    source += 4;
    for (i = 0; i < count; ++i, source += 12)
        shop_add_item(r_u32(source), r_u32(source + 4), r_u32(source + 8));
}

static uint32 shop_item_sprite(uint32 item)
{
    uint32 i, selected = 0;
    for (i = 0; i < 16; ++i)
        if (r_u8(0x800CBE4C + i) == (uint8)item)
            selected = i;
    return (uint16)(selected + 280);
}

static void shop_items(void)
{
    uint32 count = r_u16(0x800CBF04), visible = (sint16)count < 9 ? count : 8;
    uint32 i, shade, sprite, entry, offset = 0;
    sint32 base = (sint16)(184 - 20 * ((visible - 1) & 7)), y = 120;
    for (i = 0; i < r_u16(0x800CBF04); ++i)
    {
        entry = r_u32(0x800CBF00) + 12 * i;
        sprite = shop_item_sprite(r_u8(entry));
        shade = 64;
        if (r_u8(0x800AFFB0) && r_u32(0x800AFEC0) == i + 1)
            shade = 128;
        if (r_u8(0x800B00D0) && r_u32(0x800AFFE0) == i + 1)
            shade = 128;
        if (!r_u32(entry + 4))
            sub_800180D4((uint32)(base + (sint16)offset), (uint32)(sint32)(sint16)y, 8, 297, shade, shade, shade);
        sub_800180D4((uint32)(base + (sint16)offset), (uint32)(sint32)(sint16)y, 8, (uint16)sprite, shade, shade, shade);
        offset += 40;
        if ((sint16)offset == 320)
        {
            offset = 0;
            y += 40;
        }
    }
    sub_80017FB0(184, 40, 8, 296);
}

static void shop_camera(void)
{
    w_u32(0x800BBFC4, (uint32)-1000);
    w_u32(0x800BBFC8, (uint32)-1000);
    w_u16(0x800BBFD6, 0);
    w_u16(0x800BBFD4, 0);
    w_u16(0x800BBFD8, 0);
    w_u32(0x800BBFCC, (uint32)-6000);
    sub_800203B8(r_u32(r_u32(0x800CBEB8)) + 336);
}

static void shop_animation(uint32 animation)
{
    w_u16(0x800CBEF8, animation);
    sub_80057A14(0x800CBEBC, (uint16)animation);
}

static void shop_objects(void)
{
    uint32 actor = sub_8001F150(3), mesh;
    w_u32(0x800CBEB8, actor);
    w_u32(r_u32(actor) + 668, 32);
    mesh = r_u32(r_u32(0x800CBEB8));
    w_u16(mesh + 26, 2048);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    w_u32(mesh + 8, (uint32)-768);
    w_u32(mesh + 12, 0);
    w_u32(mesh + 16, 0);
    w_u16(0x800CBEBC, 3);
    w_u16(0x800CBED2, 0xFFFF);
    w_u32(0x800CBEC0, r_u32(r_u32(0x800CBEB8) + 4));
    shop_animation(0);
    mesh = sub_8001A3BC();
    w_u32(0x800CBEFC, mesh);
    sub_8001A2FC(130, mesh);
    mesh = r_u32(0x800CBEFC);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 26, 0);
    w_u16(mesh + 28, 0);
    w_u32(mesh + 8, 0);
    w_u32(mesh + 12, 0);
    w_u32(mesh + 16, 0);
}

static void shop_setup(void)
{
    sub_80032DFC();
    sub_80044800();
    w_u16(0x800719D0, 0);
    w_u16(0x800715E8, 0);
    w_u16(0x8007156C, 0);
    w_u16(0x8007155C, 0);
    w_u16(0x8007158C, 0);
    w_u16(0x80071A50, 8);
    w_u16(0x8007198C, 0);
    w_u16(0x800719FC, 0);
    sub_8004B87C();
    shop_objects();
    sub_80020124();
    shop_camera();
    sub_8002043C(768, 5, 0);
    sub_8002046C(768, 5, 0);
    w_u16(0x800717F4, 0);
    w_u16(0x80071808, 0);
    w_u16(0x80071820, 0);
}

static void shop_sound_bank(void)
{
    if ((sint16)r_u16(0x80071734) != 6)
    {
        sub_80044734();
        sub_800447B0(66, 80);
        sub_80044528(686, 66, 8);
        w_u16(0x80071734, 6);
    }
}

static void shop_gesture(uint32 gesture, uint32 duration)
{
    w_u8(0x800CBF14, gesture);
    w_u16(0x800CBF18, duration);
}

static void shop_initialize(void)
{
    uint32 i, actor;
    sub_80014848();
    shop_sound_bank();
    sub_80014F0C(687, 280, 1000);
    sub_8001EE9C();
    sub_8001EEE8(689, 690, 688, 119, 400, 400, 400, 3, 2);
    sub_80019BD4(701, 130, 400, 400, 400, 1);
    sub_800129E8();
    shop_setup();
    w_u32(0x8007165C, 0x800CBD34);
    w_u8(0x800CBF08, 0);
    for (i = 0; i < 2; ++i)
    {
        actor = 0x800AFEC0 + 288 * i;
        w_u16(actor + 228, 0);
        w_u16(actor + 226, 0);
        w_u32(actor, 0);
        w_u16(actor + 214, 0);
        w_u32(0x800CBF0C + 4 * i, 0);
        w_u16(actor + 246, 0);
    }
    shop_gesture(2, 60);
}

static void shop_cleanup(void)
{
    uint32 i;
    for (i = 119; i < 512; ++i)
        sub_80018CFC(i);
    for (i = 3; i < 32; ++i)
        sub_800573EC(i);
    sub_8003F638();
    sub_8001A3F4(r_u32(0x800CBEFC));
    sub_8001EE58(r_u32(0x800CBEB8));
    sub_80011AF8(r_u32(0x800CBF00));
}

static void shop_random_animation(void)
{
    shop_animation(r_u8(0x800CBEB4 + (sub_80011B8C() & 3)));
}

static void shop_lighting(uint32 mode)
{
    uint32 color, x, yz, green, blue;
    mode = (uint16)mode;
    if (mode > 1)
        return;
    color = mode ? 100 : 200;
    x = mode ? 80 : 160;
    yz = mode ? 66 : 132;
    green = mode ? 16 : 32;
    blue = mode ? 32 : 64;
    w_u16(0x800BEE70, color);
    w_u16(0x800BEE72, color);
    w_u16(0x800BEE74, color);
    w_u16(0x800BEE78, x);
    w_u16(0x800BEE7A, yz);
    w_u16(0x800BEE7C, yz);
    w_u16(0x800BEE82, green);
    w_u16(0x800BEE80, 0);
    w_u16(0x800BEE84, blue);
}

static void shop_next_gesture(void)
{
    uint32 gesture = r_u8(0x800CBF14);
    if (gesture == 2)
    {
        shop_lighting(1);
        shop_random_animation();
    }
    else if (gesture == 4 || gesture == 6 || gesture == 8)
    {
        shop_lighting(0);
        shop_animation(gesture);
        shop_voice(gesture == 4 ? 69 : gesture == 6 ? 70 : 73);
    }
    shop_gesture(2, 60);
}

static void shop_merchant_update(void)
{
    uint32 state;
    if (r_u16(0x800CBF18))
        w_u16(0x800CBF18, r_u16(0x800CBF18) - 1);
    if (!r_u16(0x800CBF18))
        shop_gesture(2, 60);
    state = r_u16(0x800CBEF8);
    if (!state)
    {
        if (r_u16(0x800CBECC) == 30)
            shop_voice(68);
        if (r_u8(0x800CBED0))
        {
            shop_next_gesture();
            w_u8(0x800CBF08, 1);
            shop_lighting(1);
        }
    }
    else if (state == 1)
    {
        if (r_u16(0x800CBECC) == 10)
            shop_voice(71);
        if (r_u8(0x800CBED0) && !(sint16)r_u16(0x800717A4))
            w_u16(0x800717A4, 8);
    }
    else if (state == 2 || (state >= 4 && state <= 8))
    {
        if (r_u8(0x800CBED0))
            shop_next_gesture();
    }
    sub_80058484(0x800CBEBC, r_u32(0x800CBEB8));
    sub_800585D8(0x800CBEBC);
    sub_80046278(0xFFFF);
    sub_8001DEB0(r_u32(r_u32(0x800CBEB8)));
}

static void shop_table(void)
{
    sub_80046278(0xFFFF);
    sub_8001C4B8(r_u32(0x800CBEFC));
}

static void shop_cursor(uint32 actor, uint32 player)
{
    uint32 selection = r_u32(actor), count, pulse;
    sint32 x, y;
    if (!selection)
    {
        x = 184;
        y = 40;
    }
    else
    {
        count = r_u16(0x800CBF04);
        if ((sint16)count >= 9)
            count = 8;
        x = (sint16)(184 - 20 * ((count - 1) & 7) + 40 * ((selection - 1) & 7));
        y = (sint32)selection < 9 ? 120 : 160;
    }
    pulse = r_u16(0x800719D0) & 31;
    if (pulse >= 16)
        pulse = 31 - pulse;
    pulse = (pulse + 16) * 4;
    sub_800180D4((uint32)x, (uint32)y, 7, 2 * (uint16)player + 299, pulse, pulse, pulse);
}

static void shop_replace_count(uint32 text, uint32 count)
{
    if (r_u8(text))
    {
        do
        {
            ++text;
        } while (r_u8(text));
    }
    w_u8(text - 1, count + 48);
}

static void shop_description(uint32 actor, uint32 player)
{
    uint32 selection = r_u32(actor), entry, item, text, count;
    sint32 x = (uint16)player ? 280 : 88;
    if (!selection)
        return;
    entry = r_u32(0x800CBF00) + 12 * selection - 12;
    if (!r_u32(entry + 4))
        return;
    sub_80017FB0((uint32)x, 198, 10, 2 * (uint16)player + 300);
    item = (uint16)(shop_item_sprite(r_u8(entry)) - 280);
    text = r_u32(0x800CBE5C + 4 * item);
    shop_replace_count(text, r_u16(entry + 4));
    count = sub_8004ED20(text);
    sub_8004EDD8((uint32)(x - 4 * (sint16)count), 203, text);
    shop_price((uint32)x, 184, r_u32(r_u32(0x800CBF00) + 12 * r_u32(actor) - 4));
}

static void shop_message(uint32 player, uint32 first, uint32 second)
{
    uint32 text, count;
    sint32 x = (uint16)player ? 280 : 88;
    sub_80017FB0((uint32)x, 198, 10, 2 * (uint16)player + 300);
    text = r_u32(0x800CBE9C + 4 * (uint16)first);
    count = sub_8004ED20(text);
    sub_8004EDD8((uint32)(x - 4 * (sint16)count), 184, text);
    text = r_u32(0x800CBE9C + 4 * (uint16)second);
    count = sub_8004ED20(text);
    sub_8004EDD8((uint32)(x - 4 * (sint16)count), 203, text);
}

static void shop_confirmation(uint32 actor, uint32 player)
{
    uint32 count, yes_shade = r_u16(actor + 238) ? 64 : 128;
    sint32 x = (uint16)player ? 280 : 88;
    sub_80017FB0((uint32)x, 198, 10, 2 * (uint16)player + 300);
    count = sub_8004ED20(r_u32(0x800CBEA8));
    sub_8004EDD8((uint32)(x - 4 * (sint16)count), 184, r_u32(0x800CBEA8));
    sub_8004EEFC((uint32)(x - 48), 200, r_u32(0x800CBEAC), 0, yes_shade, 0, 0);
    sub_8004EEFC((uint32)(x + 8), 200, r_u32(0x800CBEB0), 0, r_u16(actor + 238) ? 128 : 64, 0, 0);
}

static void shop_grant(uint32 actor, uint32 player, uint32 item)
{
    uint32 full = 0, address, value;
    item = (uint16)item;
    player = (uint16)player;
    if (item <= 4)
    {
        full = r_u16(actor + 210) == 72;
        sub_80052558(player, item == 0 ? 8 : item == 4 ? 1000 : 4);
    }
    else if (item == 5)
    {
        if (r_u16(actor + 208) >= 9)
            full = 1;
        else
            w_u16(actor + 208, r_u16(actor + 208) + 1);
    }
    else if (item == 6)
    {
        address = 0x80071A44 + 2 * player;
        w_u16(address, r_u16(address) + 900);
        if (r_u16(address) >= 3601)
        {
            w_u16(address, 3600);
            full = 1;
        }
    }
    else if (item >= 11 && item <= 18)
    {
        full = r_u16(actor + 246) != 0;
        value = item == 11 ? 2 : item == 12 ? 1 : item - 10;
        w_u16(actor + 246, value);
        w_u16(actor + 248, 24);
    }
    else if (item == 19)
    {
        w_u8(actor + 280, r_u8(actor + 280) + 1);
        if (r_u8(actor + 280) >= 10)
        {
            w_u8(actor + 280, 9);
            full = 1;
        }
    }
    shop_gesture(full ? 8 : 6, 150);
}

static void shop_player_update(uint32 player)
{
    uint32 actor, pending, wallet, step, buttons, state, selection, entry, other;
    player = (uint16)player;
    actor = 0x800AFEC0 + 288 * player;
    if (!r_u8(actor + 240))
        return;
    pending = 0x800CBF0C + 4 * player;
    wallet = 0x800715F4 + 4 * player;
    step = (uint32)((sint32)r_u32(pending) / 4);
    if (!step && r_u32(pending))
        step = 1;
    w_u32(wallet, r_u32(wallet) - step);
    w_u32(pending, r_u32(pending) - step);
    buttons = r_u16(0x80071790 + 2 * player);
    w_u16(actor + 226, buttons);
    w_u16(actor + 226, buttons & ~r_u16(actor + 228));
    w_u16(actor + 228, r_u16(actor + 228) & buttons);
    state = r_u16(actor + 214);
    switch (state)
    {
        case 0:
            if (r_u16(actor + 226) & 0x8000)
            {
                shop_select_sound();
                selection = r_u32(actor);
                w_u32(actor, selection ? selection - 1 : r_u16(0x800CBF04));
                w_u16(actor + 226, 0);
                w_u16(actor + 228, r_u16(actor + 228) | 0x8000);
            }
            if (r_u16(actor + 226) & 0x2000)
            {
                shop_select_sound();
                selection = r_u32(actor);
                w_u32(actor, selection == r_u16(0x800CBF04) ? 0 : selection + 1);
                w_u16(actor + 226, 0);
                w_u16(actor + 228, r_u16(actor + 228) | 0x2000);
            }
            if (r_u16(actor + 226) & 0x1000)
            {
                shop_select_sound();
                selection = r_u32(actor);
                w_u32(actor, (sint32)selection < 8 ? 0 : selection - 8);
                w_u16(actor + 226, 0);
                w_u16(actor + 228, r_u16(actor + 228) | 0x1000);
            }
            if (r_u16(actor + 226) & 0x4000)
            {
                shop_select_sound();
                selection = r_u32(actor);
                if (!selection)
                    w_u32(actor, 1);
                else if ((sint32)r_u16(0x800CBF04) >= (sint32)(selection + 8))
                    w_u32(actor, selection + 8);
                w_u16(actor + 226, 0);
                w_u16(actor + 228, r_u16(actor + 228) | 0x4000);
            }
            shop_cursor(actor, player);
            shop_description(actor, player);
            if (r_u16(actor + 226) & 240)
            {
                shop_confirm_sound();
                selection = r_u32(actor);
                w_u16(actor + 228, 240);
                if (!selection)
                {
                    w_u16(actor + 214, 4);
                    w_u32(wallet, r_u32(wallet) - r_u32(pending));
                    w_u32(pending, 0);
                }
                else
                {
                    entry = r_u32(0x800CBF00) + 12 * selection;
                    state = 1;
                    if (r_u32(wallet) - r_u32(pending) < r_u32(entry - 4))
                    {
                        shop_gesture(4, 90);
                        state = 2;
                    }
                    else if (!r_u32(entry - 8))
                    {
                        shop_gesture(4, 90);
                        state = 3;
                    }
                    w_u16(actor + 214, state);
                    w_u16(actor + 238, 0);
                }
            }
            break;
        case 1:
            shop_cursor(actor, player);
            entry = r_u32(0x800CBF00) + 12 * r_u32(actor);
            if (!r_u32(entry - 8))
            {
                shop_gesture(8, 90);
                w_u16(actor + 214, 3);
                w_u16(actor + 238, 0);
                break;
            }
            shop_confirmation(actor, player);
            if (r_u16(actor + 226) & 0x8000)
            {
                shop_select_sound();
                w_u16(actor + 228, 0x8000);
                w_u16(actor + 238, 0);
            }
            if (r_u16(actor + 226) & 0x2000)
            {
                shop_select_sound();
                w_u16(actor + 228, 0x2000);
                w_u16(actor + 238, 1);
            }
            if (r_u16(actor + 226) & 240)
            {
                w_u16(actor + 228, 240);
                if (r_u16(actor + 238))
                    shop_confirm_sound();
                else
                {
                    entry = r_u32(0x800CBF00) + 12 * r_u32(actor);
                    w_u32(entry - 8, r_u32(entry - 8) - 1);
                    w_u32(pending, r_u32(pending) + r_u32(entry - 4));
                    shop_grant(actor, player, r_u16(entry - 12));
                    shop_purchase_sound();
                }
                w_u16(actor + 214, 0);
            }
            break;
        case 2:
        case 3:
            shop_message(player, 0, state == 2 ? 1 : 2);
            w_u16(actor + 238, r_u16(actor + 238) + 1);
            if (r_u16(actor + 238) >= 61)
                w_u16(actor + 214, 0);
            break;
        case 4:
            other = 0x800AFEC0 + 288 * (player ^ 1);
            if (r_u8(0x800CBF08) && (!r_u8(other + 240) || r_u16(other + 214) == 4))
            {
                w_u8(0x800CBF08, 0);
                shop_lighting(0);
                shop_animation(1);
            }
            break;
    }
}

static uint32 shop_run(void)
{
    shop_initialize();
    sub_80048154();
    sub_8005B278(0);
    w_u16(0x8007194C, 254);
    w_u16(0x800717A4, (uint32)-16);
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
        sub_8002B134();
        sub_8003F008();
        shop_merchant_update();
        if (r_u8(0x800CBF08))
        {
            shop_items();
            shop_player_update(0);
            shop_player_update(1);
        }
        sub_8004EC74();
        shop_table();
        sub_800227FC();
        sub_800206D8();
        shop_hud();
        sub_8002F0F8();
        sub_8002F36C();
        sub_8005C008(r_u32(0x80071700));
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
        while ((sint32)sub_8005C154(0xF2000001) < 507)
        {
        }
        sub_80048180();
        sub_8005E814(r_u32(0x800719F0));
        sub_8005E648(r_u32(0x800719CC));
        sub_8005E5D8(r_u32(0x8007184C) + 9996);
        w_u16(0x800715E8, r_u16(0x800715E8) ^ 1);
        w_u16(0x800719D0, r_u16(0x800719D0) + 1);
    }
    sub_80013B64(0, 0, 0, 0);
    shop_cleanup();
    sub_80013974();
    sub_800451B8(0x8000, (uint32)-8, 0x8000, (uint32)-4);
    sub_80045048(2);
    sub_80013F80();
    return sub_800455DC();
}

uint32 sub_80014AE0(void)
{
    sub_80014888(684);
    sub_8004E4C8(685);
    shop_inventory(0);
    return shop_run();
}

uint32 sub_800203B8(uint32 mesh)
{
    w_u32(0x800BC098, mesh);
    w_u16(0x800BC09C, 0);
    w_u16(0x800BC09E, 0);
    w_u16(0x800BC0A0, 0);
    w_u16(0x800BC0C4, 8);
    return 8;
}

void sub_800227FC(void)
{
    sub_800204C0();
    sub_800210E8();
    w_u16(0x800BC0C6, 0);
    sub_80020CFC();
    sub_80020DD8();
}

uint32 sub_8004ED20(uint32 text)
{
    uint32 count = 0;
    while (r_u8(text++))
        ++count;
    return (uint32)(sint32)(sint16)count;
}
