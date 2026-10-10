#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern uint32 sub_80060CC8(uint32 x, uint32 y);
extern uint32 sub_8005E290(uint32 rectangle, uint32 source);
extern uint32 sub_8005DFE4(uint32 mode);
extern uint32 sub_8005DC2C(uint32 environment, uint32 x, uint32 y, uint32 width, uint32 height);
extern uint32 sub_8005E814(uint32 environment);
extern uint32 sub_800678A8(uint32 destination, uint32 source, uint32 size);
extern uint32 sub_80067908(uint32 mode);
extern uint32 sub_80067F98(uint32 mode);

extern uint32 sub_80068318(uint32 table);
extern uint32 sub_800634A8(uint32 buffer, uint32 size);
extern uint32 sub_80066B08(uint32 mode, uint32 start, uint32 end, uint32 callback1, uint32 callback2);
extern uint32 sub_8005B278(uint32 frames);
extern uint32 sub_8005CC48(uint32 matrix, uint32 input, uint32 output);
extern uint32 sub_8005EEB8(uint32 packet, uint32 enabled, uint32 dither, uint32 page, uint32 window);
extern void draft_gte_control(uint32 index, uint32 value);
extern void draft_gte_data(uint32 index, uint32 value);
extern void draft_gte_command(uint32 opcode);
extern uint32 draft_gte_read(uint32 index);
extern void nullsub_2(void);

uint32 sub_800130FC(uint32 format, sint32 mode, uint32 data)
{
    uint8 occupied[10][24] = {{0}};
    PSX_RECT rectangle;
    uint32 x, y, slot, i, j, chosen_x = 0, chosen_y = 0, handle, width;
    for (slot = 0; slot < r_u16(0x800716B4u); ++slot)
    {
        sub_80011DC0(r_u16(0x800C0224u + 2u * slot), draft_local_address(&x, sizeof(x)), draft_local_address(&y, sizeof(y)));
        y -= 502u; x = (uint32)((sint32)x / 16);
        /* TODO: Recover bounds when stored palette coordinates index outside the local occupancy grid */
        if (r_u8(0x800BF1ECu + slot))
            for (j = 0; j < 16u; ++j) occupied[y][x / 2u + j] = 1;
        else occupied[y][x] = 1;
    }
    if (r_u16(0x800716B4u) == 240u) return 0;
    for (i = 0; i < 10u; ++i)
    {
        if ((sint16)format == 1)
        {
            uint32 empty = 0;
            for (j = 0; j < 16u; ++j) if (!occupied[i][j]) ++empty;
            if (empty == 16u && !chosen_y) { chosen_y = i + 502u; chosen_x = 0; }
        }
        else
        {
            for (j = 0; j < 24u; ++j)
                if (!occupied[i][j] && !chosen_y) { chosen_y = i + 502u; chosen_x = 16u * j; }
        }
    }
    if (!chosen_y) return 0;
    handle = sub_80060CC8(chosen_x, chosen_y); slot = r_u16(0x800716B4u);
    w_u16(0x800AF1F4u + 2u * slot, 0xFFFFu); w_u8(0x800BF1ECu + slot, format);
    w_u16(0x800C0224u + 2u * r_u16(0x800716B4u), handle);
    width = (sint16)format ? 256u : 16u;
    rectangle.x = (sint16)chosen_x; rectangle.y = (sint16)chosen_y;
    rectangle.w = (sint16)width; rectangle.h = 1;
    if (!(sint16)mode)
        for (i = 0; i < width; ++i) w_u16(data + 2u * i, r_u16(data + 2u * i) | 0x8000u);
    sub_8005E290(draft_local_address(&rectangle, sizeof(rectangle)), data); sub_8005DFE4(0);
    slot = r_u16(0x800716B4u); w_u16(0x800716B4u, slot + 1u);
    return slot;
}

uint32 sub_8005A044(uint32 a1)
{
    uint32 x = r_u16(a1 + 10u), y = r_u16(a1 + 12u), width = r_u16(a1 + 14u), height = r_u16(a1 + 16u);
    uint32 display_width = r_u16(a1 + 8u), bytes, i;
    w_u16(0x80071A58u, r_u16(a1 + 4u)); w_u16(0x80071A5Au, display_width);
    w_u16(0x80071A5Cu, x); w_u16(0x80071A5Eu, y); w_u16(0x80071A60u, width); w_u16(0x80071A62u, height);
    w_u32(0x80071A64u, r_u32(a1 + 20u)); w_u16(0x80071A68u, r_u16(a1 + 28u)); w_u32(0x80071A6Cu, 0);
    for (i = 0; i < 5u; ++i) w_u16(0x80071A88u + 2u * i, 0);
    sub_8005DC2C(0x80071AA4u, 0, 256, (uint32)(sint32)(sint16)display_width, 256); sub_8005DC2C(0x80071AB8u, 0, 0, (uint32)(sint32)(sint16)display_width, 256);
    w_u16(0x80071AACu, 0); w_u16(0x80071AAEu, 18); w_u16(0x80071AB0u, 0); w_u16(0x80071AB2u, 256);
    w_u16(0x80071AC0u, 0); w_u16(0x80071AC2u, 18); w_u16(0x80071AC4u, 0); w_u16(0x80071AC6u, 256);
    w_u8(0x80071AC9u, (sint16)r_u16(a1 + 4u) == 1); w_u8(0x80071AB5u, r_u8(0x80071AC9u));
    sub_80013894(); sub_8005B278(0); sub_8005E814(0x80071AA4u + 20u * r_u16(0x80071A8Cu));
    w_u16(0x80071A70u, sub_8005A7A0(x)); w_u16(0x80071A72u, y); w_u16(0x80071A74u, sub_8005A7A0(width)); w_u16(0x80071A76u, height);
    w_u16(0x80071A78u, sub_8005A7A0(x)); w_u16(0x80071A7Au, y + 256u); w_u16(0x80071A7Cu, sub_8005A7A0(width)); w_u16(0x80071A7Eu, height);
    sub_800678A8(0x80071A80u, 0x80071A70u + (uint32)((sint32)(r_u16(0x80071A8Cu) << 16) >> 13), 8);
    w_u16(0x80071A84u, sub_8005A7A0(16)); bytes = r_u32(a1 + 24u); if (!bytes) bytes = 132096u;
    w_u32(0x80071A94u, sub_80011A98(bytes)); w_u32(0x80071A98u, sub_80011A98(bytes));
    bytes = r_u16(0x80071A58u) ? (uint32)((sint32)(sint16)height * 48) : (uint32)((sint32)(height << 16) >> 11);
    w_u32(0x80071A9Cu, sub_80011A98(bytes)); w_u32(0x80071AA0u, sub_80011A98(bytes));
    sub_80067908(0); sub_80067F98(0); sub_80067BA4(sub_80059EE4);
    w_u32(0x80071534u, sub_80011A98(0x20000u)); w_u32(0x80071538u, sub_80011A98(69632));
    sub_80068318(r_u32(0x80071538u)); sub_800634A8(r_u32(0x80071534u), 64);
    return sub_80066B08((uint32)(sint32)(sint16)r_u16(0x80071A58u), 0, 0xFFFFFFFFu, 0, 0);
}

uint32 sub_80045EF4(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 point = r_u32(0x80071934u) + 12u * r_u16(a1), remaining = r_u32(point + 8u) - a3;
    uint32 other_remaining = remaining, left_x = r_u32(point), right_x = left_x;
    uint32 left_y = r_u32(point + 4u), right_y = left_y, left_z = r_u32(point + 8u), right_z = left_z;
    uint32 index, next, span, product, divisor, step;
    if ((sint32)remaining < 0) return (uint32)-1000000;
    index = 3;
    while (remaining)
    {
        next = r_u32(0x80071934u) + 12u * r_u16(a1 + 2u * index); span = left_z - r_u32(next + 8u);
        if ((sint32)span < 0) return (uint32)-1000000;
        if ((sint32)span >= (sint32)remaining)
        {
            /* TODO: Preserve original BREAK handling for zero and overflow divisors */
            product = (r_u32(next) - left_x) * remaining;
            if (!span || (span == 0xFFFFFFFFu && product == 0x80000000u)) step = draft_unknown_argument("sub_80045EF4", 0);
            else step = (uint32)((sint32)product / (sint32)span);
            left_x += step; product = (r_u32(next + 4u) - left_y) * remaining;
            if (!span || (span == 0xFFFFFFFFu && product == 0x80000000u)) step = draft_unknown_argument("sub_80045EF4", 1);
            else step = (uint32)((sint32)product / (sint32)span);
            left_y += step; remaining = 0;
        }
        else { remaining -= span; left_x = r_u32(next); left_y = r_u32(next + 4u); left_z = r_u32(next + 8u); if (!index) return (uint32)-1000000; --index; }
    }
    index = 1;
    while (other_remaining)
    {
        next = r_u32(0x80071934u) + 12u * r_u16(a1 + 2u * index); span = right_z - r_u32(next + 8u);
        if ((sint32)span < 0) return (uint32)-1000000;
        if ((sint32)span >= (sint32)other_remaining)
        {
            product = (r_u32(next) - right_x) * other_remaining;
            if (!span || (span == 0xFFFFFFFFu && product == 0x80000000u)) step = draft_unknown_argument("sub_80045EF4", 2);
            else step = (uint32)((sint32)product / (sint32)span);
            right_x += step; product = (r_u32(next + 4u) - right_y) * other_remaining;
            if (!span || (span == 0xFFFFFFFFu && product == 0x80000000u)) step = draft_unknown_argument("sub_80045EF4", 3);
            else step = (uint32)((sint32)product / (sint32)span);
            right_y += step; other_remaining = 0;
        }
        else { other_remaining -= span; right_x = r_u32(next); right_y = r_u32(next + 4u); right_z = r_u32(next + 8u); if (index == 3u) return (uint32)-1000000; ++index; }
    }
    if ((sint32)left_x < (sint32)right_x)
    {
        if ((sint32)a2 < (sint32)left_x || (sint32)a2 > (sint32)right_x) return (uint32)-1000000;
        divisor = right_x - left_x; if (!divisor) return left_y; product = (right_y - left_y) * (a2 - left_x);
        if (divisor == 0xFFFFFFFFu && product == 0x80000000u) return left_y + draft_unknown_argument("sub_80045EF4", 4);
        return left_y + (uint32)((sint32)product / (sint32)divisor);
    }
    if ((sint32)a2 > (sint32)left_x || (sint32)a2 < (sint32)right_x) return (uint32)-1000000;
    divisor = left_x - right_x; if (!divisor) return left_y; product = (left_y - right_y) * (a2 - right_x);
    if (divisor == 0xFFFFFFFFu && product == 0x80000000u) return right_y + draft_unknown_argument("sub_80045EF4", 5);
    return right_y + (uint32)((sint32)product / (sint32)divisor);
}

uint32 sub_80017C8C(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9)
{
    uint32 depth, result, entry, packet, projected, bucket, tag, state, i;
    w_u32(0x1F800030u, r_u32(a1 + 8u) - r_u32(0x800BBFCCu));
    w_u32(0x1F800028u, r_u32(a1) - r_u32(0x800BBFC4u)); w_u32(0x1F80002Cu, r_u32(a1 + 4u) - r_u32(0x800BBFC8u));
    sub_8005CC48(0x800BBFDCu, 0x1F800028u, 0x1F800028u);
    depth = r_u32(0x1F800030u); result = (sint32)depth < (sint32)a3;
    if (depth > 39999u) return result;
    result = (sint32)depth < (sint32)a4;
    if ((sint32)depth < (sint32)a3 || (sint32)depth >= (sint32)a4) return result;
    result = r_u32(0x1F800028u) + 20000u > 40000u;
    if (result) return result;
    result = (sint32)depth < 32;
    if (r_u32(0x1F80002Cu) + 20000u > 40000u) return result;
    if ((sint32)depth < 32) w_u32(0x1F800030u, 32);
    entry = 0x800C0564u + 16u * (uint16)a2;
    draft_gte_control(5, 0); draft_gte_control(6, 0); draft_gte_control(7, 0);
    draft_gte_control(1, 0); draft_gte_control(3, 0); draft_gte_control(0, 4096); draft_gte_control(2, 4096); draft_gte_control(4, 4096);
    packet = r_u32(0x80071680u); w_u32(0x80071680u, packet + 40u);
    w_u16(0x1F800020u, r_u32(0x1F800028u)); w_u16(0x1F800022u, r_u32(0x1F80002Cu)); w_u16(0x1F800024u, r_u32(0x1F800030u));
    draft_gte_data(0, r_u32(0x1F800020u)); draft_gte_data(1, r_u32(0x1F800024u)); draft_gte_command(0x180001u);
    w_u8(packet + 3u, 4); w_u8(packet + 7u, 100); for (i = 0; i < 3u; ++i) w_u8(packet + 4u + i, a9);
    projected = draft_gte_read(14); w_u32(packet + 8u, projected);
    w_u16(packet + 8u, r_u16(packet + 8u) - r_u16(entry + 12u)); w_u16(packet + 10u, r_u16(packet + 10u) - r_u16(entry + 14u));
    w_u8(packet + 12u, r_u8(entry + 4u)); w_u8(packet + 13u, r_u8(entry + 6u));
    w_u16(packet + 16u, r_u16(entry + 8u) - 1u); w_u16(packet + 18u, r_u16(entry + 10u) - 1u); w_u16(packet + 14u, r_u16(entry + 2u));
    bucket = (uint32)((sint32)(r_u16(0x1F800024u) << 16) >> 20); result = bucket - 16u < 2484u;
    if (!result) return result;
    tag = r_u32(0x8007184Cu) + 4u * bucket; state = r_u32(0x80071680u);
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(tag) & 0xFFFFFFu));
    w_u32(tag, (r_u32(tag) & 0xFF000000u) | (packet & 0xFFFFFFu)); w_u32(0x80071680u, state + 40u);
    /* The original call stores a null texture window in its fifth argument */
    sub_8005EEB8(state, 1, 1, r_u16(entry), 0);
    tag = r_u32(0x8007184Cu) + 4u * bucket;
    w_u32(state, (r_u32(state) & 0xFF000000u) | (r_u32(tag) & 0xFFFFFFu));
    result = (r_u32(tag) & 0xFF000000u) | (state & 0xFFFFFFu); w_u32(tag, result);
    return result;
}

uint32 sub_8004B930(uint32 a1)
{
    static const uint32 early[] = {0x800719D0u, 0x800715E8u, 0x8007156Cu, 0x8007155Cu, 0x8007158Cu};
    static const uint32 zero[] = {0x80071654u, 0x800716C4u, 0x80071724u, 0x800716BCu, 0x80071778u,
        0x80071820u, 0x8007172Cu, 0x8007199Cu, 0x8007171Cu, 0x800718D4u, 0x80071904u, 0x80071558u,
        0x800717F4u, 0x80071808u, 0x800717ACu, 0x80071744u, 0x800715CCu, 0x8007188Cu, 0x800716E8u,
        0x8007196Cu, 0x800717A8u, 0x80071804u, 0x80071678u, 0x80071710u, 0x80071A48u,
        0x80071684u, 0x800715BCu, 0x80071930u, 0x800717C4u};
    uint32 i, value[4];
    sub_80031154(); sub_80032DFC(); sub_80044800(); sub_80052B94(0x800AFEC0u, (uint16)a1, 37); sub_80052B94(0x800AFFE0u, (uint16)a1 + 1u, 37);
    w_u32(0x80071A3Cu, sub_80011A98(128)); w_u16(0x80071798u, 64); w_u32(0x80071A1Cu, sub_80011A98(256));
    for (i = 0; i < sizeof(early) / sizeof(early[0]); ++i) w_u16(early[i], 0);
    w_u16(0x80071A50u, 8); w_u16(0x8007198Cu, 0); w_u16(0x800719FCu, 0); w_u16(0x80071750u, 0); w_u16(0x80071828u, 0);
    sub_8004B87C(); sub_80020124();
    for (i = 0; i < 4u; ++i) value[i] = r_u32(0x800AFEC0u + 4u * i);
    for (i = 0; i < 4u; ++i) w_u32(0x800BBFC4u + 4u * i, value[i]);
    for (i = 0; i < 4u; ++i) value[i] = r_u32(0x800AFEC0u + 4u * i);
    for (i = 0; i < 4u; ++i) w_u32(0x800BC0A4u + 4u * i, value[i]);
    sub_8002043C(768, 8, 0); sub_8002046C(768, 8, 0); w_u8(0x800715E4u, 1); w_u16(0x80071800u, 600);
    w_u32(0x800BD1F4u, 0); w_u32(0x800BD1FCu, 0); w_u32(0x800BD1F8u, 0); w_u32(0x80071A08u, 0);
    for (i = 0; i < sizeof(zero) / sizeof(zero[0]); ++i) w_u16(zero[i], 0);
    w_u8(0x800716ECu, 0); w_u16(0x80071810u, 1); w_u16(0x80071A34u, 0xFFFFu); w_u8(0x80071760u, 0);
    for (i = 0; i < 16u; ++i) { w_u8(0x800C9D68u + i, 0); w_u16(0x800BEE88u + 18u * i, 0xFFFFu); }
    w_u16(0x8007182Cu, 0); w_u16(0x8007176Cu, 0); w_u16(0x800719E4u, 0); w_u16(0x80071A38u, 0); w_u16(0x800715C8u, 0);
    return 0;
}

uint32 sub_800129E8(void)
{
    PSX_RECT rectangle;
    uint32 bitmap = sub_80011A98(128), slots = sub_80011A98(2048), i, id, offset = 0, file_offset, format, x, y, bytes;
    uint32 buffer, buffer_known = 0;
    for (i = 0; i < 64u; ++i) w_u16(bitmap + 2u * i, 0);
    for (i = r_u16(0x80071600u); i < r_u16(0x80071720u); ++i)
    {
        id = r_u16(0x800AF684u + 2u * i); if (id == 0xFFFFu) continue;
        w_u16(slots + 2u * id, i); w_u16(bitmap + 2u * (id >> 4), r_u16(bitmap + 2u * (id >> 4)) | (1u << (id & 15u)));
    }
    sub_8004E0A0(796);
    for (id = 0; id < 1024u; ++id)
    {
        if (!(r_u16(bitmap + 2u * (id >> 4)) & (1u << (id & 15u)))) continue;
        file_offset = r_u32(r_u32(0x80071650u) + 4u * id); format = r_u16(r_u32(r_u32(0x80071970u) + 4u * id));
        sub_8004DE84(file_offset - offset); sub_80012780(r_u8(0x800C04F4u + r_u16(slots + 2u * id)), &x, &y);
        offset = file_offset; rectangle.x = (sint16)x; rectangle.y = (sint16)y; rectangle.h = 256;
        if (format <= 2u)
        {
            bytes = 0x8000u << format; buffer = sub_80011A98(bytes); sub_8004DD18(buffer, bytes);
            offset = file_offset + bytes; rectangle.w = (sint16)(64u << format); if (!format) sub_800129B4(buffer);
            buffer_known = 1;
        }
        else if (!buffer_known)
        {
            /* TODO: An invalid first format uses an undefined incoming s5 and rectangle width */
            buffer = draft_unknown_argument("sub_800129E8 invalid first format", 0);
            rectangle.w = (sint16)draft_unknown_argument("sub_800129E8 invalid first format", 1);
        }
        /* An invalid later format retains the previous buffer and width as the original does */
        sub_8005E290(draft_local_address(&rectangle, sizeof(rectangle)), buffer); sub_8005DFE4(0); sub_80011AF8(buffer);
    }
    nullsub_2(); sub_80011AF8(slots); return sub_80011AF8(bitmap);
}
