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
#include "led.h"
#include "Timer_Ctrl.h"
#include "Motor.h"
#include "Battery.h"
#include "UartCtrl.h"
#include "FlashCtrl.h"
#include "RC.h"
#include "Control.h"

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
	
	//初始化FLASH
	FlashInit();
	
	//初始化BATTERY_DETECT
	BatteryCheckInit();
	
	//初始化遥控
	
	//初始化LED
	LED_Init();
	
	//初始化自稳定
	
	//初始化AHRS算法
	
	//初始化SENSOR
	
	//初始化电机
	Motor_Init();
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);
	
}


void loop()
{
		static uint32_t nextTick = 0;
		while(getTickCount()<nextTick){};
		nextTick = getTickCount()+TICK_FRAME_PERIOD;	//循环间隔frame，每个frame耗时1ms
	
		//读取蓝牙数据
		CommandProcess();
			
		//读取遥控数据
	
		//每100Hz，10ms一次
		if(getTickCount()%10 == 0)
		{
			//读取姿态传感器数据
			//读取欧拉角
			
			//PID二环角速度
			CtrlAttiRate();
			
			//输出电机控制
			MotorCtrl();
		}

		//每50HZ，20ms一次
		if(getTickCount()%20 == 0)
		{
			//处理遥控数据
			//PID一环角度控制
			CtrlAttiAng();
		}
		
  
		//每10HZ，100ms
		if(getTickCount()%100 == 0)
		{
			//检查电池电量
			BatteryCheck();
			
			//遥控通信丢失处理
			
			//更新LED灯状态
			UpdateLED();
			
			//故障保护
		}
	
}


int main()
{
  setup();
	while(TRUE) loop();
}

/*** (C) COPYRIGHT ***/
