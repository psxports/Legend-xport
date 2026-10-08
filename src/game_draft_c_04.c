#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern uint32 sub_800449A0(uint32 channel);
extern uint32 sub_8002F634(uint32 shade, uint32 radius);
extern uint32 sub_8004D35C(void);
extern uint32 sub_80014AE0(void);
extern uint32 sub_80014B44(void);
extern uint32 sub_80014878(void);
extern uint32 sub_80018DEC(void);
extern uint32 sub_80059C28(void);
extern uint32 sub_80059C00(void);
extern uint32 draft_guest_call0(uint32 address);
extern void draft_guest_call_void(uint32 address);
extern void nullsub_2(void);
extern uint32 sub_8005D138(uint32 vector, uint32 matrix);
extern uint32 sub_8005CDA8(uint32 vector, uint32 output);
extern uint32 sub_8005EEB8(uint32 packet, uint32 enabled, uint32 dither, uint32 page, uint32 window);
extern uint32 sub_80060DB8(uint32 packet, uint32 sprite);
extern void draft_gte_control(uint32 index, uint32 value);

uint32 sub_8002F98C(void)
{
    uint32 result, value, channel, delta;
    if (!r_u16(0x80071710u) && !r_u16(0x80071804u) && !r_u16(0x80071678u)) return 0;
    if (!r_u16(0x80071678u))
    {
        if (!r_u16(0x80071804u))
        {
            value = r_u16(0x80071684u) + 1u; w_u16(0x80071684u, value);
            result = (sint16)value < (sint16)r_u16(0x80071800u);
            if (result) return result;
            w_u16(0x80071684u, 0); w_u16(0x80071678u, (sub_80011B8C() & 3u) + 2u);
            w_u16(0x80071804u, 0); w_u16(0x80071A28u, sub_8004496C());
            /* TODO: IDA-expanded unused sound argument slots need final signature recovery */
            value = r_u16(0x800718C4u);
            sub_8004486C(1, r_u16(0x80071A28u), value, 1124, value, value);
        }
        if (!r_u16(0x80071678u)) goto render;
    }
    if (r_u16(0x800719D0u) & 3u) goto render;
    value = r_u16(0x80071804u) + r_u16(0x80071678u); w_u16(0x80071804u, value);
    if ((sint16)value <= 0)
    {
        w_u16(0x80071804u, 0); w_u16(0x80071678u, 0); channel = r_u16(0x80071A28u);
        sub_800449A0(channel);
        sub_8004486C(4, channel, 0, 0, 0, 0);
    }
    if ((sint16)r_u16(0x80071804u) >= 256)
    {
        w_u16(0x80071804u, 255); delta = r_u16(0x80071678u); w_u16(0x80071678u, 0u - delta);
    }
    result = (uint32)((sint32)(sint16)r_u16(0x80071804u) * 2);
    if (!r_u16(0x80071804u)) return result;
    channel = r_u16(0x80071A28u); value = r_u16(0x80071804u);
    sub_8004486C(2, channel, 0, 0, value, value);
    value = r_u16(0x80071804u);
    sub_8004486C(3, channel, 0, ((4u * value + 2248u) >> 1) & 0xFFFEu,
        0, 0);
render:
    if (!r_u16(0x80071804u)) return 1;
    if ((sint16)r_u16(0x80071710u) == 1)
    {
        value = r_u16(0x80071804u);
        return sub_8002F634((uint32)((sint16)value / 15),
            (value - (uint32)((sint32)(value << 16) >> 31)) >> 1);
    }
    return 0x88880000u;
}

uint32 sub_80014BA0(void)
{
    uint32 stage, result;
    w_u16(0x80071940u, 99); w_u16(0x80071594u, 0); w_u16(0x800715F0u, 0);
    w_u16(0x800AFFB6u, 2); w_u16(0x800B00D6u, 2); sub_80011BB8();
    if (r_u16(0x80071792u) == 134u) sub_8004D35C();
    sub_80014888(5); sub_800529F4(); sub_80014848(); sub_80045604();
    sub_8004B554(); sub_800129E8(); sub_80014860(); w_u16(0x80071888u, 0);
    while ((r_u8(0x800AFFB0u) || r_u8(0x800B00D0u)) && r_u16(0x80071594u) != 255u && !r_u16(0x80071888u))
    {
        sub_800149DC(); sub_80014A6C(); stage = r_u16(0x80071594u);
        if (stage == 7u || stage - 22u < 2u) draft_guest_call_void(0x800CB038u); else sub_8004CCA8();
        if (r_u8(0x800AFFA7u)) { w_u8(0x800AFFB0u, 0); w_u8(0x800AFFA7u, 0); }
        if (r_u8(0x800B00C7u)) { w_u8(0x800B00D0u, 0); w_u8(0x800B00C7u, 0); }
        if (r_u8(0x800AFFB0u) || r_u8(0x800B00D0u))
        {
            if (r_u16(0x80071888u)) continue;
            stage = r_u16(0x80071594u);
            if (stage == 7u || stage - 22u < 2u || stage == 15u || stage == 18u) sub_80014AE0();
        }
        if (!r_u16(0x80071888u)) sub_80014B44();
    }
    sub_80014878(); sub_80018DAC(); sub_800574D4(); sub_800446EC(); sub_80018DEC();
    if (r_u16(0x80071888u) == 2u) sub_80059C28();
    if (r_u16(0x80071594u) == 255u) sub_80059C00();
    result = r_u16(0x80071594u);
    if (r_u16(0x80071888u) == 2u || result == 255u) { sub_8004E4C8(11); return draft_guest_call0(0x800CB02Cu); }
    return result;
}

uint32 sub_8001EEE8(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10, uint32 a11, uint32 a12, uint32 a13)
{
    uint16 count[4];
    uint32 vertices, indices, i, object, product, j, scale[3] = {a9, a10, a11};
    sub_8005764C((uint16)a3, (uint16)a12); sub_8004E0A0((uint16)a1);
    sub_8004DD18(draft_local_address(count, sizeof(count)), 2);
    vertices = sub_80011A98(12u * count[0]); indices = sub_80011A98(2u * count[0]);
    sub_8004DD18(vertices, 12u * count[0]); sub_8004DD18(indices, 2u * count[0]);
    sub_80057514((uint16)a12);
    /* TODO: Recover the unused nullsub argument */
    nullsub_2();
    for (i = 0; i < count[0]; ++i)
    {
        for (j = 0; j < 3u; ++j)
        {
            product = r_u32(vertices + 12u * i + 4u * j) * scale[j];
            w_u32(vertices + 12u * i + 4u * j, (uint32)((sint32)product / 128));
        }
        /* TODO: Finalize IDA-expanded unused outgoing argument slots */
        sub_80019BD4((uint16)(a2 + i), (uint16)(a4 + i), a9, a10, a11, a13);
        object = 0x800AFAD8u + 8u * (i + 1u);
        sub_80019648((uint16)(a4 + i), (uint32)(sint32)(sint16)r_u16(object),
            (uint32)(sint32)(sint16)r_u16(object + 2u), (uint32)(sint32)(sint16)r_u16(object + 4u));
    }
    object = 40u * (uint16)a12;
    w_u32(0x800BFD14u + object, vertices); w_u32(0x800BFD18u + object, indices);
    w_u16(0x800BFD12u + object, a4); w_u16(0x800BFD2Cu + object, a13); w_u16(0x800BFD10u + object, count[0]);
    return object;
}

uint32 sub_8005178C(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9)
{
    sint16 local[4];
    uint32 i, destination, x, z, sum;
    local[0] = (sint16)a4;
    w_u16(a3 + 4u, 0); w_u16(a3, 0); sub_8005D138(a3, 0x1F800000u);
    for (i = 0; i < 5u; ++i) draft_gte_control(i, r_u32(0x1F800000u + 4u * i));
    w_u16(0x1F800020u, 0); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, a2); sub_8005CDA8(0x1F800020u, a9);
    w_u16(0x1F800020u, a2); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, 0); sub_8005CDA8(0x1F800020u, a9 + 16u);
    w_u16(0x1F800020u, 0); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, 0u - a2); sub_8005CDA8(0x1F800020u, a9 + 32u);
    w_u16(0x1F800020u, 0u - a2); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, 0); sub_8005CDA8(0x1F800020u, a9 + 48u);
    for (i = 0; i < 4u; ++i)
    {
        destination = a9 + 16u * i; x = r_u32(destination) + r_u32(a1); z = r_u32(destination + 8u) + r_u32(a1 + 8u);
        w_u32(destination, x); w_u32(destination + 8u, z);
        w_u32(destination + 4u, sub_80046324(x, z, draft_local_address(local, sizeof(local))));
    }
    w_u16(a3, sub_8001FCE8(a9 + 32u, a9)); w_u16(a3 + 4u, sub_8001FCE8(a9 + 16u, a9 + 48u));
    sum = r_u32(a9 + 4u) + r_u32(a9 + 20u) + r_u32(a9 + 36u) + r_u32(a9 + 52u);
    return (uint32)((sint32)sum >> 2);
}

uint32 sub_800127C8(uint32 a1, uint32 a2)
{
    uint32 slot, data, format, count, i, allocation, x, y;
    a1 = (uint16)a1; a2 = (uint16)a2;
    for (slot = 0; slot < r_u16(0x80071720u); ++slot) if (r_u16(0x800AF684u + 2u * slot) == a1) return (uint16)slot;
    if (r_u16(0x80071720u) == 22u) return 0;
    data = r_u32(r_u32(0x80071970u) + 4u * a1); format = r_u16(data);
    if (format != 2u)
    {
        count = r_u16(data + 2u); if (count >= 41u) count = 40u;
        for (i = 0; i < count; ++i)
            w_u8(0x800AF768u + 40u * r_u16(0x80071720u) + i, sub_80011DDC(r_u16(data + 4u + 2u * i), format, 0));
    }
    slot = r_u16(0x80071720u); w_u8(0x800C020Cu + slot, format); w_u16(0x800AF684u + 2u * slot, a1);
    allocation = a2;
    if (allocation == 0xFFFFu) allocation = (uint16)sub_800125FC(format);
    if (a2 != 0xFFFFu || allocation != 0xFFFFu)
    {
        sub_80012780(allocation, &x, &y);
        w_u8(0x800C04F4u + r_u16(0x80071720u), allocation);
        allocation = sub_80060C88(format, 0, x, y);
        w_u16(0x800AEE74u + 2u * r_u16(0x80071720u), allocation);
    }
    slot = r_u16(0x80071720u); w_u16(0x80071720u, slot + 1u);
    return slot;
}

uint32 sub_8001F150(uint32 a1)
{
    uint32 object = 0x800BFD08u + 40u * (uint16)a1, count = r_u16(object + 8u), source = r_u32(object + 12u);
    uint32 indices = r_u32(object + 16u), first = r_u16(object + 10u), frames = r_u16(object + 20u);
    uint32 handle = sub_8001ED84(count), root = r_u32(handle), i, parent;
    for (i = 0; i < count; ++i) sub_8001A2FC((uint16)(first + i), root + 168u * (i + 1u));
    for (i = 0; i < count; ++i)
    {
        parent = r_u16(indices + 2u * i);
        if (parent != i)
        {
            sub_8001A2BC(root + 168u * (parent + 1u), root + 168u * (i + 1u), (uint32)(sint32)(sint16)r_u16(source + 12u * i),
                (uint32)(-(sint32)(sint16)r_u32(source + 12u * i + 4u)),
                (uint32)(sint32)(sint16)r_u16(source + 12u * i + 8u));
        }
    }
    sub_8001A2BC(root, root + 168u, 0, 0, 0);
    w_u32(handle + 4u, sub_80011A98(frames * (uint16)(6u * (count + 1u) + 2u) + 4u));
    return handle;
}

uint32 sub_8002B9B4(void)
{
    uint32 x = r_u32(0x800BBFC4u), z = r_u32(0x800BBFCCu), dx, dz, cell_x, cell_z, divisor, index, address;
    if ((sint32)r_u32(0x80071900u) >= (sint32)x) x = r_u32(0x80071900u) + 1u;
    if ((sint32)x >= (sint32)r_u32(0x80071914u)) x = r_u32(0x80071914u) - 1u;
    if ((sint32)r_u32(0x80071910u) >= (sint32)z) z = r_u32(0x80071910u) + 1u;
    dx = x - r_u32(0x80071900u);
    if ((sint32)z >= (sint32)r_u32(0x8007191Cu)) z = r_u32(0x8007191Cu) - 1u;
    dz = z - r_u32(0x80071910u); divisor = r_u32(0x800718DCu);
    /* TODO: Original BREAK handling for invalid cell divisors */
    if (!divisor || (divisor == 0xFFFFFFFFu && dx == 0x80000000u)) cell_x = draft_unknown_argument("sub_8002B9B4", 0);
    else cell_x = (uint32)((sint32)dx / (sint32)divisor);
    divisor = r_u32(0x80071920u);
    if (!divisor || (divisor == 0xFFFFFFFFu && dz == 0x80000000u)) cell_z = draft_unknown_argument("sub_8002B9B4", 1);
    else cell_z = (uint32)((sint32)dz / (sint32)divisor);
    w_u16(0x800716E4u, 0); w_u32(0x800715C0u, r_u32(0x800719B8u)); w_u32(0x80071548u, r_u32(0x80071924u));
    w_u32(0x80071960u, r_u32(0x800717CCu)); w_u32(0x80071948u, r_u32(0x800717B8u));
    index = r_u32(r_u32(0x800719B8u) + 4u * (cell_z * r_u32(0x80071618u) + cell_x));
    w_u16(0x80071858u, 0); w_u16(0x8007185Au, 0); w_u16(0x8007185Cu, 0);
    w_u32(0x80071844u, r_u32(0x800716A4u)); sub_8001B7A0(1);
    for (;;)
    {
        address = r_u32(0x80071960u) + 2u * index++;
        if (r_u16(address) & 0x8000u) return address;
        sub_8002BE18(r_u16(address));
    }
}

uint32 sub_80018214(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10, uint32 a11, uint32 a12)
{
    uint32 packet = r_u32(0x80071680u), entry = 0x800C0564u + 16u * a4, page, tag, result;
    /* TODO: IDA duplicates unused parameter slots before a9; finalize the public drawing ABI */
    w_u32(0x80071680u, packet + 40u); w_u8(packet + 15u, 4); w_u8(packet + 19u, 100);
    w_u8(packet + 16u, a9); w_u8(packet + 17u, a10); w_u8(packet + 18u, a11);
    w_u8(packet + 19u, a12 ? r_u8(packet + 19u) | 2u : r_u8(packet + 19u) & 0xFDu);
    w_u16(packet + 20u, a1 - r_u16(entry + 12u)); w_u16(packet + 22u, a2 - r_u16(entry + 14u));
    w_u8(packet + 24u, r_u8(entry + 4u)); w_u8(packet + 25u, r_u8(entry + 6u));
    w_u16(packet + 28u, r_u16(entry + 8u) - 1u); w_u16(packet + 30u, r_u16(entry + 10u) - 1u);
    w_u16(packet + 26u, r_u16(entry + 2u)); page = r_u16(entry);
    if ((uint16)a12) page |= r_u16(0x8007177Eu + 2u * (uint16)a12);
    sub_8005EEB8(packet, 1, 1, page, 0); sub_80060DB8(packet, packet + 12u);
    tag = r_u32(0x8007184Cu) + 4u * a3;
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(tag) & 0xFFFFFFu));
    result = (r_u32(tag) & 0xFF000000u) | (packet & 0xFFFFFFu); w_u32(tag, result);
    return result;
}
