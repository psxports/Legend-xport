#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_8005CDD8(uint32 matrix, uint32 input, uint32 output);
extern uint32 sub_8001A3BC(void);

uint32 sub_8002A7AC(uint32 position, uint32 yaw, uint32 flags, uint32 source, uint32 owner, uint32 type)
{
    uint32 item = sub_80032EF0(), i;
    if (!item)
        return 0u;
    w_u32(item + 8u, type & 0xFFFFu);
    w_u32(item + 12u, position);
    w_u16(item + 56u, 1u);
    w_u16(item + 58u, yaw);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, yaw);
    w_u16(0x1F800024u, 0u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x1F800024u, 6000u);
    sub_8005CDD8(0x1F800000u, 0x1F800020u, item + 32u);
    for (i = 0u; i < 2u; ++i)
        w_u32(item + 32u + 4u * i, r_u32(item + 32u + 4u * i) + r_u32(position + 4u * i));
    w_u32(item + 48u, source);
    w_u32(item + 52u, owner);
    w_u16(item + 62u, flags);
    w_u16(item + 60u, 0u);
    w_u32(item + 40u, r_u32(item + 40u) + r_u32(position + 8u));
    w_u16(item + 66u, sub_8004496C());
    return sub_8004486C(1u, r_u16(item + 66u), 57u, 800u, 32000u, 512u);
}

uint32 sub_8002ACAC(uint32 position, uint32 yaw, uint32 flags, uint32 source, uint32 owner, uint32 actor)
{
    uint32 item = sub_80032EF0();
    if (!item)
        return 56u;
    w_u32(item + 8u, 56u);
    w_u32(item + 12u, position);
    w_u16(item + 44u, 1u);
    w_u16(item + 46u, yaw);
    w_u32(item + 16u, source);
    w_u32(item + 20u, owner);
    w_u16(item + 50u, flags);
    w_u16(item + 48u, 0u);
    w_u32(item + 40u, actor);
    w_u16(item + 52u, sub_8004496C());
    return sub_8004486C(1u, r_u16(item + 52u), 57u, 600u, 32000u, 512u);
}

uint32 sub_8002AD78(uint32 mesh, uint32 owner)
{
    uint32 position[4], position_address, item, first, second, third, collider, result;
    uint16 tile[4];
    tile[0] = 0xFFFFu;
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800024u, 0u);
    w_u16(0x1F800022u, r_u16(mesh + 26u) + (sub_80011B8C() & 2047u) - 1024u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x1F800024u, (sub_80011B8C() & 1023u) + 3500u);
    position_address = draft_local_address(position, sizeof(position));
    sub_8005CDD8(0x1F800000u, 0x1F800020u, position_address);
    position[0] += r_u32(mesh + 8u);
    position[1] += r_u32(mesh + 12u);
    position[2] += r_u32(mesh + 16u);
    position[1] -= 7000u + (sub_80011B8C() & 63u) * 64u;
    sub_80046324(position[0], position[2], draft_local_address(tile, sizeof(tile)));
    if (tile[0] == 0xFFFFu)
        return 0xFFFFu;
    item = sub_80032EF0();
    if (!item)
        return 57u;
    w_u32(item + 8u, 57u);
    first = sub_8001A3BC();
    second = sub_8001A3BC();
    third = sub_8001A3BC();
    sub_8001A320(first, 1u);
    sub_8001A2FC(31u, second);
    sub_8001A2FC(32u, third);
    sub_8001A2BC(second, third, 0u, (uint32)-650, 350u);
    sub_8001A2BC(first, second, 0u, 0u, 0u);
    collider = sub_800474F4();
    w_u32(item + 24u, collider);
    sub_80047534(collider, second, 1u);
    w_u16(collider + 138u, 0xFFFFu);
    w_u32(collider + 124u, owner);
    w_u32(item + 28u, 0u);
    w_u16(item + 32u, 150u);
    w_u16(item + 34u, 0u);
    w_u16(first + 24u, 0u);
    w_u16(first + 28u, 0u);
    w_u16(first + 26u, sub_80011B8C() & 4095u);
    w_u32(first + 8u, position[0]);
    w_u32(first + 12u, position[1]);
    w_u32(first + 16u, position[2]);
    /* TODO: Original local VECTOR padding is uninitialized; leave destination padding intact */
    w_u32(item + 12u, first);
    w_u32(item + 16u, second);
    w_u32(item + 20u, third);
    w_u16(item + 112u, tile[0]);
    w_u16(item + 118u, sub_8004496C());
    result = 0u - (sub_80011B8C() & 511u);
    w_u16(third + 24u, result);
    return result;
}
