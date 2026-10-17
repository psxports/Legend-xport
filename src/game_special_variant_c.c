#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_8001D684(uint32 mesh, uint32 blend, uint32 xscale, uint32 yscale, uint32 zscale, uint32 red, uint32 green, uint32 blue);

uint32 sub_800567C4(uint32 player)
{
    uint32 random, tick, scale, narrow_scale, mesh, x, y, z, pad;
    uint32 pass, shift, green, blue, enabled, shade;
    w_u32(0x800BF2B4, r_u32(0x800BF2B4) - 48);
    x = r_u32(0x800BF2B0);
    tick = r_u16(0x800718AC);
    w_u32(0x800BF2B0, x - 96);
    w_u16(0x800718AC, tick + 48);
    random = sub_80011B8C();
    tick = r_u16(0x800718F8);
    scale = (tick + (random & 15)) << 8;
    narrow_scale = scale / 3;
    mesh = sub_8001A3BC();
    for (pass = 0; pass < 3; ++pass)
    {
        sub_8001A2FC(28 + pass, mesh);
        shift = pass == 0 ? 6 : pass == 1 ? 5 : 7;
        w_u16(mesh + 24, 0);
        w_u16(mesh + 26, tick << shift);
        w_u16(mesh + 28, 0);
        x = r_u32(player);
        y = r_u32(player + 4);
        z = r_u32(player + 8);
        pad = r_u32(player + 12);
        w_u32(mesh + 8, x);
        w_u32(mesh + 12, y);
        w_u32(mesh + 16, z);
        w_u32(mesh + 20, pad);
        green = pass == 1 ? 64 : 128;
        blue = pass == 0 ? 255 : 128;
        sub_8001D684(mesh, 1, scale, pass == 2 ? scale : narrow_scale, scale, 0, green, blue);
    }
    sub_8001A3F4(mesh);
    tick = r_u16(0x800718F8);
    enabled = 0;
    shade = 0;
    if (!(tick & 2))
    {
        enabled = 1;
        if (!(r_u16(0x800719D0) & 1))
            shade = (tick + 155) & 0xFFFF;
    }
    sub_80013B64(enabled, shade, shade, shade);
    if (r_u16(0x800718F8) == 100)
    {
        w_u16(0x8007156C, 255);
        w_u16(0x8007155C, 255);
        w_u16(0x8007158C, 0);
        w_u16(0x80071A50, 4);
        return 4;
    }
    return 255;
}
