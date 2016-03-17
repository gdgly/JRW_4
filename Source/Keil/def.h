#ifndef DEF_H
#define DEF_H
#include "stdint.h"

//#ifndef TRUE
//# define TRUE 1
//#endif
//#ifndef FALSE
//# define FALSE 0
//#endif

#ifndef NULL
#define NULL        0
#endif

#ifndef bool
	#define bool        uint8_t
#endif
	
#ifndef false
	#define false        0
#endif

#define TICK_FRAME_PERIOD 1

#define SYSTEM_TICK_FREQ 1000 /*1K*/

#define DATA_Flash_Start_ADD        0x3000

#endif //DEF_H
