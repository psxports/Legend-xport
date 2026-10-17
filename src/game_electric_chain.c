#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_800465EC(uint32 first, uint32 second)
{
    uint32 x = r_u32(first) - r_u32(second);
    uint32 z = r_u32(first + 8) - r_u32(second + 8);
    uint32 y = r_u32(first + 4) - r_u32(second + 4);
    return sub_8005CBB8(x * x + z * z + y * y);
}

uint32 sub_8003CA28(uint32 position, uint32 target)
{
    uint32 index, player, x, z, words[4], i;
    sint32 distance, best = 1000000;
    for (index = 0; index < 2; ++index)
    {
        player = 0x800AFEC0 + 288 * index;
        if (!r_u8(player + 240))
            continue;
        x = r_u32(position) - r_u32(player);
        z = r_u32(position + 8) - r_u32(player + 8);
        distance = (sint32)sub_8005CBB8(x * x + z * z);
        if (distance >= best)
            continue;
        for (i = 0; i < 4; ++i)
            words[i] = r_u32(player + 4 * i);
        for (i = 0; i < 4; ++i)
            w_u32(target + 4 * i, words[i]);
        best = distance;
        w_u32(target + 4, r_u32(target + 4) - 800);
    }
    return 2;
}

uint32 sub_80029C98(uint32 position, uint32 radius, uint32 parameter, uint32 flags, uint32 lifetime, uint32 owner, uint32 target)
{
    uint32 node = sub_80032EF0(), mesh, collision, words[4], i, result;
    if (!node)
        return 43;
    w_u32(node + 8, 43);
    mesh = sub_8001A3BC();
    for (i = 0; i < 4; ++i)
        words[i] = r_u32(position + 4 * i);
    for (i = 0; i < 4; ++i)
        w_u32(mesh + 8 + 4 * i, words[i]);
    w_u16(node + 68, 1);
    w_u16(node + 70, radius);
    w_u32(node + 32, radius);
    w_u16(node + 36, 0);
    w_u16(node + 38, 0);
    w_u16(node + 40, 0);
    w_u32(mesh + 80, node + 16);
    sub_8001A494(mesh);
    collision = sub_800474F4();
    w_u32(node + 72, collision);
    sub_80047534(collision, mesh, (uint8)flags);
    result = 0xFFFF;
    if (owner)
    {
        w_u16(collision + 138, r_u16(owner + 138));
        result = r_u16(owner + 142);
        w_u16(collision + 142, result);
    }
    else
        w_u16(collision + 138, 0xFFFF);
    w_u32(collision + 124, target);
    w_u32(node + 12, mesh);
    w_u32(node + 76, parameter);
    w_u32(node + 80, lifetime);
    return result;
}

uint32 sub_8003AEE4(uint32 node)
{
    uint32 remaining = r_u32(node + 80) - 1, collision;
    w_u32(node + 80, remaining);
    if (!remaining)
    {
        sub_8003AEA8(node);
        return sub_80032FD0(node);
    }
    collision = r_u32(node + 72);
    w_u32(collision + 132, r_u32(node + 76));
    w_u16(collision + 136, (((r_u16(0x800719D0) & 1) << 11) - 1024) & 4095);
    w_u16(collision + 148, 80);
    return sub_800475A8(r_u32(node + 72));
}

uint32 sub_8003BC58(uint32 first, uint32 second, uint32 shade)
{
    uint32 packet = r_u32(0x80071680), i, endpoint, position, depth = 0;
    uint32 page, u, v, right, bottom, entry, result;
    sint32 width = r_u16(0x800719D0) & 1 ? 256 : -256;
    sint32 bucket;
    w_u32(0x80071680, packet + 40);
    w_u8(packet + 3, 9);
    w_u8(packet + 7, 46);
    for (i = 0; i < 3; ++i)
        w_u8(packet + 4 + i, shade);
    u = r_u8(0x800C15C8);
    v = r_u8(0x800C15CA);
    right = u + r_u8(0x800C15CC) - 1;
    bottom = v + r_u8(0x800C15CE) - 1;
    w_u8(packet + 12, u);
    w_u8(packet + 13, v);
    w_u8(packet + 20, right);
    w_u8(packet + 21, v);
    w_u8(packet + 28, u);
    w_u8(packet + 29, bottom);
    w_u8(packet + 36, right);
    w_u8(packet + 37, bottom);
    w_u16(packet + 14, r_u16(0x800C15C6));
    page = r_u16(0x800C15C4);
    w_u16(packet + 22, page);
    w_u16(packet + 22, page | r_u16(0x80071782));
    for (endpoint = 0; endpoint < 2; ++endpoint)
    {
        position = endpoint ? second : first;
        for (i = 0; i < 3; ++i)
            w_u32(0x1F800028 + 4 * i, r_u32(position + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
        sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
        depth += r_u32(0x1F800030);
        for (i = 0; i < 3; ++i)
            draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
        for (i = 0; i < 5; ++i)
            draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
        w_u16(0x1F800020, 0);
        w_u16(0x1F800022, -width);
        w_u16(0x1F800024, 0);
        draft_gte_data(0, r_u32(0x1F800020));
        draft_gte_data(1, r_u32(0x1F800024));
        draft_gte_command(0x180001);
        w_u16(0x1F800022, width);
        w_u32(packet + 8 + 8 * endpoint, draft_gte_read(14));
        draft_gte_data(0, r_u32(0x1F800020));
        draft_gte_data(1, r_u32(0x1F800024));
        draft_gte_command(0x180001);
        w_u32(packet + 24 + 8 * endpoint, draft_gte_read(14));
    }
    bucket = (sint32)depth >> 5;
    result = (uint32)(bucket - 16) < 0x9B4;
    if (result)
    {
        entry = r_u32(0x8007184C) + 4 * (uint32)bucket;
        w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(entry) & 0xFFFFFF));
        result = (r_u32(entry) & 0xFF000000) | (packet & 0xFFFFFF);
        w_u32(entry, result);
    }
    return result;
}

uint32 sub_8003B384(uint32 position, uint32 target)
{
    uint32 index = 0, entry, x, z, words[4], i, result;
    sint32 distance, best = 1000000;
    if (!r_u16(0x80071584))
        return 0;
    do
    {
        entry = 0x800C0404 + 28 * (uint16)index;
        x = r_u32(position) - r_u32(entry);
        z = r_u32(position + 8) - r_u32(entry + 8);
        distance = (sint32)sub_8005CBB8(x * x + z * z);
        ++index;
        if (distance < best)
        {
            for (i = 0; i < 4; ++i)
                words[i] = r_u32(entry + 4 * i);
            for (i = 0; i < 4; ++i)
                w_u32(target + 4 * i, words[i]);
            best = distance;
            w_u32(target + 4, r_u32(target + 4) - 800);
        }
        result = (uint16)index < r_u16(0x80071584);
    } while (result);
    return result;
}

uint32 sub_8003C070(uint32 node)
{
    uint32 limit = 60;
    uint32 age = r_u16(node + 60), i, source, words[4], index = 0, heading, color, result;
    uint32 position[4], previous[4], address, previous_address;
    sint32 turn, vertical;
    w_u16(node + 60, age + 1);
    if (age > limit)
    {
        sub_800449A0(r_u16(node + 66));
        sub_8004486C(4, r_u16(node + 66), 0, 0, 0, 0);
        return sub_80032FD0(node);
    }
    for (i = 0; i < 4; ++i)
        words[i] = r_u32(node + 32 + 4 * i);
    for (i = 0; i < 4; ++i)
        w_u32(node + 16 + 4 * i, words[i]);
    source = r_u32(node + 12);
    for (i = 0; i < 4; ++i)
        position[i] = r_u32(source + 4 * i);
    heading = r_u16(node + 58);
    address = draft_local_address(position, sizeof(position));
    previous_address = draft_local_address(previous, sizeof(previous));
    sub_8003B384(address, node + 16);
    w_u16(node + 64, (sub_80011B8C() & 63) - 31);
    if (r_u16(node + 56))
    {
        do
        {
            for (i = 0; i < 4; ++i)
                previous[i] = position[i];
            turn = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(sub_80046C98(previous_address, node + 16) - heading));
            if (turn < -256)
                turn = -256;
            if (turn > 256)
                turn = 256;
            heading += (uint32)turn;
            w_u16(0x1F800020, 0);
            w_u16(0x1F800022, heading);
            w_u16(0x1F800024, 0);
            sub_8005D138(0x1F800020, 0x1F800000);
            w_u16(0x1F800020, 0);
            w_u16(0x1F800022, 0);
            w_u16(0x1F800024, 512);
            sub_8005CDD8(0x1F800000, 0x1F800020, address);
            for (i = 0; i < 3; ++i)
                position[i] += previous[i];
            position[1] += (uint32)(sint32)(sint16)r_u16(node + 64);
            vertical = (sint16)r_u16(node + 64);
            if ((sint32)r_u32(node + 20) < (sint32)position[1])
            {
                if (vertical >= -127)
                    w_u16(node + 64, vertical - 128);
            }
            else if (vertical < 128)
                w_u16(node + 64, vertical + 128);
            color = (sub_80011B8C() & 63) | 64;
            sub_8003BC58(previous_address, address, color);
            sub_80016B84(address, 279, 4, 2, color >> 1, color >> 1, color);
            if ((sint32)sub_800465EC(address, node + 16) < 512)
            {
                w_u16(node + 56, index + 1);
                sub_80016B84(address, 279, 5, 2, 128, 128, 128);
                index = 1000;
                if (!(r_u16(0x800719D0) & 1))
                    sub_80029C98(address, 1000, r_u16(node + 62), 3, 2, r_u32(node + 48), r_u32(node + 52));
            }
            ++index;
        } while ((uint16)index < r_u16(node + 56));
    }
    result = r_u16(node + 56) < 32;
    if (result)
    {
        result = r_u16(node + 56) + 2;
        w_u16(node + 56, result);
    }
    return result;
}

uint32 sub_8003D16C(uint32 node)
{
    uint32 limit = r_u32(node + 8) == 63 ? 20 : 30;
    uint32 age = r_u16(node + 60), i, source, words[4], index = 0, heading, color, result;
    uint32 position[4], previous[4], address, previous_address;
    sint32 turn, vertical;
    w_u16(node + 60, age + 1);
    if (age > limit)
    {
        sub_800449A0(r_u16(node + 66));
        sub_8004486C(4, r_u16(node + 66), 0, 0, 0, 0);
        return sub_80032FD0(node);
    }
    for (i = 0; i < 4; ++i)
        words[i] = r_u32(node + 32 + 4 * i);
    for (i = 0; i < 4; ++i)
        w_u32(node + 16 + 4 * i, words[i]);
    source = r_u32(node + 12);
    for (i = 0; i < 4; ++i)
        position[i] = r_u32(source + 4 * i);
    heading = r_u16(node + 58);
    address = draft_local_address(position, sizeof(position));
    previous_address = draft_local_address(previous, sizeof(previous));
    sub_8003CA28(address, node + 16);
    w_u16(node + 64, (sub_80011B8C() & 63) - 31);
    if (r_u16(node + 56))
    {
        do
        {
            for (i = 0; i < 4; ++i)
                previous[i] = position[i];
            turn = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(sub_80046C98(previous_address, node + 16) - heading));
            if (turn < -256)
                turn = -256;
            if (turn > 256)
                turn = 256;
            heading += (uint32)turn;
            w_u16(0x1F800020, 0);
            w_u16(0x1F800022, heading);
            w_u16(0x1F800024, 0);
            sub_8005D138(0x1F800020, 0x1F800000);
            w_u16(0x1F800020, 0);
            w_u16(0x1F800022, 0);
            w_u16(0x1F800024, 512);
            sub_8005CDD8(0x1F800000, 0x1F800020, address);
            for (i = 0; i < 3; ++i)
                position[i] += previous[i];
            position[1] += (uint32)(sint32)(sint16)r_u16(node + 64);
            vertical = (sint16)r_u16(node + 64);
            if ((sint32)r_u32(node + 20) < (sint32)position[1])
            {
                if (vertical >= -127)
                    w_u16(node + 64, vertical - 128);
            }
            else if (vertical < 128)
                w_u16(node + 64, vertical + 128);
            color = (sub_80011B8C() & 63) | 64;
            sub_8003BC58(previous_address, address, color);
            if (r_u32(node + 8) == 52)
                sub_80016B84(address, 279, 4, 2, color, color >> 1, color >> 2);
            else
                sub_80016B84(address, 279, 4, 2, color >> 3, color, color >> 3);
            if ((sint32)sub_800465EC(address, node + 16) < 512)
            {
                w_u16(node + 56, index + 1);
                sub_80016B84(address, 279, 5, 2, 128, 128, 128);
                index = 1000;
                if (!(r_u16(0x800719D0) & 1))
                    sub_80029C98(address, 1000, r_u16(node + 62), 3, 2, r_u32(node + 48), r_u32(node + 52));
            }
            ++index;
        } while ((uint16)index < r_u16(node + 56));
    }
    result = r_u16(node + 56) < 32;
    if (result)
    {
        result = r_u16(node + 56) + 2;
        w_u16(node + 56, result);
    }
    return result;
}


/* Native helpers for the four repeated packet and projection blocks */
static uint32 flame_packet(uint32 descriptor, uint32 tail)
{
    uint32 packet = r_u32(0x80071680), page, uv[8];
    w_u32(0x80071680, packet + 40);
    w_u8(packet + 3, 9);
    w_u8(packet + 7, 44);
    w_u8(packet + 4, 128);
    w_u8(packet + 5, 128);
    w_u8(packet + 6, 128);
    w_u8(packet + 12, r_u8(descriptor + 4) + 16);
    w_u8(packet + 13, r_u8(descriptor + 6) + 8);
    page = r_u8(descriptor + 8);
    w_u8(packet + 20, r_u8(descriptor + 4) + page - 17);
    w_u8(packet + 21, r_u8(descriptor + 6) + 8);
    w_u8(packet + 28, r_u8(descriptor + 4) + 16);
    page = r_u8(descriptor + 10);
    w_u8(packet + 29, r_u8(descriptor + 6) + page - 17);
    page = r_u8(descriptor + 8);
    w_u8(packet + 36, r_u8(descriptor + 4) + page - 17);
    page = r_u8(descriptor + 10);
    w_u8(packet + 37, r_u8(descriptor + 6) + page - 17);
    if (tail)
    {
        uv[0] = r_u8(packet + 12);
        uv[1] = r_u8(packet + 13);
        uv[2] = r_u8(packet + 28);
        uv[3] = r_u8(packet + 29);
        uv[4] = r_u8(packet + 36);
        uv[5] = r_u8(packet + 37);
        uv[6] = r_u8(packet + 20);
        uv[7] = r_u8(packet + 21);
        w_u8(packet + 12, uv[2]);
        w_u8(packet + 13, uv[3]);
        w_u8(packet + 28, uv[4]);
        w_u8(packet + 29, uv[5]);
        w_u8(packet + 36, uv[6]);
        w_u8(packet + 37, uv[7]);
        w_u8(packet + 20, uv[0]);
        w_u8(packet + 21, uv[1]);
    }
    w_u16(packet + 14, r_u16(descriptor + 2));
    page = r_u16(descriptor);
    w_u16(packet + 22, page);
    w_u16(packet + 22, page | r_u16(0x80071782));
    return packet;
}

static void flame_project(void)
{
    draft_gte_data(0, r_u32(0x1F800020));
    draft_gte_data(1, r_u32(0x1F800024));
    draft_gte_command(0x180001);
}

uint32 sub_8003D6B0(uint32 first, uint32 old_width, uint32 second, uint32 new_width, uint32 index, uint32 count, uint32 yaw)
{
    uint32 descriptor = 0x800C1404 + 16 * (((uint16)index + r_u16(0x800719D0)) & 7);
    uint32 tail = (uint16)index == (uint32)((uint16)count - 1);
    uint32 packet, face, i, old_offset[4], new_offset[4], dx, dz, x, z, entry, result = 0;
    sint32 depth = 0;
    for (face = 0; face < 4; ++face)
    {
        packet = flame_packet(descriptor, tail);
        if (!face)
        {
            if (tail)
                new_width = 0;
            w_u16(0x1F800020, 0);
            w_u16(0x1F800022, yaw);
            w_u16(0x1F800024, 0);
            sub_8005D138(0x1F800020, 0x1F800000);
            w_u16(0x1F800020, (sint16)old_width / 2);
            w_u16(0x1F800022, 0);
            w_u16(0x1F800024, 0);
            sub_8005CDD8(0x1F800000, 0x1F800020, draft_local_address(old_offset, sizeof(old_offset)));
            w_u16(0x1F800020, (uint16)new_width >> 1);
            w_u16(0x1F800022, 0);
            w_u16(0x1F800024, 0);
            sub_8005CDD8(0x1F800000, 0x1F800020, draft_local_address(new_offset, sizeof(new_offset)));
            for (i = 0; i < 3; ++i)
                w_u32(0x1F800028 + 4 * i, r_u32(first + 4 * i) - r_u32(0x800BBFC4 + 4 * i));
            sub_8005CC48(0x800BBFDC, 0x1F800028, 0x1F800028);
            depth = (sint32)r_u32(0x1F800030);
            for (i = 0; i < 3; ++i)
                draft_gte_control(5 + i, r_u32(0x1F800028 + 4 * i));
            for (i = 0; i < 5; ++i)
                draft_gte_control(i, r_u32(0x800BBFDC + 4 * i));
        }
        w_u16(0x1F800020, 0);
        if (face & 1)
        {
            w_u16(0x1F800024, 0);
            w_u16(0x1F800022, old_width);
        }
        else
        {
            w_u16(0x1F800022, 0 - old_width);
            w_u16(0x1F800024, 0);
        }
        flame_project();
        w_u16(0x1F800022, 0);
        x = (uint16)old_offset[0];
        z = (uint16)old_offset[2];
        w_u16(0x1F800020, face < 2 ? 0 - x : x);
        w_u16(0x1F800024, face < 2 ? 0 - z : z);
        w_u32(packet + 8, draft_gte_read(14));
        flame_project();
        w_u32(packet + 24, draft_gte_read(14));
        dx = r_u16(second) - r_u16(first);
        w_u16(0x1F800022, face & 1 ? new_width : 0 - new_width);
        w_u16(0x1F800020, dx);
        dz = r_u16(second + 8) - r_u16(first + 8);
        w_u16(0x1F800024, dz);
        flame_project();
        x = (uint16)new_offset[0];
        z = (uint16)new_offset[2];
        w_u16(0x1F800022, 0);
        w_u16(0x1F800020, face < 2 ? dx - x : dx + x);
        w_u16(0x1F800024, face < 2 ? dz - z : dz + z);
        w_u32(packet + 16, draft_gte_read(14));
        flame_project();
        result = packet + 32;
        w_u32(result, draft_gte_read(14));
        if (!face)
            depth >>= 4;
        if ((uint32)depth - 16 < 0x9B4)
        {
            entry = r_u32(0x8007184C) + 4 * (uint32)depth;
            w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(entry) & 0xFFFFFF));
            result = (r_u32(entry) & 0xFF000000) | (packet & 0xFFFFFF);
            w_u32(entry, result);
        }
    }
    return result;
}

uint32 sub_8003E2E8(uint32 node)
{
    uint32 rise = (sub_80011B8C() & 63) + 100;
    uint32 actor = r_u32(node + 40), mesh = r_u32(r_u32(actor));
    uint32 age = r_u16(node + 48), source, position[4], previous[4], i, index = 0;
    uint32 radius = 400, old_radius, taper, address, previous_address, result, current;
    w_u16(node + 48, age + 1);
    if (age >= 61 || (uint32)r_u16(actor + 214) - 27 >= 6)
    {
        sub_800449A0(r_u16(node + 52));
        sub_8004486C(4, r_u16(node + 52), 0, 0, 0, 0);
        return sub_80032FD0(node);
    }
    source = r_u32(node + 12);
    for (i = 0; i < 4; ++i)
        position[i] = r_u32(source + 4 * i);
    position[1] += 200;
    w_u16(0x1F800020, 0);
    w_u16(0x1F800024, 0);
    w_u16(0x1F800022, r_u16(mesh + 26));
    sub_8005D138(0x1F800020, 0x1F800000);
    w_u16(0x1F800020, 0);
    w_u16(0x1F800022, 0);
    w_u16(0x1F800024, 384);
    sub_8005CDD8(0x1F800000, 0x1F800020, node + 24);
    taper = r_u16(node + 44);
    taper -= taper >> 2;
    address = draft_local_address(position, sizeof(position));
    previous_address = draft_local_address(previous, sizeof(previous));
    if (r_u16(node + 44))
    {
        do
        {
            for (i = 0; i < 4; ++i)
                previous[i] = position[i];
            position[0] += r_u32(node + 24);
            position[1] += r_u32(node + 28) + (uint32)(sint32)(sint16)rise;
            rise -= 10;
            position[2] += r_u32(node + 32);
            old_radius = radius;
            radius += (uint16)index < (uint16)taper ? 50 : (uint32)-100;
            sub_8003D6B0(previous_address, (uint32)(sint32)(sint16)old_radius, address, (uint16)radius,
                (uint16)index, r_u16(node + 44), (uint32)(sint32)r_s16(mesh + 26));
            if (!(r_u16(0x800719D0) & 1) && ((r_u16(0x800719D0) >> 1) & 15) == (uint16)index)
            {
                w_u32(0x1F800028, 0);
                w_u32(0x1F80002C, 0);
                w_u32(0x1F800030, 0);
                sub_80022CC0(address, 0x1F800028, 4, 5);
            }
            current = index++;
            if ((r_u16(0x800719D0) & 1) == (current & 1))
                sub_80029C98(address, (uint32)(sint32)(sint16)radius, r_u8(node + 50) | 0xC000,
                    4, 2, r_u32(node + 16), r_u32(node + 20));
        } while ((uint16)index < r_u16(node + 44));
    }
    if (r_u16(node + 44) < 24)
        w_u16(node + 44, r_u16(node + 44) + 1);
    if (!(r_u16(0x800719D0) & 1))
        sub_8002B178(address, 256, 128, 32);
    result = r_u16(0x800719D0) & 7;
    if (!result)
    {
        sub_8004EC38(8);
        w_u16(0x8007158C, 128);
        w_u16(0x80071A50, 8);
        return sub_8003278C(500);
    }
    return result;
}
