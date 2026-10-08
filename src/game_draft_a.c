#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdlib.h>

/* Unverified draft; integration deferred */
uint32 sub_8004DA84(uint8 *position, uint32 destination, uint32 sectors)
{
    uint8 parameter[8];
    uint32 remaining;
    FUNCTION_MARKER(0x8004DA84u, "SLES_007.30");
    parameter[0] = 0x80u;
    CdControl(14u, parameter, NULL);
    CdControl(6u, position, NULL);
    remaining = sectors;
    --sectors;
    if (remaining != 0u)
    {
        do
        {
            if (CdReady(0, NULL) != 1)
            {
                CdControl(9u, NULL, NULL);
                return 0u;
            }
            sub_80063E00(destination, 512u);
            destination += 2048u;
            remaining = sectors;
            --sectors;
        }
        while (remaining != 0u);
    }
    CdControl(9u, NULL, NULL);
    return 1u;
}

uint32 sub_8004DCDC(void)
{
    uint32 buffer;
    FUNCTION_MARKER(0x8004DCDCu, "SLES_007.30");
    w_u32(0x80071824u, 0x8000u);
    buffer = sub_80011A98(0x8000u);
    w_u32(0x8007166Cu, buffer);
    return sub_8004DCAC();
}

uint32 sub_800134E0(uint32 image, uint32 index, sint32 mode)
{
    uint32 data, format, offset = 2u, allocation, current;
    uint32 x, y, pixels, cursor, count, page;
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x800134E0u, "SLES_007.30");
    if (r_u16(0x80071720u) == 22u)
        return 22u;

    sub_8004E214(image & 0xFFFFu);
    data = sub_8004E308();
    format = r_u16(data);
    if (format != 2u)
    {
        uint32 palette = sub_800130FC(format, (sint32)((uint32)mode & 0xFFFFu), data + 4u);
        current = r_u16(0x80071720u);
        w_u8(0x800AF768u + 40u * current, (uint8)palette);
        offset = format == 0u ? 0x12u : 0x102u;
    }
    current = r_u16(0x80071720u);
    w_u16(0x800AF684u + 2u * current, 0xFFFFu);
    w_u8(0x800C020Cu + current, (uint8)format);
    allocation = sub_800125FC(format);
    if ((allocation & 0xFFFFu) != 0xFFFFu)
    {
        sub_80012780(allocation & 0xFFFFu, &x, &y);
        current = r_u16(0x80071720u);
        w_u8(0x800C04F4u + current, (uint8)allocation);
        page = sub_80060C88(format, 0u, x, y);
        current = r_u16(0x80071720u);
        w_u16(0x800AEE74u + 2u * current, (uint16)page);
        rectangle.h = 256;
        rectangle.x = (sint16)x;
        rectangle.y = (sint16)y;
        switch (format)
        {
        case 0u:
            pixels = data + 2u * offset;
            offset += 0x4000u;
            rectangle.w = 64;
            break;
        case 1u:
            pixels = data + 2u * offset;
            offset += 0x8000u;
            rectangle.w = 128;
            break;
        case 2u:
            pixels = data + 2u * offset;
            offset += 0x10000u;
            rectangle.w = 256;
            if (((uint32)mode & 0xFFFFu) == 0u)
            {
                cursor = pixels;
                for (count = 0u; count < 0x10000u; ++count)
                {
                    w_u16(cursor, r_u16(cursor) | 0x8000u);
                    cursor += 2u;
                }
            }
            break;
        default:
            /* TODO: Original default retains undefined pixel address and rectangle width */
            abort();
        }
        LoadImagePSX(&rectangle, (uint32 *)psx_addr(pixels, 1u));
        DrawSync(0);
    }

    current = r_u16(0x80071720u);
    w_u16(0x80071720u, (uint16)(current + 1u));
    allocation = r_u16(0x80071720u);
    w_u16(0x800C0510u + 2u * (index & 0xFFFFu), (uint16)current);
    w_u16(0x800AF684u + 2u * allocation, 0xFFFFu);
    w_u8(0x800C020Cu + allocation, (uint8)format);
    allocation = sub_800125FC(0u);
    if ((allocation & 0xFFFFu) != 0xFFFFu)
    {
        sub_80012780(allocation & 0xFFFFu, &x, &y);
        current = r_u16(0x80071720u);
        w_u8(0x800C04F4u + current, (uint8)allocation);
        page = sub_80060C88(format, 0u, x, y);
        current = r_u16(0x80071720u);
        w_u16(0x800AEE74u + 2u * current, (uint16)page);
        rectangle.h = 256;
        rectangle.x = (sint16)x;
        rectangle.y = (sint16)y;
        switch (format)
        {
        case 0u:
            pixels = data + 2u * offset;
            rectangle.w = 16;
            break;
        case 1u:
            pixels = data + 2u * offset;
            rectangle.w = 32;
            break;
        case 2u:
            pixels = data + 2u * offset;
            rectangle.w = 64;
            if (((uint32)mode & 0xFFFFu) == 0u)
            {
                cursor = pixels;
                for (count = 0u; count < 0x4000u; ++count)
                {
                    w_u16(cursor, r_u16(cursor) | 0x8000u);
                    cursor += 2u;
                }
            }
            break;
        default:
            /* TODO: Original default retains prior pixel address and rectangle width */
            abort();
        }
        LoadImagePSX(&rectangle, (uint32 *)psx_addr(pixels, 1u));
        DrawSync(0);
    }
    current = r_u16(0x80071720u);
    w_u16(0x80071720u, (uint16)(current + 1u));
    w_u16(0x800C0530u + 2u * (index & 0xFFFFu), (uint16)current);
    return sub_8004E2C0();
}
