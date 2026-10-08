#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8002A560(uint32 position, uint32 yaw, uint32 source, uint32 owner)
{
    uint32 node = sub_80032EF0(), first, second, words[4], axis;
    if (!node) return 47u;
    w_u32(node + 8u, 47u);
    first = sub_8001A3BC();
    second = sub_8001A3BC();
    sub_8001A2FC(28u, first);
    sub_8001A2FC(29u, second);
    for (axis = 0u; axis < 4u; ++axis) words[axis] = r_u32(position + 4u * axis);
    for (axis = 0u; axis < 4u; ++axis) w_u32(first + 8u + 4u * axis, words[axis]);
    for (axis = 0u; axis < 4u; ++axis) words[axis] = r_u32(position + 4u * axis);
    for (axis = 0u; axis < 4u; ++axis) w_u32(second + 8u + 4u * axis, words[axis]);
    w_u32(node + 12u, first);
    w_u32(node + 16u, second);
    w_u16(node + 20u, 0u);
    w_u32(node + 24u, 0u);
    w_u32(node + 32u, source);
    w_u32(node + 36u, owner);
    w_u16(node + 28u, yaw);
    return words[0];
}

uint32 sub_8002A658(uint32 position, uint32 yaw, uint32 flags, uint32 source, uint32 owner)
{
    uint32 node = sub_80032EF0(), channel, axis;
    if (!node) return 0u;
    w_u32(node + 8u, 48u);
    w_u32(node + 12u, position);
    w_u16(node + 56u, 1u);
    w_u16(node + 58u, yaw);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, yaw);
    w_u16(0x1F800024u, 0u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x1F800024u, 6000u);
    sub_8005CDD8(0x1F800000u, 0x1F800020u, node + 32u);
    for (axis = 0u; axis < 2u; ++axis)
        w_u32(node + 32u + 4u * axis, r_u32(node + 32u + 4u * axis) + r_u32(position + 4u * axis));
    w_u32(node + 48u, source);
    w_u32(node + 52u, owner);
    w_u16(node + 62u, flags);
    w_u16(node + 60u, 0u);
    w_u32(node + 40u, r_u32(node + 40u) + r_u32(position + 8u));
    channel = sub_8004496C();
    w_u16(node + 66u, channel);
    return sub_8004486C(1u, r_u16(node + 66u), 57u, 800u, 32000u, 512u);
}
