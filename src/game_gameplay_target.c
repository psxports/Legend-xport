#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80032F70(void)
{
    uint32 item = r_u32(0x80071670u), next, head;
    if (!item)
        return 0u;
    next = r_u32(item + 4u);
    head = r_u32(0x80071868u);
    w_u32(item, 0u);
    w_u32(0x80071670u, next);
    w_u32(item + 4u, head);
    if (head)
        w_u32(head, item);
    w_u32(0x80071868u, item);
    w_u16(0x800718F0u, r_u16(0x800718F0u) + 1u);
    return item;
}

uint32 sub_8001A3BC(void)
{
    uint32 mesh = sub_80011A98(168u);
    sub_8001A348(mesh);
    return mesh;
}

void sub_8001A320(uint32 mesh, uint32 kind)
{
    w_u16(mesh + 86u, kind);
}

uint32 sub_8001A494(uint32 mesh)
{
    uint32 kind = r_u16(mesh + 86u);
    if (kind == 1u)
        return sub_8005D3C8(mesh + 24u, mesh + 32u);
    if (kind >= 2u)
    {
        if (kind == 2u)
            return sub_8005D658(mesh + 24u, mesh + 32u);
        return 2u;
    }
    return sub_8005D138(mesh + 24u, mesh + 32u);
}

uint32 sub_80046570(uint32 x, uint32 z)
{
    uint32 magnitude = (sint32)x < 0 ? 0u - x : x;
    if ((sint32)magnitude >= 12001)
        x = 12000u;
    magnitude = (sint32)z < 0 ? 0u - z : z;
    if ((sint32)magnitude >= 12001)
        z = 12000u;
    if ((sint32)x < 12000 || (sint32)z < 12000)
        return sub_8005CBB8(x * x + z * z);
    return 24000u;
}

uint32 sub_80051F74(uint32 position, uint32 record)
{
    uint32 words[4], i;
    for (i = 0; i < 4u; ++i)
        words[i] = r_u32(position + 4u * i);
    for (i = 0; i < 4u; ++i)
        w_u32(record + 4u * i, words[i]);
    w_u32(record + 20u, 1000000u);
    w_u32(record + 16u, 1000000u);
    w_u16(record + 24u, 0u);
    for (i = 0; i < 2u; ++i)
    {
        uint32 player = 0x800AFEC0u + 288u * i;
        if (r_u8(player + 240u))
        {
            uint32 distance = sub_80046570(r_u32(position) - r_u32(player), r_u32(position + 8u) - r_u32(player + 8u));
            w_u32(record + 16u + 4u * i, distance);
        }
    }
    if ((sint32)r_u32(record + 20u) < (sint32)r_u32(record + 16u))
        w_u16(record + 24u, 1u);
    return 1u;
}
