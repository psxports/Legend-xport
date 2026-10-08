#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern void draft_gte_control(uint32 index, uint32 value);
extern uint32 sub_8003160C(uint32 index);
extern uint32 sub_80021F28(void);
extern uint32 sub_80067FC8(uint32 stream, uint32 data, uint32 length);
extern uint32 sub_80066B98(uint32 stream);
extern uint32 sub_80062128(void);
extern uint32 sub_800621A8(uint32 mode, uint32 mask);
extern uint32 sub_8005E168(PSX_RECT *rect, uint32 r, uint32 g, uint32 b);
extern uint32 sub_8005DFE4(uint32 mode);

uint32 sub_80018B38(void)
{
    uint32 i, source, destination, a, b, c, d;
    w_u32(0x800718B8u, sub_80011A98(5600u));
    for (i = 0; i < 350u; ++i)
    {
        source = 0x800C0564u + 16u * i;
        destination = r_u32(0x800718B8u) + 16u * i;
        a = r_u32(source); b = r_u32(source + 4u);
        c = r_u32(source + 8u); d = r_u32(source + 12u);
        w_u32(destination, a); w_u32(destination + 4u, b);
        w_u32(destination + 8u, c); w_u32(destination + 12u, d);
    }
    return i;
}

uint32 sub_8003220C(void)
{
    uint32 i;
    for (i = 0; i < 5u; ++i)
        draft_gte_control(i, r_u32(0x800BBFDCu + 4u * i));
    for (i = 0; i < 8u; ++i)
        if (r_u32(0x800BD408u + 4u * i)) sub_8003160C(i);
    return 0;
}

uint32 sub_800225C8(void)
{
    sub_80020DD8();
    if (r_u8(0x800715E4u)) sub_800215EC(); else sub_80021F28();
    sub_80020574(); sub_80020B54();
    w_u32(0x800BC0C8u, sub_80046324(r_u32(0x800BBFC4u), r_u32(0x800BBFCCu), 0x800BC04Cu));
    sub_800204C0(); sub_800210E8();
    return sub_80020CFC();
}

uint32 sub_8004486C(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10)
{
    uint32 index, destination;
    /* TODO: IDA includes unused argument slots a5 through a8; retain the shared draft signature */
    if (!(uint16)a9 && (uint16)a1 == 1u) return 1u;
    index = r_u16(0x80071628u);
    w_u16(0x80071628u, index + 1u);
    destination = 0x800AF028u + 12u * index;
    if (r_u16(0x80071628u) == 24u) w_u16(0x80071628u, 0);
    w_u16(destination, a1); w_u16(destination + 2u, a2);
    w_u16(destination + 4u, a3); w_u16(destination + 6u, a4);
    w_u16(destination + 8u, a9); w_u16(destination + 10u, a10);
    return 24u;
}

uint32 sub_800449B8(uint32 a1, uint32 a2)
{
    uint32 product = a1 * r_u32(0x800717ECu), adjusted, result;
    sint32 left, right;
    adjusted = product + ((sint32)product < 0 ? 255u : 0u);
    left = right = (sint32)adjusted >> 8;
    if ((sint32)a2 < 512)
    {
        product = (uint32)right * a2;
        adjusted = product + ((sint32)product < 0 ? 511u : 0u);
        right = (sint32)adjusted >> 9;
    }
    result = 1023u;
    if ((sint32)a2 >= 513)
    {
        product = (uint32)left * (1023u - a2);
        result = product + ((sint32)product < 0 ? 511u : 0u);
        left = (sint32)result >> 9;
    }
    w_u16(0x800C9E08u, (uint32)left);
    w_u16(0x800C9E0Au, (uint32)right);
    return result;
}

uint32 sub_80032EF0(void)
{
    uint32 node, next, head;
    if (r_u16(0x800718F0u) >= 71u) return 0;
    node = r_u32(0x80071670u);
    if (!node) return 0;
    next = r_u32(node + 4u); head = r_u32(0x80071868u);
    w_u32(node, 0); w_u32(0x80071670u, next); w_u32(node + 4u, head);
    if (head) w_u32(head, node);
    w_u32(0x80071868u, node);
    w_u16(0x800718F0u, r_u16(0x800718F0u) + 1u);
    return node;
}

uint32 sub_800448F4(void)
{
    uint32 attempts = 0, index;
    do
    {
        w_u16(0x800719A4u, r_u16(0x800719A4u) + 1u);
        if (r_u16(0x800719A4u) == 24u) w_u16(0x800719A4u, 0);
        index = r_u16(0x800719A4u);
        if (!r_u8(0x800AEEB0u + index)) break;
        ++attempts;
    } while ((uint16)attempts != 32u);
    return index;
}

uint32 sub_80026D18(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10, uint32 a11, uint32 a12, uint32 a13)
{
    /* TODO: IDA includes unused argument slots a5 through a8 */
    w_u16(0x800C0550u, a1); w_u16(0x800C0552u, a2);
    w_u16(0x800C0554u, (uint8)a3); w_u16(0x800C0556u, (uint8)a4);
    w_u16(0x800C0560u, 0); w_u16(0x800C0558u, (uint8)a9);
    w_u16(0x800C055Au, (uint8)a10); w_u16(0x800C055Cu, (uint8)a11);
    w_u16(0x800C055Eu, (uint8)a12); w_u16(0x800C0562u, (uint8)a13);
    return (uint8)a9;
}

uint32 sub_8005A614(uint32 a1)
{
    uint32 index, data, size;
    if (a1)
    {
        w_u16(0x80071A8Eu, r_u16(0x80071A8Eu) ^ 1u);
        index = r_u16(0x80071A8Eu);
        size = r_u32(0x80071538u);
        data = r_u32(0x80071A94u + (uint32)((sint32)(index << 16) >> 14));
        sub_80067FC8(a1, data, size);
        return sub_80066B98(a1);
    }
    /* TODO: Null argument returns an unspecified incoming value */
    return draft_unknown_return("sub_8005A614");
}

uint32 sub_80044CC0(uint32 a1, uint32 a2)
{
    uint32 x = a1 - r_u32(0x800BBFC4u), y = a2 - r_u32(0x800BBFCCu);
    if ((sint32)x >= 12000 && (sint32)y >= 12000) w_u32(0x800718A0u, 0x4000u);
    else
    {
        w_u32(0x800718A0u, sub_8001F8A8(x, y));
        if ((sint32)r_u32(0x800718A0u) >= 16385) w_u32(0x800718A0u, 0x4000u);
    }
    return 0x4000u;
}

uint32 sub_80018FA0(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    uint32 destination = a3 + 16u * (uint16)a1, source = a4 + 8u * (uint16)a2;
    uint32 result, z;
    w_u32(destination, r_u32(destination) + (uint32)(sint32)(sint16)r_u16(source));
    w_u32(destination + 4u, r_u32(destination + 4u) + (uint32)(sint32)(sint16)r_u16(source + 2u));
    result = r_u32(destination + 12u) + 1u;
    z = r_u32(destination + 8u) + (uint32)(sint32)(sint16)r_u16(source + 4u);
    w_u32(destination + 12u, result); w_u32(destination + 8u, z);
    return result;
}

uint32 sub_8001F950(uint32 a1, uint32 a2, uint32 a3)
{
    sint16 value = (sint16)a1, target = (sint16)a2;
    if (!(r_u16(0x800719D0u) & (uint16)a3))
    {
        if (value < target) value = (sint16)((uint16)value + 1u);
        if (target < value) value = (sint16)((uint16)value - 1u);
    }
    return (uint32)(sint32)value;
}

uint32 sub_800456A8(uint32 a1, uint32 a2)
{
    uint32 i, offset = 32u * (uint16)a1;
    for (i = 0; i < 16u; ++i)
    {
        w_u16(0x800AEA6Cu + offset + 2u * i, 0xFFFFu);
        w_u16(0x800BF908u + offset + 2u * i, a2);
    }
    return 0;
}

uint32 sub_8004469C(uint32 a1)
{
    uint32 location = 0x800AEED8u + 4u * (uint16)a1, result = 0x800AEED8u;
    if (r_u32(location)) { result = sub_80062128(); w_u32(location, 0); }
    return result;
}

uint32 sub_80013974(void)
{
    PSX_RECT rectangle = {0, 0, 384, 502};
    sub_8005E168(&rectangle, 0, 0, 0);
    return sub_8005DFE4(0);
}

uint32 sub_80012780(uint32 allocation, uint32 *x, uint32 *y)
{
    allocation = (uint16)allocation;
    if (allocation >= 10u) { *x = (uint16)(allocation - 10u) + 6u; *y = 256u; }
    else { *x = allocation + 6u; *y = 0; }
    *x <<= 6;
    return *x;
}

void sub_80013B64(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    w_u8(0x800BF1E8u, a1); w_u8(0x800BF244u, a1);
    w_u8(0x800BF1E9u, a2); w_u8(0x800BF1EAu, a3); w_u8(0x800BF1EBu, a4);
    w_u8(0x800BF245u, a2); w_u8(0x800BF246u, a3); w_u8(0x800BF247u, a4);
}

uint32 sub_80044734(void)
{
    uint32 i;
    for (i = 66u; i < 80u; ++i) sub_8004469C(i);
    w_u16(0x80071734u, 0xFFFFu);
    return 0xFFFFFFFFu;
}

uint32 sub_8002B134(void)
{
    uint32 i;
    w_u8(0x80071730u, 0);
    for (i = 0; i < 4u; ++i) w_u16(0x800BD3BEu + 24u * i, 0);
    return 0;
}

uint32 sub_800574D4(void)
{
    uint32 i;
    for (i = 0; i < 32u; ++i) sub_800573EC(i);
    return 0;
}

uint32 sub_8001496C(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 offset = 2u * (uint16)a1, result;
    w_u8(a2, r_u8(0x80068550u + offset));
    result = r_u8(0x80068551u + offset); w_u8(a3, result);
    return result;
}

uint32 sub_8005A7A0(uint32 a1)
{
    a1 = (uint16)a1;
    return r_u16(0x80071A58u) ? (uint16)((3u * a1) >> 1) : a1;
}

uint32 sub_80031154(void)
{
    uint32 i;
    for (i = 0; i < 8u; ++i) w_u32(0x800BD408u + 4u * i, 0);
    return 0;
}

uint32 sub_800129B4(uint32 a1)
{
    uint32 i;
    for (i = 0; i < 8192u; ++i, a1 += 4u) w_u32(a1, r_u32(a1) ^ 0x12345678u);
    return 0;
}

uint32 sub_8004496C(void)
{
    uint32 index = (uint16)sub_800448F4();
    w_u8(0x800AEEB0u + index, 1);
    return index;
}

void sub_8002046C(uint32 a1, uint32 a2, uint32 a3)
{
    w_u32(0x800BC07Cu, a1); w_u32(0x800BC080u, a2); w_u32(0x800BC084u, a3);
    w_u32(0x800BC088u, a3); w_u32(0x800BC08Cu, a3);
}

uint32 sub_80011B8C(void)
{
    uint32 index = r_u16(0x800719FCu), result = r_u16(0x800BF5E0u + 2u * (uint8)index);
    w_u16(0x800719FCu, index + 1u);
    return result;
}

uint32 sub_80059B88(void) { return sub_80059C50(0x8006A000u); }
uint32 sub_800455DC(void) { return sub_800621A8(0, 0xFFFFFFu); }
uint32 sub_8005A7D8(void) { return r_u16(0x80071A58u) ? 3u : 2u; }

uint32 sub_800471B4(void)
{
    uint32 result = sub_80011A98(32u);
    w_u16(result + 28u, 0);
    return result;
}

uint32 sub_80011DC0(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 result = (uint16)a1 >> 6;
    w_u32(a3, result); w_u32(a2, 16u * (a1 & 63u));
    return result;
}

void sub_80047590(void) { w_u16(0x80071688u, 0); w_u16(0x80071668u, 0); }

uint32 sub_80018E88(uint32 a1)
{
    uint32 result = r_u16(a1 + 8u), previous = r_u16(a1 + 6u);
    w_u16(a1 + 6u, result); w_u16(a1 + 8u, previous);
    return result;
}
