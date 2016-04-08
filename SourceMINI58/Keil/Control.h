#ifndef CONTROL_H
#define CONTROL_H

#include "ConfigTable.h"
#include "stdint.h"
#include "PID.h"


enum{PITCH,ROLL,YAW,THROTTLE};

void CtrlAttiAng(void);
void CtrlAttiRate(void); 
void CtrlMotor(void);

#endif
