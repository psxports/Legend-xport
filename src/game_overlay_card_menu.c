#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <string.h>
extern uint32 sub_800CA778(void), sub_800CA880(void), sub_800CA338(uint32), sub_800CAD5C(uint32), sub_800CC138(uint32, uint32), sub_800CBE20(uint32, uint32), sub_800CC740(void);
extern uint32 sub_80068468(uint32), sub_8005C228(uint32, uint32), sub_8005C068(uint32), sub_8005C058(uint32), sub_8005C078(uint32);
extern uint32 sub_8005DFE4(uint32), sub_8005B278(uint32), sub_8005E814(uint32), sub_8005E648(uint32), sub_8005E5D8(uint32), sub_80060D78(uint32);
uint32 sub_800CAAA8(void);

uint32 sub_800CA668(void)
{
    static const uint32 addresses[] = {0x800D08BCu, 0x800D08B8u, 0x800D0B18u, 0x800D0B1Cu, 0x800D0B20u, 0x800D08B4u, 0x800D0B40u};
    static const uint32 sizes[] = {480, 5760, 7680, 7680, 7680, 960, 16384};
    uint32 i, result = 0;
    for (i = 0; i < 7u; ++i)
    {
        result = sub_80011A98(sizes[i]);
        w_u32(addresses[i], result);
    }
    return result;
}

uint32 sub_800CA6F0(void)
{
    static const uint32 addresses[] = {0x800D08BCu, 0x800D08B8u, 0x800D0B18u, 0x800D0B1Cu, 0x800D0B20u, 0x800D08B4u, 0x800D0B40u};
    uint32 i, result = 0;
    for (i = 0; i < 7u; ++i)
        result = sub_80011AF8(r_u32(addresses[i]));
    return result;
}

uint32 sub_800CAB38(void)
{
    for (;;)
    {
        sint32 status;
        sub_800CA880();
        sub_80068468(r_u32(0x800D0B44u));
        status = (sint32)sub_800CA778();
        if (status == 0 || status == 3)
            return 1;
        if (status == 2)
            return 0;
    }
}

uint32 sub_800CAAA8(void)
{
    for (;;)
    {
        sint32 status;
        sub_800CA880();
        sub_80068468(r_u32(0x800D0B44u));
        status = (sint32)sub_800CA778();
        if (!status)
            return 1;
        if (status == 2 || status == 3)
            return 0;
    }
}

uint32 sub_800CAFBC(void)
{
    uint32 directory[10], carrier = draft_local_address(directory, sizeof(directory)), i, j, destination;
    w_u32(0x800D0B48u, 0);
    w_u32(0x800D0B4Cu, 0);
    if (!sub_800CAAA8())
        return (uint32)-1;
    sub_800CA338(r_u16(0x800D0B44u));
    w_u8(0x800D0B29u, '*');
    w_u8(0x800D0B2Au, 0);
    if (sub_8005C228(0x800D0B24u, carrier))
        do
        {
            i = r_u32(0x800D0B48u);
            destination = 0x800D08C0u + 40u * i;
            w_u32(0x800D0B48u, i + 1u);
            for (j = 0; j < 10u; ++j)
                w_u32(destination + 4u * j, directory[j]);
            w_u32(0x800D0B4Cu, r_u32(0x800D0B4Cu) + (uint32)((sint32)directory[6] >> 13));
        } while (sub_8005C068(carrier));
    for (i = 0; (sint32)i < (sint32)r_u32(0x800D0B48u); i = (uint16)(i + 1u))
        sub_800CAD5C(i);
    return sub_800CAAA8() ? r_u32(0x800D0B48u) : (uint32)-1;
}

uint32 sub_800CC1D0(void)
{
    uint32 page, index;
    for (page = 0; page < 3u; ++page)
        for (index = 0; index < 15u; ++index)
            sub_800CC138(index, page);
    return page < 3u;
}

uint32 sub_800CBC5C(void)
{
    uint32 file, i, name = r_u32(0x800D06C0u);
    if ((sint32)r_u32(0x800D0B48u) <= 0)
        return 0;
    for (file = 0; (sint32)file < (sint32)r_u32(0x800D0B48u); file = (uint16)(file + 1u))
    {
        for (i = 0; r_u8(name + i) && r_u8(name + i) == r_u8(0x800D08C0u + 40u * file + i); i = (uint16)(i + 1u))
        {
        }
        if (!r_u8(name + i))
            return 1;
    }
    return 0;
}

uint32 sub_800CB130(void)
{
    return 15u - r_u32(0x800D0B4Cu);
}

uint32 sub_800CC234(uint32 index)
{
    uint32 i, result = 0;
    for (i = 0; i < (uint16)index; ++i)
        result += (uint32)((sint32)r_u32(0x800D08D8u + 40u * i) >> 13);
    return (uint16)result;
}

uint32 sub_800CC288(uint32 index)
{
    return (uint16)(r_u32(0x800D08D8u + 40u * (uint16)index) >> 13);
}

uint32 sub_800CBF64(uint32 file)
{
    uint32 i, source = r_u32(0x800D08B4u) + 64u * (uint16)file;
    for (i = 0; i < 32u; ++i)
        sub_800CBE20(i, source + 2u * i);
    return i < 32u;
}

uint32 sub_800CB8B8(void)
{
    return sub_800CAAA8() ? sub_8005C058(0x800D0B24u) == 1u : 0u;
}

uint32 sub_800CBB80(uint32 file)
{
    uint32 i = 0, source = 0x800D08C0u + 40u * (uint16)file;
    if (!sub_800CAAA8())
        return 0;
    sub_800CA338(r_u16(0x800D0B44u));
    while (r_u8(source + i))
    {
        w_u8(0x800D0B29u + i, r_u8(source + i));
        i = (uint16)(i + 1u);
    }
    w_u8(0x800D0B29u + i, 0);
    return sub_8005C078(0x800D0B24u) == 1u;
}

uint32 sub_800CC4A8(void)
{
    return sub_8004486C(1, 3, 1, 1024, 16000, 512);
}

uint32 sub_800CC7D4(uint32 mode)
{
    uint32 held, keys;
    sub_800CC740();
    w_u16(0x800D08A0u, r_u16(0x800717F4u));
    sub_8002F0F8();
    sub_8002F36C();
    sub_8005DFE4(0);
    sub_8005B278((uint16)mode);
    sub_8005E814(r_u32(0x800719D4u));
    sub_8005E648(r_u32(0x800719CCu));
    sub_8005E5D8(r_u32(0x8007184Cu) + 9996u);
    w_u16(0x800719D0u, r_u16(0x800719D0u) + 1u);
    w_u16(0x800715E8u, r_u16(0x800715E8u) ^ 1u);
    sub_80011BB8();
    held = r_u16(0x800D08B0u);
    keys = r_u16(0x80071790u);
    w_u16(0x80071790u, keys & ~held);
    w_u16(0x800D08B0u, keys & held);
    sub_80045048(0);
    return sub_80044A5C(1);
}

void sub_800CE21C(uint32 first, uint32 count)
{
    uint32 packet, x, y, shade, ordering;
    first = (uint16)first;
    count = (uint16)count;
    while (count--)
    {
        packet = r_u32(0x80071680u);
        w_u32(0x80071680u, packet + 40u);
        x = 48u * (first % 5u);
        y = 20u * (first / 5u);
        sub_80060D78(packet);
        w_u16(packet + 8u, x + 78u);
        w_u16(packet + 10u, y + 22u);
        w_u16(packet + 12u, x + 98u);
        w_u16(packet + 14u, y + 22u);
        w_u16(packet + 16u, x + 78u);
        w_u16(packet + 18u, y + 42u);
        w_u16(packet + 20u, x + 98u);
        w_u16(packet + 22u, y + 42u);
        shade = r_u16(0x800719D0u) & 127u;
        if (shade >= 64u)
            shade = 127u - shade;
        shade += 64u;
        w_u8(packet + 4u, shade);
        w_u8(packet + 5u, shade);
        w_u8(packet + 6u, shade);
        first = (uint16)(first + 1u);
        ordering = r_u32(0x8007184Cu);
        w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(ordering) & 0xFFFFFFu));
        w_u32(ordering, (r_u32(ordering) & 0xFF000000u) | (packet & 0xFFFFFFu));
    }
}

extern uint32 sub_800CA224(uint32 character, uint32 group);
extern uint32 sub_8005C088(uint32 character);

uint32 sub_800CABC8(uint32 text)
{
    uint32 padding = 0, i;
    for (i = 0; i < 32u; ++i)
    {
        if (!r_u8(text + 2u * i))
            padding = 1;
        if (padding)
            w_u16(text + 2u * i, 0x8140);
    }
    return 0;
}

uint32 sub_800CAC18(uint32 text)
{
    uint8 original[64];
    uint32 input = 0, output = 0, i, result;
    for (i = 0; i < 64u; ++i)
        original[i] = r_u8(text + i);
    for (i = 0; i < 32u; ++i)
        w_u16(text + 2u * i, 0x8140);
    do
    {
        uint32 character = original[input];
        result = character - 128u;
        if (!character)
            break;
        if ((uint8)(character - 128u) >= 32u && character < 224u)
        {
            uint32 glyph;
            ++input;
            glyph = sub_800CA224(character, input - 1u);
            w_u16(text + 2u * output, (glyph >> 8) | (glyph << 8));
        }
        else
        {
            /* TODO: A final unpaired lead byte reads beyond the 64-byte source in the original */
            uint32 second = input + 1u < 64u ? original[input + 1u] : draft_unknown_argument("sub_800CAC18 trailing byte", input + 1u);
            w_u16(text + 2u * output, character | (second << 8));
            input += 2u;
        }
        ++output;
        result = (uint16)input < 64u;
    } while ((uint16)input < 64u);
    return result;
}

uint32 sub_800CC068(uint32 index, uint32 color, uint32 page)
{
    uint32 destination = r_u32(0x800D0B18u + 4u * (uint16)page) + 512u * (uint16)index, i;
    for (i = 0; i < 256u; ++i)
        w_u16(destination + 2u * i, color);
    return i < 256u;
}

uint32 sub_800CC0AC(uint32 index, uint32 pixels, uint32 palette, uint32 page)
{
    uint32 destination = r_u32(0x800D0B18u + 4u * (uint16)page) + 512u * (uint16)index, i;
    for (i = 0; i < 128u; ++i)
    {
        uint32 value = r_u8(pixels + i);
        w_u16(destination + 4u * i, r_u16(palette + 2u * (value & 15u)));
        w_u16(destination + 4u * i + 2u, r_u16(palette + 2u * (value >> 4)));
    }
    return i / 8u < 16u;
}

uint32 sub_800CBE00(uint32 character)
{
    return sub_8005C088((uint16)character);
}
