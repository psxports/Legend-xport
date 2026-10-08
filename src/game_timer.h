#ifndef LEGEND_GAME_TIMER_H
#define LEGEND_GAME_TIMER_H
#include "psx.h"
void legend_timer_init(void);
void legend_timer_display(const DISPENV *environment, uint32 video_mode);
void legend_timer_poll(void);
uint32 legend_timer_set(uint32 counter, uint32 target, uint32 mode);
uint32 legend_timer_get(uint32 counter);
uint32 legend_timer_start(uint32 counter);
uint32 legend_timer_stop(uint32 counter);
uint32 legend_timer_reset(uint32 counter);
sint32 legend_timer_read(void *user, uint32 address, uint32 width, uint32 *value);
sint32 legend_timer_write(void *user, uint32 address, uint32 width, uint32 value, uint32 byte_mask);
#endif
