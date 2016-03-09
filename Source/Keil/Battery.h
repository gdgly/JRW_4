#ifndef _BATTERY_H
#define _BATTERY_H


void BatteryCheckInit(void);
//void Motor_Start(void);
//检测电池电压
void BatteryCheck(void);
//返回电池AD值
int GetBatteryAD(void);
 
#endif
