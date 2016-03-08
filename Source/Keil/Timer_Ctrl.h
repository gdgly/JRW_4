#ifndef _TIMER_CTRL_H
#define _TIMER_CTRL_H
#include <stdio.h>
#include "Mini51Series.h"

extern volatile uint32_t tick_counter;

extern void setup_system_tick(uint32_t sampleRate);

#endif
