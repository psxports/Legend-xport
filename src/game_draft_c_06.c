#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern uint32 sub_80033308();
extern uint32 sub_80033700(); extern uint32 sub_800347A4();
extern uint32 sub_80034D48(); extern uint32 sub_800357B8();
extern uint32 sub_80034B4C(); extern uint32 sub_800360E8();
extern uint32 sub_80036DB4();
extern uint32 sub_800376F0(); extern uint32 sub_80037B80(); extern uint32 sub_80037E0C();
extern uint32 sub_800384B8(); extern uint32 sub_80038718(); extern uint32 sub_80038760();
extern uint32 sub_80038B08(uint32 node); extern uint32 sub_80038E20(); extern uint32 sub_800395B8();
extern uint32 sub_800398F0(); extern uint32 sub_800399C0(); extern uint32 sub_80035AB4();
extern uint32 sub_80038BC4(); extern uint32 sub_80039E24(); extern uint32 sub_800353C8();
extern uint32 sub_80039F40(); extern uint32 sub_8003A194(); extern uint32 sub_8003A4D8();
extern uint32 sub_8003A684(); extern uint32 sub_8003A9BC(); extern uint32 sub_8003AC24();
extern uint32 sub_8003AEE4(); extern uint32 sub_8003AF78(); extern uint32 sub_8003B4BC();
extern uint32 sub_8003B900(); extern uint32 sub_8003BA20(); extern uint32 sub_8003C070();
extern uint32 sub_8003C434(); extern uint32 sub_8003C7F4(); extern uint32 sub_8003CB64();
extern uint32 sub_8003D16C(); extern uint32 sub_8003CFF0(); extern uint32 sub_8003D660();
extern uint32 sub_8003E2E8(); extern uint32 sub_8003E6BC();
extern uint32 sub_8003E924(); extern uint32 sub_8003B198(); extern uint32 sub_800369DC();
extern uint32 sub_8003D688(); extern uint32 sub_8003EA78(); extern uint32 sub_8003EC18();
extern uint32 sub_80032854(); extern uint32 sub_8003FB58();
extern uint32 sub_8003FB00(); extern uint32 sub_8003FA6C(); extern uint32 sub_8003F9B8();
extern uint32 sub_800539C0(uint32 actor, uint32 bone); extern uint32 sub_8005CC48();
extern uint32 sub_8005D138(); extern uint32 sub_8004EB88();
extern void draft_gte_control(uint32 index, uint32 value);
extern void draft_gte_data(uint32 index, uint32 value);
extern void draft_gte_command(uint32 opcode);
extern uint32 draft_gte_read(uint32 index);

uint32 sub_80032FD0(uint32 node)
{
    uint32 previous = r_u32(node), next = r_u32(node + 4u), free_head, result;
    if (previous) w_u32(previous + 4u, next);
    else w_u32(0x80071868u, next);
    if (next) w_u32(next, previous);
    free_head = r_u32(0x80071670u);
    result = r_u16(0x800718F0u) - 1u;
    w_u32(0x80071670u, node); w_u32(node + 4u, free_head); w_u16(0x800718F0u, result);
    return result;
}

uint32 sub_80034A2C(uint32 node)
{
    uint32 direction = r_u16(node + 46u), texture, position[4], i, result;
    w_u32(node + 16u, r_u32(node + 16u) + 120u);
    if (direction == 0u) {
        texture = 200u; w_u16(node + 32u, r_u16(node + 32u) + 122u);
    } else if (direction == 1u) {
        texture = 201u; w_u16(node + 32u, r_u16(node + 32u) - 130u);
    } else if (direction < 4u) {
        texture = 202u; w_u16(node + 30u, r_u16(node + 30u) + 80u);
    } else {
        /* TODO: Invalid directions inherit an unspecified volatile a2 in the original */
        texture = draft_unknown_argument("sub_80034A2C invalid direction", 2);
    }
    for (i = 0; i < 4u; ++i) position[i] = r_u32(node + 12u + 4u * i);
    if ((sint32)r_u32(node + 16u) < (sint32)r_u32(node + 36u)) {
        result = (uint16)sub_80016F80(draft_local_address(position, sizeof(position)), (uint16)texture, 5u, node + 28u);
        if (result) return result;
    }
    i = r_u32(node + 40u); w_u16(i, r_u16(i) - 1u);
    return sub_80032FD0(node);
}

uint32 sub_8003F008(void)
{
    uint32 count, source, destination, copy[4], i, node, next, result;
    w_u16(0x800AFFA8u, r_u16(0x800AFFA8u) & 1u); w_u16(0x800B00C8u, r_u16(0x800B00C8u) & 1u);
    w_u16(0x800AFFAAu, r_u16(0x800AFFAAu) >> 8); w_u16(0x800B00CAu, r_u16(0x800B00CAu) >> 8);
    w_u16(0x80071584u, r_u16(0x80071778u));
    while (r_u16(0x80071778u))
    {
        count = (uint16)(r_u16(0x80071778u) - 1u); w_u16(0x80071778u, count);
        source = (uint32)-2146696188 + 28u * count; destination = (uint32)-2146713388 + 28u * count;
        for (i = 0; i < 4u; ++i) copy[i] = r_u32(source + 4u * i);
        for (i = 0; i < 4u; ++i) w_u32(destination + 4u * i, copy[i]);
        for (i = 0; i < 3u; ++i) copy[i] = r_u32(source + 16u + 4u * i);
        for (i = 0; i < 3u; ++i) w_u32(destination + 16u + 4u * i, copy[i]);
    }
    node = r_u32(0x80071868u); w_u16(0x80071778u, 0); w_u32(0x80071648u, 0); w_u32(0x8007164Cu, 0);
    w_u32(0x800C5D24u, 1000000); w_u32(0x800C5D44u, 1000000); w_u32(0x80071620u, 0); w_u32(0x80071624u, 0);
    w_u32(0x800C1B54u, 1000000); w_u32(0x800C1B74u, 1000000); w_u16(0x80071A02u, 0); w_u16(0x80071A00u, 0); w_u8(0x80071760u, 0);
    while (node)
    {
        next = r_u32(node + 4u);
        switch (r_u32(node + 8u))
        {
        case 0: sub_8003302C(node); break; case 1: sub_80033104(node); break;
        case 4: sub_80033308(node); break; case 5: sub_80033700(node); break;
        case 6: sub_8003405C(node); break; case 7: sub_800346B0(node); break;
        case 8: sub_800347A4(node); break; case 9: sub_80034890(node); break;
        case 10: sub_80034D48(node); break; case 11: sub_80035724(node); break;
        case 12: sub_800357B8(node); break; case 13: sub_80041528(node); break;
        case 14: sub_80034B4C(node); break; case 15: sub_80035D90(node); break;
        case 16: sub_800360E8(node); break; case 17: sub_8003675C(node); break;
        case 18: sub_8003681C(node); break; case 19: sub_80036C7C(node); break;
        case 20: sub_80036DB4(node); break; case 21: sub_800376F0(node); break;
        case 22: sub_80037B80(node); break; case 23: sub_80037E0C(node); break;
        case 24: sub_800384B8(node); break; case 25: sub_80038718(node); break;
        case 26: sub_80038760(node); break; case 27: sub_80038B08(node); break;
        case 28: sub_80038E20(node); break; case 29: sub_800395B8(node); break;
        case 30: sub_800398F0(); break; case 31: sub_800399C0(node); break;
        case 32: sub_80035AB4(node); break; case 33: sub_80038BC4(); break;
        case 34: sub_80036AC8(node); break; case 35: sub_80039E24(node); break;
        case 36: sub_800353C8(node); break; case 37: sub_80039F40(node); break;
        case 38: sub_8003A194(node); break; case 39: sub_8003A4D8(node); break;
        case 40: sub_8003A684(node); break; case 41: sub_8003A9BC(node); break;
        case 42: sub_8003AC24(node); break; case 43: sub_8003AEE4(node); break;
        case 44: sub_8003AF78(node); break; case 45: sub_8003B4BC(node); break;
        case 46: sub_8003B900(); break; case 47: sub_8003BA20(node); break;
        case 48: sub_8003C070(node); break; case 49: sub_8003C434(node); break;
        case 50: sub_8003C7F4(node); break; case 51: sub_8003CB64(node); break;
        case 52: case 63: sub_8003D16C(node); break; case 53: sub_8003CFF0(node); break;
        case 54: sub_8003D660(node); break;
        case 55:
            sub_80034A2C(node); break;
        case 56: sub_8003E2E8(node); break; case 57: sub_8003E6BC(node); break;
        case 58: sub_8003E924(node); break; case 59: sub_8003B198(node); break;
        case 60: sub_800369DC(node); break; case 61: sub_8003D688(node); break;
        case 62: sub_8003EA78(node); break; case 64: sub_8003EC18(node); break;
        }
        node = next;
    }
    result = r_u16(0x8007172Cu); w_u16(0x8007171Cu, 0);
    if (result) { result = r_u16(0x800715C8u) + 1u; w_u16(0x800715C8u, result); }
    return result;
}

uint32 sub_80053B00(uint32 a1)
{
    uint32 object, animation, mode, flags, bone, i, x, result;
    if (r_u16(a1 + 132u)) { sub_80032854(r_u32(r_u32(a1 + 52u)), r_u16(a1 + 132u)); w_u16(a1 + 132u, 0); }
    object = r_u32(a1 + 64u);
    if (r_u32(object + 128u)) { if (r_u16(object + 146u)) w_u8(a1 + 281u, r_u8(a1 + 281u) | 1u); w_u32(r_u32(a1 + 64u) + 128u, 0); }
    if (r_u16(a1 + 116u))
    {
        x = r_u16(a1 + 18u); flags = r_u16(a1 + 116u);
        w_u16(a1 + 36u, 0); w_u16(a1 + 40u, 0); w_u16(a1 + 116u, 0); w_u16(a1 + 38u, x); w_u32(a1 + 44u, flags);
    }
    if (r_u16(a1 + 118u))
    {
        animation = r_u16(a1 + 246u);
        if (animation == 4u || animation == 6u || animation == 8u)
        {
            w_u16(a1 + 118u, 0); if (r_u16(a1 + 126u) == 0xFFFFu) w_u8(a1 + 281u, r_u8(a1 + 281u) | 1u);
            mode = r_u16(a1 + 122u); flags = 0;
            if (animation == 6u)
            {
                flags = mode ? 7u : 3u; if (mode) w_u16(a1 + 128u, r_u16(a1 + 128u) | 0x4000u);
                sub_80028F48(40, (uint32)-281, 937, 0, (r_u16(a1 + 18u) + r_u16(a1 + 124u)) & 4095u,
                    mode == 2u ? 384 : 256, mode == 2u ? 128 : 64, r_u32(a1 + 64u), r_u32(a1 + 60u),
                    r_u16(a1 + 128u), 250, r_u16(a1 + 130u), 168u * r_u16(a1 + 120u) + r_u32(r_u32(a1 + 52u)),
                    r_u16(a1 + 126u), mode == 2u ? flags | 8u : flags);
                sub_8003FB58();
            }
            else if (animation == 4u)
            {
                if (mode == 1u) w_u16(a1 + 128u, r_u16(a1 + 128u) | 0x4000u);
                sub_80028F48(39, 109, (uint32)-273, 218, (r_u16(a1 + 18u) + r_u16(a1 + 124u)) & 4095u,
                    400, 8, r_u32(a1 + 64u), r_u32(a1 + 60u), r_u16(a1 + 128u), 250, r_u16(a1 + 130u),
                    168u * r_u16(a1 + 120u) + r_u32(r_u32(a1 + 52u)), r_u16(a1 + 126u), 0);
                sub_8003FA6C();
            }
            else
            {
                bone = 168u * r_u16(a1 + 120u) + r_u32(r_u32(a1 + 52u)) + 8u;
                if (mode >= 3u)
                {
                    if (mode == 3u) sub_8002A560(bone, r_u16(a1 + 128u) | 0xC000u, r_u32(a1 + 64u), r_u32(a1 + 60u));
                    else
                    {
                        bone = 168u * r_u16(a1 + 120u) + r_u32(r_u32(0x800AFEF4u + 288u * (r_u8(a1 + 240u) - 1u))) + 8u;
                        sub_8002A658(bone, (r_u16(a1 + 18u) + r_u16(a1 + 124u)) & 4095u, r_u16(a1 + 128u), r_u32(a1 + 64u), r_u32(a1 + 60u));
                    }
                }
                else sub_8002A00C(bone, (r_u16(a1 + 18u) + r_u16(a1 + 124u)) & 4095u, mode, 0, r_u32(a1 + 64u), r_u32(a1 + 60u),
                    r_u16(a1 + 128u) | (mode == 1u ? 0xC000u : 0u), r_u16(a1 + 130u));
                sub_8003FB00();
            }
        }
    }
    if (r_u16(a1 + 134u)) { sub_8003F9B8(r_u16(a1 + 76u)); w_u16(a1 + 134u, 0); }
    if (r_u16(a1 + 110u))
    {
        w_u32(r_u32(a1 + 64u) + 20u, 0); flags = r_u16(a1 + 112u); x = 16u * r_u16(a1 + 114u);
        w_u32(r_u32(a1 + 64u) + 132u, r_u16(a1 + 110u)); w_u16(r_u32(a1 + 64u) + 136u, x + r_u16(a1 + 18u));
        w_u16(r_u32(a1 + 64u) + 146u, 0); w_u16(r_u32(a1 + 64u) + 148u, 80);
        for (i = 0; i < 4u; ++i)
        {
            x = r_u8(a1 + 106u + i); if (!x) continue;
            if ((uint16)sub_800539C0(a1, x)) w_u16(r_u32(a1 + 64u) + 146u, r_u16(r_u32(a1 + 64u) + 146u) | 1u);
            sub_80047534(r_u32(a1 + 64u), 168u * r_u8(a1 + 106u + i) + r_u32(r_u32(a1 + 52u)), flags & 0xFFu);
        }
        return sub_800475A8(r_u32(a1 + 64u));
    }
    result = r_u8(a1 + 281u);
    if (result) { result = r_u16(a1 + 248u); w_u8(a1 + 281u, 0); if (result) { --result; w_u16(a1 + 248u, result); } }
    return result;
}

uint32 sub_80030188(void)
{
    uint32 intensity = r_u16(0x8007196Cu), particles = r_u32(0x80071530u), delta, value, i, j, packet;
    uint32 page, clut, u0, v0, u1, v1, depth, bucket, color, height, tag, result;
    delta = r_u16(0x800717A8u); if (!intensity && !delta) return 0;
    if ((sint16)delta > 0)
    {
        value = r_u16(0x8007196Cu) + delta; w_u16(0x8007196Cu, value);
        if ((sint16)value >= 128) { w_u16(0x8007196Cu, 128); w_u16(0x800717A8u, 0); }
    }
    delta = r_u16(0x800717A8u);
    if ((sint16)delta < 0)
    {
        value = r_u16(0x8007196Cu) + delta; w_u16(0x8007196Cu, value);
        if ((sint16)value <= 0) { w_u16(0x8007196Cu, 0); w_u16(0x800717A8u, 0); }
    }
    w_u32(0x1F800028u, (uint32)(sint32)(sint16)r_u16(0x80071804u) + r_u32(0x800BC050u));
    w_u32(0x1F80002Cu, r_u32(0x800BC054u)); w_u32(0x1F800030u, r_u32(0x800BC058u));
    sub_8005CC48(0x800AFE80u, 0x1F800028u, 0x1F800028u);
    w_u16(0x1F800022u, 0); w_u16(0x1F800020u, 0);
    w_u32(0x1F800028u, (uint32)((sint32)r_u32(0x1F800028u) >> 3)); w_u32(0x1F800030u, (uint32)((sint32)r_u32(0x1F800030u) >> 4));
    w_u32(0x1F80002Cu, (uint32)((sint32)r_u32(0x1F80002Cu) >> 3)); w_u16(0x1F800024u, (r_u16(0x800719D0u) << 6) & 4095u);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    for (j = 0; j < 5u; ++j) draft_gte_control(j, r_u32(0x1F800000u + 4u * j));
    packet = r_u32(0x80071680u); page = r_u16(0x800C14A4u); clut = r_u16(0x800C14A6u);
    if (r_u16(0x8007196Cu) != 128u) page |= r_u16(0x80071782u);
    u0 = r_u8(0x800C14A8u); v0 = r_u8(0x800C14AAu); u1 = (uint8)(u0 + r_u16(0x800C14ACu) - 1u); v1 = (uint8)(v0 + r_u16(0x800C14AEu) - 1u);
    for (i = 0; i < 64u; ++i, particles += 40u)
    {
        w_u8(packet + 3u, 7); w_u8(packet + 7u, r_u16(0x8007196Cu) == 128u ? 36 : 38); w_u8(packet + 7u, r_u8(packet + 7u) & 0xFEu);
        draft_gte_control(5, r_u32(particles) - 256u); draft_gte_control(6, r_u32(particles + 4u) - 256u); draft_gte_control(7, 2u * r_u32(particles + 8u) + 128u);
        for (j = 0; j < 6u; ++j) draft_gte_data(j, r_u32(particles + 16u + 4u * j));
        draft_gte_command(0x280030u);
        value = r_u32(particles + 4u) + 1u + (i & 3u); w_u32(particles + 4u, value);
        w_u32(particles + 4u, ((uint16)value - r_u32(0x1F80002Cu)) & 511u);
        w_u32(particles + 8u, ((uint16)r_u32(particles + 8u) - r_u32(0x1F800030u)) & 511u);
        w_u32(particles, ((uint16)r_u32(particles) - (i & 3u) - r_u32(0x1F800028u)) & 511u);
        depth = r_u32(particles + 8u); bucket = (depth >> 1) + 256u;
        if ((sint32)bucket >= 2500) continue;
        w_u16(packet + 14u, clut); w_u16(packet + 22u, page);
        w_u8(packet + 12u, u0); w_u8(packet + 20u, u1); w_u8(packet + 28u, u0);
        w_u8(packet + 13u, v0); w_u8(packet + 21u, v0); w_u8(packet + 29u, v1);
        w_u32(packet + 8u, draft_gte_read(12)); w_u32(packet + 16u, draft_gte_read(13)); w_u32(packet + 24u, draft_gte_read(14));
        color = intensity - (depth >> 2); if ((sint32)color < 0) color = 0;
        color = (uint8)color - ((uint8)color >> 3); height = (uint32)(sint32)(sint16)r_u16(packet + 10u);
        if ((sint32)height < 0) height = 0; if (height >= 256u) height = 255u;
        w_u8(packet + 6u, 0); w_u8(packet + 4u, ((255u - (height >> 1)) * color) >> 7); w_u8(packet + 5u, ((255u - height) * color) >> 7);
        tag = r_u32(0x8007184Cu) + 4u * bucket; w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(tag) & 0xFFFFFFu));
        w_u32(tag, (r_u32(tag) & 0xFF000000u) | (packet & 0xFFFFFFu)); packet += 32u;
    }
    w_u32(0x80071680u, packet); result = 0;
    return result;
}

uint32 sub_8004F220(uint32 a1, uint32 a2)
{
    uint32 x = (uint32)(sint32)(sint16)a2, i, glyph, visible = 0, timer, red, green, random, packet, tag, result, amount, shade = 128, phase;
    static const uint8 zero_offsets[] = {4, 5, 12, 13, 14, 20, 21, 28, 29, 30};
    sub_80017FB0(x + 30u, 8, 1, 56); sub_80017FB0(x + 38u, 8, 1, r_u16(a1 + 208u) + 59u);
    for (i = 0; i < 6u; ++i)
    {
        glyph = (uint16)(r_u8(a1 + 250u + i) + 11u); if (glyph >= 60u) visible = 1;
        if (visible || i == 5u) sub_80017FB0(x + 8u * i + 62u, 8, 1, glyph);
    }
    sub_8004EDD8(x, 40, r_u32(0x80068AF0u + 4u * r_u8(a1 + 212u)));
    sub_80017FB0(x + 12u, 40, 1, 4u * r_u8(a1 + 212u) + r_u8(a1 + 213u) + 115u);
    timer = r_u16(0x80071A42u + 2u * r_u8(a1 + 240u));
    if (timer)
    {
        phase = r_u16(0x800719D0u) & 31u;
        if (phase >= 16u) phase = 31u - phase;
        shade += 8u * phase;
    }
    sub_8004E9E4((uint32)(sint32)(sint16)(x + 30u), 24, r_u16(a1 + 210u), 72, (uint16)shade);
    if (!(r_u16(0x800719D0u) & 3u))
    {
        timer = r_u16(0x80071A42u + 2u * r_u8(a1 + 240u));
        if (timer)
        {
            red = 255; green = (timer >= 900u) << 7; if (timer >= 1800u) green = 255; if (timer >= 2700u) { red = 0; green = 255; }
            for (i = 0; i < 2u; ++i)
            {
                random = (9u * (sub_80011B8C() & 63u)) >> 3; glyph = sub_80011B8C() & 1u;
                sub_80029F40(x + random + 30u, 32, 0xFFFFFFFFu, 2, glyph, red, green, 0);
            }
        }
    }
    sub_80017FB0(x + 39u, 51, 1, 199); sub_80017FB0(x + 45u, 38, 1, 28); sub_80017FB0(x + 53u, 40, 1, r_u8(a1 + 280u) + 59u);
    if (r_u16(a1 + 246u))
    {
        amount = r_u16(a1 + 248u);
        if (amount != 24u)
        {
            packet = r_u32(0x80071680u); w_u32(0x80071680u, packet + 40u); w_u8(packet + 3u, 8); w_u8(packet + 7u, 56);
            w_u8(packet + 6u, 128); w_u8(packet + 22u, 128); for (i = 0; i < sizeof(zero_offsets); ++i) w_u8(packet + zero_offsets[i], 0);
            w_u16(packet + 10u, 43); w_u16(packet + 18u, 43); tag = r_u32(0x8007184Cu) + 4u;
            w_u16(packet + 8u, x + amount + 82u); w_u16(packet + 24u, x + amount + 82u);
            w_u16(packet + 26u, 49); w_u16(packet + 34u, 49); w_u16(packet + 16u, x + 107u); w_u16(packet + 32u, x + 107u);
            w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(tag) & 0xFFFFFFu)); w_u32(tag, (r_u32(tag) & 0xFF000000u) | (packet & 0xFFFFFFu));
        }
        sub_80017FB0(x + 65u, 51, 1, 198);
    }
    result = r_u16(a1 + 258u);
    if (result) { amount = r_u16(a1 + 256u); glyph = r_u16(a1 + 260u); timer = r_u16(a1 + 262u); w_u16(a1 + 258u, result - 1u); return sub_8004EB88(amount, glyph, timer, x); }
    return result;
}
