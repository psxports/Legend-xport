#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_8005CDD8(uint32 matrix, uint32 input, uint32 output);
extern uint32 sub_8003F928(uint32 actor);
extern uint32 sub_8002897C(uint32 mesh, uint32 type);
extern uint32 sub_80028F48(uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_80029A18(uint32, uint32);
extern uint32 sub_8002A270(uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_8002AB88(uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_8002A7AC(uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_8002ACAC(uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_8002AD78(uint32, uint32);
extern uint32 sub_8003FA6C(void);
extern uint32 sub_8003FB00(void);

uint32 sub_80041160(uint32 actor)
{
    uint32 result = r_u16(0x800719D0u) & 3u;
    if (!result)
    {
        result = r_u16(actor + 232u);
        if (result)
        {
            --result;
            w_u16(actor + 232u, result);
        }
    }
    return result;
}

uint32 sub_80040FD0(uint32 actor, uint32 record, uint32 index)
{
    uint32 destination, result, words[4], i;
    index &= 0xFFFFu;
    destination = 0x800C1B44u + 28u * index;
    if (r_u32(0x80071620u + 4u * index))
    {
        result = r_u32(destination + 16u + 4u * index);
        if ((sint32)r_u32(record + 16u + 4u * index) >= (sint32)result)
            return result;
    }
    w_u32(0x80071620u + 4u * index, actor);
    result = 28u * index;
    for (i = 0u; i < 4u; ++i)
        words[i] = r_u32(record + 4u * i);
    for (i = 0u; i < 4u; ++i)
        w_u32(destination + 4u * i, words[i]);
    for (i = 0u; i < 3u; ++i)
        words[i] = r_u32(record + 16u + 4u * i);
    for (i = 0u; i < 3u; ++i)
        w_u32(destination + 16u + 4u * i, words[i]);
    return result;
}

uint32 sub_80040E0C(uint32 actor, uint32 record, uint32 limit)
{
    uint32 mesh = r_u32(r_u32(actor)), result = 0u, i, player, distance, angle;
    sint32 first, second;
    if (!(r_u16(0x80071794u) & 16u) || !r_u16(actor + 78u))
        return 0u;
    for (i = 0u; i < 2u; ++i)
    {
        player = 0x800AFEC0u + 288u * i;
        if (!r_u8(player + 240u))
            continue;
        distance = r_u32(record + 16u + 4u * i);
        if ((sint32)distance >= (sint32)limit)
            continue;
        angle = sub_80046B84(r_u32(player) - r_u32(mesh + 8u), r_u32(player + 8u) - r_u32(mesh + 16u), distance);
        first = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(angle - (r_u16(mesh + 26u) - 2048u)));
        second = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(angle - (r_u16(player + 18u) - 2048u)));
        if (first < 0)
            first = -first;
        if (second < 0)
            second = -second;
        if ((sint16)first < 768 && (sint16)second < 768)
        {
            result |= 1u << i;
            w_u16(player + 232u, r_u16(player + 232u) | 16u);
        }
    }
    return result;
}

uint32 sub_8003FDCC(uint32 actor, uint32 mesh)
{
    uint32 i, part, value, result, mode, bone, angle, flags;
    if (r_u16(actor + 136u))
    {
        sub_80032854(mesh, r_u16(actor + 136u));
        w_u16(actor + 136u, 0u);
    }
    if (r_u16(actor + 120u))
    {
        value = r_u16(actor + 120u);
        w_u16(actor + 60u, 0u);
        w_u16(actor + 64u, 0u);
        w_u16(actor + 120u, 0u);
        w_u16(actor + 62u, r_u16(mesh + 26u));
        w_u32(actor + 68u, value);
    }
    if (r_u16(actor + 114u))
    {
        w_u32(r_u32(actor + 16u) + 20u, 0u);
        value = r_u16(actor + 116u);
        w_u32(r_u32(actor + 16u) + 132u, r_u16(actor + 114u));
        w_u16(r_u32(actor + 16u) + 136u, 16u * r_u16(actor + 118u) + r_u16(mesh + 26u));
        w_u16(r_u32(actor + 16u) + 138u, 0xFFFFu);
        w_u16(r_u32(actor + 16u) + 148u, 80u);
        for (i = 0u; i < 4u; ++i)
        {
            part = r_u8(actor + 110u + i);
            if (part)
                sub_80047534(r_u32(actor + 16u), r_u32(r_u32(actor)) + 168u * part, value & 255u);
        }
        sub_800475A8(r_u32(actor + 16u));
    }
    result = r_u16(actor + 122u);
    if (!result)
        return result;
    value = r_u16(actor + 222u);
    w_u16(actor + 122u, 0u);
    mode = r_u16(actor + 126u);
    bone = r_u32(r_u32(actor)) + 168u * r_u16(actor + 124u) + 8u;
    angle = (r_u16(mesh + 26u) + r_u16(actor + 128u)) & 4095u;
    flags = r_u16(actor + 132u);
    switch (value)
    {
        case 7:
            sub_80028F48(39u, 109u, 738u, 218u, angle, 200u, 8u, r_u32(actor + 16u), r_u32(actor + 12u), 4u, 80u, 1u, bone - 8u, r_u16(actor + 130u), 0u);
            return sub_8003FA6C();
        case 12:
            for (i = 0u; i < 4u; ++i)
                sub_80029A18(mesh, r_u32(actor + 12u));
            return 0u;
        case 19:
            if (mode < 2u)
                sub_8002A270(bone, angle, mode, 0u, r_u32(actor + 16u), r_u32(actor + 12u), flags | (mode == 0u ? 0x4000u : 0u), r_u16(actor + 134u));
            else if (mode == 2u)
                sub_8002AB88(bone, angle, flags, 5u, r_u32(actor + 16u), r_u32(actor + 12u));
            else if (mode == 3u)
                sub_8002A7AC(bone, angle, flags, r_u32(actor + 16u), r_u32(actor + 12u), 52u);
            return sub_8003FB00();
        case 20:
            if (!mode)
                return sub_8002ACAC(bone, angle, flags, r_u32(actor + 16u), r_u32(actor + 12u), actor);
            if (mode == 1u)
            {
                for (i = 0u; i < 2u; ++i)
                    sub_8002AD78(mesh, r_u32(actor + 12u));
                return 0u;
            }
            return 1u;
        case 26:
            if (!mode)
                sub_8002A7AC(bone, angle, flags, r_u32(actor + 16u), r_u32(actor + 12u), 63u);
            else if (mode == 1u || mode == 2u)
                sub_8002A270(bone, angle, mode == 1u ? 1u : 0u, 0u, r_u32(actor + 16u), r_u32(actor + 12u), flags | (mode == 2u ? 0x4000u : 0u), r_u16(actor + 134u));
            return sub_8003FB00();
        default:
            /* The switch bounds and jump-table load leave an incidental carrier */
            return value >= 7u && value < 27u ? 0x800402F4u : 0u;
    }
}

uint32 sub_8003F7F4(uint32 actor)
{
    uint32 result = r_u32(actor + 44u);
    if (result)
    {
        w_u32(result + 200u, 0u);
        w_u32(actor + 44u, 0u);
    }
    return result;
}

uint32 sub_80040748(uint32 actor, uint32 mesh)
{
    uint32 player = 0x800AFEC0u + 288u * r_u16(0x80071928u);
    uint32 x = r_u32(player), z = r_u32(player + 8u), distance, result;

    distance = sub_8001F8A8(x - r_u32(mesh + 8u), z - r_u32(mesh + 16u));
    result = sub_80046B84(x - r_u32(mesh + 8u), z - r_u32(mesh + 16u), distance);
    w_u16(mesh + 26u, result);
    return result;
}

uint32 sub_8003FD5C(uint32 mesh, uint32 actor, uint32 scale)
{
    sint32 magnitude = (sint16)scale;
    uint32 angle, state;
    if (magnitude < 0)
        magnitude = -magnitude;
    angle = r_u16(r_u32(actor + 12u) + 136u);
    if (magnitude >= 1024)
    {
        angle = (angle - 2048u) & 4095u;
        state = 14u;
    }
    else
        state = 13u;
    w_u16(mesh + 26u, angle);
    return sub_8005915C(actor, state);
}

uint32 sub_8003FCC4(uint32 mesh, uint32 actor, uint32 scale)
{
    sub_8003F8D0(r_u16(actor + 80u));
    return sub_8003FD5C(mesh, actor, scale);
}

uint32 sub_80040658(uint32 actor)
{
    uint32 mesh = r_u32(r_u32(actor)) + 176u;
    sub_8002897C(mesh, 187u);
    sub_8002897C(mesh, 188u);
    sub_8002897C(mesh, 189u);
    return sub_8002897C(mesh, 187u);
}

uint32 sub_800407D8(uint32 actor)
{
    uint32 mesh, input, mode, result, health;
    sub_8003F7F4(actor);
    mesh = r_u32(r_u32(actor));
    input = r_u16(0x80071794u);
    w_u32(r_u32(actor + 12u) + 128u, 0u);
    if (input & 128u)
    {
        result = r_u16(0x800717FCu);
        if (!result)
            return result;
    }
    mode = r_u16(0x800719F4u);
    result = mode < 2u;
    if (mode == 1u)
    {
        result = r_u16(actor + 224u);
        if (!result)
            return result;
        sub_80040748(actor, mesh);
        health = r_u16(actor + 224u);
        w_u16(actor + 236u, 60u);
        w_u16(actor + 224u, health < 17u ? 0u : health - 16u);
        w_u16(r_u32(actor + 12u) + 136u, (r_u16(mesh + 26u) + 2048u) & 4095u);
        if (r_u16(actor + 224u))
            return sub_8003FCC4(mesh, actor, 1024u);
        if (r_u16(0x80071794u) & 128u)
        {
            w_u16(0x800717C4u, 60u);
            w_u16(0x80071A34u, r_u16(0x80071928u));
            sub_80013F80();
            sub_8003F928(r_u16(actor + 80u));
            return sub_8005915C(actor, 15u);
        }
        sub_8003F928(r_u16(actor + 80u));
        return sub_8003FD5C(mesh, actor, 1024u);
    }
    if (mode >= 2u)
    {
        result = 2u;
        if (mode != 2u)
            return result;
        result = input & 256u;
        if (r_u16(actor + 224u) && result)
        {
            w_u32(mesh + 12u, r_u32(actor + 204u));
            w_u32(actor + 72u, 0u);
            sub_8005915C(actor, 26u);
            result = (sub_80011B8C() & 63u) + 180u;
            w_u16(actor + 220u, result);
        }
    }
    else if (!mode)
    {
        result = input & 512u;
        if (r_u16(actor + 224u) && result)
        {
            w_u32(mesh + 12u, r_u32(actor + 204u));
            w_u32(actor + 72u, 0u);
            result = sub_8005915C(actor, 37u);
            w_u16(actor + 220u, 0u);
        }
    }
    return result;
}

uint32 sub_8003F994(uint32 actor)
{
    return sub_8003F814(actor & 0xFFFFu, 7u);
}

void sub_8004FC14(void)
{
    uint32 player = 0u, aligned = 0u, phase, frame, packet, i, ot;
    sint32 heading, old_x, old_y;
    if (r_u8(0x800AFFB0u))
        player = 0x800AFEC0u;
    if (r_u8(0x800B00D0u) && (!player || (sint16)r_u16(player + 268u) < (sint16)r_u16(0x800B00ECu)))
        player = 0x800AFFE0u;
    if (!player)
        return;
    if (r_u8(player + 245u))
    {
        heading = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(r_u16(r_u32(0x800716D0u) + 2u * (uint32)(sint32)(sint16)r_u16(player + 268u)) - r_u16(player + 18u)));
        if (heading < 0)
            heading = -heading;
        aligned = heading < 256;
    }
    if ((sint16)r_u16(0x800717A0u) - (sint16)r_u16(player + 268u) < 2 || aligned)
    {
        w_u16(0x80071904u, 0u);
        return;
    }
    if ((sint16)r_u16(0x80071904u) < 32)
    {
        w_u16(0x80071904u, r_u16(0x80071904u) + 1u);
        w_u16(0x800718D4u, 0u);
        return;
    }
    phase = r_u16(0x800718D4u) + 1u;
    w_u16(0x800718D4u, phase);
    frame = phase & 63u;
    if (frame >= 36u)
        return;
    if (frame >= 32u)
        frame = 31u;
    frame &= 15u;
    if (frame == 1u && (sint16)phase >= 91)
        sub_8004486C(1u, 1u, 0u, 1024u, 16000u, 512u);
    ReadGeomOffset(&old_x, &old_y);
    SetGeomOffset(290, 80);
    w_u16(0x1F800020u, r_u16(0x800BBFD4u));
    w_u16(0x1F800024u, r_u16(0x800BC0C6u));
    w_u16(0x1F800022u, (r_u16(r_u32(0x800716D0u) + 2u * (uint32)(sint32)(sint16)r_u16(player + 268u)) - 1024u + r_u16(0x800BBFD6u)) & 4095u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u32(0x1F800028u, 0u);
    w_u32(0x1F80002Cu, 0u);
    w_u32(0x1F800030u, 4080u);
    for (i = 0u; i < 5u; ++i)
        draft_gte_control(i, r_u32(0x1F800000u + 4u * i));
    draft_gte_control(5u, 0u);
    draft_gte_control(6u, 0u);
    draft_gte_control(7u, 4080u);
    packet = r_u32(0x80071680u);
    w_u32(0x80071680u, packet + 40u);
    w_u16(0x1F800024u, 0u);
    w_u16(0x1F800020u, 8u * (2u * frame - r_u16(0x800C0F70u)));
    w_u16(0x1F800022u, 0u - 8u * r_u16(0x800C0F72u));
    draft_gte_data(0u, r_u32(0x1F800020u));
    draft_gte_data(1u, r_u32(0x1F800024u));
    draft_gte_command(0x180001u);
    w_u8(packet + 3u, 9u);
    w_u8(packet + 7u, 44u);
    w_u32(packet + 8u, draft_gte_read(14u));
    w_u16(0x1F800020u, r_u16(0x1F800020u) + 8u * r_u16(0x800C0F6Cu));
    draft_gte_data(0u, r_u32(0x1F800020u));
    draft_gte_data(1u, r_u32(0x1F800024u));
    draft_gte_command(0x180001u);
    w_u16(packet + 22u, r_u16(0x800C0F64u));
    w_u32(packet + 16u, draft_gte_read(14u));
    w_u16(0x1F800022u, r_u16(0x1F800022u) + 8u * r_u16(0x800C0F6Eu));
    draft_gte_data(0u, r_u32(0x1F800020u));
    draft_gte_data(1u, r_u32(0x1F800024u));
    draft_gte_command(0x180001u);
    w_u8(packet + 7u, r_u8(packet + 7u) | 1u);
    w_u16(packet + 14u, r_u16(0x800C0F66u));
    w_u32(packet + 32u, draft_gte_read(14u));
    w_u16(0x1F800020u, r_u16(0x1F800020u) - 8u * r_u16(0x800C0F6Cu));
    draft_gte_data(0u, r_u32(0x1F800020u));
    draft_gte_data(1u, r_u32(0x1F800024u));
    draft_gte_command(0x180001u);
    for (i = 0u; i < 4u; ++i)
    {
        w_u8(packet + 12u + 8u * i, r_u8(0x800C0F68u) + (i & 1u ? r_u8(0x800C0F6Cu) - 1u : 0u));
        w_u8(packet + 13u + 8u * i, r_u8(0x800C0F6Au) + (i & 2u ? r_u8(0x800C0F6Eu) - 1u : 0u));
    }
    w_u32(packet + 24u, draft_gte_read(14u));
    ot = r_u32(0x8007184Cu) + 4u;
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(ot) & 0xFFFFFFu));
    w_u32(ot, (r_u32(ot) & 0xFF000000u) | (packet & 0xFFFFFFu));
    SetGeomOffset(old_x, old_y);
}

uint32 sub_80023E84(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 id)
{
    uint32 index, entry, result, second;
    for (index = 0u; index < 16u; ++index)
    {
        entry = 0x800BEE88u + 18u * index;
        if (r_u16(entry) != 0xFFFFu)
            continue;
        w_u16(entry, id);
        w_u16(entry + 2u, a1);
        w_u16(entry + 4u, a2);
        w_u16(entry + 6u, a3);
        w_u16(entry + 8u, a4);
        result = r_u32(0x80071850u);
        second = r_u32(0x80071854u);
        w_u32(entry + 10u, result);
        w_u32(entry + 14u, second);
        return result;
    }
    return 0u;
}

uint32 sub_80023F10(uint32 image, uint32 slot, uint32 bone, uint32 xscale, uint32 yscale, uint32 zscale)
{
    uint32 item = sub_80032EF0(), model;
    sint32 product;
    if (!item)
        return 0u;
    w_u32(item + 8u, 35u);
    model = sub_8001F150(slot & 0xFFFFu);
    w_u32(item + 12u, model);
    w_u16(item + 16u, slot);
    w_u32(item + 20u, r_u32(model + 4u));
    sub_8001A2BC(r_u32(r_u32(image)) + 168u * (bone & 0xFFFFu), r_u32(model) + 168u, 0u, 0u, 0u);
    product = (sint32)(400u * xscale);
    w_u32(item + 84u, (uint32)(product / 128));
    product = (sint32)(400u * yscale);
    w_u32(item + 88u, (uint32)(product / 128));
    product = (sint32)(400u * zscale);
    w_u32(item + 92u, (uint32)(product / 128));
    w_u32(item + 76u, image);
    w_u32(image + 4u, item + 12u);
    w_u32(item + 80u, 0u);
    return sub_80057A14(item + 16u, 0u);
}

uint32 sub_80051550(uint32 position, uint32 speed, uint32 angles)
{
    uint32 result;
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800024u, 0u);
    w_u16(0x1F800022u, r_u16(angles + 2u));
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, 0u);
    w_u16(0x1F800022u, 0u);
    w_u16(0x1F800024u, speed);
    sub_8005CDD8(0x1F800000u, 0x1F800020u, 0x1F800028u);
    w_u32(position, r_u32(position) + r_u32(0x1F800028u));
    result = r_u32(position + 8u) + r_u32(0x1F800030u);
    w_u32(position + 8u, result);
    return result;
}

uint32 sub_8004A9E8(void)
{
    static const uint32 tuning[][2] = {{0x800AEA6Eu, 6}, {0x800AEA70u, 6}, {0x800AEA74u, 10}, {0x800AEA7Au, 20}, {0x800AEA6Cu, 5}, {0x800AEA72u, 5}, {0x800AEA7Cu, 3}, {0x800BF918u, 900}, {0x800AEA7Eu, 21}, {0x800BF91Au, 800}, {0x800AEA80u, 4}, {0x800BF91Cu, 900}, {0x800AEA82u, 21}, {0x800BF91Eu, 800}};
    static const uint32 lighting[] = {0x800AFB4Cu, 0x800AFB4Au, 0x800AFB48u, 0x800AFB3Cu, 0x800AFB3Au, 0x800AFB38u, 0x800AFB44u, 0x800AFB42u, 0x800AFB40u, 0x800AFB54u, 0x800AFB52u, 0x800AFB50u};
    static const uint32 slots[] = {56, 58, 57, 59, 60, 61, 62, 63, 64, 65, 66};
    uint32 i;
    sub_800456A8(0u, 700u);
    for (i = 0; i < sizeof(tuning) / sizeof(tuning[0]); ++i)
        w_u16(tuning[i][0], tuning[i][1]);
    sub_8001EE9C();
    w_u16(0x800AFB1Cu, 300u);
    w_u16(0x800AFB1Au, 300u);
    w_u16(0x800AFB18u, 300u);
    w_u16(0x800AFB24u, 300u);
    w_u16(0x800AFB22u, 300u);
    w_u16(0x800AFB20u, 300u);
    for (i = 0; i < sizeof(lighting) / sizeof(lighting[0]); ++i)
        w_u16(lighting[i], 200u);
    sub_8001EEE8(60u, 63u, 59u, 41u, 400u, 400u, 400u, 0u, 2u);
    for (i = 0; i < sizeof(slots) / sizeof(slots[0]); ++i)
        sub_80019BD4(78u + i, slots[i], 400u, 400u, 400u, 2u);
    sub_80019648(56u, 300u, 300u, 300u);
    sub_80019648(58u, 120u, 120u, 120u);
    sub_80019648(57u, 120u, 120u, 120u);
    sub_80019648(59u, 120u, 120u, 120u);
    sub_80019648(61u, 300u, 300u, 100u);
    sub_80019648(62u, 100u, 100u, 100u);
    sub_80019648(63u, 200u, 200u, 200u);
    sub_80019648(64u, 200u, 200u, 200u);
    sub_80019648(65u, 100u, 100u, 100u);
    return sub_80019648(60u, 100u, 100u, 100u);
}
