#include "psx.h"
#include "psx_spu.h"
#include "xport_trace.h"
#include <string.h>

/* Native staging occupies the area above the game's heap limit */
enum { LEGEND_CD_STAGING = 0x801FE000u };
static uint8 mode_byte;
static sint32 reading;
static uint32 pending_bytes;
extern sint32 CdControlBPSX(uint8 command, uint8 *parameter, uint8 *result);
extern sint32 CD_getsector(uint32 destination, uint32 words);

/* Original CdSetDebug swaps the image's diagnostic level */
uint32 legend_cd_set_debug(uint32 level)
{
    uint32 previous = r_u32(0x800700B4u);
    w_u32(0x800700B4u, level);
    return previous;
}

sint32 legend_cd_control(uint8 command, uint8 *parameter, uint8 *result)
{
    sint32 ok = CdControlBPSX(command, parameter, result);
    if (ok && command == 14u && parameter)
        mode_byte = parameter[0];
    if (command == 2u || command == 6u || command == 27u || command == 9u || command == 8u)
        pending_bytes = 0u;
    if (command == 6u || command == 27u)
        reading = ok;
    else if (command == 9u || command == 8u)
        reading = 0;
    return ok;
}

sint32 legend_cd_control_b(uint8 command, uint8 *parameter, uint8 *result)
{
    return legend_cd_control(command, parameter, result);
}

sint32 legend_cd_ready(sint32 mode, uint8 *result)
{
    sint32 status = CdlNoIntr;
    if (mode != 0 && mode != 1)
        status = CdlDiskError;
    else if (reading)
    {
        uint32 bytes = (mode_byte & 0x20u) ? 2340u : 2048u;
        if (!pending_bytes && CD_getsector(LEGEND_CD_STAGING, bytes / 4u))
            pending_bytes = bytes;
        status = pending_bytes ? CdlDataReady : CdlDiskError;
    }
    if (result)
        result[0] = (uint8)status;
    return status;
}

sint32 legend_cd_getsector(uint32 destination, uint32 words)
{
    if (words > 585u || legend_cd_ready(1, NULL) != CdlDataReady || words * 4u > pending_bytes)
        return 0;
    if (!xport_guest_copy(xport_guest_ref(destination), xport_guest_ref(LEGEND_CD_STAGING), words * 4u))
        return 0;
    pending_bytes = 0u;
    return 1;
}
