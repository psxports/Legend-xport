#pragma once
#include "psx.h"
sint32 legend_cd_control(uint8 command, uint8 *parameter, uint8 *result);
sint32 legend_cd_control_b(uint8 command, uint8 *parameter, uint8 *result);
sint32 legend_cd_ready(sint32 mode, uint8 *result);
sint32 legend_cd_getsector(uint32 destination, uint32 words);
uint32 legend_cd_set_debug(uint32 level);
#define CdControl legend_cd_control
#define CdControlB legend_cd_control_b
#define CdReady legend_cd_ready
#define CD_getsector legend_cd_getsector
#define CdSetDebug legend_cd_set_debug
