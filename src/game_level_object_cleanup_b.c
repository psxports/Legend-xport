#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_800449A0(uint32 channel);

uint32 sub_80033638(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_80011AF8(r_u32(node + 16));
    sub_80011AF8(r_u32(node + 20));
    return sub_80011AF8(r_u32(node + 24));
}

uint32 sub_8003468C(uint32 node)
{
    return sub_8001A3F4(r_u32(node + 12));
}

uint32 sub_80034CE8(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_8001A3F4(r_u32(node + 16));
    sub_80011AF8(r_u32(node + 20));
    sub_80011AF8(r_u32(node + 24));
    return sub_80011AF8(r_u32(node + 28));
}

uint32 sub_800376A8(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_8001A3F4(r_u32(node + 16));
    return sub_80011AF8(r_u32(node + 20));
}

uint32 sub_80037B5C(uint32 node)
{
    return sub_8001A3F4(r_u32(node + 12));
}

uint32 sub_80037DC4(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_8001A3F4(r_u32(node + 16));
    return sub_80011AF8(r_u32(node + 20));
}

uint32 sub_80038218(uint32 node)
{
    return sub_8001A3F4(r_u32(node + 12));
}

uint32 sub_800386F4(uint32 node)
{
    return sub_80011AF8(r_u32(node + 12));
}

uint32 sub_80039984(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    return sub_80011AF8(r_u32(node + 16));
}

uint32 sub_80039E00(uint32 node)
{
    return sub_8001EE58(r_u32(node + 12));
}

uint32 sub_80039F04(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    return sub_80011AF8(r_u32(node + 16));
}

uint32 sub_8003A4B4(uint32 node)
{
    return sub_8001A3F4(r_u32(node + 12));
}

uint32 sub_8003A630(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_8001A3F4(r_u32(node + 16));
    sub_80011AF8(r_u32(node + 20));
    return sub_80011AF8(r_u32(node + 24));
}

uint32 sub_8003AEA8(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    return sub_80011AF8(r_u32(node + 72));
}

uint32 sub_8003B9E4(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    return sub_8001A3F4(r_u32(node + 16));
}

uint32 sub_8003C3EC(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_80011AF8(r_u32(node + 20));
    return sub_80011AF8(r_u32(node + 16));
}

uint32 sub_8003C7B8(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    return sub_80011AF8(r_u32(node + 16));
}

uint32 sub_8003E668(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_8001A3F4(r_u32(node + 16));
    sub_8001A3F4(r_u32(node + 20));
    return sub_80011AF8(r_u32(node + 24));
}

uint32 sub_8003EBD0(uint32 node)
{
    sub_80011AF8(r_u32(node + 76));
    sub_80011AF8(r_u32(node + 80));
    return sub_8001EE58(r_u32(node + 12));
}

uint32 sub_8003B314(uint32 node)
{
    sub_8001A3F4(r_u32(node + 12));
    sub_80011AF8(r_u32(node + 72));
    if (r_u16(node + 120) == 0xFFFF)
        return 0xFFFF;
    sub_800449A0(r_u16(node + 120));
    return sub_8004486C(4, r_u16(node + 120), 0, 0, 0, 0);
}

uint32 sub_8003F638(void)
{
    uint32 node = r_u32(0x80071868);
    while (node)
    {
        uint32 next = r_u32(node + 4);
        switch (r_u32(node + 8))
        {
            case 5:
                sub_80033638(node);
                break;
            case 6:
                sub_8003468C(node);
                break;
            case 10:
            case 36:
                sub_80034CE8(node);
                break;
            case 13:
                sub_8003FC28(node);
                break;
            case 21:
            case 41:
                sub_800376A8(node);
                break;
            case 22:
                sub_80037B5C(node);
                break;
            case 23:
            case 29:
                sub_80037DC4(node);
                break;
            case 24:
                sub_80038218(node);
                break;
            case 25:
                sub_800386F4(node);
                break;
            case 31:
                sub_80039984(node);
                break;
            case 35:
                sub_80039E00(node);
                break;
            case 37:
                sub_80039F04(node);
                break;
            case 39:
                sub_8003A4B4(node);
                break;
            case 40:
                sub_8003A630(node);
                break;
            case 43:
                sub_8003AEA8(node);
                break;
            case 45:
            case 51:
                sub_8003B314(node);
                break;
            case 47:
                sub_8003B9E4(node);
                break;
            case 49:
                sub_8003C3EC(node);
                break;
            case 50:
                sub_8003C7B8(node);
                break;
            case 57:
                sub_8003E668(node);
                break;
            case 64:
                sub_8003EBD0(node);
                break;
            default:
                break;
        }
        node = next;
    }
    return sub_80011AF8(r_u32(0x80071718));
}
