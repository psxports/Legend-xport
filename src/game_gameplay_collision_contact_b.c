#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static uint32 contact_half(uint32 value)
{
    return (uint32)((sint32)(value + (value >> 31)) >> 1);
}

uint32 sub_80047224(uint32 collision)
{
    uint32 minimum[3] = {1000000u, 1000000u, 1000000u};
    uint32 maximum[3] = {(uint32)-1000000, (uint32)-1000000, (uint32)-1000000};
    uint32 part = 0u, vertex, mesh, model, axis, source, radius, value, high, low;
    uint32 extent, squared = 0u, result;
    if ((sint32)r_u32(collision + 20u) > 0)
    {
        do
        {
            mesh = r_u32(collision + 24u + 4u * part);
            model = r_u32(mesh + 80u);
            for (axis = 0u; axis < 3u; ++axis)
                draft_gte_control(5u + axis, r_u32(mesh + 8u + 4u * axis));
            for (axis = 0u; axis < 5u; ++axis)
                draft_gte_control(axis, r_u32(mesh + 32u + 4u * axis));
            radius = (uint32)(sint32)(sint16)r_u16(model + 54u);
            vertex = 0u;
            while (vertex < r_u16(model + 52u))
            {
                source = model + 20u + 8u * vertex;
                draft_gte_data(0u, r_u32(source));
                draft_gte_data(1u, r_u32(source + 4u));
                draft_gte_command(0x480012u);
                for (axis = 0u; axis < 3u; ++axis)
                {
                    value = draft_gte_read(25u + axis);
                    w_u32(0x1F800028u + 4u * axis, value);
                    high = value + radius;
                    low = value - radius;
                    if ((sint32)maximum[axis] < (sint32)high)
                        maximum[axis] = high;
                    if ((sint32)low < (sint32)minimum[axis])
                        minimum[axis] = low;
                }
                /* The original copies the fourth scratch word without modifying it */
                for (axis = 0u; axis < 4u; ++axis)
                    w_u32(mesh + 100u + 16u * vertex + 4u * axis, r_u32(0x1F800028u + 4u * axis));
                vertex = (vertex + 1u) & 65535u;
            }
            part = (part + 1u) & 65535u;
        } while ((sint32)part < (sint32)r_u32(collision + 20u));
    }
    for (axis = 0u; axis < 3u; ++axis)
    {
        w_u32(collision + 4u * axis, contact_half(maximum[axis] + minimum[axis]));
        extent = contact_half(maximum[axis] - minimum[axis]);
        squared += extent * extent;
    }
    result = sub_8005CBB8(squared);
    w_u32(collision + 16u, result);
    return result;
}
