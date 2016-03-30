#ifndef BATTERY_H
#define BATTERY_H
#include "stdint.h"

void BatteryCheckInit(void);
//检查电池电压
void BatteryCheck(void);
//获取电池电压
uint32_t GetBatteryAD(void);
 
#endif
