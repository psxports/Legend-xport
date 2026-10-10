#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Unverified draft C; integration deferred */

uint32 sub_80011A98(uint32 size)
{
    uint32 remainder;
    uint32 balance;
    uint32 allocation;
    FUNCTION_MARKER(0x80011A98u, "SLES_007.30");
    remainder = size & 3u;
    if (remainder != 0u)
        size = size + 4u - remainder;
    size += 4u;
    balance = r_u32(0x80071674u);
    w_u32(0x80071674u, balance - 8u - size);
    allocation = mallocPSX(size);
    w_u32(allocation, size);
    return allocation + 4u;
}

uint32 sub_80011808(uint32 size)
{
    uint32 enabled;
    uint32 units;
    uint32 previous;
    uint32 block;
    uint32 available;
    uint32 remaining;
    uint32 next;
    uint32 head;
    FUNCTION_MARKER(0x80011808u, "SLES_007.30");
    enabled = r_u32(0x80071474u);
    if (enabled == 0u)
        return enabled;
    if ((size & 3u) != 0u)
        size = (size + 3u) & ~3u;
    units = ((size + 7u) >> 3) + 1u;
    previous = r_u32(0x80071478u);
    block = r_u32(previous);
    for (;;)
    {
        available = r_u32(block + 4u);
        if ((sint32)available >= (sint32)units)
            break;
        head = r_u32(0x80071478u);
        previous = block;
        if (block == head)
            return 0u;
        block = r_u32(block);
    }
    remaining = available - units;
    if (available == units)
    {
        next = r_u32(block);
        w_u32(previous, next);
    }
    else
    {
        w_u32(block + 4u, remaining);
        block += remaining << 3;
        w_u32(block + 4u, units);
    }
    w_u32(0x80071478u, previous);
    return block + 8u;
}

uint32 sub_8004DCAC(void)
{
    uint32 sector;
    FUNCTION_MARKER(0x8004DCACu, "SLES_007.30");
    sector = r_u32(0x800719E0u);
    w_u32(0x8007159Cu, 0u);
    w_u32(0x80071814u, 0u);
    w_u32(0x800717E8u, 0u);
    w_u32(0x800718FCu, sector);
    return sector;
}

uint32 sub_8004E214(uint32 index)
{
    uint32 buffer;
    uint32 offset;
    uint32 length;
    uint32 base_sector;
    sint32 relative_sector;
    FUNCTION_MARKER(0x8004E214u, "SLES_007.30");
    buffer = r_u32(0x8007166Cu);
    index &= 0xFFFFu;
    sub_80011AF8(buffer);
    offset = r_u32(0x800C5D68u + 4u * index);
    if ((sint32)offset < 0)
        offset += 0x7FFu;
    length = r_u32(0x800C1CFCu + 4u * index);
    base_sector = r_u32(0x800719E0u);
    relative_sector = (sint32)offset >> 11;
    w_u32(0x800718FCu, base_sector + (uint32)relative_sector);
    if ((length & 0x7FFu) != 0u)
        length = ((length >> 11) + 1u) << 11;
    w_u32(0x8007157Cu, length);
    buffer = sub_80011A98(length);
    w_u32(0x8007166Cu, buffer);
    return 1u;
}

uint32 sub_800118BC(uint32 address)
{
    uint32 previous;
    uint32 block;
    uint32 next;
    uint32 units;
    uint32 next_units;
    uint32 previous_units;
    uint32 result;
    FUNCTION_MARKER(0x800118BCu, "SLES_007.30");
    previous = r_u32(0x80071478u);
    block = address - 8u;
    for (;;)
    {
        if (previous < block)
        {
            next = r_u32(previous);
            if (block < next)
                break;
        }
        next = r_u32(previous);
        if (previous >= next && (previous < block || block < next))
            break;
        previous = next;
    }
    units = r_u32(block + 4u);
    next = r_u32(previous);
    if (block + (units << 3) == next)
    {
        next_units = r_u32(next + 4u);
        w_u32(block + 4u, units + next_units);
        next = r_u32(previous);
        result = r_u32(next);
        w_u32(block, result);
    }
    else
    {
        w_u32(block, next);
    }
    previous_units = r_u32(previous + 4u);
    result = previous + (previous_units << 3);
    if (result == block)
    {
        units = r_u32(block + 4u);
        result = previous_units + units;
        w_u32(previous + 4u, result);
        result = r_u32(block);
        w_u32(previous, result);
    }
    else
    {
        w_u32(previous, block);
    }
    w_u32(0x80071478u, previous);
    return result;
}

uint32 sub_8001257C(const uint8 *occupied, uint32 required)
{
    const volatile uint8 *source;
    uint32 start;
    uint32 scan;
    uint32 count;
    uint32 value;
    FUNCTION_MARKER(0x8001257Cu, "SLES_007.30");
    /* TODO: The scan reads occupied[10]; retain a sufficiently sized caller buffer */
    source = occupied;
    required &= 0xFFFFu;
    start = 0u;
    for (;;)
    {
        value = source[(uint16)start];
        if (value == 0u)
        {
            scan = start;
            count = 0u;
            for (;;)
            {
                if ((uint16)scan >= 10u)
                    break;
                ++scan;
                value = source[(uint16)scan];
                ++count;
                if (value != 0u)
                    break;
            }
            if ((uint16)count >= required)
                return (uint16)start;
        }
        ++start;
        if ((uint16)start >= 10u)
            return 0xFFFFu;
    }
}
