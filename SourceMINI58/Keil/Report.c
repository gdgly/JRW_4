#include "Report.h"
#include "def.h"
#include "UartCtrl.h"
#include "ConfigTable.h"
#include "stdio.h"
#include "PID.h"

char report_mode = REPORT_ANGLE_PID;
float PID[9];

void report_angle_pid(void)
{
	
	GetPitchAnglePID(&PID[0]);
	GetRollAnglePID(&PID[3]);
	GetYawAnglePID(&PID[6]);

	{
		printf("@AnglePID:%1.1f,%1.1f,%1.1f;  %1.1f,%1.1f,%1.1f; %1.1f,%1.1f,%1.1f\n",
			PID[0],PID[1],PID[2],PID[3],PID[4],PID[5],PID[6],PID[7],PID[8]);
	}
}

void report_rate_pid(void)
{
	GetPitchRatePID(&PID[0]);
	GetRollRatePID(&PID[3]);
	GetYawRatePID(&PID[6]);
	

	{
		printf("@RatePID:%1.2f,%1.2f,%1.2f;  %1.2f,%1.2f,%1.2f; %1.2f,%1.2f,%1.2f\n",
			PID[0],PID[1],PID[2],PID[3],PID[4],PID[5],PID[6],PID[7],PID[8]);
	}
}

void ReportMessage(void)
{
	if(report_mode == REPORT_ANGLE_PID) 
	{
		report_angle_pid();
	}
	else if(report_mode == REPORT_RATE_PID) 
	{
		report_rate_pid();
	}
}



void CheckVersion()
{
	printf("table.version = %d\n",(int)table.version);
}


