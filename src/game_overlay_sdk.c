#include "psx.h"
#include "game_native_adapters.h"
#include <stdio.h>
#include <stdlib.h>

static uint32 missing_directory_service(const char *name)
{
    fprintf(stderr, "Legend BIOS adapter missing: %s\n", name);
    fflush(stderr);
    abort();
}

uint32 sub_8005C228(uint32 path, uint32 directory)
{
    return missing_directory_service("firstfile / 8005C228");
}

uint32 sub_8005C068(uint32 directory)
{
    return missing_directory_service("nextfile / BIOS B0:43");
}

uint32 sub_8005C058(uint32 path)
{
    return missing_directory_service("format / BIOS B0:41");
}

uint32 sub_8005C078(uint32 path)
{
    return missing_directory_service("delete / BIOS B0:45");
}

uint32 sub_8005C038(uint32 handle, uint32 source, uint32 size)
{
    return missing_directory_service("write / BIOS B0:35");
}

uint32 sub_8005C088(uint32 code)
{
    return missing_directory_service("Krom2RawAdd / BIOS B0:51");
}

uint32 sub_80060D78(uint32 address)
{
    uint8 *packet = legend_native_pointer(address, 8u);
    packet[3] = 5;
    packet[7] = 0x28;
    return 0x28u;
}
