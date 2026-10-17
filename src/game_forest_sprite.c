#include "psx.h"
#include "game_draft_signatures.h"

static void forest_sprite_project(void)
{
    draft_gte_data(0, r_u32(0x1F800020));
    draft_gte_data(1, r_u32(0x1F800024));
    draft_gte_command(0x180001);
}

uint32 sub_80015B70(uint32 position, uint32 texture, uint32 scale, uint32 blend, uint32 shade)
{
    uint32 desc, packet, shift = scale & 31, depth, link;
    w_u32(0x1F800030, r_u32(position + 8) - r_u32(0x800BBFCC));
    w_u32(0x1F800028, r_u32(position) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(position + 4) - r_u32(0x800BBFC8));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    if (r_u32(0x1F800030) > 39999 || r_u32(0x1F800028) + 20000 > 40000 || r_u32(0x1F80002C) + 20000 > 40000)
        return 0;
    if ((sint32)r_u32(0x1F800030) < 32)
        w_u32(0x1F800030, 32);
    desc = 0x800C0564 + 16 * (uint16)texture;
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    draft_gte_control(5, r_u32(0x1F800028));
    draft_gte_control(6, r_u32(0x1F80002C));
    draft_gte_control(7, r_u32(0x1F800030));
    packet = r_u32(0x80071680);
    w_u16(0x1F800020, (0 - (uint32)(sint32)(sint16)r_u16(desc + 12)) << shift);
    w_u32(0x80071680, packet + 40);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, (0 - (uint32)(sint32)(sint16)r_u16(desc + 14)) << shift);
    forest_sprite_project();
    w_u8(packet + 3, 9);
    w_u8(packet + 7, (uint16)blend ? 46 : 44);
    w_u8(packet + 4, shade);
    w_u8(packet + 5, shade);
    w_u8(packet + 6, shade);
    w_u32(packet + 8, draft_gte_read(14));
    w_u16(0x1F800020, r_u16(0x1F800020) + ((uint32)(sint32)(sint16)r_u16(desc + 8) << shift));
    forest_sprite_project();
    w_u16(packet + 22, r_u16(desc));
    if ((uint16)blend)
        w_u16(packet + 22, r_u16(desc) | r_u16(0x8007177E + 2 * (uint16)blend));
    w_u32(packet + 16, draft_gte_read(14));
    w_u16(0x1F800022, r_u16(0x1F800022) + ((uint32)(sint32)(sint16)r_u16(desc + 10) << shift));
    forest_sprite_project();
    w_u16(packet + 14, r_u16(desc + 2));
    w_u32(packet + 32, draft_gte_read(14));
    w_u16(0x1F800020, r_u16(0x1F800020) - ((uint32)(sint32)(sint16)r_u16(desc + 8) << shift));
    forest_sprite_project();
    w_u8(packet + 12, r_u8(desc + 4));
    w_u8(packet + 13, r_u8(desc + 6));
    w_u8(packet + 20, r_u8(desc + 4) + r_u8(desc + 8) - 1);
    w_u8(packet + 21, r_u8(desc + 6));
    w_u8(packet + 28, r_u8(desc + 4));
    w_u8(packet + 29, r_u8(desc + 6) + r_u8(desc + 10) - 1);
    w_u8(packet + 36, r_u8(desc + 4) + r_u8(desc + 8) - 1);
    w_u8(packet + 37, r_u8(desc + 6) + r_u8(desc + 10) - 1);
    w_u32(packet + 24, draft_gte_read(14));
    depth = (uint32)((sint32)r_u32(0x1F800030) >> 4);
    if (depth - 1 < 2499)
    {
        link = r_u32(0x8007184C) + 4 * depth;
        w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(link) & 0xFFFFFF));
        w_u32(link, (r_u32(link) & 0xFF000000) | (packet & 0xFFFFFF));
    }
    return 1;
}

uint32 sub_80032934(uint32 position, uint32 size, uint32 region, uint32 output)
{
    uint16 local_region[4];
    uint32 seed, x, z, result;
    local_region[0] = (uint16)region;
    seed = draft_local_address(local_region, sizeof(local_region));
    w_u32(output, r_u32(position) - size);
    z = size + r_u32(position + 8);
    x = r_u32(output);
    w_u32(output + 8, z);
    w_u32(output + 4, sub_80046324(x, z, seed));
    x = r_u32(output);
    w_u32(output + 16, size + r_u32(position));
    z = r_u32(output + 8);
    w_u32(output + 24, size + r_u32(position + 8));
    w_u32(output + 20, sub_80046324(x, z, seed));
    x = r_u32(output);
    w_u32(output + 48, r_u32(position) - size);
    z = r_u32(output + 8);
    w_u32(output + 56, r_u32(position + 8) - size);
    w_u32(output + 52, sub_80046324(x, z, seed));
    x = r_u32(output);
    w_u32(output + 32, size + r_u32(position));
    z = r_u32(output + 8);
    w_u32(output + 40, r_u32(position + 8) - size);
    result = sub_80046324(x, z, seed);
    w_u32(output + 36, result);
    return result;
}

uint32 sub_800357B8(uint32 node)
{
    uint32 state = r_u16(node + 122), floor_height, counter, proximity[7], record;
    sint32 kind, shade;
    if (!state)
    {
        sub_80030E5C(node + 12, node + 28, 80, 0);
        floor_height = sub_80046324(r_u32(node + 12), r_u32(node + 20), node + 120);
        w_u32(node + 116, floor_height);
        sub_800325CC(node + 44, node + 12, floor_height, 0);
        sub_80032934(node + 12, 300, r_u16(node + 120), node + 52);
        w_u16(node + 128, (sint32)r_u32(node + 44) < 0 ? 223 : 224);
        if ((sint16)r_u16(node + 50))
        {
            w_u16(node + 122, 1);
            w_u16(node + 126, (sub_80011B8C() & 63) + 30);
            w_u16(node + 124, 0);
        }
    }
    else if (state == 1)
    {
        counter = r_u16(node + 124);
        w_u16(node + 128, counter < 30 ? 222 : ((counter >> 5) & 1) + 225);
        w_u16(node + 124, counter + 1);
        record = draft_local_address(proximity, sizeof(proximity));
        sub_80051F74(node + 12, record);
        if (r_u16(node + 124) >= r_u16(node + 126) || (sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 2000 || (sint16)r_u16(0x80071808))
        {
            w_u32(node + 44, (uint32)-1200);
            kind = r_u8(r_u32(0x80071704) + 14 * r_u16(node + 120) + 9) - 2;
            if (kind < 0)
                kind = 0;
            sub_8005135C((uint32)(sint32)(sint16)kind, sub_80011B8C() & 127, node + 28);
            w_u16(node + 122, 0);
        }
    }
    sub_80032A20(node + 52);
    sub_80046278(r_u16(node + 120));
    shade = ((sint16)r_u16(0x800BF8E0) + (sint16)r_u16(0x800BF8E8) + (sint16)r_u16(0x800BF8F0) + (sint16)r_u16(0x800BF8E2) + (sint16)r_u16(0x800BF8EA) + (sint16)r_u16(0x800BF8F2) + (sint16)r_u16(0x800BF8E4) + (sint16)r_u16(0x800BF8EC) + (sint16)r_u16(0x800BF8F4)) / 12;
    shade += ((sint16)r_u16(0x80071858) + (sint16)r_u16(0x8007185A) + (sint16)r_u16(0x8007185C)) / 3;
    if (shade < 0)
        shade = 0;
    if (shade > 255)
        shade = 255;
    sub_80015B70(node + 12, r_u16(node + 128), 4, 0, (uint16)shade);
    if ((uint16)legend_pickup_region_check(r_u16(node + 120), 15))
        return sub_80032FD0(node);
    return 0;
}

uint32 sub_80035AB4(uint32 node)
{
    uint32 state = r_u16(node + 122), floor_height, counter, proximity[7], record, rendered, depth, fallback, result;
    sint32 kind, shade;
    if (!state)
    {
        sub_80030E5C(node + 12, node + 28, 80, 0);
        floor_height = sub_80046324(r_u32(node + 12), r_u32(node + 20), node + 120);
        w_u32(node + 116, floor_height);
        sub_800325CC(node + 44, node + 12, floor_height, 0);
        sub_80032934(node + 12, 300, r_u16(node + 120), node + 52);
        w_u16(node + 128, r_s32(node + 44) < 0 ? 260 : 259);
        if (r_s16(node + 50))
        {
            w_u16(node + 122, 1);
            w_u16(node + 126, (sub_80011B8C() & 63) + 30);
            w_u16(node + 124, 0);
        }
    }
    else if (state == 1)
    {
        counter = r_u16(node + 124);
        w_u16(node + 128, 261);
        w_u16(node + 124, counter + 1);
        record = draft_local_address(proximity, sizeof(proximity));
        sub_80051F74(node + 12, record);
        if (r_u16(node + 124) >= r_u16(node + 126) || r_s32(record + 16 + 4 * r_u16(record + 24)) < 2000 || r_s16(0x80071808))
        {
            w_u32(node + 44, (uint32)-1200);
            kind = r_u8(r_u32(0x80071704) + 14 * r_u16(node + 120) + 9) - 2;
            if (kind < 0)
                kind = 0;
            sub_8005135C((uint32)(sint32)(sint16)kind, sub_80011B8C() & 127, node + 28);
            w_u16(node + 122, 0);
        }
    }
    sub_80032A20(node + 52);
    sub_80046278(r_u16(node + 120));
    shade = (r_s16(0x800BF8E0) + r_s16(0x800BF8E8) + r_s16(0x800BF8F0) + r_s16(0x800BF8E2) + r_s16(0x800BF8EA) + r_s16(0x800BF8F2) + r_s16(0x800BF8E4) + r_s16(0x800BF8EC) + r_s16(0x800BF8F4)) / 12;
    shade += (r_s16(0x80071858) + r_s16(0x8007185A) + r_s16(0x8007185C)) / 3;
    if (shade < 0)
        shade = 0;
    if (shade > 255)
        shade = 255;
    rendered = sub_80015B70(node + 12, r_u16(node + 128), 4, 0, (uint16)shade);
    depth = (uint32)(r_s32(0x1F800030) >> 4);
    /* Sprite linking clears the cleanup fallback's low half */
    fallback = rendered && depth - 1 < 2499 ? 0 : 40;
    result = (uint16)sub_80032D9C(r_u16(node + 120), 15, fallback);
    if (result)
        return sub_80032FD0(node);
    return result;
}

uint32 sub_80038760(uint32 node)
{
    uint32 state = r_u16(node + 124), counter, texture, height, proximity[7], record, rendered, depth, fallback, result;
    sint32 kind, offset, shade;
    if (!state)
    {
        if (sub_80030E5C(node + 12, node + 28, 80, 64))
        {
            w_u16(node + 126, r_u16(node + 126) + 1);
            texture = 230 - ((r_u16(node + 126) >> 1) & 3);
        }
        else
        {
            w_u16(node + 126, 0);
            w_u16(node + 128, (sub_80011B8C() & 63) + 30);
            w_u16(node + 124, 1);
            texture = 231;
        }
        w_u16(node + 130, texture);
        height = sub_80046324(r_u32(node + 12), r_u32(node + 20), node + 120);
        w_u32(node + 116, height);
        sub_800325CC(node + 44, node + 12, height, 0);
        sub_80032934(node + 12, 300, r_u16(node + 120), node + 52);
    }
    else if (state == 1)
    {
        if (r_u16(node + 126) < 16)
        {
            w_u16(node + 130, 231);
            w_u16(node + 126, r_u16(node + 126) + 1);
        }
        if (r_u16(node + 126) == 16)
        {
            w_u16(node + 128, r_u16(node + 128) - 1);
            w_u16(node + 130, ((r_u16(node + 128) >> 2) & 1) + 232);
            record = draft_local_address(proximity, sizeof(proximity));
            sub_80051F74(node + 12, record);
            if (!r_u16(node + 128) || (sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 2000 || (sint16)r_u16(0x80071808))
                w_u16(node + 126, 17);
        }
        if (r_u16(node + 126) >= 17)
        {
            counter = r_u16(node + 126);
            w_u16(node + 130, 231);
            w_u16(node + 126, counter + 1);
            if (r_u16(node + 126) == 32)
            {
                kind = r_u8(r_u32(0x80071704) + 14 * r_u16(node + 120) + 9) - 2;
                if (kind < 0)
                    kind = 0;
                offset = (sint16)(r_u16(node + 122) - 16 + (sub_80011B8C() & 31));
                if (offset < 0)
                    offset = 0;
                if (offset >= 128)
                    offset = 127;
                w_u16(node + 122, offset);
                sub_8005135C((uint32)(sint32)(sint16)kind, (uint32)offset, node + 28);
                w_u16(node + 124, 0);
            }
        }
    }
    sub_80032A20(node + 52);
    sub_80046278(r_u16(node + 120));
    shade = ((sint16)r_u16(0x800BF8E0) + (sint16)r_u16(0x800BF8E8) + (sint16)r_u16(0x800BF8F0) + (sint16)r_u16(0x800BF8E2) + (sint16)r_u16(0x800BF8EA) + (sint16)r_u16(0x800BF8F2) + (sint16)r_u16(0x800BF8E4) + (sint16)r_u16(0x800BF8EC) + (sint16)r_u16(0x800BF8F4)) / 12;
    shade += ((sint16)r_u16(0x80071858) + (sint16)r_u16(0x8007185A) + (sint16)r_u16(0x8007185C)) / 3;
    if (shade < 0)
        shade = 0;
    if (shade > 255)
        shade = 255;
    rendered = sub_80015B70(node + 12, r_u16(node + 130), 5, 0, (uint16)shade);
    depth = (uint32)((sint32)r_u32(0x1F800030) >> 4);
    /* Sprite linking clears the cleanup fallback's low half */
    fallback = rendered && depth - 1 < 2499 ? 0 : 40;
    result = (uint16)sub_80032D9C(r_u16(node + 120), 15, fallback);
    if (result)
        return sub_80032FD0(node);
    return result;
}
