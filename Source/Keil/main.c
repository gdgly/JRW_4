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
	//初始化系统时钟
	setupSystemClock();
	
	//初始化串口
	setupUART();
	UART_NVIC_INIT();

	//初始化SystemTick
	setup_system_tick(SYSTEM_TICK_FREQ);
	
	//初始化IIC
	I2C_Init();
	
	//初始化FLASH
	FlashInit();
	LoadParamsFromFlash();
	
	//初始化BATTERY_DETECT
	BatteryCheckInit();
	
	//初始化遥控
	
	//初始化LED
	LED_Init();
	
	//初始化SENSOR
	MPU6050_initialize();
	
	//初始化自稳定
	
	//初始化AHRS算法
	
	//初始化电机
	Motor_Init();
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);
	
}
int16_t AccX = 0, AccY = 0, AccZ = 0;
int16_t RotationX = 0, RotationY = 0, RotationZ = 0;
void loop()
{
		static uint32_t nextTick = 0;
		while(getTickCount()<nextTick){};
		nextTick = getTickCount()+TICK_FRAME_PERIOD;	//循环间隔frame，每个frame耗时1ms
	
		//读取蓝牙数据
		CommandProcess();
			
		//读取遥控数据
	
		//100Hz，每10ms一次
		if(getTickCount()%10 == 0)
		{
			//读取姿态传感器数据
			MPU6050_getAcceleration(&AccX, &AccY, &AccZ);
			MPU6050_getRotation(&RotationX, &RotationY, &RotationZ);
			
			
			
			//读取欧拉角
			
			//PID二环角速度
			CtrlAttiRate();
			
			//输出电机控制
			//MotorCtrl();
			MotorPwmOutput(0,0,0,0);
			
		}

		//每50HZ，每20ms一次
		if(getTickCount()%20 == 0)
		{
			//处理遥控数据
			//PID一环角度控制
			CtrlAttiAng();
		}
		
  
		//10HZ，每100ms一次
		//if(getTickCount()%100 == 0)
		//2HZ，每500ms一次
		if(getTickCount()%500 == 0)
		{
			//检查电池电量
			BatteryCheck();
			
			//遥控通信丢失处理
			
			//更新LED灯状态
			UpdateLED();
			//printf("\n uart test\n");
			
			//故障保护
		}
		
		//1HZ
		if(getTickCount()%1000 == 0)
		{
			printf("MPU6050_getAcceleration  x=%d, y=%d, z=%d \n",AccX, AccY, AccZ);
			printf("MPU6050_getRotation  x=%d, y=%d, z=%d \n",RotationX, RotationY, RotationZ);
			printf("\n");
		}

	
}


int main()
{
  setup();
	while(TRUE) loop();
}

/*** (C) COPYRIGHT ***/
