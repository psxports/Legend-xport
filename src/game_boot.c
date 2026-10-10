#include "psx.h"
#include "xport.h"
#include "game_boot.h"
#include "game_native_adapters.h"
#include "psx_spu.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
extern void legend_bios_init(void);
extern sint32 legend_bios_configure(sint32 events, sint32 threads, uint32 stack_top);
extern void xport_bind_native_spu_transfer(void);

static sint32 skip_movies;

sint32 legend_skip_movies(void)
{
    return skip_movies;
}

sint32 legend_boot(void)
{
    PSX_EXE executable = {"../orig/SLES_007.30", 0x80010000u, 0x8007152Cu, 0x800C9E50u, 0x8006A0A4u, 0x800C9E50u, 0u};
    char directory[MAX_PATH];
    char *slash;
    DWORD length = GetModuleFileNameA(NULL, directory, sizeof(directory));
    CdlLOC toc[23];
    uint32 sector = 0u;
    sint32 track;
    const SpuMallocGuestBinding heap_binding = {0x8006FE6Cu, 0x8006FE74u, 0x8006FEA4u, 0x8006FEA8u, 0x8006FEACu, 0x8006FDDCu, 0x8006FDE0u};
    if (!length || length >= sizeof(directory))
        return 0;
    slash = strrchr(directory, '\\');
    if (!slash)
        return 0;
    *slash = '\0';
    if (!SetCurrentDirectoryA(directory) || !xport_psx_exe_load(&executable))
    {
        xport_message_error("Legend", "Cannot load the original executable: ../orig/SLES_007.30");
        return 0;
    }
    skip_movies = GetPrivateProfileIntA("Playback", "SkipMovies", 0, ".\\Legend.ini") != 0;
    /* The original bootstrap derives its BIOS heap from the loaded stack settings */
    w_u32(0x8006A0A8u, r_u32(0x80071480u) - 8u - r_u32(0x8007147Cu) - 0x000C9E50u);
    /* Original bootstrap calls InitHeap at the BSS end plus four bytes */
    if (!legend_bios_configure(16, 4, 0x801FFF00u))
        return 0;
    psx_bios_init_user_heap(r_u32(0x8006A0A4u) + 4u, r_u32(0x8006A0A8u));
    if (!r_u32(0xA0000120u) || psx_bios_events_failed())
        return 0;
    legend_bios_init();
    legend_native_adapters_init();
    xport_bind_native_spu_transfer();
    if (!spu_bind_malloc_guest(&heap_binding) || !cd_mount_cue("DATA/LEGEND_DATA.cue"))
    {
        xport_message_error("Legend", "Cannot bind native SPU memory or mount the original data track");
        return 0;
    }
    for (track = 1; track <= 23; ++track)
    {
        char path[128];
        size_t bytes;
        sprintf_s(path, sizeof(path), "../iso/Legend (Europe) (Track %02d).bin", track);
        if (!xport_file_size(path, &bytes) || bytes % 2352u != 0u || bytes / 2352u > UINT32_MAX - sector)
        {
            xport_message_error("Legend", "Cannot read the original disc track layout");
            return 0;
        }
        if (!CdIntToPos((sint32)(sector + (track == 1 ? 0u : 150u)), &toc[track - 1]))
            return 0;
        sector += (uint32)(bytes / 2352u);
    }
    if (!CdSetToc(toc, 23))
        return 0;
    return 1;
}
