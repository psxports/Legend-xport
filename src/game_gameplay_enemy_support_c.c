#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8002837C(uint32 position, uint32 image, uint32 angle, uint32 renderer, uint32 speed, uint32 lifetime)
{
    uint32 item = sub_80032EF0(), mesh, words[4], i;
    if (!item) return 22;
    w_u32(item + 8, 22);
    mesh = sub_8001A3BC();
    sub_8001A2FC((uint16)image, mesh);
    sub_8001A320(mesh, 1);
    w_u16(item + 20, 100);
    w_u16(item + 22, 0);
    w_u32(item + 16, (uint32)(-2000 - (sint32)(sub_80011B8C() & 1023)));
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    w_u16(mesh + 26, 0);
    for (i = 0; i < 4; ++i) words[i] = r_u32(position + 4 * i);
    for (i = 0; i < 4; ++i) w_u32(mesh + 8 + 4 * i, words[i]);
    w_u16(item + 28, 0xFFFF);
    w_u32(item + 12, mesh);
    w_u16(item + 30, angle);
    w_u16(item + 32, renderer);
    w_u16(item + 34, speed);
    w_u16(item + 36, lifetime);
    return 0xFFFF;
}

uint32 sub_800326FC(void)
{
    uint32 i;
    for (i = 0; i < 3; ++i) {
        uint32 channel = (uint16)sub_800448F4();
        uint32 pitch = (uint16)((sub_80011B8C() & 255) + 2500);
        uint32 volume = (uint16)sub_80044F58(16000);
        sub_8004486C(1, channel, 23, pitch, volume, r_u16(0x80071A20));
    }
    return i < 3;
}

uint32 sub_800233BC(uint32 position, uint32 target, uint32 model, uint32 count)
{
    uint32 item = sub_80032F70(), mesh, words[4], i;
    if (!item) return 6;
    w_u32(item + 8, 6);
    mesh = sub_8001A3BC();
    w_u32(item + 12, mesh);
    sub_8001A320(mesh, 1);
    w_u16(item + 112, 1000);
    w_u16(item + 92, 0xFFFF);
    w_u32(item + 16, (uint32)-2000);
    w_u16(item + 94, 0);
    w_u16(item + 114, model);
    w_u16(item + 20, 100);
    w_u16(item + 22, 0);
    for (i = 0; i < 4; ++i) words[i] = r_u32(position + 4 * i);
    for (i = 0; i < 4; ++i) w_u32(mesh + 8 + 4 * i, words[i]);
    w_u16(mesh + 24, 0);
    w_u16(mesh + 28, 0);
    w_u16(mesh + 26, 0);
    for (i = 0; i < 4; ++i) words[i] = r_u32(target + 4 * i);
    for (i = 0; i < 4; ++i) w_u32(item + 96 + 4 * i, words[i]);
    w_u16(item + 116, count);
    return words[0];
}

static uint32 enemy_support_project(void)
{
    draft_gte_data(0, r_u32(0x1F800020));
    draft_gte_data(1, r_u32(0x1F800024));
    draft_gte_command(0x180001);
    return draft_gte_read(14);
}

uint32 sub_80015F54(uint32 position, uint32 texture, uint32 width, uint32 height, uint32 semitransparency, uint32 shade, uint32 depth_bias)
{
    uint32 descriptor, packet, depth, ot;
    w_u32(0x1F800030, r_u32(position + 8) - r_u32(0x800BBFCC));
    w_u32(0x1F800028, r_u32(position) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(position + 4) - r_u32(0x800BBFC8));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    if (r_u32(0x1F800030) > 39999) return 0;
    if (r_u32(0x1F800028) + 20000 > 40000) return 0;
    if (r_u32(0x1F80002C) + 20000 > 40000) return 0;
    w_u32(0x1F800030, r_u32(0x1F800030) - (uint32)(sint32)(sint16)depth_bias);
    if ((sint32)r_u32(0x1F800030) < 32) w_u32(0x1F800030, 32);
    descriptor = 0x800C0564 + 16 * (uint16)texture;
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    draft_gte_control(5, r_u32(0x1F800028));
    draft_gte_control(6, r_u32(0x1F80002C));
    draft_gte_control(7, r_u32(0x1F800030));
    w_u16(0x1F800020, -(sint32)(sint16)width / 2);
    w_u16(0x1F800022, 0u - height);
    w_u16(0x1F800024, 0);
    packet = r_u32(0x80071680);
    w_u32(0x80071680, packet + 40);
    depth = enemy_support_project();
    w_u8(packet + 3, 9);
    w_u8(packet + 7, (uint16)semitransparency ? 46 : 44);
    w_u8(packet + 4, shade);
    w_u8(packet + 5, shade);
    w_u8(packet + 6, shade);
    w_u32(packet + 8, depth);
    w_u16(0x1F800020, r_u16(0x1F800020) + width);
    depth = enemy_support_project();
    w_u16(packet + 22, r_u16(descriptor));
    if ((uint16)semitransparency)
        w_u16(packet + 22, r_u16(packet + 22) | r_u16(0x8007177E + 2 * (uint16)semitransparency));
    w_u32(packet + 16, depth);
    w_u16(0x1F800022, r_u16(0x1F800022) + height);
    depth = enemy_support_project();
    w_u16(packet + 14, r_u16(descriptor + 2));
    w_u32(packet + 32, depth);
    w_u16(0x1F800020, r_u16(0x1F800020) - width);
    depth = enemy_support_project();
    w_u8(packet + 12, r_u8(descriptor + 4));
    w_u8(packet + 13, r_u8(descriptor + 6));
    w_u8(packet + 20, r_u8(descriptor + 4) + r_u8(descriptor + 8) - 1);
    w_u8(packet + 21, r_u8(descriptor + 6));
    w_u8(packet + 28, r_u8(descriptor + 4));
    w_u8(packet + 29, r_u8(descriptor + 6) + r_u8(descriptor + 10) - 1);
    w_u8(packet + 36, r_u8(descriptor + 4) + r_u8(descriptor + 8) - 1);
    w_u8(packet + 37, r_u8(descriptor + 6) + r_u8(descriptor + 10) - 1);
    w_u32(packet + 24, depth);
    depth = (uint32)((sint32)r_u32(0x1F800030) >> 4);
    if (depth - 1 < 2499) {
        ot = r_u32(0x8007184C) + 4 * depth;
        w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ot) & 0xFFFFFF));
        w_u32(ot, (r_u32(ot) & 0xFF000000) | (packet & 0xFFFFFF));
    }
    return 1;
}
