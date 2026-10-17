#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_8001D684(uint32 mesh, uint32 blend, uint32 xscale, uint32 yscale, uint32 zscale, uint32 red, uint32 green, uint32 blue);

static void special_variant_position(uint32 mesh, uint32 player)
{
    uint32 x = r_u32(player), y = r_u32(player + 4);
    uint32 z = r_u32(player + 8), pad = r_u32(player + 12);
    w_u32(mesh + 8, x);
    w_u32(mesh + 12, y);
    w_u32(mesh + 16, z);
    w_u32(mesh + 20, pad);
}

uint32 sub_80056324(uint32 player)
{
    uint32 counter = r_u16(0x800718F8), scale = (counter << 8) + 1024;
    uint32 mesh, enabled = 0, green = 0;
    w_u16(0x800718AC, r_u16(0x800718AC) - 48);
    w_u32(0x800BF2B4, r_u32(0x800BF2B4) - 96);
    w_u32(0x800BF2B0, r_u32(0x800BF2B0) - 64);
    mesh = sub_8001A3BC();
    sub_8001A2FC(28, mesh);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 26, counter << 6);
    w_u16(mesh + 28, 0);
    special_variant_position(mesh, player);
    sub_8001D684(mesh, 1, scale, scale >> 1, scale, 64, 128, 64);
    sub_8001A2FC(29, mesh);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 26, counter << 5);
    w_u16(mesh + 28, 0);
    special_variant_position(mesh, player);
    sub_8001D684(mesh, 1, scale, scale >> 1, scale, 64, 128, 64);
    sub_8001A3F4(mesh);
    counter = r_u16(0x800718F8);
    if (!(counter & 2))
    {
        enabled = 1;
        if (!(r_u16(0x800719D0) & 1))
            green = (uint16)(counter + 155);
    }
    sub_80013B64(enabled, 0, green, 0);
    if (r_u16(0x800718F8) != 100)
        return 255;
    w_u16(0x8007156C, 255);
    w_u16(0x8007158C, 0);
    w_u16(0x8007155C, 0);
    w_u16(0x80071A50, 4);
    return 4;
}

uint32 sub_8005653C(uint32 player)
{
    uint32 counter, xscale, yscale, zscale, mesh, enabled = 0, color = 0;
    w_u32(0x800BF2B4, r_u32(0x800BF2B4) - 96);
    counter = r_u16(0x800718F8);
    w_u32(0x800BF2B0, r_u32(0x800BF2B0) - 64);
    if (counter < 50)
    {
        xscale = 4096;
        zscale = 4096;
        yscale = counter << 8;
    }
    else
    {
        xscale = (counter << 9) - 21504;
        yscale = 12800;
        zscale = 128;
    }
    counter = r_u16(0x800718F8);
    mesh = sub_8001A3BC();
    sub_8001A2FC(28, mesh);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    w_u16(mesh + 26, counter << 6);
    special_variant_position(mesh, player);
    sub_8001D684(mesh, 1, xscale, yscale, zscale, 128, 0, 0);
    sub_8001A2FC(29, mesh);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 26, counter << 5);
    w_u16(mesh + 28, 0);
    special_variant_position(mesh, player);
    sub_8001D684(mesh, 1, xscale, yscale, zscale, 128, 64, 0);
    sub_8001A2FC(30, mesh);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 26, counter << 7);
    w_u16(mesh + 28, 0);
    special_variant_position(mesh, player);
    sub_8001D684(mesh, 1, xscale, xscale, xscale, 128, 128, 0);
    sub_8001A3F4(mesh);
    counter = r_u16(0x800718F8);
    if (!(counter & 2))
    {
        enabled = 1;
        if (!(r_u16(0x800719D0) & 1))
            color = (uint16)(counter + 155);
    }
    sub_80013B64(enabled, color, color, 0);
    if (r_u16(0x800718F8) != 100)
        return 255;
    w_u16(0x8007158C, 255);
    w_u16(0x8007156C, 0);
    w_u16(0x8007155C, 0);
    w_u16(0x80071A50, 4);
    return 4;
}
