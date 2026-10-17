#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static uint32 homing_project(void)
{
    draft_gte_data(0, r_u32(0x1F800020));
    draft_gte_data(1, r_u32(0x1F800024));
    draft_gte_command(0x180001);
    return draft_gte_read(14);
}

uint32 sub_80017828(uint32 position, uint32 texture, uint32 scale_shift, uint32 blend, uint32 red, uint32 green, uint32 blue, uint32 flip)
{
    uint32 metadata, packet, x, width, height, depth, ot;
    uint32 shift = scale_shift & 31;
    w_u32(0x1F800030, r_u32(position + 8) - r_u32(0x800BBFCC));
    w_u32(0x1F800028, r_u32(position) - r_u32(0x800BBFC4));
    w_u32(0x1F80002C, r_u32(position + 4) - r_u32(0x800BBFC8));
    sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
    depth = r_u32(0x1F800030);
    if (depth > 39999 || r_u32(0x1F800028) + 20000 > 40000 || r_u32(0x1F80002C) + 20000 > 40000)
        return 0;
    if ((sint32)depth < 32)
        w_u32(0x1F800030, 32);
    metadata = 0x800C0564 + 16 * (uint16)texture;
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    draft_gte_control(5, r_u32(0x1F800028));
    draft_gte_control(6, r_u32(0x1F80002C));
    draft_gte_control(7, r_u32(0x1F800030));
    packet = r_u32(0x80071680);
    w_u32(0x80071680, packet + 40);
    x = (uint32)(sint32)(sint16)r_u16(metadata + 12);
    if (!(uint16)flip)
        x = 0 - x;
    w_u16(0x1F800020, x << shift);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, (0 - (uint32)(sint32)(sint16)r_u16(metadata + 14)) << shift);
    x = homing_project();
    w_u8(packet + 3, 9);
    w_u8(packet + 7, (uint16)blend ? 46 : 44);
    w_u8(packet + 4, red);
    w_u8(packet + 5, green);
    w_u8(packet + 6, blue);
    w_u32(packet + 8, x);
    width = (uint32)(sint32)(sint16)r_u16(metadata + 8) << shift;
    x = r_u16(0x1F800020);
    w_u16(0x1F800020, (uint16)flip ? x - width : x + width);
    x = homing_project();
    w_u16(packet + 22, r_u16(metadata));
    if ((uint16)blend)
        w_u16(packet + 22, r_u16(metadata) | r_u16(0x8007177E + 2 * (uint16)blend));
    w_u32(packet + 16, x);
    height = (uint32)(sint32)(sint16)r_u16(metadata + 10) << shift;
    w_u16(0x1F800022, r_u16(0x1F800022) + height);
    x = homing_project();
    w_u16(packet + 14, r_u16(metadata + 2));
    w_u32(packet + 32, x);
    width = (uint32)(sint32)(sint16)r_u16(metadata + 8) << shift;
    x = r_u16(0x1F800020);
    w_u16(0x1F800020, (uint16)flip ? x + width : x - width);
    x = homing_project();
    w_u8(packet + 12, r_u8(metadata + 4));
    w_u8(packet + 13, r_u8(metadata + 6));
    w_u8(packet + 20, r_u8(metadata + 4) + r_u8(metadata + 8) - 1);
    w_u8(packet + 21, r_u8(metadata + 6));
    w_u8(packet + 28, r_u8(metadata + 4));
    w_u8(packet + 29, r_u8(metadata + 6) + r_u8(metadata + 10) - 1);
    w_u8(packet + 36, r_u8(metadata + 4) + r_u8(metadata + 8) - 1);
    w_u8(packet + 37, r_u8(metadata + 6) + r_u8(metadata + 10) - 1);
    w_u32(packet + 24, x);
    depth = (uint32)((sint32)r_u32(0x1F800030) >> 4);
    if (depth - 16 < 2484)
    {
        ot = r_u32(0x8007184C) + 4 * depth;
        w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(ot) & 0xFFFFFF));
        w_u32(ot, (r_u32(ot) & 0xFF000000) | (packet & 0xFFFFFF));
    }
    return 1;
}

uint32 sub_8002A498(uint32 position, uint32 sprite, uint32 flip, uint32 blend, uint32 fade, uint32 red, uint32 green, uint32 blue)
{
    uint32 node = sub_80032EF0(), words[4], i;
    if (!node)
        return 46;
    w_u32(node + 8, 46);
    for (i = 0; i < 4; ++i)
        words[i] = r_u32(position + 4 * i);
    for (i = 0; i < 4; ++i)
        w_u32(node + 12 + 4 * i, words[i]);
    w_u16(node + 28, sprite);
    w_u16(node + 34, flip);
    w_u16(node + 30, blend);
    w_u16(node + 32, fade);
    w_u16(node + 36, red);
    w_u16(node + 38, green);
    w_u16(node + 40, blue);
    return words[0];
}

uint32 sub_8003B900(uint32 node)
{
    uint32 fade = r_u16(node + 32), colors[3], product, i, result;
    for (i = 0; i < 3; ++i)
    {
        product = r_u16(node + 36 + 2 * i) * fade;
        if ((sint32)product < 0)
            product += 127;
        colors[i] = (uint16)(product >> 7);
    }
    sub_80017828(node + 12, r_u16(node + 28), 5, r_u16(node + 30), colors[0], colors[1], colors[2], r_u16(node + 34));
    fade = r_u16(node + 32);
    if (fade < 17)
        return sub_80032FD0(node);
    result = fade - 16;
    w_u16(node + 32, result);
    return result;
}

uint32 sub_8003CB64(uint32 node)
{
    uint32 timer = r_u16(node + 110), mesh, collision, proximity[8], address;
    uint32 active, kind, sprite, red, green, blue, flip, angle, player;
    sint32 turn, vertical, speed;
    w_u16(node + 110, timer - 1);
    if (!timer)
    {
        sub_8003B314(node);
        return sub_80032FD0(node);
    }
    mesh = r_u32(node + 12);
    address = draft_local_address(proximity, sizeof(proximity));
    sub_80051F74(mesh + 8, address);
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    active = !(r_u16(0x800719D0) & 1);
    collision = r_u32(node + 72);
    if (r_u32(collision + 128))
    {
        if (!r_u16(node + 118))
        {
            sub_8003B314(node);
            return sub_80032FD0(node);
        }
        w_u16(node + 104, 300);
        w_u16(node + 94, (r_u16(node + 94) + 2048) & 4095);
    }
    if (r_u16(node + 118))
    {
        sub_8003CA28(mesh + 8, node + 76);
        sub_8001FCE8(mesh + 8, node + 76);
        angle = sub_80046C98(mesh + 8, node + 76);
        if (!(r_u16(0x800719D0) & 1))
            w_u16(node + 94, sub_8001F8E0((uint32)(sint32)(sint16)r_u16(node + 94), (uint32)(sint32)(sint16)angle, 2));
        vertical = (sint16)r_u16(node + 106);
        if ((sint32)r_u32(node + 80) < (sint32)r_u32(mesh + 12))
        {
            if (vertical >= -127)
                w_u16(node + 106, vertical - 8);
        }
        else if (vertical < 128)
            w_u16(node + 106, vertical + 8);
        turn = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(node + 94) - angle));
        if (turn < 0)
            turn = -turn;
        if (turn < 1025)
        {
            speed = (sint16)(r_u16(node + 104) + 32);
            w_u16(node + 104, speed);
            if (speed >= 301)
                w_u16(node + 104, 300);
        }
        else
        {
            speed = (sint16)r_u16(node + 104);
            if (speed >= 129)
                w_u16(node + 104, speed - 1);
        }
    }
    sub_80031088(mesh + 8, (uint32)(sint32)(sint16)r_u16(node + 94), (uint32)(sint32)(sint16)r_u16(node + 104));
    w_u32(mesh + 12, r_u32(mesh + 12) + (uint32)(sint32)(sint16)r_u16(node + 106));
    kind = r_u16(node + 112);
    w_u16(node + 116, r_u16(node + 116) + 1);
    if (!kind)
    {
        sprite = ((r_u16(node + 116) >> 2) & 3) + 267;
        if (sprite == 270)
            sprite = 269;
        red = 0;
        green = 128;
        blue = 0;
    }
    else if (kind == 1)
    {
        sprite = 264;
        active = 1;
        red = 128;
        green = 0;
        blue = 128;
    }
    else
    {
        /* The original caller constructs only modes 0 and 1 */
        return draft_unknown_return("8003CB64 mode leaves original saved registers undefined");
    }
    angle = sub_80046D0C((uint32)(sint32)(sint16)(r_u16(node + 94) + r_u16(0x800BBFD6)));
    flip = (sint16)angle <= 0;
    sub_80017828(mesh + 8, sprite, 5, 2, red, green, blue, flip);
    if (!(r_u16(0x800719D0) & 1))
        sub_8002A498(mesh + 8, sprite, flip, 2, 128, red, green, blue);
    if (active)
    {
        w_u32(collision + 132, r_u16(node + 108));
        w_u16(collision + 136, r_u16(node + 94));
        w_u16(collision + 148, 180);
        sub_800475A8(r_u32(node + 72));
    }
    else
        w_u32(collision + 128, 0);
    if (!(r_u16(0x800719D0) & 1))
    {
        if (r_u16(node + 108) & 0x4000)
            sub_8002B178(mesh + 8, 64, 256, 0);
        else
            sub_8002B178(mesh + 8, 256, 64, 256);
    }
    player = r_u16(address + 24);
    if ((sint32)r_u32(address + 16 + 4 * player) < 6000)
        return sub_80021288(r_u32(mesh + 8), r_u32(mesh + 16), r_u32(node + 100), r_u32(node + 100), 2);
    return 2;
}

uint32 sub_8003B4BC(uint32 node)
{
    uint32 timer = r_u16(node + 110), mesh, collision, proximity[8], active, kind, sprite, flip, angle;
    sint32 turn, vertical, speed;
    w_u16(node + 110, timer - 1);
    if (!timer)
    {
        sub_8003B314(node);
        return sub_80032FD0(node);
    }
    mesh = r_u32(node + 12);
    sub_80051F74(mesh + 8, draft_local_address(proximity, sizeof(proximity)));
    sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
    sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
    active = !(r_u16(0x800719D0) & 1);
    collision = r_u32(node + 72);
    if (r_u32(collision + 128))
    {
        if (!r_u16(node + 118))
        {
            sub_8003B314(node);
            return sub_80032FD0(node);
        }
        w_u16(node + 104, 300);
        w_u16(node + 94, (r_u16(node + 94) + 2048) & 4095);
    }
    if (r_u16(node + 118))
    {
        sub_8003B384(mesh + 8, node + 76);
        sub_8001FCE8(mesh + 8, node + 76);
        angle = sub_80046C98(mesh + 8, node + 76);
        if (!(r_u16(0x800719D0) & 1))
            w_u16(node + 94, sub_8001F8E0((uint32)(sint32)r_s16(node + 94), (uint32)(sint32)(sint16)angle, 2));
        vertical = r_s16(node + 106);
        if ((sint32)r_u32(node + 80) < (sint32)r_u32(mesh + 12))
        {
            if (vertical >= -127)
                w_u16(node + 106, vertical - 8);
        }
        else if (vertical < 128)
            w_u16(node + 106, vertical + 8);
        turn = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(node + 94) - angle));
        if (turn < 0)
            turn = -turn;
        if (turn < 1025)
        {
            speed = (sint16)(r_u16(node + 104) + 32);
            w_u16(node + 104, speed);
            if (speed >= 301)
                w_u16(node + 104, 300);
        }
        else
        {
            speed = r_s16(node + 104);
            if (speed >= 129)
                w_u16(node + 104, speed - 1);
        }
    }
    sub_80031088(mesh + 8, (uint32)(sint32)r_s16(node + 94), (uint32)(sint32)r_s16(node + 104));
    w_u32(mesh + 12, r_u32(mesh + 12) + (uint32)(sint32)r_s16(node + 106));
    kind = r_u16(node + 112);
    w_u16(node + 116, r_u16(node + 116) + 1);
    if (!kind)
    {
        sprite = 264;
        active = 1;
    }
    else if (kind == 1)
        sprite = ((r_u16(node + 116) >> 2) & 1) + 265;
    else if (kind == 2)
    {
        sprite = ((r_u16(node + 116) >> 2) & 3) + 267;
        if (sprite == 270)
            sprite = 269;
    }
    else
    {
        /* TODO: Modes outside 0..2 leave the original sprite register uninitialized */
        return draft_unknown_return("8003B4BC outside reviewed 80053B00 mode range");
    }
    angle = sub_80046D0C((uint32)(sint32)(sint16)(r_u16(node + 94) + r_u16(0x800BBFD6)));
    flip = (sint16)angle <= 0;
    sub_800173DC(mesh + 8, sprite, 5, 2, 128, flip);
    if (!(r_u16(0x800719D0) & 1))
        sub_8002A498(mesh + 8, sprite, flip, 2, 128, 128, 128, 128);
    if (active)
    {
        w_u32(r_u32(node + 72) + 132, r_u16(node + 108));
        w_u16(r_u32(node + 72) + 136, r_u16(node + 94));
        w_u16(r_u32(node + 72) + 148, 180);
        sub_800475A8(r_u32(node + 72));
    }
    else
        w_u32(r_u32(node + 72) + 128, 0);
    if (!(r_u16(0x800719D0) & 1))
    {
        if (r_u16(node + 108) & 0x4000)
            return sub_8002B178(mesh + 8, 256, 128, 0);
        return sub_8002B178(mesh + 8, 64, 256, 256);
    }
    return 1;
}
