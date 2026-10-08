#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80050250(void)
{
    uint32 i, result;
    if (r_u16(0x800717AC) >= 2) {
        for (i = 0; i < 7; ++i) {
            uint32 item = r_u8(0x800715D5 + i);
            uint32 timer = r_u8(0x80071A15 + i);
            w_u8(0x800715D4 + i, item);
            w_u8(0x80071A14 + i, timer);
            w_u16(0x800AFEA0 + 2 * i, r_u16(0x800AFEA2 + 2 * i));
        }
    }
    result = r_u16(0x800717AC) - 1;
    w_u16(0x800717AC, result);
    return result;
}

uint32 sub_800502F4(uint32 item)
{
    uint32 count, i, result;
    sint32 last;
    while (r_u16(0x800717AC) >= 8) sub_80050250();
    count = r_u16(0x800717AC);
    if (count) {
        last = (sint16)r_u16(0x800AFE9E + 2 * count);
        if (last >= 195) {
            uint32 delta = (uint32)(last - 194);
            for (i = 0; i < count; ++i)
                w_u16(0x800AFEA0 + 2 * i, r_u16(0x800AFEA0 + 2 * i) - delta);
        }
    }
    w_u8(0x800715D4 + r_u16(0x800717AC), item);
    w_u8(0x80071A14 + r_u16(0x800717AC), 96);
    count = r_u16(0x800717AC);
    result = 2 * count;
    w_u16(0x800717AC, count + 1);
    w_u16(0x800AFEA0 + result, 210);
    return result;
}

static uint32 pickup_heading(uint32 node)
{
    uint32 direction = r_u8(r_u32(0x80071704) + 14 * r_u16(node + 92) + 9);
    return (r_u16(r_u32(0x800716D0) + 2 * direction) - 512
        + r_u16(0x80068700 + 2 * r_u16(node + 114))) & 4095;
}

static void pickup_wrap_angles(uint32 mesh)
{
    w_u16(mesh + 24, r_u16(mesh + 24) & 4095);
    w_u16(mesh + 28, r_u16(mesh + 28) & 4095);
    w_u16(mesh + 26, r_u16(mesh + 26) & 4095);
}

uint32 sub_8003405C(uint32 node)
{
    uint32 mesh = r_u32(node + 12), proximity[7], record, kind, result;
    uint16 angles[4];
    uint32 angles_address, effect_position[4], i;
    record = draft_local_address(proximity, sizeof(proximity));
    angles_address = draft_local_address(angles, sizeof(angles));
    sub_80051F74(mesh + 8, record);
    if (!r_u16(node + 94)) {
        sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_8001A2FC(r_u16(0x80068660 + 4 * r_u16(node + 114)), mesh);
        kind = r_u16(node + 114);
        switch (kind) {
        case 0:
            w_u16(mesh + 26, r_u16(mesh + 26) + 200);
            w_u16(mesh + 24, r_u16(mesh + 24) + 100);
            break;
        case 1: case 7: case 8:
            w_u16(mesh + 26, r_u16(mesh + 26) + 400); break;
        case 2: case 3: case 4: case 5: case 6: case 14: case 16: case 18: case 19: case 20:
            w_u16(mesh + 26, r_u16(mesh + 26) + 200); break;
        case 11: case 12: case 13: case 15: case 17:
            w_u16(mesh + 28, r_u16(mesh + 28) + 400);
            w_u16(mesh + 26, pickup_heading(node)); break;
        default: w_u16(mesh + 26, pickup_heading(node)); break;
        }
        pickup_wrap_angles(mesh);
        result = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 92);
        w_u32(node + 88, result);
        sub_800325CC(node + 16, mesh + 8, result, 1);
        sub_80030E5C(mesh + 8, node + 96, 8, 0);
        if (r_u16(node + 92) != 0xFFFF
            && sub_80046A28(r_u32(0x80071704) + 14 * r_u16(node + 92), r_u16(node + 92), mesh + 8)) {
            w_u32(node + 96, r_u32(mesh + 8));
            w_u32(node + 104, r_u32(mesh + 16));
        }
        angles[1] = (uint16)pickup_heading(node);
        sub_8005178C(mesh + 8, (uint32)(sint32)(sint16)r_u16(0x800686D4 + 2 * r_u16(node + 114)),
            angles_address, r_u16(node + 92), node + 24);
        if ((sint16)r_u16(node + 22)) {
            w_u16(mesh + 26, angles[1]);
            w_u16(mesh + 24, angles[0]);
            w_u16(mesh + 28, angles[2]);
            sub_8001A2FC(r_u16(0x80068662 + 4 * r_u16(node + 114)), mesh);
            w_u16(node + 94, 1);
            if (!r_u16(node + 116)) goto destroy;
        }
    } else if (r_u16(node + 94) == 1) {
        kind = r_u16(node + 114);
        if (kind >= 11 && kind < 19) w_u16(0x800715C8, 0);
        else if (kind == 20) w_u16(mesh + 26, r_u16(mesh + 26) + 200);
        pickup_wrap_angles(mesh);
        if ((uint16)sub_800324A0(mesh + 8, record, 1600, 2)) {
            if ((r_u16(0x800719D0) & 31) < 16) {
                for (i = 0; i < 4; ++i) effect_position[i] = r_u32(mesh + 8 + 4 * i);
                effect_position[1] += 32 * (r_u16(0x800719D0) & 31) - 1774;
                sub_80017C8C(draft_local_address(effect_position, sizeof(effect_position)), 192, 0, 40000, 128);
            }
            if ((uint16)sub_80033E98(node + 12, record, 1600)) {
                uint32 channel, volume;
                sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
                sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
                channel = (uint16)sub_800448F4();
                volume = (uint16)sub_80044F58(16000);
                sub_8004486C(1, channel, 22, 3000, volume, r_u16(0x80071A20));
                goto destroy;
            }
        }
        if (r_u16(node + 114) != 20) w_u16(node + 112, r_u16(node + 112) - 1);
        if (!r_u16(node + 112)) goto destroy;
    }
    if ((sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 3000)
        sub_80021288(r_u32(mesh + 8), r_u32(mesh + 16), r_u32(node + 88), r_u32(node + 88), 0);
    if ((sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 6000) sub_8004E520(mesh + 8, 2);
    if (r_u16(node + 112) >= 51 || (r_u16(node + 112) & 1)) {
        sub_80032A20(node + 24);
        if (r_u16(node + 112) & 31) {
            sub_80046278(r_u16(node + 92));
            sub_8001DEB0(mesh);
        } else sub_8001A7A8(mesh, 196, 196, 196);
    }
    result = (uint16)legend_pickup_region_check(r_u16(node + 92), 15);
    if (!result) return result;
    mesh = r_u32(node + 12);
destroy:
    sub_8001A3F4(mesh);
    return sub_80032FD0(node);
}

uint32 sub_8001A3F4(uint32 mesh)
{
    return sub_80011AF8(mesh);
}
