#include "LED.h"
#include "mini51series.h"
#include "Timer_Ctrl.h"

//#define NuTiny

uint8_t ledStatus = 0;
uint8_t ledLightLevel = 0;

void LED_Init(void)
{
	#ifdef NuTiny
		GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);        // For NuTiny-SDK-Mini51L
		P36 = 0;
	#else
		GPIO_SetMode(P2, BIT6, GPIO_PMD_OUTPUT);
		P26 = 0;
	#endif
	
	//GPIO_SetMode(P2, BIT2, GPIO_PMD_OUTPUT);
		
}


void UpdateLED()
{
		ledStatus = !ledStatus;
	
	#ifdef NuTiny
		P36 = ledStatus;        // For NuTiny-SDK-Mini51L
	#else
		P26 = ledStatus;
	#endif
	
//	PWM_ConfigOutputChannel(PWM, 0, 100, ledLightLevel);
//	
//	ledLightLevel += 10;
//	if(ledLightLevel >= 100) ledLightLevel = 0;
	
	
}
