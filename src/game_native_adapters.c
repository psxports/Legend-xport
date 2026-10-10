#include "psx.h"
#include "xport_trace.h"
#include "psx_spu.h"
#include "game_native_adapters.h"
#include "game_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Borrowed buffers remain owned by their native caller */
typedef struct NativeSpan
{
    uint8 *memory;
    uint32 base, size;
} NativeSpan;

static NativeSpan spans[4096];
static uint32 span_count, next_address = 0x1E000000u;
extern uint32 sub_80011808(uint32 size);
extern uint32 sub_800118BC(uint32 address);

static void adapter_failure(const char *kind, const char *owner, uint32 value)
{
    fprintf(stderr, "Legend native adapter: %s, %s, 0x%08X\n", kind, owner, value);
    fflush(stderr);
    abort();
}

static uint8 *borrowed_pointer(uint32 address, size_t size)
{
    uint32 i;
    for (i = span_count; i > 0; --i)
    {
        NativeSpan *span = &spans[i - 1u];
        if (address >= span->base && address - span->base <= span->size && size <= span->size - (address - span->base))
            return span->memory + (address - span->base);
    }
    return NULL;
}

void *legend_native_pointer(uint32 address, size_t size)
{
    uint32 physical = address & 0x1FFFFFFFu;
    uint8 *memory = borrowed_pointer(physical, size);
    if (memory)
        return memory;
    if (physical >= 0x1E000000u && physical < 0x1F000000u)
        adapter_failure("Expired or invalid borrowed span", "pointer", address);
    return psx_addr(address, size);
}

uint32 draft_local_address(void *memory, uint32 size)
{
    uint32 i, aligned;
    if (!memory || !size)
        adapter_failure("Invalid borrowed buffer", "local address", size);
    for (i = 0; i < span_count; ++i)
        if (spans[i].memory == memory && spans[i].size >= size)
            return spans[i].base;
    if (size > 0x00FFFFF0u)
        adapter_failure("Borrowed buffer too large", "local address", size);
    aligned = (size + 15u) & ~15u;
    if (span_count == 4096u || aligned > 0x1F000000u - next_address)
        adapter_failure("Borrowed span capacity exhausted", "local address", size);
    spans[span_count].memory = (uint8 *)memory;
    spans[span_count].base = next_address;
    spans[span_count].size = size;
    ++span_count;
    next_address += aligned;
    return spans[span_count - 1u].base;
}

static sint32 native_read(void *user, uint32 address, uint32 width, uint32 *value)
{
    uint8 *memory;

    if (width != 1u && width != 2u && width != 4u)
        adapter_failure("Invalid MMIO width", "read", width);
    memory = borrowed_pointer(address, width);
    if (memory)
    {
        *value = 0;
        memcpy(value, memory, width);
        return 1;
    }
    if (address == 0x1F801070u || address == 0x1F801074u || (address >= 0x1F801100u && address < 0x1F801130u))
        return legend_timer_read(NULL, address, width, value);
    if (address >= 0x1F801C00u && address < 0x1F801E00u)
        return spu_mmio_read(NULL, address, width, value);
    adapter_failure("Unbound MMIO address", "read", address);
    return 0;
}

static sint32 native_write(void *user, uint32 address, uint32 width, uint32 value, uint32 byte_mask)
{
    uint8 *memory;
    uint32 i;

    if (width != 1u && width != 2u && width != 4u)
        adapter_failure("Invalid MMIO width", "write", width);
    memory = borrowed_pointer(address, width);
    if (memory)
    {
        for (i = 0; i < width; ++i)
            if (byte_mask & (1u << i))
                memory[i] = (uint8)(value >> (8u * i));
        return 1;
    }
    if (address == 0x1F801070u || address == 0x1F801074u || (address >= 0x1F801100u && address < 0x1F801130u))
        return legend_timer_write(NULL, address, width, value, byte_mask);
    if (address >= 0x1F801C00u && address < 0x1F801E00u && spu_mmio_write(NULL, address, width, value, byte_mask))
        return 1;
    adapter_failure("Unimplemented MMIO write", "write", address);
    return 0;
}

void legend_native_adapters_init(void)
{
    span_count = 0;
    next_address = 0x1E000000u;
    legend_timer_init();
    xport_memory_bind_mmio(0x1E000000u, 0x01802000u, native_read, native_write, NULL);
}

/* Native C owns call frames; retain only the original stack address carrier */
uint32 xport_draft_switch_stack(uint32 stack)
{
    static uint32 current_stack;
    uint32 previous;
    if (!current_stack)
        current_stack = r_u32(0x80071480u) - 8u;
    previous = current_stack;
    current_stack = stack;
    return previous;
}

uint32 draft_unknown_argument(const char *owner, uint32 slot)
{
    adapter_failure("Unknown argument", owner, slot);
    return 0;
}

uint32 draft_unknown_return(const char *owner)
{
    adapter_failure("Unknown return", owner, 0);
    return 0;
}

uint32 mallocPSX(uint32 size)
{
    return sub_80011808(size);
}

uint32 freePSX(uint32 address)
{
    return sub_800118BC(address);
}
