#ifndef CONTROL_H
#define CONTROL_H

#include "PID.h"
#include "stdint.h"
enum{ROLL,PITCH,YAW,THROTTLE};
void PID_Postion_Cal(PID_Typedef * PID,float target,float measure,int32_t dertT);

void CtrlAttiAng(void);
void CtrlAttiRate(void); 
void CtrlMotor(void);

#endif
