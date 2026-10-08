#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* FILE.DAT entry 154, loaded at 800C9E50 */
static uint32 stage0_sound_init(void)
{
    uint32 result = (uint32)(sint32)(sint16)r_u16(0x80071734u);
    if (result)
    {
        sub_80044734();
        sub_800447B0(66u, 80u);
        w_u8(0x80071998u, 66u);
        w_u8(0x80071990u, 67u);
        w_u8(0x800717D4u, 68u);
        w_u8(0x80071890u, 69u);
        sub_8004477C(66u, 0u);
        sub_8004477C(r_u8(0x80071990u), 0u);
        sub_8004477C(r_u8(0x800717D4u), 0u);
        result = sub_80044528(155u, 66u, 4u);
        w_u16(0x80071734u, 0u);
    }
    return result;
}

/* Original main-image helper 80048448 */
static uint32 stage0_fill_bytes(uint32 first, uint32 last, uint32 value)
{
    last &= 0xffffu;
    while ((first & 0xffffu) <= last)
    {
        w_u8(r_u32(0x80071A1Cu) + (first & 0xffffu), value);
        ++first;
    }
    return 1u;
}

uint32 legend_stage0_begin(void)
{
    sub_80014848();
    stage0_sound_init();
    sub_8004944C();
    sub_80049504();
    sub_8002B2A0(702u);
    sub_800129E8();
    sub_8002B358(702u);
    sub_8004591C(703u, 0u, 0u);
    sub_8002292C(704u);
    sub_8004B930(0u);
    w_u32(0x800BBFC4u, r_u32(0x800BBFC4u) + 16000u);
    w_u32(0x800BBFCCu, r_u32(0x800BBFCCu) - 8000u);
    w_u32(0x800BBFC8u, r_u32(0x800BBFC8u) - 8000u);
    w_u32(0x800BC040u, r_u32(0x800BBFC4u));
    w_u32(0x800BC044u, r_u32(0x800BBFC8u));
    w_u32(0x800BC048u, r_u32(0x800BBFCCu));
    w_u32(0x800BC04Cu, r_u32(0x800BBFD0u));
    sub_80030678();
    w_u16(0x80071774u, 0u);
    w_u16(0x80071778u, 0u);
    w_u32(0x8007165Cu, 0x800CA434u);
    w_u16(0x800717A0u, r_u16(0x80071728u) - 1u);
    sub_800235D8(39u, 56u);
    sub_80027094(0u, 1038u, r_u8(0x800717D4u), 1400u, 23000u);
    sub_80027114(35u, 80u, r_u8(0x80071890u), 950u, 13000u, 120u);
    return stage0_fill_bytes(0u, 255u, 128u);
}
