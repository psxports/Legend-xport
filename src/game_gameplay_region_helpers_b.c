#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_800467A0(uint32 position)
{
    uint32 transformed[4];
    uint32 region, descriptor, heading, axis;
    do
    {
        region = r_u16(position + 10u);
        descriptor = r_u32(0x80071704u) + 14u * region;
        heading = r_u16(r_u32(0x800716D0u) + 2u * r_u8(descriptor + 9u));
        w_u16(0x1F800020u, 0);
        w_u16(0x1F800022u, (heading + 2048u) & 4095u);
        w_u16(0x1F800024u, 0);
        sub_8005D138(0x1F800020u, 0x1F800000u);
        for (axis = 0; axis < 5u; ++axis)
            draft_gte_control(axis, r_u32(0x1F800000u + 4u * axis));
        w_u16(0x1F800020u, 0);
        w_u16(0x1F800022u, 0);
        w_u16(0x1F800024u, 32);
        sub_8005CDA8(0x1F800020u, draft_local_address(transformed, sizeof(transformed)));
        w_u32(position, r_u32(position) + transformed[0]);
        w_u32(position + 4u, r_u32(position + 4u) + transformed[2]);
        sub_80046324(r_u32(position), r_u32(position + 4u), position + 10u);
        descriptor = r_u32(0x80071704u) + 14u * r_u16(position + 10u);
    } while ((sint32)r_u8(descriptor + 9u) >= (sint16)r_u16(0x800717A0u));
    return 1u;
}
