#include <stdint.h>
#include "Led.h"

#define LED PA.7

void TongleLed(void)
{
	if(LED) 
	{
		LED = 0; 
	}
	else 
	{
		LED = 1;
	}
}