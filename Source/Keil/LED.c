#include "LED.h"
#include "mini51series.h"
#include "Timer_Ctrl.h"

void LED_Init(void)
{
		GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);        // For NuTiny-SDK-Mini51L
}


void UpdateLED()
{
	static int STATUS = 0;
		STATUS = !STATUS;
		P36 = STATUS;	
}
