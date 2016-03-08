//#include <stdio.h>
//#include "Def.h"
#include "LED.h"
#include "mini51series.h"
 

void LED_Init(void)
{
		GPIO_SetMode(P3, BIT6, GPIO_PMD_OUTPUT);        // For NuTiny-SDK-Mini51L
}


void UpdateLED()
{
		P36 = 0;
}
