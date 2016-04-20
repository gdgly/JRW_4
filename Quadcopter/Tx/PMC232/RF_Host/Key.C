#include <stdint.h>
#include "Key.h"
#include "adc.h"
#include "Comm.h"


//俯仰角Pitch，偏航角Yaw，翻滚角Roll
uint8_t Pitch,Yaw,Roll,Throttle,Key;

uint8_t Filter_Data[3];
void Key_Noise_Filter(void);


void Key_Process(void)
{
	Key = 0;
	ADC_Channel = KEY_ADC_CH;
	ADC_Result = 0;
	ADC_GetValue();
	Key_Noise_Filter();
	if(ADC_Result >0 )
	{
		if((ADC_Result > KEY1_ACTIVE_ADC_VAL_LOW) && (ADC_Result<KEY1_ACTIVE_ADC_VAL_HIGH))
		{
			Key = 0x01;
		}
		else if((ADC_Result > KEY2_ACTIVE_ADC_VAL_LOW) && (ADC_Result<KEY2_ACTIVE_ADC_VAL_HIGH))
		{
			Key = 0x02;
		}
		else if((ADC_Result > KEY3_ACTIVE_ADC_VAL_LOW) && (ADC_Result<KEY3_ACTIVE_ADC_VAL_HIGH))
		{
			Key = 0x03;
		}
		else if((ADC_Result > KEY4_ACTIVE_ADC_VAL_LOW) && (ADC_Result<KEY4_ACTIVE_ADC_VAL_HIGH))
		{
			Key = 0x04;
		}
//		else if((ADC_Result > KEY5_ACTIVE_ADC_VAL_LOW) && (ADC_Result<KEY5_ACTIVE_ADC_VAL_HIGH))
		{
//			Key = 0x10;
		}
//		else if((ADC_Result > KEY6_ACTIVE_ADC_VAL_LOW) && (ADC_Result<KEY6_ACTIVE_ADC_VAL_HIGH))
		{
//			Key = 0x20;
		}
	}
	

	if(Comm_CurrentStatus == STATUS_CONNECTED)
	{
		if(Key || Throttle)
		{
			Comm_Data[0] = Throttle;		
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
	temp += Filter_Data[1] + Filter_Data[1] + Filter_Data[1] + ADC_Result;
	i = 0;
	while(temp >= 10)
	{
		temp -= 10;
		i++;
	}
	if(temp >= 5) i++;		//四舍五入
	ADC_Result = i;
	Filter_Data[2] = Filter_Data[1];
	Filter_Data[1] = Filter_Data[0];
	Filter_Data[0] = i;
}





















