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
#include "led.h"
#include "Timer_Ctrl.h"
#include "Motor.h"
#include "Battery.h"

#define RXBUFSIZE 1024
/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t g_u8SendData[12] = {0};
uint8_t g_u8RecData[RXBUFSIZE]  = {0};

volatile uint32_t g_u32comRbytes = 0;
volatile uint32_t g_u32comRhead  = 0;
volatile uint32_t g_u32comRtail  = 0;

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

void setupUART()
{
	/* Enable peripheral clock */
	CLK_EnableModuleClock(UART_MODULE);
	/* Peripheral clock source */
	CLK_SetModuleClock(UART_MODULE, CLK_CLKSEL1_UART_S_HIRC, CLK_CLKDIV_UART(1));
	/* Set PD multi-function pins for UART0 RXD, TXD */
	SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
  SYS->P1_MFP |= (SYS_MFP_P12_RXD | SYS_MFP_P13_TXD);
	
	//SYS->P0_MFP = SYS_MFP_P00_TXD | SYS_MFP_P01_RXD;
	
	/* Reset UART module */
	SYS_ResetModule(UART_RST);

	/* Configure UART0 and set UART0 Baudrate */
	UART_Open(UART0, 115200);
}


/*---------------------------------------------------------------------------------------------------------*/
/* UART Callback function                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void UART_HANDLE()
{
    uint8_t u8InChar=0xFF;
    uint32_t u32IntSts= UART->ISR;

    if(u32IntSts & UART_ISR_RDA_INT_Msk) {

        /* Get all the input characters */
        while(UART_IS_RX_READY(UART)) {
            /* Get the character from UART Buffer */
            u8InChar = UART_READ(UART);           /* Rx trigger level is 1 byte*/

						printf("%c", u8InChar);
            /* Check if buffer full */
            if(g_u32comRbytes < RXBUFSIZE) {
                /* Enqueue the character */
                g_u8RecData[g_u32comRtail] = u8InChar;
                g_u32comRtail = (g_u32comRtail == (RXBUFSIZE-1)) ? 0 : (g_u32comRtail+1);
                g_u32comRbytes++;
            }
        }
    }
		
		
}


/*---------------------------------------------------------------------------------------------------------*/
/*  UART Function Test                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void UART_NVIC_INIT()
{
    
    /* Enable Interrupt and install the call back function */
   // UART_ENABLE_INT(UART, (UART_IER_RDA_IEN_Msk | UART_IER_THRE_IEN_Msk | UART_IER_RTO_IEN_Msk));
	  UART_ENABLE_INT(UART, UART_IER_RDA_IEN_Msk);
    NVIC_EnableIRQ(UART_IRQn);
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
	//初始化BATTERY_DETECT
	//初始化遥控
	//初始化LED
	LED_Init();
	//初始化自稳定
	//初始化AHRS算法
	//初始化SENSOR
	//初始化电机
	
//	printf("\n\nCPU @ %dHz\n", SystemCoreClock);

	
}

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART_IRQHandler(void)
{
    UART_HANDLE();
}


void loop()
{
	//读取姿态传感器数据
	
	//每100Hz
		//PID二环角速度
		//输出电机控制
	
	//读取遥控数据
	
	//每50HZ
		//处理遥控数据
		//PID一环角度控制
  
	
	//每10HZ
		//检查电池电量
		//遥控通信丢失处理
		//更新LED灯状态
		UpdateLED();
	
	//故障保护
}


int main()
{
  setup();
	while(TRUE) loop();
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
