#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_800CCCAC(uint32 x, uint32 y, uint32 shade);
extern void sub_800CC6A8(uint32 text, uint32 y, uint32 red, uint32 green, uint32 blue, uint32 flags);
extern void sub_800CEEE0(uint32 x, uint32 y, uint32 text);
extern void sub_800CF048(uint32 x, uint32 y, uint32 text);

uint32 sub_800CC9D4(uint32 shade)
{
    sint32 color = (sint16)shade;
    sint32 left = -(sint16)r_u16(0x800D089Cu);
    sint32 y = (sint16)r_u16(0x800D08A0u);
    sint32 right;
    sub_800180D4(left, y, 128u, 6u, color, color, color);
    sub_800180D4(left, y + 128, 128u, 7u, color, color, color);
    w_u16(0x800D08A8u, 0u - r_u16(0x800D089Cu));
    right = (sint16)(r_u16(0x800D089Cu) + 192u);
    w_u16(0x800D08ACu, r_u16(0x800D089Cu) + 177u);
    sub_800180D4(right - 15, y, 128u, 8u, color, color, color);
    return sub_800180D4(right - 28, y + 128, 128u, 9u, color, color, color);
}

uint32 sub_800CCAE0(uint32 descriptors, uint32 count)
{
    uint32 i = 0u;
    count = (uint16)count;
    while ((uint16)i < count)
    {
        uint32 item = descriptors + 6u * (uint16)i;
        sint32 x = r_u16(0x800D08A8u) + r_u16(item);
        sint32 y = r_u16(item + 4u) + r_u16(0x800D08A0u);
        sint32 end = (sint16)(r_u16(0x800D08ACu) + r_u16(item + 2u));
        while ((sint16)x < end)
        {
            sub_80017FB0((sint16)x, (sint16)y, 127u, 12u);
            sub_80018214((sint16)x, (sint16)y, 126u, 11u, 128u, 128u, 128u, 2u);
            y = y - 8 + (sub_80011B8C() & 15u);
            x += 32;
        }
        ++i;
    }
    return (uint16)i;
}

uint32 sub_800CCC54(void)
{
    return sub_80017FB0(192u, 24u, 125u, 10u);
}

uint32 sub_800CCC80(void)
{
    return sub_80017FB0(192u, 38u, 125u, 5u);
}

void sub_800CCD48(uint32 strings, uint32 y, uint32 values, uint32 red, uint32 green, uint32 blue)
{
    sint32 index = values ? (sint16)r_u16(values) : 0;
    sub_800CC6A8(r_u32(strings + (uint32)(4 * index)), (sint16)y, (uint16)red, (uint16)green, (uint16)blue, 0u);
}

void sub_800CE1A8(uint32 y, uint32 text, uint32 shade)
{
    shade = (uint16)shade;
    sub_800CC6A8(text, (sint16)y, shade, shade, shade, 0u);
}

void sub_800CF1A8(uint32 x_argument, uint32 y_argument, uint32 index)
{
    sint32 x = (sint16)x_argument, y = (sint16)y_argument;
    uint32 item = 0x800AF6F0u + 12u * (uint16)index;
    sint32 shade;
    uint8 time_parts[8];
    uint32 parts = draft_local_address(time_parts, sizeof(time_parts));
    uint32 text, value, divisor, position, started = 0u;
    if ((uint16)(y_argument + 96u) >= 353u)
        return;
    shade = (sint16)(256u - y_argument);
    if (shade < 0)
        shade = 0;
    if (shade > 256)
        shade = 256;
    sub_800CCCAC(x, y, (uint16)(shade >> 1));
    sub_80017FB0(x + 142, y + 62, 120u, 4u * r_u8(item) + 186u);
    sub_80018214(x + 144, y + 64, 120u, 4u * r_u8(item) + 186u, 32u, 32u, 32u, 1u);
    sub_800CEEE0((sint16)(x_argument + 166u), (sint16)(y_argument + 39u), item + 2u);
    sub_8001496C(r_u8(item + 1u), parts, parts + 1u);
    text = r_u32(0x800D0868u);
    w_u8(text + 2u, time_parts[0] + 48u);
    w_u8(text + 4u, time_parts[1] + 48u);
    sub_800CEEE0((sint16)(x_argument + 214u), (sint16)(y_argument + 39u), text);
    value = r_u32(item + 8u);
    divisor = 100000u;
    for (position = 0u; position < 6u; ++position)
    {
        uint32 digit = value / divisor;
        if (digit)
            started = 1u;
        text = r_u32(0x800D086Cu);
        w_u8(text + position, started || position == 5u ? digit + 48u : 32u);
        value %= divisor;
        divisor /= 10u;
    }
    sub_800CF048((sint16)(x_argument + 262u), (sint16)(y_argument + 37u), r_u32(0x800D086Cu));
}

uint32 sub_800CC4E4(uint32 text)
{
    uint32 width = 0u, character;
    while ((character = r_u8(text++)) != 0u)
    {
        width += 8u;
        if (character - 101u < 4u)
            width += 8u;
    }
    return (uint32)(sint16)width;
}

void sub_800CC520(uint32 x, uint32 y, uint32 text, uint32 red, uint32 green, uint32 blue, uint32 flags)
{
    uint32 character, glyph, advance;
    while ((character = r_u8(text++)) != 0u)
    {
        glyph = 0xFFFFu;
        advance = 8u;
        if (character - 65u < 26u)
            glyph = character - 52u;
        switch (character)
        {
            case '.':
                glyph = 49u;
                break;
            case ',':
                glyph = 50u;
                break;
            case '!':
                glyph = 51u;
                break;
            case '?':
                glyph = 53u;
                break;
            case '-':
                glyph = 52u;
                break;
        }
        if (character - 48u < 10u)
            glyph = character - 9u;
        if (character - 97u < 4u)
            glyph = character - 43u;
        if (character - 101u < 4u)
        {
            glyph = character - 43u;
            advance = 16u;
        }
        if (glyph != 0xFFFFu)
            sub_80018214((sint16)x, (sint16)y + (sint16)r_u16(0x800D08A0u), 16u, glyph, (sint16)red, (sint16)green, (sint16)blue, (uint16)flags);
        x += advance;
    }
}

void sub_800CC6A8(uint32 text, uint32 y, uint32 red, uint32 green, uint32 blue, uint32 flags)
{
    sint32 width = (sint16)sub_800CC4E4(text);
    sub_800CC520((uint32)(192 - (width >> 1)), (sint16)y, text, (uint16)red, (uint16)green, (uint16)blue, (uint16)flags);
}

static void overlay_text(uint32 x, uint32 y, uint32 text, uint32 large)
{
    uint32 character, glyph;
    while ((character = r_u8(text++)) != 0u)
    {
        glyph = 0xFFFFu;
        if (character - 65u < 26u)
            glyph = character + (large ? 75u : 6u);
        if (!large && character - 97u < 26u)
            glyph = character + 7u;
        if (!large)
        {
            switch (character)
            {
                case '#':
                    glyph = 97u;
                    break;
                case '.':
                    glyph = 98u;
                    break;
                case ':':
                    glyph = 99u;
                    break;
                case ',':
                    glyph = 100u;
                    break;
                case '!':
                    glyph = 101u;
                    break;
                case '?':
                    glyph = 102u;
                    break;
                case '-':
                    glyph = 103u;
                    break;
            }
            if (character - 48u < 10u)
                glyph = character + 82u;
        }
        else
        {
            switch (character)
            {
                case '#':
                    glyph = 166u;
                    break;
                case '.':
                    glyph = 167u;
                    break;
                case ':':
                    glyph = 168u;
                    break;
                case ',':
                    glyph = 167u;
                    break;
                case '!':
                    glyph = 183u;
                    break;
                case '?':
                    glyph = 184u;
                    break;
                case '-':
                    glyph = 182u;
                    break;
            }
            if (character - 48u < 10u)
                glyph = character + 122u;
        }
        if (glyph != 0xFFFFu)
        {
            sub_80017FB0((sint16)x, (sint16)y, 1u, glyph);
            sub_80018214((sint16)x + 2, (sint16)y + 2, 1u, glyph, 32u, 32u, 32u, 1u);
        }
        x += large ? 16u : 8u;
    }
}

void sub_800CEEE0(uint32 x, uint32 y, uint32 text)
{
    overlay_text(x, y, text, 0u);
}

void sub_800CF048(uint32 x, uint32 y, uint32 text)
{
    overlay_text(x, y, text, 1u);
}
