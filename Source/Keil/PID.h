#ifndef PID_H
#define PID_H

// PID�ṹ
typedef struct
{
    float P;
    float I;
    float D;
    float Desired;
    float Error;
    float PreError;
    float PrePreError;
    float Increment;
    float Integ;
		float iLimit;
    float Deriv;
    float Output;
 
}PID_Typedef;



extern PID_Typedef pitch_angle_PID;	  //pitch�ǶȻ�PID
extern PID_Typedef pitch_rate_PID;		//pitch�����ʻ�PID

extern PID_Typedef roll_angle_PID;    //roll�ǶȻ�PID
extern PID_Typedef roll_rate_PID;     //roll�����ʻ�PID

extern PID_Typedef yaw_angle_PID;     //yaw�ǶȻ�PID  
extern PID_Typedef yaw_rate_PID;      //yaw�����ʻ�PID  

 
#endif
