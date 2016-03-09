#include "FlashCtrl.h"
#include "Mini51Series.h"
#include "stdio.h"
#include "fmc.h"
#include "def.h"

uint32_t DATA_Flash_Start_ADD;

int  set_data_flash_base(uint32_t u32DFBA)
{
    uint32_t   au32Config[2];

    if (FMC_ReadConfig(au32Config, 2) < 0) {
        printf("\nRead User Config failed!\n");
        return -1;
    }

    if ((!(au32Config[0] & 0x1)) && (au32Config[1] == u32DFBA))
        return 0;

    FMC_ENABLE_CFG_UPDATE();

    au32Config[0] &= ~0x1;
    au32Config[1] = u32DFBA;

    if (FMC_WriteConfig(au32Config, 2) < 0)
        return -1;

    printf("\nSet Data Flash base as 0x%x.\n", DATA_FLASH_TEST_BASE);

    // Perform chip reset to make new User Config take effect
    SYS->IPRSTC1 = SYS_IPRSTC1_CHIP_RST_Msk;
    return 0;
}


void FlashInit()
{
	SYS_UnlockReg();
	FMC_Open();
	set_data_flash_base(DATA_FLASH_TEST_BASE);
	DATA_Flash_Start_ADD = FMC_ReadDataFlashBaseAddr();
	//printf("\nDATA_Flash_Start_ADD 0x%x.\n", DATA_Flash_Start_ADD);
	FMC_Close();
	SYS_LockReg();

	printf("Flash initilize - [OK]\n");
}

