#include "psx.h"
#include "psx_stream.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft; integration deferred */
/* TODO: Missing SDK and overlay boundaries need later fail-fast adapters */
extern uint32 sub_8005C0B8(uint32 address, uint32 size, uint32 mode);
extern uint32 sub_800D04E8(void);

uint32 sub_8004B4F0(void)
{
    uint32 i;
    for (i = 0; i < 4u; ++i)
        sub_80019648(i + 31u, 200u, 200u, 200u);
    return sub_80019648(38u, 200u, 200u, 200u);
}

uint32 sub_80051EB8(uint32 a1, uint32 a2)
{
    sint32 delta = (sint16)sub_80046D0C((uint32)(sint32)(sint16)(a2 - a1));
    sint32 step = delta >> 2;
    if (step == 0 && delta != 0)
        step = delta < 0 ? -1 : 1;
    return (a1 + (uint32)step) & 0xFFFu;
}

uint32 sub_80047534(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 result = r_u16(r_u32(a2 + 80u) + 52u);
    if (result != 0)
    {
        uint32 count = r_u16(a1 + 20u);
        result = count < 20u;
        if (result)
        {
            w_u8(a1 + count + 104u, a3);
            w_u32(a1 + 24u + 4u * count, a2);
            result = (uint16)(count + 1u);
            w_u32(a1 + 20u, result);
        }
    }
    return result;
}

uint32 sub_80014328(void)
{
    uint32 result = sub_8004E0A0(1u);
    if ((sint32)result >= 0)
    {
        sub_8004DD18(0x800BC9C0u, 2048u);
        result = sub_8004DD18(0x800BC1B4u, 2048u);
        sub_8004E20C();
        /* TODO: Null callee preserves the preceding return carrier */
    }
    return result;
}

uint32 sub_800451B8(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    if (a1 != 0x8000u)
        w_u32(0x800715B8u, a1);
    w_u16(0x8007192Cu, a2);
    if (a3 != 0x8000u)
        w_u32(0x800718C8u, a3);
    w_u16(0x800716D8u, a4);
    return sub_80044FB0();
}

uint32 sub_800235D8(uint32 a1, uint32 a2)
{
    uint32 item = sub_80032EF0();
    if (item)
    {
        w_u32(item + 8u, 9u);
        w_u16(item + 12u, a1);
        w_u16(item + 14u, a2);
        w_u16(item + 16u, 0u);
    }
    return 9u;
}

uint32 sub_800475F4(uint32 a1)
{
    uint32 result = r_u32(a1 + 20u);
    w_u32(a1 + 16u, 0u);
    w_u32(a1 + 128u, 0u);
    w_u16(a1 + 150u, 0u);
    if (result)
    {
        uint32 count = r_u16(0x80071668u);
        result = count + 1u;
        if (count < 128u)
        {
            w_u16(0x80071668u, result);
            result = count * 4u;
            w_u32(0x800BEFD0u + result, a1);
        }
    }
    return result;
}

uint32 sub_800446EC(void)
{
    uint32 i;
    for (i = 0; i < 80u; ++i)
        sub_8004469C(i);
    w_u16(0x80071734u, 0xFFFFu);
    return 0xFFFFFFFFu;
}

uint32 sub_80018EB0(uint32 a1)
{
    uint32 h1 = r_u16(a1 + 16u), h0 = r_u16(a1 + 14u);
    uint32 c0 = r_u8(a1 + 4u), c1 = r_u8(a1 + 5u), c2 = r_u8(a1 + 6u);
    uint32 d0 = r_u8(a1 + 8u), d1 = r_u8(a1 + 9u), d2 = r_u8(a1 + 10u);
    w_u16(a1 + 14u, h1);
    w_u8(a1 + 4u, d0);
    w_u8(a1 + 5u, d1);
    w_u8(a1 + 6u, d2);
    w_u16(a1 + 16u, h0);
    w_u8(a1 + 8u, c0);
    w_u8(a1 + 9u, c1);
    w_u8(a1 + 10u, c2);
    return d0;
}

uint32 sub_800234BC(uint32 a1)
{
    uint32 item = sub_80032EF0();
    if (!item)
        return 7u;
    w_u32(item + 8u, 7u);
    w_u16(item + 12u, a1);
    w_u16(item + 14u, 160u);
    return 160u;
}

uint32 sub_80018DAC(void)
{
    uint32 i;
    for (i = 0; i < 512u; ++i)
        sub_80018CFC(i);
    return 0u;
}

uint32 sub_80011D3C(uint32 a1, uint32 a2)
{
    uint32 pixels = r_u32(0x800715ACu) + 32u * (uint16)a1 + 4u;
    LoadImagePSX((PSX_RECT *)psx_addr(a2, sizeof(PSX_RECT)), (uint32 *)psx_addr(pixels, 1u));
    return (uint32)DrawSync(0);
}

uint32 sub_800471E8(uint32 a1)
{
    uint32 count = r_u16(0x80071758u);
    w_u16(a1 + 28u, 0u);
    if (count >= 64u)
        return 0u;
    w_u16(0x80071758u, count + 1u);
    w_u32(0x800C1B7Cu + 4u * count, a1);
    return 4u * count;
}

uint32 sub_8004477C(uint32 a1, uint32 a2)
{
    uint32 result = (uint32)(((unsigned long long)(a2 >> 2) * 0x24924925u) >> 32) << 4;
    w_u32(0x800BED30u + 4u * (uint16)a1, result);
    return result;
}

uint32 sub_80018F38(uint32 a1)
{
    uint32 h1 = r_u16(a1 + 20u), h0 = r_u16(a1 + 18u);
    uint32 c0 = r_u8(a1 + 8u), c1 = r_u8(a1 + 9u);
    uint32 d0 = r_u8(a1 + 12u), d1 = r_u8(a1 + 13u);
    w_u16(a1 + 18u, h1);
    w_u8(a1 + 8u, d0);
    w_u8(a1 + 9u, d1);
    w_u16(a1 + 20u, h0);
    w_u8(a1 + 12u, c0);
    w_u8(a1 + 13u, c1);
    return d0;
}

uint32 sub_800149A8(uint32 a1)
{
    return sub_80014888(r_u16(0x80068580u + 2u * (uint16)a1));
}

void sub_8002043C(uint32 a1, uint32 a2, uint32 a3)
{
    w_u32(0x800BC064u, a1);
    w_u32(0x800BC068u, a2);
    w_u32(0x800BC06Cu, a3);
    w_u32(0x800BC070u, a3);
    w_u32(0x800BC074u, a3);
}

uint32 sub_80014B18(void)
{
    sub_8004E4C8(7u);
    return (uint16)sub_800D04E8();
}

uint32 sub_80048154(void)
{
    return sub_8005C0B8(0xF2000001u, 64000u, 0x2000u);
}

uint32 sub_8004F1F8(uint32 a1, uint32 a2)
{
    return sub_8004F06C(r_u8(a1 + 241u), (uint32)(sint32)(sint16)a2);
}

uint32 sub_8001A2FC(uint32 a1, uint32 a2)
{
    uint32 result = 0x800B0120u + 56u * (uint16)a1;
    w_u32(a2 + 80u, result);
    return result;
}

uint32 sub_80046D0C(uint32 a1)
{
    uint32 angle = a1 & 0xFFFu;
    if (angle >= 2049u)
        angle |= 0xF000u;
    return (uint32)(sint32)(sint16)angle;
}

void sub_80066D48(uint32 a1, uint32 a2, uint32 a3)
{
    w_u32(0x800C050Cu, a1);
    w_u32(0x800C0208u, a2);
    w_u32(0x800BC0D0u, a3);
}

uint32 sub_80014860(void)
{
    uint32 first = r_u16(0x800716B4u), second = r_u16(0x80071720u);
    w_u16(0x800715B4u, first);
    w_u16(0x80071600u, second);
    return first;
}

uint32 sub_80018E9C(uint32 a1)
{
    uint32 first = r_u16(a1 + 8u), second = r_u16(a1 + 6u);
    w_u16(a1 + 6u, first);
    w_u16(a1 + 8u, second);
    return first;
}

void sub_8004E20C(void)
{
}

/* TODO: Declare unresolved ABI bridges for a later fail-fast integration pass */
extern uint32 draft_local_address(void *memory, uint32 size);
extern uint32 draft_unknown_argument(const char *owner, uint32 slot);
extern uint32 draft_unknown_return(const char *owner);
extern void draft_gte_control(uint32 index, uint32 value);
extern uint32 sub_8005CBB8(uint32 value);
extern uint32 sub_80032FD0(uint32 item);
extern uint32 sub_8001B69C(void);
extern uint32 sub_80068444(uint32 callback);
extern uint32 sub_8006841C(uint32 callback);
extern void sub_800CA294(uint32 first, uint32 second);

uint32 sub_8001FCE8(uint32 a1, uint32 a2)
{
    uint32 dx = r_u32(a2) - r_u32(a1);
    uint32 dy = r_u32(a2 + 4u) - r_u32(a1 + 4u);
    uint32 dz = r_u32(a2 + 8u) - r_u32(a1 + 8u);
    sint32 length = (sint32)sub_8005CBB8(dx * dx + dy * dy + dz * dz);
    uint32 magnitude, value;
    sint32 scaled, ratio;
    if (!length)
        return 0u;
    magnitude = (sint32)dy < 0 ? 0u - dy : dy;
    scaled = (sint32)(magnitude << 10);
    /* TODO: Original overflow division raises BREAK 6 */
    if (length == -1 && scaled == (sint32)0x80000000u)
        return draft_unknown_return("sub_8001FCE8 division BREAK 6");
    ratio = scaled / length;
    if (ratio >= 1024)
        ratio = 1023;
    value = r_u16(0x800BC9C0u + 2u * (uint32)ratio);
    if ((sint32)dy >= 0)
        value = 0u - value;
    return (uint32)(sint32)(sint16)value;
}

uint32 sub_80045788(uint32 a1)
{
    uint32 count = r_u16(0x80071728u), index = (uint16)a1;
    uint32 left, right, offset;
    sint32 x0, y0;
    uint32 dx, dy, length;
    if ((sint32)(count - 5u) < (sint32)index)
        index = (uint16)(count - 5u);
    left = r_u32(0x800718E4u);
    right = r_u32(0x80071954u);
    offset = 8u * index;
    x0 = (sint32)(r_u32(left + offset) + r_u32(right + offset)) >> 1;
    y0 = (sint32)(r_u32(left + offset + 4u) + r_u32(right + offset + 4u)) >> 1;
    index = (uint16)(index + 4u);
    if (index >= count)
        index = (uint16)(count - 1u);
    offset = 8u * index;
    dx = (uint32)((sint32)(r_u32(left + offset) + r_u32(right + offset)) >> 1) - (uint32)x0;
    dy = (uint32)((sint32)(r_u32(left + offset + 4u) + r_u32(right + offset + 4u)) >> 1) - (uint32)y0;
    length = sub_8001F8A8(dx, dy);
    return sub_80046B84(dx, dy, length) & 0xFFFu;
}

uint32 sub_800346B0(uint32 a1)
{
    uint32 vector[4], source = 0x800AFEC0u + 288u * r_u16(a1 + 12u);
    uint32 phase, remaining;
    vector[0] = r_u32(source);
    vector[1] = r_u32(source + 4u) - 3000u;
    vector[2] = r_u32(source + 8u);
    vector[3] = r_u32(source + 12u);
    remaining = r_u16(a1 + 14u);
    phase = remaining & 31u;
    w_u16(a1 + 14u, remaining - 1u);
    if (phase >= 16u)
        phase = 32u - phase;
    sub_80017C8C(draft_local_address(vector, sizeof(vector)), (uint16)(r_u16(a1 + 12u) + 190u), 0u, 40000u, 8u * phase + 16u);
    remaining = r_u16(a1 + 14u);
    return remaining ? remaining : sub_80032FD0(a1);
}

uint32 sub_80020CFC(void)
{
    uint32 x = r_u32(0x800BC0A4u), y = r_u32(0x800BC0A8u), z = r_u32(0x800BC0ACu);
    uint32 previous_x = r_u32(0x800BBFC4u), previous_y, previous_z, result;
    w_u16(0x800BBFD4u, 0u);
    w_u16(0x800BBFD6u, 0u);
    w_u16(0x800BBFD8u, 0u);
    w_u32(0x800AF154u, x);
    w_u32(0x800AF18Cu, x - previous_x);
    previous_y = r_u32(0x800BBFC8u);
    previous_z = r_u32(0x800BBFCCu);
    w_u32(0x800AF158u, y);
    w_u32(0x800AF15Cu, z);
    w_u32(0x800AF190u, y - previous_y);
    w_u32(0x800AF194u, z - previous_z);
    sub_8001F9D0(0x800AF14Cu);
    sub_800206D8();
    sub_8001A414(0x800AF14Cu);
    sub_8001FB5C(0x800AF14Cu);
    result = r_u16(0x800BC0C6u);
    w_u16(0x800BBFD8u, result);
    return result;
}

uint32 sub_80030D84(void)
{
    uint32 offset = (uint32)(sint32)(sint16)r_u16(0x80071774u) * 8u;
    sint32 amount;
    uint32 result;
    sub_80030C38(r_u32(0x80071954u) + offset, r_u32(0x800718E4u) + offset, 2000u);
    amount = (sint16)r_u16(0x800716BCu);
    if (r_u16(0x8007172Cu))
    {
        result = (uint32)amount + 100u;
        if (amount < 2000)
            w_u16(0x800716BCu, result);
    }
    else
    {
        if (!amount)
            return 0u;
        result = (uint32)amount - 100u;
        w_u16(0x800716BCu, result);
    }
    amount = (sint16)r_u16(0x800716BCu);
    if (amount)
    {
        offset = (uint32)(sint32)(sint16)r_u16(0x800717A0u) * 8u;
        return sub_80030C38(r_u32(0x80071954u) + offset, r_u32(0x800718E4u) + offset, (uint32)amount);
    }
    return result;
}

uint32 sub_80026D8C(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10, uint32 a11, uint32 a12, uint32 a13)
{
    uint32 item = sub_80032EF0(), result = 15u;
    if (item)
    {
        w_u32(item + 8u, 15u);
        w_u32(item + 12u, a1);
        w_u32(item + 16u, a2);
        w_u32(item + 20u, a3);
        w_u16(item + 34u, a4);
        w_u16(item + 28u, a11);
        w_u16(item + 38u, a9);
        w_u16(item + 40u, a10);
        w_u16(item + 30u, a12);
        w_u16(item + 32u, a13);
        result = sub_80011B8C() & 15u;
        w_u16(item + 36u, result);
    }
    return result;
}

uint32 sub_8004944C(void)
{
    sub_800456A8(3u, 700u);
    w_u16(0x800AEACCu, 36u);
    w_u16(0x800AEACEu, 36u);
    w_u16(0x800AEAD0u, 37u);
    w_u16(0x800AEAD2u, 37u);
    w_u16(0x800AEAD4u, 38u);
    w_u16(0x800AEAD6u, 49u);
    w_u16(0x800AEAD8u, 48u);
    sub_8001EE9C();
    w_u16(0x800AFAF2u, 300u);
    return sub_8001EEE8(185u, 186u, 184u, 119u, 400u, 400u, 400u, 3u, 2u);
}

void sub_800470FC(void)
{
    uint32 i = 0u;
    while ((uint16)i < r_u16(0x80071758u))
    {
        uint32 j = (uint16)(i + 1u);
        while ((uint16)j < r_u16(0x80071758u))
        {
            sub_80046D2C(r_u32(0x800C1B7Cu + 4u * (uint16)i), r_u32(0x800C1B7Cu + 4u * (uint16)j));
            ++j;
        }
        ++i;
    }
}

uint32 sub_8005A3C8(void)
{
    /* Release native stream ownership before callbacks and buffers */
    StUnSetRing();
    sub_80066998();
    CdControlB(9u, NULL, NULL);
    sub_80067BA4(0u);
    sub_80013894();
    sub_80011AF8(r_u32(0x80071A94u));
    sub_80011AF8(r_u32(0x80071A98u));
    sub_80011AF8(r_u32(0x80071A9Cu));
    sub_80011AF8(r_u32(0x80071AA0u));
    sub_80011AF8(r_u32(0x80071534u));
    sub_80011AF8(r_u32(0x80071538u));
    PutDispEnv((DISPENV *)psx_addr(0x800BF288u, sizeof(DISPENV)));
    return (uint32)VSync(1);
}

/* TODO: SDK entry adapters need canonical names and later fail-fast definitions */
extern uint32 sub_8005CDD8(uint32 matrix, uint32 input, uint32 output);
extern uint32 sub_8005CC48(uint32 matrix, uint32 input, uint32 output);
extern uint32 sub_80031308(uint32 item);

void sub_800204C0(void)
{
    uint32 item = r_u32(0x800BC098u), result;
    if (!item)
        return;
    sub_8005CDD8(item + 32u, 0x800BC09Cu, 0x800BC0B4u);
    w_u32(0x800BC0B4u, r_u32(0x800BC0B4u) + r_u32(item + 8u));
    w_u32(0x800BC0B8u, r_u32(0x800BC0B8u) + r_u32(item + 12u));
    w_u32(0x800BC0BCu, r_u32(0x800BC0BCu) + r_u32(item + 16u));
    result = (uint32)(-(sint32)(sint16)r_u16(item + 28u) >> (r_u16(0x800BC0C4u) & 31u));
    w_u16(0x800BC0C6u, result);
}

uint32 sub_80049504(void)
{
    sub_800456A8(4u, 700u);
    w_u16(0x800AEAEEu, 6u);
    w_u16(0x800AEAF0u, 6u);
    w_u16(0x800AEAF4u, 9u);
    w_u16(0x800AEAF6u, 34u);
    w_u16(0x800AEAECu, 5u);
    w_u16(0x800AEAF2u, 5u);
    w_u16(0x800AEAF8u, 47u);
    sub_8001EE9C();
    return sub_8001EEE8(202u, 203u, 201u, 134u, 400u, 400u, 400u, 4u, 2u);
}

uint32 sub_80045604(void)
{
    sub_800447B0(0u, 80u);
    sub_8004477C(57u, 0u);
    sub_8004477C(29u, 0x1F18u);
    sub_8004477C(30u, 0x2B34u);
    sub_80044528(16u, 0u, 66u);
    w_u8(0x80071998u, 0u);
    w_u8(0x80071990u, 0u);
    w_u8(0x800717D4u, 0u);
    w_u8(0x800718C4u, 0u);
    w_u8(0x80071A10u, 0u);
    w_u8(0x800719D8u, 0u);
    w_u8(0x800719DCu, 0u);
    w_u8(0x80071898u, 0u);
    w_u16(0x80071734u, 0xFFFFu);
    return 0xFFFFFFFFu;
}

uint32 sub_800585D8(uint32 a1)
{
    uint32 limit = r_u16(a1 + 18u), count = (uint16)(r_u16(a1 + 16u) + 1u), result;
    w_u16(a1 + 16u, count);
    result = count < limit;
    if (count >= limit)
    {
        uint32 item = r_u16(a1 + 22u);
        if (item != 0xFFFFu)
        {
            sub_80031308(item);
            w_u16(a1 + 22u, 0xFFFFu);
        }
        if (r_u16(a1 + 28u) == 4096u)
        {
            result = r_u16(a1 + 18u) + 0xFFFFu;
            w_u8(a1 + 20u, 1u);
        }
        else
        {
            result = r_u16(a1 + 28u);
            w_u16(a1 + 10u, 0u);
            w_u16(a1 + 8u, 0u);
        }
        w_u16(a1 + 16u, result);
    }
    return result;
}

uint32 sub_80018BD8(void)
{
    uint32 i;
    for (i = 0u; i < 350u; ++i)
    {
        uint32 source = r_u32(0x800718B8u) + 16u * i, destination = 0x800C0564u + 16u * i;
        uint32 words[4];
        words[0] = r_u32(source);
        words[1] = r_u32(source + 4u);
        words[2] = r_u32(source + 8u);
        words[3] = r_u32(source + 12u);
        w_u32(destination, words[0]);
        w_u32(destination + 4u, words[1]);
        w_u32(destination + 8u, words[2]);
        w_u32(destination + 12u, words[3]);
    }
    return sub_80011AF8(r_u32(0x800718B8u));
}

uint32 sub_800149DC(void)
{
    uint8 values[8];
    uint32 local = draft_local_address(values, sizeof(values));
    sub_8001496C(r_u16(0x80071594u), local, local + 1u);
    if (values[1] == 0u && values[0] < 5u)
    {
        sub_80012F20(8u);
        sub_80018B38();
        sub_8004E4C8(11u);
        sub_800CA294(values[0], values[1]);
        sub_80012FBC();
        sub_80018BD8();
    }
    return sub_800149A8(r_u16(0x80071594u));
}

uint32 sub_80027114(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6)
{
    uint32 item = sub_80032EF0();
    if (item)
    {
        w_u32(item + 8u, 34u);
        w_u16(item + 12u, a1);
        w_u16(item + 14u, a2);
        w_u16(item + 16u, 0u);
        w_u16(item + 20u, a3);
        w_u16(item + 22u, a4);
        w_u16(item + 24u, a5);
        w_u16(item + 26u, a6);
    }
    return 34u;
}

uint32 sub_8001B7A0(uint32 a1)
{
    if (r_u16(0x800716E4u))
        sub_8001B69C();
    else
        sub_8001B570();
    if ((uint16)a1)
    {
        draft_gte_control(8u, r_u32(0x800B7184u));
        draft_gte_control(9u, r_u32(0x800B7188u));
        draft_gte_control(10u, r_u32(0x800B718Cu));
        draft_gte_control(11u, r_u32(0x800B7190u));
        draft_gte_control(12u, r_u32(0x800B7194u));
    }
    return (uint16)a1;
}

void sub_80066998(void)
{
    /* Native STR owns CD callbacks and controller cleanup */
    StUnSetRing();
}

uint32 sub_8001A414(uint32 a1)
{
    w_u32(0x1F800028u, r_u32(a1 + 8u) - r_u32(0x800BBFC4u));
    w_u32(0x1F80002Cu, r_u32(a1 + 12u) - r_u32(0x800BBFC8u));
    w_u32(0x1F800030u, r_u32(a1 + 16u) - r_u32(0x800BBFCCu));
    return sub_8005CC48(0x800BBFDCu, 0x1F800028u, a1 + 64u);
}

uint32 sub_8005A730(void)
{
    sint32 count = (sint32)r_u16(0x80071A62u) - 1;
    uint32 wide = r_u16(0x80071A58u);
    count = count / 16 + 1;
    return (uint32)count * (wide ? 192u : 128u);
}

uint32 sub_8005135C(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 offset = 8u * (uint16)a1, left = r_u32(0x800718E4u) + offset, right = r_u32(0x80071954u) + offset;
    uint32 x = r_u32(left), end_x = r_u32(right), y = r_u32(left + 4u), end_y = r_u32(right + 4u);
    uint32 factor = (uint32)(sint32)(sint16)a2;
    uint32 dx = (uint32)((sint32)((end_x - x) * factor) >> 7);
    uint32 dy = (uint32)((sint32)((end_y - y) * factor) >> 7);
    w_u32(a3, x + dx);
    w_u32(a3 + 8u, y + dy);
    return dy;
}

uint32 sub_80057B0C(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 cursor = a1 + 4u + 2u * ((uint32)(sint32)(sint16)r_u16(a1 + 2u) - 1u) * a3;
    sint32 target = (sint16)a2;
    if (target < (sint16)r_u16(cursor))
    {
        uint32 stride = a3 * 2u;
        cursor -= stride;
        for (;;)
        {
            sint32 previous = (sint16)r_u16(cursor);
            cursor -= stride;
            if (target >= previous)
                break;
        }
        cursor += stride;
    }
    return cursor;
}
