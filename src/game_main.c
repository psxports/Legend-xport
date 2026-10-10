#include "psx.h"
#include "xport.h"
#include "game_boot.h"
#include "game_timer.h"
#include "game_draft_signatures.h"

/* Original ResetGraph stores the device type at this image address */
const uint32 xport_gpu_graph_type_address = 0x8006FC74u;

void xport_main(void)
{
    if (!legend_boot())
    {
        xport_set_exit_code(1);
        return;
    }
    sub_80014E3C();
}

#include <stdlib.h>
void xport_missing_sn_constructors(void);
uint32 InitPAD(uint32 buffer0, uint32 size0, uint32 buffer1, uint32 size1);
uint32 StartPAD(void);
uint32 ChangeClearPAD(uint32 mode);
uint32 SpuInitMalloc(uint32 count, uint32 table);
uint32 _SpuInit(uint32 mode);

void sub_80014E3C(void)
{
    FUNCTION_MARKER(0x80014E3Cu, "SLES_007.30");
    /* The linked SN constructor table contains zero entries */
    if (r_u32(0x8006A0A0u) == 0u)
        w_u32(0x8006A0A0u, 1u);
    ResetCallback();
    w_u32(0x800716C8u, 0x800D0B64u);
    sub_800117A4(0x800D0B64u, 0x801F7FF8u - 0x800D0B64u);
    sub_80011B38();
    sub_80013CE8();
    sub_80045450();
    sub_80014644();
    sub_80013FB4();
    sub_80044FB0();
    sub_8004E4C8(7u);
    sub_800CA390();
    sub_800CA4F8();
    sub_800CB8F8(0u);
    sub_800CA590();
    sub_80059B88();
    for (;;)
    {
        sub_80059BD8();
        if ((sub_80014B18() & 0xFFFFu) != 0u)
            sub_80014BA0();
    }
}

uint32 sub_8005BFF8(void)
{
    FUNCTION_MARKER(0x8005BFF8u, "SLES_007.30");
    ExitCriticalSection();
    return 0;
}

void sub_800117A4(uint32 address, uint32 size)
{
    FUNCTION_MARKER(0x800117A4u, "SLES_007.30");
    if (address != 0u && size >= 8u)
    {
        uint32 adjusted = size + 7u;
        if ((size & 3u) != 0u)
        {
            ++size;
            while ((size++ & 3u) != 0u)
            {
            }
            --size;
            adjusted = size + 7u;
        }
        w_u32(0x80071474u, address);
        w_u32(0x80071478u, address);
        w_u32(address, address);
        w_u32(address + 4u, (adjusted >> 3) - 1u);
        sub_8001199C();
    }
}

uint32 sub_8001199C(void)
{
    FUNCTION_MARKER(0x8001199Cu, "SLES_007.30");
    w_u32(0x000002CCu, 0x80011808u);
    w_u32(0x000002D0u, 0x800118BCu);
    w_u32(0x000002DCu, 0x80011994u);
    w_u32(0x000002E0u, 0x80011994u);
    return 0x000002E0u;
}

uint32 sub_80011B38(void)
{
    uint32 heap;
    uint32 available;
    FUNCTION_MARKER(0x80011B38u, "SLES_007.30");
    heap = r_u32(0x800716C8u);
    w_u32(0x800718BCu, 0x1F800000u);
    available = 0x80200000u - heap;
    available += 0xFFFF8000u;
    w_u32(0x80071674u, available);
    return available;
}

uint32 sub_80013CE8(void)
{
    DRAWENV *first_draw;
    DRAWENV *second_draw;
    DISPENV *first_display;
    DISPENV *second_display;
    FUNCTION_MARKER(0x80013CE8u, "SLES_007.30");
    sub_8005BF08(1u);
    InitPAD(0x80071634u, 8u, 0x8007163Cu, 8u);
    StartPAD();
    ChangeClearPAD(0u);
    ResetGraph(0);
    SetGraphDebug(0);
    InitGeom();
    sub_8005D108(192u, 120u);
    sub_8005D128(400u);
    first_draw = (DRAWENV *)psx_addr(0x800BF1D0u, sizeof(DRAWENV));
    first_display = (DISPENV *)psx_addr(0x800BF288u, sizeof(DISPENV));
    second_draw = (DRAWENV *)psx_addr(0x800BF22Cu, sizeof(DRAWENV));
    second_display = (DISPENV *)psx_addr(0x800BF29Cu, sizeof(DISPENV));
    SetDefDrawEnv(first_draw, 0, 0, 384, 251);
    SetDefDispEnv(first_display, 0, 0, 384, 251);
    SetDefDrawEnv(second_draw, 0, 251, 384, 251);
    SetDefDispEnv(second_display, 0, 251, 384, 251);
    w_u8(0x800BF1E8u, 0u);
    w_u8(0x800BF244u, 0u);
    w_u8(0x800BF1E9u, 0u);
    w_u8(0x800BF1EAu, 0u);
    w_u8(0x800BF1EBu, 0u);
    w_u8(0x800BF245u, 0u);
    w_u8(0x800BF246u, 0u);
    w_u8(0x800BF247u, 0u);
    w_u8(0x800BF1E7u, 1u);
    w_u8(0x800BF243u, 1u);
    w_u8(0x800BF1E6u, 1u);
    w_u8(0x800BF242u, 1u);
    w_u16(0x800BF1E4u, GetTPage(0, 0, 320, 0));
    w_u16(0x800BF240u, GetTPage(0, 0, 320, 0));
    w_u16(0x800BF292u, 20u);
    w_u16(0x800BF2A6u, 20u);
    w_u16(0x800BF296u, 251u);
    w_u16(0x800BF2AAu, 251u);
    SetDispMask(1);
    sub_80013894();
    legend_timer_display(first_display, r_u32(0x8006B244u));
    PutDispEnv(first_display);
    return (uint32)VSync(0);
}

uint32 sub_8005BF08(uint32 mode)
{
    uint32 previous;
    FUNCTION_MARKER(0x8005BF08u, "SLES_007.30");
    previous = r_u32(0x8006B244u);
    w_u32(0x8006B244u, mode);
    return previous;
}

uint32 sub_8005BFE8(void)
{
    FUNCTION_MARKER(0x8005BFE8u, "SLES_007.30");
    return (uint32)EnterCriticalSectionPSX();
}

uint32 sub_8005C7D8(uint32 buffer0, uint32 size0, uint32 buffer1, uint32 size1)
{
    FUNCTION_MARKER(0x8005C7D8u, "SLES_007.30");
    /* User-authorized unimplemented BIOS InitPAD boundary */

    abort();
}

uint32 sub_8005C7E8(void)
{
    FUNCTION_MARKER(0x8005C7E8u, "SLES_007.30");
    /* User-authorized unimplemented BIOS StartPAD boundary */
    abort();
}

void sub_8005D108(uint32 x, uint32 y)
{
    FUNCTION_MARKER(0x8005D108u, "SLES_007.30");
    SetGeomOffset((sint32)(sint16)(uint16)x, (sint32)(sint16)(uint16)y);
}

void sub_8005D128(uint32 distance)
{
    FUNCTION_MARKER(0x8005D128u, "SLES_007.30");
    gte_write_h((uint16)distance);
}

uint32 sub_8005BF1C(void)
{
    FUNCTION_MARKER(0x8005BF1Cu, "SLES_007.30");
    return r_u32(0x8006B244u);
}

uint32 sub_80013894(void)
{
    PSX_RECT rectangle;
    FUNCTION_MARKER(0x80013894u, "SLES_007.30");
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 512;
    rectangle.h = 256;
    ClearImage(&rectangle, 0, 0, 0);
    DrawSync(0);
    rectangle.x = 512;
    rectangle.y = 0;
    rectangle.w = 512;
    rectangle.h = 256;
    ClearImage(&rectangle, 0, 0, 0);
    DrawSync(0);
    rectangle.x = 0;
    rectangle.y = 256;
    rectangle.w = 512;
    rectangle.h = 256;
    ClearImage(&rectangle, 0, 0, 0);
    DrawSync(0);
    rectangle.x = 512;
    rectangle.y = 256;
    rectangle.w = 512;
    rectangle.h = 256;
    ClearImage(&rectangle, 0, 0, 0);
    return (uint32)DrawSync(0);
}

uint32 sub_80045450(void)
{
    uint32 table;
    uint32 sample;
    uint32 count;
    FUNCTION_MARKER(0x80045450u, "SLES_007.30");
    sub_80060DF8();
    SpuInitMalloc(80u, 0x800AF3D4u);
    w_u32(0x80071590u, 128u);
    w_u32(0x8007179Cu, 128u);
    w_u32(0x800717ECu, 122u);
    w_u32(0x800718C8u, 256u);
    w_u32(0x800715B8u, 256u);
    w_u16(0x800716D8u, 0u);
    w_u16(0x8007192Cu, 0u);
    sub_80044FB0();
    SpuSetTransferMode(0);
    w_u32(0x800C9E04u, 0xFF9Fu);
    w_u32(0x800C9E00u, 0xFFFFFFu);
    w_u16(0x800C9E08u, 0x3FFFu);
    w_u16(0x800C9E0Au, 0x3FFFu);
    w_u16(0x800C9E14u, 0x1000u);
    w_u32(0x800C9E24u, 1u);
    w_u32(0x800C9E28u, 1u);
    table = 0x800AEED8u;
    w_u16(0x800C9E0Cu, 0u);
    w_u16(0x800C9E0Eu, 0u);
    w_u32(0x800C9E2Cu, 3u);
    w_u16(0x800C9E30u, 0u);
    w_u16(0x800C9E32u, 0u);
    w_u16(0x800C9E34u, 0u);
    w_u16(0x800C9E36u, 0u);
    sample = r_u32(table);
    w_u16(0x800C9E38u, 15u);
    w_u32(0x800C9E1Cu, sample);
    SpuSetVoiceAttr((SpuVoiceAttr *)psx_addr(0x800C9E00u, sizeof(SpuVoiceAttr)));
    count = 0u;
    do
    {
        w_u32(table, 0u);
        ++count;
        table += 4u;
    } while (count < 80u);
    w_u16(0x80071734u, 0xFFFFu);
    return 0xFFFFFFFFu;
}

uint32 sub_80060DF8(void)
{
    uint32 result;
    FUNCTION_MARKER(0x80060DF8u, "SLES_007.30");
    result = _SpuInit(0u);
    w_u32(0x8006FEA4u, 0u);
    w_u32(0x8006FEA8u, 0u);
    w_u32(0x8006FEACu, 0u);
    w_u32(0x8006FDDCu, 0u);
    return result;
}

#include <stdlib.h>
void xport_main(void);
const uint32 xport_cd_ready_callback_address = 0x800700B0u;
const uint32 xport_cd_sync_callback_address = 0x800700ACu;
const uint32 xport_cd_status_address = 0x800700B8u;
const uint32 xport_cd_setloc_table_address = 0x80070024u;
const uint32 xport_spu_register_pointer_address = 0x8006FE44u;

uint32 sub_80044FB0(void)
{
    uint32 master;
    uint32 master_scale;
    uint32 cd_scale;
    uint32 cd;
    uint32 volume;
    FUNCTION_MARKER(0x80044FB0u, "SLES_007.30");
    master = r_u32(0x80071590u);
    master_scale = r_u32(0x800718C8u);
    cd_scale = r_u32(0x800715B8u);
    volume = (uint32)((sint32)(master * master_scale) >> 8) << 6;
    cd = r_u32(0x8007179Cu);
    w_u32(0x800C9D78u, 0xC3u);
    w_u16(0x800C9D7Cu, (uint16)volume);
    w_u16(0x800C9D7Eu, (uint16)volume);
    volume = (uint32)((sint32)(cd * cd_scale) >> 8) << 7;
    w_u16(0x800C9D88u, (uint16)volume);
    w_u16(0x800C9D8Au, (uint16)volume);
    SpuSetCommonAttr((SpuCommonAttr *)psx_addr(0x800C9D78u, sizeof(SpuCommonAttr)));
    return 0u;
}

uint32 sub_80014644(void)
{
    uint8 tile_packet[32];
    uint8 sprite_packet[40];
    uint32 index;
    FUNCTION_MARKER(0x80014644u, "SLES_007.30");
    CdInit();
    CdSetDebug(0);
    sub_80013ECC();
    sub_80060D58(tile_packet);
    sub_80060D28(tile_packet, 0u);
    w_u32(0x80071978u, (uint32)tile_packet[7] << 24);
    sub_80060D98(sprite_packet);
    sub_80060D28(sprite_packet, 0u);
    w_u32(0x8007197Cu, (uint32)sprite_packet[7] << 24);
    sub_800119DC(32u);
    sub_800119DC(8u);
    sub_800119DC(16u);
    w_u16(0x80071780u, GetTPage(0, 0, 0, 0));
    w_u16(0x80071782u, GetTPage(0, 1, 0, 0));
    w_u16(0x80071784u, GetTPage(0, 2, 0, 0));
    w_u16(0x80071786u, GetTPage(0, 3, 0, 0));
    sub_80018C78();
    sub_800573B0();
    srandPSX(0u);
    index = 0u;
    do
    {
        w_u16(0x800BF5E0u + 2u * (uint16)index, (uint16)randPSX());
        ++index;
    } while ((uint16)index < 256u);
    w_u16(0x8007198Cu, 0u);
    w_u16(0x800719FCu, (uint8)VSync(-1));
    w_u16(0x800719C8u, 1u);
    w_u16(0x80071A30u, 0u);
    w_u16(0x800716E0u, 1u);
    w_u16(0x800719BCu, 1u);
    sub_8001455C();
    sub_8004DBE4();
    sub_8004DCDC();
    sub_80013BAC();
    sub_80014888(4u);
    index = 0u;
    do
    {
        VSync(0);
        ++index;
    } while ((uint16)index < 50u);
    sub_80014328();
    sub_800142CC();
    sub_80014378();
    w_u16(0x80071600u, 0u);
    w_u16(0x800715B4u, 0u);
    sub_80013B64(1u, 0u, 0u, 0u);
    w_u32(0x80071588u, 0xFFFFFFFFu);
    return 0xFFFFFFFFu;
}

uint32 sub_80064008(void)
{
    uint8 response[8];
    uint32 interrupt;
    uint32 status;
    uint32 length;
    uint32 index;
    uint32 destination;
    uint32 interrupt_register;
    uint32 command;
    uint32 status_code;
    uint32 error_code;
    uint32 command_name;
    uint32 result;
    FUNCTION_MARKER(0x80064008u, "SLES_007.30");
    w_u8(r_u32(0x80070370u), 1u);
    interrupt_register = r_u32(0x8007037Cu);
    interrupt = r_u8(interrupt_register) & 7u;
    status = 0u;
    if (interrupt == 0u)
        return 0u;
    while (interrupt != (r_u8(interrupt_register) & 7u))
        interrupt = r_u8(interrupt_register) & 7u;
    length = 0u;
    do
    {
        if ((r_u8(r_u32(0x80070370u)) & 0x20u) == 0u)
            break;
        response[length] = r_u8(r_u32(0x80070374u));
        ++length;
    } while ((sint32)length < 8);
    index = length;
    if ((sint32)index < 8)
    {
        do
        {
            response[index] = 0u;
            ++index;
        } while ((sint32)index < 8);
    }
    w_u8(r_u32(0x80070370u), 1u);
    w_u8(r_u32(0x8007037Cu), 7u);
    w_u8(r_u32(0x80070378u), 7u);
    if (interrupt != 3u || r_u32(0x80070270u + 4u * r_u8(0x800700C9u)) != 0u)
    {
        if ((r_u32(0x800700B8u) & 0x10u) == 0u && (response[0] & 0x10u) != 0u)
            w_u32(0x800700C0u, r_u32(0x800700C0u) + 1u);
        status = response[0] & 0x1Du;
        w_u32(0x800700B8u, response[0]);
        w_u32(0x800700BCu, response[1]);
    }
    if (interrupt == 5u && (sint32)r_u32(0x800700B4u) > 0)
    {
        printf((const char *)psx_addr(0x800113FCu, 1u));
        if ((sint32)r_u32(0x800700B4u) > 0)
        {
            command = r_u8(0x800700C9u);
            status_code = r_u32(0x800700B8u);
            error_code = r_u32(0x800700BCu);
            command_name = r_u32(0x800700D0u + 4u * command);
            printf((const char *)psx_addr(0x80011408u, 1u), (const char *)psx_addr(command_name, 1u), status_code, error_code);
        }
    }
    switch (interrupt)
    {
        case 1u:
            if (status != 0u && length == 1u)
                status = 0u;
            w_u8(0x80070389u, status != 0u ? 5u : 1u);
            destination = 0x80071C94u;
            if (destination != 0u)
            {
                index = 7u;
                do
                {
                    w_u8(destination++, response[7u - index]);
                    --index;
                } while (index != 0xFFFFFFFFu);
            }
            w_u8(r_u32(0x80070370u), 0u);
            w_u8(r_u32(0x8007037Cu), 0u);
            result = 4u;
            break;
        case 2u:
            w_u8(0x80070388u, status != 0u ? 5u : 2u);
            destination = 0x80071C8Cu;
            if (destination != 0u)
            {
                index = 7u;
                do
                {
                    w_u8(destination++, response[7u - index]);
                    --index;
                } while (index != 0xFFFFFFFFu);
            }
            result = 2u;
            break;
        case 3u:
            if (status != 0u)
            {
                w_u8(0x80070388u, 5u);
                destination = 0x80071C8Cu;
                if (destination != 0u)
                {
                    index = 7u;
                    do
                    {
                        w_u8(destination++, response[7u - index]);
                        --index;
                    } while (index != 0xFFFFFFFFu);
                }
                result = 2u;
            }
            else if (r_u32(0x80070170u + 4u * r_u8(0x800700C9u)) != 0u)
            {
                w_u8(0x80070388u, 3u);
                destination = 0x80071C8Cu;
                if (destination != 0u)
                {
                    index = 7u;
                    do
                    {
                        w_u8(destination++, response[7u - index]);
                        --index;
                    } while (index != 0xFFFFFFFFu);
                }
                result = 1u;
            }
            else
            {
                w_u8(0x80070388u, 2u);
                destination = 0x80071C8Cu;
                if (destination != 0u)
                {
                    index = 7u;
                    do
                    {
                        w_u8(destination++, response[7u - index]);
                        --index;
                    } while (index != 0xFFFFFFFFu);
                }
                result = 2u;
            }
            break;
        case 4u:
            destination = 0x80071C9Cu;
            w_u8(0x8007038Au, 4u);
            w_u8(0x80070389u, r_u8(0x8007038Au));
            if (destination != 0u)
            {
                index = 7u;
                do
                {
                    w_u8(destination++, response[7u - index]);
                    --index;
                } while (index != 0xFFFFFFFFu);
            }
            destination = 0x80071C94u;
            if (destination != 0u)
            {
                index = 7u;
                do
                {
                    w_u8(destination++, response[7u - index]);
                    --index;
                } while (index != 0xFFFFFFFFu);
            }
            result = 4u;
            break;
        case 5u:
            destination = 0x80071C8Cu;
            w_u8(0x80070389u, 5u);
            w_u8(0x80070388u, r_u8(0x80070389u));
            if (destination != 0u)
            {
                index = 7u;
                do
                {
                    w_u8(destination++, response[7u - index]);
                    --index;
                } while (index != 0xFFFFFFFFu);
            }
            destination = 0x80071C94u;
            if (destination != 0u)
            {
                index = 7u;
                do
                {
                    w_u8(destination++, response[7u - index]);
                    --index;
                } while (index != 0xFFFFFFFFu);
            }
            result = 6u;
            break;
        default:
            puts((const char *)psx_addr(0x80011424u, 1u));
            printf((const char *)psx_addr(0x80011438u, 1u), interrupt);
            result = 0u;
            break;
    }
    return result;
}

uint32 sub_80013ECC(void)
{
    uint8 parameter[8];
    uint32 result;
    uint32 index;
    uint32 address;
    FUNCTION_MARKER(0x80013ECCu, "SLES_007.30");
    parameter[0] = 5u;
    CdControlB(14u, parameter, NULL);
    result = (uint32)CdGetToc((CdlLOC *)psx_addr(0x800AFCF0u, sizeof(CdlLOC)));
    w_u16(0x80071610u, (uint16)result);
    result = (uint32)(sint32)(sint16)(uint16)result;
    index = 1u;
    if ((sint32)result > 1)
    {
        do
        {
            address = 0x800AFCF0u + 4u * (uint16)index;
            result = sub_80063F88((const uint8 *)psx_addr(address, 3u));
            CdIntToPos((sint32)(result + 26u), (CdlLOC *)psx_addr(address, sizeof(CdlLOC)));
            ++index;
            result = (sint32)(uint16)index < (sint32)(sint16)r_u16(0x80071610u);
        } while (result != 0u);
    }
    w_u8(0x80071540u, 0u);
    return result;
}

uint32 sub_80063F88(const uint8 *position)
{
    uint32 minute;
    uint32 second;
    uint32 frame;
    FUNCTION_MARKER(0x80063F88u, "SLES_007.30");
    minute = position[0];
    second = position[1];
    minute = 10u * (minute >> 4) + (minute & 15u);
    second = 10u * (second >> 4) + (second & 15u);
    frame = position[2];
    frame = 10u * (frame >> 4) + (frame & 15u);
    return 75u * (60u * minute + second) + frame - 150u;
}

uint32 sub_80060D58(uint8 *packet)
{
    FUNCTION_MARKER(0x80060D58u, "SLES_007.30");
    packet[3] = 7u;
    packet[7] = 36u;
    return 36u;
}

uint32 sub_80060D28(uint8 *packet, uint32 enabled)
{
    uint32 value;
    FUNCTION_MARKER(0x80060D28u, "SLES_007.30");
    if (enabled != 0u)
        value = (uint32)packet[7] | 1u;
    else
        value = (uint32)packet[7] & 0xFEu;
    packet[7] = (uint8)value;
    return value;
}

uint32 sub_80060D98(uint8 *packet)
{
    FUNCTION_MARKER(0x80060D98u, "SLES_007.30");
    packet[3] = 9u;
    packet[7] = 44u;
    return 44u;
}

uint32 sub_800119DC(uint32 size)
{
    uint32 previous;
    uint32 next;
    FUNCTION_MARKER(0x800119DCu, "SLES_007.30");
    if ((size & 3u) != 0u)
        size = size + 4u - (size & 3u);
    previous = r_u32(0x800718BCu);
    next = previous + size;
    w_u32(0x800718BCu, next);
    if (next > 0x1F800400u)
    {
        for (;;)
        {
        }
    }
    return previous;
}

uint32 sub_80018C78(void)
{
    uint32 index;
    uint32 address;
    FUNCTION_MARKER(0x80018C78u, "SLES_007.30");
    index = 0u;
    do
    {
        address = 0x800B0120u + 56u * (uint16)index;
        ++index;
        w_u32(address, 0u);
        w_u32(address + 4u, 0u);
        w_u32(address + 12u, 0u);
    } while ((uint16)index < 512u);
    index = 0u;
    do
    {
        w_u32(0x80071570u + 4u * (uint16)index, 0u);
        ++index;
    } while ((uint16)index < 2u);
    return 0u;
}

uint32 sub_800573B0(void)
{
    uint32 index;
    FUNCTION_MARKER(0x800573B0u, "SLES_007.30");
    index = 0u;
    do
    {
        w_u32(0x800BFD08u + 40u * (uint16)index, 0u);
        ++index;
    } while ((uint16)index < 32u);
    return 0u;
}

uint32 sub_8001455C(void)
{
    uint32 index;
    uint32 byte_index;
    uint32 name;
    uint32 address;
    uint32 value;
    FUNCTION_MARKER(0x8001455Cu, "SLES_007.30");
    index = 0u;
    do
    {
        name = r_u32(0x80068528u + 4u * (uint16)index);
        address = 0x800AF6F2u + 12u * (uint16)index;
        byte_index = 0u;
        do
        {
            value = r_u8(name + (uint16)byte_index);
            w_u8(address + (uint16)byte_index, (uint8)value);
            ++byte_index;
        } while ((uint16)byte_index < 6u);
        address = 12u * (uint16)index;
        value = r_u32(0x80068500u + 4u * (uint16)index);
        w_u8(0x800AF6F1u + address, (uint8)(20u - index));
        w_u32(0x800AF6F8u + address, value);
        w_u8(0x800AF6F0u + address, (uint8)((uint16)index % 3u));
        ++index;
    } while ((uint16)index < 10u);
    return 0u;
}

uint32 sub_8004DBE4(void)
{
    uint32 file_storage[6];
    uint8 path[32];
    uint8 *file;
    uint32 entry_sector;
    uint32 result;
    FUNCTION_MARKER(0x8004DBE4u, "SLES_007.30");
    file = (uint8 *)file_storage;
    sub_8004DB50((const uint8 *)psx_addr(0x80010A00u, 1u), path);
    while (CdSearchFile((CdlFILE *)file, (const char *)path) == NULL)
    {
    }
    entry_sector = sub_80063F88(file);
    while (sub_8004DA84(file, 0x800C1CFCu, 2u) == 0u)
    {
    }
    CdIntToPos((sint32)(entry_sector + 2u), (CdlLOC *)file);
    while (sub_8004DA84(file, 0x800C5D68u, 2u) == 0u)
    {
    }
    sub_8004DB50((const uint8 *)psx_addr(0x80010A0Cu, 1u), path);
    while (CdSearchFile((CdlFILE *)file, (const char *)path) == NULL)
    {
    }
    result = sub_80063F88(file);
    w_u32(0x800719E0u, result);
    return result;
}

uint8 *sub_8004DB50(const uint8 *name, uint8 *path)
{
    uint32 read_index;
    uint32 write_index;
    uint8 *result;
    FUNCTION_MARKER(0x8004DB50u, "SLES_007.30");
    read_index = 0u;
    path[0] = 92u;
    write_index = 1u;
    if (name[0] != 0u)
    {
        do
        {
            path[(uint16)write_index] = name[(uint16)read_index];
            ++read_index;
            ++write_index;
        } while (name[(uint16)read_index] != 0u);
    }
    path[(uint16)write_index] = 59u;
    path[(uint16)(write_index + 1u)] = 49u;
    result = path + (uint16)(write_index + 2u);
    *result = 0u;
    return result;
}

uint32 sub_800660D8(uint32 status, uint32 argument)
{
    uint32 position_storage[4];
    uint8 *position;
    uint32 result;
    uint32 callback;
    uint32 reason;
    uint32 destination;
    uint32 words;
    FUNCTION_MARKER(0x800660D8u, "SLES_007.30");
    position = (uint8 *)position_storage;
    w_u32(0x80070404u, argument);
    if ((status & 0xFFu) == 1u)
    {
        if ((sint32)r_u32(0x800703E8u) > 0)
        {
            if (r_u32(0x800703E4u) == 512u)
            {
                if ((r_u32(0x80070018u) & 1u) != 0u)
                {
                    xport_cd_data_guest_callback(0u);
                    sub_80063E20(xport_guest_buffer_address(position, 16u), 3u);
                    CdDataSync(0);
                    xport_cd_data_guest_callback(0x80066350u);
                }
                else
                {
                    sub_80063E00(xport_guest_buffer_address(position, 16u), 3u);
                }
                result = sub_80063F88(position);
                if (result != r_u32(0x800703F4u))
                {
                    puts((const char *)psx_addr(0x800116E4u, 1u));
                    w_u32(0x800703E8u, 0xFFFFFFFFu);
                }
            }
            if ((r_u32(0x80070018u) & 1u) != 0u)
            {
                destination = r_u32(0x800703DCu);
                words = r_u32(0x800703E4u);
                sub_80063E20(destination, words);
            }
            else
            {
                destination = r_u32(0x800703DCu);
                words = r_u32(0x800703E4u);
                sub_80063E00(destination, words);
                words = r_u32(0x800703E4u);
                destination = r_u32(0x800703DCu);
                w_u32(0x800703DCu, destination + (words << 2));
                w_u32(0x800703E8u, r_u32(0x800703E8u) - 1u);
                w_u32(0x800703F4u, r_u32(0x800703F4u) + 1u);
            }
        }
    }
    else
    {
        w_u32(0x800703E8u, 0xFFFFFFFFu);
    }
    w_u32(0x800703ECu, (uint32)VSync(-1));
    if ((sint32)r_u32(0x800703E8u) < 0)
        sub_80066424(1u);
    result = (uint32)VSync(-1);
    if ((sint32)(r_u32(0x800703F0u) + 1200u) < (sint32)result)
        w_u32(0x800703E8u, 0xFFFFFFFFu);
    result = r_u32(0x800703E8u);
    if (result == 0u)
        goto complete;
    result = (uint32)VSync(-1);
    if ((sint32)(r_u32(0x800703F0u) + 1200u) >= (sint32)result)
        return result;
complete:
    CdReadyCallbackPSX(r_u32(0x800703FCu));
    if ((r_u32(0x80070018u) & 1u) != 0u)
        xport_cd_data_guest_callback(r_u32(0x80070400u));
    CdControlB(9u, NULL, NULL);
    result = CdSyncCallbackPSX(r_u32(0x800703F8u));
    callback = r_u32(0x80070014u);
    if (callback != 0u)
    {
        reason = r_u32(0x800703E8u) == 0u ? 2u : 5u;
        result = (uint32)xport_guest_call2(callback, reason, argument);
    }
    return result;
}

uint32 sub_80063E00(uint32 destination, uint32 words)
{
    FUNCTION_MARKER(0x80063E00u, "SLES_007.30");
    return CD_getsector(destination, words) == 0;
}
