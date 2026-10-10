#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern void sub_800CC6A8(uint32 text, uint32 y, uint32 red, uint32 green, uint32 blue, uint32 blend);
extern void sub_800CC520(uint32 x, uint32 y, uint32 text, uint32 red, uint32 green, uint32 blue, uint32 blend);
extern uint32 sub_800CC46C(void);
extern void sub_800CC740(void);
extern uint32 sub_800CC2B4(void);
extern uint32 sub_800CBFC4(void);
extern uint32 sub_8005DFE4(uint32 mode);
extern uint32 sub_8005B278(uint32 mode);
extern uint32 sub_8005E814(uint32 environment);
extern uint32 sub_8005E648(uint32 environment);
extern uint32 sub_8005E5D8(uint32 ordering_table);

uint32 sub_800CCCAC(uint32 x, uint32 y, uint32 shade)
{
    uint32 color = (uint32)(sint32)(sint16)shade;
    sub_800180D4((uint32)(sint32)(sint16)x, (uint32)((sint16)y + (sint16)r_u16(0x800D08A0u)), 126, 0, color, color, color);
    return sub_800180D4((uint32)((sint16)x + 160), (uint32)((sint16)y + (sint16)r_u16(0x800D08A0u) + 33), 126, 1, color, color, color);
}

void sub_800CD160(uint32 index)
{
    if ((r_u16(0x800719D0u) & 63u) >= 9u)
        sub_800CC6A8(r_u32(0x800D0724u + (index & 65535u) * 4u), 216, 128, 128, 128, 0);
}

uint32 sub_800CCDA8(uint32 selection, uint32 count)
{
    uint32 result;
    sint32 value;
    if (r_u16(0x80071790u) & 0x8000u)
    {
        sub_800CC46C();
        w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x8000u);
        value = (sint16)r_u16(selection);
        w_u16(selection, (uint16)(value ? value - 1 : (sint32)count - 1));
    }
    result = r_u16(0x80071790u) & 0x2000u;
    if (result)
    {
        sub_800CC46C();
        w_u16(0x800D08B0u, r_u16(0x800D08B0u) | 0x2000u);
        value = (sint16)r_u16(selection);
        result = (uint32)(value + 1);
        w_u16(selection, (uint16)(value < (sint32)(count & 65535u) - 1 ? result : 0));
    }
    return result;
}

uint32 sub_800CCE94(uint32 address)
{
    uint32 changed = 0;
    if (!(r_u16(0x800719D0u) & 1u))
    {
        if (r_u16(0x80071790u) & 0x8000u)
        {
            changed = 1;
            if (r_u32(address))
                w_u32(address, r_u32(address) - 1u);
        }
        if (r_u16(0x80071790u) & 0x2000u)
        {
            changed = 1;
            if ((sint32)r_u32(address) < 128)
                w_u32(address, r_u32(address) + 1u);
        }
    }
    return changed ? sub_80044FB0() : 0;
}

void sub_800CE1E0(uint32 x, uint32 y, uint32 text, uint32 shade)
{
    shade &= 65535u;
    sub_800CC520((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)y, text, shade, shade, shade, 0);
}

uint32 sub_800CC46C(void)
{
    return sub_8004486C(1, 2, 0, 1024, 16000, 512);
}

void sub_800CC740(void)
{
    sint32 velocity = (sint16)r_u16(0x80071808u);
    sint32 position;
    if (!velocity)
        return;
    position = (sint16)(r_u16(0x800717F4u) + velocity);
    w_u16(0x800717F4u, (uint16)position);
    if (velocity > 0)
    {
        if (position >= velocity)
            w_u16(0x80071808u, (uint16)(1 - velocity));
    }
    else if (position <= velocity)
        w_u16(0x80071808u, (uint16)~velocity);
    if (!r_u16(0x80071808u))
        w_u16(0x800717F4u, 0);
}

uint32 sub_800CC2B4(void)
{
    uint32 tile = 0, group = 0, phase = r_u16(0x800719D0u) >> 4;
    sint32 x = 48, y = 24;
    do
    {
        uint32 repetitions = (sint32)(group & 65535u) < (sint32)r_u32(0x800D0B48u) ? r_u32(0x800D08D8u + (group & 65535u) * 40u) >> 13 : 1u;
        uint32 remaining = repetitions;
        while (remaining & 65535u)
        {
            PSX_RECT rect;
            uint32 animation = 0, kind = r_u8(0x800D0B54u + (group & 65535u));
            if (kind == 18u)
                animation = phase & 1u;
            if (kind == 19u)
                animation = (phase & 255u) % 3u;
            rect.x = (sint16)(x + 32);
            rect.y = (sint16)(y + (r_u16(0x800715E8u) ? 251 : 0));
            rect.w = 16;
            rect.h = 16;
            LoadImagePSX(&rect, (uint32 *)psx_addr(r_u32(0x800D0B18u + animation * 4u) + ((group & 65535u) << 9), 512u));
            sub_8005DFE4(0);
            ++tile;
            x += 48;
            if ((uint16)x == 288u)
            {
                x = 48;
                y += 20;
            }
            remaining += 65535u;
        }
        ++group;
    } while ((tile & 65535u) < 15u);
    return 0;
}

uint32 sub_800CBFC4(void)
{
    uint32 i, source = r_u32(0x800D0B40u);
    for (i = 0; i < 32u; ++i)
    {
        PSX_RECT rect;
        rect.x = (sint16)(16u * (i & 15u) + 56u);
        rect.y = (sint16)((i & 0xFFF0u) + (r_u16(0x800715E8u) ? 339u : 88u));
        rect.w = 16;
        rect.h = 16;
        LoadImagePSX(&rect, (uint32 *)psx_addr(source, 512u));
        sub_8005DFE4(0);
        source += 512u;
    }
    return 0;
}

uint32 sub_800CF7D4(uint32 index, uint32 texture_offset)
{
    uint32 phase = r_u16(0x800719D0u) & 63u;
    uint32 shade = 64u + 2u * (phase < 32u ? phase : 64u - phase);
    return sub_800180D4((uint32)(sint32)(sint16)(96u * (index & 65535u) + 96u), (uint32)((sint16)r_u16(0x800D08A0u) + 190), 2497, (texture_offset & 65535u) + 204u, shade, shade, shade);
}

uint32 sub_800CC8C8(uint32 update)
{
    uint16 buttons, consumed;
    sub_800CC740();
    w_u16(0x800D08A0u, r_u16(0x800717F4u));
    sub_8002F0F8();
    sub_8002F36C();
    if (update & 65535u)
    {
        sub_800CC2B4();
        sub_800CBFC4();
    }
    sub_8005DFE4(0);
    sub_8005B278(0);
    sub_8005E814(r_u32(0x800719D4u));
    sub_8005E648(r_u32(0x800719CCu));
    sub_8005E5D8(r_u32(0x8007184Cu) + 9996u);
    w_u16(0x800719D0u, r_u16(0x800719D0u) + 1u);
    w_u16(0x800715E8u, r_u16(0x800715E8u) ^ 1u);
    sub_80011BB8();
    buttons = r_u16(0x80071790u);
    consumed = r_u16(0x800D08B0u);
    w_u16(0x80071790u, buttons & ~consumed);
    w_u16(0x800D08B0u, buttons & consumed);
    sub_80045048(0);
    return sub_80044A5C(1);
}

static uint32 overlay_bar_allocate(uint32 words, uint32 command)
{
    uint32 packet = r_u32(0x80071680u);
    w_u32(0x80071680u, packet + 40u);
    w_u8(packet + 3u, (uint8)words);
    w_u8(packet + 7u, (uint8)command);
    return packet;
}

static uint32 overlay_bar_link(uint32 packet, uint32 offset)
{
    uint32 slot = r_u32(0x8007184Cu) + offset;
    uint32 result = (r_u32(slot) & 0xFF000000u) | (packet & 0xFFFFFFu);
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(slot) & 0xFFFFFFu));
    w_u32(slot, result);
    return result;
}

static void overlay_bar_coordinates(uint32 packet, sint32 left, sint32 top, sint32 right, sint32 bottom, uint32 gouraud)
{
    uint32 stride = gouraud ? 8u : 4u;
    w_u16(packet + 8u, (uint16)left);
    w_u16(packet + 10u, (uint16)top);
    w_u16(packet + 8u + stride, (uint16)right);
    w_u16(packet + 10u + stride, (uint16)top);
    w_u16(packet + 8u + 2u * stride, (uint16)left);
    w_u16(packet + 10u + 2u * stride, (uint16)bottom);
    w_u16(packet + 8u + 3u * stride, (uint16)right);
    w_u16(packet + 10u + 3u * stride, (uint16)bottom);
}

uint32 sub_800CCF38(uint32 y, uint32 value)
{
    uint32 packet, result;
    sint32 product = (sint16)((uint32)(sint32)(sint16)value * 126u);
    sint32 width = product / 128;
    packet = overlay_bar_allocate(5, 40);
    w_u8(packet + 4, 0);
    w_u8(packet + 5, 0);
    w_u8(packet + 6, 0);
    overlay_bar_coordinates(packet, 127, (sint32)y, 257, (sint32)(y + 10u), 0);
    overlay_bar_link(packet, 480);
    packet = overlay_bar_allocate(5, 40);
    w_u8(packet + 4, 160);
    w_u8(packet + 5, 32);
    w_u8(packet + 6, 0);
    overlay_bar_coordinates(packet, 128, (sint32)(y + 1u), 256, (sint32)(y + 9u), 0);
    overlay_bar_link(packet, 476);
    result = (uint32)(product < 0 ? product + 127 : product);
    if (width)
    {
        uint32 i;
        packet = overlay_bar_allocate(8, 56);
        for (i = 0; i < 4u; ++i)
        {
            uint32 color = packet + 4u + i * 8u;
            w_u8(color, (uint8)((i & 1u) ? 255 : 0));
            w_u8(color + 1u, 255);
            w_u8(color + 2u, 0);
        }
        overlay_bar_coordinates(packet, 129, (sint32)(y + 2u), width + 129, (sint32)(y + 8u), 1);
        result = overlay_bar_link(packet, 472);
    }
    return result;
}
