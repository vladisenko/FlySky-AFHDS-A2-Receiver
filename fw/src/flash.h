#ifndef __flash_h_
#define __flash_h_

#include <stdint.h>


#define FLASH_PAGE_SIZE   	1024UL
#define FLASH_SIZE   				(16*1024UL)
#define FLASH_LAST_PAGE			(FLASH_BASE + (FLASH_SIZE - FLASH_PAGE_SIZE))


uint8_t SaveEEPROM (uint8_t *data, uint16_t num);
uint8_t LoadEEPROM (uint8_t *data, uint16_t num);


#endif
