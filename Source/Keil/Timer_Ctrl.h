#ifndef TIMER_CTRL_H
#define TIMER_CTRL_H
#include <stdio.h>
#include "Mini51Series.h"

extern volatile uint32_t tick_counter;

void setup_system_tick(uint32_t sampleRate);


uint32_t millis(void);	//系统时间，单位ms

uint32_t GetFrameCount(void);

void IncFrameCount(uint8_t inc);

void DelayMsec(uint16_t time);

#endif
