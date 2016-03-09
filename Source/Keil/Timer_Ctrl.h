#ifndef _TIMER_CTRL_H
#define _TIMER_CTRL_H
#include <stdio.h>
#include "Mini51Series.h"

extern volatile uint32_t tick_counter;

void setup_system_tick(uint32_t sampleRate);

int getTickCount(void);

uint32_t GetFrameCount(void);

void IncFrameCount(int inc);

#endif
