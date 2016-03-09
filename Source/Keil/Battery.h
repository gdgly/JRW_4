#ifndef BATTERY_H
#define BATTERY_H


void BatteryCheckInit(void);
//检测电池电压
void BatteryCheck(void);
//返回电池AD值
int GetBatteryAD(void);
 
#endif
