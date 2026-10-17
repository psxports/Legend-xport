#include "game_timer.h"
#include "xport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Native elapsed-time backend, independent of the shared MMIO provider */
static PsxCrtcState crtc;
static PsxIrqState irq;
static uint64 last_us, tick_fraction;
static uint8 irq_fired[3];
static uint32 initialized, display_ready, polling;

static void timer_failure(const char *reason)
{
    fprintf(stderr, "Legend timer: %s\n", reason);
    abort();
}

static sint32 timer_clamp(sint32 value, sint32 low, sint32 high)
{
    return value < low ? low : value > high ? high : value;
}

static void timer_deliver(void)
{
    uint32 index;
    sint32 enabled = xport_bios_enter_critical();
    if (!enabled)
        return;
    xport_bios_exit_critical();
    for (index = 0; index < 3u; ++index)
    {
        uint32 bit = 1u << (index + 4u);
        if (irq.status & irq.mask & bit)
        {
            psx_irq_write(&irq, 0u, ~bit);
            DeliverEvent(0xF2000000u + index, 2u);
        }
    }
}

static void timer_raise(uint32 index, uint32 mode)
{
    if (!(mode & 0x40u) && irq_fired[index])
        return;
    irq_fired[index] = 1u;
    psx_irq_line(&irq, index + 4u, 1u);
    psx_irq_line(&irq, index + 4u, 0u);
}

static void timer_add(PsxTimerState *state, uint32 index, uint32 ticks)
{
    while (ticks)
    {
        uint32 old = state->counter[index], target = state->target[index];
        uint32 wrap = 0x10000u - old;
        uint32 match = target > old ? target - old : 0x10000u - old + target;
        uint32 step = wrap < match ? wrap : match;
        uint32 mode = state->mode[index];
        if (ticks < step)
        {
            state->counter[index] = old + ticks;
            break;
        }
        ticks -= step;
        state->counter[index] = (old + step) & 0xffffu;
        if (step == match)
        {
            mode |= 0x800u;
            if (mode & 8u)
                state->counter[index] = 0u;
        }
        if (step == wrap)
            mode |= 0x1000u;
        state->mode[index] = mode;
        if ((step == match && (mode & 0x10u)) || (step == wrap && (mode & 0x20u)))
            timer_raise(index, mode);
    }
}

void legend_timer_init(void)
{
    memset(&irq, 0, sizeof(irq));
    memset(&crtc, 0, sizeof(crtc));
    memset(irq_fired, 0, sizeof(irq_fired));
    last_us = xport_timer_get();
    tick_fraction = 0u;
    initialized = 1u;
    display_ready = 0u;
    polling = 0u;
}

void legend_timer_poll(void)
{
    uint64 now, elapsed, ticks;
    PsxTimerState state;
    uint32 index;
    if (!initialized)
        timer_failure("Backend not initialized");
    if (polling)
        return;
    polling = 1u;
    /* Poll the existing native VBlank backend without waiting for a field */
    if (VSync(-1) < 0)
        timer_failure("Native VBlank polling failed");
    now = xport_timer_get();
    elapsed = now - last_us;
    last_us = now;
    ticks = (elapsed / 1000000u) * 33868800u;
    tick_fraction += (elapsed % 1000000u) * 33868800u;
    ticks += tick_fraction / 1000000u;
    tick_fraction %= 1000000u;
    psx_timers_export(&state);
    for (index = 0; index < 3u; ++index)
        if (state.mode[index] & 0x81u)
            timer_failure("Unsupported synchronization or toggle IRQ mode");
    while (ticks)
    {
        uint32 cpu = ticks > 1000000u ? 1000000u : (uint32)ticks;
        PsxCrtcStep step;
        memset(&step, 0, sizeof(step));
        if (display_ready)
        {
            if (!psx_crtc_advance(&crtc, cpu, &step))
                timer_failure("Invalid CRTC advancement");
        }
        else if ((state.mode[0] | state.mode[1]) & 0x100u)
            timer_failure("External timer clock before display configuration");
        timer_add(&state, 0u, state.mode[0] & 0x100u ? step.dots : cpu);
        timer_add(&state, 1u, state.mode[1] & 0x100u ? step.hblanks : cpu);
        if (state.mode[2] & 0x200u)
        {
            uint32 divided = cpu + state.div8_carry;
            state.div8_carry = divided % 8u;
            timer_add(&state, 2u, divided / 8u);
        }
        else
            timer_add(&state, 2u, cpu);
        ticks -= cpu;
    }
    if (!psx_timers_import(&state))
        timer_failure("Invalid timer state");
    timer_deliver();
    polling = 0u;
}

void legend_timer_display(const DISPENV *env, uint32 video)
{
    sint32 x0, x1, y0, y1, width, span;
    uint32 resolution, divider, table;
    if (!env || video > 1u)
        timer_failure("Invalid display configuration");
    legend_timer_poll();
    width = env->disp.w;
    resolution = width < 281 ? 0u : width < 353 ? 1u : width < 401 ? 2u : width < 561 ? 3u : 4u;
    divider = r_u8(0x8006FD70u + resolution);
    if (!divider)
        timer_failure("Invalid original dot clock divider");
    table = 4u * (5u * video + resolution);
    x0 = r_u16(0x8006FD48u + table);
    span = (sint32)r_u16(0x8006FD4Au + table) - x0;
    x0 += env->screen.x * (sint32)divider;
    if (env->screen.w)
        span = (sint32)((uint32)span * (uint32)(sint32)env->screen.w) >> 8;
    x1 = x0 + span;
    y0 = env->screen.y + (video ? 19 : 16);
    y1 = y0 + (env->screen.h ? env->screen.h : 240);
    x0 = timer_clamp(x0, video ? 540 : 500, video ? 3220 : 3250);
    x1 = timer_clamp(x1, x0 + 4 * (sint32)divider, video ? 3260 : 3290);
    y0 = timer_clamp(y0, video ? 19 : 16, video ? 303 : 257);
    y1 = timer_clamp(y1, y0 + 2, video ? 305 : 258);
    crtc.pal = video;
    crtc.horizontal_total = video ? 3406u : 3413u;
    crtc.vertical_total = video ? 314u : 263u;
    crtc.horizontal_start = (uint32)x0;
    crtc.horizontal_end = (uint32)x1;
    crtc.vertical_start = (uint32)y0;
    crtc.vertical_end = (uint32)y1;
    crtc.dot_divider = divider;
    crtc.dot_external = 1u;
    crtc.scanline %= crtc.vertical_total;
    crtc.scanline_tick %= crtc.horizontal_total;
    crtc.fractional_dot_ticks %= crtc.dot_divider;
    if (!psx_crtc_validate(&crtc))
        timer_failure("Invalid GP1-derived CRTC state");
    display_ready = 1u;
}

uint32 legend_timer_set(uint32 counter, uint32 target, uint32 mode)
{
    PsxTimerState state;
    uint32 bits = 0x48u;
    legend_timer_poll();
    counter &= 0xffffu;
    if (counter >= 3u)
        return 0u;
    if (counter < 2u)
    {
        if (mode & 0x10u)
            bits = 0x49u;
        if (!(mode & 1u))
            bits |= 0x100u;
    }
    else if (!(mode & 1u))
        bits = 0x248u;
    if (mode & 0x1000u)
        bits |= 0x10u;
    if (bits & 0x81u)
        timer_failure("Unsupported SDK timer synchronization mode");
    psx_timers_export(&state);
    state.counter[counter] = 0u;
    state.target[counter] = target & 0xffffu;
    state.mode[counter] = bits | 0x400u;
    irq_fired[counter] = 0u;
    if (!psx_timers_import(&state))
        timer_failure("SetRCnt state rejected");
    return 1u;
}

uint32 legend_timer_get(uint32 counter)
{
    PsxTimerState state;
    legend_timer_poll();
    counter &= 0xffffu;
    if (counter >= 3u)
        return 0u;
    psx_timers_export(&state);
    return state.counter[counter];
}

uint32 legend_timer_reset(uint32 counter)
{
    PsxTimerState state;
    legend_timer_poll();
    counter &= 0xffffu;
    if (counter >= 3u)
        return 0u;
    psx_timers_export(&state);
    state.counter[counter] = 0u;
    if (!psx_timers_import(&state))
        timer_failure("ResetRCnt state rejected");
    return 1u;
}

uint32 legend_timer_start(uint32 counter)
{
    uint32 control, mask;
    legend_timer_poll();
    counter &= 0xffffu;
    control = r_u32(0x8006B254u) + 4u;
    mask = r_u32(0x8006B25Cu + 4u * counter);
    w_u32(control, r_u32(control) | mask);
    return counter < 3u;
}

uint32 legend_timer_stop(uint32 counter)
{
    uint32 control, mask;
    legend_timer_poll();
    counter &= 0xffffu;
    control = r_u32(0x8006B254u) + 4u;
    mask = r_u32(0x8006B25Cu + 4u * counter);
    w_u32(control, r_u32(control) & ~mask);
    return 1u;
}

sint32 legend_timer_read(void *user, uint32 address, uint32 width, uint32 *value)
{
    PsxTimerState state;
    uint32 index, offset, result;

    if (width != 2u && width != 4u)
        return 0;
    legend_timer_poll();
    if (address == 0x1F801070u || address == 0x1F801074u)
    {
        *value = address & 4u ? irq.mask : irq.status;
        return 1;
    }
    if (address < 0x1F801100u || address >= 0x1F801130u)
        return 0;
    index = (address - 0x1F801100u) / 16u;
    offset = (address - 0x1F801100u) % 16u;
    psx_timers_export(&state);
    if (offset == 0u)
        result = state.counter[index];
    else if (offset == 4u)
    {
        result = state.mode[index];
        state.mode[index] &= ~0x1800u;
        psx_timers_import(&state);
    }
    else if (offset == 8u)
        result = state.target[index];
    else
        return 0;
    *value = result;
    return 1;
}

sint32 legend_timer_write(void *user, uint32 address, uint32 width, uint32 value, uint32 mask)
{
    PsxTimerState state;
    uint32 index, offset, old, merged, i;

    if (width != 2u && width != 4u)
        return 0;
    legend_timer_poll();
    if (address == 0x1F801070u || address == 0x1F801074u)
    {
        old = address & 4u ? irq.mask : irq.status;
        merged = old;
        for (i = 0; i < width; ++i)
            if (mask & (1u << i))
                merged = (merged & ~(255u << (8u * i))) | (value & (255u << (8u * i)));
        return psx_irq_write(&irq, address & 4u, merged);
    }
    if (address < 0x1F801100u || address >= 0x1F801130u)
        return 0;
    index = (address - 0x1F801100u) / 16u;
    offset = (address - 0x1F801100u) % 16u;
    psx_timers_export(&state);
    if (offset == 0u)
        old = state.counter[index];
    else if (offset == 4u)
        old = state.mode[index];
    else if (offset == 8u)
        old = state.target[index];
    else
        return 0;
    merged = old;
    for (i = 0; i < width; ++i)
        if (mask & (1u << i))
            merged = (merged & ~(255u << (8u * i))) | (value & (255u << (8u * i)));
    if (offset == 0u)
        state.counter[index] = merged & 0xffffu;
    else if (offset == 8u)
        state.target[index] = merged & 0xffffu;
    else
    {
        if (merged & 0x81u)
            timer_failure("Unsupported MMIO timer mode");
        state.mode[index] = (merged & 0x3ffu) | 0x400u;
        state.counter[index] = 0u;
        irq_fired[index] = 0u;
    }
    return psx_timers_import(&state);
}
