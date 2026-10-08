#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8002A00C(uint32 position, uint32 yaw, uint32 mode, uint32 variant,
    uint32 source_collider, uint32 owner, uint32 flags, uint32 collider_flags)
{
    uint16 region[4];
    uint32 node, mesh, collider, i, result = 45u;
    region[0] = 0xFFFFu;
    node = sub_80032EF0();
    if (!node) return result;
    w_u32(node + 8u, 45u);
    mesh = sub_8001A3BC();
    for (i = 0; i < 4u; ++i) w_u32(mesh + 8u + i * 4u, r_u32(position + i * 4u));
    w_u32(node + 100u, sub_80046324(r_u32(position), r_u32(position + 8u), draft_local_address(region, sizeof(region))));
    w_u16(node + 70u, 500u); w_u32(node + 32u, 500u); w_u16(node + 68u, 1u);
    w_u16(node + 36u, 0); w_u16(node + 38u, 0); w_u16(node + 40u, 0);
    w_u32(mesh + 80u, node + 16u);
    sub_8001A494(mesh);
    collider = sub_800474F4();
    w_u32(node + 72u, collider);
    sub_80047534(collider, mesh, collider_flags & 0xFFu);
    if (source_collider) {
        w_u16(collider + 138u, r_u16(source_collider + 138u));
        w_u16(collider + 142u, r_u16(source_collider + 142u));
    } else w_u16(collider + 138u, 0xFFFFu);
    w_u32(collider + 124u, owner); w_u32(node + 12u, mesh);
    for (i = 0; i < 4u; ++i) w_u32(node + 76u + i * 4u, r_u32(position + i * 4u));
    w_u16(node + 94u, yaw); w_u16(node + 96u, 0); w_u16(node + 92u, 0);
    w_u16(node + 120u, 0xFFFFu);
    mode = (uint16)mode;
    result = 400u;
    if (mode == 0u) {
        w_u16(node + 104u, 400u); w_u16(node + 106u, 0);
        w_u16(node + 110u, 30u); w_u16(node + 118u, 0); result = 30u;
    } else if (mode == 1u || mode == 2u) {
        w_u16(node + 104u, 400u); w_u16(node + 110u, mode == 1u ? 120u : 60u);
        w_u16(node + 106u, 0); w_u16(node + 118u, 1u);
        w_u16(node + 120u, sub_8004496C());
        result = sub_8004486C(1u, r_u16(node + 120u), 29u, 500u, 16000u, 512u);
    }
    w_u16(node + 112u, mode); w_u16(node + 114u, variant);
    w_u16(node + 108u, flags); w_u16(node + 116u, 0);
    return result;
}
