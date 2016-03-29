#include "Motor.h"
#include "mini51series.h"
#include "Timer_Ctrl.h"

//飞机正方向，左下角为电机1，逆时钟以此类推，电机2，电机3，电机4
#define MOTOR_1 0
#define MOTOR_2 3
#define MOTOR_3 1
#define MOTOR_4 2

int16_t motor1PWM, motor2PWM, motor3PWM, motor4PWM; 

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
	
	motor1PWM = MOTO1_PWM;
	motor2PWM = MOTO2_PWM;
	motor3PWM = MOTO3_PWM;
	motor4PWM = MOTO4_PWM;

}

//void MotorPwmOutput2(void)
//{
//	PWM_ConfigOutputChannel(PWM, MOTOR_1, 400, motor1PWM);
//	
//	PWM_ConfigOutputChannel(PWM, MOTOR_2, 400, motor2PWM);

//	PWM_ConfigOutputChannel(PWM, MOTOR_3, 400, motor3PWM);

//	PWM_ConfigOutputChannel(PWM, MOTOR_4, 400, motor4PWM);

//}
