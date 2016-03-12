#ifndef CONTROL_H
#define CONTROL_H

#include "ConfigTable.h"
#include "stdint.h"
#include "PID.h"

// PID结构
//typedef struct
//{
//    float P;
//    float I;
//    float D;
//    float Desired;
//    float Error;
//    float PreError;
//    float PrePreError;
//    float Increment;
//    float Integ;
//		float iLimit;
//    float Deriv;
//    float Output;
// 
//}PID_Typedef;



//extern PID_Typedef pitch_angle_PID;	  //pitch角度环PID
//extern PID_Typedef pitch_rate_PID;		//pitch角速率环PID

//extern PID_Typedef roll_angle_PID;    //roll角度环PID
//extern PID_Typedef roll_rate_PID;     //roll角速率环PID

//extern PID_Typedef yaw_angle_PID;     //yaw角度环PID  
//extern PID_Typedef yaw_rate_PID;      //yaw角速率环PID  

enum{ROLL,PITCH,YAW,THROTTLE};
void PID_Postion_Cal(PID_Typedef * PID,float target,float measure,int32_t dertT);

void CtrlAttiAng(void);
void CtrlAttiRate(void); 
void CtrlMotor(void);

#endif
