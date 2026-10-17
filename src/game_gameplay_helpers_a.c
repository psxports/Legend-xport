#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static uint32 gameplay_project_vertex(void)
{
    draft_gte_data(0, r_u32(0x1F800020u));
    draft_gte_data(1, r_u32(0x1F800024u));
    draft_gte_command(0x180001u);
    return draft_gte_read(14);
}

uint32 sub_80016F80(uint32 position, uint32 texture, uint32 mode, uint32 rotation)
{
    uint32 depth, item, packet, ordering, i, shift = mode & 31u;
    sint32 sum;
    w_u32(0x1F800030u, r_u32(position + 8) - r_u32(0x800BBFCCu));
    w_u32(0x1F800028u, r_u32(position) - r_u32(0x800BBFC4u));
    w_u32(0x1F80002Cu, r_u32(position + 4) - r_u32(0x800BBFC8u));
    sub_8005CC48(0x800BBFDCu, 0x1F800028u, 0x1F800028u);
    if (r_u32(0x1F800030u) > 39999u || r_u32(0x1F800028u) + 20000u > 40000u || r_u32(0x1F80002Cu) + 20000u > 40000u)
        return 0;
    if ((sint32)r_u32(0x1F800030u) < 32)
        w_u32(0x1F800030u, 32);
    depth = (uint32)((sint32)r_u32(0x1F800030u) >> 4);
    if (depth - 16u >= 2484u)
        return 0;
    item = 0x800C0564u + 16 * (uint16)texture;
    sub_8005D138(rotation, 0x1F800000u);
    for (i = 0; i < 5; ++i)
        draft_gte_control(i, r_u32(0x1F800000u + 4 * i));
    for (i = 0; i < 3; ++i)
        draft_gte_control(i + 5, r_u32(0x1F800028u + 4 * i));
    w_u16(0x1F800020u, (0u - (uint32)(sint32)(sint16)r_u16(item + 12)) << shift);
    packet = r_u32(0x80071680u);
    w_u32(0x80071680u, packet + 40);
    w_u16(0x1F800024u, 0);
    w_u16(0x1F800022u, (0u - (uint32)(sint32)(sint16)r_u16(item + 14)) << shift);
    i = gameplay_project_vertex();
    for (uint32 channel = 0; channel < 3; ++channel)
    {
        sum = (sint16)r_u16(0x800BF8E0u + 2 * channel) + (sint16)r_u16(0x800BF8E8u + 2 * channel) + (sint16)r_u16(0x800BF8F0u + 2 * channel);
        w_u8(packet + 4 + channel, (uint32)(sum < 0 ? sum + 3 : sum) >> 2);
    }
    w_u8(packet + 3, 9);
    w_u8(packet + 7, 0x2C);
    w_u32(packet + 8, i);
    w_u16(0x1F800020u, r_u16(0x1F800020u) + ((uint32)(sint32)(sint16)r_u16(item + 8) << shift));
    i = gameplay_project_vertex();
    w_u8(packet + 7, r_u8(packet + 7) & 0xFE);
    w_u32(packet + 16, i);
    w_u16(0x1F800022u, r_u16(0x1F800022u) + ((uint32)(sint32)(sint16)r_u16(item + 10) << shift));
    i = gameplay_project_vertex();
    w_u16(packet + 22, r_u16(item));
    w_u16(packet + 14, r_u16(item + 2));
    w_u32(packet + 32, i);
    w_u16(0x1F800020u, r_u16(0x1F800020u) - ((uint32)(sint32)(sint16)r_u16(item + 8) << shift));
    i = gameplay_project_vertex();
    w_u8(packet + 12, r_u8(item + 4));
    w_u8(packet + 13, r_u8(item + 6));
    w_u8(packet + 20, r_u8(item + 4) + r_u8(item + 8) - 1);
    w_u8(packet + 21, r_u8(item + 6));
    w_u8(packet + 28, r_u8(item + 4));
    w_u8(packet + 29, r_u8(item + 6) + r_u8(item + 10) - 1);
    w_u8(packet + 36, r_u8(item + 4) + r_u8(item + 8) - 1);
    w_u8(packet + 37, r_u8(item + 6) + r_u8(item + 10) - 1);
    w_u32(packet + 24, i);
    ordering = r_u32(0x8007184Cu) + 4 * depth;
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(ordering) & 0xFFFFFFu));
    w_u32(ordering, (r_u32(ordering) & 0xFF000000u) | (packet & 0xFFFFFFu));
    return 1;
}

uint32 sub_80029F40(uint32 x, uint32 y, uint32 z, uint32 kind, uint32 glyph, uint32 red, uint32 green, uint32 blue)
{
    uint32 item = sub_80032EF0();
    if (!item)
        return 59u;
    w_u32(item + 8, 59u);
    w_u32(item + 12, (uint32)(sint32)(sint16)x);
    w_u32(item + 16, (uint32)(sint32)(sint16)y);
    w_u32(item + 32, (uint32)(sint32)(sint16)z);
    w_u16(item + 48, kind);
    w_u16(item + 52, red);
    w_u16(item + 54, green);
    w_u16(item + 56, blue);
    w_u16(item + 58, glyph);
    w_u16(item + 46, 0);
    w_u16(item + 44, 0);
    return (uint32)(sint32)(sint16)z;
}

uint32 sub_80044F58(uint32 volume)
{
    sint32 distance = (sint32)r_u32(0x800718A0u) >> 5;
    sint32 scaled;
    if (distance >= 1025)
        distance = 1024;
    scaled = (sint32)(volume * (1024u - (uint32)distance));
    scaled /= 512;
    if (scaled >= 16384)
        scaled = 16383;
    return (uint32)scaled;
}

uint32 sub_8003F814(uint32 actor, uint32 choice)
{
    uint32 offset = 32 * (uint16)actor + 2 * (uint16)choice;
    uint32 pitch = r_u16(0x800BF908u + offset), sound = r_u16(0x800AEA6Cu + offset), channel, volume;
    if (sound == 0xFFFFu)
        return 0xFFFFu;
    pitch = (uint16)(pitch + (sub_80011B8C() & 127u));
    channel = (uint16)sub_800448F4();
    volume = (uint16)sub_80044F58(32000);
    return sub_8004486C(1, channel, sound, pitch, volume, r_u16(0x80071A20u));
}

uint32 sub_8003F9B8(uint32 actor)
{
    return sub_8003F814((uint16)actor, (sub_80011B8C() & 3u) | 8u);
}

uint32 sub_80052FF0(uint32 actor, uint32 mask, uint32 latch_mask)
{
    mask = (uint16)mask;
    if ((r_u16(actor + 226) & mask) != mask)
        return 0;
    w_u16(actor + 228, r_u16(actor + 228) | latch_mask);
    w_u16(actor + 238, r_u16(actor + 238) + 1u);
    return 1;
}

uint32 sub_80052078(uint32 actor, uint32 cone, uint32 maximum_distance)
{
    uint32 result = r_u8(actor + 240), column, index = 0, chosen = 0;
    sint32 nearest = 1000000;
    if (!r_u16(0x800716E0u))
        return result;
    result = r_u16(0x80071778u) != 0;
    if (!result)
        return result;
    column = 4u * (uint16)(r_u8(actor + 240) - 1u);
    do
    {
        uint32 offset = 28u * index;
        sint32 distance = (sint32)r_u32(0x800C0414u + column + offset);
        index = (uint16)(index + 1u);
        if (distance >= 9 && distance < (sint32)maximum_distance && distance < nearest)
        {
            uint32 heading = sub_80046B84(r_u32(0x800C0404u + offset) - r_u32(actor), r_u32(0x800C040Cu + offset) - r_u32(actor + 8), (uint32)distance);
            sint32 delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(actor + 18) - heading));
            if (delta < 0)
                delta = -delta;
            if (delta < (sint16)cone)
            {
                nearest = distance;
                /* Preserve the selected flag and heading until the scan finishes */
                chosen = 0x10000u | (uint16)heading;
            }
        }
        result = index < r_u16(0x80071778u);
    } while (result);
    if (chosen)
        w_u16(actor + 18, chosen);
    return result;
}

uint32 sub_80054184(uint32 actor)
{
    static const uint16 commands[6][3] = {{0x83, 0xF080, 30}, {0x13, 0xF010, 31}, {0x82, 0xF080, 24}, {0x12, 0xF010, 28}, {0x80, 0xF080, 21}, {0x10, 0xF010, 26}};
    uint32 i, result = 0;
    w_u16(actor + 238, 0xFFFFu);
    for (i = 0; i < 6; ++i)
    {
        result = (uint16)sub_80052FF0(actor, commands[i][0], commands[i][1]);
        if (result)
        {
            sub_80052078(actor, 768, 10000);
            return sub_800513CC(actor, commands[i][2]);
        }
    }
    return result;
}

uint32 sub_800524AC(uint32 actor)
{
    uint32 input = r_u16(actor + 226);
    sint32 direction = 1;
    if (input & 0x2000u)
    {
        direction = (input & 0x1000u) ? -512 : 0;
        if (input & 0x4000u)
            direction += 512;
        direction &= 0xFFF;
        input = r_u16(actor + 226);
    }
    if (input & 0x8000u)
    {
        direction = (input & 0x1000u) ? -1536 : -2048;
        if (input & 0x4000u)
            direction -= 512;
        direction &= 0xFFF;
    }
    input = r_u16(actor + 226);
    if (!(input & 0xA000u))
    {
        if (input & 0x1000u)
            direction = -1024;
        if (input & 0x4000u)
            direction = 1024;
    }
    return (uint32)(sint32)(sint16)direction;
}

uint32 sub_800591A4(uint32 actor, uint32 record)
{
    uint32 target = r_u32(actor + 208), result;
    if (!target || !r_u8(target + 240))
    {
        target = 0x800AFEC0u + 288u * r_u16(record + 24);
        w_u32(actor + 208, target);
    }
    result = r_u8(target + 240);
    if (result)
    {
        result = r_u8(target + 240) - 1u;
        w_u16(0x800718CCu, result);
    }
    else
        w_u16(0x800718CCu, 0);
    return result;
}

uint32 sub_80059224(uint32 current, uint32 target)
{
    sint32 delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(target - current));
    sint32 step = delta >> 2;
    if (!step && delta)
        step = delta < 0 ? -1 : 1;
    return (current + (uint32)step) & 0xFFFu;
}

uint32 sub_80059288(uint32 actor, uint32 record, uint32 turn)
{
    uint32 model = r_u32(r_u32(actor)), target = r_u32(actor + 208);
    uint32 result = sub_80046B84(r_u32(target) - r_u32(model + 8), r_u32(target + 8) - r_u32(model + 16), r_u32(record + 16 + 4u * (uint16)(r_u8(target + 240) - 1u)));
    w_u16(0x80071608u, result);
    if ((uint16)turn)
    {
        result = sub_80059224((uint32)(sint32)(sint16)r_u16(model + 26), (uint32)(sint32)(sint16)result);
        w_u16(model + 26, result);
    }
    return result;
}

uint32 sub_80059830(uint32 actor, uint32 speed)
{
    uint32 model = r_u32(r_u32(actor));
    uint32 dx = r_u32(0x800AF6D0u) - r_u32(model + 8), dz = r_u32(0x800AF6D8u) - r_u32(model + 16);
    sint32 distance = (sint32)sub_8005CBB8(dx * dx + dz * dz);
    if (distance < 256)
        speed -= (uint32)((sint32)speed >> 4);
    if (distance >= 769)
        speed += (uint32)((sint32)speed >> 2);
    return speed;
}

uint32 sub_800599FC(uint32 actor, uint32 record)
{
    uint32 target, active, model;
    sint32 threshold = 95 - 40 * (sint16)r_u16(0x800719C8u), delta;
    if (r_u16(actor + 232) >= 151 && (r_u16(0x80071794u) & 1u))
    {
        target = r_u32(actor + 208);
        if (r_u8(target + 240) && r_u16(target + 242))
            return 1;
    }
    if (r_u8(0x800719D0u) >= 80 || !(r_u16(0x80071794u) & 1u))
        return 0;
    target = r_u32(actor + 208);
    active = r_u8(target + 240);
    if (!active || !r_u16(target + 242) || (sint32)r_u32(record + 12 + 4u * active) >= 6000)
        return 0;
    model = r_u32(r_u32(actor));
    delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(target + 18) - r_u16(model + 26)));
    if (delta < 0)
        delta = -delta;
    if (delta < 513)
        return 0;
    threshold = (sint16)((uint32)threshold * r_u16(0x800716F8u));
    threshold /= 64;
    return threshold < (sint32)(sub_80011B8C() & 127u);
}

static void draft_59318_point(uint32 target, uint32 direction, uint32 distance, uint32 vector)
{
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800022u, direction << 9);
    w_u16(0x1F800024u, 0);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u32(vector, 0);
    w_u32(vector + 4, 0);
    w_u32(vector + 8, distance);
    sub_8005CC48(0x1F800000u, vector, vector);
    w_u32(vector, r_u32(vector) + r_u32(target));
    w_u32(vector + 8, r_u32(vector + 8) + r_u32(target + 8));
}

static uint32 draft_59318_valid(uint32 vector, uint32 tile)
{
    uint32 entry, kind, height;
    sub_80046324(r_u32(vector), r_u32(vector + 8), tile);
    if (r_u16(tile) == 0xFFFFu)
        return 0;
    entry = r_u32(0x80071704u) + 14u * r_u16(tile);
    kind = r_u8(entry + 8);
    height = r_u8(entry + 9);
    return kind - 1u >= 2u && (sint16)r_u16(0x80071774u) < (sint32)height && (sint32)height < (sint16)r_u16(0x800717A0u);
}

uint32 sub_80059318(uint32 actor, uint32 distance)
{
    uint32 model = r_u32(r_u32(actor)), target = r_u32(actor + 208), angle = r_u16(0x80071608u) + 2048u;
    uint32 base = (((angle & 0xFFFu) >> 9) + ((angle & 511u) >= 256u)) & 7u, chosen = base;
    uint32 mask_address = 0x800719FEu + 2u * r_u8(target + 240), mask = r_u16(mask_address), other, count = 0, valid, result;
    uint32 vector_data[4];
    uint16 tile_data[4];
    uint32 vector = draft_local_address(vector_data, sizeof(vector_data)), tile = draft_local_address(tile_data, sizeof(tile_data));
    tile_data[0] = 0xFFFFu;
    if (base < 5)
    {
        if (!(mask & 0xF0u) && (mask & 15u))
            chosen = 6;
    }
    else if (!(mask & 15u) && (mask & 0xF0u))
        base = 2;
    mask = r_u16(mask_address);
    while ((mask >> chosen) & 1u)
        chosen = (chosen + 1u) & 7u;
    other = (chosen + 1u) & 7u;
    do
    {
        draft_59318_point(target, chosen, distance, vector);
        valid = draft_59318_valid(vector, tile);
        if (!valid)
        {
            chosen = (chosen - 1u) & 7u;
            draft_59318_point(target, other, distance, vector);
            valid = draft_59318_valid(vector, tile);
            if (valid)
                chosen = other;
            else
                other = (other + 1u) & 7u;
        }
        ++count;
        if ((sint16)count == 8)
        {
            count = 0;
            distance = (uint32)((sint32)distance / 2);
        }
    } while (!valid && (sint16)count < 8);
    w_u16(mask_address, r_u16(mask_address) | (1u << chosen));
    if ((sint16)chosen != (sint16)base)
    {
        if (((sint16)base < (sint16)chosen && (sint16)(chosen - base) < 4) || ((sint16)base >= (sint16)chosen && (sint16)(base - chosen) >= 4))
            ++base;
        else
            --base;
        draft_59318_point(target, base & 7u, distance, vector);
    }
    w_u32(0x800AF6D0u, vector_data[0]);
    w_u32(0x800AF6D4u, vector_data[1]);
    w_u32(0x800AF6D8u, vector_data[2]);
    /* TODO Original copies an unwritten VECTOR pad from its local stack */
    vector_data[0] -= r_u32(model + 8);
    vector_data[2] -= r_u32(model + 16);
    result = sub_8001F8A8(vector_data[0], vector_data[2]);
    w_u32(0x80071860u, result);
    result = sub_80046B84(vector_data[0], vector_data[2], result);
    w_u16(0x8007189Cu, result);
    return result;
}

uint32 sub_8002897C(uint32 position, uint32 kind)
{
    uint16 tile_data[4];
    uint32 item, tile, result, x, y, z, pad;
    tile_data[0] = 0xFFFFu;
    item = sub_80032EF0();
    if (!item)
        return 33;
    w_u32(item + 8, 33);
    x = r_u32(position);
    y = r_u32(position + 4);
    z = r_u32(position + 8);
    pad = r_u32(position + 12);
    w_u32(item + 12, x);
    w_u32(item + 16, y);
    w_u32(item + 20, z);
    w_u32(item + 24, pad);
    result = sub_80011B8C();
    w_u32(item + 44, 0xFFFFFF00u - (result & 127u));
    w_u32(item + 48, (uint16)kind);
    tile = draft_local_address(tile_data, sizeof(tile_data));
    result = sub_80046324(r_u32(position), r_u32(position + 8), tile);
    w_u32(item + 52, result);
    w_u16(0x1F800020u, 0);
    result = sub_80011B8C();
    w_u16(0x1F800022u, result & 0xFFFu);
    w_u16(0x1F800024u, 0);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    result = sub_80011B8C();
    w_u16(0x1F800020u, (result & 63u) + 32u);
    w_u16(0x1F800022u, 0);
    w_u16(0x1F800024u, 0);
    return sub_8005CDD8(0x1F800000u, 0x1F800020u, item + 28);
}

uint32 sub_80040ABC(uint32 actor, uint32 record, uint32 maximum_distance)
{
    uint32 model = r_u32(r_u32(actor)), flags = 0, i;
    if (!(r_u16(0x80071794u) & 16u) || !r_u16(actor + 78))
        return 0;
    for (i = 0; i < 2; ++i)
    {
        uint32 player = 0x800AFEC0u + 288u * i, heading;
        sint32 delta, opposite;
        uint32 distance = r_u32(record + 16 + 4u * i);
        if (!r_u8(player + 240) || (sint32)distance >= (sint32)maximum_distance)
            continue;
        heading = sub_80046B84(r_u32(player) - r_u32(model + 8), r_u32(player + 8) - r_u32(model + 16), distance);
        delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(heading - r_u16(model + 26)));
        if (delta < 0)
            delta = -delta;
        opposite = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(heading - (r_u16(player + 18) - 2048u)));
        if (opposite < 0)
            opposite = -opposite;
        if ((sint16)delta < 768 && (sint16)opposite < 768)
        {
            flags |= 1u << i;
            w_u16(player + 232, r_u16(player + 232) | 8u);
        }
    }
    return (uint16)flags;
}

static void draft_copy_record28(uint32 destination, uint32 source)
{
    uint32 a = r_u32(source), b = r_u32(source + 4), c = r_u32(source + 8), d = r_u32(source + 12);
    w_u32(destination, a);
    w_u32(destination + 4, b);
    w_u32(destination + 8, c);
    w_u32(destination + 12, d);
    a = r_u32(source + 16);
    b = r_u32(source + 20);
    c = r_u32(source + 24);
    w_u32(destination + 16, a);
    w_u32(destination + 20, b);
    w_u32(destination + 24, c);
}

uint32 sub_80040C7C(uint32 actor, uint32 record, uint32 index)
{
    uint32 result, owner, destination;
    index = (uint16)index;
    owner = 0x80071648u + 4u * index;
    destination = 0x800C5D14u + 28u * index;
    if (r_u32(owner))
    {
        result = r_u32(destination + 16 + 4u * index);
        if ((sint32)r_u32(record + 16 + 4u * index) >= (sint32)result)
            return result;
    }
    w_u32(owner, actor);
    result = 28u * index;
    draft_copy_record28(destination, record);
    return result;
}

uint32 sub_80030FE0(uint32 record)
{
    uint32 count = r_u16(0x80071778u), result = count < 8u;
    if (result)
    {
        w_u16(0x80071778u, count + 1u);
        result = 28u * count;
        draft_copy_record28(0x800C0404u + result, record);
    }
    return result;
}
