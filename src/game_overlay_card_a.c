#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include "game_native_adapters.h"
#include <string.h>
extern uint32 sub_800CA338(uint32);
extern uint32 sub_800CAC18(uint32);
extern uint32 sub_800CABC8(uint32);
extern uint32 sub_800CC0AC(uint32, uint32, uint32, uint32);
extern uint32 sub_800CC068(uint32, uint32, uint32);
extern uint32 sub_800CBE00(uint32);
extern uint32 sub_8005C018(uint32, uint32);
extern uint32 sub_8005C028(uint32, uint32, uint32);
extern uint32 sub_8005C038(uint32, uint32, uint32);
extern uint32 sub_8005C048(uint32);
extern uint32 sub_8005E2F0(uint32, uint32);
extern uint32 sub_8005DFE4(uint32);

uint32 sub_800CA638(uint32 source, uint32 destination, uint32 size)
{
    uint32 result = size, i;
    for (i = 0; i < size; ++i)
    {
        result = r_u8(source + i);
        w_u8(destination + i, (uint8)result);
    }
    return result;
}

uint32 sub_800CB144(uint32 destination, uint32 source, uint32 size)
{
    uint32 result = size, i, offset;
    for (i = 0; i < size; ++i)
    {
        offset = r_u16(0x800D0B50u);
        w_u16(0x800D0B50u, offset + 1);
        result = r_u8(source + i);
        w_u8(destination + offset, (uint8)result);
    }
    return result;
}

uint32 sub_800CB1D4(uint32 index, uint32 *x, uint32 *y, uint16 *clut_x, uint16 *clut_y, uint32 *u, uint32 *v)
{
    uint32 item = 0x800C0564u + 16u * (uint16)index, i, count, result;
    sub_80011DC0(r_u16(item + 2), draft_local_address(clut_x, 2), draft_local_address(clut_y, 2));
    count = r_u16(0x80071720u);
    result = count;
    for (i = 0; i < count; ++i)
    {
        if (r_u16(0x800AEE74u + 2 * i) == r_u16(item))
        {
            sub_80012780(r_u8(0x800C04F4u + i), x, y);
            *u = r_u16(item + 4);
            *v = r_u16(item + 6);
            return *v;
        }
        result = (uint16)(i + 1) < r_u16(0x80071720u);
    }
    return result;
}

uint32 sub_800CB2D8(uint32 x, uint32 y, uint32 u, uint32 v, uint32 destination)
{
    sint16 rect[4] = {(sint16)x, (sint16)y, 64, 256};
    uint32 pixels = sub_80011A98(0x8000u), row, column;
    uint32 offset = ((v + 1u) << 7) + (uint32)((sint32)u >> 1);
    sub_8005E2F0(draft_local_address(rect, sizeof(rect)), pixels);
    sub_8005DFE4(0);
    for (row = 0; row < 16; ++row, offset += 128)
        for (column = 0; column < 8; ++column)
            w_u8(destination++, (uint8)((r_u8(pixels + offset + column) >> 4) | (r_u8(pixels + offset + column + 1) << 4)));
    return sub_80011AF8(pixels);
}

uint32 sub_800CC138(uint32 index, uint32 page)
{
    index = (uint16)index;
    page = (uint16)page;
    if (r_u8(0x800D0B54u + index) && (sint32)index < (sint32)r_u32(0x800D0B48u))
        return sub_800CC0AC(index, r_u32(0x800D08B8u) + 384 * index + (uint16)(page << 7), r_u32(0x800D08BCu) + 32 * index, page);
    return sub_800CC068(index, 0x1084u, page);
}

uint32 sub_800CBE20(uint32 index, uint32 source)
{
    uint32 out = r_u32(0x800D0B40u) + ((uint16)index << 9), i, j, bits;
    uint32 glyph = sub_800CBE00(((uint32)r_u8(source) << 8) | r_u8(source + 1));
    if (glyph == 0xFFFFFFFFu)
    {
        for (i = 0; i < 256; ++i)
            w_u16(out + 2 * i, 0);
        return 0;
    }
    for (i = 0; i < 15; ++i)
    {
        bits = r_u16(glyph + 2 * i);
        for (j = 0; j < 8; ++j, out += 2)
            w_u16(out, (bits >> (7 - j)) & 1 ? 0xFFFF : 0);
        for (j = 0; j < 8; ++j, out += 2)
            w_u16(out, (bits >> (15 - j)) & 1 ? 0xFFFF : 0);
    }
    for (i = 0; i < 16; ++i)
        w_u16(out + 2 * i, 0);
    return 0;
}

uint32 sub_800CAD5C(uint32 index)
{
    uint32 data = sub_80011A98(8192), i, attempt, name, base, fd;
    index = (uint16)index;
    sub_800CA338(r_u16(0x800D0B44u));
    name = 0x800D08C0u + 40 * index;
    i = 0;
    while (r_u8(name + (uint16)i))
    {
        w_u8(0x800D0B29u + (uint16)i, r_u8(name + (uint16)i));
        ++i;
    }
    w_u8(0x800D0B29u + (uint16)i, 0);
    for (attempt = 0; attempt < 7; ++attempt)
    {
        fd = sub_8005C018(0x800D0B24u, 1);
        if (fd == 0xFFFFFFFFu)
        {
            sub_8005C048(fd);
            continue;
        }
        if (sub_8005C028(fd, data, 512) != 512)
        {
            sub_8005C048(fd);
            continue;
        }
        if (sub_8005C048(fd) == 0xFFFFFFFFu || r_u8(data) != 83 || r_u8(data + 1) != 67)
            continue;
        w_u8(0x800D0B54u + index, r_u8(data + 2));
        sub_800CA638(data + 96, r_u32(0x800D08BCu) + 32 * index, 32);
        for (i = 0; i < 3; ++i)
            sub_800CA638(data + 128 + 128 * i, r_u32(0x800D08B8u) + 384 * index + 128 * i, 128);
        base = r_u32(0x800D08B4u) + 64 * index;
        sub_800CA638(data + 4, base, 64);
        sub_800CAC18(base);
        sub_800CABC8(base);
        return sub_80011AF8(data);
    }
    w_u8(0x800D0B54u + index, 0);
    return sub_80011AF8(data);
}

uint32 sub_800CB3D0(uint32 existing)
{
    uint32 palette = sub_80011A98(32), icons[3], x, y, u, v, i, j, data, payload, sum = 0, fd, name;
    uint16 clut_x, clut_y;
    sint16 rect[4];
    uint8 header[512];
    uint32 header_address = draft_local_address(header, sizeof(header));
    static const uint32 state_addresses[] = {0x800719C8u, 0x80071A30u, 0x800716E0u, 0x800719BCu, 0x800717ECu, 0x8007179Cu, 0x80071590u, 0x800AF6F0u};
    static const uint32 state_sizes[] = {2, 2, 2, 2, 4, 4, 4, 120};
    for (i = 0; i < 3; ++i)
        icons[i] = sub_80011A98(128);
    for (i = 0; i < 3; ++i)
    {
        sub_800CB1D4(0x44 + i, &x, &y, &clut_x, &clut_y, &u, &v);
        sub_800CB2D8(x, y, u, v, icons[i]);
    }
    rect[0] = (sint16)clut_x;
    rect[1] = (sint16)clut_y;
    rect[2] = 16;
    rect[3] = 1;
    sub_8005E2F0(draft_local_address(rect, sizeof(rect)), palette);
    sub_8005DFE4(0);
    payload = sub_80011A98(2048);
    data = sub_80011A98(8192);
    for (i = 0; i < 8192; ++i)
        w_u8(data + i, 0);
    for (i = 0; i < 2048; ++i)
        w_u8(payload + i, 0);
    w_u16(0x800D0B50u, 0);
    for (i = 0; i < 8; ++i)
        sub_800CB144(payload, state_addresses[i], state_sizes[i]);
    memset(header, 0, sizeof(header));
    header[0] = 83;
    header[1] = 67;
    header[2] = 17;
    header[3] = 1;
    /* The title occupies the fixed global array itself */
    sub_800CA638(0x800D06C4u, header_address + 4, 64);
    sub_800CA638(palette, header_address + 96, 32);
    for (i = 0; i < 3; ++i)
        sub_800CA638(icons[i], header_address + 128 + 128 * i, 128);
    for (i = 0; i < 2048; ++i)
        sum += r_u8(payload + i);
    sub_800CA638(header_address, data, 512);
    for (i = 0; i < 4; ++i)
        w_u8(data + 512 + i, (uint8)(sum >> (8 * i)));
    sub_800CA638(payload, data + 516, 2048);
    sub_80011AF8(palette);
    for (i = 0; i < 3; ++i)
        sub_80011AF8(icons[i]);
    sub_80011AF8(payload);
    sub_800CA338(r_u16(0x800D0B44u));
    i = 0;
    name = r_u32(0x800D06C0u);
    while (r_u8(name + (uint16)i))
    {
        w_u8(0x800D0B29u + (uint16)i, r_u8(name + (uint16)i));
        ++i;
        name = r_u32(0x800D06C0u);
    }
    w_u8(0x800D0B29u + (uint16)i, 0);
    for (j = 0; j < 7; ++j)
    {
        if (!(uint16)existing)
        {
            fd = sub_8005C018(0x800D0B24u, 66048);
            if ((sint32)fd < 0)
                continue;
            sub_8005C048(fd);
        }
        fd = sub_8005C018(0x800D0B24u, 2);
        if ((sint32)fd < 0)
            continue;
        if (sub_8005C038(fd, data, 8192) != 8192)
            continue;
        if (sub_8005C048(fd) != fd)
            continue;
        sub_80011AF8(data);
        return 1;
    }
    sub_80011AF8(data);
    return 0;
}

uint32 sub_800CA224(uint32 character, uint32 group)
{
    uint32 marker = 0;
    character = (uint8)character;
    if ((uint8)(character - 32) < 16)
        marker = 1;
    else if ((uint8)(character - 48) < 10)
        group = 0;
    else if ((uint8)(character - 58) < 7)
        marker = 11;
    else if ((uint8)(character - 65) < 26)
        group = 1;
    else if ((uint8)(character - 91) < 6)
        marker = 37;
    else if ((uint8)(character - 97) < 26)
        group = 2;
    else if ((uint8)(character - 123) < 4)
        marker = 63;
    else
        return 0x8140u;
    if (marker)
        return r_u16(0x800D067Cu + 2 * (character - marker - 31));
    return r_u16(0x800D0670u + 4 * (uint8)group) + character - r_u16(0x800D0672u + 4 * (uint8)group);
}
