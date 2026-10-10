#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */
/* TODO: Missing external boundaries require fail-fast during integration */
extern uint32 sub_80044F58(uint32 volume);
extern uint32 sub_80066888(uint32 delay);
extern void nullsub_2(void);
extern uint32 sub_8005D138(uint32 vector, uint32 matrix);
extern uint32 sub_8005CDD8(uint32 matrix, uint32 vector, uint32 result);
extern void draft_gte_control(uint32 index, uint32 value);
extern void draft_gte_data(uint32 index, uint32 value);
extern void draft_gte_command(uint32 opcode);
extern uint32 draft_gte_read(uint32 index);

uint32 sub_8002292C(uint32 a1)
{
    uint16 count[4];
    uint32 result = sub_8004E0A0((uint16)a1), destination;
    if ((sint32)result < 0)
        return result;
    sub_8004DD18(draft_local_address(count, sizeof(count)), 2u);
    destination = sub_80011A98(28u * count[0]);
    w_u32(0x8007167Cu, destination);
    result = sub_8004DD18(destination, 28u * count[0]);
    nullsub_2();
    return result;
}

uint32 sub_8004F8BC(void)
{
    uint32 value, tens, units;
    if (r_u16(0x80071828u))
    {
        w_u16(0x80071750u, r_u16(0x80071750u) + 1u);
        if (r_u16(0x80071750u) == 512u)
        {
            value = r_u16(0x80071940u);
            if (value)
                w_u16(0x80071940u, value - 1u);
            w_u16(0x80071750u, 0);
        }
    }
    value = r_u16(0x80071940u);
    tens = value / 10u;
    units = value % 10u;
    if (value < 10u)
    {
        /* TODO: IDA retained extra unused stack parameters; resolve the drawing ABI */
        sub_800180D4(164, 40, 1, tens + 245u, 128, 0, 0);
        return sub_800180D4(192, 40, 1, units + 245u, 128, 0, 0);
    }
    sub_80017FB0(164, 40, 1, tens + 245u);
    return sub_80017FB0(192, 40, 1, units + 245u);
}

uint32 sub_800519E4(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    uint32 velocity = r_u32(a1) + (uint32)(sint32)(sint16)r_u16(a1 + 4u), position;
    uint32 result, force, sound, channel;
    w_u16(a1 + 6u, 0);
    w_u32(a1, velocity);
    position = r_u32(a2 + 4u) + (uint32)((sint32)velocity >> 3);
    w_u32(a2 + 4u, position);
    result = (sint32)position < (sint32)a3;
    if ((sint32)r_u32(a1) > 0 && !result)
    {
        w_u32(a2 + 4u, a3);
        result = 1;
        if ((sint32)r_u32(a1) >= 1025 && (uint16)a4)
        {
            w_u32(0x1F80002Cu, 5);
            w_u32(0x1F800028u, 0);
            w_u32(0x1F800030u, 0);
            sub_80022F08(a2, 0x1F800028u, 5u, 5u, 3u);
            sub_8004EC38(4);
            force = r_u32(a1) << 2;
            if ((sint32)force >= 16001)
                force = 16000;
            channel = (uint16)sub_800448F4();
            sound = (uint16)sub_80044F58(force);
            sub_8004486C(1, channel, 1, 800, sound, r_u16(0x80071A20u));
        }
        w_u32(a1, 0);
        w_u16(a1 + 6u, 1);
    }
    return result;
}

uint32 sub_8004EDD8(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 character = r_u8(a3++), glyph, result;
    /* TODO: Empty string leaves the original return carrier unspecified */
    if (!character)
        return draft_unknown_return("sub_8004EDD8");
    do
    {
        glyph = 0xFFFFu;
        if (character - 65u < 26u)
            glyph = character - 65u;
        if (character - 97u < 26u)
            glyph = character - 64u;
        switch (character)
        {
            case '#':
                glyph = 26;
                break;
            case '.':
                glyph = 27;
                break;
            case ':':
                glyph = 28;
                break;
            case ',':
                glyph = 29;
                break;
            case '!':
                glyph = 30;
                break;
            case '?':
                glyph = 31;
                break;
            case '%':
                glyph = 32;
                break;
        }
        if (character - 48u < 10u)
            glyph = character + 11u;
        result = 0xFFFFu;
        if (glyph != 0xFFFFu)
            result = sub_80017FB0((uint16)a1, (uint16)a2, 1, glyph);
        a1 = (uint16)(a1 + 8u);
        character = r_u8(a3++);
    } while (character);
    return result;
}

uint32 sub_8001A694(uint32 a1, uint32 a2)
{
    uint32 x = r_u32(a1 + 64u), z = r_u32(a1 + 72u), projected;
    uint16 radius = (uint16)a2, negative = (uint16)(0u - a2);
    if ((sint32)x < 0)
        x = 0u - x;
    if ((sint32)z < 0)
        z = 0u - z;
    if ((sint32)(x + z) > 60000)
        return 1;
    draft_gte_control(1, 0);
    draft_gte_control(3, 0);
    draft_gte_control(0, 4096);
    draft_gte_control(2, 4096);
    draft_gte_control(4, 4096);
    draft_gte_control(5, r_u32(a1 + 64u));
    draft_gte_control(6, r_u32(a1 + 68u));
    draft_gte_control(7, r_u32(a1 + 72u));
    draft_gte_data(0, negative | ((uint32)negative << 16));
    /* VZ0 consumes only the initialized low halfword */
    draft_gte_data(1, radius);
    draft_gte_command(0x180001u);
    projected = draft_gte_read(14);
    if ((sint16)projected >= 384 || (sint16)(projected >> 16) >= 252)
        return 1;
    draft_gte_data(0, radius | ((uint32)radius << 16));
    draft_gte_command(0x180001u);
    projected = draft_gte_read(14);
    return (sint16)projected < 0 || (sint16)(projected >> 16) < 0;
}

uint32 sub_800528E8(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 animation = a2 & 0x7FFFu, flagged = a2 & 0x8000u, index, root, result;
    if (!flagged)
        sub_800527C8(a1, (uint16)a2, (uint16)a3);
    w_u16(a1 + 246u, animation);
    index = (uint16)(r_u8(a1 + 212u) + 3u * animation);
    root = r_u32(r_u32(a1 + 52u));
    sub_8001A2FC(r_u16(0x800693FCu + 2u * index), root + 1512u);
    root = r_u32(r_u32(a1 + 52u));
    sub_8001A2FC(r_u16(0x8006946Cu + 2u * index), root + 1344u);
    root = r_u32(r_u32(a1 + 52u));
    result = sub_8001A2FC(r_u16(0x80069434u + 2u * index), root + 1176u);
    if (!flagged && animation)
    {
        sub_800513CC(a1, 38);
        result = r_u16(a1 + 228u);
        w_u16(a1 + 278u, 30);
        result |= 0xF000u;
        w_u16(a1 + 228u, result);
    }
    w_u8(a1 + 281u, 0);
    w_u16(a1 + 248u, a3);
    return result;
}

void sub_8004DE84(uint32 a1)
{
    uint32 available, remaining, sectors, remainder, buffer;
    if (!a1)
        return;
    available = r_u32(0x8007159Cu) - r_u32(0x80071814u);
    if ((sint32)available < (sint32)a1)
    {
        w_u32(0x80071814u, r_u32(0x8007159Cu));
        remaining = a1 - available;
        sectors = (uint32)((sint32)remaining / 2048);
        remainder = (uint32)((sint32)remaining % 2048);
        w_u32(0x800717E8u, r_u32(0x800717E8u) + (sectors << 11) + available);
        w_u32(0x800718FCu, r_u32(0x800718FCu) + sectors);
        if (remainder)
        {
            buffer = sub_80011A98(remainder);
            sub_8004DD18(buffer, remainder);
            sub_80011AF8(buffer);
        }
    }
    else
    {
        w_u32(0x80071814u, r_u32(0x80071814u) + a1);
        w_u32(0x800717E8u, r_u32(0x800717E8u) + a1);
    }
}

uint32 sub_8001F700(uint32 a1, uint32 a2, uint32 a3)
{
    uint32 index = (uint16)a1, table = 56u * (uint16)a2;
    uint32 source = r_u32(0x80071570u + 4u * index), base = r_u32(0x80071694u + 4u * index);
    uint32 destination_base = r_u32(0x800B0120u + table), count, i, destination, product, result = table;
    count = r_u16(source);
    source += 2u;
    for (i = 0; i < count; ++i, source += 8u, base += 8u)
    {
        destination = destination_base + 8u * r_u16(source);
        product = (uint32)(sint32)(sint16)r_u16(source + 2u) * a3;
        w_u16(destination, r_u16(base) + (uint32)((sint32)product >> 7));
        product = (uint32)(sint32)(sint16)r_u16(source + 4u) * a3;
        w_u16(destination + 2u, r_u16(base + 2u) + (uint32)((sint32)product >> 7));
        product = (uint32)(sint32)(sint16)r_u16(source + 6u) * a3;
        result = (uint32)(sint32)(sint16)r_u16(base + 4u) + (uint32)((sint32)product >> 7);
        w_u16(destination + 4u, result);
    }
    return result;
}

uint32 sub_80026A88(void)
{
    uint32 i, item, id, result;
    if (r_u16(0x8007172Cu) >= 3u)
        return 0;
    for (i = 0; i < 16u; ++i)
    {
        item = 0x800BEE88u + 18u * i;
        id = r_u16(item);
        if (id == 0xFFFFu || (id != 1024u && r_u8(0x800C9D68u + id)))
            continue;
        w_u32(0x80071850u, r_u32(item + 10u));
        w_u32(0x80071854u, r_u32(item + 14u));
        result = sub_80024074((uint32)(sint32)(sint16)r_u16(item + 2u), (uint32)(sint32)(sint16)r_u16(item + 4u), r_u16(item + 6u), r_u16(item + 8u), id);
        w_u16(item, 0xFFFFu);
        return result;
    }
    return 0;
}

uint32 sub_800573EC(uint32 a1)
{
    uint32 object = 0x800BFD08u + 40u * (uint16)a1, result = r_u32(object);
    if (result)
    {
        sub_80011AF8(r_u32(r_u32(object + 4u)));
        sub_80011AF8(r_u32(object + 4u));
        sub_80011AF8(r_u32(object + 12u));
        sub_80011AF8(r_u32(object + 16u));
        sub_80011AF8(r_u32(object + 24u));
        sub_80011AF8(r_u32(object + 28u));
        result = sub_80011AF8(r_u32(object + 32u));
        w_u32(object, 0);
    }
    return result;
}

uint32 sub_80051614(uint32 a1, uint32 a2, uint32 a3)
{
    w_u16(0x1F800020u, 0);
    w_u16(0x1F800022u, a3);
    w_u16(0x1F800024u, 0);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    w_u16(0x1F800020u, r_u16(a2 + 12u));
    w_u16(0x1F800022u, 0);
    w_u16(0x1F800024u, r_u16(a2 + 14u));
    sub_8005CDD8(0x1F800000u, 0x1F800020u, 0x1F800028u);
    w_u32(a1, r_u32(a1) + r_u32(0x1F800028u));
    w_u32(a1 + 8u, r_u32(a1 + 8u) + r_u32(0x1F800030u));
    return r_u32(a2 + 12u) != 0;
}

uint32 sub_80057954(uint32 a1, uint32 a2)
{
    uint32 count = (uint16)(r_u16(a1 + 2u) - 1u), source = a1 + 12u;
    uint32 destination = source + 6u * (uint16)a2, i, component;
    while ((uint16)count)
    {
        destination += 8u;
        for (i = 0; i < (uint16)a2; ++i, source += 6u, destination += 6u)
            for (component = 0; component < 3u; ++component)
                w_u16(destination + 2u * component, r_u16(destination + 2u * component) + r_u16(source + 2u * component));
        count = (uint16)(count - 1u);
        source += 8u;
    }
    return (uint16)count;
}

uint32 sub_8005129C(uint32 a1, uint32 a2, uint32 a3)
{
    sint16 local[4];
    uint32 index = (uint16)a1, left = r_u32(0x800718E4u) + 8u * index;
    uint32 right = r_u32(0x80071954u) + 8u * index, first, second, product;
    product = (r_u32(right) - r_u32(left)) * (uint32)(sint32)(sint16)a2;
    first = r_u32(left) + (uint32)((sint32)product >> 7);
    product = (r_u32(right + 4u) - r_u32(left + 4u)) * (uint32)(sint32)(sint16)a2;
    second = r_u32(left + 4u) + (uint32)((sint32)product >> 7);
    local[0] = -1;
    w_u32(a3, first);
    w_u32(a3 + 8u, second);
    w_u32(a3 + 4u, sub_80046324(first, second, draft_local_address(local, sizeof(local))));
    return (uint32)(sint32)(sint16)r_u16(r_u32(0x800716D0u) + 2u * index);
}

uint32 sub_8002B2A0(uint32 a1)
{
    uint16 local[4];
    uint32 result = sub_8004E0A0((uint16)a1), i, address;
    if ((sint32)result < 0)
        return result;
    sub_8004DD18(draft_local_address(local, sizeof(local)), 2);
    if (local[0])
        sub_8004DD18(0x800B7120u, 2u * local[0]);
    for (i = 0; i < local[0]; ++i)
    {
        address = 0x800B7120u + 2u * i;
        w_u16(address, sub_800127C8(r_u16(address), 0xFFFFu));
    }
    nullsub_2();
    return i < local[0];
}

uint32 sub_8005A47C(uint32 a1)
{
    uint32 attempts, rounds;
    for (rounds = 0; rounds < 6u; ++rounds)
    {
        for (attempts = 0; !CdControl(21, (uint8 *)psx_addr(a1, 1), NULL); ++attempts)
            if (attempts + 1u == 5u)
                return 0;
        if (rounds + 1u == 6u)
            break;
        if (sub_80066888(448))
            return 1;
    }
    return 0;
}

uint32 sub_8004B87C(void)
{
    static const uint32 clear[] = {0x800719ACu, 0x80071578u, 0x800715DCu, 0x800716F0u, 0x80071A54u, 0x8007162Cu, 0x800719A0u, 0x80071564u, 0x800715D0u, 0x800716DCu, 0x80071A4Cu, 0x8007161Cu, 0x800717D0u};
    uint32 i;
    w_u16(0x80071A2Cu, 128);
    w_u16(0x800715ECu, 128);
    w_u16(0x80071964u, 0xEA60u);
    w_u16(0x800719C4u, 1);
    w_u16(0x800717F0u, 2);
    for (i = 0; i < sizeof(clear) / sizeof(clear[0]); ++i)
        w_u16(clear[i], 0);
    w_u16(0x800C0550u, 0xFFFFu);
    return 0xFFFFu;
}

uint32 sub_80018CFC(uint32 a1)
{
    uint32 object = 0x800B0120u + 56u * (uint16)a1, result = 7u * (uint16)a1, pointer;
    pointer = r_u32(object);
    if (pointer)
    {
        result = sub_80011AF8(pointer);
        w_u32(object, 0);
    }
    pointer = r_u32(object + 4u);
    if (pointer)
        result = sub_80011AF8(pointer);
    pointer = r_u32(object + 12u);
    w_u32(object + 4u, 0);
    if (pointer)
        result = sub_80011AF8(pointer);
    w_u32(object + 12u, 0);
    return result;
}

void sub_8004EC74(void)
{
    sint16 increment = (sint16)r_u16(0x80071808u), position;
    if (!increment)
        return;
    position = (sint16)(r_u16(0x800717F4u) + increment);
    w_u16(0x800717F4u, (uint16)position);
    if (increment > 0)
    {
        if (position >= increment)
            w_u16(0x80071808u, 1u - (uint16)increment);
    }
    else if (increment >= position)
        w_u16(0x80071808u, ~(uint16)increment);
    if (!r_u16(0x80071808u))
        w_u16(0x800717F4u, 0);
    sub_8005D108(192, (uint32)(120 + (sint16)r_u16(0x800717F4u)));
}
