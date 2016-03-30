
#include "Battery.h"
#include "mini51series.h"
#include "adc.h"
#include "stdio.h"

uint32_t u32Flag;
uint32_t u32Result;

void BatteryCheckInit(void)
{
	CLK_EnableModuleClock(ADC_MODULE);
	CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL1_ADC_S_HIRC, CLK_CLKDIV_ADC(6));
	
	/* Set P3 multi-function pin ADC channel 5 input*/
   SYS->P3_MFP = SYS_MFP_P32_STADC;

	//关闭数字通道
   /* Analog pin OFFD to prevent leakage */
   P3->OFFD |= (1 << 2) << GPIO_OFFD_OFFD_Pos;
	
	// Enable channel 5
    ADC_Open(ADC, 0, 0, 0x01 << 5);
	
	// Power on ADC
    ADC_POWER_ON(ADC);
	
	// Enable ADC convert complete interrupt
    ADC_EnableInt(ADC, ADC_ADF_INT);
    NVIC_EnableIRQ(ADC_IRQn);
	
}

void ADC_IRQHandler(void)
{
    // Get ADC comparator interrupt flag
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    // Get ADC convert result
    //printf("Convert result is %x\n", (uint32_t)ADC_GET_CONVERSION_DATA(ADC, 0));
		u32Result = (uint32_t)ADC_GET_CONVERSION_DATA(ADC, 0);
	
    ADC_CLR_INT_FLAG(ADC, u32Flag);
}

//检查电池电压
void BatteryCheck(void)
{
	
	/* 开始转换 */
	ADC_START_CONV(ADC);
	 
	//while (u32Flag == 0);/*等待转换完成*/
	/* 取得转换结果 */
	//u32Result = ADC_GET_CONVERSION_DATA(ADC, 0);
	//printf("Channel 5 conversion result is 0x%x\n", u32Result);
	
	//ADC_CLR_INT_FLAG(ADC, u32Flag);

}

//获取电池电压
uint32_t GetBatteryAD(void)
{
	return u32Result;
}
