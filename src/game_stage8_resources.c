#include "psx.h"
#include "game_draft_signatures.h"

uint32 sub_80049C08(void)
{
    sub_800456A8(14, 700);
    w_u16(0x800AEC2E, 6);
    w_u16(0x800AEC30, 6);
    w_u16(0x800AEC34, 9);
    w_u16(0x800AEC36, 34);
    w_u16(0x800AEC2C, 5);
    w_u16(0x800AEC32, 5);
    w_u16(0x800AEC38, 47);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 200);
    w_u16(0x800AFB18, 200);
    w_u16(0x800AFB1C, 100);
    return sub_8001EEE8(370, 371, 369, 282, 400, 400, 400, 14, 2);
}

uint32 sub_80049CD4(void)
{
    sub_800456A8(15, 700);
    /* The original also writes the preceding resource's fields */
    w_u16(0x800AEC2E, 6);
    w_u16(0x800AEC30, 6);
    w_u16(0x800AEC54, 9);
    w_u16(0x800AEC56, 34);
    w_u16(0x800AEC2C, 5);
    w_u16(0x800AEC32, 5);
    w_u16(0x800AEC58, 47);
    sub_8001EE9C();
    w_u16(0x800AFB1A, 600);
    w_u16(0x800AFB18, 600);
    w_u16(0x800AFB1C, 100);
    return sub_8001EEE8(387, 388, 386, 297, 400, 400, 400, 15, 2);
}

uint32 sub_80049A30(void)
{
    sub_800456A8(12, 700);
    w_u16(0x800BFA88, 1200);
    w_u16(0x800BFA8C, 1200);
    w_u16(0x800BFA8E, 1200);
    w_u16(0x800AEBF4, 60);
    w_u16(0x800AEBEC, 58);
    w_u16(0x800AEBEE, 59);
    w_u16(0x800BFA8A, 700);
    w_u16(0x800AEBF0, 58);
    w_u16(0x800AEBF2, 58);
    w_u16(0x800AEBF6, 58);
    w_u16(0x800BFA92, 1300);
    w_u16(0x800AEBF8, 59);
    w_u16(0x800BFA94, 700);
    sub_8001EE9C();
    w_u16(0x800AFAE2, 200);
    w_u16(0x800AFAE0, 200);
    w_u16(0x800AFAE4, 200);
    w_u16(0x800AFAEA, 200);
    w_u16(0x800AFAE8, 200);
    w_u16(0x800AFAEC, 200);
    w_u16(0x800AFAF2, 200);
    w_u16(0x800AFAF0, 200);
    w_u16(0x800AFAF4, 200);
    return sub_8001EEE8(328, 329, 327, 244, 370, 370, 370, 12, 2);
}

uint32 sub_80049DA0(void)
{
    sub_800456A8(16, 700);
    w_u16(0x800BFB08, 1200);
    w_u16(0x800BFB0A, 1200);
    w_u16(0x800BFB0C, 1200);
    w_u16(0x800BFB0E, 1200);
    w_u16(0x800AEC74, 33);
    w_u16(0x800AEC6C, 35);
    w_u16(0x800AEC6E, 35);
    w_u16(0x800AEC70, 35);
    w_u16(0x800AEC72, 35);
    w_u16(0x800BFB10, 1300);
    sub_8001EE9C();
    w_u16(0x800AFAE2, 200);
    w_u16(0x800AFAE0, 200);
    w_u16(0x800AFAE4, 200);
    w_u16(0x800AFAEA, 200);
    w_u16(0x800AFAE8, 200);
    w_u16(0x800AFAEC, 200);
    return sub_8001EEE8(404, 405, 403, 312, 800, 800, 800, 16, 2);
}

uint32 sub_8004A664(void)
{
    sub_800456A8(26, 700);
    w_u16(0x800AEDAC, 36);
    w_u16(0x800AEDAE, 36);
    w_u16(0x800AEDB0, 37);
    w_u16(0x800AEDB2, 37);
    w_u16(0x800AEDB4, 44);
    w_u16(0x800AEDB6, 48);
    w_u16(0x800AEDB8, 48);
    sub_8001EE9C();
    w_u16(0x800AFAE2, 300);
    w_u16(0x800AFAE0, 300);
    w_u16(0x800AFAE4, 300);
    w_u16(0x800AFAEA, 300);
    w_u16(0x800AFAE8, 300);
    w_u16(0x800AFAEC, 300);
    return sub_8001EEE8(595, 596, 594, 451, 500, 500, 500, 26, 2);
}

uint32 sub_800498AC(void)
{
    sub_800456A8(10, 700);
    w_u16(0x800AEBAC, 39);
    w_u16(0x800AEBAE, 39);
    w_u16(0x800AEBB0, 40);
    w_u16(0x800AEBB2, 40);
    w_u16(0x800AEBB4, 41);
    w_u16(0x800AEBB6, 42);
    sub_8001EE9C();
    w_u16(0x800AFAEA, 200);
    w_u16(0x800AFAE8, 200);
    w_u16(0x800AFAEC, 200);
    w_u16(0x800AFAF2, 200);
    w_u16(0x800AFAF0, 200);
    w_u16(0x800AFAF4, 200);
    w_u16(0x800AFB22, 200);
    w_u16(0x800AFB20, 200);
    return sub_8001EEE8(294, 295, 293, 214, 400, 400, 400, 10, 2);
}

uint32 sub_80029C3C(uint32 region, uint32 angle_offset, uint32 screen_y)
{
    uint32 node = sub_80032EF0();
    if (node)
    {
        w_u32(node + 8, 42);
        w_u16(node + 12, region);
        w_u16(node + 16, angle_offset);
        w_u16(node + 14, screen_y);
    }
    return 42;
}

uint32 sub_8002F520(void)
{
    uint32 base = sub_80011A98(3840), i, node;
    w_u32(0x80071530, base);
    for (i = 0; i < 96; ++i)
    {
        node = base + 40 * i;
        w_u32(node, (uint32)randPSX() & 511);
        w_u32(node + 4, (uint32)randPSX() & 511);
        w_u32(node + 8, (uint32)randPSX() & 511);
        w_u16(node + 16, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 24, 5 + ((uint32)randPSX() & 7));
        w_u16(node + 32, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 18, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 26, (uint32)-5 - ((uint32)randPSX() & 7));
        w_u16(node + 34, 5 + ((uint32)randPSX() & 7));
        w_u16(node + 20, (uint32)randPSX() & 31);
        w_u16(node + 28, (uint32)randPSX() & 31);
        w_u16(node + 36, (uint32)randPSX() & 31);
    }
    return 0;
}

uint32 sub_8001599C(uint32 x, uint32 y, uint32 depth, uint32 scale, uint32 blend, uint32 sprite, uint32 red, uint32 green, uint32 blue)
{
    uint32 descriptor = 0x800C0564 + 16 * sprite;
    uint32 packet, right, bottom, u, v, page, order, result;
    sint32 product, low;
    sint32 width = (sint16)r_u16(descriptor + 8) - 1;
    sint32 height = (sint16)r_u16(descriptor + 10) - 1;
    product = (sint32)((uint32)(sint32)(sint16)r_u16(descriptor + 12) * scale);
    packet = r_u32(0x80071680);
    w_u32(0x80071680, packet + 40);
    x -= (uint32)(product / 128);
    low = product = (sint32)((uint32)(sint32)(sint16)r_u16(descriptor + 14) * scale);
    /* The original conditionally replaces LO before the following MFLO */
    if (product < 0)
        low = (sint32)((uint32)width * scale);
    y -= (uint32)(product / 128);
    product = low;
    if (product < 0)
        low = (sint32)((uint32)height * scale);
    right = x + (uint32)(product / 128);
    bottom = y + (uint32)(low / 128);
    w_u16(packet + 26, bottom);
    w_u16(packet + 34, bottom);
    w_u16(packet + 8, x);
    w_u16(packet + 10, y);
    w_u16(packet + 16, right);
    w_u16(packet + 18, y);
    w_u16(packet + 24, x);
    w_u16(packet + 32, right);
    u = r_u16(descriptor + 4);
    v = r_u16(descriptor + 6);
    w_u8(packet + 3, 9);
    w_u8(packet + 7, 44);
    w_u8(packet + 12, u);
    w_u8(packet + 13, v);
    w_u8(packet + 20, u + width);
    w_u8(packet + 21, v);
    w_u8(packet + 28, u);
    w_u8(packet + 29, v + height);
    w_u8(packet + 36, u + width);
    w_u8(packet + 37, v + height);
    w_u8(packet + 7, (uint16)blend ? 46 : 44);
    w_u16(packet + 22, r_u16(descriptor));
    page = r_u16(descriptor + 2);
    w_u8(packet + 4, red);
    w_u8(packet + 5, green);
    w_u8(packet + 6, blue);
    w_u16(packet + 14, page);
    if ((sint32)depth >= 2500)
        depth = 2499;
    if ((uint16)blend)
        w_u16(packet + 22, r_u16(packet + 22) | r_u16(0x8007177E + 2 * (uint16)blend));
    order = r_u32(0x8007184C) + 4 * depth;
    w_u32(packet, (r_u32(packet) & 0xFF000000) | (r_u32(order) & 0xFFFFFF));
    result = (r_u32(order) & 0xFF000000) | (packet & 0xFFFFFF);
    w_u32(order, result);
    return result;
}

uint32 sub_8003AC24(uint32 node)
{
    uint32 region = r_u16(0x800BC0CC), difference, angle;
    sint32 delta, intensity, horizontal, vertical, screen_y;
    if (region == 0xFFFF)
        return 0xFFFF;
    difference = r_u8(r_u32(0x80071704) + 14 * region + 9) - r_u16(node + 12);
    if ((uint16)(difference + 15) >= 31)
        return difference << 16;
    delta = (sint16)difference;
    if (delta < 0)
        delta = -delta;
    intensity = (sint16)((uint32)(sint32)(sint16)(128 - 8 * delta) * r_u32(0x800718F4));
    intensity /= 128;
    horizontal = (sint16)(((740 - r_u16(0x800BBFD6)) & 4095) - 740);
    horizontal >>= 1;
    angle = r_u16(0x800BBFD4) & 4095;
    if (angle >= 2049)
        angle |= 0xF000;
    if ((uint32)(horizontal + 216) >= 433)
        return 0;
    vertical = (sint16)(((sint16)angle >> 1) + r_u16(node + 16));
    screen_y = (sint16)r_u16(node + 14);
    sub_8001599C(192 - 3 * horizontal / 4, screen_y - 3 * vertical / 4, 48, 64, 4, 279, intensity, intensity, intensity);
    sub_8001599C(192 - horizontal / 2, screen_y - vertical / 2, 48, 100, 4, 279, intensity, intensity, 0);
    return sub_8001599C(192 - (sint16)(horizontal / 3), screen_y - (sint16)(vertical / 3), 48, 128, 4, 279, intensity, intensity / 2, 0);
}
