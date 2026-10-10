#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
extern CdlLOC *CdIntToPos(sint32 sector, CdlLOC *position);
#include <stdlib.h>

/* Unverified C draft; integration deferred */

uint32 sub_800125FC(uint32 format)
{
    uint8 occupied[20] = {0};
    const uint16 requirements[3] = {1u, 2u, 4u};
    uint32 index = 0u;
    uint32 result;
    uint32 required;

    while ((uint16)index < r_u16(0x80071720u))
    {
        uint32 type = r_u8(0x800C020Cu + (uint16)index);
        uint32 slot = r_u8(0x800C04F4u + (uint16)index);
        uint32 width;
        if (type < 3u)
        {
            width = 1u << type;
            /* TODO: Original out-of-range slot writes have an unresolved local-memory effect */
            if (slot + width > sizeof(occupied))
                abort();
            occupied[slot] = 1u;
            if (type >= 1u)
                occupied[slot + 1u] = 1u;
            if (type == 2u)
            {
                occupied[slot + 2u] = 1u;
                occupied[slot + 3u] = 1u;
            }
        }
        ++index;
    }
    format &= 0xFFFFu;
    /* TODO: Other formats read beyond the three local requirements */
    if (format >= 3u)
        abort();
    required = requirements[format];
    result = (uint16)sub_8001257C(occupied, required);
    if (result == 0xFFFFu)
    {
        /* TODO: Search may read one byte beyond occupied during the second bank */
        result = (uint16)sub_8001257C(occupied + 10u, required);
        if (result != 0xFFFFu)
            return (uint16)(result + 10u);
    }
    return result;
}

uint32 sub_80013BAC(void)
{
    DISPENV first;
    DISPENV second;
    PSX_RECT rectangle;
    uint32 index;
    uint32 value;
    uint32 image;
    SetDefDispEnv(&first, 0, 0, 640, 256);
    SetDefDispEnv(&second, 0, 256, 640, 256);
    index = 0u;
    value = r_u16(0x800BF292u);
    second.screen.h = 256;
    first.screen.h = 256;
    second.screen.y = (sint16)value;
    first.screen.y = (sint16)value;
    VSync(0);
    PutDispEnv(&first);
    VSync(0);
    sub_8004E214(0u);
    image = sub_8004E308();
    rectangle.x = 0;
    rectangle.y = 256;
    rectangle.w = 640;
    rectangle.h = 256;
    LoadImagePSX(&rectangle, (uint32 *)psx_addr(image, 1u));
    DrawSync(0);
    sub_8004E2C0();
    VSync(0);
    PutDispEnv(&second);
    VSync(0);
    do
    {
        VSync(0);
        ++index;
    } while ((uint16)index < 250u);
    sub_80013894();
    VSync(0);
    PutDispEnv((DISPENV *)psx_addr(0x800BF288u, sizeof(DISPENV)));
    return (uint32)VSync(0);
}

uint32 sub_80014888(uint32 image)
{
    uint32 table;
    uint32 environment;
    uint32 count;
    uint32 result;
    sint32 active;
    w_u16(0x800719D0u, 0u);
    sub_80014848();
    w_u16(0x800715E8u, 0u);
    sub_800134E0(image & 0xFFFFu, 0u, 0u);
    w_u16(0x8007194Cu, 0xFEu);
    w_u16(0x800717A4u, 0xFFF0u);
    w_u16(0x800716FCu, 2u);
    do
    {
        sub_800139C0();
        table = r_u32(0x8007184Cu);
        ClearOTagR((uint32 *)psx_addr(table, 1u), 2500);
        sub_800184C0(32u, 0u, 2499u, 0u);
        sub_8002F36C();
        DrawSync(0);
        VSync(0);
        environment = r_u32(0x800719CCu);
        PutDrawEnv((DRAWENV *)psx_addr(environment, sizeof(DRAWENV)));
        environment = r_u32(0x800719D4u);
        PutDispEnv((DISPENV *)psx_addr(environment, sizeof(DISPENV)));
        table = r_u32(0x8007184Cu);
        DrawOTag((uint32 *)psx_addr(table + 9996u, 1u));
        count = r_u16(0x800719D0u);
        w_u16(0x800719D0u, count + 1u);
        result = r_u16(0x800715E8u);
        active = (sint16)r_u16(0x800717A4u);
        result ^= 1u;
        w_u16(0x800715E8u, result);
    } while (active != 0);
    return result;
}

uint32 sub_80014848(void)
{
    uint32 first;
    uint32 second;
    first = r_u16(0x800715B4u);
    second = r_u16(0x80071600u);
    w_u16(0x800716B4u, first);
    w_u16(0x80071720u, second);
    return first;
}

uint32 sub_80011AF8(uint32 address)
{
    uint32 balance;
    uint32 size;
    balance = r_u32(0x80071674u);
    size = r_u32(address - 4u);
    w_u32(0x80071674u, balance + 8u + size);
    return freePSX(address - 4u);
}

uint32 sub_8004E2C0(void)
{
    uint32 buffer;
    uint32 size;
    buffer = r_u32(0x8007166Cu);
    sub_80011AF8(buffer);
    size = r_u32(0x80071824u);
    buffer = sub_80011A98(size);
    w_u32(0x8007166Cu, buffer);
    return sub_8004DCAC();
}

uint32 sub_8004E308(void)
{
    uint32 position_storage[2];
    CdlLOC *position;
    uint32 sector;
    uint32 bytes;
    uint32 destination;
    uint32 result;
    position = (CdlLOC *)position_storage;
    sector = r_u32(0x800718FCu);
    bytes = r_u32(0x8007157Cu);
    CdIntToPos((sint32)sector, position);
    do
    {
        destination = r_u32(0x8007166Cu);
        result = sub_8004DA84((uint8 *)position, destination, bytes >> 11);
    } while (result == 0u);
    return r_u32(0x8007166Cu);
}
