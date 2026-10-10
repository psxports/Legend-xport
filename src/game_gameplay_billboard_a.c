#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static uint32 billboard_project(void)
{
    draft_gte_data(0u, r_u32(0x1F800020u));
    draft_gte_data(1u, r_u32(0x1F800024u));
    draft_gte_command(0x180001u);
    return draft_gte_read(14u);
}

uint32 sub_800173DC(uint32 position, uint32 texture, uint32 scale_shift, uint32 blend, uint32 shade, uint32 flip)
{
    uint32 metadata, packet, x, width, height, depth, ot;
    uint32 shift = scale_shift & 31u;
    w_u32(0x1F800030u, r_u32(position + 8u) - r_u32(0x800BBFCCu));
    w_u32(0x1F800028u, r_u32(position) - r_u32(0x800BBFC4u));
    w_u32(0x1F80002Cu, r_u32(position + 4u) - r_u32(0x800BBFC8u));
    sub_8005CC48(0x800BBFDCu, 0x1F800028u, 0x1F800028u);
    depth = r_u32(0x1F800030u);
    if (depth > 39999u || r_u32(0x1F800028u) + 20000u > 40000u || r_u32(0x1F80002Cu) + 20000u > 40000u)
        return 0u;
    if ((sint32)depth < 32)
        w_u32(0x1F800030u, 32u);
    metadata = 0x800C0564u + 16u * (uint16)texture;
    draft_gte_control(1u, 0u);
    draft_gte_control(3u, 0u);
    draft_gte_control(0u, 4096u);
    draft_gte_control(2u, 4096u);
    draft_gte_control(4u, 4096u);
    draft_gte_control(5u, r_u32(0x1F800028u));
    draft_gte_control(6u, r_u32(0x1F80002Cu));
    draft_gte_control(7u, r_u32(0x1F800030u));
    packet = r_u32(0x80071680u);
    w_u32(0x80071680u, packet + 40u);
    x = (uint32)(sint32)(sint16)r_u16(metadata + 12u);
    if (!(uint16)flip)
        x = 0u - x;
    w_u16(0x1F800020u, x << shift);
    w_u16(0x1F800024u, 0u);
    w_u16(0x1F800022u, (0u - (uint32)(sint32)(sint16)r_u16(metadata + 14u)) << shift);
    x = billboard_project();
    w_u8(packet + 3u, 9u);
    w_u8(packet + 7u, (uint16)blend ? 46u : 44u);
    w_u8(packet + 4u, shade);
    w_u8(packet + 5u, shade);
    w_u8(packet + 6u, shade);
    w_u32(packet + 8u, x);
    width = (uint32)(sint32)(sint16)r_u16(metadata + 8u) << shift;
    x = r_u16(0x1F800020u);
    w_u16(0x1F800020u, (uint16)flip ? x - width : x + width);
    x = billboard_project();
    w_u16(packet + 22u, r_u16(metadata));
    if ((uint16)blend)
        w_u16(packet + 22u, r_u16(metadata) | r_u16(0x8007177Eu + 2u * (uint16)blend));
    w_u32(packet + 16u, x);
    height = (uint32)(sint32)(sint16)r_u16(metadata + 10u) << shift;
    w_u16(0x1F800022u, r_u16(0x1F800022u) + height);
    x = billboard_project();
    w_u16(packet + 14u, r_u16(metadata + 2u));
    w_u32(packet + 32u, x);
    width = (uint32)(sint32)(sint16)r_u16(metadata + 8u) << shift;
    x = r_u16(0x1F800020u);
    w_u16(0x1F800020u, (uint16)flip ? x + width : x - width);
    x = billboard_project();
    w_u8(packet + 12u, r_u8(metadata + 4u));
    w_u8(packet + 13u, r_u8(metadata + 6u));
    w_u8(packet + 20u, r_u8(metadata + 4u) + r_u8(metadata + 8u) - 1u);
    w_u8(packet + 21u, r_u8(metadata + 6u));
    w_u8(packet + 28u, r_u8(metadata + 4u));
    w_u8(packet + 29u, r_u8(metadata + 6u) + r_u8(metadata + 10u) - 1u);
    w_u8(packet + 36u, r_u8(metadata + 4u) + r_u8(metadata + 8u) - 1u);
    w_u8(packet + 37u, r_u8(metadata + 6u) + r_u8(metadata + 10u) - 1u);
    w_u32(packet + 24u, x);
    depth = (uint32)((sint32)r_u32(0x1F800030u) >> 4);
    if (depth - 16u < 2484u)
    {
        ot = r_u32(0x8007184Cu) + 4u * depth;
        w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(ot) & 0xFFFFFFu));
        w_u32(ot, (r_u32(ot) & 0xFF000000u) | (packet & 0xFFFFFFu));
    }
    return 1u;
}
