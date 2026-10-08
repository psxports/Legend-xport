#pragma once
#include "psx.h"
void legend_native_adapters_init(void);
void *legend_native_pointer(uint32 address, size_t size);
uint32 draft_local_address(void *memory, uint32 size);
uint32 draft_unknown_argument(const char *owner, uint32 slot);
uint32 draft_unknown_return(const char *owner);
