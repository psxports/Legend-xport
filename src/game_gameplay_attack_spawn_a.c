#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80028F48(uint32 model, uint32 x, uint32 y, uint32 z, uint32 yaw, uint32 speed, uint32 lifetime, uint32 source_collider, uint32 owner, uint32 param1, uint32 param2, uint32 collider_flags, uint32 source_mesh, uint32 param3, uint32 flags)
{
    uint32 node = sub_80032EF0(), mesh, record, collider, result, i, column;
    if (!node)
        return 0u;
    w_u32(node + 8u, 31u);
    mesh = sub_8001A3BC();
    sub_8001A2FC((uint16)model, mesh);
    record = node + 12u;
    w_u16(node + 126u, flags);
    if (flags & 1u)
    {
        w_u16(0x1F800020u, 1024u);
        w_u16(0x1F800022u, 0u);
        w_u16(0x1F800024u, 0u);
        sub_8005D138(0x1F800020u, 0x1F800000u);
        for (i = 0; i < 5u; ++i)
            draft_gte_control(i, r_u32(source_mesh + 32u + 4u * i));
        for (column = 0; column < 3u; ++column)
        {
            draft_gte_data(9u, r_u16(0x1F800000u + 2u * column));
            draft_gte_data(10u, r_u16(0x1F800006u + 2u * column));
            draft_gte_data(11u, r_u16(0x1F80000Cu + 2u * column));
            draft_gte_command(0x49E012u);
            w_u16(mesh + 32u + 2u * column, draft_gte_read(9u));
            w_u16(mesh + 38u + 2u * column, draft_gte_read(10u));
            w_u16(mesh + 44u + 2u * column, draft_gte_read(11u));
        }
    }
    else
    {
        for (i = 0; i < 32u; i += 16u)
        {
            uint32 a = r_u32(source_mesh + 32u + i), b = r_u32(source_mesh + 36u + i);
            uint32 c = r_u32(source_mesh + 40u + i), d = r_u32(source_mesh + 44u + i);
            w_u32(mesh + 32u + i, a);
            w_u32(mesh + 36u + i, b);
            w_u32(mesh + 40u + i, c);
            w_u32(mesh + 44u + i, d);
        }
    }
    sub_8001A320(mesh, 3u);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, speed);
    w_u16(0x1F800024u, 0u);
    sub_8005CDD8(mesh + 32u, 0x1F800020u, node + 108u);
    if (flags & 8u)
    {
        w_u32(node + 108u, (uint32)((sint32)r_u32(node + 108u) / 3));
        w_u32(node + 116u, (uint32)((sint32)r_u32(node + 116u) / 3));
    }
    w_u16(0x1F800020u, x);
    w_u16(0x1F800022u, y);
    w_u16(0x1F800024u, z);
    sub_8005CDD8(mesh + 32u, 0x1F800020u, mesh + 8u);
    w_u32(mesh + 8u, r_u32(mesh + 8u) + r_u32(source_mesh + 8u));
    w_u32(mesh + 12u, r_u32(mesh + 12u) + r_u32(source_mesh + 12u));
    w_u32(mesh + 16u, r_u32(mesh + 16u) + r_u32(source_mesh + 16u));
    if (flags & 2u)
    {
        w_u32(0x1F800028u, 0u);
        w_u32(0x1F80002Cu, 0u);
        w_u32(0x1F800030u, 0u);
        sub_80022CC0(mesh + 8u, 0x1F800028u, 3u, 6u);
        sub_800271A4(mesh + 8u, 1u, ((uint16)yaw + 2048u) & 4095u, 0xFFFFFFu);
    }
    collider = sub_800474F4();
    w_u32(record + 4u, collider);
    sub_80047534(collider, mesh, (uint8)collider_flags);
    if (source_collider)
    {
        w_u16(collider + 138u, r_u16(source_collider + 138u));
        w_u16(collider + 142u, r_u16(source_collider + 142u));
    }
    else
        w_u16(collider + 138u, 0xFFFFu);
    w_u32(collider + 124u, owner);
    w_u16(record + 92u, yaw);
    w_u32(record + 8u, 0u);
    w_u16(record + 12u, lifetime);
    w_u16(record + 14u, 0u);
    w_u16(record + 84u, 0xFFFFu);
    result = sub_80046324(r_u32(mesh + 8u), r_u32(mesh + 16u), record + 84u);
    w_u32(record + 80u, result);
    w_u16(record + 86u, 0u);
    w_u32(record, mesh);
    w_u16(record + 88u, param1);
    w_u16(record + 90u, param2);
    w_u16(record + 112u, param3);
    return result;
}

static uint32 attack_sound(uint32 sound, uint32 pitch, uint32 volume)
{
    uint32 channel = (uint16)sub_800448F4();
    uint32 scaled = (uint16)sub_80044F58(volume);
    return sub_8004486C(1u, channel, sound, pitch, scaled, r_u16(0x80071A20u));
}

uint32 sub_8003FA6C(void)
{
    attack_sound(50u, 1000u, 32000u);
    return attack_sound(21u, 1000u, 32000u);
}

uint32 sub_8003FB00(void)
{
    return attack_sound(56u, 1000u, 32000u);
}

uint32 sub_8003FB58(void)
{
    attack_sound(24u, 800u, 32000u);
    attack_sound(24u, 900u, 32000u);
    return attack_sound(26u, 2200u, 5000u);
}
