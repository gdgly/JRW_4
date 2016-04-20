#include <stdint.h>
#include "Key.h"
#include "adc.h"
#include "Comm.h"


//俯仰角Pitch，航向角Yaw，滚动角Roll
uint8_t Pitch,Yaw,Roll,Speed,Key;

uint8_t Filter_Data[3];
void Key_Noise_Filter(void);




void Key_Process(void)
{
	Speed = 0;
	ADC_Channel = SPEED_ADC_CH;
	ADC_Resoult = 0;
	ADC_GetValue();
	if(ADC_Resoult > SPEED_ACTIVE_ADC_VAL)
	{
		//油门大于最小门限电压
		Speed = ADC_Resoult;

		//读取俯仰角电位器电压
		Pitch = 0;
		ADC_Channel = PITCH_ADC_CH;
		ADC_Resoult = 0;
		ADC_GetValue();
		if(ADC_Resoult < PITCH_MIDDLE_POS_ADC_VAL)
		{
			Pitch = PITCH_MIDDLE_POS_ADC_VAL-ADC_Resoult;
		}
		else if(ADC_Resoult > PITCH_MIDDLE_POS_ADC_VAL)
		{
			//负数，二进制补码格式
			ADC_Resoult -= PITCH_MIDDLE_POS_ADC_VAL;
			Pitch = ~ADC_Resoult;
			Pitch++;
		}

		//读取滚动角电位器电压
		Roll = 0;
		ADC_Channel = ROLL_ADC_CH;
		ADC_Resoult = 0;
		ADC_GetValue();
		if(ADC_Resoult < ROLL_MIDDLE_POS_ADC_VAL)
		{
			Roll = ROLL_MIDDLE_POS_ADC_VAL-ADC_Resoult;
		}
		else if(ADC_Resoult > ROLL_MIDDLE_POS_ADC_VAL)
		{
			//负数，二进制补码格式
			ADC_Resoult -= ROLL_MIDDLE_POS_ADC_VAL;
			Roll = ~ADC_Resoult;
			Roll++;
		}

		//读取航向角电位器电压
		Yaw = 0;
		ADC_Channel = YAW_ADC_CH;
		ADC_Resoult = 0;
		ADC_GetValue();
		if(ADC_Resoult < YAW_MIDDLE_POS_ADC_VAL)
		{
			//负数，二进制补码格式
			Yaw = ~(YAW_MIDDLE_POS_ADC_VAL-ADC_Resoult);
			Yaw++;
		}
		else if(ADC_Resoult > YAW_MIDDLE_POS_ADC_VAL)
		{
			ADC_Resoult -= YAW_MIDDLE_POS_ADC_VAL;
			Yaw = ADC_Resoult;
		}
	}
	else
	{
		Pitch = 0;
		Roll = 0;
		Yaw = 0;
		Speed = 0;
	}

	Key = 0;
	ADC_Channel = KEY_ADC_CH;
	ADC_Resoult = 0;
	ADC_GetValue();
	Key_Noise_Filter();
	if((ADC_Resoult > KEY1_ACTIVE_ADC_VAL_LOW) && (ADC_Resoult<KEY1_ACTIVE_ADC_VAL_HIGH))
	{
		Key = 0x01;
	}
	else if((ADC_Resoult > KEY2_ACTIVE_ADC_VAL_LOW) && (ADC_Resoult<KEY2_ACTIVE_ADC_VAL_HIGH))
	{
		Key = 0x02;
	}
	else if((ADC_Resoult > KEY3_ACTIVE_ADC_VAL_LOW) && (ADC_Resoult<KEY3_ACTIVE_ADC_VAL_HIGH))
	{
		Key = 0x04;
	}
	else if((ADC_Resoult > KEY4_ACTIVE_ADC_VAL_LOW) && (ADC_Resoult<KEY4_ACTIVE_ADC_VAL_HIGH))
	{
		Key = 0x08;
	}
	else if((ADC_Resoult > KEY5_ACTIVE_ADC_VAL_LOW) && (ADC_Resoult<KEY5_ACTIVE_ADC_VAL_HIGH))
	{
		Key = 0x10;
	}
	else if((ADC_Resoult > KEY6_ACTIVE_ADC_VAL_LOW) && (ADC_Resoult<KEY6_ACTIVE_ADC_VAL_HIGH))
	{
		Key = 0x20;
	}

	if(Comm_CurrentStatus == STATUS_CONNECTED)
	{
		if(Key || Speed)
		{
			Comm_Data[0] = Speed;		
			Comm_Data[1] = Yaw;		
			Comm_Data[2] = Roll;		
			Comm_Data[3] = Pitch;	
			Comm_Data[4] = Key;
			Comm_SendData();
		}
	}
}



void Key_Noise_Filter_Init(void)
{
	Filter_Data[0] = 0;
	Filter_Data[1] = 0;
	Filter_Data[2] = 0;
}


void Key_Noise_Filter(void)
{
	uint16_t temp,i;
	//新值占结果比重10%，上一次占40%，上上次占30%，上上上次占20%
	temp = Filter_Data[2]<<1;
	temp += Filter_Data[0]<<2;
	temp += Filter_Data[1] + Filter_Data[1] + Filter_Data[1] + ADC_Resoult;
	i = 0;
	while(temp >= 10)
	{
		temp -= 10;
		i++;
	}
	if(temp >= 5) i++;		//四舍五入
	ADC_Resoult = i;
	Filter_Data[2] = Filter_Data[1];
	Filter_Data[1] = Filter_Data[0];
	Filter_Data[0] = i;
}





















