#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

uint32 sub_80047864(uint32 first, uint32 second)
{
    uint32 result, i = 0, j, a, b, first_count, second_count;
    sint32 radius = (sint32)(r_u32(first + 16) + r_u32(second + 16));
    result = radius < (sint32)sub_80047640(r_u32(first) - r_u32(second),
        r_u32(first + 4) - r_u32(second + 4), r_u32(first + 8) - r_u32(second + 8));
    if (result) return result;
    result = r_u32(first + 20);
    if ((sint32)result <= 0) return result;
    do {
        uint32 first_mesh = r_u32(first + 24 + 4 * (uint16)i);
        uint32 first_model = r_u32(first_mesh + 80);
        sint32 first_radius = (sint16)r_u16(first_model + 54);
        first_count = r_u16(first_model + 52);
        j = 0;
        if ((sint32)r_u32(second + 20) > 0) do {
            uint32 second_mesh = r_u32(second + 24 + 4 * (uint16)j);
            uint32 second_model = r_u32(second_mesh + 80);
            sint32 sum = first_radius + (sint16)r_u16(second_model + 54);
            second_count = r_u16(second_model + 52);
            for (a = 0; a < first_count; ++a) for (b = 0; b < second_count; ++b) {
                uint32 p = first_mesh + 100 + 16 * a, q = second_mesh + 100 + 16 * b;
                sint32 distance = (sint32)sub_80047640(r_u32(p) - r_u32(q),
                    r_u32(p + 4) - r_u32(q + 4), r_u32(p + 8) - r_u32(q + 8));
                if (sum >= distance) {
                    w_u32(second + 128, r_u32(second + 128) | (1u << (j & 31)));
                    w_u16(second + 136, r_u16(first + 136));
                    w_u32(second + 132, r_u32(first + 132));
                    w_u16(second + 148, r_u16(first + 148));
                    w_u16(second + 138, r_u16(first + 138));
                    w_u32(first + 128, r_u32(first + 128) | (1u << (i & 31)));
                    w_u16(first + 144, r_u16(first + 144) | r_u16(second + 144));
                    if (r_u8(first + (uint16)i + 104) == 1)
                        w_u16(second + 150, r_u16(second + 150) | 1);
                    return sub_800476F4(q, (uint32)(sint32)(sint16)r_u16(first + 136),
                        (r_u8(first + (uint16)i + 104) << 4) | r_u8(second + (uint16)j + 104));
                }
            }
            ++j;
        } while ((sint32)(uint16)j < (sint32)r_u32(second + 20));
        ++i;
        result = (sint32)(uint16)i < (sint32)r_u32(first + 20);
    } while (result);
    return result;
}

uint32 sub_800476F4(uint32 position, uint32 sound, uint32 kind)
{
    uint32 group = 0, color = 0, index, effect, pitch, channel, i;
    uint32 result = kind & 15;
    if (result == 4) return result;
    result = (uint16)kind;
    if (((kind & 240) >> 4) == 4) return result;
    switch ((uint16)kind) {
    case 3: case 19: case 35: case 48: case 49: case 50: case 51: group = 3; break;
    case 16: group = 2; break;
    case 17: case 18: case 33: case 34: group = 1; color = 0xFF8040; break;
    }
    index = (uint16)((group << 2) | (sub_80011B8C() & 3));
    sub_800271A4(position, r_u8(0x8006883C + index), (uint32)(sint32)(sint16)sound, color);
    for (i = 0; i < 5; ++i) sub_80028894(position);
    sub_80044CC0(r_u32(position), r_u32(position + 8));
    sub_80044DC8(r_u32(position), r_u32(position + 8));
    effect = r_u8(0x8006882C + index);
    pitch = (sub_80011B8C() & 255) + 600;
    channel = (uint16)sub_800448F4();
    return sub_8004486C(1, channel, effect, pitch, 31000, r_u16(0x80071A20));
}
