#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_8002BB88(uint32 color, uint32 first, uint32 second, uint32 third)
{
    uint32 center[3], channels[3], axis, slot, entry, delta, squared, distance, factor, product, result;
    sint32 sum;
    for (axis = 0u; axis < 3u; ++axis)
    {
        sum = (sint16)r_u16(first + 2u * axis) + (sint16)r_u16(second + 2u * axis) + (sint16)r_u16(third + 2u * axis);
        center[axis] = (uint32)(sum / 3) + r_u32(0x800BEFA8u + 4u * axis);
        channels[axis] = r_u8(color + axis);
    }
    for (slot = 0u; slot < 4u; ++slot)
    {
        entry = 0x800BD3A8u + 24u * slot;
        if (!r_u16(entry + 22u)) continue;
        squared = 0u;
        for (axis = 0u; axis < 3u; ++axis)
        {
            delta = (uint32)((sint32)(center[axis] - r_u32(entry + 4u * axis)) >> 4);
            w_u32(0x1F800028u + 4u * axis, delta);
            squared += delta * delta;
        }
        distance = sub_8005CBB8(squared);
        if ((sint32)distance >= 256) continue;
        factor = 256u - distance;
        for (axis = 0u; axis < 3u; ++axis)
        {
            product = r_u16(entry + 16u + 2u * axis) * factor;
            if ((sint32)product < 0) product += 255u;
            channels[axis] += (uint32)((sint32)product >> 8);
        }
    }
    result = (uint16)channels[2] < 256u;
    for (axis = 0u; axis < 3u; ++axis)
        w_u8(color + axis, (uint16)channels[axis] >= 256u ? 255u : channels[axis]);
    return result;
}
