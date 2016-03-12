#include "Control.h"
#include "mini51series.h"
#include "Timer_Ctrl.h"
#include "RC.h"


float Thro=0,Roll=0,Pitch=0,Yaw=0;

//PID_Typedef pitch_angle_PID;	  //pitch角度环PID
//PID_Typedef pitch_rate_PID;		//pitch角速率环PID

//PID_Typedef roll_angle_PID;    //roll角度环PID
//PID_Typedef roll_rate_PID;     //roll角速率环PID

//PID_Typedef yaw_angle_PID;     //yaw角度环PID  
//PID_Typedef yaw_rate_PID;      //yaw角速率环PID

//-----------位置式PID-----------
void PID_Postion_Cal(PID_Typedef * PID,float target,float measure,int32_t dertT)
{
 float termI=0;
 float dt= dertT/1000000.0;
	//-----------位置式PID-----------
	//误差=期望值-测量值
	PID->Error=target-measure;
	
	PID->Deriv= (PID->Error-PID->PreError)/dt;
	
	PID->Output=(PID->P * PID->Error) + (PID->I * PID->Integ) + (PID->D * PID->Deriv);    //PID:????+????+????
	
	PID->PreError=PID->Error;
	//仅用于角度环和角速度环的

	//if(FLY_ENABLE && offLandFlag)
	{
			//if(fabs(PID->Output) < Thro )		              //比油门还大时不积分
			{
				termI=(PID->Integ) + (PID->Error) * dt;     //积分环节
				if(termI > - PID->iLimit && termI < PID->iLimit && PID->Output > - PID->iLimit && PID->Output < PID->iLimit)       //?-300~300????????
						PID->Integ=termI;
			}
	}
	//else
	//		PID->Integ= 0;
}


void CtrlAttiAng(void)
{
	static float yawHold=0;
		static uint32_t tPrev=0;
		float yawRateTarget=0;
		float angTarget[3]={0};
		float dt=0,t=0;
		//t=micros();
		t = getTickCount();
		dt=(tPrev>0)?(t-tPrev):0;
		tPrev=t;
		
//		if(altCtrlMode==MANUAL)
//		{
//			angTarget[ROLL]=(float)(RC_DATA.ROOL);
//			angTarget[PITCH]=(float)(RC_DATA.PITCH);
//		}
//		else
//		{
//			angTarget[ROLL]=rollSp;
//			angTarget[PITCH]=pitchSp;
//		}
		angTarget[ROLL]=(float)(RC_DATA.ROOL);
		angTarget[PITCH]=(float)(RC_DATA.PITCH);
		
//		angTarget[YAW]=(float)(RC_DATA.YAW);		//?????
//		yawRateTarget=
//		angTarget[YAW]= (angTarget[YAW] + yawRateTarget * dt);

//		if(headFreeMode)
//		{
//			#ifdef YAW_CORRECT
//        float radDiff = -(imu.yaw - headHold) * M_PI_F / 180.0f; 
//			#else
//				float radDiff = (imu.yaw - headHold) * M_PI_F / 180.0f; 
//			#endif
//        float cosDiff = cosf(radDiff);
//        float sinDiff = sinf(radDiff);
//        float tarPitFree = angTarget[PITCH] * cosDiff + angTarget[ROLL] * sinDiff;
//        angTarget[ROLL] = angTarget[ROLL] * cosDiff - angTarget[PITCH] * sinDiff;
//        angTarget[PITCH] = tarPitFree;
//		}
 
//		PID_Postion_Cal(&pitch_angle_PID,angTarget[PITCH],imu.pitch,dt);
//		PID_Postion_Cal(&roll_angle_PID,angTarget[ROLL],imu.roll,dt);	 
}

void CtrlAttiRate(void)
{
	float yawRateTarget=0;
	static uint32_t tPrev=0; 

	float dt=0,t=0;
	//t=micros();
	t = getTickCount();
	dt=(tPrev>0)?(t-tPrev):0;
	tPrev=t;
		
		yawRateTarget=-(float)RC_DATA.YAW;

	//	PID_Postion_Cal(&pitch_rate_PID,pitch_angle_PID.Output,imu.gyro[PITCH]*180.0f/M_PI_F,dt);	
	//	PID_Postion_Cal(&roll_rate_PID,roll_angle_PID.Output,imu.gyro[ROLL]*180.0f/M_PI_F,dt);//gyroxGloble
//		PID_Postion_Cal(&yaw_rate_PID,yawRateTarget,imu.gyro[YAW]*180.0f/M_PI_F,dt);//DMP_DATA.GYROz

		
//		Pitch = pitch_rate_PID.Output;
//    Roll  = roll_rate_PID.Output;
//    Yaw   = yaw_rate_PID.Output; 
}

void CtrlMotor(void)
{

}
