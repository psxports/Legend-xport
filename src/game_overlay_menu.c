#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* FILE.DAT entry 7 owns these address bindings */
extern uint32 sub_8001EE9C(void), sub_80013F80(void), sub_80044800(void);
extern uint32 sub_800CC9D4(uint32), sub_800CCC54(void), sub_800CCC80(void), sub_800CC46C(void), sub_800CC4A8(void);
extern uint32 sub_800CCAE0(uint32, uint32), sub_800CCCAC(uint32, uint32, uint32), sub_800CC7D4(uint32), sub_800CC8C8(uint32);
extern void sub_800CCD48(uint32, uint32, uint32, uint32, uint32, uint32);
extern void sub_800CD160(uint32);
extern uint32 sub_800CCF38(uint32, uint32), sub_800CCDA8(uint32, uint32), sub_800CCE94(uint32);
extern void sub_800CE1A8(uint32, uint32, uint32);
extern void sub_800CE1E0(uint32, uint32, uint32, uint32);
extern uint32 sub_800CF7D4(uint32, uint32);
extern void sub_800CF1A8(uint32, uint32, uint32);
extern uint32 sub_800CA668(void), sub_800CA4F8(void), sub_800CA6F0(void), sub_800CA338(uint32), sub_800CA930(void), sub_800CAFBC(void), sub_800CC1D0(void);
extern void sub_800CE21C(uint32, uint32);
extern uint32 sub_800CAB38(void), sub_800CAAA8(void), sub_800CBC5C(void), sub_800CB130(void), sub_800CC234(uint32), sub_800CC288(uint32), sub_800CBF64(uint32), sub_800CB3D0(uint32), sub_800CB8B8(void), sub_800CBB80(uint32);
extern uint32 sub_8005E4D0(uint32, uint32), sub_8005B278(uint32);

uint32 sub_800CF6E0(void)
{
    sub_8001EE9C();
    return sub_8001EEE8(62, 63, 61, 41, 400, 400, 400, 0, 2);
}

uint32 sub_800CF730(void)
{
    sub_8001EE9C();
    return sub_8001EEE8(92, 93, 91, 67, 360, 360, 360, 1, 2);
}

uint32 sub_800CF784(void)
{
    sub_8001EE9C();
    return sub_8001EEE8(124, 125, 123, 93, 400, 400, 400, 2, 2);
}

static void menu_reset(void)
{
    static const uint32 zeros[] = {0x800719D0u, 0x800715E8u, 0x800717F4u, 0x80071808u, 0x80071A50u, 0x8007155Cu, 0x8007156Cu, 0x8007158Cu};
    uint32 i;
    sub_80013B64(1, 0, 0, 0);
    for (i = 0; i < sizeof(zeros) / sizeof(zeros[0]); ++i)
        w_u16(zeros[i], 0);
    sub_800451B8(0, 0, 255, 0);
    sub_80044800();
}

static sint32 menu_flash(uint32 velocity, uint32 outward)
{
    uint32 frame = r_u16(0x800719D0u);
    if (!(frame & 15u))
        sub_8004486C(1, 1, 3, 1500, 26000, 512);
    if (frame & 1u)
        sub_80013B64(1, 0, 0, 0);
    else
        sub_80013B64(1, 192, 255, 255);
    w_u16(0x800D089Cu, r_u16(0x800D089Cu) + (outward ? velocity : 0u - velocity));
    if (!(frame & 1u))
    {
        ++velocity;
        w_u16(0x80071808u, 3);
    }
    sub_800CC9D4(128);
    sub_800CCAE0(0x800D0704u, 5);
    return (sint32)velocity;
}

static void menu_burst(void)
{
    w_u16(0x80071808u, 8);
    w_u16(0x8007155Cu, 255);
    w_u16(0x8007156Cu, 255);
    w_u16(0x8007158Cu, 255);
    w_u16(0x80071A50u, 4);
}

uint32 sub_800CF440(void)
{
    sint32 position = -800;
    uint32 state = 0, timer = 0, i;
    sint32 y;
    menu_reset();
    w_u16(0x8007194Cu, 254);
    w_u16(0x800717A4u, (uint32)-16);
    w_u16(0x800716FCu, 2);
    while (r_u16(0x8007194Cu) != 255u || r_u16(0x800717A4u))
    {
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        w_u16(0x800D089Cu, (uint32)((sint16)position / -4));
        sub_800CC9D4((uint16)(((sint16)(position + 800) * 64) / 800));
        y = (sint16)position;
        for (i = 0; i < 10u; ++i)
        {
            sub_800CF1A8((uint32)-16, (uint32)y, i);
            y = (sint16)(y + 80);
        }
        if (state == 1u)
        {
            if (timer)
                timer = (uint16)(timer - 1u);
            if (timer == 1u)
                w_u16(0x800717A4u, 16);
        }
        else if (!state)
        {
            if ((sint16)position)
                position += 4;
            else
            {
                state = 1;
                timer = 180;
                menu_burst();
                sub_8004486C(1, 1, 12, 1200, 32000, 512);
            }
        }
        if ((r_u16(0x80071790u) & 0x800u) && !r_u16(0x8007194Cu))
            w_u16(0x800717A4u, 16);
        sub_800CC7D4(0);
    }
    sub_80013974();
    sub_800455DC();
    return sub_80013F80();
}

uint32 sub_800CD944(void)
{
    uint32 state = 0, selection = 0, idle = 0, done = 0, timer = 0, i;
    sint32 velocity = 0, slide = 0;
    menu_reset();
    w_u16(0x800717A4u, 0);
    w_u16(0x8007194Cu, 0);
    w_u16(0x800D089Cu, 256);
    sub_8004486C(1, 0, 2, 1500, 32000, 512);
    while (!done)
    {
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        switch (state)
        {
            case 0:
                velocity = menu_flash((uint32)velocity, 0);
                if ((sint16)r_u16(0x800D089Cu) <= 0)
                {
                    state = 1;
                    menu_burst();
                    w_u16(0x800D089Cu, 0);
                    sub_80013B64(1, 0, 0, 0);
                    sub_8004486C(4, 0, 0, 0, 0, 0);
                    sub_8004486C(1, 1, 4, 1500, 20000, 512);
                    timer = 50;
                    slide = 384;
                    velocity = 32;
                }
                break;
            case 1:
                sub_800CC9D4(64);
                sub_800CCC54();
                sub_800CCCAC((uint32)(-24 - slide), 8, 128);
                if ((sint16)timer)
                    timer = (uint16)(timer - 1u);
                if ((sint16)timer == 1)
                {
                    sub_8004486C(1, 0, 11, 1000, 32000, 512);
                    sub_80013FE8(13, 230, 65535);
                    sub_800451B8(0, 1, 0x8000, 0);
                }
                if (!(sint16)timer)
                {
                    slide -= velocity;
                    if (!(r_u16(0x800719D0u) & 1u))
                        velocity += 2;
                    if ((sint16)slide <= 0)
                    {
                        slide = 0;
                        state = 2;
                        timer = 25;
                        menu_burst();
                        sub_8004486C(1, 1, 12, 900, 32000, 512);
                    }
                }
                break;
            case 2:
                if ((sint16)timer)
                {
                    timer = (uint16)(timer - 1u);
                    if (!timer)
                        sub_8004486C(1, 0, 9, 1000, 32000, 512);
                }
                sub_800CC9D4(64);
                sub_800CCC54();
                sub_800CCCAC((uint32)-24, 8, 128);
                for (i = 0; i < 3u; ++i)
                {
                    /* MIPS supplies equal red, green and blue for each menu item */
                    uint32 shade = 48;
                    if (i == selection)
                    {
                        shade = r_u16(0x800719D0u) & 63u;
                        if (shade >= 32u)
                            shade = 64u - shade;
                        shade = 2u * shade + 128u;
                    }
                    sub_800180D4(192, (uint32)(sint32)(sint16)r_u16(0x800D07ACu + 2u * i), 125, i + 2u, shade, shade, shade);
                }
                if (selection == 1u && r_u16(0x80071A26u) != 65u)
                    selection = 0;
                if (r_u16(0x80071790u) & 0x1000u)
                {
                    idle = 0;
                    if ((uint16)selection)
                    {
                        --selection;
                        sub_800CC46C();
                        w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x1000u);
                        if ((uint16)selection == 1u && r_u16(0x80071A26u) != 65u)
                            selection = 0;
                    }
                }
                if (r_u16(0x80071790u) & 0x4000u)
                {
                    idle = 0;
                    if ((uint16)selection < 2u)
                    {
                        ++selection;
                        sub_800CC46C();
                        w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x4000u);
                        if ((uint16)selection == 1u && r_u16(0x80071A26u) != 65u)
                            selection = 2;
                    }
                }
                i = idle;
                if (r_u16(0x80071790u) & 0x40u)
                {
                    timer = 100;
                    sub_800CC4A8();
                    state = 3;
                    w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x40u);
                    idle = 0;
                    sub_800451B8(0x8000, (uint32)-16, 0x8000, 0);
                    i = 0;
                }
                idle = (uint16)(idle + 1u);
                if (i >= 1801u)
                {
                    sub_800451B8(0x8000, (uint32)-16, 0x8000, 0);
                    state = 4;
                    velocity = 0;
                    sub_8004486C(1, 0, 2, 1500, 32000, 512);
                    selection = 255;
                }
                break;
            case 3:
                if ((sint16)timer)
                {
                    timer = (uint16)(timer - 1u);
                    if (!timer)
                    {
                        state = 4;
                        velocity = 0;
                        sub_8004486C(1, 0, 2, 1500, 32000, 512);
                    }
                }
                sub_800CC9D4(64);
                sub_800CCC54();
                sub_800CCCAC((uint32)-24, 8, 128);
                for (i = 0; i < 3u; ++i)
                    if (i != (uint16)selection || (r_u16(0x800719D0u) & 15u) >= 8u)
                        sub_80017FB0(192, (uint32)(sint32)(sint16)r_u16(0x800D07ACu + 2u * i), 125, i + 2u);
                break;
            case 4:
                velocity = menu_flash((uint32)velocity, 1);
                if ((sint16)r_u16(0x800D089Cu) >= 257)
                {
                    sub_80013B64(1, 0, 0, 0);
                    done = 1;
                }
                break;
        }
        sub_800CC7D4(0);
        sub_800140DC();
    }
    sub_80013974();
    sub_800455DC();
    sub_80013F80();
    return (uint16)selection;
}

uint32 sub_800CD1BC(void)
{
    uint32 state = 0, done = 0, selection = 0, accepted = 0, i;
    sint32 velocity = 0;
    menu_reset();
    w_u16(0x800D089Cu, 256);
    w_u16(0x800717A4u, 0);
    w_u16(0x8007194Cu, 0);
    sub_8004486C(1, 0, 2, 1500, 32000, 512);
    do
    {
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        switch (state)
        {
            case 0:
                velocity = menu_flash((uint32)velocity, 0);
                if ((sint16)r_u16(0x800D089Cu) <= 0)
                {
                    state = 1;
                    menu_burst();
                    w_u16(0x800D089Cu, 0);
                    sub_80013B64(1, 0, 0, 0);
                    sub_8004486C(4, 0, 0, 0, 0, 0);
                    sub_8004486C(1, 1, 4, 1500, 20000, 512);
                }
                break;
            case 1:
                sub_800CC9D4(64);
                sub_80013FE8(13, 230, 65535);
                sub_800451B8(0, 1, 0x8000, 0);
                state = 2;
                break;
            case 2:
                sub_800CC9D4(64);
                sub_800CCC80();
                sub_800CCCAC((uint32)-24, (uint32)-24, 128);
                for (i = 0; i < 9u; ++i)
                {
                    uint32 red = 128, green = 128, blue = 128;
                    if (i == (uint16)selection)
                    {
                        blue = r_u16(0x800719D0u) & 63u;
                        if (blue >= 32u)
                            blue = 64u - blue;
                        blue = 2u * blue + 128u;
                        red = green = 128u - (blue >> 2);
                    }
                    sub_800CCD48(0x800D0730u + 4u * r_u8(0x800D0768u + 2u * i), (uint32)(sint32)(sint16)r_u16(0x800D0774u + 2u * i), r_u32(0x800D0788u + 4u * i), blue, red, green);
                }
                sub_800CD160((uint16)selection >= 7u);
                sub_800CCF38((uint32)(sint32)(sint16)r_u16(0x800D077Cu) + (uint32)(sint32)(sint16)r_u16(0x800D08A0u) + 11u, r_u16(0x800717ECu));
                sub_800CCF38((uint32)(sint32)(sint16)r_u16(0x800D077Eu) + (uint32)(sint32)(sint16)r_u16(0x800D08A0u) + 11u, r_u16(0x8007179Cu));
                sub_800CCF38((uint32)(sint32)(sint16)r_u16(0x800D0780u) + (uint32)(sint32)(sint16)r_u16(0x800D08A0u) + 11u, r_u16(0x80071590u));
                if ((r_u16(0x80071790u) & 0x1000u) && (uint16)selection)
                {
                    --selection;
                    sub_800CC46C();
                    w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x1000u);
                }
                if ((r_u16(0x80071790u) & 0x4000u) && (uint16)selection < 8u)
                {
                    ++selection;
                    sub_800CC46C();
                    w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x4000u);
                }
                switch ((uint16)selection)
                {
                    case 0:
                        sub_800CCDA8(0x800719C8u, 3);
                        break;
                    case 1:
                        sub_800CCDA8(0x80071A30u, 2);
                        break;
                    case 2:
                        sub_800CCDA8(0x800716E0u, 2);
                        break;
                    case 3:
                        sub_800CCDA8(0x800719BCu, 2);
                        break;
                    case 4:
                        sub_800CCE94(0x800717ECu);
                        break;
                    case 5:
                        sub_800CCE94(0x8007179Cu);
                        break;
                    case 6:
                        sub_800CCE94(0x80071590u);
                        break;
                    case 7:
                    case 8:
                        if (r_u16(0x80071790u) & 0x40u)
                        {
                            accepted = 1;
                            sub_800CC4A8();
                        }
                        break;
                }
                if (r_u16(0x80071790u) & 0x10u)
                {
                    accepted = 1;
                    selection = 8;
                }
                if (accepted)
                {
                    state = 3;
                    w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x50u);
                    velocity = 0;
                    sub_800451B8(0x8000, (uint32)-16, 0x8000, 0);
                    sub_8004486C(1, 0, 2, 1500, 32000, 512);
                }
                break;
            case 3:
                velocity = menu_flash((uint32)velocity, 1);
                if ((sint16)r_u16(0x800D089Cu) >= 257)
                {
                    sub_80013B64(1, 0, 0, 0);
                    done = 1;
                }
                break;
        }
        sub_800CC7D4(0);
        sub_800140DC();
    } while (!done);
    sub_80013974();
    sub_800455DC();
    sub_80013F80();
    return (uint16)selection;
}

uint32 sub_800CF860(uint32 mode)
{
    uint16 angle[4], speed[4];
    uint8 chosen[4], occupied[4], selected[2] = {0, 1}, latched[2] = {1, 1}, confirmed[2] = {0, 0};
    uint32 objects[3], entities[3][15], entity_address[3], targets[2][4];
    uint32 cancelled = 0, state = 0, fade = 128, wait = 0, i, j, player, object, mesh;
    mode = (uint16)mode;
    sub_80013B64(1, 0, 0, 0);
    w_u16(0x8007194Cu, 254);
    w_u16(0x800717A4u, (uint32)-16);
    w_u16(0x800719D0u, 0);
    w_u16(0x800715E8u, 0);
    w_u16(0x800716FCu, 2);
    w_u16(0x800717F4u, 0);
    w_u16(0x80071808u, 0);
    w_u16(0x80071A50u, 0);
    w_u16(0x8007155Cu, 0);
    w_u16(0x8007156Cu, 0);
    w_u16(0x8007158Cu, 0);
    sub_800451B8(0, 0, 255, 0);
    sub_80013FE8(15, 230, 65535);
    sub_800451B8(0, 1, 0x8000, 0);
    sub_80044800();
    for (i = 0; i < 3u; ++i)
    {
        chosen[i] = 0;
        speed[i] = 0;
        angle[i] = 0;
        objects[i] = sub_8001F150(i);
        mesh = r_u32(objects[i]);
        if (i == 1u)
            w_u32(mesh + 332u, (uint32)-32);
        /* Entity fields beyond the initialized subset are filled by 57A14 */
        ((uint16 *)entities[i])[0] = (uint16)i;
        entities[i][1] = r_u32(objects[i] + 4u);
        ((uint16 *)entities[i])[11] = 65535u;
        entity_address[i] = draft_local_address(entities[i], sizeof(entities[i]));
        sub_80057A14(entity_address[i], 0);
        w_u16(mesh + 26u, 2048);
        w_u32(mesh + 8u, 2000u * i - 2000u);
        w_u32(mesh + 12u, 2000);
        w_u32(mesh + 16u, 7000);
        occupied[i] = 0;
    }
    sub_80020124();
    w_u16(0x800BBFD6u, 0);
    w_u16(0x800BBFD4u, 0);
    w_u16(0x800BBFD8u, 0);
    w_u32(0x800BBFC4u, 0);
    w_u32(0x800BBFC8u, 0);
    w_u32(0x800BBFCCu, (uint32)-1000);
    sub_8004B87C();
    {
        static const uint32 first[] = {0x800BEFBAu, 0x800BEFB8u, 0x800BEFC0u, 0x800BEFCAu, 0x800BEFC8u, 0x800BEE70u, 0x800BEE72u, 0x800BEE74u, 0x800BEE78u, 0x800BEE7Au, 0x800BEE7Cu, 0x800BEE82u, 0x800BEE84u, 0x800BEFC2u, 0x800BEE80u};
        static const uint32 second[] = {0x800C5D4Eu, 0x800C5D4Cu, 0x800C5D54u, 0x800C5D5Eu, 0x800C5D5Cu, 0x800C5CFCu, 0x800C5CFEu, 0x800C5D00u, 0x800C5D04u, 0x800C5D06u, 0x800C5D08u, 0x800C5D0Eu, 0x800C5D10u, 0x800C5D56u, 0x800C5D0Cu};
        static const uint32 value[] = {2816, 512, 768, 1280, (uint32)-256, 255, 200, 200, 200, 200, 132, 32, 128, 2048, 0};
        for (i = 0; i < 15u; ++i)
        {
            w_u16(first[i], value[i]);
            w_u16(second[i], value[i]);
        }
        w_u16(0x800719A0u, 64);
        w_u16(0x80071564u, 64);
        w_u16(0x800715D0u, 64);
        w_u16(0x800716DCu, 64);
        w_u16(0x80071A4Cu, 64);
        w_u16(0x8007161Cu, 64);
    }
    if (mode == 1u)
    {
        confirmed[1] = 1;
        targets[0][0] = 0;
        targets[0][1] = 2000;
        targets[0][2] = 6000;
    }
    else
    {
        targets[0][0] = (uint32)-1000;
        targets[0][1] = 2000;
        targets[0][2] = 6000;
        targets[1][0] = 1000;
        targets[1][1] = 2000;
        targets[1][2] = 6000;
    }
    while (r_u16(0x8007194Cu) != 255u || r_u16(0x800717A4u))
    {
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        sub_80048EB8();
        sub_80049180();
        sub_800206D8();
        for (player = 0; player < 2u; ++player)
        {
            uint32 pad = 0x80071790u + 2u * player;
            if (r_u16(pad))
            {
                if (latched[player])
                    w_u16(pad, 0);
            }
            else
                latched[player] = 0;
        }
        if (state == 1u)
        {
            if ((r_u16(0x80071790u) & 0x10u) && !cancelled)
            {
                cancelled = 1;
                w_u16(0x800717A4u, 16);
            }
            if (mode == 2u && (r_u16(0x80071792u) & 0x10u) && !cancelled)
            {
                cancelled = 1;
                w_u16(0x800717A4u, 16);
            }
            for (player = 0; player < 2u; ++player)
                if (!confirmed[player] && !cancelled)
                {
                    uint32 keys = r_u16(0x80071790u + 2u * player);
                    while (occupied[selected[player]])
                        selected[player] = (uint8)((selected[player] + 1u) % 3u);
                    if (keys & 0x8000u)
                    {
                        do
                        {
                            selected[player] = selected[player] ? selected[player] - 1u : 2u;
                        } while (occupied[selected[player]]);
                        sub_800CC46C();
                        latched[player] = 1;
                    }
                    if (keys & 0x2000u)
                    {
                        do
                        {
                            selected[player] = selected[player] == 2u ? 0u : selected[player] + 1u;
                        } while (occupied[selected[player]]);
                        sub_800CC46C();
                        latched[player] = 1;
                    }
                    if (keys & 0x40u)
                    {
                        confirmed[player] = 1;
                        occupied[selected[player]] = (uint8)(player + 1u);
                        chosen[selected[player]] = 1;
                        latched[player] = 1;
                        sub_800CC4A8();
                        w_u16(0x80071808u, 8);
                        speed[selected[player]] = 160;
                        sub_8004486C(1, 1, 4, 2000, 10000, 512);
                        sub_8004486C(1, 2, r_u16(0x800D0870u + 2u * selected[player]), 1000, 30000, 512);
                        w_u16(0x8007158Cu, 128);
                        w_u16(0x8007156Cu, 64);
                        w_u16(0x8007155Cu, 0);
                        w_u16(0x80071A50u, 16);
                    }
                    sub_800CF7D4(selected[player], player);
                }
            if (confirmed[0] && confirmed[1])
            {
                wait = 250;
                state = 2;
                sub_800451B8(0x8000, (uint32)-8, 0x8000, 0);
            }
        }
        else if (state == 2u)
        {
            if (fade)
                --fade;
            if (wait)
            {
                wait = (uint16)(wait - 1u);
                if (wait == 150u)
                    sub_8004486C(1, 0, 10, 1000, 30000, 512);
                if (!wait)
                    w_u16(0x800717A4u, 16);
            }
        }
        else if (!state && !r_u16(0x8007194Cu) && !r_u16(0x800717A4u))
        {
            state = 1;
            sub_8004486C(1, 0, 8, 1000, 30000, 512);
        }
        if (fade)
        {
            sint32 y = (sint16)r_u16(0x800D08A0u);
            for (i = 0; i < 4u; ++i)
                sub_800180D4((i & 1u) ? 192u : 0u, (uint32)(y + (i >= 2u ? 128 : 0)), 2499, 62u + i, fade, fade, fade);
        }
        for (i = 0; i < 3u; ++i)
        {
            uint32 x = 96u + 96u * i;
            angle[i] = (uint16)((angle[i] - speed[i]) & 4095u);
            sub_80015364(x, 190, 2498, chosen[i] ? 203u : 198u + i, (uint32)(sint32)(sint16)angle[i], 1);
            sub_80015364(x, 190, 2498, chosen[i] ? 202u : 201u, (uint32)(sint32)(sint16)angle[i], (uint32)-1);
            if (!(r_u16(0x800719D0u) & 1u) && (sint16)speed[i] >= 33)
                speed[i] = (uint16)(speed[i] - 1u);
        }
        for (i = 0; i < 3u; ++i)
            if (occupied[i])
            {
                object = objects[i];
                mesh = r_u32(object);
                j = occupied[i] - 1u;
                sub_80030E5C(mesh + 8u, draft_local_address(targets[j], sizeof(targets[j])), 128, 8);
                sub_80058484(entity_address[i], object);
                sub_80051614(mesh + 8u, entity_address[i], (uint32)(sint32)(sint16)r_u16(mesh + 26u));
                sub_800585D8(entity_address[i]);
                sub_80046278(0xFFFFF);
                sub_8001DEB0(mesh);
            }
        sub_800CC7D4(0);
        sub_800140DC();
    }
    sub_80013974();
    sub_800455DC();
    sub_80013F80();
    for (i = 0; i < 3u; ++i)
        sub_8001EE58(objects[i]);
    if (cancelled)
        return 0;
    w_u8(0x800AFFB0u, 1);
    w_u16(0x800AFFB6u, 0);
    w_u8(0x800B00D0u, 0);
    w_u8(0x800AFF94u, selected[0]);
    if (mode == 2u)
    {
        w_u8(0x800B00D0u, 2);
        w_u16(0x800B00D6u, 0);
        w_u8(0x800B00B4u, selected[1]);
    }
    return mode;
}

void sub_800CE39C(void)
{
    uint32 selection = 0, latch = 1, state = 0, message = 1, timer = 0, file = 0, yes = 0, count = 0, i, shade, detail;
    sint32 card = -1;
    w_u16(0x8007194Cu, 254);
    w_u16(0x800717A4u, (uint32)-16);
    w_u16(0x800716FCu, 2);
    sub_80044800();
    sub_800CA668();
    sub_800CA4F8();
    while (r_u16(0x8007194Cu) != 255u || r_u16(0x800717A4u))
    {
        if (latch)
        {
            if (r_u16(0x80071790u))
                w_u16(0x80071790u, 0);
            else
                latch = 0;
        }
        sub_800139C0();
        sub_8005E4D0(r_u32(0x8007184Cu), 2500);
        if (message)
        {
            i = (uint16)(2u * message - 2u);
            sub_800CE1A8(90, r_u32(0x800D0800u + 4u * i), 128);
            sub_800CE1A8(108, r_u32(0x800D0804u + 4u * i), 128);
        }
        else if (state != 10u)
            for (i = 0; i < 5u; ++i)
            {
                uint32 enabled = 1;
                shade = r_u16(0x800719D0u) & 63u;
                if (shade >= 32u)
                    shade = 63u - shade;
                shade = 2u * shade + 64u;
                if (i != (uint16)selection)
                    shade = 32;
                if (i && i < 4u)
                    enabled = card != -1;
                if (i && i < 3u && card == -2)
                    enabled = 0;
                if (i == 3u && card == 1)
                    enabled = 0;
                if (enabled)
                    sub_800CE1A8((uint32)(sint32)(sint16)(18u * r_u16(0x800D07F4u + 2u * i)), r_u32(0x800D07B4u + 4u * i), shade);
            }
        detail = 0;
        switch (state)
        {
            case 0:
                if (!r_u16(0x8007194Cu))
                    state = 1;
                break;
            case 1:
                if ((uint16)timer)
                {
                    --timer;
                    break;
                }
                sub_800CA338(r_u16(0x800CA1C2u) ? 16u : 0u);
                do
                {
                    card = (sint32)sub_800CA930();
                    count = card == 1 ? sub_800CAFBC() : 0;
                } while ((sint32)count == -1);
                selection = 0;
                sub_800CC1D0();
                state = 2;
                message = 0;
                file = 0;
                if (card == -2)
                {
                    latch = 1;
                    sub_800CC46C();
                    state = 10;
                    yes = 0;
                }
                break;
            case 2:
                if (card == -1)
                {
                    if (sub_800CAB38())
                        goto retry;
                }
                else if (!sub_800CAAA8())
                    goto retry;
                if (r_u16(0x80071790u) & 0x10u)
                    goto exit_card;
                if (r_u16(0x80071790u) & 0x1000u)
                {
                    if (card == -1)
                    {
                        selection = 0;
                        sub_800CC46C();
                    }
                    if (card == 1)
                    {
                        if ((uint16)selection)
                        {
                            --selection;
                            sub_800CC46C();
                        }
                        if ((uint16)selection == 3u)
                            --selection;
                    }
                    latch = 1;
                    if (card == -2 && (uint16)selection)
                    {
                        selection = 0;
                        sub_800CC46C();
                    }
                }
                if (r_u16(0x80071790u) & 0x4000u)
                {
                    if (card == -1)
                    {
                        selection = 4;
                        sub_800CC46C();
                    }
                    if (card == 1)
                    {
                        if ((uint16)selection < 4u)
                        {
                            ++selection;
                            sub_800CC46C();
                        }
                        if ((uint16)selection == 3u)
                            selection = 4;
                    }
                    latch = 1;
                    if (card == -2 && (uint16)selection != 3u)
                    {
                        selection = 3;
                        sub_800CC46C();
                    }
                }
                switch ((uint16)selection)
                {
                    case 0:
                        i = card == -1 ? 4u : card == 1 ? 0u : 2u;
                        sub_800CE1A8(36, r_u32(0x800D0848u + 4u * i), 128);
                        sub_800CE1A8(54, r_u32(0x800D084Cu + 4u * i), 128);
                        break;
                    case 1:
                        if (sub_800CBC5C() || (sint32)sub_800CB130() > 0)
                        {
                            if (r_u16(0x80071790u) & 0x40u)
                            {
                                latch = 1;
                                sub_800CC46C();
                                state = 11;
                                if (!sub_800CBC5C())
                                {
                                    state = 6;
                                    timer = 4;
                                    message = 6;
                                }
                                else
                                    yes = 0;
                            }
                        }
                        else
                        {
                            sub_800CE1A8(36, r_u32(0x800D07ECu), 128);
                            sub_800CE1A8(54, r_u32(0x800D07F0u), 128);
                        }
                        break;
                    case 2:
                        if (count)
                        {
                            uint32 first, second;
                            detail = 1;
                            first = sub_800CC234(file);
                            second = sub_800CC288(file);
                            sub_800CE21C((uint16)first, (uint16)second);
                            sub_800CBF64(file);
                        }
                        else
                        {
                            sub_800CE1A8(36, r_u32(0x800D0860u), 128);
                            sub_800CE1A8(54, r_u32(0x800D0864u), 128);
                            break;
                        }
                        if ((r_u16(0x80071790u) & 0x2000u) && file < count - 1u)
                        {
                            latch = 1;
                            file = (uint16)(file + 1u);
                            sub_800CC46C();
                        }
                        else if ((r_u16(0x80071790u) & 0x8000u) && file)
                        {
                            latch = 1;
                            file = (uint16)(file - 1u);
                            sub_800CC46C();
                        }
                        else if (r_u16(0x80071790u) & 0x40u)
                        {
                            latch = 1;
                            sub_800CC46C();
                            state = 8;
                            yes = 0;
                        }
                        break;
                    case 3:
                        if (r_u16(0x80071790u) & 0x40u)
                        {
                            latch = 1;
                            sub_800CC46C();
                            state = 10;
                            yes = 0;
                        }
                        break;
                    case 4:
                        if (r_u16(0x80071790u) & 0x40u)
                        {
                            w_u16(0x800717A4u, 16);
                            state = 4;
                            sub_800CC46C();
                        }
                        break;
                }
                break;
            case 5:
                if ((uint16)timer)
                    --timer;
                if (r_u16(0x80071790u) & 0x40u)
                {
                    timer = 0;
                    latch = 1;
                }
                if (!(uint16)timer)
                {
                    timer = 4;
                    state = 1;
                    message = 1;
                }
                break;
            case 6:
                i = (uint16)timer;
                --timer;
                if (i)
                    break;
                state = 5;
                timer = 300;
                message = 2;
                if (sub_800CB3D0(0))
                    message = 4;
                break;
            case 7:
                i = (uint16)timer;
                --timer;
                if (!i)
                {
                    state = 5;
                    timer = 300;
                    message = 2;
                    if (sub_800CB8B8())
                        message = 5;
                }
                break;
            case 8:
            case 10:
            case 11:
                if (!sub_800CAAA8())
                    goto retry;
                if (state == 10u)
                {
                    sub_800CE1A8(36, r_u32(0x800D07E0u), 128);
                    sub_800CE1A8(54, r_u32(0x800D07E4u), 128);
                    sub_800CE1A8(72, r_u32(0x800D07E8u), 128);
                    i = 90;
                }
                else
                {
                    sub_800CE1A8(36, r_u32(state == 8u ? 0x800D07D0u : 0x800D07DCu), 128);
                    i = 54;
                }
                sub_800CE1E0(144, i, r_u32(0x800D07D4u), yes ? 64u : 200u);
                sub_800CE1E0(208, i, r_u32(0x800D07D8u), yes ? 200u : 64u);
                if (r_u16(0x80071790u) & 0x8000u)
                {
                    if (yes)
                    {
                        yes = 0;
                        latch = 1;
                        sub_800CC46C();
                    }
                    break;
                }
                if (r_u16(0x80071790u) & 0x2000u)
                {
                    if (!yes)
                    {
                        yes = 1;
                        latch = 1;
                        sub_800CC46C();
                    }
                    break;
                }
                if (r_u16(0x80071790u) & 0x40u)
                {
                    if (state == 10u)
                    {
                        if (!yes)
                        {
                            w_u16(0x800717A4u, 16);
                            state = 4;
                            latch = 1;
                            sub_800CC46C();
                        }
                        else
                        {
                            latch = 1;
                            sub_800CC46C();
                            state = 7;
                            timer = 4;
                            message = 7;
                        }
                    }
                    else if (state == 8u)
                    {
                        state = 9;
                        if (yes)
                        {
                            latch = 1;
                            sub_800CC46C();
                            message = 8;
                            timer = 4;
                        }
                        else
                        {
                            state = 2;
                            latch = 1;
                            sub_800CC46C();
                        }
                    }
                    else if (!yes)
                    {
                        state = 2;
                        latch = 1;
                        sub_800CC46C();
                    }
                    else
                    {
                        latch = 1;
                        sub_800CC46C();
                        state = 12;
                        timer = 4;
                        message = 6;
                    }
                }
                else if (state == 10u)
                {
                    if (r_u16(0x80071790u) & 0x10u)
                        goto exit_card;
                }
                else if (r_u16(0x80071790u) & 0x5010u)
                    state = 2;
                break;
            case 9:
                i = (uint16)timer;
                --timer;
                if (!i)
                {
                    state = 5;
                    timer = 300;
                    message = 3;
                    if (sub_800CBB80(file))
                        message = 9;
                }
                break;
            case 12:
                if ((uint16)timer)
                    --timer;
                else
                {
                    state = 5;
                    timer = 300;
                    message = 2;
                    if (sub_800CB3D0(1))
                        message = 4;
                }
                break;
        }
        goto render_card;
    retry:
        state = 1;
        message = 1;
        timer = 4;
        goto render_card;
    exit_card:
        w_u16(0x800717A4u, 16);
        state = 4;
    render_card:
        sub_800CC8C8(detail);
    }
    sub_80013974();
    sub_8005B278(0);
    sub_800CA6F0();
    sub_800CA590();
}
