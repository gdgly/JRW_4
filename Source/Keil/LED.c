#include "LED.h"
#include "mini51series.h"
#include "Timer_Ctrl.h"

uint8_t ledStatus = 0;

void LED_Init(void)
{
		GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);        // For NuTiny-SDK-Mini51L
}


void UpdateLED()
{
		ledStatus = !ledStatus;
		P36 = ledStatus;	
	//	P36 = 0;
}
