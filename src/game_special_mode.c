#include "psx.h"
#include "game_draft_signatures.h"

extern uint32 sub_800449A0(uint32 channel);

static void special_copy_player(uint32 destination, uint32 source)
{
    uint32 offset;
    for (offset = 0; offset < 288u; offset += 16u)
    {
        uint32 a = r_u32(source + offset), b = r_u32(source + offset + 4u);
        uint32 c = r_u32(source + offset + 8u), d = r_u32(source + offset + 12u);
        w_u32(destination + offset, a);
        w_u32(destination + offset + 4u, b);
        w_u32(destination + offset + 8u, c);
        w_u32(destination + offset + 12u, d);
    }
}

uint32 sub_8003278C(uint32 pitch)
{
    uint32 channel = (uint16)sub_800448F4();
    uint32 volume = (uint16)sub_80044F58(16000u);
    return sub_8004486C(1, channel, 24, (uint16)pitch, volume, r_u16(0x80071A20u));
}

void sub_80056A5C(uint32 player)
{
    uint32 active = r_u8(player + 240u), kind;
    if (!active || (r_u16(0x8007199Cu) && active - 1u == (r_u16(0x80071928u) ^ 1u)))
        return;
    w_u16(0x800718F8u, r_u16(0x800718F8u) + 1u);
    kind = r_u16(0x800719F4u);
    if (kind == 0u)
        sub_80056324(player);
    else if (kind == 1u)
        sub_8005653C(player);
    else if (kind == 2u)
        sub_800567C4(player);
    if (!(r_u16(0x800718F8u) & 3u))
        sub_8003278C((sub_80011B8C() & 127u) + 400u);
    if (r_u16(0x800718F8u) == 100u)
    {
        w_u16(0x8007199Cu, 0);
        w_u8(0x80071544u, 0);
        sub_800513CC(player, 0);
        sub_80022B24(0);
        sub_80013B64(1, 0, 0, 0);
        w_u16(0x8007171Cu, 1);
        sub_800449A0(r_u16(0x8007168Cu));
        sub_8004486C(4, r_u16(0x8007168Cu), 0, 0, 0, 0);
        w_u32(0x8007179Cu, r_u16(0x80071830u));
        sub_80044FB0();
    }
    sub_80058484(player + 76u, r_u32(player + 52u));
    sub_800585D8(player + 76u);
    sub_80052EE8(player);
}

uint32 sub_800571F0(void)
{
    uint32 temporary = sub_800119DC(288u), i, player;
    special_copy_player(temporary, 0x800AFEC0u);
    sub_80056A5C(temporary);
    special_copy_player(0x800AFEC0u, temporary);
    special_copy_player(temporary, 0x800AFFE0u);
    sub_80056A5C(temporary);
    special_copy_player(0x800AFFE0u, temporary);
    sub_80011A70(288u);
    for (i = 0; i < 2u; ++i)
    {
        player = 0x800AFEC0u + 288u * i;
        if (r_u8(player + 240u) && r_u8(player + 240u) - 1u == r_u16(0x80071928u))
        {
            sub_80046278(r_u16(player + 266u));
            sub_8001DEB0(r_u32(r_u32(player + 52u)));
        }
    }
    return 0;
}

void sub_800406B8(uint32 node)
{
    uint32 descriptor = r_u32(node + 12u), mesh = r_u32(descriptor);
    sub_80058484(node + 92u, descriptor);
    sub_80046278(r_u16(node + 224u));
    if (r_u16(0x800BFD2Cu + 40u * r_u16(node + 92u)) == 2u)
        sub_8001DEB0(mesh);
    else
        sub_8001C4B8(mesh);
}

void sub_8003F5E0(void)
{
    uint32 node = r_u32(0x80071868u);
    while (node)
    {
        uint32 kind = r_u32(node + 8u), next = r_u32(node + 4u);
        if (kind == 13u)
            sub_800406B8(node);
        node = next;
    }
}
