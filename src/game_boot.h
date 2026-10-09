#pragma once
#include "psx.h"

sint32 legend_boot(void);
sint32 legend_skip_movies(void);
sint32 CdInit(void);
CdlLOC *CdIntToPos(sint32 sector, CdlLOC *position);
sint32 CdDataSync(sint32 mode);
sint32 CD_getsector(uint32 destination, uint32 words);
sint32 xport_guest_call2(uint32 target, uint32 first, uint32 second);
uint32 xport_cd_data_guest_callback(uint32 callback);
