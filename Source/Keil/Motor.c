#include "Motor.h"
#include "mini51series.h"
 

void Motor_Init(void)
{
	CLK_EnableModuleClock(PWM01_MODULE);
	CLK_EnableModuleClock(PWM23_MODULE);
	CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HCLK, 0);
	CLK_SetModuleClock(PWM23_MODULE, CLK_CLKSEL1_PWM23_S_HCLK, 0);
	SYS->P2_MFP = SYS_MFP_P22_PWM0 | SYS_MFP_P23_PWM1 | SYS_MFP_P24_PWM2 | SYS_MFP_P25_PWM3;
	
	PWM_ConfigOutputChannel(PWM, 0, 100, 0);
	PWM_ConfigOutputChannel(PWM, 1, 100, 0);
	PWM_ConfigOutputChannel(PWM, 2, 100, 0);
	PWM_ConfigOutputChannel(PWM, 3, 100, 0);
	
	PWM_EnableOutput(PWM, 0x0f);
	
	PWM_Start(PWM, 0x0f);
}


//void Motor_Start(void)
//{
//		//PWM_ConfigOutputChannel(PWM, 0, 100, 30);
//    //PWM_EnableDeadZone(PWM, 0, 400);
//}

//void MotorCtrl(void)
//{

//}

void MotorPwmOutput(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
{
	PWM_ConfigOutputChannel(PWM, 0, 100, MOTO1_PWM);
	PWM_ConfigOutputChannel(PWM, 1, 100, MOTO2_PWM);
	PWM_ConfigOutputChannel(PWM, 2, 100, MOTO3_PWM);
	PWM_ConfigOutputChannel(PWM, 3, 100, MOTO4_PWM);
}
