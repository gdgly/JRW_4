/******************************************************************************
 * @file     main.c
 * @version  
 * $Revision: 
 * $Date: 
 * @brief    
 *
 * @note
 * Copyright (C) 
*****************************************************************************/
#include <stdio.h>

#include "Mini51Series.h"


#include "def.h"
#include "ConfigTable.h"
#include "led.h"
#include "Timer_Ctrl.h"
#include "Motor.h"
#include "Battery.h"
#include "UartCtrl.h"
#include "FlashCtrl.h"
#include "RC.h"
#include "Control.h"
#include "I2CDev.h"
#include "MPU6050.h"
#include "IMUSO3.h"
#include "IMU.h"
#include "DMP.h"

void setupSystemClock(void)
{
		SYS_UnlockReg();
	
		/* Enable HIRC clock */
		CLK_EnableXtalRC(CLK_PWRCON_HIRC_EN_Msk);

		/* Waiting for HIRC clock ready */
		CLK_WaitClockReady(CLK_CLKSTATUS_HIRC_STB_Msk);

		/* Switch HCLK clock source to HIRC */
		CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));
	
		/* To update the variable SystemCoreClock */
    SystemCoreClockUpdate();
	
		SYS_LockReg();
}


void setup()
{
	uint8_t ledStatus2 =0,i=0;
	//初始化系统时钟
	setupSystemClock();
	
	//初始化串口
	setupUART();
	UART_NVIC_INIT();

	//初始化System_tick
	setup_system_tick(SYSTEM_TICK_FREQ);
	
	//初始化IIC
	I2C_Init();
	
	//初始化FLASH
	FlashInit();
	LoadParamsFromFlash();
	
	//初始化低电压检测
	BatteryCheckInit();
	
	//初始化遥控
	
	//初始化LED
	LED_Init();
	
	//初始化SENSOR
	#ifdef IMU_SW											//软件姿态解算
	
		MPU6050_initialize();
		DelayMsec(1000);			//必须加延迟，否则读取陀螺仪数据出错
	#else
		MPU6050_initialize();
		DelayMsec(1000);			//必须加延迟，否则读取陀螺仪数据出错
		MPU6050_DMP_Initialize();     //初始化DMP引擎
	#endif
	
	//初始化自稳定
	
	LED_ON();
	//测试用，延迟启动时间
	for(i=0;i<6;i++)
	{
		
		DelayMsec(1000);
		LED_OFF();
	}
		
	
	//初始化电机
	Motor_Init();
	//Motor_Start();
	//printf("Motor_Init(); \n");
	
	//IMU_Init();			// sample rate and cutoff freq.  sample rate is too low now due to using dmp.
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);
	//MotorPwmOutput(100,100,0,0);

}
bool falg = false;
void loop()
{
	
		static uint32_t nextTick = 0;
		while(millis()<nextTick){}
		nextTick = millis()+TICK_FRAME_PERIOD;	//循环间隔FRAME
	
		//处理蓝牙命令
		CommandProcess();
			
		//读取遥控命令
	
		if(GetFrameCount()%10 == 0)
		{
			//读取姿态传感器数据
			
			
			//读取欧拉角
			#ifdef IMU_SW											//软件姿态解算
			//IMUSO3Thread();
			#else
			DMP_Routing();	//DMP 线程  所有的数据都在这里更新
			#endif
			
			//PID二环角速度
			CtrlAttiRate();
			
		}

		if(GetFrameCount()%20 == 0)
		{
			//处理遥控数据
			//PID一环角度控制
			CtrlAttiAng();
		}
		
  
		//10HZ,每100ms一次
		//if(getTickCount()%100 == 0)
		
		
		if(GetFrameCount()%1000 == 0)
		{
			//检测电池电量
			BatteryCheck();
			
			//遥控通信丢失处理
			
			//更新LED灯状态
			UpdateLED();
			
			
		}
		
		if(GetFrameCount()%100 == 0)
		{
			
			//printf("yaw=%d, roll=%d, pitch=%d \n",(int)imu.yaw, (int)imu.roll, (int)imu.pitch);
			
			//printf("\n");
		}
		
		//故障保护
		if(GetFrameCount() > 6000 && GetFrameCount() < 8000)
		{
			Motor_Start();
			MotorPwmOutput(20,20,20,20);
		}
//		else if(GetFrameCount() >= 8000  && GetFrameCount() < 10000)
//		{
//			MotorPwmOutput(40,40,40,40);
//		}
//		else if(GetFrameCount() >= 10000   && GetFrameCount() < 12000)
//		{
//			MotorPwmOutput(60,60,60,60);
//		}
//		else if(GetFrameCount() >= 12000  && GetFrameCount() < 14000)
//		{
//			MotorPwmOutput(80,80,80,80);
//		}
		else if(GetFrameCount() >= 14000 && GetFrameCount() < 16000)
		{
			MotorPwmOutput(100,100,100,100);
		}
		else if(GetFrameCount() >= 16000 && !falg)
		{
			falg = true;
			//MotorPwmOutput(0,0,0,0);
			Motor_Stop();
		}
		
		
	
		IncFrameCount(1);
}


int main()
{
  setup();
	while(TRUE) loop();
}

/*** (C) COPYRIGHT ***/
