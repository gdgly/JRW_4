
#include	"extern.h"
#include	"User\XN297L\RF.H"
#include	"Comm.h"
#include	"Timer.h"
#include	"adc.h"
#include	"Key.h"
#include 	"Led.h"

void IO_Init(void)
{
	/**************将IO配置为模拟输入**************/
	$ PBDIER 0B0100_0001	//PB1~5模拟输入
	//俯仰角电位器输入引脚配置
	PBC.1 = 0;				//配置为输入
	PBPH.1 = 0;				//关闭内部弱上拉电阻
	//翻滚角电位器输入引脚配置
	PBC.3 = 0;				//配置为输入
	PBPH.3 = 0;				//关闭内部弱上拉电阻
	//航向角电位器输入引脚配置
	PBC.2 = 0;				//配置为输入
	PBPH.2 = 0;				//关闭内部弱上拉电阻
	//油门电位器输入引脚配置
	PBC.4 = 0;				//配置为输入
	PBPH.4 = 0;				//关闭内部弱上拉电阻
	//低电压检测输入引脚配置
	PBC.5 = 0;				//配置为输入
	PBPH.5 = 0;				//关闭内部弱上拉电阻

	$ PADIER 0B1111_0101	//PA3模拟输入
	//按键检测输入引脚配置
	PAC.3 = 0;				//配置为输入
	PAPH.3 = 0;				//关闭内部弱上拉电阻
	/**********************************************/

	PAC.7 = 1;//LED(PA7) Output
	PBC.0 = 1;//蜂鸣器驱动端口
}




void	FPPA0 (void)
{
	.ADJUST_IC	SYSCLK=IHRC/8,IHRC=16MHz,VDD=3.3V,Bandgap=On

	clkmd.En_WatchDog	=	1;		//	WatchDog Enable
	//	Insert Initial Code
	Timer16_Init();	//初始化T16定时器
	$ INTEN	T16		//允许T16中断
	engint			//打开全局中断
	Comm_Init();
	IO_Init();
	ADC_Init();
	Key_Noise_Filter_Init();
	FlashLedTime = 0;

	FPPEN.1 = 1;	//使能FPPA1
 	while (1)
	{
		wdreset;					//复位看门狗
		if(FlashLedTime <= 0)
		{
			switch(Comm_CurrentStatus)		//根据2.4G连接状态，更改灯的状态
			{
				case STATUS_CONNECTED:
				{
					FlashLedTime = 1000;
					break;
				}
				case STATUS_DISCONNECT:
				case STATUS_CONNECTING:
				case STATUS_LOST:
				default:
				{
					FlashLedTime = 100;
					break;
				}
			}

			TongleLed();	//切换LED状态
		}

	}
}

void	FPPA1 (void)
{
	while(1)
	{
		Key_Process();
		Comm_Process();
	}
}


void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	//	T16 Trig
		//	User can add code
		SysTick++;
		if(FlashLedTime) FlashLedTime--;
		if(DelayTime) DelayTime--;
		stt16	T16_ReloadVal;
		Intrq.T16	=	0;
		//...
	}

	popaf;
}

