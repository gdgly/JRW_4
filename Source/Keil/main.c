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
	//��ʼ��ϵͳʱ��
	setupSystemClock();
	
	//��ʼ������
	setupUART();
	UART_NVIC_INIT();

	//��ʼ��SystemTick
	setup_system_tick(SYSTEM_TICK_FREQ);
	
	//��ʼ��IIC
	I2C_Init();
	
	//��ʼ��FLASH
	FlashInit();
	LoadParamsFromFlash();
	
	//��ʼ��BATTERY_DETECT
	BatteryCheckInit();
	
	//��ʼ��ң��
	
	//��ʼ��LED
	LED_Init();
	
	//��ʼ��SENSOR
	MPU6050_initialize();
	
	//��ʼ�����ȶ�
	
	//��ʼ��AHRS�㷨
	
	//��ʼ�����
	Motor_Init();
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);
	
}
int16_t AccX = 0, AccY = 0, AccZ = 0;
int16_t RotationX = 0, RotationY = 0, RotationZ = 0;
void loop()
{
		static uint32_t nextTick = 0;
		while(getTickCount()<nextTick){};
		nextTick = getTickCount()+TICK_FRAME_PERIOD;	//ѭ�����frame��ÿ��frame��ʱ1ms
	
		//��ȡ��������
		CommandProcess();
			
		//��ȡң������
	
		//100Hz��ÿ10msһ��
		if(getTickCount()%10 == 0)
		{
			//��ȡ��̬����������
			MPU6050_getAcceleration(&AccX, &AccY, &AccZ);
			MPU6050_getRotation(&RotationX, &RotationY, &RotationZ);
			
			
			
			//��ȡŷ����
			
			//PID�������ٶ�
			CtrlAttiRate();
			
			//����������
			//MotorCtrl();
			MotorPwmOutput(0,0,0,0);
			
		}

		//ÿ50HZ��ÿ20msһ��
		if(getTickCount()%20 == 0)
		{
			//����ң������
			//PIDһ���Ƕȿ���
			CtrlAttiAng();
		}
		
  
		//10HZ��ÿ100msһ��
		//if(getTickCount()%100 == 0)
		//2HZ��ÿ500msһ��
		if(getTickCount()%500 == 0)
		{
			//����ص���
			BatteryCheck();
			
			//ң��ͨ�Ŷ�ʧ����
			
			//����LED��״̬
			UpdateLED();
			//printf("\n uart test\n");
			
			//���ϱ���
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
