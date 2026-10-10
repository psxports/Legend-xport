#include "psx.h"
#include "psx_gpu.h"
#include "xport.h"
#include "game_native_adapters.h"
#include "game_cd.h"
#include "game_timer.h"
#include "game_draft_signatures.h"
#include "psx_stream.h"
extern uint32 legend_bios_card_info(uint32 channel);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reviewed SLES_007.30 SDK aliases are recorded in status/analysis.sqlite */
static uint32 sdk_missing(const char *name)
{
    fprintf(stderr, "Missing native SDK adapter: %s\n", name);
    fflush(stderr);
    abort();
}

static void *sdk_pointer(uint32 address, size_t size)
{
    return address ? legend_native_pointer(address, size) : NULL;
}

uint32 sub_8005B278(uint32 mode)
{
    /* Present completed VRAM at the native display boundary */
    if ((sint32)mode >= 0)
        gpu_present();
    return (uint32)VSync((sint32)mode);
}

uint32 sub_8005CC48(uint32 matrix, uint32 input, uint32 output)
{
    uint32 controls[5], values[3], high[3], low[3], high_mac[3], result[3], i;
    uint32 *destination;
    memcpy(controls, sdk_pointer(matrix, 20u), sizeof(controls));
    for (i = 0; i < 5u; ++i)
        xport_gte_write_control(i, controls[i]);
    memcpy(values, sdk_pointer(input, 12u), sizeof(values));
    for (i = 0; i < 3u; ++i)
    {
        uint32 magnitude = values[i];
        if ((sint32)magnitude < 0)
        {
            magnitude = 0u - magnitude;
            high[i] = 0u - (uint32)((sint32)magnitude >> 15);
            low[i] = 0u - (magnitude & 0x7FFFu);
        }
        else
        {
            high[i] = (uint32)((sint32)magnitude >> 15);
            low[i] = magnitude & 0x7FFFu;
        }
        xport_gte_write_data(9u + i, high[i]);
    }
    xport_gte_execute(0x41E012u);
    for (i = 0; i < 3u; ++i)
        high_mac[i] = xport_gte_read_data(25u + i);
    for (i = 0; i < 3u; ++i)
        xport_gte_write_data(9u + i, low[i]);
    xport_gte_execute(0x49E012u);
    for (i = 0; i < 3u; ++i)
        result[i] = xport_gte_read_data(25u + i) + (high_mac[i] << 3);
    destination = sdk_pointer(output, 12u);
    for (i = 0; i < 3u; ++i)
        xport_store_le32(destination + i, result[i]);
    return output;
}

uint32 sub_8005CDA8(uint32 input, uint32 output)
{
    uint32 vector[2], i;
    uint32 *destination;
    memcpy(vector, sdk_pointer(input, 8u), sizeof(vector));
    xport_gte_write_data(0u, vector[0]);
    xport_gte_write_data(1u, vector[1]);
    xport_gte_execute(0x486012u);
    destination = sdk_pointer(output, 12u);
    for (i = 0; i < 3u; ++i)
        xport_store_le32(destination + i, xport_gte_read_data(9u + i));
    return output;
}

uint32 sub_8005CDD8(uint32 matrix, uint32 input, uint32 output)
{
    uint32 controls[5], vector[2], i;
    const uint32 *source = sdk_pointer(matrix, 20u);
    memcpy(controls, source, sizeof(controls));
    for (i = 0; i < 5u; ++i)
        xport_gte_write_control(i, controls[i]);
    source = sdk_pointer(input, 8u);
    memcpy(vector, source, sizeof(vector));
    xport_gte_write_data(0u, vector[0]);
    xport_gte_write_data(1u, vector[1]);
    xport_gte_execute(0x486012u);
    /* Original ApplyMatrix stores three words without VECTOR padding */
    source = sdk_pointer(output, 12u);
    for (i = 0; i < 3u; ++i)
        xport_store_le32((uint32 *)source + i, xport_gte_read_data(25u + i));
    return output;
}

void sub_8005CF98(uint32 matrix)
{
    SetColorMatrix(sdk_pointer(matrix, sizeof(MATRIX)));
}

uint32 sub_8005D138(uint32 rotation, uint32 matrix)
{
    RotMatrix(sdk_pointer(rotation, sizeof(SVECTOR)), sdk_pointer(matrix, sizeof(MATRIX)));
    return matrix;
}

uint32 sub_8005D3C8(uint32 rotation, uint32 matrix)
{
    RotMatrixYXZ(sdk_pointer(rotation, sizeof(SVECTOR)), sdk_pointer(matrix, sizeof(MATRIX)));
    return matrix;
}

static sint32 sdk_mul12(sint32 a, sint32 b)
{
    return (sint32)((uint32)a * (uint32)b) >> 12;
}

static void sdk_table_trig(sint16 angle, sint32 *sine, sint32 *cosine)
{
    uint32 magnitude = angle < 0 ? (uint32)(-(sint32)angle) : (uint32)angle;
    uint32 packed = r_u32(0x8006BC24u + 4 * (magnitude & 4095u));
    *sine = angle < 0 ? -(sint32)(sint16)packed : (sint32)(sint16)packed;
    *cosine = (sint32)packed >> 16;
}

uint32 sub_8005D658(uint32 rotation, uint32 matrix)
{
    sint16 *angles = sdk_pointer(rotation, 6), *m = sdk_pointer(matrix, 18);
    sint32 sx, cx, sy, cy, sz, cz, t;
    sdk_table_trig(angles[2], &sz, &cz);
    sdk_table_trig(angles[1], &sy, &cy);
    m[1] = (sint16)-sz;
    m[0] = (sint16)sdk_mul12(cz, cy);
    m[2] = (sint16)sdk_mul12(cz, sy);
    sdk_table_trig(angles[0], &sx, &cx);
    m[4] = (sint16)sdk_mul12(cx, cz);
    m[7] = (sint16)sdk_mul12(sx, cz);
    t = sdk_mul12(sz, sy);
    m[8] = (sint16)(sdk_mul12(t, sx) + sdk_mul12(cx, cy));
    m[5] = (sint16)(sdk_mul12(t, cx) - sdk_mul12(sx, cy));
    t = sdk_mul12(sz, cy);
    m[6] = (sint16)(sdk_mul12(t, sx) - sdk_mul12(cx, sy));
    m[3] = (sint16)(sdk_mul12(t, cx) + sdk_mul12(sx, sy));
    return matrix;
}

uint32 sub_8005DFE4(uint32 mode)
{
    return (uint32)DrawSync((sint32)mode);
}

uint32 sub_8005E290(uint32 rectangle, uint32 pixels)
{
    PSX_RECT *rect = sdk_pointer(rectangle, sizeof(PSX_RECT));
    size_t bytes = (size_t)(uint16)rect->w * (uint16)rect->h * 2u;
    return (uint32)LoadImagePSX(rect, sdk_pointer(pixels, bytes));
}

uint32 sub_8005E814(uint32 environment)
{
    DISPENV *display = sdk_pointer(environment, sizeof(DISPENV));
    legend_timer_display(display, r_u32(0x8006B244u));
    PutDispEnv(display);
    return environment;
}

uint32 sub_8005EEB8(uint32 packet, uint32 draw, uint32 dither, uint32 page, uint32 window)
{
    void *destination = sdk_pointer(packet, 12u);
    PSX_RECT *rect = sdk_pointer(window, sizeof(PSX_RECT));
    SetDrawMode(destination, draw, dither, (uint16)page, rect);
    /* MIPS returns the texture-window command from its final helper */
    return psx_texture_window(rect);
}

uint32 sub_80060DB8(uint32 first, uint32 second)
{
    return (uint32)MargePrim(first, second);
}

uint32 sub_80063C94(uint32 command, uint32 parameter, uint32 result)
{
    return (uint32)legend_cd_control_b((uint8)command, sdk_pointer(parameter, 8u), sdk_pointer(result, 8u));
}

uint32 sub_80065768(uint32 result, uint32 filename)
{
    CdlFILE *found = CdSearchFile(sdk_pointer(result, sizeof(CdlFILE)), sdk_pointer(filename, 1u));
    return found ? result : 0u;
}

uint32 sub_80067A6C(uint32 input, uint32 mode)
{
    DecDCTin(sdk_pointer(input, 4u), (sint32)mode);
    return 0u;
}

uint32 sub_80067AE8(uint32 output, uint32 words)
{
    DecDCTout(sdk_pointer(output, (words & ~31u) * 4u), (sint32)words);
    return 0u;
}

uint32 sub_8005C0B8(uint32 counter, uint32 target, uint32 mode)
{
    return legend_timer_set(counter, target, mode);
}

uint32 sub_8005C154(uint32 counter)
{
    return legend_timer_get(counter);
}

uint32 sub_8005C958(uint32 angle)
{
    return (uint32)rsin((sint32)angle);
}

uint32 sub_8005CA28(uint32 angle)
{
    return (uint32)rcos((sint32)angle);
}

uint32 sub_8005CBB8(uint32 value)
{
    return SquareRoot0((sint32)value);
}

void sub_8005CF68(uint32 ignored_matrix)
{
    /* This reviewed SDK body is specialized to the scratchpad matrix */
    SetRotMatrix(sdk_pointer(0x1F800000u, sizeof(MATRIX)));
}

void sub_8005D0D8(uint32 x, uint32 y)
{
    ReadGeomOffset(sdk_pointer(x, sizeof(sint32)), sdk_pointer(y, sizeof(sint32)));
}

uint32 sub_8005DC2C(uint32 environment, uint32 x, uint32 y, uint32 width, uint32 height)
{
    SetDefDispEnv(sdk_pointer(environment, sizeof(DISPENV)), (sint32)x, (sint32)y, (sint32)width, (sint32)height);
    return environment;
}

uint32 sub_8005E168(uint32 rectangle, uint32 red, uint32 green, uint32 blue)
{
    return (uint32)ClearImage(sdk_pointer(rectangle, sizeof(PSX_RECT)), (uint8)red, (uint8)green, (uint8)blue);
}

uint32 sub_8005E2F0(uint32 rectangle, uint32 pixels)
{
    PSX_RECT *rect = sdk_pointer(rectangle, sizeof(PSX_RECT));
    size_t bytes = (size_t)(uint16)rect->w * (uint16)rect->h * 2u;
    return (uint32)StoreImage(rect, sdk_pointer(pixels, bytes));
}

uint32 sub_80060CC8(uint32 x, uint32 y)
{
    return GetClut((sint32)x, (sint32)y);
}

uint32 sub_800623F8(uint32 address)
{
    return SpuSetTransferStartAddr(address);
}

uint32 sub_80062488(uint32 mode)
{
    return (uint32)SpuIsTransferCompleted((sint32)mode);
}

uint32 sub_80066888(uint32 mode)
{
    stream_set_read_mode(mode);
    return (uint32)CdRead2((sint32)mode);
}

uint32 sub_800678A8(uint32 destination, uint32 source, uint32 bytes)
{
    memcpy(sdk_pointer(destination, bytes), sdk_pointer(source, bytes), bytes);
    return destination;
}

uint32 sub_80060C88(uint32 depth, uint32 blend, uint32 x, uint32 y)
{
    return GetTPage((sint32)depth, (sint32)blend, (sint32)x, (sint32)y);
}

uint32 sub_80061B58(uint32 bytes)
{
    return (uint32)SpuMalloc((sint32)bytes);
}

void sub_80062128(uint32 address)
{
    SpuFree(address);
}

void sub_800621A8(uint32 on_off, uint32 voices)
{
    SpuSetKey((sint32)on_off, voices);
}

void sub_800628B8(uint32 attributes)
{
    SpuSetVoiceAttr(sdk_pointer(attributes, sizeof(SpuVoiceAttr)));
}

void sub_80062368(uint32 attributes)
{
    SpuSetVoiceAttr(sdk_pointer(attributes, sizeof(SpuVoiceAttr)));
    SpuSetKey(1, xport_load_le32((uint32 *)sdk_pointer(attributes, 4u)));
}

uint32 sub_8005E4D0(uint32 ordering_table, uint32 count)
{
    ClearOTagR(sdk_pointer(ordering_table, (size_t)count * 4u), (sint32)count);
    return ordering_table;
}

uint32 sub_8005E648(uint32 environment)
{
    PutDrawEnv(sdk_pointer(environment, sizeof(DRAWENV)));
    return environment;
}

void sub_8005E5D8(uint32 ordering_table)
{
    uint32 address = ordering_table & 0xFFFFFFu, nodes = 0;
    while (address != 0xFFFFFFu)
    {
        uint32 tag, count, index = 0, packet[256];
        uint32 *source;
        if ((address & 3u) || address >= 0x200000u || ++nodes > 65536u)
            sdk_missing("DrawOTag invalid guest chain");
        tag = r_u32(address);
        count = tag >> 24;
        source = sdk_pointer(address + 4u, count * 4u);
        /* Submit leading state and NOP commands before the primitive */
        while (index < count)
        {
            uint32 command = source[index] >> 24;
            if (command != 0 && (command < 0xE1u || command > 0xE6u))
                break;
            packet[0] = 0x01000000u;
            packet[1] = source[index++];
            gpu_packet(packet);
        }
        if (index < count)
        {
            uint32 remaining = count - index;
            packet[0] = remaining << 24;
            memcpy(packet + 1, source + index, remaining * 4u);
            gpu_packet(packet);
        }
        address = tag & 0xFFFFFFu;
    }
    /* Publish the completed native rendering without changing guest frame timing */
    gpu_present();
}

uint32 draft_sdk_sqrt(uint32 value)
{
    return SquareRoot0((sint32)value);
}

uint32 draft_sdk_cd_mix(uint8 *buffer)
{
    return (uint32)CdMix((CdlATV *)buffer);
}

uint32 draft_sdk_open_event(uint32 counter)
{
    return legend_timer_reset(counter);
}

uint32 draft_sdk_enable_event(uint32 counter)
{
    return legend_timer_start(counter);
}

uint32 draft_sdk_spu_write(uint32 source, uint32 bytes, uint32 unused_mode)
{
    /* The reviewed _spu_Fw body does not consume a2 */

    return SpuWrite(sdk_pointer(source, bytes), bytes);
}

uint32 sub_80066424()
{
    return sdk_missing("CDREAD_OBJ_34C retry / 80066424");
}

extern void draft_gte_control(uint32 index, uint32 value);

void sub_8005CAC8(uint32 far_distance, uint32 projection)
{
    sint32 numerator = (sint32)((0u - far_distance) << 6), denominator = (sint32)projection;
    if (!denominator || (numerator == (-2147483647 - 1) && denominator == -1))
    {
        fprintf(stderr, "SetFogFar MIPS division trap: far=%d h=%d\n", (sint32)far_distance, denominator);
        abort();
    }
    xport_gte_write_control(27, (uint32)(numerator / denominator));
    xport_gte_write_control(28, 0x01400000u);
}

uint32 sub_80068444()
{
    return sdk_missing("DsDataCallback / 80068444");
}

static LegendVideoCallback video_output_callback;

static void video_output_complete(void)
{
    if (video_output_callback)
        video_output_callback();
}

LegendVideoCallback sub_80067BA4(LegendVideoCallback callback)
{
    LegendVideoCallback previous = video_output_callback;
    video_output_callback = callback;
    DecDCToutCallback(callback ? video_output_complete : NULL);
    return previous;
}

uint32 sub_80067FC8(uint32 stream, uint32 output, uint32 table)
{
    return (uint32)DecDCTvlc2(sdk_pointer(stream, 4u), sdk_pointer(output, 4u), sdk_pointer(table, sizeof(DECDCTTAB)));
}

uint32 sub_80066B98(uint32 stream)
{
    return StFreeRing(sdk_pointer(stream, 4u));
}

uint32 sub_80066D68(void)
{
    StCdInterrupt();
    return 0u;
}

uint32 sub_80067908(uint32 mode)
{
    DecDCTReset((sint32)mode);
    return 0u;
}

uint32 sub_80067F98(uint32 size)
{
    return (uint32)DecDCTvlcSize2((sint32)size);
}

uint32 sub_80068318(uint32 table)
{
    DecDCTvlcBuild(sdk_pointer(table, sizeof(DECDCTTAB)));
    return 0u;
}

uint32 sub_800634A8(uint32 ring, uint32 sectors)
{
    StSetRing(sdk_pointer(ring, (size_t)sectors * 2048u), sectors);
    return 0u;
}

static uint32 video_frame_callback, video_end_callback;
extern void draft_guest_call_void(uint32 callback);

static void video_frame_complete(void)
{
    draft_guest_call_void(video_frame_callback);
}

static void video_stream_complete(void)
{
    draft_guest_call_void(video_end_callback);
}

uint32 sub_80066B08(uint32 mode, uint32 start, uint32 end, uint32 callback1, uint32 callback2)
{
    video_frame_callback = callback1;
    video_end_callback = callback2;
    StSetStream(mode, start, end, callback1 ? video_frame_complete : NULL, callback2 ? video_stream_complete : NULL);
    return 0u;
}

uint32 draft_boundary_80066C88(uint32 *data, uint32 *header)
{
    uint32 *native_data, *native_header, result;
    result = StGetNext(&native_data, &native_header);
    if (!result)
    {
        /* Both outputs remain inside the caller-owned guest ring */
        if ((uint8 *)native_data < DRAM || (uint8 *)native_data >= DRAM + PSX_DRAM_SIZE || (uint8 *)native_header < DRAM || (uint8 *)native_header >= DRAM + PSX_DRAM_SIZE)
            return sdk_missing("STR output outside guest ring");
        *data = 0x80000000u | (uint32)((uint8 *)native_data - DRAM);
        *header = 0x80000000u | (uint32)((uint8 *)native_header - DRAM);
    }
    return result;
}

uint32 sub_8005C018(uint32 path, uint32 mode)
{
    return sdk_missing("BIOS open / 8005C018");
}

uint32 sub_8005C028(uint32 handle, uint32 destination, uint32 size)
{
    return sdk_missing("BIOS read / 8005C028");
}

uint32 sub_8005C048(uint32 handle)
{
    return sdk_missing("BIOS close / 8005C048");
}

uint32 sub_80068468(uint32 channel)
{
    return (uint32)legend_bios_card_info(channel);
}

uint32 sub_80068478(uint32 channel)
{
    return psx_bios_card_load_guest(channel);
}

uint32 sub_800684A8(uint32 channel)
{
    return sdk_missing("BIOS card_clear / 800684A8");
}

void sub_800630B8(uint32 attributes)
{
    SpuGetVoiceAttr(sdk_pointer(attributes, sizeof(SpuVoiceAttr)));
}
