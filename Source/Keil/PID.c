#include "PID.h"
#include "mini51series.h"
#include "UartCtrl.h"


PID_Typedef pitch_angle_PID;	//pitch角度环的PID
PID_Typedef pitch_rate_PID;		//pitch角速率环的PID

PID_Typedef roll_angle_PID;   //roll角度环的PID
PID_Typedef roll_rate_PID;    //roll角速率环的PID

PID_Typedef yaw_angle_PID;    //yaw角度环的PID 
PID_Typedef yaw_rate_PID;     //yaw角速率环的PID

//-----------位置式PID-----------
void PID_Postion_Cal(PID_Typedef * PID,float target,float measure,int32_t dertT)
{
 float termI=0;
 float dt= dertT/1000000.0;
	//-----------位置式PID-----------
	//误差=期望值-测量值
	PID->Error=target-measure;
	
	PID->Deriv= (PID->Error-PID->PreError)/dt;
	
	PID->Output=(PID->P * PID->Error) + (PID->I * PID->Integ) + (PID->D * PID->Deriv);    //PID:比例环节+积分环节+微分环节
	
	PID->PreError=PID->Error;
	//仅用于角度环和角速度环的

	//if(FLY_ENABLE && offLandFlag)
	{
			//if(fabs(PID->Output) < Thro )		              //比油门还大时不积分
			{
				termI=(PID->Integ) + (PID->Error) * dt;     //积分环节
				if(termI > - PID->iLimit && termI < PID->iLimit && PID->Output > - PID->iLimit && PID->Output < PID->iLimit)       //在-300~300时才进行积分环节
						PID->Integ=termI;
			}
	}
//	else
//			PID->Integ= 0;
}

//void SetPID()
//{
//	char type = g_u8RecData[2];//GetChar();
//	//int value;
//	char rpy, pid;
//	float valuef;
//	if(type=='p') { //PID
//		rpy = GetChar();
//		if(rpy=='r') { //Roll
//			pid = GetChar();
//			valuef = GetPIDfloat();
//			if(pid=='p')
//				controllerSetRollPID(valuef, -1, -1);
//			else if(pid=='i') 
//				controllerSetRollPID(-1, valuef, -1);
//			else if(pid=='d') 
//				controllerSetRollPID(-1, -1, valuef);
//		}
//		else if(rpy=='p') { //Pitch
//			pid = GetChar();
//			valuef = GetPIDfloat();
//			if(pid=='p') 
//				controllerSetPitchPID(valuef, -1, -1);
//			else if(pid=='i') 
//				controllerSetPitchPID(-1, valuef, -1);
//			else if(pid=='d') 
//				controllerSetPitchPID(-1, -1, valuef);
//		}
//		else if(rpy=='y') { //Yaw
//			pid = GetChar();
//			valuef = GetPIDfloat();
//			if(pid=='p') 
//				controllerSetYawPID(valuef, -1, -1);
//			else if(pid=='i') 
//				controllerSetYawPID(-1, valuef, -1);
//			else if(pid=='d') 
//				controllerSetYawPID(-1, -1, valuef);
//		}
//	}
//	else if(type=='r') { //Rate PID
//		rpy = GetChar();
//		if(rpy=='r') { //Roll
//			pid = GetChar();
//			valuef = GetPIDfloat();
//			if(pid=='p') 
//				controllerSetRollRatePID((float)valuef, -1, -1);
//			else if(pid=='i') 
//				controllerSetRollRatePID(-1, (float)valuef, -1);
//			else if(pid=='d') 
//				controllerSetRollRatePID(-1, -1, (float)valuef);
//		}
//		else if(rpy=='p') { //Pitch
//			pid = GetChar();
//			valuef = GetPIDfloat();
//			if(pid=='p') 
//				controllerSetPitchRatePID((float)valuef, -1, -1);
//			else if(pid=='i') 
//				controllerSetPitchRatePID(-1, (float)valuef, -1);
//			else if(pid=='d') 
//				controllerSetPitchRatePID(-1, -1, (float)valuef);
//		}
//		else if(rpy=='y') { //Yaw
//			pid = GetChar();
//			valuef = GetPIDfloat();
//			if(pid=='p') 
//				controllerSetYawRatePID((float)valuef, -1, -1);
//			else if(pid=='i') 
//				controllerSetYawRatePID(-1, (float)valuef, -1);
//			else if(pid=='d') 
//				controllerSetYawRatePID(-1, -1, (float)valuef);
//		}
//	}
////	else if(type=='a') { //Altitide Hold PID
////		pid = GetChar();
////		valuef = GetPIDfloat();
////		if(pid=='p') 
////			controllerSetAltHoldPID((float)valuef, -1, -1);
////		else if(pid=='i') 
////			controllerSetAltHoldPID(-1, (float)valuef, -1);
////		else if(pid=='d') 
////			controllerSetAltHoldPID(-1, -1, (float)valuef);
////	}
////	else if(type=='s') { //'s'tore flash PID
////		UpdateFlashPID(false);
////	}
////	else if(type=='l') { //'l'oad flash PID
////		LoadFlashPID();
////	}
//}
