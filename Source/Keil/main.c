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
#include "I2Cdev.h"
//#include "mpu6050.h"



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
	CLK_SetModuleClock(I2C_MODULE, 0, 0);
		CLK_EnableModuleClock(I2C_MODULE);
	
//	/* Set P3.4 and P3.5 for I2C SDA and SCL */
    SYS->P3_MFP = SYS_MFP_P34_SDA | SYS_MFP_P35_SCL;
		
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
	
	//��ʼ�����ȶ�
	
	//��ʼ��AHRS�㷨
	
	//��ʼ��SENSOR
//	MPU6050_initialize();
	
	//��ʼ�����
	Motor_Init();
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);
	
}


void loop()
{
		static uint32_t nextTick = 0;
		while(getTickCount()<nextTick){};
		nextTick = getTickCount()+TICK_FRAME_PERIOD;	//ѭ�����frame��ÿ��frame��ʱ1ms
	
		//��ȡ��������
		CommandProcess();
			
		//��ȡң������
	
		//ÿ100Hz��10msһ��
		if(getTickCount()%10 == 0)
		{
			//��ȡ��̬����������
			//��ȡŷ����
			
			//PID�������ٶ�
			CtrlAttiRate();
			
			//����������
			//MotorCtrl();
			MotorPwmOutput(0,0,0,0);
			
		}

		//ÿ50HZ��20msһ��
		if(getTickCount()%20 == 0)
		{
			//����ң������
			//PIDһ���Ƕȿ���
			CtrlAttiAng();
		}
		
  
		//10HZ��100msһ��
		//if(getTickCount()%100 == 0)
		//2HZ��100msһ��
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
	
}


int main()
{
  setup();
	while(TRUE) loop();
}

/*** (C) COPYRIGHT ***/
