#include "Motor.h"
#include "mini51series.h"
#include "Timer_Ctrl.h"

#define MOTOR_1 0
#define MOTOR_2 1
#define MOTOR_3 3
#define MOTOR_4 2

void Motor_Init(void)
{
	CLK_EnableModuleClock(PWM01_MODULE);
	CLK_EnableModuleClock(PWM23_MODULE);
	CLK_SetModuleClock(PWM01_MODULE, CLK_CLKSEL1_PWM01_S_HCLK, 0);
	CLK_SetModuleClock(PWM23_MODULE, CLK_CLKSEL1_PWM23_S_HCLK, 0);
	SYS->P2_MFP = SYS_MFP_P22_PWM0 | SYS_MFP_P23_PWM1 | SYS_MFP_P24_PWM2 | SYS_MFP_P25_PWM3;
	
	MotorPwmOutput(0,0,0,0);
}


void Motor_Start(void)
{
	
	PWM_EnableOutput(PWM, 0x0f);
	PWM_Start(PWM, 0x0f);
	//MotorPwmOutput(15,15,15,15);
}

void Motor_Stop(void)
{
	PWM_DisableOutput(PWM, 0xf);
	PWM_Stop(PWM, 0x0f);
	printf("Motor_Stop \n");
}

void MotorPwmOutput(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
{
	PWM_ConfigOutputChannel(PWM, MOTOR_1, 400, MOTO1_PWM);
	
	PWM_ConfigOutputChannel(PWM, MOTOR_2, 400, MOTO2_PWM);

	PWM_ConfigOutputChannel(PWM, MOTOR_3, 400, MOTO3_PWM);

	PWM_ConfigOutputChannel(PWM, MOTOR_4, 400, MOTO4_PWM);

}
