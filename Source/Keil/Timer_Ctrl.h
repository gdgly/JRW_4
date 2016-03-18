#ifndef TIMER_CTRL_H
#define TIMER_CTRL_H
#include <stdio.h>
#include "Mini51Series.h"

extern volatile uint32_t tick_counter;

void setup_system_tick(uint32_t sampleRate);

int getTickCount(void);

uint32_t GetFrameCount(void);

void IncFrameCount(uint8_t inc);

void DelayMsec(uint8_t time);	//ÑÓ³Ù£¬µ¥Î»ms

#endif
