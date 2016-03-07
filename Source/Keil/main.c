/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 5 $
 * $Date: 15/10/06 11:26a $
 * @brief    A project template for Mini51DE MCU.
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "Mini51Series.h"

#include "def.h"
volatile uint32_t tick_counter = 0;

void setupSystemClock(void)
{
		SYS_UnlockReg();
	
		/* Enable HIRC clock */
		CLK_EnableXtalRC(CLK_PWRCON_HIRC_EN_Msk);

		/* Waiting for HIRC clock ready */
		CLK_WaitClockReady(CLK_CLKSTATUS_HIRC_STB_Msk);

		/* Switch HCLK clock source to HIRC */
		CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HIRC, CLK_CLKDIV_HCLK(1));
	
		/* SysTick source to HCLK/2 */
    CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLK_S_HCLK_DIV2);
		
		/* To update the variable SystemCoreClock */
    SystemCoreClockUpdate();
	
		SYS_LockReg();
}
void SysTick_Handler(void)
{
	tick_counter++;
}

void setupUART()
{
	/* Enable peripheral clock */
	CLK_EnableModuleClock(UART_MODULE);
	/* Peripheral clock source */
	CLK_SetModuleClock(UART_MODULE, CLK_CLKSEL1_UART_S_HIRC, CLK_CLKDIV_UART(1));
	/* Set PD multi-function pins for UART0 RXD, TXD */
	SYS->P0_MFP = SYS_MFP_P00_TXD | SYS_MFP_P01_RXD;
	/* Reset UART module */
	SYS_ResetModule(UART_RST);

	/* Configure UART0 and set UART0 Baudrate */
	UART_Open(UART0, 115200);
}

void setup_system_tick(uint32_t sampleRate)
{
	uint32_t tickPeriod = SystemCoreClock/sampleRate;
	
	SysTick_Config(tickPeriod);
	//ChronographStart(ChronMain);
	printf("SystemCoreClock:%d\n",SystemCoreClock);
	printf("Tick Time: %d us\n",1000000/sampleRate);
}

void setup()
{
	//��ʼ��ϵͳʱ��
	setupSystemClock();
		
	//��ʼ������
	setupUART();

	//��ʼ��ϵͳ��ʱ��
	setup_system_tick(SYSTEM_TICK_FREQ);
	
	//��ʼ��IIC
	//��ʼ��FLASH
	//��ʼ��BATTERY_DETECT
	//��ʼ��ң��
	//��ʼ��LED
	//��ʼ��TIMER
	//��ʼ�����ȶ�
	//��ʼ��AHRS�㷨
	//��ʼ��SENSOR
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);
}

void loop()
{
	
}


int main()
{
  setup();
	while(1) loop();
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
