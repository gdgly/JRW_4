#ifndef FLASHCTRL_H
#define FLASHCTRL_H
#include "stdint.h"

void FlashInit(void);
void DATA_FLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint8_t NumToWrite);
void DATA_FLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint8_t NumToRead);
 
#endif
